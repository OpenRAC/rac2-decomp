#include "include_asm.h"
#include "names.h"

typedef int V1306TI __attribute__((mode(TI)));
typedef union { V1306TI q; float f[4]; } V1306Vec;
typedef struct { int entry[6]; } V1306Table;
typedef struct { V1306TI q[5]; } __attribute__((aligned(16))) V1306Packet;
typedef struct { char pad[4]; unsigned char flag; char mid[107]; float f70; char tail[108]; } V1306Material;
extern unsigned char g_item_slot_to_record[];
extern V1306Material g_weapon_l00_table[];
extern V1306Packet D_L00_002A26A0;
extern V1306Table D_L00_001AEFE0, D_L00_001AEFF8;
extern char g_camera_l00_position[], g_area_hit_targets[];
typedef struct { char pad[0x160]; float amount; int unused, duration, state; } V1439Camera;
extern V1439Camera D_L00_001B8C80;
extern float IntToFloat(int);
extern void FastVecScale(char *, char *, float);
extern void FastVecSub(char *, char *, char *);
extern void FastVecAdd(char *, char *, char *);
extern float FastVecDot(char *, char *);
extern void vec_fast_divide_helper(char *, char *, float);
extern int coll_process_hit(char *, int, char *, int, float);
extern void moby_queue_knockback_for_nodes(char *, char *, char *, int, int, int, int, int, float, float, float);
extern int math_random_int_range(int, int);
extern char *part_spawn_spinning_debris(char *, char *, int, int, int);
extern int FloatToInt(float);
extern int gfx_swap_packed_color_channels(int, int);
extern char *part_spawn_firework_spark(char *, char *, int, int, float, int, int, float, int, int);
extern char *part_create_explosion(char *, char *, char *, int, int, int, int, int, float);
extern void swap_color_channel_words(int *, int *, int *, int);
extern int PlayMobySound(int, int, char *);
extern char *moby_spawn_template_effect(void *, char *, int, void *);
static inline V1306Material *V1306Current(void) { return (V1306Material *)(g_item_slot_to_record[12] * 224 + (int)g_weapon_l00_table); }
#define V1306_FLAG (V1306Current()->flag != 0)

extern int math_random_int_below(int mode);

extern float coll_get_ground_height_at_position(char *object, char *local);

extern void func_00282D30_7(char *local, int value, float scale);

extern float func_002A7878_1(float low, float high);

extern void part_spawn_bubble(char *object, char *local, float amount, float base);

/* Measured partial layouts; original type and game roles are unknown. */
typedef struct Rac2Native_b1b523716b470b36_FamilyNative192Vector {
    float x;
    float y;
    float z;
    float w;
} Rac2Native_b1b523716b470b36_FamilyNative192Vector;

extern void func_00282CF0_11(Rac2Native_b1b523716b470b36_FamilyNative192Vector *out,
    const Rac2Native_b1b523716b470b36_FamilyNative192Vector *first, const Rac2Native_b1b523716b470b36_FamilyNative192Vector *second);

extern void func_00282CC0_23(Rac2Native_b1b523716b470b36_FamilyNative192Vector *out,
    const Rac2Native_b1b523716b470b36_FamilyNative192Vector *first, const Rac2Native_b1b523716b470b36_FamilyNative192Vector *second);

#ifndef RAC2_T_WORKER_F9E2CD219
#define RAC2_T_WORKER_F9E2CD219
typedef struct {
    unsigned char pad00[76];
    short field4C;
    unsigned char pad4E[2];
    int field50;
    float field54;
    float field58;
} Worker_F9e2cd219;
#endif

#ifndef RAC2_T_OWNER_F9E2CD219
#define RAC2_T_OWNER_F9E2CD219
typedef struct {
    unsigned char pad00[104];
    Worker_F9e2cd219 *child;
} Owner_F9e2cd219;
#endif

extern float math_ease_out_quad(float value);

extern void mat_build_rotation_toward_vector(void *out, void *in, void *tmp, int mode, float value);

extern void moby_l00_place_part_from_direction(void *owner, void *out);

/* Measured partial C views; original types and object ownership are unknown. */
typedef unsigned char QwenRecovery_4ecc6b5a4034_u8;

typedef unsigned int QwenRecovery_4ecc6b5a4034_u32;

/* Minimum external views; neither declaration allocates original game storage. */
typedef struct {
    QwenRecovery_4ecc6b5a4034_u8 prefix[0x24];
    QwenRecovery_4ecc6b5a4034_u32 word;
    QwenRecovery_4ecc6b5a4034_u8 tail[8];
} QwenRecovery_4ecc6b5a4034_ExtraResetRecord164;

