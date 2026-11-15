#include "include_asm.h"
#include "names.h"

extern char D_00189E20_8[];

extern int hero_pick_linked_anim_pair(int, int *, int *);

/* Frozen Batch A A14-struct-2field-20; acknowledged claim 3e0e0bb01b3da304ddd50c7212de48bebcbf96d3b2d117369779044d96f69b21. */
typedef unsigned int BatchA_A14_u32;

typedef struct { unsigned char pad[0x2494]; BatchA_A14_u32 a; BatchA_A14_u32 b; } BatchA_A14_S;

extern BatchA_A14_S g_hero_state;

typedef struct { short key; short val; } Entry;

extern Entry *D_0018C2B8;

/* Measured partial layouts; original type and game roles are unknown. */
typedef int Rac2Native_28c929cadd7aca24_s32;

typedef unsigned char Rac2Native_28c929cadd7aca24_u8;

typedef struct {
    Rac2Native_28c929cadd7aca24_u8 prefix[0xc40];
    Rac2Native_28c929cadd7aca24_s32 selected;
    Rac2Native_28c929cadd7aca24_s32 index;
    Rac2Native_28c929cadd7aca24_u8 gap[0x1648];
    Rac2Native_28c929cadd7aca24_u8 *object;
} Rac2Native_28c929cadd7aca24_NativeResidentView;

extern Rac2Native_28c929cadd7aca24_NativeResidentView D_00189E20_19;

extern char D_00189E20_17[];

typedef unsigned char u8;

extern u8 D_00189E20_1[];

typedef struct { u8 prefix[0x34]; unsigned short flags; } FlagPairObjectView;

typedef struct {
    u8 prefix[0x1860];
    FlagPairObjectView *secondary;
    u8 between[0xa2c];
    FlagPairObjectView *primary;
} FlagPairResidentView;

/* Guards three fields of a level state block, calls one helper with two stack outputs, then copies a shared float into offset 72 of two optional objects. */
void hero_update_linked_object_clock(void)
{
    char *level = D_00189E20_8;
    int animA;
    int animB;
    int *linkedObj;

    if (*(unsigned char *)(level + 8884) != 0)
        return;
    if (*(int *)(level + 4916) != 2)
        return;
    if (hero_pick_linked_anim_pair(*(unsigned char *)(*(int *)(level + 8848) + 67), &animA, &animB) == 0)
        return;
    linkedObj = (int *)*(int *)(level + 4880);
    if (linkedObj != 0)
        *(float *)((char *)linkedObj + 72) = *(float *)(level + 3104);
    linkedObj = (int *)*(int *)(level + 4884);
    if (linkedObj != 0)
        *(float *)((char *)linkedObj + 72) = *(float *)(level + 3104);
}

/* A14-struct-2field-20 freshly exact-verified under family reservation */
void hero_clear_anim_flags(void) {
    g_hero_state.a = 0;
    g_hero_state.b = 0;
}

/* shared native body of family c68ad20a */
/* Looks up a key in the current table and gives back its value. Returns 1 when found, otherwise 0. */
int hero_lookup_anim_by_key(int key, int *out)
{
    Entry *table = D_0018C2B8;
    Entry *entry;

    if (table == 0)
        return 0;
    if (table->key == -1)
        goto notfound;
    entry = table;
    for (;;) {
        if (key == entry->key) {
            *out = entry->val;
            return 1;
        }
        entry++;
        if (entry->key == -1)
            goto notfound;
    }
notfound:
    *out = 0;
    return 0;
}

/* The resident block this reads its state from. */
extern char D_00189E20_2[];

extern void anim_start_blended(void *, int, int, int);

/* Routes the object the state word names to the mode the helper reports: the helper's value
   and the caller's index are handed over with the caller's float as an int, otherwise the
   object's own flag picks the fixed mode 7. Same two gates as its sibling below. */
void hero_start_linked_object_anim(int seq, int frame, float speed)
{
    char *base = D_00189E20_2;
    int animId;

    if (*(int *)(base + 0x2494) == 0)
        return;
    if (*(int *)(base + 0x2498) == 0)
        return;
    if (hero_lookup_anim_by_key(seq, &animId) != 0) {
        anim_start_blended(*(void **)(base + 0x2494), animId, frame, (int)speed);
    } else if (*(unsigned char *)(*(char **)(base + 0x2494) + 0x43) != 0) {
        anim_start_blended(*(void **)(base + 0x2494), 0, 0, 7);
    }
}

