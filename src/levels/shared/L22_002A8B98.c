#include "include_asm.h"

extern char D_00189E20[];

extern int D_001A79F0;

extern int D_001A73A0;

extern unsigned char D_00139568[];

extern char D_L22_002645F0[];

extern char D_L22_001B1920[];

extern void func_L00_002D24B8(void);

extern void func_L22_002C9898(int mode, int flag);

extern void func_L00_003B09F8(void);

extern int func_L00_002ADEA0(int index);

/* Loads the level's tuning constants and starts the two subsystems. */
INCLUDE_ASM("asm/levels", func_L22_002A8B98);

/* Picks the shop entry the level's table names for the current progress state. */
INCLUDE_ASM("asm/levels", func_L22_002A8CE0);


extern void func_L00_002D36E0(void *, int, float, float, float);
extern void func_002AA2E8(float *, float, float);
extern int D_00138320;
extern int func_L00_0032EF10(int, int, int);
extern int func_L22_003B9428(void *);
extern void func_L00_00310C88(void *, void *);
extern void *func_L00_00310BC8(void *, int);
extern void func_L00_00311080(void *, void *, int, int, int, int);
extern void func_L00_00310D30(void *, void *);
extern void func_00282948(void *);
extern void func_0029FCC0(void *, int, void *);
extern void func_002AFD88(void *, void *, float, float, float);
/* the two calls whose targets differ between levels 22 and 23 */
extern void ref_L22_002AA678_00(void *, void *, int);
extern void ref_L22_002AA678_01(void *, void *, int, int, int);

typedef struct {
    int unk0;
    int unk4;
    int unk8;
    int unkC;
} Counts_002AA678;

typedef struct {
    char pad0[5];
    unsigned char flags;
    char pad6[2];
    float fade;
    char padC[0x21 - 0xC];
    unsigned char state;
    char pad22[0x28 - 0x22];
    float unk28;
} Effect_002AA678;

typedef struct {
    char pad0[0x1E0];
    short unk1E0;
    char pad1E2[0x1870 - 0x1E2];
    Effect_002AA678 *effect; /* 0x1870 */
    char pad1874[0x187C - 0x1874];
    int active;              /* 0x187C */
    int fading;              /* 0x1880 */
    int timer;               /* 0x1884 */
    Counts_002AA678 *counts; /* 0x1888 */
    char pad188C[0x2290 - 0x188C];
    void *unk2290;
    int unk2294;
} Hero_002AA678;

/* Every access names the resident block through a struct cast, so the address's
   %hi stays in one saved register and each stretch of the body re-materialises
   its own %lo base. */
#define HERO ((Hero_002AA678 *)D_00189E20)

/* Per-frame update of the hero's effect slot (0x1870): spends the counted charges
   on the two level-specific actions, fades the effect out (releasing it at zero)
   or in, and creates it when it is allowed and absent. */
void func_L22_002AA678(void) {
    float v[4];
    int available;
    int i;

    if (HERO->unk1E0)
        return;
    if (HERO->unk2294 == 1 && func_L00_0032EF10(16, 7, 0) && !func_L22_003B9428(HERO->unk2290) &&
        HERO->counts->unkC) {
        func_L00_002D36E0(v, 1, 2.0f, -2.1f, 8.7f);
        ref_L22_002AA678_00(HERO->unk2290, v, 1);
        HERO->counts->unkC--;
    }
    available = 1;
    if (!HERO->counts->unk8 || func_L22_003B9428(HERO->unk2290))
        available = 0;
    if ((unsigned)(HERO->unk2294 - 0x5D) <= 1)
        available = 0;
    if (HERO->active) {
        if (!HERO->counts->unk8) {
            if (HERO->effect) {
                if (HERO->effect->flags & 2)
                    HERO->fading = 1;
                if (HERO->fading) {
                    if (HERO->effect->fade == 0) {
                        func_L00_00310C88(HERO->unk2290, &HERO->effect);
                        HERO->active = 0;
                        return;
                    }
                    func_002AA2E8(&HERO->effect->fade, 0, 0.07f);
                }
            } else
                HERO->active = 0;
        }
    }
    if (HERO->active) {
        if (!(D_00138320 & 0x20) || !available) {
            if (HERO->effect) {
                if (HERO->effect->flags & 2)
                    HERO->fading = 1;
                if (HERO->fading) {
                    if (HERO->effect->fade == 0) {
                        func_L00_00310C88(HERO->unk2290, &HERO->effect);
                        HERO->active = 0;
                        return;
                    }
                    func_002AA2E8(&HERO->effect->fade, 0, 0.07f);
                }
            } else
                HERO->active = 0;
        } else if (HERO->counts->unk8)
            HERO->fading = 0;
    }
    if (!HERO->active && available && func_L00_0032EF10(32, 8, 0)) {
        Effect_002AA678 *p = func_L00_00310BC8(HERO->unk2290, 2);
        HERO->fading = 0;
        HERO->effect = p;
        if (p) {
            HERO->active = 1;
            func_L00_00311080(HERO->unk2290, p, 13, 0, 9, 1);
        }
    }
    if (!HERO->active || !HERO->effect || HERO->fading)
        return;
    func_002AA2E8(&HERO->effect->fade, 1, 0.13f);
    HERO->effect->unk28 = 2;
    func_L00_00310D30(HERO->unk2290, HERO->effect);
    func_00282948(&HERO->timer);
    if (HERO->effect->state == 4 && !HERO->timer) {
        HERO->timer = 5;
        for (i = 0; i < 2; i++) {
            func_0029FCC0(HERO->unk2290, i + 3, v);
            func_002AFD88(HERO->unk2290, v, 1.4f, 0, 0);
            if (HERO->counts->unk8) {
                ref_L22_002AA678_01(HERO->unk2290, v, 0, 0, HERO->counts->unk0 != 0);
                HERO->counts->unk8--;
            }
        }
    }
}

