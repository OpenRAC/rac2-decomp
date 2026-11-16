#include "include_asm.h"
#include "common.h"

extern float IntToFloat(int);
/* Partial view of the shared screen/render state. */
typedef struct {
    char pad[0xA0];
    float fA0, fA4;
    char gap[8];
    float fB0;
    char gapB4[0x14C];
    float f200, f204, f208, f20C;
    char gap210[8];
    float f218, f21C;
    char gap220[8];
    float f228, f22C;
    int color[3];
} ScreenState;
extern ScreenState g_view_params;
extern void UpdateViewContext(void);

extern void F4778f810_FUN_002B00D8(char *a, char *b, char *c, f32 d);

extern void F4778f810_FUN_00282CC0(char *a, char *b, char *c);

extern void F4778f810_FUN_00283098(char *a, char *b, char *c);

extern void F4778f810_FUN_00283958(char *a, char *b);

extern void F4778f810_FUN_00283738(char *a, char *b, char *c);

extern void F4778f810_FUN_00282CF0(char *a, char *b, char *c);

#ifndef RAC2_T_V4_F4778F810
#define RAC2_T_V4_F4778F810
typedef struct {
    f32 x, y, z, w;
} V4_F4778f810;
#endif

#ifndef RAC2_T_SUB_F4778F810
#define RAC2_T_SUB_F4778F810
typedef struct {
    u8 pad000[0x10];
    u8 at010[0x10];
    u8 at020[0x28];
    f32 f048;
} Sub_F4778f810;
#endif

#ifndef RAC2_T_OBJ_F4778F810
#define RAC2_T_OBJ_F4778F810
typedef struct {
    u8 pad000[0x10];
    u8 at010[0x58];
    char *p068;
    u8 pad06C[0xC0 - 0x6C];
    u8 at0C0[0x10];
} Obj_F4778f810;
#endif

/* Append an observed point index and update the original geometric descriptor. */
typedef struct {
    unsigned char gap0[0x10];
    float plane[4];
    unsigned char gap20[0x10];
    float (*points)[4];
    unsigned char gap34[0x25];
    unsigned char indices[3];
    unsigned char count;
} OozlaAppendDescriptor164;

typedef struct {
    unsigned char gap0[0x68];
    OozlaAppendDescriptor164 *descriptor;
    unsigned char gap6c[0x54];
    float transform[3][4];
} OozlaAppendObject164;

extern void coll_prune_index_set_by_projection(OozlaAppendObject164 *, int, const float *);

extern void FastVecSub(float *, const float *, const float *);

extern void matrix_mul_vec3(float *, const float *, const float *);

extern void vec_scale_by_direction(OozlaAppendObject164 *, float *, const float *);

extern void vec_fast_normalize(void *a, void *b, void *c);

extern float func_00282DF0_5(void *a);

extern float func_00282DB0_3(void *a, void *b);

extern f32 func_002AA2E8_2(float *p, float a, float b);

extern void func_00282F20_16(void *a, void *b, float f);

/* Measured partial layouts; original type and game roles are unknown. */
struct Rac2Native_00169805055547ed_Rec31cd0302 {
    int v[10];
};

extern struct Rac2Native_00169805055547ed_Rec31cd0302 g_slot_l04_value_table[];

extern char Fd8e166aa_D_001B7F80[];

extern int Fcdb4d905_FUN_0027A0F8(int a, int b, int c);

extern void lerp_vector(float *out, float *a, float *b, float t);
extern void vec_scale_to_length(float *out, float *in, float s);
extern void FastVecCross(float *out, float *a, float *b);
extern void cam_compute_view_direction(float *a, float *b, int c);
extern void quaternion_to_rotation_basis(float *a, float *b);
extern void multiply_matrix3x3(float *a, float *b, float *c);
extern void coll_clamp_movement_vector(char *o, float *p, float *v);

/* Hit-index descriptor: a vector at 0x20 (its w is the scale), the point array at 0x30,
   the collision data at 0x54, the point count at 0x58, three used indices at 0x59 and
   the used count at 0x5C. */
typedef struct {
    u8 pad000[0x20];
    f32 vec020[4];
    f32 (*points030)[4];
    u8 pad034[0x20];
    char *p054;
    u8 count058;
    u8 indices059[3];
    u8 count05C;
} HitIndex_00274500;

extern int coll_test_segment_hit(float *a, float *b, int c, int d);

extern int coll_test_point(float *out, int mode, float scale, char *data);

extern float g_coll_hit_position[];

/* Collision-hit nudge subject: geometry plane at 0x20, scale 0x2C, data pointer 0x54. */
typedef struct {
    u8 pad000[0x20];
    u8 at020[0xC];
    f32 f02C;
    u8 pad030[0x24];
    char *p054;
} HitNudge_002746C8;

extern float g_coll_hit_point[];

extern void vec_set_direction_with_complement(float *, float *, float);

extern void FastVecScale(void *, void *, float);

extern void gfx_wait_for_dma_status_bits(int);
extern void gfx_select_packet_buffer_setup(void);
extern void gfx_reset_packet_buffer(void);
extern void FadeToBlack(int);
extern int g_saved_draw_position;
extern int g_vram_frame_base __attribute__((sda));