extern QwenRecovery_4ecc6b5a4034_ExtraResetRecord164 D_L00_002372C0[100];

extern QwenRecovery_4ecc6b5a4034_u32 D_L00_00238580[139];

extern void func_00282CF0_12(Rac2Native_b1b523716b470b36_FamilyNative192Vector *out,
    const Rac2Native_b1b523716b470b36_FamilyNative192Vector *first, const Rac2Native_b1b523716b470b36_FamilyNative192Vector *second);

extern void func_00282CC0_24(Rac2Native_b1b523716b470b36_FamilyNative192Vector *out,
    const Rac2Native_b1b523716b470b36_FamilyNative192Vector *first, const Rac2Native_b1b523716b470b36_FamilyNative192Vector *second);

extern void moby_l00_place_part_from_direction_2(void *owner, void *out);

/* Measured partial layouts; original type and game roles are unknown. */
typedef unsigned int Rac2Native_03c444112283bc5f_u32;

extern Rac2Native_03c444112283bc5f_u32 D_L00_00238DF0[139];

extern void projectile_bouncing_update(char *object);

extern void projectile_falling_update(char *object);

extern float func_00283B98_5(float value, float step);

extern void moby_fade_colour_by_countdown(char *object);

extern void func_00300190_3(char *target, char *source);

extern void shop_trigger_current_state_effect(char *target, char *source);

extern void weapon_update_hit_sweep(char *object);

/* Does nothing. */
void stub_l00_nop_3(void)
{
}

/* Level object-update walk: one pass over the object list the game exposes at
 * D_L00_001B1EA8, with a per-class dispatch. */
/* Runs the level's per-frame update: goes through every object and updates a few special kinds, then runs the shared effect updates. */
typedef unsigned char L00_0037F7E8_u8;
typedef unsigned short L00_0037F7E8_u16;
typedef unsigned int L00_0037F7E8_u32;

extern void SetBackgroundColor(int, int, int);

extern int request_begin_slot(int, int, int, int, int);

/* The empty method this call reaches sits in a different copy in each level
 * (the catalogue splits the identical bodies), so the callee takes a ref_ name:
 * its value is read from the retail bytes at every place. */
extern unsigned int ref_L00_0036F480_00(void);

extern void game_reset_frame_counters(void);

extern void UpdateSoundVoices();

extern L00_0037F7E8_u8 *func_002A08A0(void);

extern L00_0037F7E8_u8 *D_L00_001B1EA8 __attribute__((sda));

extern void func_002A05A8(char *);

extern void func_002A0F48(void *);

extern void hero_l00_update_frame_2(void);

extern void cam_update_state(void);

extern void UpdateObjectPreviewSequence(void);

extern void part_update_all(void);

extern void game_update_idle_frame_counters(void);

extern L00_0037F7E8_u32 g_save_menu_flags __attribute__((sda));

/* Measured partial layout; original type and game roles are unknown. */
typedef struct L00_0037F7E8_Object {
    L00_0037F7E8_u8 pad00[0x20];
    signed char field20;
    L00_0037F7E8_u8 pad21[7];
    struct L00_0037F7E8_Object *next;
    L00_0037F7E8_u8 pad2C[8];
    L00_0037F7E8_u16 field34;
    L00_0037F7E8_u8 pad36[0x2e];
    void (*field64)(struct L00_0037F7E8_Object *);
    L00_0037F7E8_u8 pad68[0x42];
    short fieldAA;
} L00_0037F7E8_Object;

/* The level's own data: each place resolves its own value from the retail
 * bytes. The two adjacent flags stay one array so both sites keep the retail's
 * in-place absolute load, which the sda attribute selects. */
extern int ref_L00_001A8F00_00 __attribute__((sda));

extern L00_0037F7E8_u8 ref_L00_001B267C_00[] __attribute__((sda));

