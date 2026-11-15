#include "include_asm.h"
#include "common.h"

/* func_L19_003E9400 is defined in L19_003E9400-controller.c. */

/* func_L19_00411890 is defined in L19_00411890-g8.c. */

/* func_L19_00411EF0 is defined in L19_00411EF0-g8.c. */

/* func_L19_00412140 is defined in L19_00412140-g8.c. */

/* func_L19_004160A0 is defined in L19_004160A0-g8.c. */

/* func_L19_004170D8 is defined in L19_004170D8-g8.c. */

extern void func_2EB590();

extern float func_2EB5C0();

extern float func_3183D8(float, float);

extern float func_2EBF18(float);

extern float func_2EBF30(float);

/* Ticks two timers in the object's data and counts up its age, stopping at the maximum. */
void moby_tick_timers_age(char *moby)
{
    int vars_addr = *(int *)(moby + 0x68);

    func_2EB590(vars_addr + 0x218);
    func_2EB5C0(vars_addr + 0x21C);
    if (*(unsigned short *)(moby + 0x96) < 0xFFFF) {
        *(unsigned short *)(moby + 0x96) += 1;
    }
}

/* func_L19_00417A58 is defined in L19_00417A58.c. */


/* func_L19_00417CA0 is defined in L19_003E9400-effects-g8.c. */

typedef int TI128 __attribute__((mode(TI)));
typedef float V[4] __attribute__((aligned(16)));
typedef struct {
    float u, v;
} UV;
typedef struct {
    V p[4];
    int color[4];
    UV uv[4];
    long zero, texture, state, flags;
} Quad;

