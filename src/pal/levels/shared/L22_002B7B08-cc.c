/* func_PAL_L22_002B7B08, the PAL copy of func_L22_002B7C70: the same C, where lit 0.024f becomes 0.0288f. */

extern char D_00189E20[];

extern void func_L22_002C9898(int mode, int flag);

/* Loads the level's tuning constants and starts the two subsystems. */
/* func_L22_002A8B98 is defined in L22_002A8B98-init.c. */

extern void func_002AA2E8(float *, float, float);
extern int D_00138320;
/* the two calls whose targets differ between levels 22 and 23 */
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
#undef HERO

extern int D_00138320;

extern void func_PAL_L22_002B7B08(void);

/* the three routines the tuning table points at; their places differ per level */
typedef unsigned char u8;

typedef unsigned short u16;

typedef float f32;

/* Restarts the run: resets the racer's state block, plays the two subsystem
   start-ups, then arms the racer for the mode the caller asked for.
   The state block is reached through three block-scoped copies of its address,
   so each stretch of the body re-materialises the base instead of keeping it
   live across the calls; the three table entries are the routines the tuning
   table points at, whose places differ from level to level. */
extern float func_00282E80(void *, void *);
extern void func_002AA2E8(float *, float, float);
extern void func_002AA3A8(float *, float *, float, float, float, float);

void func_PAL_L22_002B7B08(void) {
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
        func_002AA2E8(speeds, *(float *)(g + 0x258), 0.024f);
        func_002AA2E8(speeds + 1, *(float *)(g + 0x25C), 0.024f);
        func_002AA3A8(speeds + 5, speeds + 6, *(float *)(g + 0x260), 0.028800001f, 0.43200004f, 0.080000006f);
    }
}

extern void func_L22_002C9898(int a0, int a1);

/* plays one of three resident messages, picked by the type byte; the second argument
   is 1 or 2 depending on the caller's flag */
