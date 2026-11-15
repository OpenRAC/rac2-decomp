#include "include_asm.h"
#include "names.h"

#define MACRO_ADDR __attribute__((section(".sdata")))

/* The class dispatch table: three-word records, each a class id, the function
   that updates that class and a shared auxiliary pointer, ended by a class id
   of -1. */
typedef struct {
    int classId;
    void (*update)(char *);
    void *aux;
} ClassDispatchRecord;

extern ClassDispatchRecord D_0026E880[];

extern void (*D_001CDF40[])(char *);
extern void (*D_001D04E0[])(char *);
extern int D_001B1B40 MACRO_ADDR;
extern int D_001B1B44 MACRO_ADDR;

/* Looks up a moby class in the dispatch table and queues its update function in one of two lists. */
void moby_queue_class_update(int classId, int noHeader)
{
    int i = 0;

    while (D_0026E880[i].classId != -1) {
        if (D_0026E880[i].classId == classId)
            break;
        i++;
    }
    if (noHeader) {
        D_001D04E0[D_001B1B44] = D_0026E880[i].update;
    } else {
        D_001CDF40[D_001B1B40] = D_0026E880[i].update;
    }
}