/* Publishes the resident clock into the object the state word names, once the state word and
   the second gate are both set and the helper accepts the object's key. */
void hero_sync_linked_object_clock(void)
{
    char *base = D_00189E20_2;
    int animId;
    int linkedObj;

    if (*(int *)(base + 0x2494) == 0)
        return;
    if (*(int *)(base + 0x2498) == 0)
        return;
    if (hero_lookup_anim_by_key(*(unsigned char *)(*(char **)(base + 0x2290) + 0x43), &animId) == 0)
        return;
    linkedObj = *(int *)(base + 0x2494);
    *(float *)(linkedObj + 0x48) = *(float *)(base + 0xC20);
}


/* func_L00_002D2168 is in L00_002D1ED8-g8.c. */


/* updates the resident selection and index after validating the selected table entry */
void hero_select_anim_frame(Rac2Native_28c929cadd7aca24_s32 selected, Rac2Native_28c929cadd7aca24_s32 index) {
    if (selected >= 0) {
        Rac2Native_28c929cadd7aca24_u8 *object = D_00189E20_19.object;
        Rac2Native_28c929cadd7aca24_s32 offset = object[0x43] * 4;
        Rac2Native_28c929cadd7aca24_u8 *table = *(Rac2Native_28c929cadd7aca24_u8 **)(object + 0x24);
        Rac2Native_28c929cadd7aca24_u8 *entry = *(Rac2Native_28c929cadd7aca24_u8 **)(table + offset + 0x48);
        if (index < entry[0x10]) {
            D_00189E20_19.selected = selected;
            D_00189E20_19.index = index;
        }
    }
}

/* Marks no slot as running and parks the cursor past the end of the list. */
void hero_clear_queued_anim(void) {
    char *hero = D_00189E20_8;
    *(int *)(hero + 0xC40) = -1;
    *(int *)(hero + 0xC48) = 0;
}

/* The resident word published below. */
extern int D_0018AA68;

/* Publishes the argument into the resident word, with 0xFFFFFFFF becoming 5. */
void hero_set_anim_mode(int value)
{
    if (value == -1)
        value = 5;
    D_0018AA68 = value;
}


/* func_L00_002D2E68 is in L00_002D1ED8-scan-g8.c. */

/* shared native body of family ea34650e369e */
/* Clears the flag bit on the hero and its attached objects, and sets other bits on them in some special cases. */
void hero_clear_objects_flag_bit(void)
{
    char *hero = D_00189E20_17;
    char *obj;
    int i;

    obj = *(char **)(hero + 3096);
    *(unsigned short *)(obj + 52) &= 0xFFFE;

    for (i = 0; i < 7; i++) {
        obj = *(char **)(hero + 4640 + i * 80);
        if (obj != 0)
            *(unsigned short *)(obj + 52) &= 0xFFFE;
        obj = *(char **)(hero + 4644 + i * 80);
        if (obj != 0)
            *(unsigned short *)(obj + 52) &= 0xFFFE;
        obj = *(char **)(hero + 4648 + i * 80);
        if (obj != 0)
            *(unsigned short *)(obj + 52) &= 0xFFFE;
    }

    if (1) {
        char *heroBlock = D_00189E20_17;
        obj = *(char **)(heroBlock + 4892);
        if (obj != 0)
            *(unsigned short *)(obj + 52) &= 0xFFFE;
    }

    if (1) {
        char *heroBlock = D_00189E20_17;
        if (*(unsigned char *)(heroBlock + 8884) == 1) {
            heroBlock = D_00189E20_17;
            obj = *(char **)(heroBlock + 6244);
            if (obj != 0)
                *(unsigned short *)(obj + 52) &= 0xFFFE;
        }
    }

    if (1) {
        char *heroBlock = D_00189E20_17;
        if (*(short *)(heroBlock + 9468) != 0 || *(int *)(heroBlock + 8860) == 31) {
            heroBlock = D_00189E20_17;
            obj = *(char **)(heroBlock + 4880);
            if (obj != 0)
                *(unsigned short *)(obj + 52) |= 0x41;
            heroBlock = D_00189E20_17;
            obj = *(char **)(heroBlock + 4884);
            if (obj != 0)
                *(unsigned short *)(obj + 52) |= 0x41;
            heroBlock = D_00189E20_17;
            obj = *(char **)(heroBlock + 4892);
            if (obj != 0)
                *(unsigned short *)(obj + 52) |= 0x41;
        }
    }

    if (1) {
        char *heroBlock = D_00189E20_17;
        if ((*(unsigned char *)(heroBlock + 8894) != 0 && *(int *)(heroBlock + 4680) == 10) ||
            *(unsigned char *)(heroBlock + 8895) != 0) {
            char *heroBlock2 = D_00189E20_17;
            obj = *(char **)(heroBlock2 + 4640);
            if (obj != 0)
                *(unsigned short *)(obj + 52) |= 0x41;
        }
    }
}