extern char D_L19_001BFEA0[], D_L19_001B9A40[];
extern UV D_L19_001B1C08[] MACRO_ADDR;
extern void moby_transform_joint_point(void *, int, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void part_spawn_random_direction_effect(void *, float, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void draw_world_quad(void *, int, int);
extern float math_random_angle(void);
extern void gfx_draw_billboard_quad(void *, int, int, int, float, float, float);
extern int CollLine(void *, void *, int, void *, void *);
extern long GetEffectTextureDescriptor(int);

/* Draws the glowing beam: glow sprites at the start, a line check to find where it ends, and two bright strips from the start to the end point. */
void DrawGrelbinBeamEffect(char *moby)
{
    V matrix[4], origin, tmp, jitter, end;
    Quad q;
    V other, factor, impact, ray, corner;
    /* The named constants below are real arguments (each is what retail passes), but they also steer:
     * declared before d, they bring d to a later pseudo, so the gcse bucket of d + 0x2c0 follows &origin's
     * and settles a 173/173 global-alloc tie between $s6 and $s7. Written as literals, the function is one
     * register swap short (the same lever as 0030A348-tether-g8.c and 0032EB28-probe-g8.c). */
    int i, hit, texture, tag, mode;
    int part = 0, sprite = 0x31, layer = 1, mask = 2, flags = 0;
    float inner, outer;
    char *d = *(char **)(moby + 0x68);

    moby_transform_joint_point(moby, part, matrix);
    qcopy(origin, matrix[3]);
    inner = 0.25f;
    outer = 0.45f;
    vec_scale_to_length(tmp, matrix, inner);
    FastVecAdd(origin, origin, tmp);
    origin[2] += 1;

    part_spawn_random_direction_effect(jitter, inner, outer);
    FastVecAdd(end, jitter, origin);
    gfx_draw_billboard_quad(origin, sprite, 0x60804020, layer, *(float *)(d + 0x228) * 2, 0.08f, math_random_angle());
    gfx_draw_billboard_quad(origin, sprite, 0x80808080, layer, *(float *)(d + 0x228) * 1.5f, 0.08f, math_random_angle());
    part_spawn_random_direction_effect(jitter, inner, outer);
    FastVecAdd(end, jitter, origin);
    gfx_draw_billboard_quad(end, sprite, 0x60804020, layer, *(float *)(d + 0x228) * 2, 0.08f, math_random_angle());
    gfx_draw_billboard_quad(end, sprite, 0x80808080, layer, *(float *)(d + 0x228) * 1.5f, 0.08f, math_random_angle());
    part_spawn_random_direction_effect(jitter, inner, outer);
    FastVecAdd(end, jitter, origin);
    gfx_draw_billboard_quad(end, sprite, 0x60804020, layer, *(float *)(d + 0x228) * 2, 0.08f, math_random_angle());
    gfx_draw_billboard_quad(end, sprite, 0x80808080, layer, *(float *)(d + 0x228) * 1.5f, 0.08f, math_random_angle());

    FastVecSub(ray, d + 0x2e0, origin);
    vec_scale_to_length(ray, ray, *(float *)(d + 0x238) * 60);
    FastVecAdd(ray, ray, origin);
    hit = CollLine(origin, ray, mask, moby, flags);
    if (hit) {
        qcopy_nc(impact, D_L19_001BFEA0);
    } else {
        qcopy_nc(impact, ray);
    }

    factor[0] = 0;
    factor[1] = 0;
    factor[2] = 1;
    factor[3] = 1;
    FastVecSub(jitter, origin, D_L19_001B9A40);
    FastVecSub(other, impact, D_L19_001B9A40);
    vec_scale_to_length(jitter, jitter, 1);
    vec_scale_to_length(other, other, 1);
    FastVecCross(jitter, jitter, factor);
    vec_scale_to_length(jitter, jitter, *(float *)(d + 0x234) * 2);
    FastVecCross(other, other, factor);
    vec_scale_to_length(other, other, *(float *)(d + 0x234) * 2);

    texture = 14;
    q.texture = GetEffectTextureDescriptor(texture);
    q.state = 0xff9000000260L;
    q.flags = 0x8000000048L;
    q.zero = 0;
    q.color[0] = q.color[1] = q.color[2] = q.color[3] = 0x80804020;
    for (i = 0; i < 4; i++) {
        q.uv[i].u = D_L19_001B1C08[i].u;
        q.uv[i].v = D_L19_001B1C08[i].v;
    }

    FastVecSub(corner, origin, jitter);
    *(TI128 *)q.p[0] = *(TI128 *)corner;
    FastVecAdd(corner, origin, jitter);
    *(TI128 *)q.p[1] = *(TI128 *)corner;
    FastVecSub(corner, impact, other);
    *(TI128 *)q.p[2] = *(TI128 *)corner;
    tag = 0;
    mode = 0;
    FastVecAdd(corner, impact, other);
    *(TI128 *)q.p[3] = *(TI128 *)corner;
    draw_world_quad(&q, tag, mode);

    vec_scale_to_length(jitter, jitter, *(float *)(d + 0x234) * 1.5f);
    vec_scale_to_length(other, other, *(float *)(d + 0x234) * 1.5f);
    q.color[0] = q.color[1] = q.color[2] = q.color[3] = 0x80806060;
    draw_world_quad(&q, tag, mode);
    qcopy(d + 0x2c0, impact);
}

/* func_L19_0041B078 is defined in L19_0041B078-g8.c. */

/* func_L19_0041BFD0 is defined in L19_0041BFD0-g8.c. */

extern u16 *D_L19_001FB5A0[];
extern u8 *g_moby_l19_array[] __attribute__((sda));
extern s32 D_L19_001B2A38[] __attribute__((sda));

/* Mark every entity in this object's group state. */
void group_mark_entities(u8 *object)
{
    u16 *group_ptr;
    u8 *entity;

    if (object[0x21] == 0xFF)
        return;
    group_ptr = D_L19_001FB5A0[object[0x21]];
    while (object[0x21] != 0xFF && object[0x21] <= D_L19_001B2A38[0] && group_ptr != 0 &&
           ((group_ptr != 0 && (s16)group_ptr[-1] >= 0) || group_ptr == D_L19_001FB5A0[object[0x21]])) {
        entity = g_moby_l19_array[0] + ((*group_ptr & 0x7FFF) << 8);
        if (entity == 0)
            break;
        *(s32 *)(*(u8 **)(entity + 0x68) + 0x240) = 1;
        group_ptr++;
    }
}

/* A separate no-op moby handler, entered by fifteen class records. */
void spaceship_attachment_update(void *object)
{
}


/* func_L19_0041E5B0 is defined in L19_003E9400-lift-g8.c. */

/* func_L19_0041EE60 is defined in L19_0041EE60.c. */

/* func_L19_004203F0 is defined in L19_004203F0-g8.c. */

extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void moby_set_state(void *, int, int);
extern s32 g_current_map_index __attribute__((sda));
extern u8 D_0019B2E8[];
extern u8 *g_moby_l19_array[] __attribute__((sda));
extern char g_sound_state[];
extern float D_L19_001A8F20[] MACRO_ADDR;
extern float vec_spring_to_target(void *, void *, void *, float, float, float);
extern int PlayMobySound(int, int, void *);
extern float fast_vec_dist(void *, void *);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
extern void gfx_draw_beam_along_heading(void *);
extern void make_hit_descriptor(float, void *, void *, int, void *);
extern int CollLine(void *, void *, int, void *, void *);

/* Moves the object between two points. State 0 records its home position and builds the far
   point (along the axis at 0xC0, raised by the first state word); state 1 waits for its trigger
   flag or for its linked entity to leave state 0; states 2 and 3 move it out and back, keeping
   its looping sound alive, and then cast a collision line along the axis at 0xE0. */
void UpdateGrelbinTriggeredShuttle(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float offset[4] __attribute__((aligned(16)));
    char query[0x30] __attribute__((aligned(16)));
    char *sound_slot;

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        vec_scale_to_length(offset, moby + 0xC0, *(float *)(vars + 4));
        FastVecAdd(vars + 0x30, offset, moby + 0x10);
        *(float *)(vars + 0x38) += *(float *)vars;
        qcopy(vars + 0x20, moby + 0x10);
        *(int *)(vars + 0x40) = -1;
    case 1:
        if ((*(u8 *)(moby + 0xB0) != 0xFF && (D_0019B2E8[*(u8 *)(moby + 0xB0) + (g_current_map_index << 4)] & 0x80)) ||
            (*(int *)(vars + 0x1C) != -1 &&
             *(u8 *)((char *)((*(int *)(vars + 0x1C) << 8) + (int)g_moby_l19_array[0]) + 0x20) != 0))
            moby_set_state(moby, 2, -1);
        break;
    case 2:
        vec_spring_to_target(moby + 0x10, vars + 0x30, vars + 0x14, *(float *)(vars + 8) * 0.00027777778f,
                      *(float *)(vars + 8) * 0.00027777778f, *(float *)(vars + 8) * 0.016666668f);
        sound_slot = g_sound_state + *(int *)(vars + 0x40) * 0x70;
        if (*(char **)(sound_slot + 0x88) != moby || !*(u8 *)(sound_slot + 0x74))
            *(int *)(vars + 0x40) = PlayMobySound(0, 4, moby);
        if (fast_vec_dist(moby + 0x10, vars + 0x30) < *(float *)(vars + 8) * 0.016666668f)
            moby_set_state(moby, 3, -1);
        break;
    case 3:
        sound_slot = g_sound_state + *(int *)(vars + 0x40) * 0x70;
        if (*(char **)(sound_slot + 0x88) != moby || !*(u8 *)(sound_slot + 0x74))
            *(int *)(vars + 0x40) = PlayMobySound(0, 4, moby);
        vec_spring_to_target(moby + 0x10, vars + 0x20, vars + 0x14, *(float *)(vars + 8) * 0.00027777778f,
                      *(float *)(vars + 8) * 0.00027777778f, *(float *)(vars + 8) * 0.016666668f);
        if (fast_vec_dist(moby + 0x10, vars + 0x20) < *(float *)(vars + 8) * 0.016666668f)
            moby_set_state(moby, 2, -1);
        break;
    }
    if (*(u8 *)(moby + 0x20) >= 2) {
        gfx_add_draw_callback_first(gfx_draw_beam_along_heading, moby);
        make_hit_descriptor(4.0f, query, moby, 1, D_L19_001A8F20);
        *(u16 *)(query + 0x1A) = *(u16 *)(moby + 0xAA);
        vec_scale_to_length(offset, moby + 0xE0, *(float *)(vars + 0xC));
        FastVecAdd(offset, moby + 0x10, offset);
        CollLine(moby + 0x10, offset, 0, moby, query);
    }
}


extern int D_L19_001C9FC0[];
extern void BuildObjectAttachmentTransforms(char *, char *, int, int, int, int, int, int);
extern void moby_update_attached_transforms(char *, char *);
extern void euler_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);

