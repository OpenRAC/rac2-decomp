#include "include_asm.h"
#include "common.h"
extern void *part_find_owned_effect_slot(void *a0, s32 a1, s32 a2);
extern s32 math_random_int_below(s32 a0);
extern s32 snd_play_from_class_bank(s32 a0, s32 a1, char *a2, s32 a3);
extern void part_spawn_explosion_with_sparks(u8 *a0, void *a1, s32 a2, f32 f12, f32 f13);
extern s32 PlayMobySound(s32 a0, s32 a1, char *a2);
extern void part_spawn_masked_debris(char *a0, s32 a1, f32 *a2, u8 a3, f32 f12, f32 f13, f32 f14,
                        f32 f15);
extern void moby_mark_spawned(char *a0);

extern unsigned char D_00139574;
extern void FastVecScale(void *, void *, float);
extern void part_spawn_spark_puff(void *);
extern void part_l00_spawn_impact_burst(void *, void *, void *);
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char g_item_slot_to_record[];
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int D_L22_001AC790 __attribute__((sda));
extern int D_L22_001B28B0 __attribute__((sda)), D_L22_001B28B8 __attribute__((sda));
extern char D_L22_002645F0[];
extern void part_steer_effect_direction(int, void *, int);
extern void vec_transform_or_copy(void *, void *);
extern void shop_trigger_current_state_effect(void *, void *);
extern void vec_add_object_direction_scaled(void *, void *, float);
extern void part_emit_sparkle(void *);
extern void vec_fast_normalize_helper(void *, void *, float);
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
extern void *part_spawn_spark_2(void *, void *, int, int);
extern void vec_fast_normalize(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int math_fast_float_d(char *);
extern void table_clear_entry_flag(int);
extern void part_spawn_big_explosion(void *, void *, void *);
extern void cam_compute_view_direction(void *, void *, int);
extern void FastVecCross(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern struct { char pad[0x18]; char *target; } D_L22_001C00C0;
extern u8 *g_hero_moby;
extern void QueueMobyImpact(void *, void *);

typedef int TI128 __attribute__((mode(TI)));

extern s32 D_L22_001B2128 __attribute__((sda));
extern u8 D_L22_001A7A78 __attribute__((sda));
extern s32 D_L22_001A903C __attribute__((sda));

extern void func_31FBB8();
extern void func_3300E8();
extern s32 D_L22_0018B6A8 __attribute__((sda));

extern s32 func_2F36F0(s32);
extern void func_2F3720();
extern void func_2F3AB0(void *, void *, void *);
extern void func_2F3D60(void *, void *, f32);
extern void func_2F3A80(void *, void *, void *);
extern void func_2F9E20(s32, s32);
extern void func_32F330(s32, s32);
extern void func_3A2988(void *, f32);
extern void func_2F4788(s32, s32, f32);
extern f32 func_2F4AD0(f32, f32);
extern void func_3167E8(s32, s32, s32);
extern void func_362E98(s32, s32, s32);
extern void func_32AE80(s32, s32);

extern void text_show_message_at_moby(s32, s32, s32);
extern void text_show_message_with_sound(s32, s32, s32);



/* func_L22_00385F40 is in L22_00385F40.c. */

/* Moves a thrown projectile one step. It bounces off what it hits and sprays sparks when it lands in the water or hits the ground. */
void projectile_l22_update_bouncing(unsigned char *moby) {
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
    } work;
    char *vars = *(char **)(moby + 0x68), *position = (char *)moby + 0x10;
    int spark_count, spark_life;
    float angle, speed;

    work.velocity.q = 0;
    work.velocity.f[2] = 0.033333335f;
    work.normal.q = 0;
    work.normal.f[2] = 1.0f;
    qcopy(&work.old, position);
    FastVecAdd(position, vars, position);
    part_steer_effect_direction(*(int *)(vars + 0x1C), vars, 0);
    vec_transform_or_copy(position, position);
    shop_trigger_current_state_effect(vars, vars);
    vec_add_object_direction_scaled(position, vars, 0.0030555557f);
    part_emit_sparkle(moby);
    work.packet.moby = moby;
    work.packet.flags = 0x830000;
    if (*(int *)(vars + 0x18) < 0x122)
        work.packet.flags = 0x830001;
    work.packet.enabled = 1;
    work.packet.material =
        ((Material *)((u32)D_L22_002645F0 + g_item_slot_to_record[12] * sizeof(Material)))->material;
    qcopy(&work.packet.vector, vars);
    vec_fast_normalize_helper(&work.packet.vector, &work.packet.vector, 1.0f);
    work.packet.vector.f[2] = 1.0f;
    work.packet.vector.f[3] = 5627.925f;
    work.packet.kind = 2;
    work.packet.class_id = *(unsigned short *)(moby + 0xAA);
    work.packet.active = 1;
    if (CollLine(&work.old, position, 0x10, moby, (int)&work.packet)) {
        if (!GetCollHitMaterial() && *(float *)(vars + 8) < 0.0f) {
            char *splash;
            Vec *spread;
            RippleDisturb(D_L22_001B28B0, D_L22_001B28B8, 1,
                *(float *)(moby + 0x10), *(float *)(moby + 0x14), 0.5f, -0.35f);
            *(int *)(vars + 0x14) = 1;
            vec_clear_128(vars);
            *(float *)(vars + 8) = -0.025000002f;
            work.position.f[0] = *(float *)(moby + 0x10);
            work.position.f[1] = *(float *)(moby + 0x14);
            work.position.f[2] = ((Collision *)&D_L22_001C00C0)->point.f[2];
            splash = moby_spawn_scaled_effect(&work.position, 2.0f);
            if (splash)
                splash[0x23] = 0x70;
            spread = &work.spread;
            spark_count = 15;
            do {
                --spark_count;
                angle = math_random_angle();
                speed = math_random_float_range(0.0f, 0.050000004f);
                work.spread.f[0] = math_fast_sin_or_cos_a(angle) * speed;
                work.spread.f[1] = math_fast_sin_or_cos_b(angle) * speed;
                work.spread.f[2] = math_random_float_range(0.050000004f, 0.10833334f);
                spark_life = math_random_int_range(90, 120);
                part_spawn_spark_2(&work.position, spread, math_random_int_below(2), spark_life);
            } while (spark_count >= 0);
        } else {
            /* The hit branch re-reads the collision record through its own pointer and has its
               own copy of the response; jump optimization merges the two identical responses.
               This shape gives retail's reload of the hit moby and its register assignment. */
            Collision *collision = ((Collision *)&D_L22_001C00C0);
            char *hit, *model;
            hit = collision->hit;
            if (hit) {
                Collision *reread;
                if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == MOBY_CLASS_BOMB_GLOVE) && *(int *)(vars + 0x18) > 0x121)
                    goto finish;
                reread = ((Collision *)&D_L22_001C00C0);
                model = reread->hit;
                if (*(int *)(model + 0x64) == D_L22_001AC790 && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
                    goto finish;
                moby[0xBC] = 1;
                qcopy(moby + 0x10, &reread->point);
                vec_fast_normalize(&work.velocity, vars, &reread->normal);
                vec_scale_to_length(&work.velocity, &work.velocity, 0.033333335f);
                vec_scale_to_length(&work.normal, &reread->normal, 1.0f);
            } else {
                if (collision->count < 1)
                    goto finish;
                moby[0xBC] = 1;
                qcopy(moby + 0x10, &collision->point);
                vec_fast_normalize(&work.velocity, vars, &collision->normal);
                vec_scale_to_length(&work.velocity, &work.velocity, 0.033333335f);
                vec_scale_to_length(&work.normal, &collision->normal, 1.0f);
            }
        }
    } else if (math_fast_float_d(vars + 0x18)) {
        moby[0xBC] = 1;
        FastVecAdd((char *)&work.velocity, (char *)&work.velocity, vars);
    }
finish:
    if (moby[0xBC]) {
        table_clear_entry_flag(*(int *)(vars + 0x1C));
        part_spawn_big_explosion(moby, &work.velocity, &work.normal);
    }
}


