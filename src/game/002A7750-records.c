#include "common.h"
struct ImpactQueueState { char pad[20]; int index; };
extern struct ImpactQueueState D_001BAF80;
struct ImpactQueueEntry { int __attribute__((mode(TI))) a, b; int kind, flags; unsigned char c,d; unsigned short e; float strength; int f; float g; char * owner; int h; };
extern struct ImpactQueueEntry D_001BF200[];
extern void func_00282C88(void *);
extern float func_00282DF0(void *);

void func_002A8F70(char *object, int kind, int bits, void *position, void *vector, float strength) {
    int index=D_001BAF80.index;
    int flags=0;
    struct ImpactQueueEntry *entry;
    if ((unsigned char)object[0xA8]!=255) {
        struct ImpactQueueEntry *entry=&D_001BF200[(unsigned char)object[0xA8]];
        if (entry->owner==object) {
            if (strength<entry->strength) {
                entry->flags|=bits;
                return;
            }
            flags=entry->flags;
        }
    }
    entry=&D_001BF200[index];
    entry->flags=bits|flags;
    entry->kind=kind;
    entry->owner=object;
    entry->strength=strength;
    entry->g=strength;
    entry->h=0;
    if(FastVecLength(vector)>0.0001f) entry->f=1;
    else entry->f=0;
    qcopy(&D_001BF200[index].a,position);
    qcopy(&D_001BF200[index].b,vector);
    object[0xA8]=index;
    D_001BAF80.index=(index+1)&63;
}