void moby_update_level_objects(void)
{
    L00_0037F7E8_u8 *head;
    L00_0037F7E8_Object *object;
    short id;

    SetBackgroundColor(0, 0, 0);
    if (ref_L00_001A8F00_00 == 0 && (g_save_menu_flags & 1)) {
        if (request_begin_slot(4, 1, 1, 0, 0) == 0)
            return;
    }
    if (ref_L00_0036F480_00() != 0)
        return;
    game_reset_frame_counters();
    UpdateSoundVoices();
    D_L00_001B1EA8 = head = func_002A08A0();
    object = (L00_0037F7E8_Object *)head;
    if (object != 0) {
        while (object != 0) {
            if (object->field20 >= 0) {
                id = object->fieldAA;
                if (id == 0xDC1 /* moby class 3521 */) {
                    object->field64(object);
                    if ((object->field34 & 4) == 0)
                        func_002A0F48(object);
                } else if (id == 0xCB2 /* Synthenoid */ || id == 0xB02 /* Kilonoid */
                           || id == 0x259 /* moby class 601 */
                           || id == 0xA5C /* Shield Charger */ || id == 0x1192 /* Tesla Barrier */) {
                    func_002A05A8((char *)object);
                    func_002A0F48(object);
                }
            }
            object = object->next;
        }
    }
    if (ref_L00_001B267C_00[0])
        hero_l00_update_frame_2();
    if (ref_L00_001B267C_00[1])
        cam_update_state();
    UpdateObjectPreviewSequence();
    part_update_all();
    game_update_idle_frame_counters();
}

/* func_L00_0037FA90 is defined in L00_0037FA90-qcopy.c. */

typedef struct {
    char *entry[64][4];
    int count;
    int best;
} L00_0037FE08_Pool;

extern L00_0037FE08_Pool D_L00_00231540;

extern char g_hero_position[];

extern float vec_fast_helper_c(char *origin, char *point);

/* Keep the pool entry nearest to the fixed origin: the count is re-read every
 * pass, so the loop bound stays live in memory. */
/* Finds which stored object is closest to a fixed spot and remembers its number. */
void moby_find_nearest_pool_entry(void)
{
    float best;
    int i;

    if (D_L00_00231540.count != 0) {
        best = 100000000.0f;
        for (i = 0; i < D_L00_00231540.count; i++) {
            float distance = vec_fast_helper_c(g_hero_position, D_L00_00231540.entry[i][0] + 0x10);

            if (distance < best) {
                D_L00_00231540.best = i;
                best = distance;
            }
        }
    }
}


extern int FindSurfaceGridCell(int object, char *name, int first, int second);

/* 16-slot object table searched for the first entry the name resolver accepts.
 * The `sda` attribute (SYMBOL_REF_FLAG) suppresses gcc's HIGH/LO_SUM split: its
 * `lui`/`addiu` pair is one RTL insn, so the address stays in the single
 * callee-saved register that retail uses instead of taking an extra one. */
extern int *g_collected_objects[] __attribute__((sda));

/* Checks the sixteen collected objects and returns 1 if any of them accepts the given name, otherwise 0. */
int moby_find_accepting_table_object(char *name)
{
    int i = 0;
    int **slot = g_collected_objects;

    do {
        int object = *slot;
        if (object == 0)
            break;
        if (FindSurfaceGridCell(object, name, 0, 0))
            return 1;
        i++;
        slot++;
    } while (i < 16);
    return 0;
}

/* Update handler that does nothing. */
void moby_l00_update_empty(void)
{
}

/* Update handler that does nothing. */
void moby_l00_update_empty_2(void)
{
}

/* func_L00_003825C8 is defined in L00_003825C8.c. */

extern void ref_L00_003827C0_00(void);

/* Update handler that just calls the shared update. */
void moby_update_via_shared_handler(void)
{
    ref_L00_003827C0_00();
}

/* func_L00_00382910 is defined in L00_00382910.c. */



/* func_L00_00382F28 is defined in L00_0037E898-g8.c. */



/* func_L00_00384248 is defined in L00_0037E898-trail-g8.c. */

/* func_L00_00384678 is defined in L00_00384678-g8.c. */

/* func_L00_00384C20 is matched in L00_00384C20.c (built with -fno-strength-reduce). */

/* func_L00_00384CA8 is defined in L00_00384CA8-qcopy.c. */




/* func_L00_00387370 is defined in L00_00387370-g8-qcopy.c. */

/* Family 6eb4f363e5305bed: seed body at func_L00_00387408. */
/* Throws out a small burst of effect at the object's position. */
void part_l00_spawn_object_effect_burst(char *object)
{
    char local[16];
    float base;
    int value = *(int *)(object + 104);

    if (math_random_int_below(5))
        return;
    base = coll_get_ground_height_at_position(object + 16, local);
    func_00282D30_7(local, value, 0.25f);
    part_spawn_bubble(object + 16, local, func_002A7878_1(0.05f, 0.1f) * 210000.0f, base);
}

