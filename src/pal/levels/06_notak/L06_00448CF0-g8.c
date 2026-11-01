#include "include_asm.h"

#include "common.h"
extern u8 *D_L06_001FB3A0[];
extern unsigned char *D_L06_001B281C_base[3] __asm__("D_L06_001B281C") __attribute__((sda));
extern int D_L06_001B2838;
extern int D_L06_001B2348;
typedef struct {
    char pad0[0x220];
    float vec[4];
    char pad1[0x324 - 0x230];
    float scale;
    float angle;
    float blend;
    int stamp;
} L06Cfg;
typedef struct {
    char pad0[0x20];
    unsigned char kind;
    unsigned char group;
    char pad1[0x31 - 0x22];
    unsigned char live;
    char pad2[0x68 - 0x32];
    L06Cfg *cfg;
    char pad3[0x78 - 0x6C];
    int tint;
    char pad4[0xAA - 0x7C];
    short cls;
} L06Obj;
typedef struct {
    int a;
    int b;
} L06ColorPair;
extern void func_L06_00444300(L06Obj *);
extern L06ColorPair D_L06_001B1098[];
extern float func_00283B98(float, float);
extern float func_00283198(float);
extern int func_00283D38(int, int, float);
extern void func_0029FC20(void *moby, int joint, void *out);
extern void func_L00_002E6CF0(void *, void *);

/* Advances the owner's pulse (the angle, then the blend it gives), tints the owner with the
   colour pair and, when its stamp is not the current one, refreshes every live class-0xDB0
   entity of its group (joint 0 position into +0x220, then the stamp) and queues
   func_L06_00444300 for the owner. */
void func_PAL_L06_00448CF0(L06Obj *self)
{
    L06Cfg *state = self->cfg;
    L06ColorPair colors = D_L06_001B1098[0];
    unsigned short *p;
    L06Obj *e;
    L06Cfg *s0;
    float angle;
    float blend;

    angle = func_00283B98(state->angle, 0.25132746f);
    state->angle = angle;
    blend = func_00283198(angle) * 0.5f + 0.5f;
    state->blend = blend;
    self->tint = func_00283D38(colors.a, colors.b, blend);
    if (state->stamp != D_L06_001B2348) {
        for (p = (unsigned short *)D_L06_001FB3A0[self->group];
             self->group != 0xFF && self->group <= D_L06_001B2838 && p != 0 &&
             ((p != 0 && (short)p[-1] >= 0) || p == (unsigned short *)D_L06_001FB3A0[self->group]);
             p++) {
            e = (L06Obj *)(D_L06_001B281C_base[0] + ((*p & 0x7FFF) << 8));
            if (e == 0)
                break;
            if (e->live != 0) {
                if (e->cls == 0xDB0) {
                    /* two tests, as retail has them: `!= 0xFE && != 0xFD` is folded into one */
                    if (e->kind != 0xFE) {
                        if (e->kind != 0xFD) {
                            s0 = e->cfg;
                            func_0029FC20(e, 0, &s0->vec);
                            s0->stamp = D_L06_001B2348;
                        }
                    }
                }
            }
        }
        func_L00_002E6CF0((void *)func_L06_00444300, self);
    }
}
