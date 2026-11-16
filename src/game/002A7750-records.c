#include "common.h"
struct ImpactQueueState { char pad[20]; int index; };
extern struct ImpactQueueState g_collision_hit;
struct ImpactQueueEntry { int __attribute__((mode(TI))) a, b; int kind, flags; unsigned char c,d; unsigned short e; float strength; int f; float g; char * owner; int h; };
extern struct ImpactQueueEntry g_impact_queue[];
extern void vec_clear_128(void *);
extern float FastVecLength(void *);

/* Adds a hit effect to the impact queue for an object, merging with its earlier one if that is stronger. */
void part_queue_impact_effect(char *object, int kind, int bits, void *position, void *vector, float strength) {
    int index=g_collision_hit.index;
    int flags=0;
    struct ImpactQueueEntry *entry;
    if ((unsigned char)object[0xA8]!=255) {
        struct ImpactQueueEntry *entry=&g_impact_queue[(unsigned char)object[0xA8]];
        if (entry->owner==object) {
            if (strength<entry->strength) {
                entry->flags|=bits;
                return;
            }
            flags=entry->flags;
        }
    }
    entry=&g_impact_queue[index];
    entry->flags=bits|flags;
    entry->kind=kind;
    entry->owner=object;
    entry->strength=strength;
    entry->g=strength;
    entry->h=0;
    if(FastVecLength(vector)>0.0001f) entry->f=1;
    else entry->f=0;
    qcopy(&g_impact_queue[index].a,position);
    qcopy(&g_impact_queue[index].b,vector);
    object[0xA8]=index;
    g_collision_hit.index=(index+1)&63;
}

