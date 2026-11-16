#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern float g_vendor_logo_spin_speed __attribute__((sda));

extern float FastAddRotations(float, float);

extern void build_axis_rotation_quaternion(char *, int, float);

extern void AttachManipulator(char *, int, char *);

extern float math_random_angle(void);

/* grows a moby out of the ground the first time, then spins it down */
/* Updates the Megacorp Vendor Logo: it spins and turns its inner part the opposite way. */
void megacorp_vendor_logo_update(char *moby)
{
    char *moby_vars = *(char **)(moby + 0x68);

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(unsigned char *)(moby + 0x20) = 1;
        *(unsigned char *)(moby + 0x63) = 0x20;
        *(float *)(moby_vars + 0x40) = math_random_angle();
        AttachManipulator(moby, 1, moby_vars);
        break;
    case 1: {
        float spin_step = g_vendor_logo_spin_speed * 0.000290888245f;

        *(float *)(moby + 0xF8) = FastAddRotations(*(float *)(moby + 0xF8), spin_step);
        *(float *)(moby_vars + 0x40) = FastAddRotations(*(float *)(moby_vars + 0x40), spin_step * -2.0f);
        build_axis_rotation_quaternion(moby_vars + 0x10, 2, *(float *)(moby_vars + 0x40));
        break;
    }
    }
}

/* spins the moby's wheels down and leans them, then steps the frame counter */

extern float g_collectible_height_scale __attribute__((sda));

extern float g_bob_base_height __attribute__((sda));

extern float g_bob_l01_amplitude __attribute__((sda));

extern float g_bolt_bob_spin_speed __attribute__((sda));

extern int g_sparkle_chance __attribute__((sda));

extern float func_002E3A60(float);


extern int func_003104E8(int);

extern void part_draw_bolt_glow_rings(char *);



extern void euler_rotation_basis(void *, void *);

extern void vec_scale_to_length(void *, void *, float);

extern void func_002A0F48(void *);

/* turns each of the three carried objects with a swinging pitch */
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec4;

struct Carrier_00398938;

typedef struct {
    char pad0[0x10];
    Vec4 pos;
    char pad20[0x48];
    struct Carrier_00398938 *vars;
    char pad6C[0x54];
    Vec4 mtx;
    char padD0[0x20];
    Vec4 rot;
} Moby_00398938;

typedef struct Carrier_00398938 {
    char pad0[0x14];
    Moby_00398938 *list[3];
    float swing;
    float t;
} Carrier_00398938;

extern void FastVecAdd(void *, void *, void *);

/* The level's per-frame lift and heading: they sit at another address in every level. */
extern float ref_L01_00398938_00 __attribute__((sda));

extern float ref_L01_00398938_01 __attribute__((sda));

/* Places each of the three carried child objects at the moby's position and tilts them with a swing. */
void moby_position_carried_objects(Moby_00398938 *moby)
{
    Carrier_00398938 *moby_vars = moby->vars;
    Moby_00398938 **list = moby_vars->list;
    Vec4 *src = &moby->pos;
    Vec4 v;
    float pitch;
    int i;

    for (i = 0; i < 3; i++) {
        if (list[i] != 0) {
            Vec4 *rot;

            qcopy_nc(&list[i]->pos, src);
            list[i]->pos.z = list[i]->pos.z + ref_L01_00398938_00;
            rot = &list[i]->rot;
            rot->y = ref_L01_00398938_01 * 0.017453294f;
            pitch = moby_vars->swing * 2.4f - 1.2f;
            euler_rotation_basis(&list[i]->mtx, &list[i]->rot);
            vec_scale_to_length(&v, &list[i]->mtx, pitch);
            FastVecAdd(&list[i]->pos, &list[i]->pos, &v);
            rot = &list[i]->rot;
            rot->y = moby_vars->t * -1.0471977f - 0.3490659f;
            euler_rotation_basis(&list[i]->mtx, &list[i]->rot);
            func_002A0F48(list[i]);
        }
    }
}

extern float g_sparkle_drift_a_min __attribute__((sda));

extern float g_sparkle_drift_a_max __attribute__((sda));

