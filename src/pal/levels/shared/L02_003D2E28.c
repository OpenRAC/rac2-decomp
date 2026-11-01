#include "include_asm.h"

#include "common.h"
extern float func_00283198(float);
extern char *D_L02_001B359C __attribute__((sda));
extern char *D_L02_001FC060[];
extern float func_00283B98(float, float);
extern int D_L02_001B35B8 __attribute__((sda));
typedef int L02Word;
extern L02Word D_L02_001B35B8 __attribute__((sda));
extern int D_L02_001B35B8 __attribute__((sda));
extern void func_L02_003CEFD8(char *);
extern int D_L02_001B30C8 __attribute__((sda));
struct L02PairWord {
    int a;
    int b;
};
extern struct L02PairWord D_L02_001B00C0;
extern float func_00283B98(float, float);
extern int func_00283D38(int, int, float);
extern void func_0029FC20(char *, int, void *);
extern void func_L00_002E6CF0(void *, void *);
struct L02Kind330 {
    char pad[0x328];
    float f328;
    float f32C;
    int f330;
};
struct L02Kind330Entity {
    char pad0[0x20];
    unsigned char state;
    char pad1[0x10];
    unsigned char f31;
    char pad2[0x36];
    struct L02Kind330 *obj;
    char pad3[0x3E];
    short type;
};
struct L02Kind330Object {
    char pad0[0x21];
    unsigned char group;
    char pad1[0x46];
    struct L02Kind330 *obj;
    char pad2[0x0C];
    int f78;
};

/* Turns the object's angle and its mirrored scale into its word at +0x78; when the frame
   counter D_L02_001B30C8 differs from the object's word at +0x330, walks the object's group
   and refreshes every live entity of kind 0xA4E, then registers func_L02_003CEFD8. */
void func_PAL_L02_003D2E28(struct L02Kind330Object *a0) {
    struct L02Kind330 *o = a0->obj;
    struct L02PairWord v = D_L02_001B00C0;
    float f;
    unsigned short *q;
    struct L02Kind330Entity *e;
    struct L02Kind330 *s0;

    f = func_00283B98(o->f328, 0.25132746f);
    o->f328 = f;
    f = func_00283198(f);
    o->f32C = f * 0.5f + 0.5f;
    a0->f78 = func_00283D38(v.a, v.b, o->f32C);
    if (o->f330 != D_L02_001B30C8) {
        for (q = (unsigned short *)D_L02_001FC060[a0->group];
             a0->group != 0xFF && a0->group <= D_L02_001B35B8 && q != 0 &&
             ((q != 0 && (short)q[-1] >= 0) || q == (unsigned short *)D_L02_001FC060[a0->group]);
             q++) {
            e = (struct L02Kind330Entity *)(D_L02_001B359C + ((*q & 0x7FFF) << 8));
            if (e == 0)
                break;
            if (e->f31 != 0 && e->type == 0xA4E && e->state != 0xFE && e->state != 0xFD) {
                s0 = e->obj;
                func_0029FC20((char *)e, 0, (char *)s0 + 0x220);
                s0->f330 = D_L02_001B30C8;
            }
        }
        func_L00_002E6CF0((void *)func_L02_003CEFD8, a0);
    }
}

