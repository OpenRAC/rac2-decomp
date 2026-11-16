#include "include_asm.h"

#include "common.h"

/* Small-data unit: the bodies whose state lives at $gp-relative offsets. */

extern float g_rotor_timer_step __attribute__((sda));

/* Bleeds the ten rotation timers the level keeps beside its state: each armed
   entry loses a sixtieth of the shared rate and clamps at zero, disarming. */
void rotor_tick_timers(char *obj)
{
    char *state = *(char **)(obj + 0x68);
    int i;

    for (i = 0; i < 10; i++) {
        u8 *armed = (u8 *)(state + 0x380 + i);
        f32 *timer = (f32 *)(state + 0x2F0 + 4 * i);
        if (*armed == 1) {
            f32 left = *timer - g_rotor_timer_step * 0.016666667f;
            *timer = left;
            if (left < 0.0f) {
                *timer = 0.0f;
                *armed = 2;
            }
        }
    }
}

extern float g_rotor_random_spin_rate __attribute__((sda));

extern void anim_start_blended(void *, int, int, int);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern void mem_clear(unsigned int *, unsigned int, int);
extern void AttachManipulator(unsigned char *, unsigned int, unsigned char *);

/* Re-aims the object: resets the measured state, draws a random angle and
   clears the two rotation slots of the state. */
void rotor_reaim_random_spin(char *obj)
{
    char *state = *(char **)(obj + 0x68);
    float spin_angle;
    float spin_rate;

    *(unsigned char *)(state + 0x2E) = 3;
    *(float *)(state + 0x20) = (float)*(short *)(state + 0x24);
    *(short *)(state + 0x1A8) = 0;
    *(unsigned char *)(state + 0x18A) = 0;
    *(unsigned char *)(obj + 0x31) = 1;
    *(unsigned short *)(obj + 0x34) &= 0xFFFE;
    *(int *)(obj + 0x98) = *(int *)(*(int *)(obj + 0x24) + 0x10);
    *(unsigned short *)(obj + 0x34) = (*(unsigned short *)(obj + 0x34) | 0x1000) & 0xFFB9;
    *(unsigned char *)(obj + 0x7F) = 0;
    if (*(unsigned char *)(obj + 0x43) != 1)
        anim_start_blended(obj, 1, 0, 0);
    spin_angle = math_random_float_range(10.0f, 30.0f) * 0.017453294f;
    if (math_random_int_below(2) != 0)
        spin_angle = -spin_angle;
    *(float *)(state + 0x2D4) = spin_angle;
    if (math_random_int_below(2) != 0)
        spin_rate = -g_rotor_random_spin_rate;
    else
        spin_rate = g_rotor_random_spin_rate;
    *(short *)(state + 0x2EE) = 0;
    *(float *)(state + 0x2DC) = spin_rate;
    mem_clear((unsigned int *)(state + 0x220), 0, 0x40);
    AttachManipulator((unsigned char *)obj, 2, (unsigned char *)(state + 0x220));
    mem_clear((unsigned int *)(state + 0x260), 0, 0x40);
    AttachManipulator((unsigned char *)obj, 3, (unsigned char *)(state + 0x260));
}

extern float g_rotor_aim_motion_speed __attribute__((sda));

extern int g_moby_l11_table;

extern void FastVecSub(void *dst, void *a, void *b);

extern void vec_scale_to_length(void *dst, void *src, float scale);

extern void vec_add_random_offset(float *p, float f);

extern int math_random_int_below(int n);

extern char *arena_get_center_point(char *object);

extern void arena_set_boss_owner(char *object, int value);

extern void InitializeRandomizedObjectMotion(void *a0, void *a1, float f0, float f1);


/* Aims the object at the entry its state names: crosses the entry with the record,
   jitters the result by a random sixtieth and hands it to the level's own helper.
   The table base is read afresh for each of the three groups, which is how retail
   keeps it in the caller-saved registers. */
