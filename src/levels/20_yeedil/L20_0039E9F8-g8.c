#include "common.h"

/* Built with -mno-split-addresses (config/cflags.txt): retail reaches D_L20_001B308C
   with an absolute lui/lw pair each time it is read, so it is declared nosda here
   (L20_0039C448-g8.c reaches it through $gp and declares it sda). */

#define FLD(base, T, off) (((struct { u8 pad[off]; T v; } *)(base))->v)

extern float D_L20_001AED10 __attribute__((sda));
extern float D_L20_001AED0C __attribute__((sda));
extern char *D_L20_001B308C __attribute__((nosda));

extern float func_00283B98(float, float);
extern float func_00283C80(float, float);
extern float func_002AAA00(void *, float, float, float, float, void *, int);
extern float func_002AA548(char *, char *, float, float, float, float);
extern float func_00282C48(float);
extern int func_00282C30(int);
extern void func_00282C90(char *);
extern void func_002830C0(char *, char *, char *);

void func_L20_0039E9F8(char *obj) {
    char *state = FLD(obj, char *, 0x68);
    char *entry;
    float turn;
    float spin;
    float target;
    float r;

    entry = (char *)((FLD(state, int, 0x84) << 7) + (unsigned int)D_L20_001B308C);
    turn = D_L20_001AED10 * 0.00027777778f;
    spin = D_L20_001AED0C * 0.016666668f;
    target = FLD(entry, float, 0x78);
    if (FLD(state, int, 0x190) < 0) {
        target = func_00283B98(target, 3.1415927f);
    }
    r = func_00283C80(FLD(obj, float, 0xF8), target);
    if (r > 0.017453294f) {
        func_002AAA00(obj + 0xF8, target, 0.00087266474f, 0.00087266474f, 0.052359886f,
                      state + 0x19C, 0);
    } else {
        func_002AA548(state + 0x194, state + 0x198, (float)FLD(state, int, 0x190), turn,
                      turn, spin);
        r = FLD(state, float, 0x194) * (float)FLD(state, int, 0x190);
        if (r > 0.0f) {
            target = func_00282C48(FLD(state, float, 0x194));
            if ((float)func_00282C30(FLD(state, int, 0x190)) <= target) {
                FLD(state, int, 0x190) = -FLD(state, int, 0x190);
            }
        }
    }
    func_00282C90(obj + 0x10);
    FLD(obj, float, 0x10) = FLD(state, float, 0x194);
    func_002830C0(obj + 0x10, obj + 0x10, D_L20_001B308C + (FLD(state, int, 0x84) << 7));
}