#undef HERO

extern int D_00138320;

extern void func_L00_002AF7D0(void);

extern void func_L00_002B1F90(void);

extern void func_L00_00322EC8(void *p);

extern void func_L00_002D2E68(void);

extern void func_L00_002A6708(void);

extern void func_L00_002A53B8(void);

extern void func_0028B3D0(int a0, int a1, void *a2, void *a3, void *a4, int a5, int a6);

extern void func_L00_002F6B90(int a0);

extern void func_L22_002B7C70(void);

extern void func_002A677C(int a0);

/* the three routines the tuning table points at; their places differ per level */
extern void ref_L22_002B70F8_00(void);

extern void ref_L22_002B70F8_01(void);

extern void ref_L22_002B70F8_02(void);

typedef unsigned char u8;

typedef unsigned short u16;

typedef float f32;

/* Restarts the run: resets the racer's state block, plays the two subsystem
   start-ups, then arms the racer for the mode the caller asked for.
   The state block is reached through three block-scoped copies of its address,
   so each stretch of the body re-materialises the base instead of keeping it
   live across the calls; the three table entries are the routines the tuning
   table points at, whose places differ from level to level. */
void func_L22_002B70F8(int a0, int a1, void *a2) {
    char *s0 = D_00189E20;

    func_L00_002AF7D0();
    s0[0x22B6] = 1;
    func_L00_002B1F90();
    *(int *)(s0 + 0x2290) = *(int *)(s0 + 0xC18);
    func_L00_00322EC8(s0 + 0x18E0);
    func_L00_00322EC8(s0 + 0x1A30);
    *(int *)(*(int *)(s0 + 0x2290) + 0x9C) = -1;
    if (a0 != 4 || *(u8 *)(s0 + 0x22B4) != a0)
        func_L00_002D2E68();
    func_L00_002A6708();
    func_L00_002A53B8();
    {
        char *s1 = D_00189E20;

        *(u8 *)(s1 + 0x22B4) = (u8)a0;
        *(int *)(s1 + 0xC14) = (int)a2;
        *(int *)(s1 + 0x2290) = (int)a2;
    }
    if ((a0 & 0xFF) == 1) {
        if (D_00138320 & 0x10) {
            func_0028B3D0(0x23, 0, &ref_L22_002B70F8_00, &ref_L22_002B70F8_01,
                          &ref_L22_002B70F8_02, 0, 0);
            func_L00_002F6B90(3);
        }
    }
    func_L22_002B7C70();
    {
        char *s2 = D_00189E20;

        *(f32 *)(s2 + 0x250) = *(f32 *)(s2 + 0x258);
        *(f32 *)(s2 + 0x254) = *(f32 *)(s2 + 0x25C);
        *(u16 *)(*(int *)(s2 + 0x2290) + 0x34) |= 6;
        *(f32 *)(s2 + 0xC20) = 1.0f;
        *(f32 *)(s2 + 0xC24) = 1.0f;
        func_L00_002D24B8();
        func_002A677C(*(int *)(s2 + 0x2290));
        *(u16 *)(s2 + 0x24F2) = (u16)a1;
        switch (a0) {
        case 1:
            *(u16 *)(s2 + 0x24D4) = *(u16 *)(s2 + 0x24CC);
            *(int *)(s2 + 0x24CC) = *(int *)(s2 + 0x24D0);
            if (*(int *)(s2 + 0x24D0) >= 5)
                *(int *)(s2 + 0x24CC) = 4;
            break;
        case 2:
            *(int *)(s2 + 0x1874) = 0x4B0;
            break;
        }
    }
    func_L22_002C9898(a1, 2);
}