/* Update the owner vector using the two bound vector helpers, refresh the three saved source coordinates, and conditionally set the measured owner byte to 7; original game role is unknown. */
void moby_l00_follow_source_position(void *object)
{
    Rac2Native_b1b523716b470b36_FamilyNative192Vector input;
    Rac2Native_b1b523716b470b36_FamilyNative192Vector output;
    char *base = (char *)object;
    char *state;
    char *source;
    char *kind;
    char *extra;

    input.w = 0.0f;
    state = *(char **)(base + 0x68);
    input.x = *(float *)(state + 0x74);
    input.y = *(float *)(state + 0x78);
    input.z = *(float *)(state + 0x7c);
    source = *(char **)(state + 0x70);
    func_00282CF0_11(&output,
        (const Rac2Native_b1b523716b470b36_FamilyNative192Vector *)(source + 0x10), &input);
    func_00282CC0_23((Rac2Native_b1b523716b470b36_FamilyNative192Vector *)(base + 0x10), &output,
        (const Rac2Native_b1b523716b470b36_FamilyNative192Vector *)(base + 0x10));
    source = *(char **)(state + 0x70);
    *(float *)(state + 0x74) = *(float *)(source + 0x10);
    *(float *)(state + 0x78) = *(float *)(source + 0x14);
    *(float *)(state + 0x7c) = *(float *)(source + 0x18);
    kind = *(char **)(source + 0x24);
    if (*(short *)(kind + 0x46) == 0x12) {
        extra = *(char **)(source + 0x68);
        if (*(unsigned char *)(extra + 0x14) == 0) {
            *(unsigned char *)(base + 0x20) = 7;
        }
    }
}

/* Shared native body; original game role is unknown. */
/* Moves a child object forward along its blend and marks it done when it reaches the end. */
void moby_l00_advance_child_blend(Owner_F9e2cd219 *self)
{
    Worker_F9e2cd219 *child = self->child;

    mat_build_rotation_toward_vector((char *)child + 48, (char *)child + 16, (char *)child + 32, 0,
            math_ease_out_quad(child->field54));

    child->field54 = child->field54 + child->field58;
    moby_l00_place_part_from_direction(self, (char *)child + 48);

    if (child->field54 > 0.9f)
        child->field50 = 1;
    else
        child->field50 = 0;

    if (child->field54 >= 1.0f) {
        child->field54 = 1.0f;
        child->field4C = 1;
    }
}

/* Clear the selected word in 100 records, reset 136 state words, and set the three trailing state words. */
void state_reset_records(void)
{
    int i;
    for (i = 99; i >= 0; --i)
        D_L00_002372C0[i].word = 0;
    D_L00_00238580[138] = 5;
    D_L00_00238580[137] = 0;
    D_L00_00238580[136] = 0;
    for (i = 0; i < 64; ++i) {
        D_L00_00238580[i] = 0;
        D_L00_00238580[i + 64] = 0;
    }
    for (i = 7; i >= 0; --i)
        D_L00_00238580[i + 128] = 0;
}

extern void ref_L00_00387F98_00(void *arg);

/* Runs the shared reset on the state word block. */
void state_l00_apply_shared_reset_words(void)
{
    ref_L00_00387F98_00(D_L00_00238580);
}

/* shared native body of family a04928c6 */
/* Fills a block with its starting values: unit scales, corner offsets of plus and minus 2, and a fixed flag value. */
void gfx_l00_init_default_block(char *block)
{
    *(long long *)(block + 112) = 0LL;
    *(int *)(block + 80) = 0;
    *(int *)(block + 84) = 0;
    *(float *)(block + 88) = 1.0f;
    *(int *)(block + 92) = 0;
    *(int *)(block + 96) = 0;
    *(float *)(block + 100) = 1.0f;
    *(float *)(block + 104) = 1.0f;
    *(float *)(block + 108) = 1.0f;
    *(float *)(block + 8) = -2.0f;
    *(float *)(block + 24) = 2.0f;
    *(float *)(block + 40) = -2.0f;
    *(float *)(block + 56) = 2.0f;
    *(float *)(block + 4) = -2.0f;
    *(float *)(block + 36) = 2.0f;
    *(int *)(block + 0) = 0;
    *(int *)(block + 16) = 0;
    *(int *)(block + 32) = 0;
    *(int *)(block + 48) = 0;
    *(float *)(block + 12) = 1.0f;
    *(float *)(block + 28) = 1.0f;
    *(float *)(block + 44) = 1.0f;
    *(long long *)(block + 128) = 0x0000FF9000000260LL;
    *(float *)(block + 20) = -2.0f;
    *(float *)(block + 52) = 2.0f;
    *(float *)(block + 60) = 1.0f;
}

/* func_L00_00388490 is defined in L00_00388490.c. */

