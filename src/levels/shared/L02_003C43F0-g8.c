#include "include_asm.h"
#include "common.h"

extern void func_L00_00325AE8(void *, void *, float, float);

extern void *D_L02_001B17E8 __attribute__((sda));

extern float D_L02_001B17E4 __attribute__((sda));

extern float D_L02_001B17E0 __attribute__((sda));

extern float D_L02_001B17EC __attribute__((sda));

extern char *D_L02_001B1190[1] __attribute__((sda));

extern float func_00283CE0(int);

extern int func_00283CF0(float);

extern int func_L02_003F9B70(int);

extern int func_00288D58(void);

extern unsigned char D_001395B8[0x100];

/* Runs the kind's placement helper with the kind's own angles. */
/* Places an object using its state: states 2 and 3 pick different angle values. */
void func_L02_00402440(char *object) {
    if (*(unsigned char *)(object + 0x20) == 3)
        DrawBillboardQuad_L00(object + 0x10, D_L02_001B17E8, D_L02_001B17E4, D_L02_001B17E0);
    else if (*(unsigned char *)(object + 0x20) == 2)
        DrawBillboardQuad_L00(object + 0x10, D_L02_001B17E8, D_L02_001B17EC, D_L02_001B17E0);
}

#ifndef RAC2_T_TI128_L02
#define RAC2_T_TI128_L02
typedef int TI128 __attribute__((mode(TI)));
#endif

extern float D_L02_001B0180 __attribute__((sda));

extern float D_L02_001B0188 __attribute__((sda));

extern int D_L02_001B0184 __attribute__((sda));

extern float D_L02_001B0178 __attribute__((sda));

extern float D_L02_001B017C __attribute__((sda));

extern char D_L02_001BA500[];

extern void func_00282D30(void *, void *, float);

extern void func_00282CC0(void *, void *, void *);

extern void func_00282CF0(void *, void *, void *);

extern void func_00282F20(void *, void *, float);

extern float func_00282DB0(void *, void *);

/* The second declaration of the kind's helper in this unit: it takes the packed
   word where the call above takes a pointer. */
extern void func_L00_00325AE8_1(void *, int, float, float);

/* The 24-bit mask is written as 0xFFFFFF: the assembler expands `li` for 0xFF0000
   into `lui $v0,0xFF` and `ori $v0,$v0,0xFFFF`, so the register holds 0xFFFFFFFF. */
/* Spawns a fading spark from an object when the player is looking at it from far enough away. The spark color fades with distance. */
void func_L02_003D28E0(void *owner)
{
    void *object = owner;
    void *direction = (char *)object + 0xE0;
    TI128 spawnPoint;
    TI128 toCamera;
    float dot;
    int colorWord;
    int alpha;

    FastVecScale(&spawnPoint, direction, D_L02_001B0180);
    FastVecAdd(&spawnPoint, &spawnPoint, (char *)object + 0x10);
    FastVecSub(&toCamera, gCameraPosition_L02, (char *)object + 0x10);
    vec_scale_to_length(&toCamera, &toCamera, 1.0f);
    dot = FastVecDot(&toCamera, direction);
    if (D_L02_001B0188 < dot) {
        colorWord = D_L02_001B0184;
        dot = dot * dot;
        alpha = (int)(dot * (float)(colorWord >> 24));
        func_L00_00325AE8_1(&spawnPoint, (colorWord & 0xFFFFFF) | (alpha << 24), D_L02_001B0178,
                            D_L02_001B017C);
    }
}

/* func_L02_004013C0 is defined in L02_004013C0-g8.c. */

/* The kind's table gives a count; the kind's own helper gives the kind's id. */

/* The byte table the count is read from, at its address in the boot's resident memory. */

/* Scales the kind's own angle at +0xC down by 0.3 once per count the kind's byte table
   gives, keeps it inside the kind's own range, scales it by ten when the global flag is
   set, and hands it to the angle setter. */
