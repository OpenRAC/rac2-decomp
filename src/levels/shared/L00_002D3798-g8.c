#include "common.h"

/* func_L00_002D5940 is here rather than in L00_002D3798.c because its tuning floats are read
   through $gp (-G8). */

typedef int Quad5940 __attribute__((mode(TI)));

typedef struct {
    float bounds[4];            /* 0x00; [3] is the radius */
    float position[4];          /* 0x10 */
    unsigned char state;        /* 0x20 */
    char pad21[0x10];
    unsigned char drawn;        /* 0x31 */
    char pad32[0x2];
    unsigned short modeBits;    /* 0x34 */
    char pad36[0x2E];
    void (*update)(void *);     /* 0x64 */
    char pad68[0x42];
    short oClass;               /* 0xAA */
    char padAC[0x14];
    float rotMatrix[3][4];      /* 0xC0 */
    float rotation[4];          /* 0xF0 */
} Moby5940;

typedef struct {
    char pad0000[0x80];
    float position[4];          /* 0x0080 */
    char pad0090[0xC0];
    float velocity[4];          /* 0x0150 */
    char pad0160[0x14];
    float speed;                /* 0x0174 */
    char pad0178[0x1C8];
    int f340;                   /* 0x0340 */
    char pad0344[0x3EC];
    float transform[12];        /* 0x0730 */
    Quad5940 vector760;         /* 0x0760 */
    Quad5940 vector770;         /* 0x0770 */
    char pad0780[0xAA0];
    Moby5940 *object;           /* 0x1220 */
    char pad1224[0xC];
    int flags;                  /* 0x1230 */
    char pad1234[0x8];
    unsigned char visible;      /* 0x123C */
    char pad123D[0xB];
    int weapon;                 /* 0x1248 */
    char pad124C[0x254];
    float transitionPos[4];     /* 0x14A0 */
    float transitionRot[4];     /* 0x14B0 */
    float rotation[4];          /* 0x14C0 */
    char pad14D0[0x28];
    float blend;                /* 0x14F8 */
    float blendVelocity;        /* 0x14FC */
    char pad1500[0x4];
    float offsetVelocity;       /* 0x1504 */
    float offset;               /* 0x1508 */
    float offsetTarget;         /* 0x150C */
    float angle;                /* 0x1510 */
    float angleVelocity;        /* 0x1514 */
    char pad1518[0xD78];
    int owner;                  /* 0x2290 */
} Hero5940;

extern Hero5940 g_hero_state;
extern char D_L00_001B8FF0[], g_camera_l00_position[], D_L00_001BF220[];
extern Quad5940 D_L00_001B8DD0;
/* Incomplete sda arrays are read with the assembler's lui/load macro, as in retail. */
extern unsigned char D_001A7A44[] __attribute__((sda));
extern int g_frame_l00_counter[] __attribute__((sda));
extern float D_L00_001A7FE4[] __attribute__((sda));
extern const float D_L00_001A7FE0 __attribute__((sda));
extern float D_L00_001A7CE0 __attribute__((sda)), D_L00_001A7CE4 __attribute__((sda));

extern int hero_is_slot_item_wrench(int);
extern void func_002A0F48(void *);
extern char *level_get_table_entry_address(int);
extern int hero_is_action_allowed(void);
extern void copy_matrix_rotation(void *, void *);
extern void ApproachValue(float *, float, float);
extern float math_step_value_toward_target(float *, float *, float, float, float, float);
extern float FastAddRotations(float, float), math_fast_sin_or_cos_b(float);
extern void transform_vector(void *, void *, void *), FastVecAdd(void *, void *, void *);
extern void euler_to_matrix(void *, void *), multiply_matrix3x3(void *, void *, void *);
extern void mat_get_euler_angles(void *, void *), mat_build_rotation_from_angles(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *), lerp_vector(void *, void *, void *, float);
extern void vec_fast_normalize3(void *, void *, void *, float), quaternion_to_rotation_basis(void *, void *);
extern void FastVecScale(void *, void *, float), vec_scale_to_length(void *, void *, float);
extern int CollLine(void *, void *, int, int, int);
extern float fast_vec_dist(void *, void *);
extern void copy_matrix3x4(void *, void *);

/* Places the hero's held object (D_00189E20.object): from the weapon's mount offset and
   rotation, a turning bob angle, the blend from the transition pose while blend < 1, and a
   ground probe that limits the vertical offset to [-1.5, 0]. */
