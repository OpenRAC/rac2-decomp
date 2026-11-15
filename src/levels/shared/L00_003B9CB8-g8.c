#include "common.h"
#include "include_asm.h"

extern int D_L00_001AFDA0 __attribute__((sda));

/* Reads the small counter in the shared data area and reports whether it equals two. */
int func_L00_003BB5F0(void)
{
    return D_L00_001AFDA0 == 2;
}

extern char D_L00_0023DDA0[] __attribute__((nosda));

extern char D_L00_0023F060[] __attribute__((nosda));

/* Clears one word of each of the thirty 0xA0-byte records that start at D_L00_0023DDA0,
   then one word of each of the sixteen 0xB0-byte records at D_L00_0023F060, walking down
   from the last record of each table, and finally the shared flag word. */
void func_L00_003BB600(void)
{
    char *base;
    char *record;
    int index;

    base = D_L00_0023DDA0;
    record = base + (0x1D * 0xA0 + 0x8C);
    index = 0x1D;
    do {
        *(int *)record = 0;
        index--;
        record -= 0xA0;
    } while (index >= 0);

    base = D_L00_0023F060;
    record = base + (0xF * 0xB0 + 0xA0);
    index = 0xF;
    do {
        *(int *)record = 0;
        index--;
        record -= 0xB0;
    } while (index >= 0);

    D_L00_001AFDA0 = 0;
}

extern int D_L04_001A8F00;

extern int D_L00_001AFF44 __attribute__((sda));

extern int D_L00_001AFF98 __attribute__((sda));

/* Clears the shared flag word this file's small-data area holds at 0x1AFF98. */
void func_L00_003C58E0(void)
{
    D_L00_001AFF98 = 0;
}

extern char D_0018C0B0[];

extern float func_L00_0037E668(void);

extern int func_L00_003C5B18(float f12);

extern void func_0029FCC0(char *a, int b, char *c);

extern void func_L00_003C48D0(char *p);

extern void func_L00_003C4B98(char *p);

extern void func_L00_003C4F78(char *p);

/* Gate followed by a fixed sequence of four bound helpers on the state record at offset 0x68. */
/* Each frame, if the level allows it, draws this effect: sets up its sound, then runs its three drawing steps. */
void func_L00_003C4850(char *moby)
{
    char *vars;

    if (D_L04_001A8F00 != 0)
        return;
    vars = *(char **)(moby + 0x68);
    if (CanUseHeldWeapon(GetFadeValue()) == 0)
        return;
    if (D_L00_001AFF44 == 0x28)
        return;
    TransformMobyJointToWorld(*(char **)gHeroMoby_0018C0B0, 0xA, vars + 0x30);
    UpdateElectricRibbons(moby);
    DrawGlowSphereEffect(moby);
    DrawEffectTrails(moby);
}


extern char D_00139568[];

typedef struct {
    char prefix[0x760];
    float vector[4];
    char pad770[0xBF8 - 0x770];
    int mode;
    char padBFC[0x24EC - 0xBFC];
    short state;
} Player37;
extern Player37 D_00189E20_13;

extern char D_L00_00262570[];

/* A float in the boot's small data: the sda attribute and this unit's -G8 make the
   reference to it $gp-relative, the way retail has it. */
extern float D_001AFF08 __attribute__((sda));

extern void func_00282F20(void *a0, void *a1, float f);

extern void func_L00_003C3920(char *a0, char *a1, void *a2);

extern void func_L00_0032A1A8(int a0, char *a1, void *a2, float f);

extern float func_00282DF0(void *a0);

extern void *func_L00_003A98E8(char *a0, void *a1, char *a2, int a3, float f12, float f13, float f14);

/* Scales a direction by the current class record's speed (per frame at 60 Hz), negated from the
   object's own vector in player state 1, re-reads the record's second value, applies the
   optional mode adjustment, then spawns through func_L00_003A98E8 and links the result back to
   the object. The two record lookups use separate locals: one reused pointer becomes a global
   pseudo and loses the first lookup's tie to the multiply's register. */
/* Fires a shot from the moby toward the target, using the speed of the current weapon class,
   and ties the new shot back to the moby that fired it. */
void func_L00_003C37C8(char *moby, char *shot)
{
    char velocity[16];
    char *vars = *(char **)(moby + 0x68);
    char *classRecord;
    char *classRecord2;
    float speed;
    float secondValue;
    float value;
    float extra;
    int mode;
    void *newMoby;

    classRecord = gWeaponTable_L00 + (unsigned char)gItemSlotToRecord[0x19] * 0xE0;
    value = *(float *)(classRecord + 0x50);
    speed = value * 0.016666667f;
    mode = D_00189E20_13.state;
    if (mode == 1)
        vec_scale_to_length(velocity, moby + 0xD0, -speed);
    else
        vec_scale_to_length(velocity, D_00189E20_13.vector, speed);

    classRecord2 = gWeaponTable_L00 + (unsigned char)gItemSlotToRecord[0x19] * 0xE0;
    secondValue = *(float *)(classRecord2 + 0x70);
    SpawnSparkShower_L00(moby, shot, velocity);

    mode = D_00189E20_13.mode;
    if (mode != 0)
        ComputeObjectToTargetVector(mode, shot, velocity, speed);

    value = FastVecLength(velocity);
    extra = D_001AFF08;
    newMoby = SpawnProjectile(shot, velocity, moby, 0, value, secondValue, extra);
    *(int *)vars = (int)newMoby;
    if (newMoby != 0) {
        *(int *)((char *)newMoby + 0xB8) = (int)moby;
    }
}