int func_L02_003FCDF8(int entry) {
    float value;
    int i = 0;

    value = IntToFloat(*(int *)(D_L02_001B1190[entry] + 0xC));
    while (i < D_001395B8[GetChallengeSaveIndex(entry)]) {
        value *= 0.3f;
        i++;
    }
    {
        float limit = (float)*(int *)(D_L02_001B1190[entry] + 0xC);

        if (limit < value)
            value = limit;
        else if (value < 500.0f)
            value = 500.0f;
    }
    if (IsFlagByteSet() != 0)
        value *= 10.0f;
    return FloatToInt(value);
}

/* Near miss: same body with the other entry parameter (draft beside this one). */
/* Same idea as the one above, but for the second entry value, shifted left by 5. */
int func_L02_003FCF08(int entry) {
    float value;
    int i = 0;

    value = IntToFloat(*(int *)(D_L02_001B1190[entry] + 0x10));
    while (i < D_001395B8[GetChallengeSaveIndex(entry)]) {
        value *= 0.33333f;
        i++;
    }
    {
        float limit = (float)*(int *)(D_L02_001B1190[entry] + 0x10);

        if (limit < value)
            value = limit;
        else if (value < 5.0f)
            value = 5.0f;
    }
    return FloatToInt(value) << 5;
}

extern void func_00282C98(void *);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F70(void *, void *, float);
extern int func_L02_0032EF10(void *, char *, char *, int, float);

/* The level's 0x80-byte placement records, whose direction sits at +0x30. */
extern char *D_L02_001B368C;

/* Aligns the actor with the record its state names: the -1 case builds a direction from the
   +0x1F0 axis and the +0x340 vector and picks the 1.5-scaled or negated one by the sign of the
   dot product; the other case uses the 0x80-byte record from the boot table. The shared tail
   copies the +0x340 vector to the stack and hands it to the level's nine-place routine. */
int func_L02_003CCFE8(char *object, char *output)
{
    char *vars = *(char **)(object + 0x68);
    TI128 a, b, c, d, e;
    int result;

    if (*(int *)(vars + 0x334) == -1) {
        FastVecSub((float *)&a, (float *)(vars + 0x1F0), (float *)(vars + 0x340));
        VectorCopyHelperA(&b);
        FastVecCross(&c, &a, &b);
        vec_scale_to_length((char *)&c, (char *)&c, 1.5f);
        FastVecScale(&d, &c, -1.0f);
        FastVecSub((float *)&e, object + 0x10, (float *)(vars + 0x340));
        if (FastVecDot(&e, &c) < 0.0f) {
            FastVecAdd(output, &c, vars + 0x340);
            result = 1;
        } else {
            FastVecAdd(output, &d, vars + 0x340);
            result = 0;
        }
    } else {
        FastVecSub((float *)&a, (float *)(vars + 0x1F0),
                      (float *)(D_L02_001B368C + (*(int *)(vars + 0x334) << 7) + 0x30));
        result = 1;
        FastVectorNormalizeHelper((char *)&a, (char *)&a,
                      FastVecLength(D_L02_001B368C + (*(int *)(vars + 0x334) << 7)));
        FastVecAdd(output, &a, D_L02_001B368C + (*(int *)(vars + 0x334) << 7) + 0x30);
        FastVecSub((float *)&b, output, object + 0x10);
        if (!(0.0f <= FastVecDot(&b, object + 0xD0)))
            result = 0;
    }
    a = *(TI128 *)(vars + 0x340);
    ClampMoveToPathArea(&a, output, output, *(int *)(vars + 0x318), *(float *)(vars + 0x100));
    return result;
}


extern char *D_L02_001B359C __attribute__((sda));

