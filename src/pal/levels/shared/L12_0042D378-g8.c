#include "include_asm.h"

typedef unsigned char u8;
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern int func_00283D38(int, int, float);
extern void func_0029FC20(char *, int, void *);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L12_004281D8(u8 *);
extern unsigned short *D_L12_001FB960[];
extern int D_L12_001B2EB8 __attribute__((sda));
extern u8 *D_L12_001B2E9C[3] __attribute__((sda));
extern int D_L12_001B29C8[3] __attribute__((sda));
extern int D_L12_001B29C8_s __asm__("D_L12_001B29C8") __attribute__((sda));
struct L12PairWord {
    int a;
    int b;
};
extern struct L12PairWord D_L12_001B21D0 __attribute__((nosda));
struct L12Kind348 {
    char pad[0x348];
    float f348;
    float f34C;
    int f350;
};
struct L12Kind348Entity {
    char pad0[0x20];
    u8 state;
    char pad1[0x10];
    u8 f31;
    char pad2[0x36];
    struct L12Kind348 *obj;
    char pad3[0x3E];
    short type;
};
struct L12Kind348Object {
    char pad0[0x21];
    u8 group;
    char pad1[0x46];
    struct L12Kind348 *obj;
    char pad2[0x0C];
    int f78;
};
extern struct L12PairWord D_L12_001B21F0;

/* Turns the object's angle and its mirrored scale into its word at +0x78; when the frame
   counter D_L12_001B29C8 differs from the object's word at +0x350, walks the object's group
   and refreshes every live entity of kind 0x11EB, then registers func_L12_004281D8. */
void func_PAL_L12_0042D5E8(struct L12Kind348Object *a0) {
    struct L12Kind348 *o = a0->obj;
    struct L12PairWord v = D_L12_001B21D0;
    float f;
    unsigned short *q;
    struct L12Kind348Entity *e;
    struct L12Kind348 *s0;

    f = func_00283B98(o->f348, 0.25132746f);
    o->f348 = f;
    f = func_00283198(f);
    o->f34C = f * 0.5f + 0.5f;
    a0->f78 = func_00283D38(v.a, v.b, o->f34C);
    if (o->f350 != D_L12_001B29C8_s) {
        for (q = D_L12_001FB960[a0->group];
             a0->group != 0xFF && a0->group <= D_L12_001B2EB8 && q != 0 &&
             ((q != 0 && (short)q[-1] >= 0) || q == D_L12_001FB960[a0->group]);
             q++) {
            e = (struct L12Kind348Entity *)(D_L12_001B2E9C[0] + ((*q & 0x7FFF) << 8));
            if (e == 0)
                break;
            if (e->f31 != 0 && e->type == 0x11EB && e->state != 0xFE && e->state != 0xFD) {
                s0 = e->obj;
                func_0029FC20((char *)e, 0, (char *)s0 + 0x240);
                s0->f350 = D_L12_001B29C8[0];
            }
        }
        func_L00_002E6CF0((void *)func_L12_004281D8, a0);
    }
}
