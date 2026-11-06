#include "include_asm.h"

extern char D_00189E20[];
extern void func_L00_002D24B8(void);
extern void func_L22_002C9898(int mode, int flag);
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
extern void ref_L22_002B70F8_00(void);
extern void ref_L22_002B70F8_01(void);
extern void ref_L22_002B70F8_02(void);
typedef unsigned char u8;
typedef unsigned short u16;
typedef float f32;
extern void func_L22_002C9898(int a0, int a1);

/* func_PAL_L22_002AA488, the PAL copy of func_L22_002AA678: the same C, where the fade rates
   0.07f and 0.13f become 0.08400001f and 0.156f, the timer 5 becomes 4, and the three call
   arguments 7, 8 and 9 become 6, 7 and 7. func_00282948 is declared int, as at its other call
   sites: the ignored result keeps $v0 from the base load after the call. */
extern void func_L00_002D36E0(void *, int, float, float, float);
extern void func_002AA2E8(float *, float, float);
extern int D_00138320;
extern int func_L00_0032EF10(int, int, int);
extern int func_L22_003B9428(void *);
extern void func_L00_00310C88(void *, void *);
extern void *func_L00_00310BC8(void *, int);
extern void func_L00_00311080(void *, void *, int, int, int, int);
extern void func_L00_00310D30(void *, void *);
extern int func_00282948(void *);
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

/* Per-frame update of the hero's effect slot (0x1870): spends the counted charges
   on the two level-specific actions, fades the effect out (releasing it at zero)
   or in, and creates it when it is allowed and absent. */
void func_PAL_L22_002AA488(void) {
    float v[4];
    int available;
    int i;

    if (((Hero_002AA678 *)D_00189E20)->unk1E0)
        return;
    if (((Hero_002AA678 *)D_00189E20)->unk2294 == 1 && func_L00_0032EF10(16, 6, 0) && !func_L22_003B9428(((Hero_002AA678 *)D_00189E20)->unk2290) &&
        ((Hero_002AA678 *)D_00189E20)->counts->unkC) {
        func_L00_002D36E0(v, 1, 2.0f, -2.1f, 8.7f);
        ref_L22_002AA678_00(((Hero_002AA678 *)D_00189E20)->unk2290, v, 1);
        ((Hero_002AA678 *)D_00189E20)->counts->unkC--;
    }
    available = 1;
    if (!((Hero_002AA678 *)D_00189E20)->counts->unk8 || func_L22_003B9428(((Hero_002AA678 *)D_00189E20)->unk2290))
        available = 0;
    if ((unsigned)(((Hero_002AA678 *)D_00189E20)->unk2294 - 0x5D) <= 1)
        available = 0;
    if (((Hero_002AA678 *)D_00189E20)->active) {
        if (!((Hero_002AA678 *)D_00189E20)->counts->unk8) {
            if (((Hero_002AA678 *)D_00189E20)->effect) {
                if (((Hero_002AA678 *)D_00189E20)->effect->flags & 2)
                    ((Hero_002AA678 *)D_00189E20)->fading = 1;
                if (((Hero_002AA678 *)D_00189E20)->fading) {
                    if (((Hero_002AA678 *)D_00189E20)->effect->fade == 0) {
                        func_L00_00310C88(((Hero_002AA678 *)D_00189E20)->unk2290, &((Hero_002AA678 *)D_00189E20)->effect);
                        ((Hero_002AA678 *)D_00189E20)->active = 0;
                        return;
                    }
                    func_002AA2E8(&((Hero_002AA678 *)D_00189E20)->effect->fade, 0, 0.08400001f);
                }
            } else
                ((Hero_002AA678 *)D_00189E20)->active = 0;
        }
    }
    if (((Hero_002AA678 *)D_00189E20)->active) {
        if (!(D_00138320 & 0x20) || !available) {
            if (((Hero_002AA678 *)D_00189E20)->effect) {
                if (((Hero_002AA678 *)D_00189E20)->effect->flags & 2)
                    ((Hero_002AA678 *)D_00189E20)->fading = 1;
                if (((Hero_002AA678 *)D_00189E20)->fading) {
                    if (((Hero_002AA678 *)D_00189E20)->effect->fade == 0) {
                        func_L00_00310C88(((Hero_002AA678 *)D_00189E20)->unk2290, &((Hero_002AA678 *)D_00189E20)->effect);
                        ((Hero_002AA678 *)D_00189E20)->active = 0;
                        return;
                    }
                    func_002AA2E8(&((Hero_002AA678 *)D_00189E20)->effect->fade, 0, 0.08400001f);
                }
            } else
                ((Hero_002AA678 *)D_00189E20)->active = 0;
        } else if (((Hero_002AA678 *)D_00189E20)->counts->unk8)
            ((Hero_002AA678 *)D_00189E20)->fading = 0;
    }
    if (!((Hero_002AA678 *)D_00189E20)->active && available && func_L00_0032EF10(32, 7, 0)) {
        Effect_002AA678 *p = func_L00_00310BC8(((Hero_002AA678 *)D_00189E20)->unk2290, 2);
        ((Hero_002AA678 *)D_00189E20)->fading = 0;
        ((Hero_002AA678 *)D_00189E20)->effect = p;
        if (p) {
            ((Hero_002AA678 *)D_00189E20)->active = 1;
            func_L00_00311080(((Hero_002AA678 *)D_00189E20)->unk2290, p, 13, 0, 7, 1);
        }
    }
    if (!((Hero_002AA678 *)D_00189E20)->active || !((Hero_002AA678 *)D_00189E20)->effect || ((Hero_002AA678 *)D_00189E20)->fading)
        return;
    func_002AA2E8(&((Hero_002AA678 *)D_00189E20)->effect->fade, 1, 0.156f);
    ((Hero_002AA678 *)D_00189E20)->effect->unk28 = 2;
    func_L00_00310D30(((Hero_002AA678 *)D_00189E20)->unk2290, ((Hero_002AA678 *)D_00189E20)->effect);
    func_00282948(&((Hero_002AA678 *)D_00189E20)->timer);
    if (((Hero_002AA678 *)D_00189E20)->effect->state == 4 && !((Hero_002AA678 *)D_00189E20)->timer) {
        ((Hero_002AA678 *)D_00189E20)->timer = 4;
        for (i = 0; i < 2; i++) {
            func_0029FCC0(((Hero_002AA678 *)D_00189E20)->unk2290, i + 3, v);
            func_002AFD88(((Hero_002AA678 *)D_00189E20)->unk2290, v, 1.4f, 0, 0);
            if (((Hero_002AA678 *)D_00189E20)->counts->unk8) {
                ref_L22_002AA678_01(((Hero_002AA678 *)D_00189E20)->unk2290, v, 0, 0, ((Hero_002AA678 *)D_00189E20)->counts->unk0 != 0);
                ((Hero_002AA678 *)D_00189E20)->counts->unk8--;
            }
        }
    }
}


/* Restarts the run: resets the racer's state block, plays the two subsystem
   start-ups, then arms the racer for the mode the caller asked for.
   The state block is reached through three block-scoped copies of its address,
   so each stretch of the body re-materialises the base instead of keeping it
   live across the calls; the three table entries are the routines the tuning
   table points at, whose places differ from level to level. */
void func_PAL_L22_002B6F90(int a0, int a1, void *a2) {
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

