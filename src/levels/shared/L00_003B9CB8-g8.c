#include "common.h"
#include "include_asm.h"

extern int D_L00_001AFDA0 __attribute__((sda));

/* Reads the small counter in the shared data area and reports whether it equals two. */
int effect_is_count_two(void)
{
    return D_L00_001AFDA0 == 2;
}

extern char D_L00_0023DDA0[] __attribute__((nosda));

extern char D_L00_0023F060[] __attribute__((nosda));

/* Clears one word of each of the thirty 0xA0-byte records that start at D_L00_0023DDA0,
   then one word of each of the sixteen 0xB0-byte records at D_L00_0023F060, walking down
   from the last record of each table, and finally the shared flag word. */
void effect_clear_slot_tables(void)
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
void trail_effect_clear_pointer(void)
{
    D_L00_001AFF98 = 0;
}

extern char g_hero_moby[];

extern float fade_get_value(void);

extern int weapon_can_use_held(float f12);

extern void moby_transform_joint_to_world(char *a, int b, char *c);

extern void electric_ribbons_update(char *p);

extern void gfx_draw_glow_sphere(char *p);

extern void effect_draw_trails(char *p);

/* Gate followed by a fixed sequence of four bound helpers on the state record at offset 0x68. */
/* Each frame, if the level allows it, draws this effect: sets up its sound, then runs its three drawing steps. */
void trail_effect_update_draw(char *moby)
{
    char *vars;

    if (D_L04_001A8F00 != 0)
        return;
    vars = *(char **)(moby + 0x68);
    if (weapon_can_use_held(fade_get_value()) == 0)
        return;
    if (D_L00_001AFF44 == 0x28)
        return;
    moby_transform_joint_to_world(*(char **)g_hero_moby, 0xA, vars + 0x30);
    electric_ribbons_update(moby);
    gfx_draw_glow_sphere(moby);
    effect_draw_trails(moby);
}


extern char g_item_slot_to_record[];

typedef struct {
    char prefix[0x760];
    float vector[4];
    char pad770[0xBF8 - 0x770];
    int mode;
    char padBFC[0x24EC - 0xBFC];
    short state;
} Player37;
extern Player37 D_00189E20_13;

extern char g_weapon_l00_table[];

/* A float in the boot's small data: the sda attribute and this unit's -G8 make the
   reference to it $gp-relative, the way retail has it. */
extern float D_001AFF08 __attribute__((sda));

extern void vec_scale_to_length(void *a0, void *a1, float f);

extern void part_l00_spawn_spark_shower(char *a0, char *a1, void *a2);

extern void vec_compute_object_to_target(int a0, char *a1, void *a2, float f);

extern float FastVecLength(void *a0);

extern void *SpawnProjectile(char *a0, void *a1, char *a2, int a3, float f12, float f13, float f14);

/* Scales a direction by the current class record's speed (per frame at 60 Hz), negated from the
   object's own vector in player state 1, re-reads the record's second value, applies the
   optional mode adjustment, then spawns through func_L00_003A98E8 and links the result back to
   the object. The two record lookups use separate locals: one reused pointer becomes a global
   pseudo and loses the first lookup's tie to the multiply's register. */
/* Fires a shot from the moby toward the target, using the speed of the current weapon class,
   and ties the new shot back to the moby that fired it. */
void moby_fire_shot(char *moby, char *shot)
{
    char velocity[16];
    char *vars = *(char **)(moby + 0x68);
    char *class_record;
    char *class_record2;
    float speed;
    float second_value;
    float value;
    float extra;
    int mode;
    void *new_moby;

    class_record = g_weapon_l00_table + (unsigned char)g_item_slot_to_record[0x19] * 0xE0;
    value = *(float *)(class_record + 0x50);
    speed = value * 0.016666667f;
    mode = D_00189E20_13.state;
    if (mode == 1)
        vec_scale_to_length(velocity, moby + 0xD0, -speed);
    else
        vec_scale_to_length(velocity, D_00189E20_13.vector, speed);

    class_record2 = g_weapon_l00_table + (unsigned char)g_item_slot_to_record[0x19] * 0xE0;
    second_value = *(float *)(class_record2 + 0x70);
    part_l00_spawn_spark_shower(moby, shot, velocity);

    mode = D_00189E20_13.mode;
    if (mode != 0)
        vec_compute_object_to_target(mode, shot, velocity, speed);

    value = FastVecLength(velocity);
    extra = D_001AFF08;
    new_moby = SpawnProjectile(shot, velocity, moby, 0, value, second_value, extra);
    *(int *)vars = (int)new_moby;
    if (new_moby != 0) {
        *(int *)((char *)new_moby + 0xB8) = (int)moby;
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
extern void FastVecAdd(void *, void *, void *);
/* The second integer-bank input is forwarded as the axis vector pointer. */
extern void math_build_axis_angle_quat(void *, void *, float);
extern void vec_rotate_by_quaternion(void *, void *, void *);
extern void vec_add_random_offset(float *, float);
extern float FastVecLength(void *);
extern void FastVecScale(void *, void *, float);
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
extern UiTrailParticle *part_spawn_bluish_fade(void *, int, int, int);
extern void ref_L00_003C4F78_00(void *, int, int, int, int, int, int, int,
                              int, int, int, float, float, float);

/* Ages the four trail histories (20 points each), turns and clamps each head point, builds the
   vertex strip around the owner's origin and spawns two particles at the tip. The point address
   is formed in its own group so the copy source keeps its own D - 16 base. */
/* Draws four glowing trails behind the effect. Each trail remembers its last 20 points and
   spawns two small particles at its tip. */
void effect_draw_trails(char *owner)
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
        math_build_axis_angle_quat(&change, &D_L00_001B2900[i], 0.10471976548433304f);
        vec_rotate_by_quaternion(head, head, &change);
        vec_add_random_offset(head->f, 0.025f);
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
        effect = part_spawn_bluish_fade(tip, 2, 0, 1);
        if (effect != 0) {
            char *tables = D_L00_001FE940;
            effect->color = D_L00_001AFF50 | state->flags;
            effect->size = D_L00_001AFF5C * 210000.0f;
            effect->texture = (*(char **)(tables + 0xF8))[1];
        }
        effect = part_spawn_bluish_fade(tip, 2, 0, 1);
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
