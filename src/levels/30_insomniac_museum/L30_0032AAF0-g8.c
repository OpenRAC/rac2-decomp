#include "common.h"

typedef struct { unsigned short id, kind; void *callback; unsigned short value, pad; } InitEntry30;
typedef struct { unsigned short id, pad, value; char rest[6]; } SourceEntry30;
/* Reloaded at each search step in retail. */
extern struct { char pad[0x230]; int selected; } D_L30_001CA3A0;

extern int func_002A7820(int, int);
extern float func_002A7940(void);
extern void func_L16_00405818(void *, int, float, int, float, float, int, int, void *);
extern float D_L30_001B15AC __attribute__((sda));
extern float D_L30_001B15B0 __attribute__((sda));
extern int D_L30_001B15A4 __attribute__((sda));
extern int D_L30_001B15A8 __attribute__((sda));
extern int D_L30_001B156C __attribute__((sda));
extern int D_L30_001B1570 __attribute__((sda));

/* Small-data unit: every body here reaches a global through $gp, so the file is built
   with -G8 (the -g8.c name gives it that profile). */

extern float D_L30_001AEE90 __attribute__((sda));
extern float D_L30_001AEE94 __attribute__((sda));
extern char D_L30_001AEE98[];

extern void func_0026FEB8(const char *, ...);
extern void func_001163A0(unsigned int);
extern int func_002A77E0(int);
extern void func_002A7750(u8 *, int, int);
extern void func_002AEE70(u8 *, u8 *, u8 *, float, float, float);
extern float func_00283B98(float, float);

typedef struct {
    unsigned char pad[0x1A0];
    unsigned int f1A0;
    unsigned int f1A4;
} D00138180_Flags;

extern D00138180_Flags D_00138180;
extern float D_001B35B8;
extern int D_001A79F0;
extern float D_L30_001AEC24 __attribute__((sda));
extern float D_L30_001AEC2C __attribute__((sda));
extern float D_L30_001AEC28 __attribute__((sda));
extern float D_L30_001AEC20 __attribute__((sda));
extern int D_L30_001AEC18 __attribute__((sda));
extern int D_L30_001AEC10 __attribute__((sda));
extern int D_L30_001AEC1C __attribute__((sda));
extern int D_L30_001AEC14 __attribute__((sda));
extern int D_L30_001AEC08 __attribute__((sda));
extern float D_L30_001AEC0C __attribute__((sda));
extern int D_L30_001AEBB8 __attribute__((sda));
extern float D_00233A60[][24][24];

extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern void func_L30_00382F10(void);
extern void func_L30_003830D8(void);
extern float func_L30_00382EF0(float, float, float);
extern void func_L30_003831E8(int, int, float, float);
extern void func_L30_00383928(void *);

extern char D_00189E20[];
extern char *D_001B2D1C __attribute__((sda));
extern void func_002A7470(void *, int, int, int);
extern void func_L00_0042A500(int);
extern void func_002B0C28(int, int, int);
extern void func_L00_002B9D60(void *, void *, int, int);
extern void func_L30_003BE678(char *);