void UpdateHeroHeldObject(void) {
    Moby5940 *obj = g_hero_state.object;
    char *mount;
    float m[16], rot[16], offset[4], temp[4], a[4], b[4];
    float turn, height, scale, target;
    int state;

    if (!obj)
        return;
    if (obj->oClass == 0x47 /* moby class 71 */) {
        if (!g_hero_state.visible && !obj->state) {
            obj->drawn = 0;
            obj->modeBits |= 1;
        } else {
            obj->drawn = 1;
            obj->modeBits &= ~1;
        }
        return;
    }
    if (hero_is_slot_item_wrench(0)) {
        obj->modeBits |= 1;
        obj->drawn = 0;
        if (obj->update)
            obj->update(obj);
        func_002A0F48(obj);
        return;
    }

    mount = level_get_table_entry_address(g_hero_state.weapon);
    copy_matrix_rotation(m, D_L00_001B8FF0);
    qcopy_nc(&m[12], D_L00_001B8FF0 - 0x230);
    m[15] = 1.0f;
    qcopy_nc(offset, mount);
    offset[0] += g_hero_state.offset;
    if (D_001A7A44[0] && !hero_is_action_allowed())
        offset[1] = -offset[1];

    /* Turn rate in degrees per second (FE4 while moving, FE0 otherwise) to radians per frame. */
    if (g_hero_state.speed > 0.02f)
        turn = D_L00_001A7FE4[0] * 0.0002908882452175021f;
    else
        turn = D_L00_001A7FE0 * 0.0002908882452175021f;
    ApproachValue(&g_hero_state.angleVelocity, turn, 0.006981317885220051f);
    g_hero_state.angle = FastAddRotations(g_hero_state.angle, g_hero_state.angleVelocity);
    offset[2] += math_fast_sin_or_cos_b(g_hero_state.angle) * 0.02f;

    transform_vector(obj->position, offset, m);
    if (!hero_is_action_allowed())
        FastVecAdd(obj->position, obj->position, g_hero_state.velocity);
    euler_to_matrix(rot, mount + 0x10);
    multiply_matrix3x3(obj->rotMatrix, m, rot);
    mat_get_euler_angles(obj->rotMatrix, obj->rotation);
    mat_build_rotation_from_angles(g_hero_state.rotation, obj->rotation);

    if (g_hero_state.blend < 1.0f) {
        math_step_value_toward_target(&g_hero_state.blend, &g_hero_state.blendVelocity, 1.0f,
                      D_L00_001A7CE0 * 0.016666667f, D_L00_001A7CE4 * 0.00027777778f,
                      D_L00_001A7CE0 * 0.016666667f);
        matrix_mul_vec3(temp, g_hero_state.transitionPos, &g_hero_state);
        FastVecAdd(temp, temp, g_hero_state.position);
        lerp_vector(obj->position, temp, obj->position, g_hero_state.blend);
        mat_build_rotation_from_angles(a, obj->rotation);
        vec_fast_normalize3(b, g_hero_state.transitionRot, a, g_hero_state.blend);
        quaternion_to_rotation_basis(b, obj->rotMatrix);
    }

    obj->drawn = 1;
    obj->modeBits &= ~1;
    func_002A0F48(obj);

    if ((g_frame_l00_counter[0] ^ 1) & 1) {
        scale = 0.0009765625f;
        height = obj->bounds[3] * scale;
        FastVecScale(temp, obj->bounds, scale);
        vec_scale_to_length(a, obj->rotMatrix[1], height * -1.2f);
        FastVecAdd(a, a, temp);
        if (CollLine(g_camera_l00_position, a, 0, g_hero_state.owner, 0)) {
            target = (g_hero_state.offset - height) + fast_vec_dist(D_L00_001BF220, temp);
            g_hero_state.offsetTarget = target;
            if (target > 0.0f)
                g_hero_state.offsetTarget = 0.0f;
            else if (target < -1.5f)
                g_hero_state.offsetTarget = -1.5f;
        } else {
            g_hero_state.offsetTarget = 0;
        }
    }

    math_step_value_toward_target(&g_hero_state.offset, &g_hero_state.offsetVelocity, g_hero_state.offsetTarget,
                  0.0041666669f, 0.0041666669f, 0.083333336f);
    copy_matrix3x4(g_hero_state.transform, m);
    qcopy_nc(&g_hero_state.vector760, m);
    qcopy_nc(&g_hero_state.vector770, &D_L00_001B8DD0);

    state = hero_is_action_allowed();
    if (state)
        g_hero_state.flags |= 5;
    if (obj->update)
        obj->update(obj);
    if (state)
        g_hero_state.flags &= ~5;
}

/* func_L00_002D5EB8 */
extern int D_0018C350[];
extern unsigned char D_001A7A00[] __attribute__((sda));
extern int D_0018C2EC[];
extern unsigned char D_001A7A28[] MACRO_ADDR;
extern unsigned char g_item_slot_to_record[];
extern int D_L00_001A903C;
extern unsigned short g_subtitle_history __attribute__((section(".data")));
extern int D_00139868[];
extern int D_001A7398[] MACRO_ADDR;
extern unsigned char g_item_owned_flags[] MACRO_ADDR;

/* One 0xE0-byte entry of D_L00_00262570, indexed through D_00139568. */
typedef struct {
    int exists;                 /* 0x00 */
    unsigned char state;        /* 0x04 */
    char pad05[0x7];
    int index;                  /* 0x0C */
    char pad10[0x3A];
    short value;                /* 0x4A */
    char pad4C[0x20];
    int limit;                  /* 0x6C */
    char pad70[0x70];
} Entry1269;

