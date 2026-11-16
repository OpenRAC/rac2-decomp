#include "include_asm.h"
#include "names.h"
typedef struct {
    float f0;
    float f4;
    float f8;
    float f12;
    float f16;
    float f20;
    unsigned char f24;
    unsigned char f25;
    short f26;
    unsigned char f28;
    unsigned char f29;
    unsigned char f30;
    unsigned char f31;
    unsigned char pad32[16];
    short f48;
    short f50;
    int f52;
    int f56;
    int f60;
} PoolRecord64;
extern PoolRecord64 g_cam_l16_override_slots[];

/* Finds a free camera override slot, fills it with starting values and returns it, or returns 0 if all are used. */
PoolRecord64 *cam_alloc_override_slot_pal(int kind)
{
    PoolRecord64 *p = g_cam_l16_override_slots;
    int i;

    for (i = 0; i < 32; i++) {
        if (p->f29 == 0) {
            p->f0 = -1.0f;
            p->f4 = -1.0f;
            p->f8 = -1.0f;
            p->f12 = -1.0f;
            p->f16 = -1.0f;
            p->f20 = -1.0f;
            p->f28 = kind;
            p->f52 = 6;
            p->f50 = 100;
            p->f29 = 1;
            p->f56 = -1;
            p->f24 = 0;
            p->f25 = 0;
            p->f26 = 0;
            p->f30 = 0;
            p->f31 = 0;
            p->f60 = 0;
            p->f48 = 0;
            return p;
        }
        p++;
    }
    return 0;
}