extern int D_001A79F0[] __attribute__((sda));
extern unsigned char D_0019B2E8[];
extern unsigned char D_001395B8[];
struct PortalPlayer {
    char pad0[0x80];
    float pos[4];
    char pad90[0x182];
    short state;
    char pad214[0x128];
    char *portal;
    int active;
    char pad344[0x21ac];
    unsigned char flag;
};
extern struct PortalPlayer D_00189E20;
extern unsigned char D_00189EA0[];
extern unsigned char D_001A7BC8[] __attribute__((sda));
extern unsigned int D_00138324 __attribute__((nosda));
extern unsigned char D_L02_001C0700[];
extern void func_002A7470(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern void func_L00_003294F0(void *, int);
extern void func_L00_003672F8(void);
extern void func_L02_00327350(int, int);
extern void func_002DF3F8(void *, void *);
extern void func_002AF0A8(int);
extern void func_002AFDD8(void *, void *, void *, int);
extern void func_002B0C28(int, int, int);
extern void func_00288CB0(int, int);
extern int func_00288AA0(void *, int);
extern int func_00288BE8(void *);
extern void func_L02_00404778(void);
extern void func_002F5CB8(void (*)(void), void *);
extern void func_002AD7B8(int);

/* Update for a portal moby. On the first frame it sets up its look and level link; later it sends the hero to the linked level when they step into it. */
void func_L02_00404410(char *obj) {
    char *vars = *(char **)(obj + 0x68);
    float delta[4];
    int destLevel;

    switch (*(unsigned char *)(obj + 0x20)) {
    case 0: {
        int levelRow;
        if (*(unsigned char *)(obj + 0x43) != 2) StartAnimationBlended(obj, 2, 0, 1);
        SetMobyState(obj, 1, -1);
        *(unsigned char *)(obj + 0x30) = 255;
        if (gCurrentMapIndex[0] == 26) *(short *)(obj + 0x32) = 255;
        qcopy(vars + 0x20, obj + 0x10);
        qcopy(vars + 0x30, obj + 0xf0);
        levelRow = gCurrentMapIndex[0] << 4;
        *(short *)(vars + 0x1e) = D_0019B2E8[*(unsigned char *)(obj + 0xb0) + levelRow] >> 7;
        if (D_0019B2E8[*(unsigned char *)(obj + 0xb0) + levelRow] & 0x80) {
            if (*(int *)(vars + 4)) SetObjectFlagBit(gMobyPool_L02 + (*(int *)(vars + 4) << 8), 1);
        }
        if (gCurrentMapIndex[0] == 2 && D_001395B8[0x71] == 26) {
            SetFlagToOne();
            D_001395B8[0x71] = 1;
            StartRecordEffectByIndex(*(int *)(vars + 0x14), *(int *)(vars + 0x10));
            CaptureCheckpointState(gHeroPosition, gHeroPosition + 0x10);
            if (D_001A7BC8[4] && !D_001395B8[0xa5]) {
                D_001395B8[0xa5] = 1;
                PlayIndexedSound(4);
            }
        }
    }
    case 1:
        if (gHeroState.portal == obj && gHeroState.active) {
            FastVecSub(delta, gHeroState.pos, obj + 0x10);
            TransformVectorByObjectOrGiven(obj, delta, delta, 0);
            if (delta[2] < -0.6f) {
                int currentLevel;
                currentLevel = gCurrentMapIndex[0];
                gHeroState.state = 2;
                destLevel = 2;
                if (currentLevel == 26) {
                    TryClaimNotice(8, 0x27b1, 1);
                } else {
                    TryClaimNotice(8, D_0019B2E8[*(unsigned char *)(obj + 0xb0) + (currentLevel << 4)] & 0x80 ? 0x27cd : 0x27b0, 1);
                    destLevel = 26;
                }
                if (D_00138324 & 0x10) {
                    CaptureCheckpointState(gHeroPosition, gHeroPosition + 0x10);
                    SetSmallDataValueAndRefresh(destLevel, 1);
                    if (destLevel == 26) D_001395B8[1] = 1;
                }
            }
        }
        if (gCurrentMapIndex[0] == 26 && (D_0019B2E8[0x1a0 + *(unsigned char *)(obj + 0xb0)] & 0x80)) {
            if (D_001A7BC8[4]) return;
            if (PushRequestQueue(D_L02_001C0700, 0xa7)) {
                PushRequestQueue(D_L02_001C0700, 4);
                PushRequestQueue(D_L02_001C0700, 0xa8);
                LaunchQueuedRequest(D_L02_001C0700);
                SetStoredValuePair(CallHelperWithTwoAndOne, obj);
                gHeroState.flag = 0;
                MarkFlagAndAppendToList(4);
                SetMobyState(obj, 3, -1);
            }
        }
        break;
    }
}