extern int math_fast_float_d(void *);
extern char g_shared_data_block[];

/* Index holder at 0x1B7F80: the current item index and the key that goes with it. */
typedef struct {
    char pad000[0x20];
    unsigned short idx;
    unsigned short idx2;
} OozlaIndex_001B7F80;

/* Item table at 0x1B8308: 32 entries of 40 bytes; the group key first, the item pointer at 0x1C. */
typedef struct {
    int key;
    char pad004[0x18];
    int ptr;
    char pad020[8];
} OozlaEntry_001B8308;

typedef struct {
    OozlaEntry_001B8308 e[32];
    int count;
} OozlaTable_001B8308;

extern OozlaTable_001B8308 g_disc_player_seq_table;
extern int AdvanceGroupedTableOffset(int, int *, int *);

/* The index holder itself, named through the symbol the file already uses for it. */
#define OozlaHolder ((OozlaIndex_001B7F80 *)Fd8e166aa_D_001B7F80)

/* The level's state word.  It sits at a different address in every program that has
   this function (0x1B1580 in the boot, 0x1B18C0 in level 00, and so on), so it is a
   per-level external.  The sda attribute makes the compiler emit a bare symbol
   reference; the assembler then expands it - in reorder mode, and with the symbol's
   size still unknown - into the retail's "lui $reg,0x1B" plus offset, with the
   address in $at for the stores.  This unit therefore has to stay at -G0: a -G8
   sibling would emit the .extern directive, and the reference would become
   gp-relative instead. */
extern int ref_L00_002E38F0_00 __attribute__((sda));

extern int g_vis_update_mode __attribute__((sda));
extern char g_visibility_bitmap[];
extern void mem_clear(void *, int, int);
extern void UpdateVisibilityBitmap(void);

/* Occlusion state read by func_0027A288: the camera position, the current and
   merged visibility bitmaps, and the two fallback tables (octant and
   directional, both a 16-byte origin followed by 128-byte bitmaps). */
typedef struct { float origin[4]; char visibility[0][128]; } OcclDirectional;
typedef struct { char pad[0x140]; float position[3]; } OcclCamera;
extern OcclCamera g_active_camera;
extern char g_visibility_work_bitmap[128];
extern float *g_vis_cell_cursor __attribute__((sda));
extern float *g_vis_directional_data __attribute__((sda));
extern int g_vis_fallback_mode __attribute__((sda));
extern int g_vis_cell_found_flag __attribute__((sda));
extern unsigned char *g_vis_previous_bitmap __attribute__((sda));
extern int FloatToInt(float);
extern void mem_fast_helper_c(void *, const void *, int);
extern void mem_fast_helper_b(void *, int);
extern void mem_fast_helper_d(void *, const void *, const void *, int);
extern float mat_fast_helper_a(float, float);
extern float vec_distance_xy(const void *, const void *);

/* The screen extent record: size, half size and the four <<4 edges around 0x800. Its
   fields are stored as symbol+offset, which this cc1 counts as two-instruction macro
   stores, so none of them takes a call's delay slot (retail's order). */
typedef struct {
    int width, height, half_width, half_height;
    int left, top, right, bottom;
} ScreenExtent;
extern ScreenExtent g_screen_width __attribute__((sda));
typedef struct { char pad[0x150]; short width, height; } ScreenDimensions;
extern ScreenDimensions g_screen_adjust_offsets;

/* Moves a game object toward its target using the saved path data, then turns it to match. */
void path_apply_move_step(Obj_F4778f810 *obj)
{
    V4_F4778f810 tmp[6];
    Sub_F4778f810 *vars = (Sub_F4778f810 *)obj->p068;

    F4778f810_FUN_002B00D8((char *)obj + 0x10, (char *)vars, (char *)vars, vars->f048);
    F4778f810_FUN_00282CC0((char *)obj + 0x10, (char *)obj + 0x10, (char *)vars);
    F4778f810_FUN_00283098((char *)&tmp[0], (char *)vars + 0x20, (char *)obj + 0xC0);
    F4778f810_FUN_00283958((char *)vars + 0x10, (char *)&tmp[3]);
    F4778f810_FUN_00283738((char *)obj + 0xC0, (char *)&tmp[3], (char *)obj + 0xC0);
    F4778f810_FUN_00283098((char *)&tmp[1], (char *)vars + 0x20, (char *)obj + 0xC0);
    F4778f810_FUN_00282CF0((char *)&tmp[2], (char *)&tmp[1], (char *)&tmp[0]);
    F4778f810_FUN_00282CF0((char *)obj + 0x10, (char *)obj + 0x10, (char *)&tmp[2]);
}

