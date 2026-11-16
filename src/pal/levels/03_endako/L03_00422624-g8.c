#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef float f32;
extern u8 *g_moby_record_base __attribute__((sda));
extern s32 g_endako_boss_forced_behaviour __attribute__((sda));
extern u32 g_endako_boss_initial_timer __attribute__((sda));
extern int math_random_int_below(int id);
extern int math_fast_float_d(void *target);
extern int FastDecTimer(void *target);
extern void moby_update_eased_node(void *entity, void *target, int a, float f0, float f1);
extern void vec_transform_by_object_or_given(void *entity, void *out, void *target, int a);
extern void moby_transform_joint_to_world(void *entity, int a, void *out);
extern u8 *part_spawn_spinning_spark_pal(void *p, float f0, float f1, float f2, int z, void *local,
                         float f3, int v, int t);
extern int FloatToInt(float f);
extern void value_set_and_smooth_pal(void *entity, float *target, float f, int a, int b);
extern float g_particle_fire_blend_scale __attribute__((sda));
extern f32 g_robot_speed_scale __attribute__((sda));
extern f32 g_robot_turn_scale __attribute__((sda));
extern s32 flag_is_third_pending_set();
typedef struct {
    s32 a;
    s32 b;
    f32 c;
    f32 d;
} ParticleSetup;
extern u8 *g_entity_id_lists[];
extern s32 g_hero_l03_mode __attribute__((sda));
extern s32 func_3240F0(u8 *a0);

/* Sets the entity's two blend channels up, then fires two particles: the engine builds
 * each one from the state's direction, a random count and a colour, and the caller fills
 * the record's own fields in.  The two blocks fill the FIRST particle's header again, and
 * the second one keeps its own pointer to the sub-record: both are the original's own
 * wording, and the compiler's schedule depends on it. */
void part_fire_blend_particles_pal(u8 *moby) {
    u8 *state = *(u8 **)(moby + 0x68);
    float local_point[4];
    ParticleSetup setup;
    float joint_pos[4];
    u16 timer;
    s32 count;
    f32 blend_y;
    u8 *particle_a;
    u8 *particle_b;
    u8 *spark_data;
    u8 *spark_data2;

    math_fast_float_d(state + 0x34C);
    FastDecTimer(state + 0x330);
    FastDecTimer(state + 0x332);
    moby_update_eased_node(moby, state + 0x220, 0, 0.0432f, 0.43200004f);
    moby_update_eased_node(moby, state + 0x2A0, 1, 0.0432f, 0.43200004f);
    timer = *(u16 *)(moby + 0x96);
    if (timer <= 0xFFFE)
        *(u16 *)(moby + 0x96) = timer + 1;
    vec_transform_by_object_or_given(moby, local_point, state + 0x1A0, 0);
    blend_y = local_point[1] * g_particle_fire_blend_scale;
    *(float *)(moby + 0xF0) = blend_y;
    /* The four words the engine reads the particle_a's setup from, in the order the
     * original stores them. */
    setup.a = 0;
    setup.c = -0.02f;
    setup.d = 1.0f;
    setup.b = 0;
    count = math_random_int_below(16);
    if (math_random_int_below(2))
        count = -count;
    moby_transform_joint_to_world(moby, 4, joint_pos);
    joint_pos[2] += 0.1f;
    particle_a = part_spawn_spinning_spark_pal(joint_pos, 0.1f, 1.0f, 0.9f, count, &setup,
                             105000.0f, 0xDF204080, 0);
    if (particle_a != 0) {
        spark_data = particle_a + 0x20;
        *(u16 *)(particle_a + 0xA) = 4;
        particle_a[9] = FloatToInt(4.0f) + 0x70;
        *(u32 *)(spark_data + 4) = 2;
        spark_data[0xA] = 0xDF;
        spark_data[0xB] = particle_a[0xA];
    }
    particle_b = part_spawn_spinning_spark_pal(joint_pos, 0.1f, 1.0f, 0.9f, count, &setup,
                              105000.0f, 0xDF204080, 0);
    spark_data2 = particle_b;
    if (spark_data2 != 0) {
        *(u16 *)(particle_a + 0xA) = 4;
        spark_data2 += 0x20;
        particle_a[9] = FloatToInt(4.0f) + 0x70;
        *(u32 *)(spark_data2 + 4) = 2;
        spark_data2[0xA] = 0xDF;
        spark_data2[0xB] = particle_a[0xA];
    }
    if (moby[0x31] != 0)
        value_set_and_smooth_pal(moby, (float *)(state + 0x360), 2.5f, 5, 1);
}

extern u8 *SpawnSpinningSparkParticle(void *cursor, float f0, float f1, float f2, int z, void *local,
                         float f3, int v, int t);

/* Same walk as func_L03_0041D0A8 after seeding two state halfwords. */
void rivet_bot_mark_stream_pal(u8 *moby) {
    u8 *state = *(u8 **)(moby + 0x68);
    u8 *id_list;
    u8 *cursor;
    u8 *record_base;

    *(short *)(state + 0x336) = 1;
    *(short *)(state + 0x330) = 0xC8;
    if (moby[0x21] == 0xFF)
        return;
    id_list = g_entity_id_lists[moby[0x21]];
    if (id_list == 0)
        return;
    cursor = id_list;
    record_base = g_moby_record_base;
    for (;;) {
        u8 *record = record_base + ((*(unsigned short *)cursor & 0x7FFF) << 8);

        if (*(signed char *)(record + 0x20) >= 0) {
            if (*(short *)(record + 0xAA) == 0xFFC) {
                *(short *)(*(u8 **)(record + 0x68) + 0x336) = 1;
            }
        }
        if (*(short *)cursor < 0)
            break;
        cursor += 2;
    }
}