extern float func_00282E80(void *, void *);
extern void func_002AA2E8(float *, float, float);
extern void func_002AA3A8(float *, float *, float, float, float, float);

void func_L22_002B7C70(void) {
    char *g = D_00189E20;
    switch (*(u8 *)(g + 0x22B4)) {
    case 0:
        *(float *)(g + 0x258) = 0.8f;
        *(float *)(g + 0x25C) = 0.7f;
        *(float *)(g + 0x260) = 0.45f;
        break;
    case 1:
        *(float *)(g + 0x258) = 0.59999996f;
        *(float *)(g + 0x25C) = 0.45000002f;
        *(float *)(g + 0x260) = 0.3f;
        break;
    case 2:
        *(float *)(g + 0x258) = 5.25f;
        *(float *)(g + 0x25C) = 4.45f;
        *(float *)(g + 0x260) = 3.75f;
        break;
    }
    {
        char *g = D_00189E20;
        if (*(int *)(g + 0x229C) == 4) {
            if (*(short *)(g + 0x4AC) < *(int *)(g + 0x1B8) && !*(u8 *)(g + 0x49E))
                *(float *)(g + 0x25C) = *(float *)(g + 0x4B8);
        } else if (*(int *)(g + 0x2294) == 6) {
            *(float *)(g + 0x25C) = 0.5f;
        } else if (*(int *)(g + 0x2294) == 4) {
            *(float *)(g + 0x258) = 0.35000002f;
        } else if ((unsigned)(*(int *)(g + 0x229C) - 17) < 2) {
            *(float *)(g + 0x258) = 0;
            *(float *)(g + 0x25C) = 0;
        } else if (*(u8 *)(g + 0x1492) && *(int *)(g + 0x340)) {
            *(float *)(g + 0x258) = 0.8f;
            *(float *)(g + 0x25C) = 0.9f;
        } else {
            char *g = D_00189E20;
            if (*(int *)(g + 0x2294) == 0x7C)
                *(float *)(g + 0x260) = 0.8f;
        }
    }
    {
        char *g = D_00189E20;
        if (*(u8 *)(g + 0x287) && *(int *)(g + 0x22A4) != 18 && *(int *)(g + 0x22B0) != 18 &&
            (*(u8 *)(g + 0x22B4) != 0 || !(*(float *)(g + 0x254) < 0.53f)) &&
            *(int *)(g + 0x229C) != 17 && !*(u8 *)(g + 0x1494) &&
            !(func_00282E80(g + 0x240, g + 0x80) > *(float *)(g + 0x264) * 0.5f))
            return;
    }
    {
        float *speeds = (float *)(D_00189E20 + 0x250);
        char *g = (char *)speeds - 0x250;
        func_002AA2E8(speeds, *(float *)(g + 0x258), 0.02f);
        func_002AA2E8(speeds + 1, *(float *)(g + 0x25C), 0.02f);
        func_002AA3A8(speeds + 5, speeds + 6, *(float *)(g + 0x260), 0.02f, 0.3f, 0.06666667f);
    }
}



extern unsigned char D_0018C0D4;

extern void func_L22_002C9898(int a0, int a1);

/* plays one of three resident messages, picked by the type byte; the second argument
   is 1 or 2 depending on the caller's flag */
void func_L22_002CE468(int a0) {
    unsigned char type = D_0018C0D4;
    int mode = 1;

    if (a0 != 0)
        mode = 2;
    switch (type) {
    case 0:
        func_L22_002C9898(0, mode);
        break;
    case 1:
        func_L22_002C9898(0x3F, mode);
        break;
    case 2:
        func_L22_002C9898(0x56, mode);
        break;
    }
}
