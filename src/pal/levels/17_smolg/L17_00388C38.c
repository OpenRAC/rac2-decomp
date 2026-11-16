#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union {
    Quad q;
    float f[4];
} Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
typedef struct { char pad[0x70]; float material; char tail[0x6C]; } Material;
extern unsigned char g_item_slot_to_record[];
extern char *g_hero_moby NOT_SDA;
extern int g_projectile_model_ref __attribute__((sda));
extern int g_ripple_object __attribute__((sda)), g_ripple_param __attribute__((sda));
extern Collision g_collision_result;
extern Material g_weapon_l00_table[];
extern void part_steer_effect_direction(int, void *, int);
extern void vec_transform_or_copy(void *, void *);
extern void shop_trigger_current_state_effect(void *, void *);
extern void vec_add_object_direction_scaled(void *, void *, float);
extern void func_PAL_L00_00392250(void *);
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
extern void *func_PAL_002C0838(void *, void *, int, int);
extern void vec_fast_normalize(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int math_fast_float_d(void *);
extern void table_clear_entry_flag(int);
extern void func_PAL_L00_00390F48(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);

/* func_PAL_L17_00388C38, the PAL copy of func_L17_00385DE8: the same C, where the sparks' life of
   16 frames becomes 13 and the second spark's spin stays a literal 16. */
/* Read once as a GP macro load in a delay slot and otherwise as lui/lw, as at -G0 in retail. */
extern int g_spark_effect_state __attribute__((sda));
typedef struct { char pad[0x30]; int phase, frame; char gap[0x15C]; char *actor; } CutsceneState;
extern CutsceneState g_cutscene_l17_state;
typedef struct EffectMoby {
    char pad0[0x28]; struct EffectMoby *next; char pad1[8]; unsigned short flags;
    char pad2[0x62]; int unknown; char pad3[0xE]; short classId;
} EffectMoby;
extern EffectMoby *g_effect_moby_list __attribute__((sda));
extern void moby_transform_joint_to_world(void *, int, void *);
typedef struct { char pad0[4]; int state; char pad1[2]; unsigned char opacity, age; } EffectTail;
typedef struct { char pad0[8]; unsigned char color, size; short life; char pad1[0x14]; EffectTail tail; } CutsceneParticle;
/* Each register bank keeps the callee's order (a0-t0: position, spin, axis, colour, count;
   f12-f15: jitter, lo, hi, size); the interleaving gives retail's argument setup order. */
extern CutsceneParticle *func_PAL_002BE9A8(void *, int, float, float, void *, float, unsigned int, float, int);
extern int FloatToInt(float);

/* Activates the scene's effect mobys during phase 6 and emits paired sparks from the
   scene actor during two frame windows of phases 4 and 5. */
void cutscene_update_spark_effects_pal(unsigned char *self) {
    Vec velocity, point;
    char *obj;
    CutsceneParticle *first, *second;
    EffectTail *detail;
    int amount, state;

    switch (self[0x20]) {
    case 0:
        self[0x30] = 255;
        self[0x20] = 1;
        break;
    case 1:
        if (g_spark_effect_state != 2)
            break;
        if (g_cutscene_l17_state.phase == 6) {
            EffectMoby *m;
            for (m = g_effect_moby_list; m; m = m->next) {
                if (m->classId == 0xB88 || m->classId == 0x1249) {
                    m->unknown = 0;
                    m->flags = (m->flags | 0x43) & 0xEFFF;
                }
            }
        }
        state = g_spark_effect_state;
        if (state != 2)
            break;
        if (g_cutscene_l17_state.phase == 4 && (unsigned)(g_cutscene_l17_state.frame - 301) < 59) {
            obj = g_cutscene_l17_state.actor;
            if (*(short *)(obj + 0xAA) == 0x125E) {
                moby_transform_joint_to_world(obj, 0, &point);
                vec_scale_to_length(&velocity, obj + 0xE0, -0.05f);
                amount = math_random_int_below(16);
                if (math_random_int_below(2))
                    amount = -amount;
                first = func_PAL_002BE9A8(&point, amount, 0.1f, 1.0f, &velocity, 0.9f, 0x7F204080, 100000.0f, 0);
                if (first) {
                    first->life = 13;
                    first->size = FloatToInt(4.0f) + 64;
                    detail = &first->tail;
                    detail->opacity = 127;
                    detail->state = state;
                    detail->age = (unsigned char)first->life;
                }
                second = func_PAL_002BE9A8(&point, 16, 0.05f, 1.0f, &velocity, 0.97f, 0x7FFFFFFF, 60000.0f, 0);
                /* Retail tests the first spark again before writing the second. */
                if (first) {
                    detail = &second->tail;
                    second->size = FloatToInt(4.0f) + 64;
                    second->life = 13;
                    second->color = math_random_int_below(255);
                    detail->state = state;
                    detail->opacity = 127;
                    detail->age = (unsigned char)first->life;
                }
                state = g_spark_effect_state;
            }
        }
        if (state != 2)
            break;
        if (g_cutscene_l17_state.phase == 5 && g_cutscene_l17_state.frame >= 531) {
            obj = g_cutscene_l17_state.actor;
            if (*(short *)(obj + 0xAA) == 0x125E) {
                moby_transform_joint_to_world(obj, 0, &point);
                vec_scale_to_length(&velocity, obj + 0xE0, -0.05f);
                amount = math_random_int_below(16);
                if (math_random_int_below(2))
                    amount = -amount;
                first = func_PAL_002BE9A8(&point, amount, 0.1f, 1.0f, &velocity, 0.9f, 0x7F204080, 100000.0f, 0);
                if (first) {
                    first->life = 13;
                    first->size = FloatToInt(4.0f) + 64;
                    detail = &first->tail;
                    detail->opacity = 127;
                    detail->state = state;
                    detail->age = (unsigned char)first->life;
                }
                second = func_PAL_002BE9A8(&point, 16, 0.05f, 1.0f, &velocity, 0.97f, 0x7FFFFFFF, 60000.0f, 0);
                if (first) {
                    detail = &second->tail;
                    second->size = FloatToInt(4.0f) + 64;
                    second->life = 13;
                    second->color = math_random_int_below(255);
                    detail->state = state;
                    detail->opacity = 127;
                    detail->age = (unsigned char)first->life;
                }
            }
        }
        break;
    }
}

void func_PAL_L17_00393E08(unsigned char *obj) {
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
    frame.velocity.f[2] = 0.040000003f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    FastVecAdd(position, ctx, position);
    part_steer_effect_direction(*(int *)(ctx + 0x1C), ctx, 0);
    vec_transform_or_copy(position, position);
    shop_trigger_current_state_effect(ctx, ctx);
    vec_add_object_direction_scaled(position, ctx, 0.0044f);
    func_PAL_L00_00392250(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0xF2)
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
            *(float *)(ctx + 8) = -0.030000001f;
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
                speed = math_random_float_range(0.0f, 0.060000002f);
                frame.spread.f[0] = math_fast_sin_or_cos_a(angle) * speed;
                frame.spread.f[1] = math_fast_sin_or_cos_b(angle) * speed;
                frame.spread.f[2] = math_random_float_range(0.060000002f, 0.13000001f);
                lifetime = math_random_int_range(90, 120);
                func_PAL_002C0838(&frame.position, spread, math_random_int_below(2), lifetime);
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
                if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) > 0xF1)
                    goto finish;
                reread = &g_collision_result;
                model = reread->hit;
                if (*(int *)(model + 0x64) == g_projectile_model_ref && *(short *)(model + 0xAA) != 0x336)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &reread->point);
                vec_fast_normalize(&frame.velocity, ctx, &reread->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.040000003f);
                vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
            } else {
                if (collision->count < 1)
                    goto finish;
                obj[0xBC] = 1;
                qcopy(obj + 0x10, &collision->point);
                vec_fast_normalize(&frame.velocity, ctx, &collision->normal);
                vec_scale_to_length(&frame.velocity, &frame.velocity, 0.040000003f);
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
        func_PAL_L00_00390F48(obj, &frame.velocity, &frame.normal);
    }
}