/* Set bit0 of the primary object's halfword flags and of the optional secondary object's flags */
void hero_set_pair_flag_bit(void) {
    FlagPairResidentView *root = (FlagPairResidentView *)D_00189E20_1;
    FlagPairObjectView *primary = root->primary;
    FlagPairObjectView *secondary;
    primary->flags |= 1;
    secondary = root->secondary;
    if (secondary) secondary->flags |= 1;
}

/* Clear bit0 of the primary object's halfword flags and of the optional secondary object's flags */
void hero_clear_pair_flag_bit(void) {
    FlagPairResidentView *root = (FlagPairResidentView *)D_00189E20_1;
    FlagPairObjectView *primary = root->primary;
    FlagPairObjectView *secondary;
    primary->flags &= ~1;
    secondary = root->secondary;
    if (secondary) secondary->flags &= ~1;
}


/* The matrix the level state keeps 0x90 bytes in; the state itself is 0x90 below it. */
extern char D_00189EB0[];

extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern float mat_fast_helper_a(float, float);
extern void vec_clear_128(void *);
extern void transform_vector(void *, void *, void *);
extern void euler_to_matrix(void *, void *);

typedef int TI128_L00_002D3290 __attribute__((mode(TI)));

/* Rotates the level state's aim vector: the two angles of the state's yaw and pitch
   drive two matrix builds, and the state's own vector is transformed between them. */
float hero_compute_aim_angle(void)
{
    TI128_L00_002D3290 matrix[4];
    float aimVec[4];
    float rollRot[4];
    float yawRot[4];
    float aimCopy[4];
    float angle;
    char *heroState;

    aimVec[0] = math_fast_sin_or_cos_a(0.0f);
    aimVec[1] = math_fast_sin_or_cos_b(0.0f);
    aimVec[2] = 0.0f;
    euler_to_matrix(matrix, D_00189EB0);
    transform_vector(aimVec, aimVec, matrix);
    heroState = D_00189EB0 - 0x90;

    if (*(float *)(heroState + 0x2A0) != 0.0f || *(float *)(heroState + 0x2A4) != 0.0f) {
        *(TI128_L00_002D3290 *)aimCopy = *(TI128_L00_002D3290 *)(heroState + 0x2A0);
        vec_clear_128(rollRot);
        vec_clear_128(yawRot);
        angle = mat_fast_helper_a(*(float *)(heroState + 0x2A0), *(float *)(heroState + 0x2A4));
        rollRot[2] = -angle;
        euler_to_matrix(matrix, rollRot);
        transform_vector(aimVec, aimVec, matrix);
        transform_vector(aimCopy, aimCopy, matrix);
        yawRot[1] = -mat_fast_helper_a(aimCopy[2], aimCopy[0]);
        euler_to_matrix(matrix, yawRot);
        transform_vector(aimVec, aimVec, matrix);
        rollRot[2] = -rollRot[2];
        euler_to_matrix(matrix, rollRot);
        transform_vector(aimVec, aimVec, matrix);
    }

    return mat_fast_helper_a(aimVec[0], aimVec[1]);
}