/* Arms the rig object once its data arrives, then, when the level word matches the rig's tag, applies the stored rotations to the object and to every joint record. */
void rotated_rig_update(char *moby)
{
    char *rig = *(char **)(moby + 0x68);
    float turn[4] __attribute__((aligned(16)));
    char mat[0x30] __attribute__((aligned(16)));
    char *joint;
    int tag;

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        if (*(long *)rig != -1) {
            { u8 a = 0xFF; *(u8 *)(moby + 0x30) = a; }
            BuildObjectAttachmentTransforms(moby, rig + 0x30, 0x32, *(s32 *)(rig + 4), *(s32 *)rig, *(s32 *)(rig + 8), 7, 0);
            if (*(u8 *)(rig + 0x7A) == 0) {
                moby_mark_spawned((u8 *)moby);
            } else {
                *(u8 *)(rig + 0x7D) = 1;
                *(u16 *)(moby + 0x34) |= 0x104;
                euler_rotation_basis(moby + 0xC0, moby + 0xF0);
                *(u8 *)(moby + 0x20) = 1;
            }
        }
        return;
    case 1:
        if (D_L19_001C9FC0[0] == *(s32 *)(rig + 0xC)) {
            turn[0] = *(float *)(rig + 0x10) * 0.00029088825f;
            turn[1] = *(float *)(rig + 0x14) * 0.00029088825f;
            turn[2] = *(float *)(rig + 0x18) * 0.00029088825f;
            euler_rotation_basis(mat, turn);
            multiply_matrix3x3(moby + 0xC0, moby + 0xC0, mat);
            joint = rig + 0x30;
            do {
                turn[0] = *(float *)(rig + 0x1C) * 0.00029088825f;
                turn[1] = *(float *)(rig + 0x20) * 0.00029088825f;
                turn[2] = *(float *)(rig + 0x24) * 0.00029088825f;
                euler_rotation_basis(mat, turn);
                multiply_matrix3x3(joint, joint, mat);
                tag = *(u8 *)(joint + 0x4A);
                joint += 0x50;
            } while (tag != 1);
            moby_update_attached_transforms(moby, rig + 0x30);
        }
        break;
    }
}

