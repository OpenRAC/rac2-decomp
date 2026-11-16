#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef signed short s16;
typedef signed int s32;
typedef unsigned int u32;
typedef float f32;
typedef int TI128 __attribute__((mode(TI)));

/* The resident global is an array here on purpose: with a scalar declaration
 * cc1 folds the load and reuses the destination as the address base, while the
 * retail materialises the address in its own register first -- declaring the
 * symbol as an array and indexing it [0] restores the two-instruction form
 * (`lui $v1,%hi; lw $a1,%lo($v1)`). */
extern u32 g_hero_moby[];

extern int g_player_slot_flag_other __attribute__((sda));

extern int g_player_slot_flag_hero __attribute__((sda));

extern float g_space_ship_threshold __attribute__((sda));

extern float g_ship_align_turn_threshold __attribute__((sda));

extern s16 g_platform_mode[];

extern f32 math_fabs(f32 f);

/* Says whether the given player has an object in its slot. */
s32 player_slot_has_object(u32 owner) {
    u32 currentOwner = g_hero_moby[0];
    int *flag = (owner == currentOwner) ? &g_player_slot_flag_hero : &g_player_slot_flag_other;
    return *flag != 0;
}

/* Says whether the ship is lined up well enough with its target to carry on. */
s32 space_ship_is_aligned_with_target(u8 *obj) {
    u8 *vars = *(u8 **)(obj + 0x68);
    f32 turn;
    if (*(f32 *)(vars + 0x3DC) < g_space_ship_threshold) return 1;
    turn = math_fabs(*(f32 *)(vars + 0x414) - *(f32 *)(vars + 0x410));
    if (g_platform_mode[0] < 0xB) return 0;
    if (*(f32 *)(vars + 0x3E0) < g_space_ship_threshold) {
        if (turn < g_ship_align_turn_threshold) return 1;
    }
    return 0;
}

/* The four resident words sit at the level-22 addresses; in the other program that carries
 * func_L22_003B9358 they are elsewhere, so they take per-program names. */
extern int ref_L22_003B9358_00 __attribute__((sda));   /* the level-22 word D_L22_001AFA08 */

extern int ref_L22_003B9358_01 __attribute__((sda));   /* the level-22 word D_L22_001AFA00 */

extern int ref_L22_003B9358_02 __attribute__((sda));   /* the level-22 word D_L22_001AFA0C */

extern int ref_L22_003B9358_03 __attribute__((sda));   /* the level-22 word D_L22_001AFA04 */

extern void snd_stop_voice(int handle);

extern void gfx_free_point_light(int index);

extern void func_0029F338_22(char *object);

extern int g_charged_shot_active;
extern int g_charged_shot_screen_effect;

/* Drops the resident slot the argument's record selects: the slot word is released and stamped
 * -1, and the object the slot holds is torn down when its id is 0x5F3 and it has not started
 * (the two resident words it owns are cleared first, and its stored index is released when it is
 * not -1). An object with any other id only clears the slot. */
/* Removes the object held in a player's slot and cleans up what it was using. */
void player_slot_clear_object(u32 owner)
{
    u32 currentOwner = g_hero_moby[0];
    int *slot;
    char *object;

    if (owner == currentOwner) {
        slot = &ref_L22_003B9358_00;
        if (ref_L22_003B9358_01 != -1) {
            snd_stop_voice(ref_L22_003B9358_01);
            ref_L22_003B9358_01 = -1;
        }
    } else {
        slot = &ref_L22_003B9358_02;
        if (ref_L22_003B9358_03 != -1) {
            snd_stop_voice(ref_L22_003B9358_03);
            ref_L22_003B9358_03 = -1;
        }
    }
    object = (char *)*slot;
    if (object == 0)
        return;
    if (*(short *)(object + 0xAA) != 0x5F3 /* moby class 1523 */) {
        *slot = 0;
        return;
    }
    if (*(unsigned char *)(object + 0x20) != 0)
        return;
    {
        char *vars = *(char **)(object + 0x68);
        int index;

        g_charged_shot_active = 0;
        g_charged_shot_screen_effect = 0;
        index = *(short *)(vars + 0x2C);
        if (index != -1)
            gfx_free_point_light(index);
    }
    func_0029F338_22((char *)*slot);
    *slot = 0;
}