extern Entry1269 g_weapon_l00_table[];
extern int math_sum_table_entries_under_limit(int *, int *, int *);
extern void hud_queue_hint_message(int, int);
extern void effect_controller_spawn(void);
extern void module_l00_call_handler_with_arg_4(int);
extern void value_set_entry_by_index(int, int);
extern int snd_play_from_global_bank(int, int, void *);
extern int flag_is_byte_set(void);
extern int menu_count_chain_entries_after_head(int);
extern void gfx_set_screen_pair_run_effect(int, int);
extern void menu_advance_chain_entry(int);
extern void help_show_message_for_id(int);
extern int ref_L00_002D5EB8_00 __attribute__((sda));

static inline int special(int i)
{
    int r = 0;

    switch (i) {
    case 12:
    case 14:
    case 17:
    case 18:
    case 53:
        r = 1;
        break;
    }
    return r;
}

static inline int unlocked(Entry1269 *e, int i)
{
    if (e->state >= 2 || (e->state == 1 && special(i)))
        return 1;
    return 0;
}

static inline int owned(int i)
{
    if (g_weapon_l00_table[g_item_slot_to_record[i]].exists) {
        int n = menu_count_chain_entries_after_head(i);
        if (n >= 2 || (n == 1 && special(i)))
            return 1;
    }
    return 0;
}

/* Checks the player's weapons and gadgets each frame: updates the item count, plays the unlock effects, and gives the final reward once everything is collected. */
void hero_update_collection_progress(void)
{
    int count, i, j, ok;

    if ((g_frame_l00_counter[0] & 15) == 1 && g_frame_l00_counter[0] != 1)
        return;
    count = 4;
    {
        int *p = D_0018C350;
        math_sum_table_entries_under_limit(p, p - 1, &count);
    }
    for (j = 0; j < 10; j++)
        if (D_001A7A28[j])
            count++;
    if (*(int *)D_001A7A00 != count) {
        if (ref_L00_002D5EB8_00 >= 11 && *(int *)D_001A7A00 < count) {
            if (!g_subtitle_history)
                hud_queue_hint_message(0x9A9, 0);
            effect_controller_spawn();
            module_l00_call_handler_with_arg_4(0x168);
            value_set_entry_by_index(0x1235, -1);
            snd_play_from_global_bank(6, 0, 0);
        }
        D_0018C2EC[0] = count;
        *(int *)D_001A7A00 = count;
    }

    for (i = 0; i < 56; i++) {
        if ((g_weapon_l00_table + g_item_slot_to_record[i])->state) {
            if (!flag_is_byte_set())
                continue;
            if (menu_count_chain_entries_after_head(i) == 1)
                continue;
        }
        {
            Entry1269 *e = &g_weapon_l00_table[g_item_slot_to_record[i]];
            int sel = 0;
            if (e->exists)
                sel = e->state == 3;
            if (sel)
                continue;
        }
        if (menu_count_chain_entries_after_head(i) <= 0)
            continue;
        {
            Entry1269 *e = &g_weapon_l00_table[g_item_slot_to_record[i]];
            if ((D_00139868[i] >> 5) < e->limit || e->limit <= 0)
                continue;
            if (i == 31 || i == 9 || i == 45) {
                gfx_set_screen_pair_run_effect(i, g_weapon_l00_table[g_item_slot_to_record[i]].value);
                continue;
            }
            if (g_hero_state.weapon == i) {
                if (!g_hero_state.f340)
                    continue;
                if (D_001A7398[e->index] != i)
                    continue;
                gfx_set_screen_pair_run_effect(i, e->value);
                continue;
            }
        }
        if (flag_is_byte_set()) {
            Entry1269 *e = &g_weapon_l00_table[g_item_slot_to_record[i]];
            if (!e->exists)
                continue;
            if (unlocked(e, i)) {
                if (owned(i)) {
                    menu_advance_chain_entry(i);
                    help_show_message_for_id(i);
                }
            }
        } else {
            menu_advance_chain_entry(i);
            help_show_message_for_id(i);
        }
    }

    if ((g_frame_l00_counter[0] & 127) || D_001A7A00[0x7A])
        return;
    ok = 1;
    for (i = 0; i < 56; i++) {
        int ex = g_weapon_l00_table[g_item_slot_to_record[i]].exists;
        if (ex && i == 10)
            continue;
        if (ex && i == 9)
            continue;
        if (ex) {
            if (!g_item_owned_flags[i]) {
                ok = 0;
                break;
            }
            if (i == 14 || i == 12 || i == 17 || i == 18 || i == 53)
                continue;
            if (menu_count_chain_entries_after_head(i) <= 0)
                continue;
            if (!g_weapon_l00_table[g_item_slot_to_record[i]].state) {
                ok = 0;
                break;
            }
        }
    }
    if (ok && !D_001A7A00[0x7A]) {
        D_001A7A00[0x7A] = 1;
        snd_play_from_global_bank(1, 0, 0);
        value_set_entry_by_index(0x1233, -1);
        D_L00_001A903C = 1;
    }
}