/* func_L19_00421E80 is defined in L19_00421E80-g8.c. */

/* func_L19_00422238 is defined in L19_00422238.c. */

extern u16 *D_L19_001FB5A0[];
extern u8 *g_moby_l19_array[] __attribute__((sda));
extern s32 D_L19_001B2A38[] __attribute__((sda));
extern s32 g_current_map_index __attribute__((sda));
extern u8 D_0019B2E8[];
extern char D_0019B4A8[];

extern s32 flag_is_third_pending_set(u8 *);
extern void moby_mark_spawned(u8 *);
extern void moby_set_group_enabled(s32, s32);

/* The part of the object's state this function reads: the id of its first entity, three group
   words, four mark words (-1 means none). */
typedef struct {
    s32 first;
    s32 groups[3];
    u8 pad[0x10];
    s32 marks[4];
} GrelbinState;

/* Leaves at once when byte 0xBC is clear, func_002B38B8 returns zero, the entity of state word 0
   is in neither state 0xFE nor 0xFD and the table byte of the object lacks bit 7; otherwise hands
   every entity of the three groups to func_0029F338, releases the four marks, counts one nibble of
   the table byte at 0xB2 up (saturating at 7) and releases the object. */
void group_release_linked_when_triggered(u8 *moby)
{
    GrelbinState *state = *(GrelbinState **)(moby + 0x68);
    u16 *group_ptr;
    u8 *entity;
    u8 *first;
    s32 i;
    s32 k;
    u16 flag_word;

    if (moby[0xBC] == 0) {
        if (flag_is_third_pending_set(moby) == 0) {
            if (state->first != -1) {
                first = (u8 *)((state->first << 8) + (int)g_moby_l19_array[0]);
                if (first[0x20] != 0xFE) {
                    if (first[0x20] != 0xFD) {
                        if ((D_0019B2E8[moby[0xB0] + g_current_map_index * 16] & 0x80) == 0)
                            return;
                    }
                }
            }
        }
    }
    for (i = 0; i < 3; i++) {
        if (state->groups[i] == -1)
            continue;
        for (group_ptr = D_L19_001FB5A0[state->groups[i]];
             (state->groups[i] & 0xFF) != 0xFF && state->groups[i] <= D_L19_001B2A38[0] &&
             group_ptr != 0 && ((s16)group_ptr[-1] >= 0 || group_ptr == D_L19_001FB5A0[state->groups[i]]);
             group_ptr++) {
            entity = g_moby_l19_array[0] + ((*group_ptr & 0x7FFF) << 8);
            if (entity == 0)
                break;
            moby_mark_spawned(entity);
        }
    }
    for (k = 0; k < 4; k++) {
        if (state->marks[k] != -1)
            moby_set_group_enabled(state->marks[k], 1);
    }
    flag_word = *(u16 *)(moby + 0xB2);
    if (flag_word & 1) {
        u8 *q = (u8 *)(((s16)flag_word >> 1) + (g_current_map_index << 10)) + (int)D_0019B4A8;
        u8 c = *q;

        if (((c >> 4) & 7) != 7)
            *q = c + 0x10;
    } else {
        u8 *q = (u8 *)(((s16)flag_word >> 1) + (g_current_map_index << 10)) + (int)D_0019B4A8;
        u8 c = *q;

        if ((c & 7) != 7)
            *q = c + 1;
    }
    moby_mark_spawned(moby);
}