/* func_L22_003F54B8 sets up the motion that func_L22_003F5580 runs: the heading of the
 * object's variables is a coin toss of +/- pi/2 added to the angle of the vector from the
 * object to a level point (after func_002AFDD8), the phase step is a rate in degrees per
 * second turned into radians per frame (pi / 180 / 60), and the amplitude is a level
 * value. The point and both values take per-program names.
 */
extern void FastVecSub(void *, void *, void *);
extern void vec_transform_by_object_or_given(void *, void *, void *, int);
extern int math_random_int_below(int);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 FastAddRotations(f32, f32);

typedef struct {
    u8 pad[0xB0];
    f32 heading;     /* 0xB0 */
    u8 pad_b4[8];
    f32 amplitude;   /* 0xBC */
    f32 phase_step;  /* 0xC0 */
    f32 phase;       /* 0xC4 */
} SwayVars;

extern char ref_L22_003F54B8_00[];
extern f32 ref_L22_003F54B8_01 __attribute__((sda));
extern f32 ref_L22_003F54B8_02 __attribute__((sda));

/* Starts a swaying motion by choosing a random side and setting the speed and size of the sway. */
void sway_start(u8 *obj) {
    SwayVars *vars = *(SwayVars **)(obj + 0x68);
    f32 delta[4];

    FastVecSub(delta, ref_L22_003F54B8_00, obj + 0x10);
    vec_transform_by_object_or_given(obj, delta, delta, 0);
    vars->heading = math_random_int_below(2) ? 1.5707964f : -1.5707964f;
    vars->heading = FastAddRotations(vars->heading, mat_fast_helper_a(delta[0], delta[1]));
    vars->phase_step = ref_L22_003F54B8_01 * 0.000290888245f;
    vars->amplitude = ref_L22_003F54B8_02;
    vars->phase = 0.0f;
}

/* func_L22_003F5580 is another function of this unit that reaches a level word through
 * $gp; the scale factor it multiplies is at a different address in the other program that
 * carries the function, so it takes a per-program name.
 */
extern f32 math_fast_sin_or_cos_b(f32);
extern f32 math_fast_sin_or_cos_a(f32);
extern void matrix_mul_vec3(f32 *, const f32 *, const f32 *);
extern void FastVecAdd(char *, char *, char *);
extern f32 FastAddRotations(f32, f32);
extern f32 ApproachValue(f32 *, f32, f32);
extern float ref_L22_003F5580_00 __attribute__((sda));

/* Scales the controller of the object: when the controller is idle its position is copied to
 * the object, otherwise the controller's values are scaled and written back.
 */
/* Moves the object in a sway that gets smaller over time, and stops it when it reaches zero. */
void sway_update_decaying(u8 *obj) {
    u8 *ctl = *(u8 **)(obj + 0x68);
    f32 buf[4];
    f32 a, b, c, d, g, r;

    if (*(f32 *)(ctl + 0xBC) == 0.0f) {
        if (*(f32 *)(ctl + 0xC0) == 0.0f)
            return;
        *(TI128 *)(obj + 0xE0) = *(TI128 *)ctl;
        *(f32 *)(ctl + 0xC0) = 0.0f;
        return;
    }
    a = math_fast_sin_or_cos_b(*(f32 *)(ctl + 0xC4));
    b = *(f32 *)(ctl + 0xBC);
    c = math_fast_sin_or_cos_a(*(f32 *)(ctl + 0xB0));
    b = b * a;
    c = c * b;
    buf[0] = c;
    d = math_fast_sin_or_cos_b(*(f32 *)(ctl + 0xB0));
    d = d * b;
    buf[1] = d;
    buf[2] = 0.0f;
    matrix_mul_vec3(buf, buf, obj + 0xC0);
    buf[3] = 0.0f;
    FastVecAdd(obj + 0xE0, buf, ctl);
    r = FastAddRotations(*(f32 *)(ctl + 0xC4), *(f32 *)(ctl + 0xC0));
    g = ref_L22_003F5580_00;
    *(f32 *)(ctl + 0xC4) = r;
    ApproachValue((f32 *)(ctl + 0xBC), 0.0f, g * (1.0f / 60.0f));
}