void rotor_aim_at_entry(char *obj, int index, int flag)
{
    char *state = *(char **)(obj + 0x68);
    char *base1;
    char *base2;
    char *base3;
    int offset = index * 4;
    char *entry;
    float aim_vec[3];
    float falloff;
    int random_value;
    int record;

    entry = arena_get_center_point(*(char **)(obj + 0xB8));

    base1 = g_moby_l11_table;
    FastVecSub(aim_vec, entry, ((char *)(base1 + (*(int *)(*(char **)(obj + 0x68) + offset + 0x330) << 8))) + 0x10);
    random_value = math_random_int_below(10) + 15;
    vec_scale_to_length(aim_vec, aim_vec, (float)random_value * (1.0f / 60.0f));
    vec_add_random_offset(aim_vec, 1.0f / 60.0f);
    random_value = math_random_int_below(5) + 5;
    aim_vec[2] = (float)random_value * (1.0f / 60.0f);

    falloff = 1.0f - ((float)*(short *)(state + 0x378) - 4.0f) * (1.0f / 6.0f);
    if (falloff > 1.0f)
        falloff = 1.0f;
    if (falloff < 0.0f)
        falloff = 0.0f;

    base2 = g_moby_l11_table;
    InitializeRandomizedObjectMotion(((char *)(base2 + (*(int *)(*(char **)(obj + 0x68) + offset + 0x330) << 8))), aim_vec, g_rotor_aim_motion_speed * (1.0f / 3600.0f), falloff);

    base3 = g_moby_l11_table;
    /* The record's field at 0xB8 takes the object's own handle. */
    *(int *)((char *)((*(int *)(*(char **)(obj + 0x68) + offset + 0x330) << 8) + (int)base3)
            + 0xB8) = *(int *)(obj + 0xB8);
    record = (int)((char *)(base3 + (*(int *)(*(char **)(obj + 0x68) + offset + 0x330) << 8)));
    *(int *)(state + 0x364) = record;
    if (flag != 0)
        arena_set_boss_owner(*(char **)(obj + 0xB8), record);
    else
        arena_set_boss_owner(*(char **)(obj + 0xB8), 0);

    *(unsigned char *)(state + index + 0x380) = 1;
}

typedef int TI128 __attribute__((mode(TI)));

/* The flat quad the effect submits: four positions, four colours, four uv
   pairs and the four GS words (primitive, texture, mode, registers). */
typedef struct {
    TI128 position[4];
    u32 color[4];
    float uv[4][2];
    unsigned long primitive, texture, mode, registers;
} EffectQuad;

typedef struct {
    TI128 saved;
    EffectQuad quad;
    float a[4];
    float b[4];
    float c[4];
    TI128 corner;
} EffectQuadFrame;

