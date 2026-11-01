#include "include_asm.h"

extern int func_00283D38(int a, int b, float c);
extern float func_00283B98(float a, float b);
extern float func_00283198(float a);
extern int func_00283D38(int a, int b, float c);
extern unsigned short *D_L14_001FB060[];
extern int D_L14_001B25B8;
extern unsigned char *D_L14_001B259C_base[3] __asm__("D_L14_001B259C") __attribute__((sda));
typedef struct {
    char pad0[0x220];
    float vec[4];
    char pad1[0x324 - 0x230];
    float scale;
    float angle;
    float blend;
    int stamp;
} L14Cfg;
typedef struct {
    char pad0[0x20];
    unsigned char kind;
    unsigned char group;
    char pad1[0x31 - 0x22];
    unsigned char live;
    char pad2[0x68 - 0x32];
    L14Cfg *cfg;
    char pad3[0x78 - 0x6C];
    int tint;
    char pad4[0xAA - 0x7C];
    short cls;
} L14Obj;
typedef struct {
    int a;
    int b;
} L14ColorPair;
extern void func_L14_00428BA0(L14Obj *);
extern L14ColorPair D_L14_001B18C0[];
extern int D_L14_001B20C8;
extern void func_0029FC20(void *moby, int joint, void *out);
extern void func_L00_002E6CF0(void *, void *);

/* Advances the owner's pulse (the angle, then the blend it gives), tints the owner with the
   first colour pair and, when its stamp is not the current one, refreshes every live class-0x112B
   entity of its group (joint 0 position into +0x220, then the stamp) and queues
   func_L14_00428BA0 for the owner. */
void func_PAL_L14_0042E150(L14Obj *self)
{
    L14Cfg *state = self->cfg;
    L14ColorPair colors = D_L14_001B18C0[0];
    unsigned short *p;
    L14Obj *e;
    L14Cfg *s0;
    float angle;
    float blend;

    angle = func_00283B98(state->angle, 0.25132746f);
    state->angle = angle;
    blend = func_00283198(angle) * 0.5f + 0.5f;
    state->blend = blend;
    self->tint = func_00283D38(colors.a, colors.b, blend);
    if (state->stamp != D_L14_001B20C8) {
        for (p = D_L14_001FB060[self->group];
             self->group != 0xFF && self->group <= D_L14_001B25B8 && p != 0 &&
             ((p != 0 && (short)p[-1] >= 0) || p == D_L14_001FB060[self->group]);
             p++) {
            e = (L14Obj *)(D_L14_001B259C_base[0] + ((*p & 0x7FFF) << 8));
            if (e == 0)
                break;
            if (e->live != 0) {
                if (e->cls == 0x112B) {
                    /* two tests, as retail has them: `!= 0xFE && != 0xFD` is folded into one */
                    if (e->kind != 0xFE) {
                        if (e->kind != 0xFD) {
                            s0 = e->cfg;
                            func_0029FC20(e, 0, &s0->vec);
                            s0->stamp = D_L14_001B20C8;
                        }
                    }
                }
            }
        }
        func_L00_002E6CF0((void *)func_L14_00428BA0, self);
    }
}