/* func_L00_00388790 is defined in L00_00388790-qcopy.c. */

/* Family 6eb4f363e5305bed: seed body at func_L00_00387408. */
/* Throws out a small burst of effect at the object's position. */
void part_l00_spawn_object_effect_burst_2(char *object)
{
    char local[16];
    float base;
    int value = *(int *)(object + 104);

    if (math_random_int_below(5))
        return;
    base = coll_get_ground_height_at_position(object + 16, local);
    func_00282D30_7(local, value, 0.25f);
    part_spawn_bubble(object + 16, local, func_002A7878_1(0.05f, 0.1f) * 210000.0f, base);
}

/* Update the owner vector using the two bound vector helpers, refresh the three saved source coordinates, and conditionally set the measured owner byte to 7; original game role is unknown. */
void moby_l00_follow_source_position_2(void *object)
{
    Rac2Native_b1b523716b470b36_FamilyNative192Vector input;
    Rac2Native_b1b523716b470b36_FamilyNative192Vector output;
    char *base = (char *)object;
    char *state;
    char *source;
    char *kind;
    char *extra;

    input.w = 0.0f;
    state = *(char **)(base + 0x68);
    input.x = *(float *)(state + 0x74);
    input.y = *(float *)(state + 0x78);
    input.z = *(float *)(state + 0x7c);
    source = *(char **)(state + 0x70);
    func_00282CF0_12(&output,
        (const Rac2Native_b1b523716b470b36_FamilyNative192Vector *)(source + 0x10), &input);
    func_00282CC0_24((Rac2Native_b1b523716b470b36_FamilyNative192Vector *)(base + 0x10), &output,
        (const Rac2Native_b1b523716b470b36_FamilyNative192Vector *)(base + 0x10));
    source = *(char **)(state + 0x70);
    *(float *)(state + 0x74) = *(float *)(source + 0x10);
    *(float *)(state + 0x78) = *(float *)(source + 0x14);
    *(float *)(state + 0x7c) = *(float *)(source + 0x18);
    kind = *(char **)(source + 0x24);
    if (*(short *)(kind + 0x46) == 0x12) {
        extra = *(char **)(source + 0x68);
        if (*(unsigned char *)(extra + 0x14) == 0) {
            *(unsigned char *)(base + 0x20) = 7;
        }
    }
}

/* Shared native body; original game role is unknown. */
/* Moves a child object forward along its blend and marks it done when it reaches the end. */
void moby_l00_advance_child_blend_2(Owner_F9e2cd219 *self)
{
    Worker_F9e2cd219 *child = self->child;

    mat_build_rotation_toward_vector((char *)child + 48, (char *)child + 16, (char *)child + 32, 0,
            math_ease_out_quad(child->field54));

    child->field54 = child->field54 + child->field58;
    moby_l00_place_part_from_direction_2(self, (char *)child + 48);

    if (child->field54 > 0.9f)
        child->field50 = 1;
    else
        child->field50 = 0;

    if (child->field54 >= 1.0f) {
        child->field54 = 1.0f;
        child->field4C = 1;
    }
}

/* Reset two 64-word banks, eight trailing words, and three state words. The original game role is unknown. */
void state_reset_words(void)
{
    int i;
    D_L00_00238DF0[138] = 5;
    D_L00_00238DF0[137] = 0;
    D_L00_00238DF0[136] = 0;
    for (i = 0; i < 64; ++i) {
        D_L00_00238DF0[i] = 0;
        D_L00_00238DF0[i + 64] = 0;
    }
    for (i = 7; i >= 0; --i)
        D_L00_00238DF0[i + 128] = 0;
}

extern void ref_L00_0038A9E0_00(void *arg);

/* Runs the shared reset on the state word block. */
void state_l00_apply_shared_reset_words_2(void)
{
    ref_L00_0038A9E0_00(D_L00_00238DF0);
}