/* Moves a projectile one step along its velocity and bounces it off walls and objects it hits. */
void projectile_update_motion(char *moby) {
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
    } work;
    char *vars = *(char **)(moby + 0x68);
    char *position = moby + 0x10;
    char *hit;
    Collision *collision;

    work.velocity.q = 0;
    work.velocity.f[2] = 0.033333335f;
    work.normal.q = 0;
    work.normal.f[2] = 1.0f;
    qcopy(&work.old, position);
    FastVecAdd(position, position, vars);
    cam_compute_view_direction(position, &work.surface, 0);
    FastVecScale(&work.surface, &work.surface, 0.0003055556f);
    part_spawn_spark_puff(moby);
    work.packet.moby = moby;
    work.packet.flags = 0x830000;
    if (*(int *)(vars + 0x18) < 0x122)
        work.packet.flags = 0x830001;
    work.packet.enabled = 1;
    work.packet.material = ((Material *)D_L22_002645F0 + D_00139574)->material;
    qcopy(&work.packet.vector, vars);
    vec_fast_normalize_helper(&work.packet.vector, &work.packet.vector, 1.0f);
    work.packet.kind = 2;
    work.packet.vector.f[3] = 5627.925f;
    work.packet.class_id = *(unsigned short *)(moby + 0xAA);
    work.packet.vector.f[2] = 1.0f;
    work.packet.active = 1;
    (*(int *)(vars + 0x14))++;
    if (CollLine(&work.old, position, 0x10, moby, (int)&work.packet)) {
        collision = ((Collision *)&D_L22_001C00C0);
        hit = collision->hit;
        if (hit) {
            Collision *reread;
            char *model;
            if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == MOBY_CLASS_BOMB_GLOVE) && *(int *)(vars + 0x18) >= 0x122)
                goto finish;
            reread = ((Collision *)&D_L22_001C00C0);
            model = reread->hit;
            if (*(int *)(model + 0x64) == D_L22_001AC790 && *(short *)(model + 0xAA) != 0x336 /* moby class 822 */)
                goto finish;
            moby[0xBC] = 1;
            {
                void *source = &reread->point;
                void *dest = moby + 0x10;
                qcopy(dest, source);
            }
            vec_fast_normalize(&work.velocity, vars, &reread->normal);
            vec_scale_to_length(&work.velocity, &work.velocity, 0.033333335f);
            vec_scale_to_length(&work.normal, &reread->normal, 1.0f);
        } else {
            collision = ((Collision *)&D_L22_001C00C0);
            if (collision->count <= 0)
                goto finish;
            moby[0xBC] = 1;
            qcopy(position, &collision->point);
            vec_fast_normalize(&work.velocity, vars, &collision->normal);
            vec_scale_to_length(&work.velocity, &work.velocity, 0.033333335f);
            vec_scale_to_length(&work.normal, &collision->normal, 1.0f);
        }
    } else if (math_fast_float_d(vars + 0x18)) {
        moby[0xBC] = 1;
        FastVecAdd((char *)&work.velocity, (char *)&work.velocity, vars);
    }
