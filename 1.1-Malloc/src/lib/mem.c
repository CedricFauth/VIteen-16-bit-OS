#include "libc.h"
#include "mem.h"

#define MAGIC 0xFFFF // larger than actual heap so always the largest addr
#define HEAP_SIZE 0x8000

struct block {
    struct block *next;
    uint16_t size;
    uint8_t data[];
};

static uint8_t heap[HEAP_SIZE] = {0};

static struct block *head = NULL;

void print_heap() {
    struct block *ptr = head;

    if (head == NULL) {
        PRINTS("*heap not initialized*\n");
        return;
    } else if (head == MAGIC) {
        PRINTS("*heap is full*\n");
        return;
    }

    PRINTS("head\n|\n");
    while (ptr != MAGIC) {
        PRINTS("|  |addr:"); PRINTX(ptr); PRINTC('\n');
        PRINTS("|  |offs:"); PRINTX((uint16_t)ptr-(uint16_t)heap); PRINTC('\n');
        PRINTS("+->|size:"); PRINTX(ptr->size); PRINTC('\n');
        ptr = ptr->next;
        if (ptr != MAGIC) PRINTS("|\n");
    }
}

void malloc_init(){
	head = (struct block*) heap;
    head->next = MAGIC; // block is free but MAGIC marks that there is nothing after this block
    head->size = HEAP_SIZE - sizeof(struct block);
}

void *malloc(uint16_t size) {
    struct block **chunk_pp = &head, *next_p, *ret;

    if (size <= 0 || head == NULL || head == MAGIC) return NULL;
    
    // search chunk with enough space
    while (*chunk_pp != MAGIC && (*chunk_pp)->size < size) {
        chunk_pp = &(*chunk_pp)->next;
    }

    // not enough space found
    if (*chunk_pp == MAGIC) return NULL;

    //PRINTS("chunk found\n");

    next_p = (*chunk_pp)->next;
    ret = *chunk_pp;
    // if more space than needed split chunk
    if ((*chunk_pp)->size > size + sizeof(struct block)) {
        next_p = (struct block*) ((*chunk_pp)->data + size);
        next_p->next = (*chunk_pp)->next;
        next_p->size = (*chunk_pp)->size - size - sizeof(struct block);
        (*chunk_pp)->size = size;
    }

    ret->next = MAGIC;
    *chunk_pp = next_p;
    
    return ret->data;
}

// if merge successful, returns first else second
struct block *try_merge(struct block *first, struct block *second) {

    // check if blocks are next to each other
    if (first->data + first->size != second) return second;

    DEBUGS("MERGE: "); DEBUGX(first); DEBUGS(" AND "); 
    DEBUGX(second); DEBUGC('\n');

    first->next = second->next;
    first->size = first->size + sizeof(*second) + second->size;

    second->next = NULL;
    second->size = 0;
    return first;
}

struct block *get_block_before(struct block *chunk) {
    struct block *run = head;
    while (run->next < chunk) {
        run = run->next;
    }
    return run;
}

void free(void *p) {
    struct block *chunk, *before;
    if (p == NULL || p == MAGIC) return;

    chunk = (struct block*) ((uint16_t)p-sizeof(struct block));
    DEBUGS("FREE: ");
    DEBUGX(chunk);
    DEBUGC('\n');

    if (chunk->next != MAGIC /*|| chunk == head*/) return;

    if (head > chunk) {
        chunk->next = head;
        head = chunk;
    } else {
        before = get_block_before(chunk);
        chunk->next = before->next;
        before->next = chunk;
        chunk = try_merge(before, chunk);
    }
    try_merge(chunk, chunk->next);
    
    /*
    adr_pp = get_block_before(chunk);
    next = *adr_pp
    *adr_pp = */
}
