#include "common.h"
extern void func_002A7750(void *, int, int);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern void func_L04_0043BEE8(void *);
extern float func_002AA2E8(void *, float, float);
extern void *func_0032C700(void *, int, float, int, int, int, int, int, int, int, int, int, int, float);
extern void func_002A0488(void *, int, int, int);
extern void func_0029F338(void *);
extern void func_L04_0043BE40(void *);
extern int func_002AD0E0(void *, void *, void *, void *, void *, void *);
extern float D_L04_001B1394 SDATA(D_L04_001B1394);
extern float D_L04_001B1398 SDATA(D_L04_001B1398);
extern int D_L04_001B139C SDATA(D_L04_001B139C);
extern int D_L04_001B13A0 SDATA(D_L04_001B13A0);
extern int D_L04_001B13A4 SDATA(D_L04_001B13A4);
extern int D_L04_001B13A8 SDATA(D_L04_001B13A8);
extern int D_L04_001B13AC SDATA(D_L04_001B13AC);
extern int D_L04_001B13B0 SDATA(D_L04_001B13B0);
extern int D_L04_001B13B4 SDATA(D_L04_001B13B4);
extern int D_L04_001B13B8 SDATA(D_L04_001B13B8);
extern int D_L04_001B13BC SDATA(D_L04_001B13BC);
/* Updates a spark burst: waits, grows along its path with sparkles, then explodes and fades out. */
void func_L04_0043BC58(unsigned char *moby)
{
    float temporary[4];
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    switch (moby[0x20]) {
    case 0:
        SetMobyState(moby, 1, -1);
        break;
    case 1:
        AddDrawCallbackToList1(DrawSparkBurstGlows, moby);
        ApproachValue(vars + 0x4c, 1.0f, *(float *)(vars + 0x5c));
        if (*(float *)(vars + 0x4c) >= 1.0f) {
            SetMobyState(moby, 2, -1);
            SpawnExplosion(vars + 0x20, 0, D_L04_001B1398, D_L04_001B139C, D_L04_001B13A0, D_L04_001B13A4, D_L04_001B13A8, D_L04_001B13AC, D_L04_001B13B0, D_L04_001B13B4, D_L04_001B13B8, D_L04_001B13BC, *(int *)(vars + 0x44), 20.0f);
        }
        break;
    case 2:
        if (!(*(float *)(vars + 0x58) < 1.0f)) {
            *(unsigned short *)(*(unsigned char **)(vars + 0x48) + 0x34) = *(unsigned short *)(vars + 0x50);
            set_moby_color(*(void **)(vars + 0x48), vars[0x54], vars[0x55], vars[0x56]);
            MarkMobySpawned(moby);
            return;
        }
        ApplyFadeColorToLinkedMoby(moby);
        ApproachValue(vars + 0x58, 1.0f, D_L04_001B1394 * 0.016666668f);
        break;
    }
    if (*(int *)(vars + 0x40))
        TransformPointAndRotationByParent(moby, *(void **)(vars + 0x40), vars, temporary, vars, temporary);
    if (*(int *)(vars + 0x44)) {
        unsigned char *other = *(unsigned char **)(vars + 0x48);
        TransformPointAndRotationByParent(other, *(void **)(vars + 0x44), other + 0x10, other + 0xf0, other + 0x10, other + 0xf0);
        qcopy(vars + 0x20, other + 0x10);
    }
}