extern void FastVecAdd(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern unsigned long GetEffectTextureDescriptor(int);
extern void draw_world_quad(void *, void *, int);
extern char g_hero_l11_position[];
extern int g_joba_beam_first_stage_registers __attribute__((sda));
extern int g_joba_beam_first_stage_color __attribute__((sda));
/* The two uv columns: macro-addressed tables, so each base is one la. */
extern float g_joba_beam_stage_uv_u[] __attribute__((sda));
extern float g_joba_beam_stage_uv_v[] __attribute__((sda));

/* Draws the first stage of the beam between the state's two end points: each
   side is pulled a tenth of the way toward the level's anchor, then the four
   corners are crossed out from the span and submitted as one textured quad. */
void joba_draw_beam_first_stage(char *obj, void *q)
{
    EffectQuadFrame quad_frame;
    char *vars;
    int i;

    quad_frame.saved = *(TI128 *)q;
    vars = *(char **)(obj + 0x68);
    FastVecSub(quad_frame.c, vars, vars + 0x10);
    FastVecSub(quad_frame.a, vars, g_hero_l11_position);
    FastVecSub(quad_frame.b, vars + 0x10, g_hero_l11_position);
    FastVecCross(quad_frame.a, quad_frame.a, quad_frame.c);
    vec_scale_to_length(quad_frame.a, quad_frame.a, 0.1f);
    FastVecCross(quad_frame.b, quad_frame.b, quad_frame.c);
    vec_scale_to_length(quad_frame.b, quad_frame.b, 0.1f);
    quad_frame.quad.texture = GetEffectTextureDescriptor(7);
    quad_frame.quad.mode = 0x0000ff9000000260UL;
    quad_frame.quad.registers = ((unsigned long)g_joba_beam_first_stage_registers << 32) | 0x48;
    quad_frame.quad.primitive = 0;
    quad_frame.quad.color[0] = quad_frame.quad.color[1] = quad_frame.quad.color[2] = quad_frame.quad.color[3] = g_joba_beam_first_stage_color;
    for (i = 0; i < 4; i++) {
        quad_frame.quad.uv[i][0] = g_joba_beam_stage_uv_u[i * 2];
        quad_frame.quad.uv[i][1] = g_joba_beam_stage_uv_v[i * 2];
    }
    FastVecSub(&quad_frame.corner, vars, quad_frame.a);
    quad_frame.quad.position[0] = quad_frame.corner;
    FastVecAdd(&quad_frame.corner, vars, quad_frame.a);
    quad_frame.quad.position[1] = quad_frame.corner;
    FastVecSub(&quad_frame.corner, vars + 0x10, quad_frame.b);
    quad_frame.quad.position[2] = quad_frame.corner;
    FastVecAdd(&quad_frame.corner, vars + 0x10, quad_frame.b);
    quad_frame.quad.position[3] = quad_frame.corner;
    draw_world_quad(&quad_frame.quad, 0, 0);
}

extern int g_joba_beam_second_stage_registers __attribute__((sda));
extern int g_joba_beam_second_stage_color __attribute__((sda));

/* The second stage: the same quad pulled a twentieth of the way in, drawn
   once with its own texture and then again with the additive overlay. */
void joba_draw_beam_second_stage(char *obj, void *q)
{
    EffectQuadFrame quad_frame;
    char *vars;
    int i;

    quad_frame.saved = *(TI128 *)q;
    vars = *(char **)(obj + 0x68);
    FastVecSub(quad_frame.c, vars, vars + 0x10);
    FastVecSub(quad_frame.a, vars, g_hero_l11_position);
    FastVecSub(quad_frame.b, vars + 0x10, g_hero_l11_position);
    FastVecCross(quad_frame.a, quad_frame.a, quad_frame.c);
    vec_scale_to_length(quad_frame.a, quad_frame.a, 0.05f);
    FastVecCross(quad_frame.b, quad_frame.b, quad_frame.c);
    vec_scale_to_length(quad_frame.b, quad_frame.b, 0.05f);
    quad_frame.quad.texture = GetEffectTextureDescriptor(0x13);
    quad_frame.quad.mode = 0x0000ff9000000260UL;
    quad_frame.quad.registers = ((unsigned long)g_joba_beam_second_stage_registers << 32) | 0x48;
    quad_frame.quad.primitive = 0;
    quad_frame.quad.color[0] = quad_frame.quad.color[1] = quad_frame.quad.color[2] = quad_frame.quad.color[3] = g_joba_beam_second_stage_color;
    for (i = 0; i < 4; i++) {
        quad_frame.quad.uv[i][0] = g_joba_beam_stage_uv_u[i * 2];
        quad_frame.quad.uv[i][1] = g_joba_beam_stage_uv_v[i * 2];
    }
    FastVecSub(&quad_frame.corner, vars, quad_frame.a);
    quad_frame.quad.position[0] = quad_frame.corner;
    FastVecAdd(&quad_frame.corner, vars, quad_frame.a);
    quad_frame.quad.position[1] = quad_frame.corner;
    FastVecSub(&quad_frame.corner, vars + 0x10, quad_frame.b);
    quad_frame.quad.position[2] = quad_frame.corner;
    FastVecAdd(&quad_frame.corner, vars + 0x10, quad_frame.b);
    quad_frame.quad.position[3] = quad_frame.corner;
    draw_world_quad(&quad_frame.quad, 0, 0);
    quad_frame.quad.texture = GetEffectTextureDescriptor(0x10);
    quad_frame.quad.mode = 0x0000ff9000000260UL;
    quad_frame.quad.registers = 0x8000000048UL;
    quad_frame.quad.primitive = 0;
    draw_world_quad(&quad_frame.quad, 0, 0);
}