finish:
    if (*(unsigned char *)(moby + 0xBC)) {
        table_clear_entry_flag(*(int *)(vars + 0x1C));
        if (*(int *)(vars + 0x14) < 20)
            part_spawn_big_explosion(moby, &work.velocity, &work.normal);
        else
            part_l00_spawn_impact_burst(moby, &work.velocity, &work.normal);
    }
}



/* func_L22_003A6620 lives in the -g8 sibling file (it reaches a global through $gp). */



/* func_L22_003D0840 is in L22_003D0840.c. */

/* func_L22_003E87B8 is in L22_003E87B8.c. */

/* Shows the message effect for this object and clears one of its flags. */
void text_show_message_clear_flag(s32 moby) {
    s32 vars_ptr = *(u32 *)(moby + 0x68);

    text_show_message_at_moby(moby, vars_ptr, vars_ptr);
    *(u8 *)(moby + 0x30) = 0xFF;
}

/* Shows a text message with a sound at the object and starts its effect. Does nothing if the object has no target. */
void text_show_message_with_sound(s32 moby_addr, s32 unused1, s32 unused2)
{
    char *moby = (char *)moby_addr;
    char *target = part_find_owned_effect_slot(moby, -1, 0);
    char offset[0x10];

    if (target == 0)
        return;
    snd_play_from_class_bank(math_random_int_below(3) + 0xC, 0, moby, 0xE0B);
    part_spawn_explosion_with_sparks((u8 *)moby, moby + 0x10, -1, 2.0f, 13.0f);
    PlayMobySound(0, 0, moby);
    func_2F3D60(offset, target + 0x10, 0.25f);
    part_spawn_masked_debris(moby, 3, (f32 *)offset, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
    moby_mark_spawned(moby);
}


/* Shows the message effect with sound for this object and clears one of its flags. */
void text_show_message_sound_clear_flag(s32 moby) {
    s32 vars_ptr = *(u32 *)(moby + 0x68);

    text_show_message_with_sound(moby, vars_ptr, vars_ptr);
    *(u8 *)(moby + 0x30) = 0xFF;
}


/* func_L22_0040C888 is in L22_0040C888-g8.c. */

/* func_L22_0040D638 lives in L22_00358778-state-g8.c. */

/* Updates the timers and animation of an object each frame, and ages it by one tick. */
void flyer_update_timers_anim(s32 moby) {
    s32 moby_copy = moby;
    s32 vars = *(u32 *)(moby_copy + 0x68);

    func_2F36F0(vars + 0x258);
    func_2F3720(vars + 0x25C);
    if (*(u16 *)(moby_copy + 0x96) <= 0xFFFE)
        *(u16 *)(moby_copy + 0x96) = *(u16 *)(moby_copy + 0x96) + 1;
    if (*(u8 *)(vars + 0x211) == 0)
        func_3167E8(moby_copy, 7, vars + 0x210);
    func_2F4788(vars + 0x220, 2, *(f32 *)(vars + 0x26C));
    *(f32 *)(vars + 0x26C) = func_2F4AD0(*(f32 *)(vars + 0x26C), 0.41597018f);
}


/* Steers an object toward a target position, scaled by speed and the frame time. */
void moby_l22_steer_toward_target(s32 moby, s32 target, s32 use_offset, f32 speed) {
    u8 steer[0x10];
    u8 adjusted[0x10];
    f32 step = speed;

    func_2F3AB0(steer, (void *)target, (void *)(moby + 0x10));
    step = step * 0.016666668f;
    func_2F3D60(steer, steer, step);
    if (use_offset != 0) {
        func_2F3A80(adjusted, (void *)(moby + 0x10), steer);
        func_3A2988(adjusted, 7.2f);
        func_2F3AB0(steer, adjusted, (void *)(moby + 0x10));
        func_2F3D60(steer, steer, step);
    }
    func_32F330(moby, target);
    func_3300E8(moby, steer);
}

/* The existing implementation is in L22_0040DD20-rc2.c. */

/* Spawns moby 0xF5D at pos moving along vel: copies both in, sets its colour and life
   from *scale, and builds its three-point trail (vel, vel + offset from the pos's
   reference point, and that again) with zeroed fourth components. */
typedef struct {
    float vel[4];
    int life;
    int f14;
    int f18;
    float scale;
} TrailVars0040DE00;
typedef struct {
    u8 pad0[0x10];
    float pos[4];
    u8 flag20;
    u8 pad21[0xF];
    u8 alpha;
    u8 pad31;
    short colour;
    u8 pad34[0x34];
    TrailVars0040DE00 *vars;
    u8 pad6C[0x54];
    float p0[4];
    float p1[4];
    float p2[4];
} TrailMoby0040DE00;
extern void cam_compute_view_direction(void *, void *, int);
extern TrailMoby0040DE00 *CreateMoby(int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);

/* Creates a trail effect object at a position moving along a velocity, and fills in its size, lifetime and three trail points. */
TrailMoby0040DE00 *part_spawn_trail_effect(float *pos, float *vel, float *scale)
{
    float ref[4];
    float scaled[4];
    TrailMoby0040DE00 *moby;
    TrailVars0040DE00 *vars;

    cam_compute_view_direction(pos, ref, 1);
    moby = CreateMoby(0xF5D /* moby class 3933 */);
    if (moby != 0) {
        vars = moby->vars;
        vars->scale = *scale;
        vars->life = 0x50;
        moby->alpha = 0xFF;
        moby->colour = 0xFF;
        moby->flag20 = 0;
        qcopy(moby->pos, pos);
        qcopy(vars->vel, vel);
        vars->f18 = 0;
        vars->f14 = 0;
        vec_scale_to_length(scaled, vel, 1.0f);
        qcopy(moby->p0, scaled);
        FastVecCross(moby->p1, moby->p0, ref);
        vec_scale_to_length(moby->p1, moby->p1, 1.0f);
        FastVecCross(moby->p2, moby->p1, moby->p0);
        moby->p0[3] = moby->p1[3] = moby->p2[3] = 0.0f;
    }
    return moby;
}

extern u8 *D_L22_001AF314[] __attribute__((sda));
extern f32 D_L22_001B2A98 __attribute__((sda));
extern void moby_transform_joint_to_world(void *, s32, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);

/* Spawns two trail effects at the object's joints, flying away from an origin point. */
void part_spawn_joint_trails(u8 *moby, f32 *origin, f32 size_arg) {
    f32 joint_pos[4] __attribute__((aligned(16)));
    f32 velocity[4] __attribute__((aligned(16)));
    f32 size = size_arg;

    if (D_L22_001AF314[0] != 0 && *(f32 *)(*(u8 **)(D_L22_001AF314[0] + 0x68) + 0x20) <= 0.0f) {
        return;
    }
    moby_transform_joint_to_world(moby, 2, joint_pos);
    if (size == 0.0f) {
        size = D_L22_001B2A98;
    }
    FastVecSub(velocity, origin, joint_pos);
    vec_scale_to_length(velocity, velocity, 0.6666667f);
    part_spawn_trail_effect(joint_pos, velocity, &size);
    moby_transform_joint_to_world(moby, 3, joint_pos);
    FastVecSub(velocity, origin, joint_pos);
    vec_scale_to_length(velocity, velocity, 0.6666667f);
    part_spawn_trail_effect(joint_pos, velocity, &size);
}

typedef struct { u8 pad[0x18]; u8 *target; } G1C00C0;
extern G1C00C0 D_001C00C0;
extern u8 *g_hero_moby;
extern int CollLine(void *, void *, int, void *, int);
extern void vec_scale_to_length(void *, void *, f32);
extern void make_hit_descriptor(void *, void *, int, void *, f32);
extern void QueueMobyImpact(void *, void *);
extern void part_start_random_scale_effect(void *, s32, s32);

/* Checks whether the object hit something since its last position. If so it hurts the target, spawns the impact effect and goes to state 2. */
void projectile_check_hit_explode(u8 *moby, u8 *old_pos) {
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 hit_dir[16] __attribute__((aligned(16)));
    u8 hit_event[0x30] __attribute__((aligned(16)));
    u8 impact_pos[16] __attribute__((aligned(16)));
    u8 *target;

    if (CollLine(old_pos, moby + 0x10, 0, moby, 0) == 0) {
        return;
    }
    target = D_001C00C0.target;
    if (target == 0) {
        return;
    }
    if (*(s16 *)(target + 0xAA) == 0xEDD /* moby class 3805 */ || *(s16 *)(target + 0xAA) == 0xE0B /* moby class 3595 */) {
        return;
    }
    if (target == g_hero_moby && !(*(f32 *)(vars + 0x1C) < 50.0f)) {
        return;
    }
    if (*(f32 *)(vars + 0x1C) >= 50.0f) {
        *(f32 *)(vars + 0x1C) = 50.1f;
    }
    vec_scale_to_length(hit_dir, vars, 1.0f);
    make_hit_descriptor(hit_event, moby, 0x8B0003, hit_dir, *(f32 *)(vars + 0x1C));
    hit_event[0x18] = 5;
    hit_event[0x19] = 3;
    *(u16 *)(hit_event + 0x1A) = *(u16 *)(moby + 0xAA);
    QueueMobyImpact(D_001C00C0.target, hit_event);
    part_start_random_scale_effect(moby + 0x10, 10, 1);
    if (D_001C00C0.target == 0) {
        qcopy(impact_pos, moby + 0x10);
        part_start_random_scale_effect(impact_pos, 15, 0);
    }
    moby[0x20] = 2;
}

/* func_L22_0040E098 uses the profile in L22_0040E098-g8.c. */

/* func_L22_0040F1C0 is in L22_00358778-f7-g8.c. */

/* func_L22_004135F8 is in L22_004135F8-g8.c. */

/* func_L22_00413B70 is in L22_00413B70-g8.c. */