typedef struct { float f[4]; } __attribute__((aligned(16))) UiHistoryPoint;
extern int D_L00_001B2940[] MACRO_ADDR;
extern UiHistoryPoint D_L00_0023FB80[][20];
extern UiHistoryPoint D_L00_001B2900[] MACRO_ADDR;
extern float D_L00_001AFF4C __attribute__((sda));
extern int D_L00_001AFF50 __attribute__((sda));
extern int D_L00_001AFF54 __attribute__((sda));
extern int D_L00_001AFF58 __attribute__((sda));
extern float D_L00_001AFF5C __attribute__((sda));
extern float D_L00_001AFF60 __attribute__((sda));
extern char D_L00_001FE940[] __attribute__((nosda));
extern void func_00282CC0(void *, void *, void *);
/* The second integer-bank input is forwarded as the axis vector pointer. */
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *, void *);
extern void func_002ACB48(float *, float);
extern float func_00282DF0(void *);
extern void func_00282D30(void *, void *, float);
typedef struct {
    char prefix[8];
    int flags;
    char pad[0x24];
    UiHistoryPoint origin;
} UiTrailState;
typedef struct {
    unsigned char prefix[2];
    unsigned char texture;
    unsigned char flags;
    int color;
    int unused;
    float size;
} UiTrailParticle;
extern UiTrailParticle *func_002C36D0(void *, int, int, int);
extern void ref_L00_003C4F78_00(void *, int, int, int, int, int, int, int,
                              int, int, int, float, float, float);

/* Ages the four trail histories (20 points each), turns and clamps each head point, builds the
   vertex strip around the owner's origin and spawns two particles at the tip. The point address
   is formed in its own group so the copy source keeps its own D - 16 base. */
/* Draws four glowing trails behind the effect. Each trail remembers its last 20 points and
   spawns two small particles at its tip. */
void func_L00_003C4F78(char *owner)
{
    UiHistoryPoint vertices[20], origin, change;
    UiTrailState *state = *(UiTrailState **)(owner + 0x68);
    int i;
    qcopy(&origin, &state->origin);
    for (i = 0; i < 4; i++) {
        int last, j;
        UiHistoryPoint *head, *tip;
        float length, limit;
        UiTrailParticle *effect;
        D_L00_001B2940[i]++;
        if (D_L00_001B2940[i] >= 20)
            D_L00_001B2940[i] = 20;
        last = D_L00_001B2940[i] - 1;
        for (j = last; j > 0; j--) {
            int index = last - j;
            UiHistoryPoint *dst;
            do { dst = &D_L00_0023FB80[0][j]; dst += i * 20; } while (0);
            qcopy(dst, &D_L00_0023FB80[i][j - 1]);
            FastVecAdd(&vertices[index], &origin, dst);
            vertices[index].f[3] = 0.05f;
        }
        head = &D_L00_0023FB80[i][0];
        BuildAxisAngleQuaternion(&change, &D_L00_001B2900[i], 0.10471976548433304f);
        RotateVectorByQuaternion(head, head, &change);
        AddRandomOffsetToVector(head->f, 0.025f);
        length = FastVecLength(head);
        limit = D_L00_001AFF4C * 1.1f;
        if (length > limit)
            FastVecScale(head, head, limit / length);
        else {
            limit = D_L00_001AFF4C * 0.9f;
            if (length < limit)
                FastVecScale(head, head, limit / length);
        }
        FastVecAdd(&vertices[last], &origin, &D_L00_0023FB80[i][0]);
        vertices[last].f[3] = 0.05f;
        {
            int endpoint = D_L00_001B2940[i] - 1;
            tip = vertices + endpoint;
        }
        effect = SpawnBluishFadeParticle(tip, 2, 0, 1);
        if (effect != 0) {
            char *tables = D_L00_001FE940;
            effect->color = D_L00_001AFF50 | state->flags;
            effect->size = D_L00_001AFF5C * 210000.0f;
            effect->texture = (*(char **)(tables + 0xF8))[1];
        }
        effect = SpawnBluishFadeParticle(tip, 2, 0, 1);
        if (effect != 0) {
            effect->color = 0x407F7F7F;
            effect->size = D_L00_001AFF5C * 31500.001953125f;
        }
        ref_L00_003C4F78_00(vertices, 20, 14, 14,
                          D_L00_001AFF54, D_L00_001AFF54 & 0xFFFFFF,
                          D_L00_001AFF58 | state->flags, D_L00_001AFF58,
                          0, D_L00_001B2940[i] - 1, D_L00_001B2940[i],
                          0.02f, 0.07f, D_L00_001AFF60);
    }
}
