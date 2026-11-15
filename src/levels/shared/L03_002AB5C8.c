#include "include_asm.h"
#include "common.h"

typedef union { int quad __attribute__((mode(TI))); struct { float x, y, z, w; } f; } HopVector;
/* Player (Ratchet) state block in the level's data, reached through D_L03_00189E20. */
typedef struct {
    HopVector field_0;
    unsigned char pad_10[0x10];
    HopVector field_20;
    unsigned char pad_30[0x68];
    float rot_z;
    unsigned char pad_9C[0x54];
    float vel_x;
    float vel_y;
    unsigned char pad_F8[0x68];
    HopVector field_160;
    unsigned char pad_170[0x4];
    float field_174;
    unsigned char pad_178[0x18];
    HopVector field_190;
    float facing_angle;
    float field_1A4;
    float field_1A8;
    unsigned char pad_1AC[0x4];
    float field_1B0;
    float field_1B4;
    int state_time;
    unsigned char pad_1BC[0x18c];
    short field_348;
    short field_34A;
    unsigned char pad_34C[0x108];
    float field_454;
    unsigned char pad_458[0x18];
    HopVector field_470;
    HopVector field_480;
    unsigned char pad_490[0x4];
    float field_494;
    unsigned char pad_498[0x6];
    unsigned char field_49E;
    unsigned char pad_49F[0xf];
    short field_4AE;
    unsigned char pad_4B0[0xc];
    float field_4BC;
    float field_4C0;
    float field_4C4;
    unsigned char pad_4C8[0xc];
    int field_4D4;
    float field_4D8;
    float field_4DC;
    unsigned char pad_4E0[0x10];
    HopVector field_4F0;
    unsigned char pad_500[0x20];
    float field_520;
    short field_524;
    unsigned char pad_526[0x7];
    unsigned char field_52D;
    unsigned char pad_52E[0x532];
    HopVector field_A60;
    unsigned char pad_A70[0x14];
    float field_A84;
    unsigned char pad_A88[0x1b0];
    float anim_time;
    unsigned char pad_C3C[0x804];
    HopVector field_1440;
    unsigned char pad_1450[0x4];
    short field_1454;
    unsigned char pad_1456[0x2];
    float field_1458;
    unsigned char pad_145C[0xe38];
    int state;
    unsigned char pad_2298[0x4];
    int field_229C;
    unsigned char pad_22A0[0x23];
    unsigned char field_22C3;
    unsigned char pad_22C4[0x1f4];
    float field_24B8;
} HopPlayer;
#define HOP_PLAYER (*(HopPlayer *)D_L03_00189E20)
extern int D_L03_001A8FF0[] __attribute__((sda));
extern float D_L03_001A7DC0[] __attribute__((sda));
typedef struct {
    unsigned char pad_0[0x158];
    float angle;
    unsigned char pad_15C[0x214];
    HopVector basis;
} HopSavedState;
extern unsigned char D_L03_001B9840[];
#define HOP_SAVED (*(HopSavedState *)D_L03_001B9840)
extern void hero_build_move_impulse(float, float);
extern void hero_approach_speed(float, float);
extern void cam_set_view_space_vector_length(float, void *, void *);
extern void cam_offset_point_by_side_direction(void *, void *, float);
extern void hero_steer_heading(float, float, float, int);
extern void hero_approach_velocity(float);
extern float FastVecDot(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void cam_set_view_space_height(float, void *, void *);
extern float FastDiffRots(float, float);
extern float math_approach_with_velocity(float *, float *, int, float, float, float, float);
extern float fast_subtract_rotations(float, float);
extern void hero_start_pose_offset(float, float, float);
extern float cam_get_view_space_vector_length(void *);

/* Object (moby) header: its state pointer and class id. */
typedef struct {
    unsigned char pad_0[0x68];
    unsigned char *state;
    unsigned char pad_6C[0x3e];
    short type;
} Moby;

/* Particle record returned by func_002BDCE8; its payload follows at 0x20. */
typedef struct {
    unsigned char pad_0[4];
    int mode;
    unsigned char pad_8[2];
    unsigned char alpha;
    unsigned char alpha_copy;
} ParticlePayload;

typedef struct {
    unsigned char pad_0[8];
    unsigned char variation;
    unsigned char pad_9;
    union {
        short duration;
        unsigned char duration_lo;
    } life;
    unsigned char pad_C[0x14];
    ParticlePayload payload;
} Particle;

/* Particle emitter inputs; the two register banks retain their EE argument order. */
extern float D_L03_001A8F20[] __attribute__((sda));
extern void FastVecAdd(void *, void *, void *);
extern int math_random_int_below(int);
extern void moby_transform_joint_point(void *, int, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern Particle *SpawnSpinningSparkParticle(void *, float, float, float, int, void *, float, unsigned int, int);


#define MACRO_ADDR __attribute__((section(".sdata")))

typedef int TI128 __attribute__((mode(TI)));

extern int func_2B3760(int);

extern unsigned char D_L03_00189E20[];

extern int r1_D_L02_0015F04C MACRO_ADDR;

extern int r1_D_L02_00169670[];

extern int func_2EEC20(void *);

extern void func_331270(void *);

extern TI128 D_001A8F20;

extern void func_2EEFB0(void *, void *, void *);

extern void func_2EF020(void *, float);

extern void func_2ECA50(unsigned char *, int, int, int);

extern int D_001AEF60 __attribute__((sda));

extern float func_2EF158(void *, void *);

extern void func_2B8300(int, int, void *);

extern int func_419B10(void *, void *, int, void *, void *, void *, float, float);

extern void func_32D0F0(void *, int, float);

extern float func_2EF670(float, float);



/* func_L03_002ADC00 is in its dedicated zero-vector profile unit. */

/* Copies a value from the hero into the object the hero is holding, when the hero has one. */
void hero_copy_value_to_held_object(void) {
    unsigned char *hero = D_L03_00189E20;

    if (*(short *)(hero + 0x6BC) != 0 && *(int *)(hero + 0x660) == 0)
        *(float *)(*(unsigned char **)(hero + 0x2290) + 0xF4) = *(float *)(hero + 0x6B0);
}


extern float ApproachValue(float *, float, float);
extern void math_spring_float_to_goal(float *, float *, float, float, float, float);
extern float vec_distance_xy(void *, void *);

/* Picks target values for the hero's camera settings from the hero's state, then eases the current values toward them. */
void cam_update_hero_targets(void) {
    switch (D_L03_00189E20[0x22B4]) {
    case 0:
        *(float *)(D_L03_00189E20 + 0x258) = 0.8f;
        *(float *)(D_L03_00189E20 + 0x25C) = 0.7f;
        *(float *)(D_L03_00189E20 + 0x260) = 0.449999988079071f;
        break;
    case 1:
        *(float *)(D_L03_00189E20 + 0x258) = 0.599999964237213f;
        *(float *)(D_L03_00189E20 + 0x25C) = 0.450000017881394f;
        *(float *)(D_L03_00189E20 + 0x260) = 0.3f;
        break;
    }
    {
        unsigned char *hero = D_L03_00189E20;
        if (*(int *)(hero + 0x229C) == 4) {
            if (*(short *)(hero + 0x4AC) < *(int *)(hero + 0x1B8) && !hero[0x49E])
                *(float *)(hero + 0x25C) = *(float *)(hero + 0x4B8);
        } else if (*(int *)(hero + 0x2294) == 6) {
            *(float *)(hero + 0x25C) = 0.5f;
        } else if (*(int *)(hero + 0x2294) == 4) {
            *(float *)(hero + 0x258) = 0.350000023841858f;
        } else if (*(int *)(hero + 0x2294) == 0x7C) {
            *(float *)(hero + 0x260) = 0.8f;
        }
    }
    if (!D_L03_00189E20[0x287] || *(int *)(D_L03_00189E20 + 0x22A4) == 0x12 ||
        *(int *)(D_L03_00189E20 + 0x22B0) == 0x12 ||
        (!D_L03_00189E20[0x22B4] && *(float *)(D_L03_00189E20 + 0x254) < 0.53f) ||
        *(int *)(D_L03_00189E20 + 0x229C) == 0x11 || D_L03_00189E20[0x1494] ||
        vec_distance_xy(D_L03_00189E20 + 0x240, D_L03_00189E20 + 0x80) > *(float *)(D_L03_00189E20 + 0x264) * 0.5f) {
        float *values = (float *)(D_L03_00189E20 + 0x250);
        unsigned char *hero = D_L03_00189E20;
        ApproachValue(values, *(float *)(hero + 0x258), 0.02f);
        ApproachValue(values + 1, *(float *)(hero + 0x25C), 0.02f);
        math_spring_float_to_goal(values + 5, values + 6, *(float *)(hero + 0x260), 0.02f, 0.3f, 0.06666667f);
    }
}

/* Per-state airborne steering of the player: velocity, facing and speed targets. */
void HeroUpdateHopVelocity(void) {
    HopVector temp;
    float step, scale;

    if (HOP_PLAYER.state == 10) {
        hero_build_move_impulse(0.7f, 0.0f);
        qcopy(&HOP_PLAYER.field_160, &HOP_PLAYER.field_A60);
        HOP_PLAYER.field_1B4 = HOP_PLAYER.field_174;
        return;
    }

    if (HOP_PLAYER.state == 0x10) {
        if (HOP_PLAYER.state_time > 0x36)
            ApproachValue(&HOP_PLAYER.field_520, 0.0069444444961845875f, 0.0019444444915279746f);
        if (HOP_PLAYER.state_time <= 0x36)
            HOP_PLAYER.field_1B0 = HOP_PLAYER.field_454;
        else
            HOP_PLAYER.field_1B0 = 0.05833333730697632f;
        hero_approach_speed(0.012222222983837128f, 0.0125f);
        cam_set_view_space_vector_length(0.0f, &HOP_PLAYER.vel_x, &HOP_PLAYER.vel_x);
        cam_offset_point_by_side_direction(&HOP_PLAYER.vel_x, &HOP_PLAYER.vel_x, HOP_PLAYER.field_1B4);
        return;
    }

    if (HOP_PLAYER.state == 0x1B) {
        if (HOP_PLAYER.state_time > 0x28) {
            hero_steer_heading(0.04f, 0.2f, 0.2501639127731323f, 0);
            hero_approach_velocity(0.0055555556900799274f);
        }
        if (HOP_PLAYER.anim_time >= 13.0f && HOP_PLAYER.anim_time <= 30.0f) {
            if (HOP_PLAYER.anim_time > 27.0f)
                ApproachValue(&HOP_PLAYER.field_4BC, 0.0f, 0.002222222276031971f);
            else
                ApproachValue(&HOP_PLAYER.field_4BC, 0.03333333507180214f, 0.002222222276031971f);
        }
        temp.f.x = HOP_PLAYER.field_4BC;
        temp.f.y = 0.0f;
        temp.f.z = FastVecDot(&HOP_PLAYER.vel_x, &HOP_PLAYER.field_20);
        matrix_mul_vec3(&HOP_PLAYER.vel_x, &temp, &HOP_PLAYER);
        return;
    }

    if (HOP_PLAYER.state == 0x48) {
        if (HOP_PLAYER.anim_time >= 5.0f && HOP_PLAYER.anim_time <= 18.0f) {
            if (HOP_PLAYER.anim_time > 15.0f)
                ApproachValue(&HOP_PLAYER.field_4BC, 0.0f, 0.002222222276031971f);
            else
                ApproachValue(&HOP_PLAYER.field_4BC, 0.02083333395421505f, 0.002222222276031971f);
        }
        temp.f.x = HOP_PLAYER.field_4BC;
        temp.f.y = 0.0f;
        temp.f.z = FastVecDot(&HOP_PLAYER.vel_x, &HOP_PLAYER.field_20);
        matrix_mul_vec3(&HOP_PLAYER.vel_x, &temp, &HOP_PLAYER);
        return;
    }

    if (HOP_PLAYER.state == 0xB) {
        HOP_PLAYER.facing_angle = HOP_PLAYER.field_4C4;
        qcopy(&HOP_PLAYER.field_190, &HOP_PLAYER.field_480);
        hero_steer_heading(0.04f, 0.2f, 0.116355299949646f, 0);
        if (HOP_PLAYER.field_4D4 != 3)
            HOP_PLAYER.field_1B4 = HOP_PLAYER.field_4D8;
        else
            HOP_PLAYER.field_1B4 = 0.0f;
        if (HOP_PLAYER.field_52D) {
            step = HOP_PLAYER.field_24B8 * 0.0833333358168602f;
            if (step < 0.03333333507180214f)
                step = 0.03333333507180214f;
            ApproachValue(&HOP_PLAYER.field_4DC, step, 0.010277777910232544f);
            HOP_PLAYER.field_1B4 = HOP_PLAYER.field_174;
        } else {
            if (HOP_PLAYER.field_49E && HOP_PLAYER.field_4AE <= 11)
                ApproachValue(&HOP_PLAYER.field_4DC, 0.0f, 0.002222222276031971f);
            else
                ApproachValue(&HOP_PLAYER.field_4DC, 0.07f, 0.002222222276031971f);
        }
        if (!HOP_PLAYER.field_22C3) {
            HOP_PLAYER.vel_x = math_fast_sin_or_cos_a(HOP_PLAYER.field_4C0);
            HOP_PLAYER.vel_x *= HOP_PLAYER.field_4DC;
            HOP_PLAYER.vel_y = math_fast_sin_or_cos_b(HOP_PLAYER.field_4C0);
            HOP_PLAYER.vel_y *= HOP_PLAYER.field_4DC;
        } else {
            cam_set_view_space_vector_length(HOP_PLAYER.field_4DC, &temp, &HOP_PLAYER.field_470);
            cam_set_view_space_height(0.0f, &temp, &temp);
            cam_set_view_space_vector_length(0.0f, &HOP_PLAYER.vel_x, &HOP_PLAYER.vel_x);
            FastVecAdd(&HOP_PLAYER.vel_x, &HOP_PLAYER.vel_x, &temp);
        }
        if (!HOP_PLAYER.field_22C3 && !HOP_PLAYER.field_52D) {
            scale = HOP_PLAYER.field_4D8 * math_fast_sin_or_cos_b(FastDiffRots(HOP_PLAYER.field_4C4, HOP_PLAYER.field_4C0));
            HOP_PLAYER.vel_x += math_fast_sin_or_cos_a(HOP_PLAYER.field_4C4) * scale;
            HOP_PLAYER.vel_y += math_fast_sin_or_cos_b(HOP_PLAYER.field_4C4) * scale;
        }
        hero_build_move_impulse(0.7f, 0.0f);
        qcopy(&HOP_PLAYER.field_160, &HOP_PLAYER.field_A60);
        return;
    }

    if (HOP_PLAYER.state == 0x11) {
        HOP_PLAYER.facing_angle = HOP_PLAYER.field_4F0.f.w;
        qcopy(&HOP_PLAYER.field_190, &HOP_PLAYER.field_4F0);
        if (HOP_PLAYER.state_time > 9)
            hero_steer_heading(0.041999999433755875f, 0.2f, 0.1978040188550949f, -1);
        if (HOP_PLAYER.state_time > 8) {
            if (!HOP_PLAYER.field_348) {
                HOP_PLAYER.vel_x = math_fast_sin_or_cos_a(HOP_PLAYER.facing_angle) * 0.08166667073965073f;
                HOP_PLAYER.vel_y = math_fast_sin_or_cos_b(HOP_PLAYER.facing_angle) * 0.08166667073965073f;
            } else {
                cam_set_view_space_vector_length(0.0f, &HOP_PLAYER.vel_x, &HOP_PLAYER.vel_x);
                vec_scale_to_length(&temp, &HOP_PLAYER.field_190, 0.08166667073965073f);
                FastVecAdd(&HOP_PLAYER.vel_x, &HOP_PLAYER.vel_x, &temp);
            }
        }
        HOP_PLAYER.field_1B4 = HOP_PLAYER.field_174;
        return;
    }

    if (HOP_PLAYER.state == 0x81 && !D_L03_001A8FF0[0]) {
        hero_steer_heading(0.04f, 0.2f, HOP_PLAYER.field_494, 0);
        HOP_PLAYER.field_1B4 = 0.0f;
        return;
    }

    if (HOP_PLAYER.state == 0x2C) {
        float angle = HOP_PLAYER.rot_z;
        float delta;

        HOP_PLAYER.field_1A8 = math_approach_with_velocity(&angle, &HOP_PLAYER.field_1A4, 0, HOP_PLAYER.facing_angle,
                                             0.017999999225139618f, 0.2f, 0.12217307090759277f);
        delta = fast_subtract_rotations(angle, HOP_PLAYER.rot_z);
        hero_start_pose_offset(0.0f, 0.0f, delta);
    } else {
        float oldAngle = HOP_PLAYER.facing_angle;

        qcopy(&temp, &HOP_PLAYER.field_190);
        if (HOP_PLAYER.field_1454) {
            HOP_PLAYER.facing_angle = HOP_SAVED.angle;
            qcopy(&HOP_PLAYER.field_190, &HOP_SAVED.basis);
        }
        hero_steer_heading(0.04f, 0.2f, HOP_PLAYER.field_494, 0);
        if (HOP_PLAYER.field_1454) {
            HOP_PLAYER.field_1458 = oldAngle;
            qcopy(&HOP_PLAYER.field_1440, &temp);
            HOP_PLAYER.facing_angle = oldAngle;
            qcopy(&HOP_PLAYER.field_190, &HOP_PLAYER.field_1440);
        }
    }

    hero_build_move_impulse(0.7f, 0.0f);
    qcopy(&HOP_PLAYER.field_160, &HOP_PLAYER.field_A60);

    step = 0.0055555556900799274f;
    if (HOP_PLAYER.field_1B0 < D_L03_001A7DC0[0] * 0.0033333336468786f) {
        if (HOP_PLAYER.field_229C == 2) {
            float brake = HOP_PLAYER.field_A84;
            float angle = cam_get_view_space_vector_length(&HOP_PLAYER.vel_x);

            ApproachValue(&angle, 0.0f, brake);
            cam_set_view_space_vector_length(angle, &HOP_PLAYER.vel_x, &HOP_PLAYER.vel_x);
            return;
        }
        if (HOP_PLAYER.field_34A)
            step = 0.003055555745959282f;
        else
            step = HOP_PLAYER.field_524 ? 0.0005555555690079927f : 0.002222222276031971f;
    }

    hero_approach_velocity(step);
}

#undef HOP_PLAYER
#undef HOP_SAVED

/* rac1-decomp src/overlays/shared/camera_001FC308.c: func_L02_001FC308 */
/* Adapted from Lombyte (GPL-3.0) for PAL by OpenRAC's tools/port.py: src/overlays/shared/gameplay/camera/001fc008.c, FUN_L02_001fc008. */
/* Remembers an id in a list of up to 16, unless it is already there. */
void register_camera_update_callback(int id) {
    int i;

    if (r1_D_L02_0015F04C < 16) {
        for (i = 0; i < r1_D_L02_0015F04C; i++) {
            if (id == r1_D_L02_00169670[i]) {
                return;
            }
        }
        r1_D_L02_00169670[r1_D_L02_0015F04C++] = id;
    }
}




ASM_FUNC("asm/levels", func_L03_002EFB60);


/* Emits two particle groups scaled by the object's transformed basis length. */
void EmitScaledObjectParticles(Moby *object)
{
    float matrix[16], point[4], velocity[4];
    float weight, radius, energy;
    short type = object->type;

    if ((type != 0x2EE /* moby class 750 */ && type != 0xCE0 /* moby class 3296 */) || object == 0)
        return;

    moby_transform_joint_point(object, 0, matrix);
    weight = FastVecLength(matrix) * 0.9746588468551636f;
    if (weight > 1.0f)
        weight = 1.0f;
    energy = weight * 44000.0f + 6000.0f;
    radius = weight * 0.02f + 0.01f;
    vec_scale_to_length(velocity, matrix + 8, weight * -0.025f + -0.025f);

    /* Larger smoke puffs with random spin. */
    {
        int i;
        short duration;
        int mode;
        unsigned char alpha;

        duration = 6;
        mode = 2;
        alpha = 0x50;
        FastVecAdd(point, matrix + 12, velocity);
        i = 1;
        do {
            Particle *particle;
            int spin;

            spin = math_random_int_below(16);
            if (math_random_int_below(2))
                spin = -spin;
            particle = SpawnSpinningSparkParticle(point, radius, 1.0f, 0.75f, spin, D_L03_001A8F20, energy, 0x503030FF, 0);
            if (particle != 0) {
                ParticlePayload *payload = &particle->payload;

                particle->life.duration = duration;
                payload->mode = mode;
                payload->alpha = alpha;
                payload->alpha_copy = particle->life.duration_lo;
            }
            i--;
        } while (i >= 0);
    }

    energy = weight * 25000.0f + 5000.0f;
    radius = weight * 0.015000000596046448f + 0.01f;
    vec_scale_to_length(velocity, matrix + 8, weight * -0.015000000596046448f + -0.01f);

    /* Smaller, short-lived sparks. */
    {
        short duration;
        int mode;
        unsigned char alpha;

        duration = 2;
        mode = 2;
        alpha = 0x7F;
        FastVecAdd(point, matrix + 12, velocity);
        {
            int j;

            j = 4;
            do {
                Particle *particle;

                particle = SpawnSpinningSparkParticle(point, radius, 1.0f, 1.0f, 16, D_L03_001A8F20, energy, 0x7FFFFFFF, 0);
                if (particle != 0) {
                    ParticlePayload *payload = &particle->payload;

                    particle->life.duration = duration;
                    particle->variation = math_random_int_below(255);
                    payload->mode = mode;
                    payload->alpha = alpha;
                    payload->alpha_copy = particle->life.duration_lo;
                }
                j--;
            } while (j >= 0);
        }
    }
}


/* func_L03_00329EF0 is defined in L03_002AB5C8-region.c. */


/* func_L03_00339128 is defined in L03_00339128-qcopy.c. */

/* Starts an effect only when the entry is in use and the check on it passes. */
void part_start_effect_if_active(unsigned char *effect) {
    if (*(short *)(effect + 0xA) == -1)
        return;
    if (func_2EEC20(effect + 0xA) == 0)
        return;
    func_331270(effect);
}


/* func_L03_0038AB30 is defined in L03_002AB5C8-ribbon.c (its own loop-pass flags). */

/* func_L03_0038B238 is defined in L03_002AB5C8-g8.c (this unit has no $gp access for it). */


/* Sets up an effect record with the same value in its first four slots and default scales. */
void part_l03_init_effect_record(unsigned char *effect, int param_a, int param_b, int fill_value) {
    unsigned char *record = effect;
    int value = fill_value;

    func_2ECA50(effect, param_a, param_b, 0x80);
    *(int *)(record + 0x4C) = value;
    *(int *)(record + 0x48) = value;
    *(int *)(record + 0x44) = value;
    *(int *)(record + 0x40) = value;
    *(int *)(record + 0x50) = 0;
    *(int *)(record + 0x54) = 0;
    *(int *)(record + 0x58) = 0;
    *(float *)(record + 0x5C) = 1.0f;
    *(float *)(record + 0x60) = 1.0f;
    *(int *)(record + 0x64) = 0;
    *(float *)(record + 0x68) = 1.0f;
    *(float *)(record + 0x6C) = 1.0f;
    *(long long *)(record + 0x70) = 5;
}

extern void vec_average_list(void *, void *, int);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float (*D_L03_001FE700[])[4];

/* Effect state hung off an object: four vertex-table indices, a vertex count and an offset. */
typedef struct {
    unsigned char pad_0[0x28];
    int groups[4];
    int count;
    unsigned char pad_3C[0xA4];
    float offset[4];
} VertexGroupState;

/* Adjusts each vertex of the object's groups relative to a computed centre, then offsets it by the state vector. */
void func_L03_0038B408(Moby *object)
{
    float center[4];
    VertexGroupState *state = (VertexGroupState *)object->state;
    float (**table)[4] = D_L03_001FE700;
    float (*vertices)[4];
    int i, j;

    for (i = 0; i < 4; i++) {
        vertices = table[state->groups[i]];
        if (vertices != 0) {
            vec_average_list(center, vertices, state->count);
            for (j = 0; j < state->count; j++) {
                FastVecSub(vertices + j + 1, vertices + j + 1, center);
                FastVecAdd(vertices + j + 1, vertices + j + 1, state->offset);
            }
        }
    }
}




/* Fires a trigger on the object when the hero is standing close to it. */
void moby_trigger_when_hero_near(unsigned char *object) {
    unsigned char *hero = D_L03_00189E20;

    if (*(unsigned char *)(hero + 0x22B4) == 0)
        if (func_2EF158(hero + 0x80, object + 0x10) < 1.7f)
            func_2B8300(1, 0x3F, object);
}


/* Returns true when the object is in state 1. */
int moby_l03_is_state_one(unsigned char *object) { return object[0x20] == 1; }



float bot_compute_speed_from_turn(unsigned char *);

/* Asks where a bot should go next and moves it that way, returning the result of the check. */
int bot_move_toward_waypoint(unsigned char *object, int index, int use_extra) {
    unsigned char *state = *(unsigned char **)(object + 0x68);
    float extra = 0.0f;
    float out;
    int result;

    if (use_extra != 0)
        extra = bot_compute_speed_from_turn(object);
    result = func_419B10(*(void **)(state + 0x220), object + 0x10, index, &out, state + 0x368, state + 0x36C, extra,
                    *(float *)(state + 0x110));
    func_32D0F0(object, index, out);
    return result;
}

/* func_L03_003C4240 is defined in L03_002AB5C8-g8.c (it reads two $gp constants). */

/* func_L03_003C4368 is defined in L03_003C4368-g8.c. */

/* func_L03_003C4468 is defined in L03_003C4468-flags.c. */

/* func_L03_003C4578 is defined in L03_002AB5C8-g8.c (it reads $gp data). */


/* func_L03_003C4A10 is defined in L03_002AB5C8-g8.c (it reads $gp data). */

extern int math_fast_float_d(void *);

extern float math_random_signed_float_range(float, float);

extern float math_random_float_range(float, float);

extern int math_random_int_range(int, int);

extern int math_random_int_below(int);

/* The level's own copy of the object's tilt routine (func_L03_003C4A10), at another address
   in every level that has it. */
extern void ref_L03_003C4BD8_00(unsigned char *, void *);

/* The position the tilt is measured from: a four-float vector in the boot's resident data. */
extern char D_L00_00189F00[];

/* Every so often picks a new random head tilt for the bot, or makes it look toward a fixed point. */
void bot_update_head_tilt(unsigned char *object) {
    unsigned char *state = *(unsigned char **)(object + 0x68);
    float tilt_yaw;
    float tilt_pitch;
    int look_at_point;

    if (math_fast_float_d(state + 0x384) != 0) {
        if (object[0x95] == 2) {
            *(float *)(state + 0x388) = math_random_signed_float_range(5.0f, 60.0f) * 0.017453294f;
            *(float *)(state + 0x38C) = math_random_float_range(-20.0f, 0.0f) * 0.017453294f;
            *(int *)(state + 0x384) = math_random_int_range(30, 45);
            *(int *)(state + 0x390) = 0;
        } else {
            *(float *)(state + 0x388) = math_random_signed_float_range(5.0f, 20.0f) * 0.017453294f;
            *(float *)(state + 0x38C) = math_random_float_range(-15.0f, 5.0f) * 0.017453294f;
            look_at_point = (math_random_int_below(4) == 0);
            *(int *)(state + 0x390) = look_at_point;
            if (look_at_point) {
                *(int *)(state + 0x384) = math_random_int_range(180, 300);
            } else {
                *(int *)(state + 0x384) = math_random_int_range(60, 120);
            }
        }
    }

    if (*(int *)(state + 0x390) != 0) {
        ref_L03_003C4BD8_00(object, D_L00_00189F00);
    } else {
        tilt_yaw = *(float *)(state + 0x38C);
        tilt_pitch = *(float *)(state + 0x388);
        /* This cc1 emits the two pairs of stores in the opposite order to the source, so the
           pair at 0x324 comes first here to land them at 0x2A4 as the retail has them. */
        *(float *)(state + 0x324) = tilt_yaw;
        *(float *)(state + 0x328) = tilt_pitch;
        *(float *)(state + 0x2A4) = tilt_yaw;
        *(float *)(state + 0x2A8) = tilt_pitch;
    }
}

/* The level's entity table base, the group count and the table of group id lists (in the
   resident image: the list of group g ends after its first entry with bit 15 set). */
extern unsigned char *D_L03_001B2A1C __attribute__((sda));

extern int D_L03_001B2A38[] __attribute__((sda));

extern unsigned short *D_L03_001FB5A0[];

/* The part of the object's private state (at +0x68) that these walks read: eight group ids at
   +0x200 and the id of an entity at +0x220. */
typedef struct {
    unsigned char pad0[0x200];
    int ids[8];
    unsigned int ref220;
} L03GroupState;

extern unsigned int moby_get_count_in_state_two(unsigned char *);

extern int route_check_points(unsigned int, void *, void *);

extern float vec_distance_xy(void *, void *);

extern float math_fabs(float);

/* Returns the entity nearest to the object, within 15.0, among its eight groups, that has bit 12
   of its flags at 0x34 set, a value of 5 at 0x46 of the record at 0x24, a height (at 0x18)
   within 1.5 of the object's and that func_L03_00419BD8 accepts, or 0. */
unsigned char *moby_find_nearest_tilt_target(unsigned char *object) {
    L03GroupState *vars = *(L03GroupState **)(object + 0x68);
    unsigned short *id_list;
    unsigned char *entity;
    unsigned char *best = 0;
    float best_distance = 15.0f;
    float distance;
    int i;

    for (i = 0; i < 8; i++) {
        for (id_list = D_L03_001FB5A0[vars->ids[i]];
             (vars->ids[i] & 0xFF) != 0xFF && vars->ids[i] <= D_L03_001B2A38[0] && id_list != 0 &&
             ((short)id_list[-1] >= 0 || id_list == D_L03_001FB5A0[vars->ids[i]]);
             id_list++) {
            entity = D_L03_001B2A1C + ((*id_list & 0x7FFF) << 8);
            if (entity == 0)
                break;
            if (entity[0x20] == 0xFE)
                continue;
            if (entity[0x20] == 0xFD)
                continue;
            if (*(unsigned short *)(entity + 0x34) & 0x1000) {
                if (*(short *)(*(unsigned char **)(entity + 0x24) + 0x46) == 5) {
                    if (math_fabs(*(float *)(object + 0x18) - *(float *)(entity + 0x18)) < 1.5f) {
                        if (route_check_points(vars->ref220, object + 0x10, entity + 0x10)) {
                            distance = vec_distance_xy(object + 0x10, entity + 0x10);
                            if (distance < best_distance) {
                                best_distance = distance;
                                best = entity;
                            }
                        }
                    }
                }
            }
        }
    }
    return best;
}

/* Returns the entity of class 0xEF9 nearest to the object, within 15.0, among its eight groups
   (func_L03_004197A8 and func_L03_00419BD8 must both accept it), or 0. */
unsigned char *moby_find_nearest_entity_a(unsigned char *object) {
    L03GroupState *vars = *(L03GroupState **)(object + 0x68);
    unsigned short *id_list;
    unsigned char *entity;
    unsigned char *best = 0;
    float best_distance = 15.0f;
    float distance;
    int i;

    for (i = 0; i < 8; i++) {
        for (id_list = D_L03_001FB5A0[vars->ids[i]];
             (vars->ids[i] & 0xFF) != 0xFF && vars->ids[i] <= D_L03_001B2A38[0] && id_list != 0 &&
             ((short)id_list[-1] >= 0 || id_list == D_L03_001FB5A0[vars->ids[i]]);
             id_list++) {
            entity = D_L03_001B2A1C + ((*id_list & 0x7FFF) << 8);
            if (entity == 0)
                break;
            if (*(short *)(entity + 0xAA) == 0xEF9 /* moby class 3833 */) {
                if (moby_get_count_in_state_two(entity)) {
                    if (route_check_points(vars->ref220, object + 0x10, entity + 0x10)) {
                        distance = vec_distance_xy(object + 0x10, entity + 0x10);
                        if (distance < best_distance) {
                            best_distance = distance;
                            best = entity;
                        }
                    }
                }
            }
        }
    }
    return best;
}

extern unsigned int moby_check_against_stored_value(unsigned char *, unsigned char *);

/* Returns the first entity of class 0x97A, in the object's eight groups, that
   func_L03_003CAAC8 finds near the object or near the player, or 0. The group table is reached
   through a local pointer: with its address computed once outside the loops, the walk's other
   constants (0x97A, 0xFF, the player's address) all fit loop.c's budget for moving invariants
   out of the walk, as in retail. */
unsigned char *moby_find_entity_nearby(unsigned char *object) {
    L03GroupState *vars = *(L03GroupState **)(object + 0x68);
    unsigned short **group_table = D_L03_001FB5A0;
    unsigned short *id_list;
    unsigned char *entity;
    int i;

    for (i = 0; i < 8; i++) {
        for (id_list = group_table[vars->ids[i]];
             (vars->ids[i] & 0xFF) != 0xFF && vars->ids[i] <= D_L03_001B2A38[0] && id_list != 0 &&
             ((short)id_list[-1] >= 0 || id_list == group_table[vars->ids[i]]);
             id_list++) {
            entity = D_L03_001B2A1C + ((*id_list & 0x7FFF) << 8);
            if (entity == 0)
                break;
            if (*(short *)(entity + 0xAA) == 0x97A /* moby class 2426 */) {
                if (moby_check_against_stored_value(entity, object + 0x10))
                    return entity;
                if (moby_check_against_stored_value(entity, D_L03_00189E20 + 0x80))
                    return entity;
            }
        }
    }
    return 0;
}

extern int moby_is_first_state(unsigned char *);

/* Returns the entity of class 0xE87 or 0xE88 in state 1 nearest to the object, within 14.0,
   among its eight groups, or 0. */
unsigned char *moby_find_nearest_entity_b(unsigned char *object) {
    L03GroupState *vars = *(L03GroupState **)(object + 0x68);
    unsigned short *id_list;
    unsigned char *entity;
    unsigned char *best = 0;
    float best_distance = 14.0f;
    float distance;
    int i;

    for (i = 0; i < 8; i++) {
        for (id_list = D_L03_001FB5A0[vars->ids[i]];
             (vars->ids[i] & 0xFF) != 0xFF && vars->ids[i] <= D_L03_001B2A38[0] && id_list != 0 &&
             ((short)id_list[-1] >= 0 || id_list == D_L03_001FB5A0[vars->ids[i]]);
             id_list++) {
            entity = D_L03_001B2A1C + ((*id_list & 0x7FFF) << 8);
            if (entity == 0)
                break;
            if (*(unsigned short *)(entity + 0xAA) == 0xE87 /* moby class 3719 */ || *(unsigned short *)(entity + 0xAA) == 0xE88 /* moby class 3720 */) {
                if (moby_is_first_state(entity)) {
                    distance = vec_distance_xy(object + 0x10, entity + 0x10);
                    if (distance < best_distance) {
                        best_distance = distance;
                        best = entity;
                    }
                }
            }
        }
    }
    return best;
}

extern int moby_is_in_state_one(unsigned char *);

/* Returns the entity of class 0xB10, or of class 0xF4D that func_L03_003CA280 accepts (state 1),
   nearest to the object, within 10.0, among its eight groups (entities in state 0xFE or 0xFD are
   skipped), or 0. The group table goes through a local pointer, as in func_L03_003C5128: that is
   what leaves 0xFE out of loop.c's budget for hoisting the walk's constants, as in retail. */
unsigned char *moby_find_nearest_pickup_target(unsigned char *object) {
    L03GroupState *vars = *(L03GroupState **)(object + 0x68);
    unsigned short **group_table = D_L03_001FB5A0;
    unsigned short *id_list;
    unsigned char *entity;
    unsigned char *best = 0;
    float best_distance = 10.0f;
    float distance;
    int class_id;
    int i;

    for (i = 0; i < 8; i++) {
        for (id_list = group_table[vars->ids[i]];
             (vars->ids[i] & 0xFF) != 0xFF && vars->ids[i] <= D_L03_001B2A38[0] && id_list != 0 &&
             ((short)id_list[-1] >= 0 || id_list == group_table[vars->ids[i]]);
             id_list++) {
            entity = D_L03_001B2A1C + ((*id_list & 0x7FFF) << 8);
            if (entity == 0)
                break;
            if (entity[0x20] == 0xFE)
                continue;
            if (entity[0x20] == 0xFD)
                continue;
            class_id = *(short *)(entity + 0xAA);
            if (class_id == 0xB10 /* moby class 2832 */ || class_id == 0xF4D /* moby class 3917 */) {
                if (class_id == 0xF4D && moby_is_in_state_one(entity) == 0)
                    continue;
                distance = vec_distance_xy(object + 0x10, entity + 0x10);
                if (distance < best_distance) {
                    best_distance = distance;
                    best = entity;
                }
            }
        }
    }
    return best;
}

extern int coll_test_point(void *, int, void *, float);

extern float coll_probe_ground_height_below(void *, int, float);

extern float fast_vec_dist(void *, void *);

typedef struct {
    unsigned char pad0[0x200];
    int ids[8];
    unsigned int ref220;
    unsigned char pad1[0x354 - 0x224];
    unsigned char *target;
} L03SeekState;

/* Picks the object's target or a nearer reachable entity (type 0x972) from its eight groups,
   then copies that entity's position to a1 (height set by func_002A89A8) and its 0xF0 vector
   to a2. */
void ChooseVisibleGroupTarget(unsigned char *object, float *out_position, float *out_forward) {
    L03SeekState *vars = *(L03SeekState **)(object + 0x68);
    unsigned char *chosen;
    unsigned char *reachable;
    unsigned char *entity;
    unsigned short *id_list;
    float best_distance;
    float distance;
    float lifted[4] __attribute__((aligned(16)));
    int can_reach;
    int i;

    best_distance = fast_vec_dist(object + 0x10, vars->target + 0x10);
    chosen = vars->target;
    if (route_check_points(vars->ref220, object + 0x10, chosen + 0x10))
        reachable = vars->target;
    else
        reachable = 0;
    for (i = 0; i < 8; i++) {
        for (id_list = D_L03_001FB5A0[vars->ids[i]];
             (vars->ids[i] & 0xFF) != 0xFF && vars->ids[i] <= D_L03_001B2A38[0] && id_list != 0 &&
             ((short)id_list[-1] >= 0 || id_list == D_L03_001FB5A0[vars->ids[i]]);
             id_list++) {
            entity = D_L03_001B2A1C + ((*id_list & 0x7FFF) << 8);
            if (entity == 0)
                break;
            if (*(short *)(entity + 0xAA) == 0x972 /* moby class 2418 */) {
                distance = vec_distance_xy(object + 0x10, entity + 0x10);
                if (distance < best_distance) {
                    qcopy(lifted, entity + 0x10);
                    lifted[2] += 1.0f;
                    if (coll_test_point(lifted, 0, object, 0.5f) == 0) {
                        chosen = entity;
                        can_reach = route_check_points(vars->ref220, object + 0x10, entity + 0x10);
                        best_distance = distance;
                        if (can_reach)
                            reachable = chosen;
                    }
                }
            }
        }
    }
    if (reachable)
        chosen = reachable;
    qcopy(out_forward, chosen + 0xF0);
    qcopy_nc(out_position, chosen + 0x10);
    out_position[2] = coll_probe_ground_height_below(out_position, 0, 0.5f);
}


/* func_L03_003C58F0 is defined in L03_002AB5C8-g8.c (it reads the group count through $gp). */

/* Works out a speed-like value from the bot's turn amount, capped, times its count. */
float bot_compute_speed_from_turn(unsigned char *object) {
    unsigned char *vars = *(unsigned char **)(object + 0x68);
    float amount = func_2EF670(*(float *)(vars + 0x1DC), 1.5f);
    float count;

    if (amount > 1.4959966f)
        amount = 1.4959966f;
    amount = amount * 0.2f;
    count = (float)*(int *)(vars + 0x360);
    return amount * count;
}
