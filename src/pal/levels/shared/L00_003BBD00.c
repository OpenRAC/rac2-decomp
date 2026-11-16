#include "include_asm.h"

#include "common.h"
typedef struct NODE {
    char pad0[0x8];
    int f08;
    int f0C;
    char pad1[0x24 - 0x10];
    int f24;
    int f28;
    int f2C;
    unsigned char f30;
    char pad2[0x40 - 0x31];
    int f40;
    char pad3[0x68 - 0x44];
    void *f68;
    char pad4[0xB8 - 0x6C];
    int fB8;
    unsigned char fBC;
} NODE;
typedef struct V2 {
    float x;
    float y;
} V2;
extern V2 g_helper_hit_position;
extern void func_37CB80(void *, void *, float, void *);
extern NODE *func_3100D8();

void helper_update_hit_test_pal(NODE *a0)
{
    NODE *o = a0->f68;

    if (o->f24 == 0)
        return;
    if (o->f2C == 0) {
        func_37CB80(o, (char *)o + 0x10, 1.0f, 0);
    } else {
        V2 v = g_helper_hit_position;

        func_37CB80(o, (char *)o + 0x10, 1.0f, &v);
    }
}

