
#include "keyboard.h"

static char key_to_ascii[] = {
	 0,		ESC,	'1',	'2',
	'3',	'4',	'5',	'6',
	'7',	'8',	'9',	'0',
	'-',	'=',	 BACK,	 TAB,
	'q',	'w',	'e',	'r',
	't',	'y',	'u',	'i',
	'o',	'p',	'[',	']',
	ENTER,	 0,		'a',	's',
	'd',	'f',	'g',	'h',
	'j',	'k',	'l',	';',
	'\'',	'`',	 0,		'\\',
	'z',	'x',	'c',	'v',
	'b',	'n',	'm',	',',
	'.',	'/',	 0,		'*',
	 0,		' '	};

static char above_num[] = {')','!','@','#','$','%','^','&','*','('};

static struct {
	bool_t ctrl;
	bool_t alt;
	bool_t shift;
	char ascii;
} keys = {0,0,0,0};

void translate_scancode(int set, uint16_t scancode, int break_code) {
	if (break_code) {
		if (scancode == 0x1D) keys.ctrl = 0;
		else if (scancode == 0x2A || scancode == 0x36) keys.shift = 0;
		else if (scancode == 0x38) keys.alt = 0;
	} else {
		if (scancode == 0x1D) keys.ctrl = 1;
		else if (scancode == 0x2A || scancode == 0x36) keys.shift = 1;
		else if (scancode == 0x38) keys.alt = 1;
		else if (scancode < 0x3A) {
			keys.ascii = key_to_ascii[scancode];
			if (keys.shift){
				if(keys.ascii >= 'a' && keys.ascii <= 'z' ) {
					keys.ascii = keys.ascii + 'A'-'a';
				} else if (keys.ascii >= '0' && keys.ascii <= '9' ) {
					keys.ascii = above_num[keys.ascii-'0'];
				}
				else if (keys.ascii == ';') keys.ascii = ':';
				else if (keys.ascii == '\'') keys.ascii = '\"';
				else if (keys.ascii == '-') keys.ascii = '_';
				else if (keys.ascii == '=') keys.ascii = '+';
			} 
			DEBUGX(keys.ctrl);
			DEBUGX(keys.alt);
			DEBUGX(keys.shift);
			DEBUGC('\n');
			DEBUGC(keys.ascii);
			DEBUGC('\n');
			//DEBUGX(scancode);
			//DEBUGS("\n");
		}
	}
}

// from https://www.lowlevel.eu/wiki/Keyboard_Controller

void keyboard(uint8_t scancode) {
    int break_code = 0;
 
    // Status-Variablen fuer das Behandeln von e0- und e1-Scancodes
    static int e0_code = 0;
    // Wird auf 1 gesetzt, sobald e1 gelesen wurde, und auf 2, sobald das erste
    // Datenbyte gelesen wurde
    static int e1_code = 0;
    static uint16_t e1_prev = 0;

    // Um einen Breakcode handelt es sich, wenn das oberste Bit gesetzt ist und
    // es kein e0 oder e1 fuer einen Extended-scancode ist
    if ((scancode & 0x80) &&
        (e1_code || (scancode != 0xE1)) &&
        (e0_code || (scancode != 0xE0)))
    {
        break_code = 1;
        scancode = scancode & ~0x80;
    }
 
    if (e0_code) {
        // Fake shift abfangen und ignorieren
        if ((scancode == 0x2A) || (scancode == 0x36)) {
            e0_code = 0;
            return;
        }
        translate_scancode(1, scancode, break_code);
        e0_code = 0;
    } else if (e1_code == 2) {
        // Fertiger e1-Scancode
        // Zweiten Scancode in hoeherwertiges Byte packen
        e1_prev = e1_prev | ((uint16_t) scancode << 8);
        translate_scancode(2, e1_prev, break_code);
        e1_code = 0;
    } else if (e1_code == 1) {
        // Erstes Byte fuer e1-Scancode
        e1_prev = scancode;
        e1_code = e1_code + 1;
    } else if (scancode == 0xE0) {
        // Anfang eines e0-Codes
        e0_code = 1;
    } else if (scancode == 0xE1) {
        // Anfang eines e1-Codes
        e1_code = 1;
    } else {
        // Normaler Scancode
        translate_scancode(0, scancode, break_code);
    }


}