/* func_L19_00422A98 is defined in L19_00422A98-g8.c. */

extern char D_L19_001B9A40[];
extern float D_L19_001B1ECC[] SDATA(D_L19_001B1ECC);
extern float D_L19_001B1ED0[] SDATA(D_L19_001B1ED0);
extern float D_L19_001B1ED4[] SDATA(D_L19_001B1ED4);
extern float D_L19_001B1ED8[] SDATA(D_L19_001B1ED8);
extern u8 D_L19_001B1EDC[] SDATA(D_L19_001B1EDC);
extern int D_L19_001B1EE0[] SDATA(D_L19_001B1EE0);
extern int D_L19_001B1EE4[] SDATA(D_L19_001B1EE4);
extern float D_L19_001B1EE8[] SDATA(D_L19_001B1EE8);
extern float D_L19_001B1EEC[] SDATA(D_L19_001B1EEC);
extern u32 D_L19_001B1EF0[] SDATA(D_L19_001B1EF0);
extern u32 D_L19_001B1EF4[] SDATA(D_L19_001B1EF4);
extern int D_L19_001B1EFC[] SDATA(D_L19_001B1EFC);
extern int D_L19_001B1F00[] SDATA(D_L19_001B1F00);
extern int g_frame_l19_counter[] __attribute__((sda));
extern int math_random_int_below(int);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void vec_random_direction(float *, float, float);
extern void *part_spawn_hero_relative(void *, void *, int, unsigned char, unsigned char, int, float);
extern void FastVecSub(void *, void *, void *);
extern float IntToFloat(int);
extern float math_fabs(float);
extern int FastTweenColor(unsigned int, unsigned int, float);
extern unsigned char *part_spawn_fading(void *, int, unsigned char, int, int, int, int, float);

