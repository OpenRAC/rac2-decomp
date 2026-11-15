#include "common.h"
typedef struct {
    char pad0[0x2290]; void *object;
} UpdateHeroBase;
extern UpdateHeroBase D_00189E20;
extern void func_L22_002AA480(void);
extern void func_L22_002AA678(void);
extern void func_002AFD88(void *, void *, float, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_0029FCC0(void *, int, void *);

extern void func_L00_002D24E8(void);
extern void func_L00_002B36E0(void);
extern void func_L00_002ACA08(void);
extern void func_L00_002ACF88(void *, void *, void *);
extern void func_L00_002B8930(void);
extern void func_L00_002B9BB0(int, void *, int);
extern void func_002E59F8(int);
extern void func_002A8C28(void *, void *, float, float, int, int, float, int, int);
extern float func_L00_002B9B38(void *, int);
extern float func_00283BE0(float, float);
extern void func_L22_002D0C98(void);
extern void func_L00_002AE0C8(void);
extern void func_L00_002B9CA8(void);
extern void func_L00_002A5368(void);
extern void func_L00_002A9600(void);
extern void func_L00_002A7958(void);
extern void func_L00_002A7748(void);
extern void func_L00_002A5840(void);
extern void func_L00_002A5CB0(void);
extern void func_L00_002A6008(void);
extern void func_002E5CF8(void *, int, void *);
extern void func_L00_003080D0(void *);
extern void func_L00_002A7A10(void);
extern void func_L00_002A9760(void);
extern void func_002A677C(void *);
extern char D_00188660[];
typedef struct {
    char pad0[0x11DC]; float rate;
    char pad11e0[0x12F8 - 0x11E0]; float negative_angle;
    char pad12fc[0x1334 - 0x12FC]; float field1334, field1338;
    char pad133c[0x13EC - 0x133C]; float field13ec;
    char pad13f0[0x1458 - 0x13F0]; float angle;
    char pad145c[0x1494 - 0x145C]; float field1494, field1498;
} UpdateCamera;
extern UpdateCamera D_L22_0025DE90;
extern int D_L22_001A8FF0;
/* Retail reads this byte only inside the mode-2 path (002AAD00..002AAD08).
 * Preserve that conditional access rather than speculating it before the guard.
 * Its owning allocation's extent is unknown, so retain an incomplete declaration. */
extern volatile unsigned char D_001A7A43[] MACRO_ADDR;
extern float D_L22_001A7CF8 __attribute__((sda));

void func_L22_002AAA30(void) {
    float v[4] __attribute__((aligned(16)));
    AdvanceHeroAnimation();
    UpdateHeroInputAndHistory();
    func_L00_002ACA08();
    {
        char *g = (char *)&D_00189E20;
        if (*(u8 *)(g + 0x22B4) == 1) {
            func_L00_002ACF88(g + 0x80, g + 0x90, g + 0x550);
            UpdateHeroMotionResponseParameters();
        }
        if (*(u8 *)(g + 0x22B4) == 2) {
            if (*(int *)(g + 0x2294) == 0x5B) {
                func_L00_002B9BB0(8, *(void **)(g + 0x2290), 10);
            } else {
                int n = *(int *)(g + 0x242C);
                if (n != -1) {
                    char *entry = D_00188660 + n * 0x70;
                    if (*(void **)(entry + 0x88) == *(void **)(g + 0x2290) && *(u8 *)(entry + 0x74))
                        func_002E59F8(n);
                }
                {
                    char *g = (char *)&D_00189E20;
                    *(int *)(g + 0x242C) = -1;
                }
            }
            {
                char *g = (char *)&D_00189E20;
                if (*(int *)(g + 0x33C)) {
                    func_002AFD88(*(void **)(g + 0x2290), v, 0, 0, 2.5f);
                    FastVecAdd(v, v, g + 0x80);
                    func_002A8C28(*(void **)(g + 0x2290), v, 4, 100, 0x80000, 0, 1, 1, 0);
                }
                if (*(short *)(g + 0x1454) && *(float *)(g + 0x24B8) > 0.15f && !*(u8 *)(g + 0x1456)) {
                    float angle;
                    {
                        UpdateCamera *camera = &D_L22_0025DE90;
                        camera->field1498 = 0.27f;
                        camera->field1494 = 0.037f;
                        camera->field1334 = 0.025f;
                        camera->field1338 = 0.27f;
                    }
                    if (D_L22_001A8FF0) angle = func_L00_002B9B38(g + 0x1440, 0);
                    else angle = fast_subtract_rotations(*(float *)(g + 0x1458), *(float *)(g + 0x98));
                    {
                        UpdateCamera *camera = &D_L22_0025DE90;
                        camera->angle = angle;
                        camera->negative_angle = -angle;
                    }
                }
            }
        }
    }
    func_L22_002D0C98();
    RebuildRegionObjectMembership();
    {
        char *g = (char *)&D_00189E20;
        if (!*(u8 *)(g + 0x22B4)) return;
        UpdateDelayedSounds();
        func_L00_002A5368();
        if (!*(u8 *)(g + 0x22B4)) return;
        func_L00_002A9600();
        func_L00_002A7958();
        ApplyHeroAxisScales();
        if (*(u8 *)(g + 0x22B4) == 1) {
            D_L22_0025DE90.rate = D_L22_001A7CF8;
            UpdateHeroGlowAndExtraManipulators();
            UpdateHeroJointEffect();
            func_L00_002A6008();
            if (*(char **)(g + 0x24E4)) {
                PlayMobySound(*(char **)(g + 0x24E4) + 0x10, 0, *(void **)(g + 0x2290));
                *(u16 *)(g + 0x2520) = 0x39;
                *(u16 *)(g + 0x2522) = *(u16 *)(g + 0x24E4);
            }
            *(int *)(g + 0x24E4) = 0;
        }
    }
    {
        char *pos = (char *)&D_00189E20 + 0x80;
        char *g = pos - 0x80;
        func_L00_003080D0(pos);
        if (*(u8 *)(g + 0x22B4) == 2) {
            if (*D_001A7A43) D_L22_0025DE90.field13ec = D_L22_001A7CF8 * 1.4f;
            if (*(short *)(g + 0x1E2) < 10000) ++*(u16 *)(g + 0x1E2);
            UpdateHeroGlowAndExtraManipulators();
            func_L22_002AA480();
            func_L22_002AA678();
            if ((*(u16 *)(*(char **)(g + 0x2290) + 0x34) ^ 1) & 1) {
                func_0029FCC0(*(void **)(g + 0x2290), 6, v);
                qcopy(pos + 0x1F90, v);
                func_L00_002A7A10();
            }
        }
        UpdateHeroMobyProbedHeightBounds();
    }
    func_002A677C(D_00189E20.object);
}
