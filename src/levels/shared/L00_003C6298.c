#include "include_asm.h"

/* Sound fields measured at 0x38/0x3A in the 0xE0-byte resource entries. */
typedef struct {
    char pad_00[0x38];
    short multiple_sound;
    short single_sound;
    char pad_3C[0xA4];
} L00PickupSoundEntry;

typedef struct {
    char pad_00[0x60];
    int limit;
    char pad_64[4];
    int item;
    char pad_6C[8];
    float fade_rate;
    char pad_78[0x14];
} L00PickupState;

typedef struct {
    char pad_00[0x20];
    unsigned char phase;
    char pad_21[0xB];
    float scale;
    char pad_30[0x38];
    L00PickupState *state;
} L00PickupObject;

extern int func_L00_002D3FB0(int);
extern int func_L00_002D3FB8(int, int);
extern int D_00139688[];
extern unsigned char D_00139568[];
extern L00PickupSoundEntry D_L00_00262570[];
extern void func_L00_00326200(int, int, int);
extern void func_00282C88(void *);
extern int func_00282C30(int);
extern int D_L00_001B19C8[] __attribute__((sda));
extern int ref_L00_003D1B50_00[] __attribute__((sda));

#define RAC2_T_VEC16_FC936841D

typedef struct {
    char pad_000[0x140];
    float x_140;
    float y_144;
    float z_148;
} L00AimVector;

typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner {
    unsigned char prefix_00[0x68];
    void *context_68;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner;

typedef struct Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext {
    unsigned char prefix_00[0x10];
    float vector_10[4];
    unsigned int field_20;
    unsigned int active_24;
} Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext;

typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;

typedef struct Rac2Native_9cdc323a4d0c2fbd_ClearedRecord {
    unsigned char prefix_00[0x48];
    unsigned int field_48;
    unsigned char suffix_4C[4];
} Rac2Native_9cdc323a4d0c2fbd_ClearedRecord;

extern L00AimVector D_L00_001B8C80;

extern void func_002FDBD8_3(float scale, Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context,
                                    float *vector, int mode);

extern void func_00282D30_2(char *dst, char *src, float scale);

extern void func_00282CF0_9(char *local, char *first, char *second);

extern void func_00282CC0_15(char *target, char *first, char *local);

extern Rac2Native_9cdc323a4d0c2fbd_ClearedRecord D_L00_00241500[];

extern float func_00282E80(void *dst, void *src);

extern void func_002A7470(void *object, int kind, int value, int extra);

extern int func_002E5CF8(int index, int value, void *object);

extern char D_00189EA0[];

extern int func_0027C878(int);

extern float func_00283248(float, float);

extern void func_00283410(void *, void *);

extern void func_00280B90(void *, void *, int);

extern void ref_L00_003CC030_00(char *);

/* Measured partial layouts; original type and game roles are unknown. */

#ifndef RAC2_T_VEC16_FC936841D
#endif

/* Measured partial layout; original type and game role are unknown. */

INCLUDE_ASM("asm/levels", func_L00_003C6298);

/* Defined in L00_003C6A88-g8.c. */


/* Defined in L00_003C79F8-g8.c. */

/* func_L00_003C7DF0 is defined in L00_003C6298-ribbon-g8.c. */

/* func_L00_003C83E0 is defined in L00_003C8608-g64.c. */

/* Defined in L00_003C8608-g64.c. */

/* Defined in L00_003C8828-input.c. */

/* When the context flag at offset 0x24 is nonzero, pass scale 1.0, the context, its vector at offset 0x10 and mode zero to the bound helper; original game role is unknown. */
void func_L00_003C8A58(Rac2Native_9cdc323a4d0c2fbd_AnalysisOwner *owner)
{
    Rac2Native_9cdc323a4d0c2fbd_AnalysisConditionalContext *context = owner->context_68;
    if (context->active_24 != 0) {
        func_002FDBD8_3(1.0f, context, context->vector_10, 0);
    }
}

INCLUDE_ASM("asm/levels", func_L00_003C8A90);

INCLUDE_ASM("asm/levels", func_L00_003C94D8);

INCLUDE_ASM("asm/levels", func_L00_003C9978);

/* Clears one word of each of three hundred 80-byte records, from the last one down. */
void func_L00_003CA470(void)
{
    int i;

    for (i = 299; i >= 0; i--)
        D_L00_00241500[i].field_48 = 0;
}

/* func_L00_003CA730 is defined in L00_003C6298-shot-g8.c. */



/* func_L00_003CB980 is defined in L00_003C6298-pool-g8.c. */

/* resets a state record: zero words, plus/minus one float flags and two 64-bit fields in the retail store order */
void func_L00_003CBC80(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 280993940374112LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}

/* func_L00_003CBD08 is defined in L00_003CBD08-curve.c. */

/* Scales four consecutive 16-byte XYZ vectors in place by one scalar through a vector helper. */
void func_L00_003CBE28(char *p, float scale)
{
    func_00282D30_2(p, p, scale);
    func_00282D30_2(p + 16, p + 16, scale);
    func_00282D30_2(p + 32, p + 32, scale);
    func_00282D30_2(p + 48, p + 48, scale);
}

/* Sets the render state of a position: resets a work record, takes the two aim angles from the
   level's float table, copies the position and the scale into the record and hands it to the
   level's draw helper. The first call goes to a neighbour that has two identical copies in
   some levels, so its target is a per-level name. */
void func_L00_003CC030(char *position, int color, float scale, char *resource, float alpha, int mode, int flag)
{
    unsigned char work[0xE0];
    unsigned int rgba;
    unsigned long long mode_bits;
    float first_angle;
    float second_angle;
    float distance;

    ref_L00_003CC030_00((char *)work);
    *(long long *)(work + 0x78) = func_0027C878(mode);

    mode_bits = ((unsigned long long)flag << 2) | 0x0000008000000040ULL;
    *(long long *)(work + 0x88) = mode_bits;
    *(long long *)(work + 0x80) = 0x0000FF9000000260ULL;

    rgba = (unsigned int)color + ((unsigned int)resource << 24);
    *(int *)(work + 0x4C) = rgba;
    *(int *)(work + 0x48) = rgba;
    *(int *)(work + 0x44) = rgba;
    *(int *)(work + 0x40) = rgba;
    *(long long *)(work + 0x70) = 0;

    *(int *)(work + 0xDC) = 0;
    first_angle = func_00283248(D_L00_001B8C80.x_140 - *(float *)(position + 0),
                                D_L00_001B8C80.y_144 - *(float *)(position + 4));
    *(float *)(work + 0xD8) = first_angle;

    distance = func_00282E80(position, &D_L00_001B8C80.x_140);
    second_angle = func_00283248(distance, D_L00_001B8C80.z_148 - *(float *)(position + 8));
    *(float *)(work + 0xD0) = alpha;
    *(float *)(work + 0xD4) = -second_angle;

    func_00283410(work + 0x90, work + 0xD0);
    *(float *)(work + 0xC0) = *(float *)(position + 0);
    *(float *)(work + 0xC4) = *(float *)(position + 4);
    *(float *)(work + 0xC8) = *(float *)(position + 8);
    *(float *)(work + 0xCC) = 1.0f;
    func_L00_003CBE28((char *)work, scale);
    func_00280B90(work, work + 0x90, 0);
}

/* Derives a 16-byte element at index-1 from its index-2 and index-3 neighbours through two bound helpers; original game role is unknown. */
void func_L00_003CC6D8(Vec16_Fc936841d *object, int index)
{
    char local[16];

    func_00282CF0_9(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    func_00282CC0_15((char *)&object[index - 1], (char *)&object[index - 2], local);
}

void func_L00_003CD158(void)
{
}

void func_L00_003CEC50(char *object)
{
    char *s0 = object;

    if (*(unsigned char *)(s0 + 0x20) == 0) {
        if (func_00282E80(s0 + 0x10, D_00189EA0) < 6.0f) {
            *(unsigned char *)(s0 + 0x20) = 1;
            *(unsigned int *)(s0 + 0x78) = 0x24C102;
            if (*(unsigned char *)(s0 + 0x43) != 1) {
                func_002A7470(s0, 1, 0, 0);
            }
            func_002E5CF8(0, 0, s0);
            *(unsigned int *)(s0 + 0x98) = 0;
        }
    }
    if (*(unsigned char *)(s0 + 0x20) == 1) {
        if (*(unsigned char *)(s0 + 0x60) & 2) {
            *(unsigned char *)(s0 + 0x20) = 2;
            *(unsigned int *)(s0 + 0x78) = 0x224C1;
            if (*(unsigned char *)(s0 + 0x43) != 2) {
                func_002A7470(s0, 2, 0, 0);
            }
            func_002E5CF8(1, 0, s0);
        }
    }
}

/* Defined in L00_003D1258-g8.c. */


/* Checks whether a pickup object has just added to the stock counter of its item kind: plays the
   single or multiple pickup sound, and when the amount exceeds the limit marks the object as
   used up. Returns 1 if the counter grew. */
int func_L00_003D1B50(L00PickupObject *object)
{
    L00PickupState *state = object->state;
    int old_count;
    int delta;
    int sound;
    int result;
    float overflow;

    if (object->phase == 2)
        return 0;

    old_count = D_00139688[func_L00_002D3FB0(state->item)];
    overflow = func_L00_002D3FB8(state->item, state->limit);
    if (old_count < D_00139688[func_L00_002D3FB0(state->item)]) {
        delta = D_00139688[func_L00_002D3FB0(state->item)] - old_count;
        if (delta == 1) {
            sound = ((L00PickupSoundEntry *)(D_00139568[func_L00_002D3FB0(state->item)] * 224 +
                                             (unsigned int)D_L00_00262570))->single_sound;
        } else {
            sound = ((L00PickupSoundEntry *)(D_00139568[func_L00_002D3FB0(state->item)] * 224 +
                                             (unsigned int)D_L00_00262570))->multiple_sound;
        }
        func_L00_00326200(sound, delta, -1);
        if (overflow < state->limit) {
            int elapsed;

            object->phase = 2;
            object->scale *= 1.2f;
            func_00282C88(state);
            elapsed = D_L00_001B19C8[0] - ref_L00_003D1B50_00[0];
            state->fade_rate = 0.13333334f;
            if (func_00282C30(elapsed) >= 11) {
                func_002E5CF8(0, 0, object);
                ref_L00_003D1B50_00[0] = D_L00_001B19C8[0];
            }
        }
        result = 1;
    } else {
        result = 0;
    }
    return result;
}

INCLUDE_ASM("asm/levels", func_L00_003D1D28);


/* func_L00_003D2C00 is defined in L00_003C6298-strip.c. */

/* func_L00_003D2ED0 is defined in L00_003D2ED0-g8.c. */

INCLUDE_ASM("asm/levels", func_L00_003D3388);