extern float g_sparkle_drift_b_min __attribute__((sda));

extern float g_sparkle_drift_b_max __attribute__((sda));

extern unsigned char g_sparkle_l01_alpha_2 __attribute__((sda));

extern int g_sparkle_particle_type_a __attribute__((sda));

extern int g_sparkle_particle_type_b __attribute__((sda));

extern float g_sparkle_scale_a __attribute__((sda));

extern float g_sparkle_scale_b __attribute__((sda));


extern void FastVecScale(void *, void *, float);

extern void moby_transform_joint_to_world(void *, int, void *);

extern void vec_random_direction(void *, float, float);

extern int math_random_int_below(int);

extern void *part_spawn_hero_relative(void *, void *, int, unsigned char, unsigned char, int, float);

extern void FastVecAdd(void *, void *, void *);

/* builds the tilt of a hanging chain over three steps and draws it */
/* Spawns three small sparkles at the moby, each with a random drift. */
void part_spawn_sparkle_drift(char *moby)
{
    TI128 spark_pos, drift_a, drift_b;
    int i;
    int alpha;

    if (*(unsigned char *)(moby + 0x20) == 1) {
        FastVecScale(&spark_pos, moby, 0.0009765625f);
    } else {
        moby_transform_joint_to_world(moby, 0, &spark_pos);
    }
    i = 2;
    vec_random_direction(&drift_a, g_sparkle_drift_a_min * 0.016666668f, g_sparkle_drift_a_max * 0.016666668f);
    alpha = g_sparkle_l01_alpha_2;
    part_spawn_hero_relative(&spark_pos, &drift_a, g_sparkle_particle_type_a, alpha, math_random_int_below(255), 0, g_sparkle_scale_a);
    do {
        i--;
        vec_random_direction(&drift_b, g_sparkle_drift_b_min * 0.016666668f, g_sparkle_drift_b_max * 0.016666668f);
        FastVecAdd(&drift_a, &drift_a, &drift_b);
        alpha = g_sparkle_l01_alpha_2;
        part_spawn_hero_relative(&spark_pos, &drift_a, g_sparkle_particle_type_b, alpha, math_random_int_below(255), 0, g_sparkle_scale_b);
    } while (i >= 0);
}

/* Same body as func_L01_00417090, with this function's own callees. */
extern float g_ground_height __attribute__((nosda));

extern float ref_L01_00397EB0_00 __attribute__((sda));
extern float ref_L01_00397EB0_01 __attribute__((sda));
extern unsigned char ref_L01_00397EB0_02 __attribute__((sda));
extern int ref_L01_00397EB0_03 __attribute__((sda));
extern float ref_L01_00397EB0_04 __attribute__((sda));
extern float ref_L01_00397EB0_05 __attribute__((sda));
extern float ref_L01_00397EB0_06 __attribute__((sda));
extern int ref_L01_00397EB0_07 __attribute__((sda));
extern float ref_L01_00397EB0_08 __attribute__((sda));
/* Spawns three small sparkles at the moby unless it is below the ground height. */
void part_spawn_sparkle_trail_above_ground(char *moby)
{
    TI128 spark_pos, drift_a, drift_b;
    int i;
    int alpha;

    if (*(unsigned char *)(moby + 0x20) == 1) {
        FastVecScale(&spark_pos, moby, 0.0009765625f);
    } else {
        moby_transform_joint_to_world(moby, 0, &spark_pos);
        if (((float *)&spark_pos)[2] < g_ground_height) return;
    }
    i = 2;
    vec_random_direction(&drift_a, ref_L01_00397EB0_00 * 0.016666668f, ref_L01_00397EB0_01 * 0.016666668f);
    alpha = ref_L01_00397EB0_02;
    part_spawn_hero_relative(&spark_pos, &drift_a, ref_L01_00397EB0_03, alpha, math_random_int_below(255), 0, ref_L01_00397EB0_04);
    do {
        i--;
        vec_random_direction(&drift_b, ref_L01_00397EB0_05 * 0.016666668f, ref_L01_00397EB0_06 * 0.016666668f);
        FastVecAdd(&drift_a, &drift_a, &drift_b);
        alpha = ref_L01_00397EB0_02;
        part_spawn_hero_relative(&spark_pos, &drift_a, ref_L01_00397EB0_07, alpha, math_random_int_below(255), 0, ref_L01_00397EB0_08);
    } while (i >= 0);
}