/* Emits the glow of this object. Its origin is 1.5 units along the axis at 0xE0 for class
   0x11C7 and joint 0 otherwise. On one call in four it bursts four anchored particles whose
   velocities drift by random steps; every call it spawns four sprites in a line leading from
   the origin away from the point D_L19_001B9A40, coloured and faded by the counter at
   D_L19_001B2508 and scaled by the object's size. */
void EmitGrelbinGlowSprites(char *moby)
{
    float origin[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float jitter[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float step[4] __attribute__((aligned(16)));
    int i, color, alpha, spriteAlpha;
    float inv255, half, three;

    if (*(short *)(moby + 0xAA) == 0x11C7 /* moby class 4551 */) {
        vec_scale_to_length(point, moby + 0xE0, 1.5f);
        FastVecAdd(origin, moby + 0x10, point);
    } else {
        moby_transform_joint_to_world(moby, 0, origin);
    }
    if (!math_random_int_below(4)) {
        vec_random_direction(velocity, D_L19_001B1ECC[0] * 0.016666668f, D_L19_001B1ED0[0] * 0.016666668f);
        {
            int glowAlpha = D_L19_001B1EDC[0];
            part_spawn_hero_relative(origin, velocity, D_L19_001B1EE0[0], glowAlpha, math_random_int_below(255), 0,
                          D_L19_001B1EE8[0]);
        }
        for (i = 2; i >= 0; i--) {
            vec_random_direction(jitter, D_L19_001B1ED4[0] * 0.016666668f, D_L19_001B1ED8[0] * 0.016666668f);
            FastVecAdd(velocity, velocity, jitter);
            {
                int glowAlpha = D_L19_001B1EDC[0];
                part_spawn_hero_relative(origin, velocity, D_L19_001B1EE4[0], glowAlpha, math_random_int_below(255), 0,
                              D_L19_001B1EEC[0]);
            }
        }
    }
    inv255 = 1.0f / 255.0f;
    half = 0.5f;
    three = 3.0f;
    FastVecSub(point, D_L19_001B9A40, origin);
    vec_scale_to_length(point, point, -0.3f);
    vec_scale_to_length(step, point, 0.1f);
    FastVecAdd(point, point, origin);
    for (i = 0; i < 4; i++) {
        color = FastTweenColor(D_L19_001B1EF0[0], D_L19_001B1EF4[0],
                              math_fabs(half - IntToFloat(255 - ((g_frame_l19_counter[0] + i * 20) & 255)) * inv255));
        alpha = *(u8 *)g_frame_l19_counter;
        if (i & 2)
            alpha *= 2;
        if (i & 1)
            alpha = 255 - alpha;
        spriteAlpha = (u8)alpha;
        part_spawn_fading(point, color, spriteAlpha, D_L19_001B1F00[0], D_L19_001B1EFC[0], 2, 0,
                      (IntToFloat(i) + three) * (*(float *)(moby + 0x2C) / *(float *)(*(char **)(moby + 0x24) + 0x24)));
        FastVecAdd(point, point, step);
    }
}

/* func_L19_00423548 is in L19_003E9400-g8.c. */

/* func_L19_00423A98 is in L19_003E9400-g8.c. */

/* func_L19_00423CC0 is defined in L19_00423CC0.c. */

extern struct { u8 pad[0x464]; u8 flags[1]; } D_L19_0021EA30;
extern int math_fast_float_d(void *);
extern float math_fast_sin_or_cos_a(float);
extern void FastVecScale(void *, void *, float);
extern void mat_combine_and_store(void *, void *, void *, void *);

/* Moves the object down 6 units along a smooth curve once a linked object is done, and signals another object first. */
void sinking_l19_platform_update(u8 *moby)
{
    u8 *vars = *(u8 **)(moby + 0x68);
    float oldPos[4] __attribute__((aligned(16)));
    float oldRot[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    int bits;
    float ease;
    qcopy(oldPos, moby + 0x10);
    qcopy(oldRot, moby + 0xF0);
    switch (moby[0x20]) {
    case 0: {
        u8 *other;
        u16 id;
        *(int *)(vars + 0x5C) |= 1;
        *(float *)(vars + 0x74) = 0;
        qcopy(vars + 0x60, moby + 0x10);
        if (*(int *)(vars + 0x7C) == -1) goto alreadyActive;
        other = (u8 *)((*(int *)(vars + 0x7C) << 8) + (int)g_moby_l19_array[0]);
        if (other[0x20] == 0xFE) goto alreadyActive;
        if (other[0x20] == 0xFD) goto alreadyActive;
        id = *(u16 *)(other + 0xB2);
        if (D_L19_0021EA30.flags[(s16)id]) goto alreadyActive;
        bits = *((u8 *)(((s16)id >> 1) + (g_current_map_index << 10)) + (int)D_0019B4A8);
        if (id & 1) {
            if ((bits >> 4) & 7) goto alreadyActive;
        } else if (bits & 7) goto alreadyActive;
        goto initialize;
    alreadyActive:
        *(u16 *)(moby + 0x34) |= 2;
        moby_set_state(moby, 4, -1);
        break;
    initialize:
        moby[0x30] = 0xFF;
        *(float *)(moby + 0x18) -= 6.0f;
        moby_set_state(moby, 1, -1);
        break;
    }
    case 1: {
        u8 *other;
        u16 id;
        other = (u8 *)((*(int *)(vars + 0x7C) << 8) + (int)g_moby_l19_array[0]);
        id = *(u16 *)(other + 0xB2);
        if (D_L19_0021EA30.flags[(s16)id]) goto activate;
        bits = *((u8 *)(((s16)id >> 1) + (g_current_map_index << 10)) + (int)D_0019B4A8);
        if (id & 1) {
            if ((bits >> 4) & 7) goto activate;
        } else if (bits & 7) goto activate;
        break;
    activate:
        if (*(int *)(vars + 0x80) != -1)
            ((u8 *)((*(int *)(vars + 0x80) << 8) + (int)g_moby_l19_array[0]))[0xBC] = 1;
        moby_set_state(moby, 2, -1);
        break;
    }
    case 2:
        if (math_fast_float_d(vars + 0x78)) moby_set_state(moby, 3, -1);
        break;
    case 3:
        *(float *)(vars + 0x74) += 1.0f / *(float *)(vars + 0x70);
        if (*(float *)(vars + 0x74) > 1.0f) *(float *)(vars + 0x74) = 1.0f;
        ease = (math_fast_sin_or_cos_a(*(float *)(vars + 0x74) * 3.1415927f) + 1.0f) * 0.5f;
        qzero_nc(delta);
        delta[2] = -6.0f;
        FastVecScale(delta, delta, ease);
        FastVecAdd(moby + 0x10, vars + 0x60, delta);
        if (*(float *)(vars + 0x74) >= 1.0f) moby_set_state(moby, 4, -1);
        break;
    case 4:
        if (*(int *)(vars + 0x80) == -1 || ((u8 *)((*(int *)(vars + 0x80) << 8) + (int)g_moby_l19_array[0]))[0xBC] == 0)
            *(u16 *)(moby + 0x34) |= 2;
        break;
    }
    if (moby[0x20] < 4) {
        FastVecSub(delta, moby + 0x10, oldPos);
        mat_combine_and_store(vars + 0x20, delta, oldRot, moby + 0xF0);
    }
}