typedef unsigned short u16;

extern void cam_compute_view_direction(void *, void *, int);

extern f32 FastVecDot(void *, void *);

extern f32 IntToFloat(int);

extern f32 math_lerp_float(f32, f32, f32);

/* The resident object the point is derived from, the word that picks one of two threshold
   pairs, the four threshold words (read through $gp) and, for the two id lists, the table of
   lists and the base of the 32-byte records each one indexes (read bare: `lui`/`lw` in one
   register). */
extern u8 g_tether_origin[];

extern int g_hero_l22_mode_state;

extern f32 g_linked_toggle_near_b __attribute__((sda));

extern f32 g_linked_toggle_far_b __attribute__((sda));

extern f32 g_linked_toggle_near_a __attribute__((sda));

extern f32 g_linked_toggle_far_a __attribute__((sda));

extern u16 **g_linked_moby_lists_by_state;

extern u16 **g_linked_moby_lists_by_id;

extern u8 *g_toggle_link_table_b;

extern u8 *g_toggle_link_table_a;

/* Switches the object on (+0xCC set) when its position (+0xE0) comes within a threshold of the
   point func_002AFFD8 derives from D_L22_001B9C80 (func_00282DB0 measures it), and off when it
   moves beyond it; the threshold is interpolated between two words by the index at +0x14
   (divided by 14), the pair of words depending on D_L22_001A8F00 == 4. Only a change does
   anything more: switching off clears bit 2 of byte +0x1E of every record of the id list at
   +0x10 and bit 0 of byte +0x16 of every record of the list at +0x16; switching on sets those
   bits (a list index below zero means no list). */
/* Switches linked objects on when the player comes near and off again when the player moves away. */
void moby_toggle_linked_by_distance(u8 *self) {
    u8 *state = *(u8 **)(self + 0x68);
    f32 v[4];
    f32 dist;
    f32 thr;
    f32 f;
    u16 *p;
    u8 *e;

    cam_compute_view_direction(g_tether_origin, v, 1);
    dist = FastVecDot(self + 0xE0, v);
    f = IntToFloat(*(s16 *)(state + 0x14)) * 0.071428575f;
    if (g_hero_l22_mode_state == 4)
        thr = math_lerp_float(g_linked_toggle_near_b, g_linked_toggle_far_b, f);
    else
        thr = math_lerp_float(g_linked_toggle_near_a, g_linked_toggle_far_a, f);
    if (*(int *)(state + 0xCC) != 0) {
        if (thr < dist)
            *(int *)(state + 0xCC) = 0;
        if (*(int *)(state + 0xCC) != 0)
            return;
        if (*(int *)(state + 0x10) >= 0) {
            for (p = g_linked_moby_lists_by_state[*(int *)(state + 0x10)];
                 p != 0 && ((s16)p[-1] >= 0 || p == g_linked_moby_lists_by_state[*(int *)(state + 0x10)]);
                 p++) {
                e = g_toggle_link_table_b + ((*p & 0x7FFF) << 5);
                if (e == 0)
                    break;
                e[0x1E] &= 0xFB;
            }
        }
        if (*(s16 *)(state + 0x16) >= 0) {
            for (p = g_linked_moby_lists_by_id[*(s16 *)(state + 0x16)];
                 p != 0 && ((s16)p[-1] >= 0 || p == g_linked_moby_lists_by_id[*(s16 *)(state + 0x16)]);
                 p++) {
                e = g_toggle_link_table_a + ((*p & 0x7FFF) << 5);
                if (e == 0)
                    break;
                e[0x16] &= 0xFE;
            }
        }
    } else {
        if (dist < thr)
            *(int *)(state + 0xCC) = 1;
        if (*(int *)(state + 0xCC) == 0)
            return;
        if (*(int *)(state + 0x10) >= 0) {
            for (p = g_linked_moby_lists_by_state[*(int *)(state + 0x10)];
                 p != 0 && ((s16)p[-1] >= 0 || p == g_linked_moby_lists_by_state[*(int *)(state + 0x10)]);
                 p++) {
                e = g_toggle_link_table_b + ((*p & 0x7FFF) << 5);
                if (e == 0)
                    break;
                e[0x1E] |= 4;
            }
        }
        if (*(s16 *)(state + 0x16) >= 0) {
            for (p = g_linked_moby_lists_by_id[*(s16 *)(state + 0x16)];
                 p != 0 && ((s16)p[-1] >= 0 || p == g_linked_moby_lists_by_id[*(s16 *)(state + 0x16)]);
                 p++) {
                e = g_toggle_link_table_a + ((*p & 0x7FFF) << 5);
                if (e == 0)
                    break;
                e[0x16] |= 1;
            }
        }
    }
}