extern unsigned char g_bouncing_weapon_index;
extern void FastVecScale(void *, void *, float);
extern void cam_compute_view_direction(void *, void *, int);
extern void func_PAL_L00_00391958(void *, void *, void *);
extern void func_PAL_L00_00392500(void *);

void func_PAL_L17_00394220(char *obj) {
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
    frame.velocity.f[2] = 0.040000003f;
    frame.normal.q = 0;
    frame.normal.f[2] = 1.0f;
    qcopy(&frame.old, position);
    FastVecAdd(position, position, ctx);
    cam_compute_view_direction(position, &frame.surface, 0);
    FastVecScale(&frame.surface, &frame.surface, 0.00044f);
    func_PAL_L00_00392500(obj);
    frame.packet.moby = obj;
    frame.packet.flags = 0x830000;
    if (*(int *)(ctx + 0x18) < 0xF2)
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
            if ((hit == g_hero_moby || *(short *)(hit + 0xAA) == 0xC0) && *(int *)(ctx + 0x18) >= 0xF2)
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
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.040000003f);
            vec_scale_to_length(&frame.normal, &reread->normal, 1.0f);
        } else {
            collision = &g_collision_result;
            if (collision->count <= 0)
                goto finish;
            obj[0xBC] = 1;
            qcopy(position, &collision->point);
            vec_fast_normalize(&frame.velocity, ctx, &collision->normal);
            vec_scale_to_length(&frame.velocity, &frame.velocity, 0.040000003f);
            vec_scale_to_length(&frame.normal, &collision->normal, 1.0f);
        }
    } else if (math_fast_float_d(ctx + 0x18)) {
        obj[0xBC] = 1;
        FastVecAdd((char *)&frame.velocity, (char *)&frame.velocity, ctx);
    }