/* Updates the museum water pool (moby class 4504). It sets up the water surface, then ripples it, adds drops and draws it every frame. */
void func_L30_003840E0(char *object) {
    int state = *(unsigned char *)(object + 0x20);

    switch (state) {
    case 0:
        *(unsigned char *)(object + 0x20) = 1;
        *(float *)(object + 0x18) += D_001B35B8;
        InitMuseumWaterGrid();
        *(unsigned char *)(object + 0x30) = 0xFF;
        break;
    case 1:
        if (!(gPadState.f1A0 & 0x80))
            StepMuseumWaterShape();
        if (D_L30_001AEC24 >= D_L30_001AEC2C && RandomIntBelow(200) == 1) {
            D_L30_001AEC24 = 0.0f;
            D_L30_001AEC18 += D_L30_001AEC10;
            D_L30_001AEC1C += D_L30_001AEC14;
            if (D_L30_001AEC18 < 4 || D_L30_001AEC18 > 20)
                D_L30_001AEC10 = -D_L30_001AEC10;
            if (D_L30_001AEC1C < 4 || D_L30_001AEC1C > 20)
                D_L30_001AEC14 = -D_L30_001AEC14;
            D_00233A60[D_L30_001AEBB8][D_L30_001AEC18][D_L30_001AEC1C] = D_L30_001AEC20;
        } else {
            FloatToInt(LerpFloat_L30(IntToFloat(D_L30_001AEC18),
                                            IntToFloat(D_L30_001AEC18 + D_L30_001AEC10),
                                            D_L30_001AEC24));
            FloatToInt(LerpFloat_L30(IntToFloat(D_L30_001AEC1C),
                                            IntToFloat(D_L30_001AEC1C + D_L30_001AEC14),
                                            D_L30_001AEC24));
        }
        D_L30_001AEC24 += D_L30_001AEC28;
        if (gPadState.f1A0 & 0x20)
            RaiseMuseumHeightFieldDome(12, 12, D_L30_001AEC08, D_L30_001AEC0C);
        AddDrawCallbackToList1(DrawMuseumWaterGrid, object);
        break;
    }
}

/* Steps one record: with the state byte clear it copies the record's own angle into the
   state block, and once the state index reaches thirteen it redraws the record with a fresh
   random duration, a timer sample and the state block's new bit mask. With the state byte
   set it folds the shared angle words into the record and the state block instead, and
   counts the frame in the record's halfword at 0x96. */
/* Updates a museum object (moby class 4942) that picks a random look out of thirteen, turns a little each frame and counts frames. */
void func_L30_00386300(u8 *object) {
    u8 *state = *(u8 **)(object + 0x68);
    u16 counter;

    if (*(u8 *)(object + 0x20) == 0) {
        float height = *(float *)(object + 0x18);
        unsigned int index = *(unsigned int *)state;

        *(float *)(state + 0xC) = height;
        if (index >= 13) {
            short classId = *(short *)(object + 0xAA);
            short extraId = *(short *)(object + 0xB2);
            unsigned int ticks = T1_COUNT;

            STUB_printf(D_L30_001AEE98, classId, extraId);
            Srand(ticks);
            *(int *)state = RandomIntBelow(13);
        }
        *(u16 *)(object + 0x7C) = 1 << *(int *)state;
        SetMobyState(object, 1, -1);
    } else {
        float f0 = D_L30_001AEE94;

        UpdateWrappedAngleOffset(object, state + 4, state + 8, D_L30_001AEE90,
                      f0 * 0.000290888245f, *(float *)(state + 0xC));
        *(float *)(object + 0xF8) =
            FastAddRotations(*(float *)(object + 0xF8), 0.01745329424738884f);
        *(u16 *)(object + 0x96) = 0;
    }
    counter = *(u16 *)(object + 0x96);
    *(u16 *)(object + 0x96) = counter + 1;
}

