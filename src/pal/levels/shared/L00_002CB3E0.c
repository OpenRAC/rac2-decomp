#include "include_asm.h"
/* func_PAL_L00_002CB3E0, the PAL copy of func_L00_002CB038. */
extern char D_00189E20_36[];

extern unsigned char D_001A7A80[] __attribute__((sda));
extern unsigned int D_00138320;
extern unsigned char D_00138180[];
extern unsigned int D_001A7390 __attribute__((sda));
extern int D_001A79F0 __attribute__((sda));
extern unsigned char D_L00_001B8C80[];

typedef struct {
    unsigned short count;
    unsigned short reserved;
    unsigned int best;
    unsigned int levels;
} Statistics;
extern Statistics D_0018C750[];

extern float func_00282E48(void *, void *);
/* Typed call shape: the EE assigns the GPR and FP banks independently of this order. */
extern char *func_L00_002AE888(void *, float, float, float, float, int, int);

/* keeps the hero's held target (0x1450) while both low pad bits are set: clears it on an ineligible screen, beyond 30 units or on release, records a statistic when the target stops being eligible; with no target and both bits set plus either in the next pad word, picks one from the camera's view and then from the hero's */
void func_PAL_L00_002CB3E0(void)
{
    char *hero = D_00189E20_36;
    int screen = *(int *)(hero + 0x1248);
    char *object;

    if (screen < 0 || !(D_001A7A80[screen] & 0x20) || *(int *)(hero + 0x2294) == 0x31) {
        *(int *)(hero + 0x1450) = 0;
        return;
    }
    object = *(char **)(hero + 0x1450);
    if (object) {
        if (30.0f < func_00282E48(hero + 0x80, object + 0x10))
            *(int *)(hero + 0x1450) = 0;
        if ((D_00138320 & 3) != 3)
            *(int *)(hero + 0x1450) = 0;
        if (!*(char **)(hero + 0x1450) || (*(unsigned short *)(*(char **)(hero + 0x1450) + 0x34) & 0x1000))
            return;
        *(int *)(hero + 0x1450) = 0;
        if (D_0018C750[36].count < 0xFFFF)
            D_0018C750[36].count++;
        if ((((int)(D_001A7390) * 5 + 2) / 6) > D_0018C750[36].best)
            D_0018C750[36].best = ((int)(D_001A7390) * 5 + 2) / 6;
        D_0018C750[36].levels = (D_0018C750[36].levels | (1u << D_001A79F0)) | 0x80000000u;
        return;
    }
    {
        unsigned char *pad = D_00138180;
        if ((*(unsigned int *)(pad + 0x1A0) & 3) == 3 && (*(unsigned int *)(pad + 0x1A4) & 3) != 0) {
            float radius = 25.0f;
            unsigned char *camera = D_L00_001B8C80;
            float nearAngle = 0.6108652949333191f;
            float farAngle = 1.2217305898666382f;
            char *found = func_L00_002AE888(camera + 0x370, radius, *(float *)(camera + 0x158), nearAngle, farAngle, 5, 1);
            *(char **)(hero + 0x1450) = found;
            if (!found)
                *(char **)(hero + 0x1450) = func_L00_002AE888(hero, radius, *(float *)(hero + 0x98), nearAngle, farAngle, 5, 1);
        }
    }
}
