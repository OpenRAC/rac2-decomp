#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

extern float D_L02_001B1FC4 __attribute__((sda));

extern void func_002F2270(void *, void *, float);
extern void func_00322F98(void *, void *, float);
extern void func_002F1FF8(void *, void *, float);
extern void func_00324C28(void *, void *, void *);
extern void func_002F1F70(void *, void *, void *);
extern float func_002F3048(float, float);
extern void func_002EA180(void *, void *);
extern void func_L02_00422638(int);

/* Rebuilds the record's second frame and folds the resident angle step in. */
void func_L02_00422538(char *moby) {
    float buf[4];
    char *vars = *(char **)(moby + 0x68);
    char *mobyPos = moby + 0x10;
    char *frame = vars + 0x10;

    func_002F2270(buf, vars + 0x40, 1.0f);
    func_00322F98(buf, buf, *(float *)(vars + 0x30));
    func_002F1FF8(frame, vars, *(float *)(vars + 0x60));
    func_00324C28(frame, frame, buf);
    *(float *)(vars + 0x20) = -*(float *)(vars + 0x10);
    *(float *)(vars + 0x24) = -*(float *)(vars + 0x14);
    *(float *)(vars + 0x28) = -*(float *)(vars + 0x18);
    func_002F1F70(frame, mobyPos, frame);
    func_002F1F70(vars + 0x20, mobyPos, vars + 0x20);
    *(float *)(vars + 0x30) =
        func_002F3048(*(float *)(vars + 0x30), D_L02_001B1FC4 * 0.000290888245f);
    func_002EA180(DrawBeamEffectPasses, moby);
}
