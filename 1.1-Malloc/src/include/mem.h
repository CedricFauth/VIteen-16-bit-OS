#ifndef MEM_H
#define MEM_H

void malloc_init();
void print_heap();

void *malloc(uint16_t size);
void free(void *p);

#endif //MEM_H
