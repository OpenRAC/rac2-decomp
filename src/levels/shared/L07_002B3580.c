#include "include_asm.h"
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char D_00139574;
extern void FastVecScale(void *, void *, float);
extern void cam_compute_view_direction(void *, void *, int);
extern void part_spawn_spark_puff(void *);
extern void part_l00_spawn_impact_burst(void *, void *, void *);
extern unsigned char g_item_slot_to_record[];
extern char *g_hero_moby NOT_SDA;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int D_L00_001AC850 __attribute__((sda));
extern int D_L00_001B2630 __attribute__((sda)), D_L00_001B2638 __attribute__((sda));
extern Collision g_collision_result;
extern Material g_weapon_l00_table[];
extern void part_steer_effect_direction(int, void *, int);
extern void vec_transform_or_copy(void *, void *);
extern void shop_trigger_current_state_effect(void *, void *);
extern void vec_add_object_direction_scaled(void *, void *, float);
extern void part_emit_sparkle(void *);
extern void vec_fast_normalize_helper(void *, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern int GetCollHitMaterial(void);
extern void RippleDisturb(int, int, int, float, float, float, float);
extern void vec_clear_128(void *);
extern char *moby_spawn_scaled_effect(void *, float);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern int math_random_int_range(int, int);
extern int math_random_int_below(int);
extern void part_spawn_spark_2(void *, void *, int, int);
extern void vec_fast_normalize(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int math_fast_float_d(char *);
extern void table_clear_entry_flag(int);
extern void part_spawn_big_explosion(void *, void *, void *);

extern char D_L07_001FDEC0[];
extern void func_338D68();

typedef int DriveVector __attribute__((mode(TI)));
typedef struct PlayerDriveView {
    unsigned char pad0[0x20]; float basis[16];
    unsigned char pad60[0x98 - 0x60]; float rotation;
    unsigned char pad9C[0xF0 - 0x9C]; DriveVector velocity;
    unsigned char pad100[0x160 - 0x100]; DriveVector pendingResult;
    float distance, planarDistance;
    unsigned char pad178[0x190 - 0x178]; DriveVector direction; float heading;
    float yawRate, yawError;
    unsigned char pad1AC[4]; float speed, targetSpeed; int frame;
    unsigned char pad1BC[0x348 - 0x1BC]; short request, contact;
    unsigned char pad34C[0x454 - 0x34C]; float recoverySpeed;
    unsigned char pad458[0x470 - 0x458]; DriveVector localDirection, targetDirection;
    float pad490, acceleration;
    unsigned char pad498[6]; unsigned char allowAction;
    unsigned char pad49F[0x4AE - 0x49F]; short actionFrame;
    unsigned char pad4B0[12]; float lateralSpeed, inputHeading, targetHeading;
    unsigned char pad4C8[12]; int transition; float inputSpeed, strafeSpeed;
    unsigned char pad4E0[16]; DriveVector jumpDirection;
    unsigned char pad500[0x20]; float recoveryRate; short special;
    unsigned char pad526[7]; unsigned char useCurrentSpeed;
    unsigned char pad52E[0xA60 - 0x52E]; DriveVector pending;
    unsigned char padA70[0x14]; float pendingDamping;
    unsigned char padA88[0xC38 - 0xA88]; float plane;
    unsigned char padC3C[0x1440 - 0xC3C]; DriveVector savedDirection;
    unsigned char pad1450[4]; short overrideDirection;
    unsigned char pad1456[2]; float savedHeading;
    unsigned char pad145C[0x2294 - 0x145C]; int state;
    unsigned char pad2298[4]; int mode;
    unsigned char pad22A0[0x22C3 - 0x22A0]; unsigned char axisMode;
    unsigned char pad22C4[0x24B8 - 0x22C4]; float animationSpeed;
} PlayerDriveView;
extern PlayerDriveView g_hero_state;
/* Resident subview at the velocity vector; targetSpeed is 0xC4 bytes later. */
typedef struct DriveVelocityView {
    DriveVector velocity;
    unsigned char pad10[0xC4 - 0x10]; float targetSpeed;
} DriveVelocityView;
extern DriveVelocityView D_00189F10;
extern int D_L07_001A8FF0 MACRO_ADDR;
extern float D_L07_001A7DC0 MACRO_ADDR;
/* The settings prefix ends at the observed direction vector. */
typedef struct DriveSettings {
    unsigned char pad0[0x158]; float heading;
    unsigned char pad15C[0x370 - 0x15C]; DriveVector direction;
} DriveSettings;
extern DriveSettings D_L07_001B90C0;
extern void hero_build_move_impulse(float, float);
extern void hero_approach_speed(float, float);
extern void hero_steer_heading(int, float, float, float);
extern void hero_approach_velocity(float);
extern void cam_offset_point_by_side_direction(DriveVector *, DriveVector *, float);
extern void cam_set_view_space_height(DriveVector *, DriveVector *, float);
extern void cam_set_view_space_vector_length(void *, const void *, float);
extern float cam_get_view_space_vector_length(char *);
extern float ApproachValue(float *, float, float);
extern float math_approach_with_velocity(float *, float *, int, float, float, float, float);
extern float fast_subtract_rotations(float, float);
extern void hero_start_pose_offset(float, float, float);
extern float FastVecDot(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float FastDiffRots(float, float);
extern void FastVecAdd(void *, void *, void *);


/* Update directional movement, including the state-44 yaw spring.
 * Shares the resident views and locomotion arms with func_L01_002B7360. */
void UpdateHeroVelocityForStateWithYawSpring(void)
{
    union { DriveVector q; float f[4]; } local;
    float smoothed;
    float oldHeading;
    int state = g_hero_state.state;

    if (state == 10) {
        hero_build_move_impulse(0.7f, 0.0f);
        qcopy(&g_hero_state.pendingResult, &g_hero_state.pending);
        g_hero_state.targetSpeed = g_hero_state.planarDistance;
    } else if (state == 16) {
        float speed;
        PlayerDriveView *hero = &g_hero_state;
        if (g_hero_state.frame > 54) {
            ApproachValue((float *)(&g_hero_state.recoveryRate), 0.0069444445f, 0.0019444445f);
        }
        if (g_hero_state.frame <= 54) speed = g_hero_state.recoverySpeed;
        else speed = 0.058333337f;
        hero->speed = speed;
        hero_approach_speed(0.012222223f, 0.0125f);
        cam_set_view_space_vector_length(&D_00189F10.velocity, &D_00189F10.velocity, 0.0f);
        cam_offset_point_by_side_direction((DriveVector *)(&D_00189F10.velocity), (DriveVector *)(&D_00189F10.velocity), D_00189F10.targetSpeed);
    } else if (state == 27) {
        if (g_hero_state.frame > 40) {
            hero_steer_heading(0, 0.04f, 0.2f, 0.250163913f);
            hero_approach_velocity(0.0055555557f);
        }
        if (13.0f <= g_hero_state.plane && g_hero_state.plane <= 30.0f) {
            if (27.0f < g_hero_state.plane)
                ApproachValue((float *)(&g_hero_state.lateralSpeed), 0.0f, 0.0022222223f);
            else ApproachValue((float *)(&g_hero_state.lateralSpeed), 0.033333335f, 0.0022222223f);
        }
        local.f[0] = g_hero_state.lateralSpeed;
        local.f[1] = 0.0f;
        local.f[2] = FastVecDot(&g_hero_state.velocity, &g_hero_state.basis);
        matrix_mul_vec3(&g_hero_state.velocity, &local, &g_hero_state);
    } else if (state == 11) {
        g_hero_state.heading = g_hero_state.targetHeading;
        qcopy(&g_hero_state.direction, &g_hero_state.targetDirection);
        hero_steer_heading(0, 0.04f, 0.2f, 0.11635530f);
        if (g_hero_state.transition != 3) g_hero_state.targetSpeed = g_hero_state.inputSpeed;
        else g_hero_state.targetSpeed = 0.0f;
        if (g_hero_state.useCurrentSpeed != 0) {
            float rate = g_hero_state.animationSpeed * 0.083333336f;
            if (rate < 0.033333335f) rate = 0.033333335f;
            ApproachValue((float *)(&g_hero_state.strafeSpeed), rate, 0.010277778f);
            g_hero_state.targetSpeed = g_hero_state.planarDistance;
        } else {
            if (g_hero_state.allowAction != 0 && g_hero_state.actionFrame <= 11)
                ApproachValue((float *)(&g_hero_state.strafeSpeed), 0.0f, 0.0022222223f);
            else ApproachValue((float *)(&g_hero_state.strafeSpeed), 0.07f, 0.0022222223f);
        }
        if (g_hero_state.axisMode == 0) {
            ((float *)&g_hero_state.velocity)[0] = math_fast_sin_or_cos_a(g_hero_state.inputHeading);
            ((float *)&g_hero_state.velocity)[0] *= g_hero_state.strafeSpeed;
            ((float *)&g_hero_state.velocity)[1] = math_fast_sin_or_cos_b(g_hero_state.inputHeading);
            ((float *)&g_hero_state.velocity)[1] *= g_hero_state.strafeSpeed;
        } else {
            cam_set_view_space_vector_length(&local, &g_hero_state.localDirection, g_hero_state.strafeSpeed);
            cam_set_view_space_height(&local.q, &local.q, 0.0f);
            cam_set_view_space_vector_length(&g_hero_state.velocity, &g_hero_state.velocity, 0.0f);
            FastVecAdd(&g_hero_state.velocity, &g_hero_state.velocity, &local);
        }
        if (g_hero_state.axisMode == 0 && g_hero_state.useCurrentSpeed == 0) {
            float angle = FastDiffRots(g_hero_state.targetHeading, g_hero_state.inputHeading);
            float cosine = math_fast_sin_or_cos_b(angle);
            float amount = g_hero_state.inputSpeed * cosine;
            float component = math_fast_sin_or_cos_a(g_hero_state.targetHeading);
            ((float *)&g_hero_state.velocity)[0] += component * amount;
            component = math_fast_sin_or_cos_b(g_hero_state.targetHeading);
            ((float *)&g_hero_state.velocity)[1] += component * amount;
        }
        hero_build_move_impulse(0.7f, 0.0f);
        qcopy(&g_hero_state.pendingResult, &g_hero_state.pending);
    } else if (state == 17) {
        g_hero_state.heading = ((float *)&g_hero_state.jumpDirection)[3];
        qcopy(&g_hero_state.direction, &g_hero_state.jumpDirection);
        if (g_hero_state.frame > 9) hero_steer_heading(-1, 0.042f, 0.2f, 0.19780402f);
        if (g_hero_state.frame > 8) {
            if (g_hero_state.request == 0) {
                ((float *)&g_hero_state.velocity)[0] = math_fast_sin_or_cos_a(g_hero_state.heading);
                ((float *)&g_hero_state.velocity)[0] *= 0.08166667f;
                ((float *)&g_hero_state.velocity)[1] = math_fast_sin_or_cos_b(g_hero_state.heading);
                ((float *)&g_hero_state.velocity)[1] *= 0.08166667f;
            } else {
                cam_set_view_space_vector_length(&g_hero_state.velocity, &g_hero_state.velocity, 0.0f);
                vec_scale_to_length(&local, &g_hero_state.direction, 0.08166667f);
                FastVecAdd(&g_hero_state.velocity, &g_hero_state.velocity, &local);
            }
        }
        g_hero_state.targetSpeed = g_hero_state.planarDistance;
    } else if (state == 129 && D_L07_001A8FF0 == 0) {
        hero_steer_heading(0, 0.04f, 0.2f, g_hero_state.acceleration);
        g_hero_state.targetSpeed = 0.0f;
    } else {
        if (g_hero_state.state == 44) {
            float angle = g_hero_state.rotation;
            float delta;
            g_hero_state.yawError = math_approach_with_velocity(&angle, &g_hero_state.yawRate, 0,
                g_hero_state.heading, 0.017999999225139618f, 0.2f, 0.12217307090759277f);
            delta = fast_subtract_rotations(angle, g_hero_state.rotation);
            hero_start_pose_offset(0.0f, 0.0f, delta);
        } else {
            oldHeading = g_hero_state.heading;
            qcopy(&local, &g_hero_state.direction);
            if (g_hero_state.overrideDirection != 0) {
                g_hero_state.heading = D_L07_001B90C0.heading;
                qcopy(&g_hero_state.direction, &D_L07_001B90C0.direction);
            }
            hero_steer_heading(0, 0.04f, 0.2f, g_hero_state.acceleration);
            if (g_hero_state.overrideDirection != 0) {
                g_hero_state.savedHeading = oldHeading;
                qcopy(&g_hero_state.savedDirection, &local);
                g_hero_state.heading = oldHeading;
                qcopy(&g_hero_state.direction, &g_hero_state.savedDirection);
            }
        }
        hero_build_move_impulse(0.7f, 0.0f);
        qcopy(&g_hero_state.pendingResult, &g_hero_state.pending);
        {
            float damping = 0.0055555557f;
            if (g_hero_state.speed < D_L07_001A7DC0 * 0.00333333365f) {
                if (g_hero_state.mode == 2) {
                    float rate = g_hero_state.pendingDamping;
                    smoothed = cam_get_view_space_vector_length((char *)&g_hero_state.velocity);
                    ApproachValue(&smoothed, 0.0f, rate);
                    cam_set_view_space_vector_length(&g_hero_state.velocity, &g_hero_state.velocity, smoothed);
                    return;
                }
                if (g_hero_state.contact != 0) damping = 0.00305555575f;
                else if (g_hero_state.special != 0) damping = 0.00055555557f;
                else damping = 0.0022222223f;
            }
            hero_approach_velocity(damping);
        }
    }
}

/* func_L07_00321D68 is in its qualified quadword-copy unit. */


/* Looks up an entry by index and runs its handler. Returns -1 when the index is missing. */
int table_run_entry_by_index(int index)
{
    char *entry;

    if (index == -1)
        return -1;
    entry = *(char **)(D_L07_001FDEC0 + index * 4);
    if (entry == 0)
        return -1;
    func_338D68(entry);
    return 0;
}



/* Moves a bouncing projectile one step. On a hit it splashes or bounces, and when it ends it sets off its explosion. */
void bouncing_l07_projectile_update(unsigned char *obj) {
    struct {
        Vec old, velocity, normal;
        struct {
            Vec vector;
            char *moby;
            int flags;
            unsigned char kind, active;
            unsigned short class_id;
            float material;
            int enabled;
        } packet;
        Vec position, spread;
    } frame;
    char *ctx = *(char **)(obj + 0x68), *position = (char *)obj + 0x10;
    int i, lifetime;
    float angle, speed;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    FastVecAdd(position, ctx, position);
    part_steer_effect_direction(*(int *)(ctx + 0x1C), ctx, 0);
    vec_transform_or_copy(position, position);
    shop_trigger_current_state_effect(ctx, ctx);
    vec_add_object_direction_scaled(position, ctx, 0.0030555557f);
    part_emit_sparkle(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material =
        ((Material *)((u32)g_weapon_l00_table + g_item_slot_to_record[12] * sizeof(Material)))->material;
    qcopy(&frame.packet.vector, ctx);
    vec_fast_normalize_helper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.kind = 2;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.active = 1;
    if (CollLine(&frame.old, position, 0x10, obj, &frame.packet)) {
        if (!GetCollHitMaterial() && *(float *)(ctx + 8) < 0.0f) {
            char *effect;
            Vec *spread;
            RippleDisturb(D_L00_001B2630, D_L00_001B2638, 1,
                *(float *)(obj + 0x10), *(float *)(obj + 0x14), 0.5f, -0.35f);
            *(int *)(ctx + 0x14) = 1;
            vec_clear_128(ctx);
            *(float *)(ctx + 8) = -0.025000002f;
            frame.position.f[0] = *(float *)(obj + 0x10);
            frame.position.f[1] = *(float *)(obj + 0x14);
            frame.position.f[2] = g_collision_result.point.f[2];
            effect = moby_spawn_scaled_effect(&frame.position, 2.0f);
            if (effect)
                effect[0x23] = 0x70;
            spread = &frame.spread;
            i = 15;
            do {
                --i;
                angle = math_random_angle();
                speed = math_random_float_range(0.0f, 0.050000004f);
                frame.spread.f[0] = math_fast_sin_or_cos_a(angle) * speed;
                frame.spread.f[1] = math_fast_sin_or_cos_b(angle) * speed;
                frame.spread.f[2] = math_random_float_range(0.050000004f, 0.10833334f);
                lifetime = math_random_int_range(90, 120);
                part_spawn_spark_2(&frame.position, spread, math_random_int_below(2), lifetime);
            } while (i >= 0);
        } else {
            /* The hit branch re-reads the collision record through its own pointer and has its
               own copy of the response; jump optimization merges the two identical responses.
               This shape gives retail's reload of the hit moby and its register assignment. */
            Collision *collision = &g_collision_result;
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == MOBY_CLASS_BOMB_GLOVE) && *(int *)(ctx + 0x18) > 0x121)
                    goto finish;
                reread = &g_collision_result;
                model = reread->hit;
                if (*(int *)(model + 0x64) == D_L00_001AC850 && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &reread->point);
                vec_fast_normalize(&frame.velocity, ctx, &reread->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
                vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
            } else {
                if (collision->count < 1)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &collision->point);
                vec_fast_normalize(&frame.velocity, ctx, &collision->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
                vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
            }
        }
    } else if (math_fast_float_d(ctx + 0x18)) {
        obj[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, ctx);
    }
finish:
    if (obj[0xBC]) {
        table_clear_entry_flag(*(int *)(ctx + 0x1C));
        part_spawn_big_explosion(obj, &frame.velocity, &frame.normal);
    }
}


/* Moves a bouncing projectile one step, like the other one, but counts steps and picks between two explosions. */
void bouncing_projectile_update_counted(char *obj) {
    struct {
        Vec velocity, normal, old, surface;
        struct {
            Vec vector;
            char *moby;
            int flags;
            unsigned char kind, active;
            unsigned short class_id;
            float material;
            int enabled;
        } packet;
    } frame;
    char *ctx = *(char **)(obj + 0x68);
    char *position = obj + 0x10;
    char *hit;
    Collision *collision;

    frame.velocity.q = 0;
    frame.velocity.f[2] = 0.033333335f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    FastVecAdd(position, position, ctx);
    cam_compute_view_direction(position, &frame.surface, 0);
    FastVecScale(&frame.surface, &frame.surface, 0.0003055556f);
    part_spawn_spark_puff(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0x122)
        frame.packet.flags = 0x830001;
    frame.packet.enabled = 1;
    frame.packet.material = (D_00139574 + g_weapon_l00_table)->material;
    qcopy(&frame.packet.vector, ctx);
    vec_fast_normalize_helper(&frame.packet.vector, &frame.packet.vector, 1.0f);
    frame.packet.kind = 2;
    frame.packet.vector.f[3] = 5627.925f;
    frame.packet.class_id = *(unsigned short *)(obj + 0xAA);
    frame.packet.vector.f[2] = 1.0f;
    frame.packet.active = 1;
    (*(int *)(ctx + 0x14))++;
    if (CollLine(&frame.old, position, 0x10, obj, &frame.packet)) {
        collision = &g_collision_result;
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == MOBY_CLASS_BOMB_GLOVE) && *(int *)(ctx + 0x18) >= 0x122)
                goto finish;
            reread = &g_collision_result;
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L00_001AC850 && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
                goto finish;
            obj[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = obj + 0x10;
                qcopy(dest, source);
            }
            vec_fast_normalize(&frame.velocity, ctx, &reread->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &g_collision_result;
            if (collision->count <= 0)
                goto finish;
            obj[0xBC] = 1;
            qcopy(position, &collision->point);
            vec_fast_normalize(&frame.velocity, ctx, &collision->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.033333335f);
            vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (math_fast_float_d(ctx + 0x18)) {
        obj[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, ctx);
    }
finish:
    if (*(unsigned char *)(obj + 0xBC)) {
        table_clear_entry_flag(*(int *)(ctx + 0x1C));
        if (*(int *)(ctx + 0x14) < 20)
            part_spawn_big_explosion(obj, &frame.velocity, &frame.normal);
        else
            part_l00_spawn_impact_burst(obj, &frame.velocity, &frame.normal);
    }
}



extern unsigned short *g_moby_l07_group_lists[];

extern unsigned char *g_moby_l07_array[] __attribute__((sda));

extern int D_L07_001B22F8[] __attribute__((sda));

/* Returns the first entity of the group's id list whose state byte is 1, or 0. */
unsigned char *moby_find_active_in_group(int group) {
    unsigned short *p;
    unsigned char *e;

    for (p = g_moby_l07_group_lists[group];
         (unsigned char)group != 0xFF && group <= D_L07_001B22F8[0] && p != 0 &&
         ((short)p[-1] >= 0 || p == g_moby_l07_group_lists[group]);
         p++) {
        e = g_moby_l07_array[0] + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (e[0x20] == 1)
            return e;
    }
    return 0;
}

/* func_L07_003F6F00 is defined in L07_002B3580-g8.c (it reads five tuning words through $gp). */



/* func_L07_00416510 is defined in L07_00416510-g8.c. */
