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

extern ClassDispatchRecord g_class_dispatch_table[];

extern void (*g_moby_class_updates[])(char *);
extern void (*g_moby_class_updates_second[])(char *);
extern int g_class_cache_count MACRO_ADDR;
extern int g_class_cache_next MACRO_ADDR;

/* Looks up a moby class in the dispatch table and queues its update function in one of two lists. */
void moby_queue_class_update(int classId, int noHeader)
{
    int i = 0;

    while (g_class_dispatch_table[i].classId != -1) {
        if (g_class_dispatch_table[i].classId == classId)
            break;
        i++;
    }
    if (noHeader) {
        g_moby_class_updates_second[g_class_cache_next] = g_class_dispatch_table[i].update;
    } else {
        g_moby_class_updates[g_class_cache_count] = g_class_dispatch_table[i].update;
    }
}