finish:
    if (*(unsigned char *)(obj + 0xBC)) {
        table_clear_entry_flag(*(int *)(ctx + 0x1C));
        if (*(int *)(ctx + 0x14) < 17)
            func_PAL_L00_00390F48(obj, &frame.velocity, &frame.normal);
        else
            func_PAL_L00_00391958(obj, &frame.velocity, &frame.normal);
    }
}




/* func_PAL_L17_003A7DB0, the PAL copy of func_L17_003A4740: the same C, where the 90-tick fade
 * becomes 75. */

extern int g_screen_width[] MACRO_ADDR;
extern int g_tile_grid_scroll[];
extern float IntToFloat(int);
extern unsigned long GetEffectTextureDescriptor(int);
extern void DrawTexturedQuad(int, int, int, int, int, int, int, int, unsigned long long, unsigned long long);

void func_PAL_L17_003A7DB0(char *self) {
    char *data = *(char **)(self + 0x68);
    float fv[2];
    unsigned long packet;
    int nx, ny, i, j;
    float pv[2];
    float base, a, b;
    int color;
    int t0, t1;

    fv[0] = IntToFloat(g_screen_width[2]);
    fv[1] = IntToFloat(g_screen_width[3]);
    packet = GetEffectTextureDescriptor(0x1E);
    nx = g_screen_width[0] / 32 + 1;
    ny = g_screen_width[1] / 32 + 1;

    for (i = 0; i < nx; i++) {
        int *p = g_tile_grid_scroll;
        for (j = 0; j < ny; j++) {
            pv[0] = (float)(i * 32);
            pv[1] = (float)(j * 32);
            base = (float)*p;
            a = IntToFloat(*(int *)(data + 0x140));
            b = IntToFloat(0x4B);
            color = (FloatToInt(a * 127.5f / b) << 24) + 0xFF7F7F;
            t0 = math_random_int_below(0x20);
            t1 = math_random_int_below(0x20);
            DrawTexturedQuad(FloatToInt(pv[0] - base), FloatToInt(pv[1] - base), 0x20, 0x20, t0, t1, 0x20, 0x20, color, packet);
        }
    }
}