/* shared native body of family a04928c6 */
/* Fills a block with its starting values: unit scales, corner offsets of plus and minus 2, and a fixed flag value. */
void gfx_l00_init_default_block_2(char *block)
{
    *(long long *)(block + 112) = 0LL;
    *(int *)(block + 80) = 0;
    *(int *)(block + 84) = 0;
    *(float *)(block + 88) = 1.0f;
    *(int *)(block + 92) = 0;
    *(int *)(block + 96) = 0;
    *(float *)(block + 100) = 1.0f;
    *(float *)(block + 104) = 1.0f;
    *(float *)(block + 108) = 1.0f;
    *(float *)(block + 8) = -2.0f;
    *(float *)(block + 24) = 2.0f;
    *(float *)(block + 40) = -2.0f;
    *(float *)(block + 56) = 2.0f;
    *(float *)(block + 4) = -2.0f;
    *(float *)(block + 36) = 2.0f;
    *(int *)(block + 0) = 0;
    *(int *)(block + 16) = 0;
    *(int *)(block + 32) = 0;
    *(int *)(block + 48) = 0;
    *(float *)(block + 12) = 1.0f;
    *(float *)(block + 28) = 1.0f;
    *(float *)(block + 44) = 1.0f;
    *(long long *)(block + 128) = 0x0000FF9000000260LL;
    *(float *)(block + 20) = -2.0f;
    *(float *)(block + 52) = 2.0f;
    *(float *)(block + 60) = 1.0f;
}

/* func_L00_0038AAD0 is defined in L00_0038AAD0.c. */


extern void *D_L00_001BF218;

extern void *ref_L00_0038B848_00(void *arg);

/* Returns 1 if the current record has its ninth byte equal to 1, otherwise 0. */
int record_is_current_byte_one(void)
{
    int result = 0;
    unsigned char *record = 0;
    if (D_L00_001BF218) {
        record = (unsigned char *)ref_L00_0038B848_00(D_L00_001BF218);
    }
    if (record) {
        result = (record[9] == 1);
    }
    return result;
}

extern void *D_L00_001BF218;

extern void *ref_L00_0038B848_00(void *arg);

/* Returns 1 if the current record has bit 2 set in its flags, otherwise 0. */
int record_is_current_flag_set(void)
{
    unsigned short *record = (unsigned short *)ref_L00_0038B848_00(D_L00_001BF218);
    if (record) {
        if (record[15] & 2) {
            return 1;
        }
    }
    return 0;
}



extern unsigned char D_001A7B2A __attribute__((sda));

/* Measured partial layouts; the original types and game roles are unknown. */
typedef struct L00_0038BD00_Kind {
    unsigned char pad00[0x46];
    short type;
} L00_0038BD00_Kind;

typedef struct L00_0038BD00_Node {
    unsigned char pad00[0x20];
    unsigned char mode;
    unsigned char pad21[3];
    L00_0038BD00_Kind *kind;
    struct L00_0038BD00_Node *next;
} L00_0038BD00_Node;

typedef struct {
    unsigned char pad[0x2290];
    int value;
} D_00189E20_Struct;

extern D_00189E20_Struct g_hero_state;

extern float fast_vec_dist(char *object, char *other);

extern int pickup_start_fly_to_target(char *object, int value, float first, float second);

extern int moby_is_ammo(char *object);

extern int pickup_check_stock_increase(char *value);

/* Walk the level's node list from D_L00_001B1EA8: each node's own measure is
 * compared with the limit (2.7, or 10.0 when D_001A7B2A is set); a node of kind
 * 0x13 is then handed to func_003022A0, any other node to its own handler. A mode
 * of 0xFE or 0xFD, or a null next pointer, ends the walk. */
/* Looks for a nearby object to act on and stops after the first one that responds. */
void moby_trigger_nearby_response(char *object)
{
    L00_0038BD00_Node *node;
    float limit;
    float step;
    float value;
    int mode;
    int result;
    L00_0038BD00_Kind *kind;

    limit = 2.7f;
    if (D_001A7B2A != 0)
        limit = 10.0f;
    node = (L00_0038BD00_Node *)D_L00_001B1EA8;
    if (node == 0)
        return;
    step = 0.01745329424738884f;
    while (1) {
        mode = node->mode;
        if (mode == 0xFE)
            return;
        if (mode == 0xFD)
            return;
        if (node != 0 && (kind = node->kind) != 0 && kind->type == 0x13) {
            value = fast_vec_dist((char *)node + 0x10, object + 0x10);
            if (value < limit) {
                value = func_002A7878_1(-30.0f, 30.0f);
                result = pickup_start_fly_to_target((char *)node, g_hero_state.value, value * step, 0.0f);
            } else {
                node = node->next;
                goto next;
            }
        } else {
            if (moby_is_ammo((char *)node) == 0) {
                node = node->next;
                goto next;
            }
            value = fast_vec_dist((char *)node + 0x10, object + 0x10);
            if (value < limit) {
                result = pickup_check_stock_increase((char *)node);
            } else {
                node = node->next;
                goto next;
            }
        }
        if (result != 0)
            return;
        node = node->next;
next:
        /* The walk's end test: the goto above reaches it with the next pointer
         * already loaded, which is the shape retail's code has. */
        if (node == 0)
            return;
    }
}