/* Updates a museum info stand (moby class 2263). When the player stands at it, it shows a message and lets the player press a button to use it. */
void func_L30_003BE478(char *object) {
    char *hero;
    char *state = *(char **)(object + 0x68);
    int id;

    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        if (*(int *)(state + 4) != 0) {
            *(unsigned char *)(object + 0x20) = 1;
            if (*(unsigned char *)(object + 0x43) != 0)
                StartAnimationBlended(object, 0, 0, 5);
        } else {
            *(unsigned char *)(object + 0x20) = 3;
            if (*(unsigned char *)(object + 0x43) != 2)
                StartAnimationBlended(object, 2, 0, 5);
        }
        break;
    case 1:
        break;
    case 2:
        if (*(unsigned char *)(object + 0x60) & 2) {
            *(unsigned char *)(object + 0x20) = 5;
            if (*(unsigned char *)(object + 0x43) != 2)
                StartAnimationBlended(object, 2, 0, 5);
            if (*(int *)(state + 0xC) != -1)
                ResetCameraEntry(*(int *)(state + 0xC));
        }
        break;
    case 3:
        id = -1;
        if (gCurrentMapIndex != 0x15 && gCurrentMapIndex != 0x1E) {
            switch (*(int *)(state + 8)) {
            case 0:
                id = 0x279C;
                break;
            case 1:
                id = 0x279D;
                break;
            }
        } else {
            id = 0x27ED;
        }
        hero = gHeroState;
        if (*(char **)(hero + 0x33C) == object && *(int *)(hero + 0x340) != 0) {
            TryClaimNotice(8, id, 1);
            if (gPadState.f1A4 & 0x10) {
                char *entry = D_001B2D1C + (*(int *)state << 8);

                AdvanceMuseumInfoStandState(entry);
                ResetHeroPositionAndDirection(entry + 0x10, entry + 0xF0, 0x6F, 1);
                *(unsigned char *)(hero + 0x22B5) = 1;
            }
        }
        break;
    case 4:
        break;
    case 5: {
        char *heroBlock = gHeroState;

        if (*(int *)(heroBlock + 0x2294) == 0x6F) {
            *(unsigned char *)(heroBlock + 0x22B5) = 0;
            ResetHeroPositionAndDirection(heroBlock + 0x80, heroBlock + 0x90, 0, 0);
        }
        *(unsigned char *)(object + 0x20) = 3;
        break;
    }
    }
}

/* Spawns two puffs of dust at the object's position, each with a random size. */
void func_L30_00404608(char *object) {
    int value;
    int value2;
    float scale;
    float scale2;
    float random;
    scale = D_L30_001B15AC;
    scale *= *(float *)(object + 0x2C);
    value = RandomIntRange(95, 111);
    random = RandomAngle();
    DrawBeamQuadsAndGlows(object + 0x10, D_L30_001B156C, scale, value, random, 1.0f, D_L30_001B15A4, 2, object);
    scale2 = D_L30_001B15AC;
    scale2 *= *(float *)(object + 0x2C);
    scale2 *= D_L30_001B15B0;
    value2 = RandomIntRange(111, 127);
    random = RandomAngle();
    DrawBeamQuadsAndGlows(object + 0x10, D_L30_001B1570, scale2, value2, random, 1.0f, D_L30_001B15A8, 2, object);
}

extern float D_L30_001AEBC8 __attribute__((sda));
extern float D_L30_001AEBCC __attribute__((sda));
extern int D_L30_001AEBC0 __attribute__((sda));
extern int D_L30_001AEBC4 __attribute__((sda));
extern int D_L30_001AEBBC __attribute__((sda));

extern void func_L30_00382FB8(void);

/* Moves the water surface toward its next shape; when that is done it runs one step of the ripple simulation instead. */
void func_L30_003830D8(void) {
    if (0.95f <= D_L30_001AEBC8) {
        D_L30_001AEBC8 = D_L30_001AEBCC;
        StepMuseumHeightField();
        D_L30_001AEBC0 = D_L30_001AEBBC;
        D_L30_001AEBC4 = D_L30_001AEBB8;
    } else {
        int x;
        int y;

        D_L30_001AEBC0 = 2;
        D_L30_001AEBC4 = 2;
        for (x = 0; x < 24; x++) {
            for (y = 0; y < 24; y++) {
                D_00233A60[D_L30_001AEBC0][y][x] =
                    LerpFloat_L30(D_00233A60[D_L30_001AEBBC][y][x],
                                      D_00233A60[D_L30_001AEBB8][y][x], D_L30_001AEBC8);
            }
        }
    }
    D_L30_001AEBC8 = D_L30_001AEBC8 + D_L30_001AEBCC;
}