/* func_L22_003FC338: draws a pulsing ring around an object.  The 290-vertex
 * mesh is scaled, transformed by a basis built from the object's axis and
 * written to the shared vertex buffer as three strips; then 32 quads are drawn
 * from the ring's index table, the outer two corners pushed out by a factor. */
typedef struct { f32 x, y, z; } RingVertex;
extern RingVertex g_ring_vertices[];
extern f32 g_ring_vertex_offsets[][4];
extern f32 g_ring_glint_params[][2];
extern f32 g_ring_packet_vertices[][4];
extern s16 g_ring_index_table[][4];
extern f32 g_ring_phase_step __attribute__((sda));
extern f32 g_ring_pulse_amplitude __attribute__((sda));
extern f32 g_ring_base_scale __attribute__((sda));
extern int g_ring_l22_texture_id __attribute__((sda));
extern int g_ring_gs_bits_a __attribute__((sda));
extern int g_ring_gs_bits_b __attribute__((sda));
extern int g_ring_gs_bits_c __attribute__((sda));
extern int g_ring_gs_bits_d __attribute__((sda));
extern int g_ring_gs_bits_e __attribute__((sda));
extern int g_ring_l22_vertex_color __attribute__((sda));
extern int g_ring_color_rgb __attribute__((sda));
extern f32 g_ring_outer_scale __attribute__((sda));
extern f32 g_ring_inner_scale __attribute__((sda));
extern f32 g_ring_scale_factor __attribute__((sda));
extern unsigned long GetEffectTextureDescriptor(int);
extern void VU1_addGSregister(int, unsigned long);
extern void FastVecScale(void *, void *, f32);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void FastVecCross(void *, void *, void *);
extern void transform_vector(void *, void *, void *);
extern void font_queue_vu_state(void);
extern void part_draw_glint_effect(int, void *, void *, void *, int);
extern void draw_world_quad(void *, void *, int);
extern int FloatToInt(f32);

typedef struct {
    char pad[0x4C];
    f32 phase;
} RingController;

typedef struct {
    char pad0[0x10];
    f32 x, y, z;
    char pad1C[0x68 - 0x1C];
    RingController *controller;
    char pad6C[0xE0 - 0x6C];
    f32 axis[4];
} RingObject;