extern float g_wind_min_count __attribute__((sda));

extern float g_wind_max_count __attribute__((sda));

extern float g_wind_x __attribute__((sda));

extern float g_wind_change_delay __attribute__((sda));

extern float g_level_float_param_2 __attribute__((nosda));

extern int g_level_int_param __attribute__((nosda));

extern float func_00310580(float, float);

extern float func_002E35D0(char *);

extern float func_002E35A0(float *);


extern char *ref_L01_003E9CF8_00 MACRO_ADDR;

extern int ref_L01_003E9CF8_01 MACRO_ADDR;


extern char *CreateMoby(int);

extern void get_moby_color(char *, int *, int *, int *);

/* makes sure a live moby of class 0xC41 exists, then queues this moby in one of its 0x40 slots
   with its colour and a callback; with the queue full it runs the callback or deletes the moby */
typedef struct {
    char *obj;
    int rgb;
    int arg;
    float scale;
    void (*cb)(char *);
    int pad[3];
} Ent_3E9CF8;
extern Ent_3E9CF8 ref_L01_003E9CF8_02[];
extern void moby_mark_spawned(void *);
/* Queues a moby for the glow effect manager, creating the manager if needed. If the queue is full it runs the callback or deletes the moby. */
void part_queue_moby_for_glow(char *moby, int extra, void (*callback)(char *))
{
    char *manager = ref_L01_003E9CF8_00;
    int red;
    int green;
    int blue;
    int count;
    if (manager == 0 || *(short *)(manager + 0xAA) != 0xC41 /* moby class 3137 */ ||
        *(unsigned char *)(manager + 0x20) == 0xFE || *(unsigned char *)(manager + 0x20) == 0xFD) {
        char *new_manager = CreateMoby(0xC41 /* moby class 3137 */);
        ref_L01_003E9CF8_00 = new_manager;
        *(unsigned char *)(new_manager + 0x30) = 0xFF;
    }
    count = ref_L01_003E9CF8_01;
    *(unsigned short *)(moby + 0x34) |= 2;
    *(int *)(moby + 0x48) = 0;
    *(int *)(moby + 0x44) = 0;
    if (count < 0x40) {
        int slot_index;
        get_moby_color(moby, &red, &green, &blue);
        slot_index = ref_L01_003E9CF8_01;
        ref_L01_003E9CF8_02[slot_index].obj = moby;
        ref_L01_003E9CF8_02[slot_index].rgb = (blue << 16) | (green << 8) | red;
        ref_L01_003E9CF8_02[slot_index].arg = extra;
        ref_L01_003E9CF8_02[slot_index].scale = 1.0f;
        ref_L01_003E9CF8_02[slot_index].cb = callback;
        ref_L01_003E9CF8_01 = slot_index + 1;
    } else if (callback != 0) {
        callback(moby);
    } else {
        moby_mark_spawned(moby);
    }
}


extern void moby_release_and_reset_impact_slot(char *);

extern void anim_start_blended(char *, int, int, int);

extern void anim_start_immediate(char *, int, int);

extern int math_fast_float_d(char *);

extern const int g_flashing_ring_color_a __attribute__((sda));

extern const int g_flashing_ring_color_b __attribute__((sda));

