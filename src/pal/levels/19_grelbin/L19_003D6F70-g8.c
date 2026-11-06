/* func_PAL_L19_003D6F70, the PAL copy of func_L19_003D2E38: the same C at 50 Hz, with the callees'
   PAL names, the frame counts and tuning values scaled by 5/6 and the per-frame steps by 6/5. */
#include "common.h"

/* Incomplete SDA arrays preserve the measured absolute accesses in this G8 unit. */
extern int D_L19_001A8F00[] __attribute__((sda));
extern int D_001A79F0[] __attribute__((sda));
extern unsigned int D_001A7390[] __attribute__((sda));
typedef struct {
    char pad[0x73C];
    unsigned int time;
} GrelbinTimestamp;
extern GrelbinTimestamp D_0018C958;
extern char D_00188660[];
extern int D_00138324 NOT_SDA;
extern unsigned short D_0018D090 NOT_SDA;
extern char D_L19_001B2424[] __attribute__((sda));
extern int D_L19_001B2728[] __attribute__((sda));
extern void *D_L19_001AC000[] __attribute__((sda));
extern int D_L19_001B06E8 __attribute__((sda));
extern int D_L19_001B06F0 __attribute__((sda));
extern int D_L19_001B06F4 __attribute__((sda));
extern int D_L19_001B06F8 __attribute__((sda));
extern float D_L19_001B070C __attribute__((sda));

extern void func_002A7750(char *, int, int);
extern void func_002AA2E8(void *, float, float);
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, void *);
extern void func_002E5F40(int, int);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_00282978(void *);
extern void func_0029F338(void *);
extern int func_002B3868(void *);
extern void func_002B4B70(int, int);
extern void func_L00_002E6CF0(void *, void *);
extern void func_PAL_L03_003E8000(void);
extern void func_L03_003E5218(void *);
extern void func_PAL_L03_003E6CA8(void *);
extern void func_L03_003E3018(void *);
extern void func_L03_003E2EC8(void *);
extern void func_PAL_L03_003E7C78(void *);
extern void func_L03_003E3430(void *);
extern void func_PAL_L03_003E8B88(void *);
extern int func_L03_003E3800(void *);
extern void func_PAL_00289730(int, int);

typedef struct {
    char pad[0x40];
    unsigned char kind;
    char gap[0xF];
    short field50, field52, field54, field56;
    float field58;
    short field5c, field5e, field60, field62, field64, field66, field68, field6a;
    char tail[0x10];
    int sound;
} GrelbinState;

void func_PAL_L19_003D6F70(char *m)
{
    GrelbinState *p;
    int i, sound, kind;

    p = *(GrelbinState **)(m + 0x68);
    if (D_L19_001A8F00[0] != 7) {
        if (*(unsigned char *)(m + 0x20))
            func_002A7750(m, 0, -1);
        return;
    }
    func_002AA2E8(D_L19_001B2424, 0.0f, 0.20000002f);
    D_L19_001B2728[0] = 1;
    switch (*(unsigned char *)(m + 0x20)) {
    case 0:
        for (i = 0; i < 52; i++)
            func_002E59F8(i);
        func_PAL_L03_003E6CA8(m);
        *(unsigned short *)(m + 0x34) |= 0x100;
        func_L03_003E3018(m);
        func_002A7750(m, D_001A79F0[0] == 11 ? 1 : 3, -1);
        break;
    case 1:
        if (((s32)D_001A7390[0] * 5 + 2) / 6 - D_0018C958.time > 900 || !D_0018C958.time)
            func_PAL_00289730(0xA43, 0x9A);
        else if (D_0018C958.time < ((s32)D_001A7390[0] * 5 + 2) / 6)
            D_0018C958.time = ((s32)D_001A7390[0] * 5 + 2) / 6;
        func_002A7750(m, 3, -1);
        break;
    case 2:
        if (!p->field68) {
            func_002A7750(m, 4, -1);
            break;
        }
        if (func_L03_003E3800(m)) {
            p->field6a = 1;
            func_L03_003E2EC8(m);
            func_002E5CF8(4, 0, m);
            func_002A7750(m, 3, -1);
        }
        break;
    case 3:
        func_PAL_L03_003E7C78(m);
        if (p->field56) {
            if (p->field66 != -1) {
                p->field52 = (unsigned short)p->field66;
                p->field66 = -1;
            } else {
                func_L03_003E3430(m);
            }
            kind = p->kind;
            kind ^= 255;
            if (kind == 0) {
                func_002E5CF8(0, 0, m);
            } else {
                sound = func_002E5CF8(1, 0, m);
                if (sound != -1)
                    func_002E5F40(sound, func_00283CF0(
                        func_00283CE0(p->field5e) / func_00283CE0(D_L19_001B06E8)
                        * 1024.0f) + 1024);
            }
            if (p->field5e > p->field60) {
                p->field60 = (unsigned short)p->field5e;
                p->field68 = (unsigned short)p->field68 + ((s32)D_L19_001B06F8 * 5 + 2) / 6;
                if (p->field68 > ((s32)D_L19_001B06F0 * 5 + 2) / 6)
                    p->field68 = ((s32)D_L19_001B06F0 * 5 + 2) / 6;
            }
            if (p->field5e == D_L19_001B06E8) {
                func_002E5CF8(5, 0, m);
                func_002A7750(m, 5, -1);
            } else {
                func_002A7750(m, 2, -1);
            }
        }
        break;
    case 4:
        if (p->field56) {
            if (p->field5c != p->field50) {
                p->field52 = (unsigned short)p->field5c;
                func_L03_003E2EC8(m);
                func_002E5CF8(2, 0, m);
            } else {
                p->field68 = ((s32)D_L19_001B06F4 * 5 + 2) / 6;
                p->field6a = 0;
                p->field60 = 0;
                func_002A7750(m, 2, -1);
            }
        } else {
            func_PAL_L03_003E7C78(m);
        }
        break;
    case 5:
        if (func_002B3868(m))
            *(unsigned short *)(m + 0x96) = 100;
        if (!*(unsigned short *)(m + 0x96)) {
            D_0018D090 = 65535;
            func_L03_003E5218(D_L19_001AC000[0]);
            goto destroy;
        }
        (*(unsigned short *)(m + 0x96))--;
        break;
    }
    if (D_00138324 & 16) {
        if (*(unsigned char *)(m + 0x20) == 5)
            func_L03_003E5218(D_L19_001AC000[0]);
    destroy:
        func_002B4B70(0, 0);
        func_0029F338(m);
        return;
    }
    if (*(unsigned char *)(m + 0x20) != 5 && p->field6a)
        func_00282978(&p->field68);
    if (p->field6a && p->field68) {
        char *s = D_00188660 + p->sound * 0x70;
        if (*(char **)(s + 0x88) != m || !*(unsigned char *)(s + 0x74))
            p->sound = func_002E5CF8(3, 4, m);
    } else {
        if (p->sound != -1) {
            char *s = D_00188660 + p->sound * 0x70;
            if (*(char **)(s + 0x88) == m && *(unsigned char *)(s + 0x74))
                func_002E59F8(p->sound);
        }
        p->sound = -1;
    }
    func_PAL_L03_003E8B88(m);
    p->field58 -= D_L19_001B070C * 0.020000001f;
    if (p->field58 < -1.0f)
        p->field58 += 1.0f;
    func_L00_002E6CF0(func_PAL_L03_003E8000, m);
}