/* Draws a pulsing ring around an object, facing the camera. */
void gfx_draw_pulsing_ring(RingObject *o) {
    struct {
        f32 verts[4][4];
        int colors[4];
        f32 uv[8];
        unsigned long state[4];
    } packet;
    f32 matrix[4][4], offset[4], dir[4], v[4];
    int col[290];
    f32 scaled[4];
    RingController *ctl = o->controller;
    int i;
    f32 alpha = 1.0f;
    f32 sine;
    unsigned long bits;

    ctl->phase = FastAddRotations(ctl->phase, g_ring_phase_step);

    packet.state[1] = GetEffectTextureDescriptor(g_ring_l22_texture_id);
    packet.state[2] = 0xFF9000000260UL;
    bits = (unsigned long)g_ring_gs_bits_a | ((unsigned long)g_ring_gs_bits_b << 2);
    bits |= (unsigned long)g_ring_gs_bits_c << 4;
    bits |= (unsigned long)g_ring_gs_bits_d << 6;
    bits |= (unsigned long)g_ring_gs_bits_e << 32;
    packet.state[3] = bits;
    packet.state[0] = 0;
    VU1_addGSregister(0x47, 0x53001);

    matrix[3][0] = o->x;
    matrix[3][1] = o->y;
    matrix[3][2] = o->z;
    matrix[3][3] = 1.0f;
    sine = math_fast_sin_or_cos_b(ctl->phase);
    FastVecScale(offset, o->axis, g_ring_base_scale + g_ring_pulse_amplitude * sine);
    FastVecAdd((char *)matrix[3], (char *)matrix[3], (char *)offset);
    FastVecSub(dir, g_tether_origin, matrix[3]);
    vec_scale_to_length(matrix[0], dir, 1.0f);
    FastVecCross(matrix[1], matrix[0], o->axis);
    vec_scale_to_length(matrix[1], matrix[1], 1.0f);
    FastVecCross(matrix[2], matrix[1], matrix[0]);

    packet.colors[0] = packet.colors[1] = packet.colors[2] = packet.colors[3] = g_ring_l22_vertex_color;
    VU1_addGSregister(6, GetEffectTextureDescriptor(g_ring_l22_texture_id));
    VU1_addGSregister(0x42, 0x8000000044UL);
    VU1_addGSregister(8, 0);
    VU1_addGSregister(0x14, 0xFF9000000260UL);
    VU1_addGSregister(0x4A, 0);
    font_queue_vu_state();

    for (i = 0; i < 290; i++) {
        FastVecScale(scaled, g_ring_vertex_offsets[i], g_ring_inner_scale);
        transform_vector(v, scaled, matrix[0]);
        g_ring_vertices[i].x = v[0];
        g_ring_vertices[i].y = v[1];
        g_ring_vertices[i].z = v[2];
        col[i] = packet.colors[0];
    }
    part_draw_glint_effect(148, &g_ring_vertices[0], &col[0], g_ring_glint_params[0], 1);
    part_draw_glint_effect(109, &g_ring_vertices[146], &col[146], g_ring_glint_params[146], 1);
    part_draw_glint_effect(36, &g_ring_vertices[254], &col[254], g_ring_glint_params[254], 1);

    packet.state[1] = GetEffectTextureDescriptor(11);
    packet.state[3] = 0x8000000048UL;
    {
        int color = (FloatToInt(alpha * 64.0f + 128.0f) << 24) | g_ring_color_rgb;
        packet.colors[1] = color;
        packet.colors[0] = color;
        packet.colors[3] = 0;
        packet.colors[2] = 0;
    }
    {
        int ring;

        for (ring = 0; ring < 32; ring++) {
            for (i = 0; i < 4; i++) {
                int idx = g_ring_index_table[ring][i];

                if (i >= 2) {
                    FastVecScale(packet.verts[i], g_ring_packet_vertices[idx], g_ring_outer_scale * g_ring_scale_factor);
                } else {
                    FastVecScale(packet.verts[i], g_ring_packet_vertices[idx], g_ring_outer_scale);
                }
            }
            packet.uv[0] = 0.5f;
            packet.uv[1] = 0.5f;
            packet.uv[2] = 0.5f;
            packet.uv[3] = 0.5f;
            packet.uv[4] = 0.5f;
            packet.uv[5] = 1.0f;
            packet.uv[6] = 0.5f;
            packet.uv[7] = 1.0f;
            draw_world_quad(packet.verts, matrix[0], 0);
        }
    }
    VU1_addGSregister(0x47, 0x5360B);
}