/* brings the ring out of the ground, then lets it spin and hand itself over */
/* Updates a ring moby: it lifts out of the ground, flashes between two colors while active, then resets. */
void flashing_ring_update(char *moby)
{
    char *moby_vars;

    moby_vars = *(char **)(moby + 0x68);
    moby_release_and_reset_impact_slot(moby);

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        *(float *)(moby + 0x18) = *(float *)(moby + 0x18) + 1.0f;
        *(float *)(moby_vars + 0x14) = *(float *)(moby + 0xF0);
        *(unsigned char *)(moby + 0x20) = 1;
        if (*(unsigned char *)(moby + 0x43) != 0)
            anim_start_blended(moby, 0, 0, 0xC);
        *(int *)(moby_vars + 0x50) = 0;
        *(unsigned short *)(moby + 0x34) |= 0x1000;
        break;
    case 1:
        if ((*(unsigned char *)(moby + 0x60) & 2) != 0) {
            if (*(unsigned char *)(moby + 0x43) != 0)
                anim_start_immediate(moby, 0, 0);
        }
        if (*(unsigned char *)(moby + 0xBC) == 0)
            break;
        *(unsigned short *)(moby + 0x34) &= 0xEFFF;
        anim_start_immediate(moby, 1, 0);
        if (*(int *)(moby_vars + 0x0) != 0) {
            *(int *)(moby_vars + 0x10) = 10;
            *(unsigned char *)(moby + 0x20) = 2;
            *(int *)(moby_vars + 0xC) = *(int *)(moby_vars + 0x4);
        } else {
            *(unsigned char *)(moby + 0x20) = 2;
            *(int *)(moby + 0x78) = g_flashing_ring_color_b;
            *(int *)(moby_vars + 0xC) = 0;
        }
        break;
    case 2:
        if (*(int *)(moby_vars + 0x0) != 0) {
            if (math_fast_float_d(moby_vars + 0x10) != 0) {
                if (*(int *)(moby + 0x78) == g_flashing_ring_color_a)
                    *(int *)(moby + 0x78) = g_flashing_ring_color_b;
                else
                    *(int *)(moby + 0x78) = g_flashing_ring_color_a;
                *(int *)(moby_vars + 0x10) = 10;
            }
            if (math_fast_float_d(moby_vars + 0xC) != 0)
                *(unsigned char *)(moby + 0xBC) = 0;
        }
        if ((*(unsigned char *)(moby + 0x60) & 2) != 0) {
            if (*(unsigned char *)(moby + 0x43) == 1)
                anim_start_immediate(moby, 2, 0);
        }
        if (*(unsigned char *)(moby + 0xBC) != 0)
            break;
        if ((*(unsigned char *)(moby + 0x60) & 2) != 0) {
            *(unsigned short *)(moby + 0x34) |= 0x1000;
            anim_start_immediate(moby, 3, 0);
            *(unsigned char *)(moby + 0x20) = 1;
            *(int *)(moby + 0x78) = g_flashing_ring_color_a;
        }
        break;
    }
}

extern float FastAddRotations(float, float);
extern void FastVecAdd(void *, void *, void *);
extern char g_hero_state[];



extern void moby_transform_joint_to_world(void *, int, void *);
extern int math_fast_float_d(char *);
extern char g_hero_state[];
extern void CalculateAimedLaunchVelocity(void *, void *, int, int, float, float, float, float);
extern int coll_trace_projectile_to_impact(void *, void *, void *, void *, void *, char **, int *, float);
extern int weapon_get_group(int);
extern void moby_get_facing_direction(void *, void *);
extern float FastVecDot(void *, void *);
extern int weapon_spend_ammo(int, int);
extern int ForceClaimNotice(int, int, int);
extern void start_equipped_item_animation(void);
extern void cancel_hero_item_animation(void);
extern int PlayMobySound(int, int, void *);
extern char *spider_bot_spawn(void *, void *);
extern void ref_L01_003B2598_00(void (*)(void *), void *);
extern void helper_update_hit_test(void *);
extern char *g_spiderbot_glove_target __attribute__((sda));
extern int g_hero_l01_control_mode MACRO_ADDR;
extern int g_hero_aux_mode MACRO_ADDR;
extern int g_hero_input_lock_alt MACRO_ADDR;
extern int g_pad_held_flags NOT_SDA;

