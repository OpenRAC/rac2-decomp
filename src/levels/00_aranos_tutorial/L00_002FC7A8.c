#include "include_asm.h"
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union {
    Quad q;
    float f[4];
} Vec;

typedef struct {
    char pad00[0x24];
    float f24;
} AranosModel;

/* Context of the child objects spawned by func_L00_003CFB00. */
typedef struct {
    char pad00[4];
    float f04;
    char pad08[0x48];
    int f50;
} AranosChildCtx;

/* The generic object these functions work on: position at 0x10, state at 0x20, context at 0x68. */
typedef struct AranosMoby {
    char pad00[0x10];
    Vec position;
    unsigned char state;
    char pad21[2];
    unsigned char f23;
    AranosModel *model;
    char pad28[4];
    float f2C;
    char pad30;
    unsigned char f31;
    char pad32[2];
    unsigned short flags;
    char pad36[0x2E];
    void (*hook)(void *);
    void *ctx;
    char pad6C[0x10];
    unsigned short f7C;
    char pad7E[0x1A];
    int f98;
    char pad9C[0xC];
    unsigned char fA8;
    char padA9;
    short classId;
    char padAC[0x14];
    char matrix[0x30];
    Vec rotation;
} AranosMoby;

extern float g_effect_fade_value_a __attribute__((sda));
extern float g_effect_fade_value_b __attribute__((sda));
extern void *part_find_owned_effect_slot(void *, unsigned int, int);
extern int flag_set_first_pending(void *);
extern void moby_set_state(void *, int, int);
extern void euler_rotation_basis(void *, void *);
extern void vec_random_direction(void *, float, float);
extern int coll_scatter_points_in_shapes(void *, int, void *, int, float);
extern int snd_play_from_class_bank(int, int, void *, int);
extern char *moby_l00_spawn_child(void *, int, int);
extern AranosMoby *cam_moby_create(void *, int, int, int, void *, void *, void *, unsigned char, float, float);
extern void glow_fade_update(void *);
extern void set_moby_color(void *, unsigned char, unsigned char, unsigned char);

extern char g_hero_position[];
extern int IsPointInCuboid(char *, unsigned int);
extern void moby_mark_spawned(void *);
extern int PlayMobySound(int, int, void *);

extern unsigned char g_bouncing_weapon_index;
extern void FastVecScale(void *, void *, float);
extern void cam_compute_view_direction(void *, void *, int);
extern void part_l00_spawn_impact_burst(void *, void *, void *);
extern void part_spawn_spark_puff(void *);

typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char g_item_slot_to_record[];
extern char *g_hero_moby NOT_SDA;
/* sda: one `lw` macro instruction at -G0, scheduled as a single load as in retail. */
extern int g_projectile_model_ref __attribute__((sda));
extern int g_ripple_object __attribute__((sda)), g_ripple_param __attribute__((sda));
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
extern void *part_spawn_spark_2(void *, void *, int, int);
extern void vec_fast_normalize(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int math_fast_float_d(void *);
extern void table_clear_entry_flag(int);
extern void part_spawn_big_explosion(void *, void *, void *);

extern void *part_alloc(int);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern unsigned char *g_aranos_spark_table[];
typedef int TI128 __attribute__((mode(TI)));

/* Per-spark data after the common header: velocity, fade rate and colour. */
typedef struct {
    Vec velocity;
    float duration;
    int rgb;
    int color;
    unsigned short step;
} AranosSparkTail;

/* A spark particle object. */
typedef struct {
    char pad00;
    unsigned char f01;
    unsigned char f02;
    unsigned char f03;
    int rgb;
    unsigned char f08;
    unsigned char f09;
    unsigned short frames;
    float f0C;
    Vec position;
    AranosSparkTail tail;
} AranosSpark;

/* Allocates a spark at the given position and velocity; the last arguments set its life, step and colour. */
void *aranos_spark_spawn(TI128 *position, TI128 *velocity, int frames, int step, int color, float scale) {
    AranosSpark *obj;
    AranosSparkTail *cursor;

    obj = part_alloc(0x30);
    if (obj != 0) {
        qcopy_nc(&obj->position, position);
        cursor = &obj->tail;
        obj->rgb = color & 0x00FFFFFF;
        obj->f09 = FloatToInt(2.0f) + 0x10;
        obj->f03 = 0x44;
        obj->f01 = 0;
        obj->f02 = g_aranos_spark_table[0][0];
        obj->f0C = scale * 210000.0f;
        obj->f08 = math_random_int_below(0x100);
        qcopy_nc(cursor, velocity);
        cursor->duration = 2.0f / IntToFloat(frames);
        obj->frames = frames;
        cursor->step = step;
        cursor->rgb = color & 0x00FFFFFF;
        cursor->color = color;
    }
    return obj;
}


extern void FastVecAdd(void *, void *, void *);
extern float math_fabs(float);
extern float IntToFloat(int);
extern int FastTweenColor(char *, char *, float);
extern int FastDecTimer(char *);
extern void part_kill(void *);

/* Moves a spark, fades it out over time and removes it when its life runs out. */
void aranos_spark_update(char *obj) {
    char *tail = obj + 0x20;
    obj[8] += tail[0x1C];
    FastVecAdd(obj + 0x10, obj + 0x10, tail);
    *(int *)(obj + 4) = FastTweenColor(*(char **)(tail + 0x18), *(char **)(tail + 0x14),
        math_fabs(IntToFloat(*(short *)(obj + 0x0A)) * *(float *)(tail + 0x10) - 1.0f));
    if (FastDecTimer(obj + 0x0A) != 0) {
        part_kill(obj);
    }
}


extern unsigned int g_equipment_bits __attribute__((sda));
extern void ship_spawn_engine_flame(void *, int, int);
extern void part_draw_effect_records(void);

/* Draws the object once, or three times when a special display mode is on. */
void gfx_draw_object_multi_pass(void *obj) {
    int count;
    int i;
    count = 1;
    if (((g_equipment_bits >> 4) & 1) != 0) count = 3;
    i = 0;
    while (i < count) {
        ship_spawn_engine_flame(obj, i, 1);
        i++;
    }
    part_draw_effect_records();
}



/* AranosMoby.matrix as the three rows it holds. */
typedef struct { char pad[0xC0]; float matrix[3][4]; } AranosMatrixView;

extern AranosMoby *g_launch_moby_list[];
extern int g_game_l00_mode __attribute__((sda));
extern void moby_transform_joint_point(void *, int, void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void mat_get_euler_angles(void *, void *);
extern void func_002A10E8(void *);

/* Moves every attached object of the null-terminated list onto obj, taking its orientation. */
void SnapMobyListToParent(AranosMoby *obj) {
    Vec position, rotation;
    float matrix[4][4];
    Vec transformed, offset;
    int i = 0, j;
    Vec *source;

    if (g_launch_moby_list[0]) {
        do {
            g_launch_moby_list[i]->flags &= 0xFFBE;
            g_launch_moby_list[i]->flags |= 0x1000;
            g_launch_moby_list[i]->f98 = *(int *)((char *)g_launch_moby_list[i]->model + 0x10);
            /* Retail stores these two saves and never reads them back. */
            qcopy_nc(&position, &g_launch_moby_list[i]->position);
            qcopy_nc(&rotation, &g_launch_moby_list[i]->rotation);
            /* A statement of its own: the longer life lets loop hoist it on its first pass. */
            source = &obj->position;
            qcopy(&g_launch_moby_list[i]->position, source);
            moby_transform_joint_point(obj, 0, matrix);
            for (j = 0; j < 3; j++) {
                float *row = matrix[j];
                ((AranosMatrixView *)g_launch_moby_list[i])->matrix[j][0] = row[0];
                ((AranosMatrixView *)g_launch_moby_list[i])->matrix[j][1] = row[1];
                ((AranosMatrixView *)g_launch_moby_list[i])->matrix[j][2] = row[2];
            }
            if (g_game_l00_mode == 2) {
                offset.q = 0;
                offset.f[0] = -4.1919f;
                offset.f[2] = -1.355f;
                moby_transform_joint_to_world(obj, 1, &transformed);
                matrix_mul_vec3(&offset, &offset, g_launch_moby_list[i]->matrix);
                FastVecAdd(&transformed, &transformed, &offset);
                qcopy(&g_launch_moby_list[i]->position, &transformed);
            }
            mat_get_euler_angles(g_launch_moby_list[i]->matrix, &g_launch_moby_list[i]->rotation);
            func_002A10E8(g_launch_moby_list[i]);
            if (g_game_l00_mode != 0) {
                g_launch_moby_list[i]->f98 = 0;
            } else if (obj->f98) {
                g_launch_moby_list[i]->f98 = *(int *)((char *)g_launch_moby_list[i]->model + 0x10);
            }
            i++;
        } while (g_launch_moby_list[i]);
    }
}

/* Moves a falling projectile, bounces it off surfaces it hits and spawns hit effects when it lands. */
void projectile_falling_update(unsigned char *obj) {
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
            RippleDisturb(g_ripple_object, g_ripple_param, 1,
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
                if (*(int *)(model + 0x64) == g_projectile_model_ref && *(short *)(model + 0xAA) != 0x336)
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

/* Moves a bouncing projectile and passes each hit on to the impact code, using a different one after 20 bounces. */
void projectile_bouncing_update(char *obj) {
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
    frame.packet.material = (g_bouncing_weapon_index + g_weapon_l00_table)->material;
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
            if (*(int *)(model + 0x64) == g_projectile_model_ref && *(short *)(model + 0xAA) != 0x336)
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


/* The level's copy of func_003173B0 (src/game/003173B0.c): same instructions, its own path table. */
extern float FastAddRotations(float angle, float step);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern void anim_start_blended(void *, int, int, int);
extern int flyer_init_check_death(char *);
extern int flag_set_second_pending(char *);
extern int moby_dispatch_action_by_kind(char *, char *);
extern void snd_stop_voice(int);
extern void *SpawnExplosion(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern void SetDeathBits(void *, int, int);
extern void moby_mark_spawned(void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float vec_distance_xy(void *, void *);
extern float coll_probe_ground_height_below(void *, int, float);
extern void func_002A677C(void *);
extern int moby_turn_toward_target_and_step(void *, void *, float);
extern int coll_test_hit_at_bone(void *, int, float, float, int, float, int, int, int);
extern void flyer_tick_timers(char *);
extern unsigned char g_sound_state[];
extern unsigned char g_hero_state[];
typedef struct { char pad[0x249C]; char *target; } Hero3173;
extern char *g_launch_path_table[];
#define FI(p,o) (*(int *)((p)+(o)))
#define FF(p,o) (*(float *)((p)+(o)))
#define FH(p,o) (*(short *)((p)+(o)))
#define FU(p,o) (*(unsigned short *)((p)+(o)))
#define FB(p,o) (*(unsigned char *)((p)+(o)))
#define FP(p,o) (*(char **)((p)+(o)))
/* Keeps state 6's transition from cross-jumping into state 10's identical call tail, as
   RAC1 pause.c does for its duplicate start_audio_stream_read_r3/r4 calls. Both names
   have the same EE interface. */
extern void changeMode3173Six(void *, int, int) __asm__("func_002A7750");
/* Updates a path-following enemy that idles, walks toward the player, reacts to hits and explodes when destroyed. */
void path_walker_update(char *self)
{
    char *d = FP(self,0x68);
    int flags, n, i;
    char *sound, *path;
    float target[4], delta[4];
    float f, height, savedHeight;
    /* Written out here and at the end of state 3, not shared through a label: cross-jumping
       merges the two after sched1, which has to see func_0029F338 in the same block as the
       explosion's calls for it to set a3..t3 up before a0..a2. */
    if (flyer_init_check_death(self)) {
        moby_mark_spawned(self);
        return;
    }
    switch (FB(self,0x95)) {
    case 0:
        if (flag_set_second_pending(self))
            moby_set_controller_speed_limits(self,0.006666667f,0.06666667f,0.8377582f,0.8377582f);
        if (FI(d,0x258)==1 && math_fast_float_d(d+0x2A4) && FI(d,0x2AC)) {
            if (FI(d,0x294)==-1) {
                moby_set_state(self,6,2);
                FF(self,0x18)=FF(d,0x28C);
                if (FB(self,0x43)!=2) anim_start_blended(self,2,0,5);
            } else moby_set_state(self,4,2);
        } else if (FH(d,0x276)) {
            moby_set_state(self,3,1);
            FH(d,0x276)=0;
            if (FH(d,0x270)<300) FH(d,0x270)=math_random_int_range(480,600);
        }
        FF(self,0xF8)=FastAddRotations(FF(self,0xF8),0.03490659f);
        break;
    case 1:
        if (flag_set_second_pending(self))
            moby_set_controller_speed_limits(self,0.006666667f,0.06666667f,0.8377582f,0.8377582f);
        if ((FI(d,0x258)==1 || FI(d,0x25C)==1) && FI(d,0x2AC)) {
            if (FI(d,0x294)!=-1) moby_set_state(self,4,2);
            else {
                moby_set_state(self,6,2);
                FF(self,0x18)=FF(d,0x28C);
                if (FB(self,0x43)!=2) anim_start_blended(self,2,0,5);
            }
        }
        FF(self,0xF8)=FastAddRotations(FF(self,0xF8),0.03490659f);
        break;
    case 2:
        if (flag_set_second_pending(self))
            moby_set_controller_speed_limits(self,0.006666667f,0.06666667f,0.8377582f,0.8377582f);
        if (FI(d,0x258)!=1 && FI(d,0x25C)!=1 && FB(self,0x20)!=4) {
            moby_set_state(self,1,1);
            if (FB(self,0x43)) anim_start_blended(self,0,0,20);
            FH(d,0x270)=math_random_int_range(580,600);
        }
        break;
    case 3:
        flags=moby_dispatch_action_by_kind(self,d+0x60);
        if (flags&1) {
            n=FI(d,0x2A8);
            if (n!=-1) {
                sound=(char *)g_sound_state+n*0x70;
                if (FP(sound,0x88)==self && FB(sound,0x74)) snd_stop_voice(n);
            }
            FI(d,0x2A8)=-1;
            SpawnExplosion(self+0x10,0,0,0,0,20,45,1,0.3f,20.0f,1,0,0,0);
            PlayMobySound(0,0,self);
            SetDeathBits(self,0,3);
            moby_mark_spawned(self);
            return;
        }
        if (flags&2) {
            if (FI(d,0x258)==1 || FI(d,0x25C)==1) {
                moby_set_state(self,5,2);
                if (FB(self,0x43)) anim_start_blended(self,0,0,5);
                if (FI(d,0x294)!=-1) moby_set_state(self,4,2);
            } else {
                moby_set_state(self,3,1);
                FH(d,0x270)=math_random_int_range(580,600);
            }
        }
        break;
    }
    switch (FB(self,0x20)) {
    case 1:
        if (FU(self,0x96)>=26) {
            if (FB(self,0x43)) anim_start_blended(self,0,0,5);
            moby_set_state(self,2,-1);
            FF(self,0x18)=FF(d,0x28C);
        } else {
            f=math_fast_sin_or_cos_b((float)FU(self,0x96)*0.12566361f)*0.02f;
            if (FF(self,0x18)>FF(d,0x28C)) FF(self,0x18)-=f;
            else FF(self,0x18)+=f;
        }
        break;
    case 4:
        path=g_launch_path_table[FI(d,0x294)];
        if (FI(d,0x298)>=FI(path,0)) {
            FI(d,0x294)=-1;
            FF(d,0x28C)=coll_probe_ground_height_below(self+0x10,0,0.5f)+0.5f;
            moby_set_state(self,5,-1);
        } else {
            qcopy(target,path+0x10+FI(d,0x298)*16);
            FastVecSub(delta,target,self+0x10);
            vec_scale_to_length(delta,delta,FF(d,0x1C0));
            FastVecAdd(self+0x10,self+0x10,delta);
            if (vec_distance_xy(self+0x10,target)<0.5f) FI(d,0x298)++;
            if (FI(d,0x298)>=FI(path,0)-6 && FF(d,0x1C0)>=0.10000001f)
                FF(d,0x1C0)-=0.0022222223f;
            height=coll_probe_ground_height_below(self+0x10,0,0.5f)+0.5f;
            if (FF(self,0x18)<height) FF(self,0x18)=height;
            FF(d,0x28C)=FF(self,0x18);
            func_002A677C(self);
        }
        FF(self,0xF8)=FastAddRotations(FF(self,0xF8),0.03490659f);
        break;
    case 5:
        savedHeight=FF(self,0x18);
        moby_turn_toward_target_and_step(self,d+0x230,FF(d,0x290));
        FF(self,0x18)=savedHeight;
        if (vec_distance_xy(self+0x10,FP(d,0x240)+0x10)<1.3f) moby_set_state(self,7,-1);
        FF(self,0xF8)=FastAddRotations(FF(self,0xF8),0.03490659f);
        break;
    case 6:
        if (FB(self,0x60)&2) {
            if (FB(self,0x43)!=3) anim_start_blended(self,3,0,5);
            changeMode3173Six(self,8,-1);
        }
        break;
    case 8:
        height=1.75f;
        FF(self,0x48)=height;
        for (i=0;i<4;i++) coll_test_hit_at_bone(self,i,0.17f,FF(d,0x2B0),1,1.0f,0,1,0);
        if (((Hero3173 *)g_hero_state)->target==self) moby_set_state(self,9,-1);
        if (vec_distance_xy(self+0x10,FP(d,0x240)+0x10)>1.3f && (float)FU(self,0x96)>120.0f) {
            if (FB(self,0x43)) anim_start_blended(self,0,0,15);
            moby_set_state(self,5,-1);
            FF(self,0x48)=1.0f;
        }
        break;
    case 9:
        if ((float)FU(self,0x96)>20.0f) {
            moby_set_state(self,10,-1);
            if (FB(self,0x43)!=4) anim_start_blended(self,4,0,5);
            FF(self,0x48)=1.0f;
        }
        break;
    case 10:
        if (FB(self,0x60)&2) {
            if (FB(self,0x43)) anim_start_blended(self,0,0,15);
            moby_set_state(self,5,-1);
        }
        break;
    case 7:
        if (FU(self,0x96)>=30) {
            moby_set_state(self,6,-1);
            if (FB(self,0x43)!=1) anim_start_blended(self,1,0,2);
            FF(self,0x48)=1.0f;
        }
        break;
    }
    if (FB(self,0x20)!=4 && FB(self,0x95)==2 && FF(self,0x18)<FF(d,0x28C)) FF(self,0x18)=FF(d,0x28C);
    flyer_tick_timers(self);
}
#undef FI
#undef FF
#undef FH
#undef FU
#undef FB
#undef FP


/* func_L00_003CD160 is defined in L00_003CD160.c. */

/* func_L00_003CD8E0 is defined in L00_003CD8E0-lift-g8.c. */

/* func_L00_003CE278 is defined in L00_003CE278-update.c. */


/* Context of func_L00_003CF530's object: the flag that starts it and a frame counter. */
typedef struct {
    unsigned int flag;
    int frames;
} AranosDriftCtx;

/* Once its flag is set, drifts the object along its heading for 100 frames, then removes it. */
void aranos_drift_update(AranosMoby *obj) {
    AranosDriftCtx *ctx;
    int result;
    float angle;
    float point[3];

    ctx = obj->ctx;
    if (obj->state == 0) {
        result = IsPointInCuboid(g_hero_position, ctx->flag);
        if (result != 0) {
            obj->state = 1;
            ctx->frames = 0;
            PlayMobySound(0, 0, obj);
        }
    }
    if (obj->state != 1)
        return;
    angle = obj->rotation.f[2];
    point[0] = math_fast_sin_or_cos_a(angle) * 0.4166667f;
    angle = obj->rotation.f[2];
    point[1] = math_fast_sin_or_cos_b(angle) * 0.4166667f;
    point[2] = 0.0f;
    FastVecAdd(&obj->position, &obj->position, point);
    ctx->frames += 1;
    if (ctx->frames < 0x65)
        return;
    moby_mark_spawned(obj);
}


/* func_L00_003CF610 is defined in L00_003CF610-update.c. */

extern float math_random_signed_float_range(float, float);
extern float math_spring_float_to_goal(float *, float *, float, float, float, float);

/* Slowly turns the object to random angles and pauses between turns. */
void random_turner_update(char *obj) {
    char *ctx;
    float limit;
    ctx = *(char **)(obj + 0x68);
    if (*(unsigned char *)(obj + 0x20) == 0) {
        *(float *)(ctx + 8) = math_random_signed_float_range(5.0f, 15.0f);
        *(unsigned char *)(obj + 0x20) = 1;
        *(int *)(ctx + 0x0C) = math_random_int_range(0x3C, 0x78);
        limit = *(float *)(ctx + 8) * 0.017453294f;
        if (*(float *)(obj + 0xF0) < limit) {
            PlayMobySound(0, 0, obj);
        } else {
            PlayMobySound(1, 0, obj);
        }
    }
    if (*(unsigned char *)(obj + 0x20) != 1) return;
    limit = *(float *)(ctx + 8) * 0.017453294f;
    math_spring_float_to_goal((float *)(obj + 0xF0), (float *)ctx, limit,
        0.0008726647356525064f, 0.0008726647356525064f, 0.004363324f);
    euler_rotation_basis(obj + 0xC0, obj + 0xF0);
    if (math_fast_float_d(ctx + 0x0C) != 0) {
        *(unsigned char *)(obj + 0x20) = 0;
    } else if (*(float *)(obj + 0xF0) == *(float *)(ctx + 8) * 0.017453294f) {
        *(unsigned char *)(obj + 0x20) = 0;
    }
}

/* Context of func_L00_003CFB00's object: the sparks it spawned and their decay rates. */
typedef struct {
    AranosMoby *sparks[16];
    float decay[16];
    int hold;
    int timer;
} AranosSparkerCtx;

/* Spawns a burst of sparks around the object, then fades them until the timer runs out. */
void aranos_spark_burst_update(AranosMoby *obj) {
    struct {
        Vec velocity, offset, position;
    } frame;
    AranosSparkerCtx *ctx = obj->ctx;
    AranosMoby *child;
    AranosChildCtx *childctx;
    int type, i;
    float life;

    switch (obj->state) {
    case 0:
        for (i = 15; i >= 0; i--)
            ctx->sparks[i] = 0;
        if (obj->classId == 0xAC9) {
            obj->rotation.f[1] += 0.78539824f;
            euler_rotation_basis(obj->matrix, &obj->rotation);
        }
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(obj, 0x10000, 0) && ctx->hold == 0)
            moby_set_state(obj, 2, -1);
        obj->fA8 = 0xFF;
        return;
    case 2: {
        unsigned char alpha;
        int count = 5, n;

        if (g_effect_fade_value_a < 0.85f && g_effect_fade_value_b < 0.85f)
            count = 14;
        for (n = 0; n < count; n++) {
            vec_random_direction(&frame.offset, 0.85f, 1.95f);
            coll_scatter_points_in_shapes(obj, 1, &frame.position, 0xFFFF, 1000.0f);
            FastVecAdd(&frame.offset, &frame.offset, &frame.position);
            frame.velocity.f[2] = math_random_float_range(0.0f, 5.0f) * 0.016666668f;
            frame.velocity.f[1] = math_random_float_range(-6.0f, 6.0f) * 0.016666668f;
            if (math_random_int_below(4)) {
                type = 1;
                ctx->decay[n] = math_random_float_range(20.0f, 40.0f) * 0.00027777778f;
                frame.velocity.f[0] = math_random_float_range(-8.0f, -4.0f) * 0.016666668f;
                life = math_random_float_range(5.0f, 10.0f);
            } else {
                type = 2;
                ctx->decay[n] = 0.0f;
                frame.velocity.f[0] = math_random_float_range(2.0f, 4.0f) * 0.016666668f;
                life = math_random_float_range(15.0f, 20.0f);
            }
            child = cam_moby_create(obj, type, 0x43E, math_random_int_below(4), &frame.offset, &obj->rotation, &frame.velocity,
                                  0xFF, 180.0f, life);
            ctx->sparks[n] = child;
            if (child) {
                child->hook = glow_fade_update;
                life = math_random_float_range(0.75f, 5.0f);
                ctx->sparks[n]->f2C = ctx->sparks[n]->model->f24 * life;
                childctx = ctx->sparks[n]->ctx;
                alpha = 0x80;
                set_moby_color(ctx->sparks[n], 0x20, 0x60, alpha);
                ctx->sparks[n]->f23 = alpha;
                childctx->f50 = 0x1806020;
            }
        }
        snd_play_from_class_bank(math_random_int_range(0, 1), 0, obj, 0xC0A);
        switch (obj->classId) {
        case 0xC0A:
            moby_l00_spawn_child(obj, 0xC10, 0);
            break;
        case 0xC0B:
            moby_l00_spawn_child(obj, 0xC11, 0);
            break;
        case 0xC0C:
            moby_l00_spawn_child(obj, 0xC12, 0);
            break;
        case 0xC0D:
            moby_l00_spawn_child(obj, 0xC13, 0);
            break;
        case 0xE01:
            obj->f7C = 0x8001;
            break;
        case 0xE02:
            obj->f7C = 0x8001;
            break;
        case 0xAC9:
            obj->f7C = 0x8001;
            break;
        }
        moby_set_state(obj, 3, -1);
        break;
    }
    case 3:
        if (flag_set_first_pending(obj)) {
            if (!(obj->f7C & 0x8000)) {
                obj->f31 = 0;
                obj->flags |= 1;
            }
            obj->f98 = 0;
            ctx->timer = 300;
        }
        if (!math_fast_float_d(&ctx->timer)) {
            for (i = 0; i < 16; i++) {
                if (ctx->sparks[i])
                    ((AranosChildCtx *)ctx->sparks[i]->ctx)->f04 -= ctx->decay[i];
            }
        } else if (!(obj->f7C & 0x8000)) {
            moby_mark_spawned(obj);
        }
        return;
    default:
        return;
    }
}


/* func_L00_003D0008 is in L00_002FC7A8-lift.c. */

/* func_L00_003D0910 is in L00_002FC7A8-exhaust-g8.c. */