/* Same movement step as the one before it, kept as a separate copy for another group of objects. */
void path_apply_move_step_copy(Obj_F4778f810 *obj)
{
    V4_F4778f810 tmp[6];
    Sub_F4778f810 *vars = (Sub_F4778f810 *)obj->p068;

    F4778f810_FUN_002B00D8((char *)obj + 0x10, (char *)vars, (char *)vars, vars->f048);
    F4778f810_FUN_00282CC0((char *)obj + 0x10, (char *)obj + 0x10, (char *)vars);
    F4778f810_FUN_00283098((char *)&tmp[0], (char *)vars + 0x20, (char *)obj + 0xC0);
    F4778f810_FUN_00283958((char *)vars + 0x10, (char *)&tmp[3]);
    F4778f810_FUN_00283738((char *)obj + 0xC0, (char *)&tmp[3], (char *)obj + 0xC0);
    F4778f810_FUN_00283098((char *)&tmp[1], (char *)vars + 0x20, (char *)obj + 0xC0);
    F4778f810_FUN_00282CF0((char *)&tmp[2], (char *)&tmp[1], (char *)&tmp[0]);
    F4778f810_FUN_00282CF0((char *)obj + 0x10, (char *)obj + 0x10, (char *)&tmp[2]);
}

/* Slides an object along the one or two touched points, then nudges it back out of the wall it hit. */
void moby_slide_along_hit_points(char *moby)
{
    float a[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float h[4] __attribute__((aligned(16)));
    float i[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    float e[4] __attribute__((aligned(16)));
    float f[4] __attribute__((aligned(16)));
    float g[3][4] __attribute__((aligned(16)));
    unsigned char *vars = *(unsigned char **)(moby + 0x68);
    float *xform;

    if (vars[0x5C] >= 2) {
        lerp_vector(a, (float *)(*(char **)(vars + 0x30) + vars[0x59] * 16), (float *)(*(char **)(vars + 0x30) + vars[0x5A] * 16), 0.5f);
        FastVecSub(b, (float *)(*(char **)(vars + 0x30) + vars[0x59] * 16), (float *)(*(char **)(vars + 0x30) + vars[0x5A] * 16));
        matrix_mul_vec3(b, b, (float *)(moby + 0xC0));
        xform = (float *)(moby + 0xC0);
    } else {
        qcopy(a, *(char **)(vars + 0x30) + vars[0x59] * 16);
        xform = (float *)(moby + 0xC0);
    }
    matrix_mul_vec3(c, a, xform);
    cam_compute_view_direction((float *)(moby + 0x10), d, 1);
    FastVecSub(e, a, (float *)(vars + 0x20));
    matrix_mul_vec3(e, e, xform);
    vec_scale_to_length(e, e, 1.0f);
    FastVecCross(f, e, d);
    vec_scale_to_length(f, f, *(float *)(vars + 0x4C));
    coll_clamp_movement_vector(moby, (float *)(vars + 0x10), f);
    if (vars[0x5C] >= 2)
        vec_scale_by_direction(moby, (float *)(vars + 0x10), b);
    quaternion_to_rotation_basis((float *)(vars + 0x10), g[0]);
    multiply_matrix3x3(xform, g[0], xform);
    matrix_mul_vec3(h, a, xform);
    FastVecSub(i, h, c);
    FastVecSub((float *)(moby + 0x10), (float *)(moby + 0x10), i);
}

/* Checks the object against nearby points that have not been used yet and pushes it out of the first one that is touching. Returns that point number, or -1 if none. */
int moby_push_out_of_hit_point(Obj_F4778f810 *obj)
{
    float tmp0[4];
    float tmp1[4];
    float tmp2[4];
    float tmp3[4];
    float *hit_info;
    HitIndex_00274500 *vars = (HitIndex_00274500 *)obj->p068;
    int i;
    int j;
    int used;
    int hit;
    float scale;

    matrix_mul_vec3(tmp0, vars->vec020, (float *)((char *)obj + 0xC0));
    F4778f810_FUN_00282CC0((char *)tmp0, (char *)tmp0, (char *)obj + 0x10);
    hit = coll_test_point(tmp0, 0x62, vars->vec020[3], vars->p054);
    if (hit != 0) {
        for (i = 0; i < vars->count058; i++) {
            used = 0;
            for (j = 0; j < vars->count05C; j++) {
                if (vars->indices059[j] == i) {
                    used = 1;
                    break;
                }
            }
            if (used)
                continue;
            matrix_mul_vec3(tmp1, vars->points030[i], (float *)((char *)obj + 0xC0));
            F4778f810_FUN_00282CC0((char *)tmp1, (char *)tmp1, (char *)obj + 0x10);
            if (coll_test_segment_hit(tmp0, tmp1, hit, 0) != 0) {
                hit_info = g_coll_hit_position;
                F4778f810_FUN_00282CF0((char *)tmp2, (char *)tmp1, (char *)hit_info);
                func_00282F20_16(hit_info + 8, hit_info + 8, 1.0f);
                scale = func_00282DB0_3(tmp2, hit_info + 8);
                func_00282F20_16(tmp3, hit_info + 8, -scale);
                F4778f810_FUN_00282CC0((char *)obj + 0x10, (char *)obj + 0x10, (char *)tmp3);
                return i;
            }
        }
        return -1;
    }
    vars->count05C = 0;
    return -1;
}

/* Tests one touch point of the object and pushes the object away from the hit surface. Returns 1 if there was a hit. */
int moby_push_away_from_hit(Obj_F4778f810 *obj)
{
    V4_F4778f810 tmp[2];
    HitNudge_002746C8 *vars = (HitNudge_002746C8 *)obj->p068;

    matrix_mul_vec3((char *)&tmp[0], (char *)vars + 0x20, (char *)obj + 0xC0);
    FastVecAdd((char *)&tmp[0], (char *)&tmp[0], (char *)obj + 0x10);
    if (coll_test_point((float *)&tmp[0], 2, vars->f02C, vars->p054) != 0) {
        FastVecSub((char *)&tmp[1], (char *)g_coll_hit_point, (char *)&tmp[0]);
        FastVecAdd((char *)obj + 0x10, (char *)obj + 0x10, (char *)&tmp[1]);
        return 1;
    }
    return 0;
}

/* appendindexbyte59/count5C descriptor68, originalthreeGPR geometricupdate inclincomingdirectionA2, ifcount!=1 originalpointdifference24/transform40/bound80 andterminalcountbyte return */
unsigned int coll_append_hit_point_index(OozlaAppendObject164 *object, unsigned int index, const float *direction)
{
    float difference[4];
    OozlaAppendDescriptor164 *descriptor = object->descriptor;
    descriptor->indices[descriptor->count] = index;
    ++descriptor->count;
    coll_prune_index_set_by_projection(object, (int)descriptor->count - 1, direction);
    if (descriptor->count != 1) {
        FastVecSub(difference, descriptor->points[descriptor->indices[0]], descriptor->points[descriptor->indices[1]]);
        matrix_mul_vec3(difference, difference, &object->transform[0][0]);
        vec_scale_by_direction(object, descriptor->plane, difference);
    }
    return descriptor->count;
}

/* Turns a direction into a unit length and uses it to move the given vector. */
void vec_scale_by_direction(OozlaAppendObject164 *a0, float *vec, const float *direction) {
    float tmp[4];
    float value;
    func_00282F20_16(tmp, (void *)direction, 1.0f);
    value = func_00282DB0_3(tmp, vec);
    vec_set_direction_with_complement(vec, tmp, value);
}

/* Keeps the float one helper returns, and when a later helper reports a ratio above 0.7 scales it by a factor with a floor, hands it to a setter through a local, then reports whether the kept value is non-zero. */
/* Shortens a vector and then scales it again if it points mostly in the same direction as another one. Returns 1 if some length is left. */
int vec_shorten_by_dot(void *vec, void *other, void *compare, float scale, float minimum)
{
    float saved;
    float scaled;
    float dot;

    vec_fast_normalize(vec, vec, other);
    saved = func_00282DF0_5(vec);
    dot = func_00282DB0_3(compare, other);
    if (dot > 0.7f) {
        scaled = saved * scale;
        if (scaled < minimum) scaled = minimum;
        func_002AA2E8_2(&saved, 0.0f, scaled);
        func_00282F20_16(vec, vec, saved);
    }
    if (saved != 0.0f) return 1;
    return 0;
}

/* Copies up to a limit of stored points into a list of vectors, converting them to real numbers and scaling them. Returns how many were copied. */
int coll_convert_packed_points_to_vectors(char *object, float *output, int limit)
{
    char *data = *(char **)(*(char **)(object + 0x24) + 0x10);
    char *entry, *base;
    float scale;
    int count, remaining;
    float *cursor;
    if (!data)
        return 0;
    count = *(int *)(data + 0xC) / 8;
    base = data + *(int *)(data + 4);
    scale = *(float *)(object + 0x2C) * (1.0f / 1024.0f);
    if (limit < count)
        count = limit;
    entry = base + 16;
    if (count > 0) {
    cursor = output;
    remaining = count;
    do {
        remaining--;
        cursor[0] = IntToFloat(*(short *)entry);
        cursor[1] = IntToFloat(*(short *)(entry + 2));
        cursor[2] = IntToFloat(*(short *)(entry + 4));
        entry += 8;
        FastVecScale(cursor, cursor, scale);
        cursor[3] = 1.0f;
        cursor += 4;
    } while (remaining);
    }
    return count;
}

ASM_FUNC("asm/game", func_00274D90);

ASM_FUNC("asm/game", func_00276158);

ASM_FUNC("asm/game", func_002761F8);

/* Tests a point against the collision data. Returns a hit handle or 0. */
ASM_FUNC("asm/game", func_00277258);

ASM_FUNC("asm/game", func_00277F48);

ASM_FUNC("asm/game", func_00278870);

/* Original VU0 macro implementation: vector/Q/ACC operations and trapping addi.
   The complete 408-byte body is present in boot and all 27 levels of each release. */
ASM_FUNC("asm/game", func_00278CE0);

ASM_FUNC("asm/game", func_00278E78);

/* Resets the graphics state and restores the saved drawing position. */
void gfx_restore_draw_position(void) {
    gfx_wait_for_dma_status_bits(1);
    gfx_select_packet_buffer_setup();
    gfx_reset_packet_buffer();
    g_vram_frame_base = g_saved_draw_position;
    FadeToBlack(30);
}

/* Store ten integer arguments in the indexed record when the unsigned index is below 32; otherwise leave the table unchanged. */
/* Saves ten numbers into one slot of a table of 32 slots. Does nothing if the slot number is too large. */
void table_set_slot_values(int p0, int p1, int p2, int p3, int p4, int p5,
                                      int p6, int p7, int p8, int p9, unsigned idx)
{
    if (idx >= 32u)
        return;
    g_slot_l04_value_table[idx].v[0] = p0;
    g_slot_l04_value_table[idx].v[1] = p1;
    g_slot_l04_value_table[idx].v[2] = p2;
    g_slot_l04_value_table[idx].v[3] = p3;
    g_slot_l04_value_table[idx].v[4] = p4;
    g_slot_l04_value_table[idx].v[5] = p5;
    g_slot_l04_value_table[idx].v[6] = p6;
    g_slot_l04_value_table[idx].v[7] = p7;
    g_slot_l04_value_table[idx].v[8] = p8;
    g_slot_l04_value_table[idx].v[9] = p9;
}

/* Walk the item table from the current index, carrying the offset across entries of one group; return 1 when it lands inside an entry. */
int AdvanceGroupedTableOffset(int value, int *out_index, int *out_offset)
{
    OozlaTable_001B8308 *table;
    char *start_field;
    char *end_field;

    *out_index = (short)OozlaHolder->idx;
    *out_offset = (short)OozlaHolder->idx2 + value;

    while (*out_index >= 0 && *out_index < g_disc_player_seq_table.count) {
        int row, start, end, offset, next_offset;

        table = &g_disc_player_seq_table;
        start_field = (char *)table + 4;
        end_field = (char *)table + 8;
        row = *out_index * sizeof(OozlaEntry_001B8308);
        start = *(int *)(row + start_field);
        end = *(int *)(row + end_field);
        offset = *out_offset;

        if (end >= start + offset)
            return 1;
        if (*out_index + 1 >= table->count)
            return 0;
        if (*(int *)(row + (char *)table) != table->e[*out_index + 1].key)
            return 0;

        next_offset = offset - 1;
        next_offset -= end - start;
        *out_offset = next_offset;
        *out_index = *out_index + 1;
    }
    return 0;
}

/* Asks a helper about the shared data block and returns the answer. */
int data_query_shared_block(void) {
    return math_fast_float_d(g_shared_data_block);
}

/* Moves the current item index to the next group of items in the table. Returns whether it moved on. */
int data_advance_to_next_item_group(void)
{
    int t1, t2;
    OozlaIndex_001B7F80 *g = OozlaHolder;
    int key, found, count;

    if ((short)g->idx == -1) {
        g->idx = 0;
        g->idx2 = 0;
        if (ref_L00_002E38F0_00 == 1) {
            ref_L00_002E38F0_00 = 2;
            g->idx = 4;
            g->idx2 = 0;
        }
        return 1;
    }
    if (AdvanceGroupedTableOffset(g_disc_player_seq_table.e[(short)g->idx].ptr, &t1, &t2)) {
        if (g_disc_player_seq_table.e[(short)g->idx].ptr != 0) {
            g->idx = (unsigned short)t1;
            g->idx2 = (unsigned short)t2;
            return 1;
        }
    }
    {
        OozlaEntry_001B8308 *e = &g_disc_player_seq_table.e[(short)OozlaHolder->idx];

        found = 1;
        count = g_disc_player_seq_table.count;
        key = e->key;
        OozlaHolder->idx2 = 0;
        OozlaHolder->idx = OozlaHolder->idx + 1;
        if ((short)OozlaHolder->idx < count) {
            do {
                if (g_disc_player_seq_table.e[(short)OozlaHolder->idx].key != key) {
                    found = 0;
                } else {
                    OozlaHolder->idx = OozlaHolder->idx + 1;
                }
            } while ((short)OozlaHolder->idx < count && found);
        }
        if ((short)OozlaHolder->idx == 4 && ref_L00_002E38F0_00 == 0) {
            OozlaHolder->idx = 3;
            ref_L00_002E38F0_00 = 1;
            return 0;
        }
    }
    return !found;
}

/* Looks up a cell in the lookup table, trying the nearer of two cells first and the other one if it is empty. */
int vis_find_nearer_cell(float x, int a, int b, int c, int d, int e, int g)
{
    int found, p, q, s;
    if (x < 0.5f) {
        found = Fcdb4d905_FUN_0027A0F8(a, b, c);
        if (found) return found;
        p = d;
        q = e;
        s = g;
    } else {
        found = Fcdb4d905_FUN_0027A0F8(d, e, g);
        if (found) return found;
        p = a;
        q = b;
        s = c;
    }
    return Fcdb4d905_FUN_0027A0F8(p, q, s);
}

/* Fills the visibility bitmap D_001BADC0 for the camera's grid cell (position / 4).
   Without an entry for the cell, mode 0 merges the nearer neighbor along each axis;
   otherwise the mode in D_001B170C picks a fallback: the previous bitmap, all visible,
   an octant table around an origin, or a directional table indexed by azimuth and
   elevation. The last bit is always set. */
void UpdateVisibilityBitmap(void)
{
    float origin[4], delta[4];
    float scale = 0.25f;
    int x, y, z, bx, by, bz, index;
    int xm, xp, ym, yp, zm, zp;
    float fraction;
    unsigned char *vis, *gx, *gy, *gz, *previous;
    float *p;

    x = FloatToInt(g_active_camera.position[0] * scale);
    y = FloatToInt(g_active_camera.position[1] * scale);
    z = FloatToInt(g_active_camera.position[2] * scale);
    vis = (unsigned char *)Fcdb4d905_FUN_0027A0F8(x, y, z);
    if (vis) {
        g_vis_cell_found_flag = 0;
        mem_fast_helper_c(g_visibility_bitmap, vis, 128);
        g_vis_previous_bitmap = vis;
    } else {
        g_vis_cell_found_flag = 1;
        if (g_vis_fallback_mode == 0) {
            xm = x - 1;
            xp = x + 1;
            fraction = IntToFloat(x);
            yp = y + 1;
            zp = z + 1;
            ym = y - 1;
            zm = z - 1;
            gx = (unsigned char *)vis_find_nearer_cell(g_active_camera.position[0] * scale - fraction, xm, y, z, xp, y, z);
            fraction = IntToFloat(y);
            gy = (unsigned char *)vis_find_nearer_cell(g_active_camera.position[1] * scale - fraction, x, ym, z, x, yp, z);
            fraction = IntToFloat(z);
            gz = (unsigned char *)vis_find_nearer_cell(g_active_camera.position[2] * scale - fraction, x, y, zm, x, y, zp);
            if (gx || gy || gz) {
                mem_fast_helper_b(g_visibility_work_bitmap, 128);
                if (gx) mem_fast_helper_d(g_visibility_work_bitmap, g_visibility_work_bitmap, gx, 128);
                if (gy) mem_fast_helper_d(g_visibility_work_bitmap, g_visibility_work_bitmap, gy, 128);
                if (gz) mem_fast_helper_d(g_visibility_work_bitmap, g_visibility_work_bitmap, gz, 128);
                vis = g_visibility_work_bitmap;
                g_vis_previous_bitmap = vis;
                mem_fast_helper_c(g_visibility_bitmap, vis, 128);
            }
        }
        if (!vis) {
            switch (g_vis_fallback_mode) {
            case 0:
                previous = g_vis_previous_bitmap;
                if (previous) mem_fast_helper_c(g_visibility_bitmap, previous, 128);
                else mem_clear(g_visibility_bitmap, -1, 128);
                break;
            case 2:
                p = g_vis_cell_cursor;
                if (p) {
                    bx = 0.0f < g_active_camera.position[0] - p[0];
                    by = 0.0f < g_active_camera.position[1] - p[1];
                    bz = 0.0f < g_active_camera.position[2] - p[2];
                    mem_fast_helper_c(g_visibility_bitmap, (char *)p + ((bz + by * 2 + bx * 4) * 128 + 16), 128);
                    break;
                }
                if (g_vis_previous_bitmap) {
                    mem_fast_helper_c(g_visibility_bitmap, g_vis_previous_bitmap, 128);
                    break;
                }
                /* fall through */
            case 1:
                mem_clear(g_visibility_bitmap, -1, 128);
                break;
            case 3: {
                float *directional = g_vis_directional_data;
                if (directional) {
                    origin[0] = directional[0];
                    origin[1] = directional[1];
                    origin[2] = directional[2];
                    origin[3] = 0;
                    delta[0] = g_active_camera.position[0] - origin[0];
                    delta[1] = g_active_camera.position[1] - origin[1];
                    delta[2] = g_active_camera.position[2] - origin[2];
                    delta[3] = 0;
                    index = 0;
                    if (delta[0] > 0 && delta[1] > 0) {
                        index = FloatToInt(mat_fast_helper_a(delta[0], delta[1]) * 10.185916f) << 6;
                        delta[0] = vec_distance_xy(g_active_camera.position, origin);
                    } else if (delta[0] <= 0 && delta[1] > 0) {
                        index = 1024;
                        if (delta[0] == 0) {
                            delta[0] = delta[1];
                        } else {
                            index += FloatToInt(mat_fast_helper_a(delta[1], -delta[0]) * 10.185916f) << 6;
                            delta[0] = vec_distance_xy(g_active_camera.position, origin);
                        }
                    } else if (delta[0] < 0 && delta[1] < 0) {
                        index = FloatToInt(mat_fast_helper_a(-delta[0], -delta[1]) * 10.185916f) << 6;
                        delta[0] = -vec_distance_xy(g_active_camera.position, origin);
                    } else if (delta[0] >= 0 && delta[1] < 0) {
                        index = 1024;
                        if (delta[0] == 0) {
                            delta[0] = delta[1];
                        } else {
                            index += FloatToInt(mat_fast_helper_a(-delta[1], delta[0]) * 10.185916f) << 6;
                            delta[0] = -vec_distance_xy(g_active_camera.position, origin);
                        }
                    }
                    if (delta[2] > 0 && delta[0] > 0) {
                        index += FloatToInt(mat_fast_helper_a(delta[2], delta[0]) * 10.185916f);
                    } else if (delta[2] <= 0 && delta[0] > 0) {
                        index += 16;
                        if (delta[2] != 0) index += FloatToInt(mat_fast_helper_a(delta[0], -delta[2]) * 10.185916f);
                    } else if (delta[2] < 0 && delta[0] <= 0) {
                        index += 32;
                        if (delta[0] != 0) index += FloatToInt(mat_fast_helper_a(-delta[2], -delta[0]) * 10.185916f);
                    } else if (delta[2] >= 0 && delta[0] < 0) {
                        index += 48;
                        if (delta[2] != 0) index += FloatToInt(mat_fast_helper_a(-delta[0], delta[2]) * 10.185916f);
                    }
                    mem_fast_helper_c(g_visibility_bitmap, ((OcclDirectional *)g_vis_directional_data)->visibility[index], 128);
                } else {
                    previous = g_vis_previous_bitmap;
                    if (previous) {
                        mem_fast_helper_c(g_visibility_bitmap, previous, 128);
                    } else {
                        mem_clear(g_visibility_bitmap, -1, 128);
                    }
                }
                break;
            }
            }
        }
    }
    g_visibility_bitmap[127] |= 128;
}


/* Updates the visibility data depending on the visibility mode setting. */
void vis_update_by_mode(void)
{
    if (g_vis_update_mode == 0)
        mem_clear(g_visibility_bitmap, -1, 0x80);
    else if (g_vis_update_mode == 2)
        UpdateVisibilityBitmap();
}

/* gfx_init_view_context: set the screen extent from the display size and the view's fixed scales. */
/* Sets up the screen size, edges and view limits from the display size. */
void gfx_init_view_context(void)
{
    ScreenDimensions *dimensions = &g_screen_adjust_offsets;
    ScreenState *view = &g_view_params;
    short width = dimensions->width;
    short height = dimensions->height;
    int half_width = width >> 1;
    int half_height = height >> 1;
    float half_height_f;

    g_screen_width.width = width;
    g_screen_width.height = height;
    g_screen_width.half_width = half_width;
    g_screen_width.half_height = half_height;
    g_screen_width.left = (2048 - half_width) << 4;
    g_screen_width.top = (2048 - half_height) << 4;
    g_screen_width.right = (half_width + 2048) << 4;
    g_screen_width.bottom = (half_height + 2048) << 4;

    view->fA0 = 32.0f;
    view->fA4 = 1048576.0f;
    view->fB0 = 0.62f;
    view->f200 = IntToFloat(width) * 0.5f;
    half_height_f = IntToFloat(dimensions->height) * 0.5f;
    view->f204 = half_height_f;
    view->f208 = view->f200 * 4.0f;
    view->f20C = half_height_f * 4.0f;
    view->f218 = 0.0f;
    view->f21C = 524288.0f;
    view->f228 = 255.0f;
    view->f22C = 0.0f;
}

/* gfx_configure_projection: gfx_init_view_context for a given size and scale, with the four
   context values from the arguments, then func_0027AB40. */
/* Sets up the screen size and view limits from the given values, then applies them. */
void gfx_configure_projection(int width, int height, float scale, float a, float b, float c, float d)
{
    ScreenState *context = &g_view_params;
    int halfW = width >> 1;
    int halfH = height >> 1;
    float halfHeight;
    g_screen_width.width = width;
    g_screen_width.height = height;
    g_screen_width.half_width = halfW;
    g_screen_width.half_height = halfH;
    g_screen_width.left = (2048 - halfW) << 4;
    g_screen_width.top = (2048 - halfH) << 4;
    g_screen_width.right = (halfW + 2048) << 4;
    g_screen_width.bottom = (halfH + 2048) << 4;
    context->fB0 = scale;
    context->fA0 = 32.0f;
    context->fA4 = 1048576.0f;
    context->f200 = IntToFloat(width) * 0.5f;
    halfHeight = IntToFloat(height) * 0.5f;
    context->f204 = halfHeight;
    context->f208 = context->f200 * 4.0f;
    context->f20C = halfHeight * 4.0f;
    context->f218 = a;
    context->f21C = b;
    context->f228 = c;
    context->f22C = d;
    UpdateViewContext();
}

/* The full-screen anti-aliasing buffer record behind the screen dimensions above: the
   display size at 0x150 and the storage size at 0x158. */
typedef struct {
    char disp_and_contexts[0x150];
    s16 display_width;
    s16 display_height;
    s16 psm;
    s16 fbp0;
    s16 storage_width;
    s16 storage_height;
} FsAaBuf;
#define FsAaBuffer (*(FsAaBuf *)&D_001A6480)

/* The drawing environment's GS register values, each followed by its register address. */
typedef struct {
    u64 pad0[2];
    u64 frame1;
    u64 pad18;
    u64 frame2;
    u64 pad28;
    u64 zbuf1;
    u64 pad38;
    u64 zbuf2;
    u64 pad48;
    u64 xyoffset1;
    u64 pad58;
    u64 xyoffset2;
    u64 pad68;
    u64 scissor1;
    u64 pad78;
    u64 scissor2;
} GsDrawEnvRegs;

typedef struct {
    char b[0x60];
} GsLoadImage;

extern GsDrawEnvRegs g_gs_draw_env_regs;
extern u64 g_gs_zbuf_reg;
extern u64 g_gs_zbuf_reg_masked;
extern unsigned char g_gs_transfer_buffer[];
extern int g_is_pal_video __attribute__((sda));
extern int g_widescreen_flag __attribute__((sda));
extern int g_vram_cursor __attribute__((sda));
extern int g_vram_fb_offset __attribute__((sda));
extern int g_vram_display_address __attribute__((sda));
extern int g_vram_zbuffer_address __attribute__((sda));
extern int g_vram_texture_base __attribute__((sda));
extern int g_vram_texture_base_copy __attribute__((sda));
extern int g_vram_clut_first __attribute__((sda));
extern int g_vram_clut_second __attribute__((sda));
extern int g_vram_clut_third __attribute__((sda));
extern void FlushCache(int);
extern int gfx_wait_paths_idle(int, int);
extern void SetupFS_AA_buffer(int, int, int, int, int, int);
extern void gfx_append_draw_list_header(void);
extern void gfx_append_draw_list_buffer_tag(int);
extern int gfx_query_display_buffer(void);
extern int func_00126288(GsLoadImage *, s16, s16, s16, s16, s16, s16, s16);
extern int sceGsExecLoadImage(GsLoadImage *, unsigned char *);

/* Adapted from RAC1 SetPalMode (GPL-3.0), with RAC2's mode selection, texture cursors
   and optional image clearing.
   Adapted from Lombyte's project (GPL-3.0): src/video/display/set_pal_mode.c, set_pal_mode. */
void SetPalMode(int clear) {
    GsLoadImage image;
    int n;
    int i;
    u64 zbuf;
    u64 frame;
    u64 scissor;
    s16 w;

    FlushCache(0);
    if (g_is_pal_video != 0) {
        g_vram_zbuffer_address = 0x100000;
        g_vram_display_address = 0x1E0000;
        g_vram_fb_offset = 0;
        g_vram_texture_base = 0x2C0000;
        SetupFS_AA_buffer(0x200, 0x1C0, 0x200, 0x200, 4, 0);
    } else if (g_widescreen_flag != 0) {
        g_vram_zbuffer_address = 0x118000;
        g_vram_display_address = 0x1E8000;
        g_vram_fb_offset = 0;
        g_vram_texture_base = 0x2C0000;
        SetupFS_AA_buffer(0x200, 0x1A0, 0x280, 0x1C0, 0, 0);
    } else {
        g_vram_zbuffer_address = 0x118000;
        g_vram_display_address = 0x1E8000;
        g_vram_fb_offset = 0;
        g_vram_texture_base = 0x2C0000;
        SetupFS_AA_buffer(0x200, 0x1A0, 0x200, 0x1C0, 0, 0);
    }
    g_vram_texture_base_copy = g_vram_texture_base;
    g_vram_clut_first = g_vram_texture_base + 0x1000;
    g_vram_clut_second = g_vram_texture_base + 0x1400;
    g_vram_clut_third = g_vram_texture_base + 0x1800;
    w = FsAaBuffer.display_width;
    g_screen_width.width = w;
    g_screen_width.height = FsAaBuffer.display_height;
    g_screen_width.half_width = w >> 1;
    g_screen_width.half_height = g_screen_width.height >> 1;
    g_screen_width.left = (0x800 - g_screen_width.half_width) << 4;
    g_screen_width.top = (0x800 - g_screen_width.half_height) << 4;
    g_screen_width.right = (g_screen_width.half_width + 0x800) << 4;
    g_screen_width.bottom = (g_screen_width.half_height + 0x800) << 4;
    frame = (g_vram_display_address >> 13) | ((u64)(g_screen_width.width >> 6) << 16);
    g_gs_draw_env_regs.frame1 = frame;
    zbuf = (g_vram_zbuffer_address >> 13) | 0x1000000;
    g_gs_draw_env_regs.frame2 = frame;
    g_gs_draw_env_regs.xyoffset1 = g_screen_width.left | ((u64)g_screen_width.top << 32);
    g_gs_draw_env_regs.zbuf1 = zbuf;
    g_gs_draw_env_regs.zbuf2 = zbuf;
    g_gs_draw_env_regs.xyoffset2 = g_screen_width.left | ((u64)g_screen_width.top << 32);
    scissor = ((u64)(g_screen_width.width - 1) << 16) | ((u64)(g_screen_width.height - 1) << 48);
    g_gs_zbuf_reg = zbuf;
    g_gs_draw_env_regs.scissor1 = scissor;
    g_gs_draw_env_regs.scissor2 = scissor;
    g_gs_zbuf_reg_masked = zbuf | ((u64)0x8000 << 17);
    if (clear) {
        g_vram_cursor = g_vram_texture_base;
        g_vram_frame_base = g_vram_texture_base;
        FlushCache(0);
        gfx_wait_paths_idle(0, 0);
        FlushCache(0);
        gfx_append_draw_list_header();
        gfx_append_draw_list_buffer_tag(0);
        FlushCache(0);
        gfx_wait_paths_idle(0, 0);
        gfx_query_display_buffer();
        mem_clear(g_gs_transfer_buffer, 0, 0x1000);
        n = (FsAaBuffer.storage_width * FsAaBuffer.storage_height) >> 10;
        for (i = 0; i < n; i++) {
            func_00126288(&image, i << 4, 1, 0, 0, 0, 32, 32);
            FlushCache(0);
            sceGsExecLoadImage(&image, g_gs_transfer_buffer);
            gfx_wait_paths_idle(0, 0);
        }
    }
}