extern float D_00189EB8;

extern float mat_fast_helper_a(float first, float second);

extern float FastDiffRots(float value, float angle);

extern float FastVecLength(char *object);

extern void vec_scale_to_length(char *object, char *other, float value);

/* Fold an angle into the measured 1.8325959 ceiling, ease the remaining gap and
 * hand the result to the setter. */
/* Shrinks the object's vector depending on an angle, so it gets shorter when the angle is small. */
void vec_scale_by_angle_limit(char *object)
{
    float limit = 1.83259594440460205078125f;
    float base = mat_fast_helper_a(*(float *)object, *(float *)(object + 4));
    float scaled = FastDiffRots(D_00189EB8, base);
    float angle;

    if (limit < scaled)
        scaled = limit;
    angle = FastVecLength(object);
    vec_scale_to_length(object, object,
        angle * ((limit - scaled) * 0.1637022197246551513671875f + 0.699999988079071044921875f));
}


/* Dispatches on a byte mode at object+32: mode 0 updates two float angles from a linked node and runs a follow-up call; mode 1 refreshes a 16-byte block and a node copy then calls a final update. */
/* Updates this object each frame: in the first state it turns and fades, in the second it refreshes its position. */
void turning_fading_moby_update(char *object)
{
    char *moby = object;
    unsigned char mode = *(unsigned char *)(moby + 32);
    char *vars = *(char **)(moby + 104);
    float result;

    switch (mode) {
    case 0:
        if (*(int *)(vars + 20) != 0) {
            projectile_bouncing_update(moby);
        } else {
            projectile_falling_update(moby);
        }
        result = func_00283B98_5(*(float *)(moby + 240), 3.4906592220067977905273e-02f);
        *(float *)(moby + 240) = result;
        result = func_00283B98_5(*(float *)(moby + 244), 1.3089971244335174560547e-01f);
        *(float *)(moby + 244) = result;
        moby_fade_colour_by_countdown(moby);
        break;
    case 1:
        func_00300190_3((char *)(moby + 16), (char *)(moby + 16));
        shop_trigger_current_state_effect(vars, vars);
        weapon_update_hit_sweep(moby);
        break;
    }
}