/* Updates the Spiderbot Glove pickup: checks that the hero may use it, lets the hero grab it with the button, and plays its use effect. */
void spiderbot_glove_update(char *moby) {
    float pos[4], sweep_storage[4], normal[4];
    float *sweep;
    char *hit;
    int aux;
    char *moby_vars = *(char **)(moby + 0x68);
    int result, state, ready;
    float height;

    {
        char *hero = g_hero_state;

        if (*(int *)(hero + 0x1244) == 3)
            g_spiderbot_glove_target = 0;
        moby_transform_joint_to_world(moby, 0, pos);
        *(int *)(moby_vars + 0x2C) = 0;
        sweep = sweep_storage;
        height = (*(int *)(hero + 0x2294) == 29) ? 11.0f : 4.5f;
        CalculateAimedLaunchVelocity(sweep, pos, 0, 0, 1.6f, height, 0.13333334028720856f, 0.003055555745959282f);
    }
    *(int *)(moby_vars + 0x24) = coll_trace_projectile_to_impact(pos, sweep, moby_vars, moby_vars + 0x10, moby, &hit, &aux, 0.003055555745959282f);
    result = weapon_get_group(aux);
    if (g_hero_l01_control_mode || g_hero_aux_mode != -2)
        *(int *)(moby_vars + 0x2C) = 1;
    if (g_hero_input_lock_alt && *(float *)(moby_vars + 8) < 462.42999267578125f)
        *(int *)(moby_vars + 0x2C) = 1;
    if (result || !*(int *)(moby_vars + 0x24) || !*(int *)(moby_vars + 0x28))
        goto blocked;
    {
        char *hero = g_hero_state;

        state = *(int *)(hero + 0x2294);
        if (state == 40 || state == 62 || state == 39 || state == 41 || state == 42 || state == 6 ||
            state == 116 || state == 129)
            goto blocked;
        if (*(char **)(hero + 0x33C) && (*(short *)(*(char **)(hero + 0x33C) + 0xAA) == MOBY_CLASS_TAXI ||
                                      *(short *)(*(char **)(hero + 0x33C) + 0xAA) == 0xB21 /* moby class 2849 */))
            goto blocked;
        if (hit && (*(short *)(hit + 0xAA) == 0xB21 /* moby class 2849 */ || *(short *)(hit + 0xAA) == 0xB5B /* moby class 2907 */))
            goto blocked;
    }
    moby_get_facing_direction(moby_vars, normal);
    if (!(FastVecDot(moby_vars + 0x10, normal) < 0.75f))
        goto timer;
blocked:
    *(int *)(moby_vars + 0x2C) = 1;
timer:
    {
        char *hero = g_hero_state;

        ready = 1;
        if (*(int *)(hero + 0x2294) == 29) {
            if (!math_fast_float_d(hero + 0x2534))
                ready = 0;
        } else
            *(int *)(hero + 0x2534) = 40;
    }
    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        g_spiderbot_glove_target = moby;
        *(unsigned char *)(moby + 0x20) = 1;
        *(int *)(moby_vars + 0x28) = 1;
        *(int *)(moby_vars + 0x24) = 0;
        /* falls through */
    case 1: {
        char *hero = g_hero_state;

        if ((g_pad_held_flags & *(int *)(hero + 0x1230)) && !*(unsigned char *)(hero + 0x22BC) &&
            !*(int *)(moby_vars + 0x2C) && ready) {
            if (weapon_spend_ammo(-1, 1)) {
                *(short *)(hero + 0x1E0) = 120;
                ForceClaimNotice(6, 0, 1);
                *(short *)(hero + 0x1D2) = 0;
                start_equipped_item_animation();
                *(unsigned char *)(moby + 0x20) = 2;
                *(int *)(moby_vars + 0x20) = 12;
                *(int *)(moby_vars + 0x28) = 0;
            } else
                PlayMobySound(0, 0, moby);
        }
        break;
    }
    case 2:
        if (math_fast_float_d(moby_vars + 0x20)) {
            char *effect_moby = spider_bot_spawn(pos, sweep);

            if (effect_moby)
                *(char **)(effect_moby + 0xB8) = moby;
            PlayMobySound(1, 0, moby);
            cancel_hero_item_animation();
            *(unsigned char *)(moby + 0x20) = 3;
            *(int *)(moby_vars + 0x20) = 5;
        }
        break;
    case 3:
        if (math_fast_float_d(moby_vars + 0x20))
            *(unsigned char *)(moby + 0x20) = 1;
        break;
    }
    ref_L01_003B2598_00(helper_update_hit_test, moby);
}