/* Makes a big explosion with sparks, smoke and glow at the object, and shakes the camera more when the player is close. */
void part_spawn_big_explosion(char *object, char *direction, char *axis)
{
    V1306Packet packet;
    V1306Vec delta, temp, vector, random;
    V1306Table first, second;
    int red, green, blue, red2, green2, blue2;
    int *child;
    int i, n, counter, asset1, asset2, life1, life2;
    float scale, length, twice, speed, force;
    packet = D_L00_002A26A0;
    child = *(int **)(object + 0x68);
    scale = IntToFloat(V1306_FLAG) + 1.0f;
    FastVecScale(direction, direction, scale);
    FastVecSub((char *)&delta, g_camera_l00_position, object + 0x10);
    length = FastVecLength((char *)&delta);
    i = coll_process_hit(object + 0x10, 16, object, 0, scale * 0.5f);
    vector.q = *(V1306TI *)(object + 0x10);
    moby_queue_knockback_for_nodes(object, (char *)&vector, g_area_hit_targets, i, 0, 0x830000, 2, 1,
        V1306Current()->f70, 1.0f, 1.0f);
    object[0x20] = 1;
    for (counter = 0; counter < 10; counter++) {
        random.q = 0;
        random.f[0] = func_002A7878_1(-1.0f, 1.0f);
        random.f[1] = func_002A7878_1(-1.0f, 1.0f);
        vector.q = random.q;
        vec_scale_to_length((char *)&temp, axis, FastVecDot((char *)&vector, axis));
        FastVecSub((char *)&vector, (char *)&vector, (char *)&temp);
        vec_scale_to_length((char *)&temp, axis, func_002A7878_1(0.0f, 1.0f));
        FastVecAdd((char *)&vector, (char *)&vector, (char *)&temp);
        vec_scale_to_length((char *)&vector, (char *)&vector, scale * func_002A7878_1(3.5f, 6.5f) * (1.0f/60.0f));
        FastVecAdd((char *)&vector, (char *)&vector, direction);
        life1 = math_random_int_range(60,120);
        part_spawn_spinning_debris(object+0x10, (char *)&vector, life1, 0, V1306_FLAG);
    }
    twice = length + length;
    for (n = 0; n < 4; n++) {
        random.q = 0;
        random.f[0] = func_002A7878_1(-1.0f, 1.0f);
        random.f[1] = func_002A7878_1(-1.0f, 1.0f);
        vector.q = random.q;
        vec_scale_to_length((char *)&temp, axis, FastVecDot((char *)&vector, axis));
        FastVecSub((char *)&vector, (char *)&vector, (char *)&temp);
        vec_scale_to_length((char *)&temp, axis, func_002A7878_1(0.0f, 1.0f));
        FastVecAdd((char *)&vector, (char *)&vector, (char *)&temp);
        vec_scale_to_length((char *)&vector, (char *)&vector, scale * func_002A7878_1(6.5f, 10.0f) * (1.0f/60.0f));
        FastVecAdd((char *)&vector, (char *)&vector, direction);
        life1 = math_random_int_range(60,90);
        part_spawn_spinning_debris(object+0x10, (char *)&vector, life1, 1, V1306_FLAG);
    }
    random.q = 0;
    random.f[0] = func_002A7878_1(-1.0f, 1.0f);
    random.f[1] = func_002A7878_1(-1.0f, 1.0f);
    random.f[2] = func_002A7878_1(-1.0f, 1.0f);
    vector.q = random.q;
    delta.f[2] += length * 0.5f;
    vec_scale_to_length((char *)&vector, (char *)&vector, length * 0.0033333336468786f);
    vec_scale_to_length((char *)&delta, (char *)&delta, twice * (1.0f/60.0f));
    FastVecAdd((char *)&vector, (char *)&vector, (char *)&delta);
    vec_fast_divide_helper((char *)&vector, (char *)&vector, 1.0f/6.0f);
    life1 = math_random_int_range(60,90);
    part_spawn_spinning_debris(object+0x10, (char *)&vector, life1, 1, V1306_FLAG);
    if (length < 6.0f) i = FloatToInt(length) + 1;
    else i = 4;
    twice = 0.0f;
    if (length < 7.0f) twice = 7.0f - length;
    for (n = 0; n < i; n++) {
        float step = 1.0f/60.0f;
        float limit = 400000.0f;
        force = scale;
        speed = scale * func_002A7878_1(8.0f, 10.0f);
        force *= limit;
        first = D_L00_001AEFE0;
        second = D_L00_001AEFF8;
        speed *= step;
        speed -= twice * step;
        asset1 = gfx_swap_packed_color_channels(first.entry[math_random_int_below(6)], V1306_FLAG);
        asset2 = gfx_swap_packed_color_channels(second.entry[math_random_int_below(6)], V1306_FLAG);
        life1 = math_random_int_range(15,20);
        life2 = math_random_int_range(25,30);
        part_spawn_firework_spark(object+0x10, direction, asset1, asset2, force, life1, life2, speed, 0, 0);
    }
    if (length > 9.0f) {
        float size = scale * 4.0f;
        part_create_explosion(object,object+0x10,direction,15,127,127,127,32,size);
        red=127; green=32; blue=0;
        swap_color_channel_words(&red,&green,&blue,V1306_FLAG);
        part_create_explosion(object,object+0x10,direction,24,(unsigned char)red,(unsigned char)green,(unsigned char)blue,32,size);
    }
    red2=127; green2=63; blue2=0;
    swap_color_channel_words(&red2,&green2,&blue2,V1306_FLAG);
    part_create_explosion(object,object+0x10,direction,20,(unsigned char)red2,(unsigned char)green2,(unsigned char)blue2,48,scale*4.0f);
    red2=96; green2=16; blue2=0;
    swap_color_channel_words(&red2,&green2,&blue2,V1306_FLAG);
    part_create_explosion(object,object+0x10,direction,27,(unsigned char)red2,(unsigned char)green2,(unsigned char)blue2,64,scale*3.5f);
    red2=32; green2=0; blue2=0;
    swap_color_channel_words(&red2,&green2,&blue2,V1306_FLAG);
    part_create_explosion(object,object+0x10,direction,29,(unsigned char)red2,(unsigned char)green2,(unsigned char)blue2,32,scale*3.0f);
    *child = 0;
    object[0xBC] = 0;
    if (V1306_FLAG) PlayMobySound(0,0,object);
    else PlayMobySound(0,0,object);
    { V1439Camera *camera = &D_L00_001B8C80;
    if (length < 20.0f) camera->amount = 0.4f - length * 0.0175f;
    else camera->amount = 0.050000011920928955f;
    }
    D_L00_001B8C80.duration=25;
    D_L00_001B8C80.state=0;
    moby_spawn_template_effect(&packet,object+0x10,0,0);
}

/* func_L00_0038E880 is defined in L00_0038E880-g8.c. */
