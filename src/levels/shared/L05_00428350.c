#include "include_asm.h"
#include "common.h"
typedef unsigned int QuadWord __attribute__((mode(TI)));
typedef union { QuadWord word; float v[4]; } Vector;
typedef struct { Vector row[3]; Vector position; } Frame;
typedef struct {
    Vector vertex[4];
    unsigned int color[4];
    float uv[4][2];
    long f70, f78, f80, flags;
} RenderPacket;

extern Vector g_hero_state_block;
extern Vector ref_L05_0042F4E8_01[4];
extern void gfx_init_quad_packet_state(void *, int, int, int);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void euler_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern void transform_vector(void *, void *, void *);
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern void gfx_world_to_screen_unit(int, float *, float *);
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);

extern void FastVecSub(char *, char *, char *);
extern void vec_scale_to_length(char *, char *, float);
extern void FastVecCross(char *, char *, char *);
extern void draw_world_quad(char *, int, int);
extern char ref_L05_0042F4E8_00[];


extern int g_screen_offset_x __attribute__((sda));

extern int g_screen_offset_y __attribute__((sda));

extern void func_2FC560(char *out, char *src);

extern int func_307778(float value);

extern void func_00282CF0_9(char *local, char *first, char *second);

extern void func_00282CC0_14(char *target, char *first, char *local);

extern char *g_hero_l05_moby;

extern int FastDecTimer(void *);

extern void moby_mark_spawned(void *);

/* The call target and the callback it registers are not the same function in
   every level this unit is placed in, so neither name may state an address. */
extern void ref_L05_0042E4E8_00(void);

extern int ref_L05_0042E4E8_01(void *, void *);

#ifndef RAC2_T_VEC16_FC936841D
#define RAC2_T_VEC16_FC936841D
typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vec16_Fc936841d;
#endif

/* func_L05_00428350 is defined in L05_00428350-g8.c. */

/* func_L05_00428518 is defined in L05_00428518-g8.c. */

/* func_L05_00428AC8 is defined in L05_00428AC8-g8.c. */




/* func_L05_0042B2C0 is defined in L05_0042B2C0-strip-g8.c. */

/* func_L05_0042BB10 is defined in L05_0042BB10-g8.c. */

extern char *func_328508(char *);

extern void func_32AF08(char *);

extern void func_3073E0(char *, char *);

extern void func_3065F8(char *);

extern void func_3066A0(char *, char *, float);

extern void func_306630(char *, char *, char *);

extern int func_2F9888(char *, int, char *, int, float);

extern void func_2DCB60(int, int);

extern void func_2EB6E8(void);

extern int g_ship_encounter_flag;

extern int g_current_map_index;

extern char *g_ship_encounter_table;

extern char *g_moby_pool_base;

extern char g_hero_state[];

extern char g_moby_group_flags[];

extern char g_unused_byte_buffer[];

extern char g_unused_data_block[];

#ifndef RAC2_T_TI128_15C4FA
#define RAC2_T_TI128_15C4FA
typedef int TI128 __attribute__((mode(TI)));
#endif

/* Creates the 0x1226 object, seeds its flags from the caller's two floats and copies the
   caller's quadword into the object's transform slot. */
char *stream_spawn_piece(char *a0, char *a1, float f12, float f13)
{
    char *obj = func_328508((char *)0x1226);

    if (obj != 0) {
        char *sub;

        *(unsigned char *)(obj + 0x30) = 0xFF;
        *(unsigned short *)(obj + 0x32) = 0x1FF;
        *(unsigned char *)(obj + 0x31) = 1;
        *(float *)(obj + 0x2C) = *(float *)(*(char **)(obj + 0x24) + 0x24) * f12;
        *(unsigned short *)(obj + 0x34) =
            (*(unsigned short *)(obj + 0x34) & 0xFFF8) | 0x100;
        sub = *(char **)(obj + 0x68);
        qcopy(obj + 0x10, a0);
        func_3073E0(a1, obj + 0xC0);
        *(float *)(sub + 0x10) = f13;
        func_32AF08(obj);
    }
    return obj;
}

/* func_L05_0042BDB0 is defined in L05_0042BDB0-g8.c. */

/* func_L05_0042C928 is defined in L05_00428350-g8.c. */

/* Two bound helpers at the node's +0x68; the second call registers a callback
   and the context, the other branch calls a one-argument helper. */
void moby_register_callback(char *a0)
{
    char *context = a0;
    char *node = *(char **)(context + 0x68);

    if (FastDecTimer(node) == 0) {
        FastDecTimer(node + 4);
        ref_L05_0042E4E8_01(&ref_L05_0042E4E8_00, context);
    } else {
        moby_mark_spawned(context);
    }
}

/* Draws a camera-facing quad, then redraws it with jittered, clamped screen-projected UVs. */
void gfx_l05_draw_jittered_billboard_quad(Vector *position, float size, float offset, float roll,
                       float unused, float jitter, int texture, int mode)
{
    RenderPacket packet;
    Frame frame;
    /* One 64-byte scratch area: the roll angles (later the offset), then the roll rotation,
       whose first two rows are reused for the projection's centre and point. */
    struct {
        Vector angles;
        union {
            Vector rotation[3];
            struct { Vector center, point; } projection;
        } u;
    } scratch;
    Vector *corner;

    gfx_init_quad_packet_state(&packet, texture, 1, 0x80);
    packet.flags = 0x800000004aULL;
    packet.color[3] = 0x80808080;
    packet.color[2] = 0x80808080;
    packet.color[1] = 0x80808080;
    packet.color[0] = 0x80808080;
    packet.uv[0][0] = 0.0f;
    packet.uv[0][1] = 0.0f;
    packet.uv[1][0] = 0.0f;
    packet.uv[1][1] = 1.0f;
    packet.uv[2][0] = 1.0f;
    packet.uv[2][1] = 0.0f;
    packet.uv[3][0] = 1.0f;
    packet.uv[3][1] = 1.0f;
    qcopy(&frame.position, position);
    FastVecSub((char *)&frame.row[0], (char *)(ref_L05_0042F4E8_00 + 0x140), (char *)&frame.position);
    vec_scale_to_length((char *)&frame.row[0], (char *)&frame.row[0], 1.0f);
    FastVecCross((char *)&frame.row[1], (char *)&frame.row[0], (char *)&g_hero_state_block);
    vec_scale_to_length((char *)&frame.row[1], (char *)&frame.row[1], 1.0f);
    FastVecCross((char *)&frame.row[2], (char *)&frame.row[1], (char *)&frame.row[0]);
    if (roll != 0.0f) {
        scratch.angles.word = 0;
        scratch.angles.v[0] = roll;
        euler_rotation_basis(scratch.u.rotation, &scratch.angles);
        multiply_matrix3x3(frame.row, frame.row, scratch.u.rotation);
    }
    FastVecScale(&scratch.angles, &frame.row[0], offset);
    FastVecAdd(&frame.position, &frame.position, &scratch.angles);
    {
        Vector *vertex = packet.vertex;
        int count;
        corner = ref_L05_0042F4E8_01;
        count = 3;
        do {
            FastVecScale(vertex, corner, size);
            ++corner;
            --count;
            transform_vector(vertex, vertex, &frame);
            ++vertex;
        } while (count >= 0);
    }
    VU1_addGSregister(0x47, 0x31001ULL);
    draw_world_quad((char *)&packet, 0, 0);
    if (mode != 0) {
        int i;

        qcopy(&scratch.u.projection.center, &packet.vertex[0]);
        {
            Vector *vertex = &packet.vertex[1];
            int count;
            count = 2;
            do {
                FastVecAdd(&scratch.u.projection.center, &scratch.u.projection.center,
                              vertex);
                ++vertex;
                --count;
            } while (count >= 0);
        }
        FastVecScale(&scratch.u.projection.center, &scratch.u.projection.center, 0.25f);
        for (i = 0; i < 4; ++i) {
            FastVecSub((char *)&scratch.u.projection.point, (char *)&packet.vertex[i],
                          (char *)&scratch.u.projection.center);
            FastVecScale(&scratch.u.projection.point, &scratch.u.projection.point, 0.8f);
            FastVecAdd(&scratch.u.projection.point, &scratch.u.projection.center,
                          &scratch.u.projection.point);
            gfx_world_to_screen_unit((int)&scratch.u.projection.point, &packet.uv[i][0], &packet.uv[i][1]);
            if (math_random_int_below(1) == 0) {
                packet.uv[i][0] += math_random_float_range(-jitter, jitter);
                packet.uv[i][1] += math_random_float_range(-jitter, jitter);
            }
            if (packet.uv[i][0] > 1.0f) packet.uv[i][0] = 1.0f;
            else if (packet.uv[i][0] < 0.0f) packet.uv[i][0] = 0.0f;
            if (packet.uv[i][1] > 1.0f) packet.uv[i][1] = 1.0f;
            else if (packet.uv[i][1] < 0.0f) packet.uv[i][1] = 0.0f;
        }
    } else {
        int i;

        for (i = 0; i < 4; ++i) {
            gfx_world_to_screen_unit((int)&packet.vertex[i], &packet.uv[i][0], &packet.uv[i][1]);
            if (math_random_int_below(1) == 0) {
                packet.uv[i][0] += math_random_float_range(-jitter, jitter);
                packet.uv[i][1] += math_random_float_range(-jitter, jitter);
            }
            if (packet.uv[i][0] > 1.0f) packet.uv[i][0] = 1.0f;
            else if (packet.uv[i][0] < 0.0f) packet.uv[i][0] = 0.0f;
            if (packet.uv[i][1] > 1.0f) packet.uv[i][1] = 1.0f;
            else if (packet.uv[i][1] < 0.0f) packet.uv[i][1] = 0.0f;
        }
    }
    gfx_init_quad_packet_state(&packet, -1, 1, 0x80);
    packet.flags = 0x8000000054ULL;
    VU1_addGSregister(0x47, 0x33001ULL);
    draw_world_quad((char *)&packet, 0, 0);
    VU1_addGSregister(0x47, 0x5360bULL);
}


/* func_L05_00430318 is defined in x-qcopy.c. */

/* Derives a 16-byte element at index-1 from its index-2 and index-3 neighbours through two bound helpers; original game role is unknown. */
void vec_derive_from_neighbours(Vec16_Fc936841d *object, int index)
{
    char local[16];

    func_00282CF0_9(local, (char *)&object[index - 2], (char *)&object[index - 3]);
    func_00282CC0_14((char *)&object[index - 1], (char *)&object[index - 2], local);
}


/* Creates the 0x10E3 object and copies the caller's transforms into it. */
/* func_L05_00432080 is defined in L05_00432080.c. */

/* func_L05_00432158 is matched in its own unit, src/levels/shared/L05_00432158.c (-frac2-qcopy -frac2-qcopy-barrier -fno-strength-reduce). */


/* func_L05_00441D40 is defined in L05_00428350-g8.c. */


/* func_L05_00441F30 is defined in L05_00441F30-g8.c. */

/* func_L05_00442398 is defined in L05_00442398-g8.c. */

/* func_L05_00442560 is defined in L05_00442560-q.c. */

/* func_L05_00442720 is matched in L05_00442720.c (built with -mno-split-addresses). */

/* func_L05_004427A8 is defined in L05_004427A8-flags.c. */


/* func_L05_00442880 is defined in L05_00428350-g8.c. */

/* func_L05_00442A58 is defined in L05_00442A58-g8.c. */

/* func_L05_004431A0 is defined in L05_004431A0.c. */

/* func_L05_004432E0 is defined in L05_00428350-camera-g8.c. */
/* func_L05_00443740 is defined in L05_00443740-g8.c. */

/* Folds the object's two turn rates out of its parent's rotation into the moby, then
   rebuilds the three orientation blocks the driver reads. */
/* func_L05_00443C18 is matched in L05_00443C18.c (built with -g). */

/* func_L05_00443D08 is defined in L05_00443D08-g8.c. */

/* func_L05_00444840 is defined in L05_00444840-g8.c. */

/* Converts a two-float record to the coordinate pair the level's bias words expect. */
void gfx_convert_float_pair_bias_coords(char *a0, int *a1, int *a2, int a3)
{
    float local[2];
    float bias;

    func_2FC560((char *)local, a0);
    bias = (float)g_screen_offset_x;
    *a1 = func_307778((local[0] - bias) * 0.0625f);
    bias = (float)g_screen_offset_y;
    *a2 = func_307778((local[1] - bias) * 0.0625f) + a3;
}


/* func_L05_00444FD0 is in L05_00444FD0.c. */

/* func_L05_00445338 is defined in L05_00445338-g8.c. */

/* Reads a state word from a fixed global; unless its +0x86 halfword is 0x19 it
   returns 0, otherwise it reports whether the signed halfword reached through
   the pointer at +0x70, offset +0xD8, is non-zero. */
int hero_is_state_flag_set(void)
{
    char *base = g_hero_l05_moby;

    if (*(short *)(base + 0x86) != 0x19)
        return 0;
    return *(short *)(*(char **)(base + 0x70) + 0xD8) != 0;
}

typedef struct { char pad[0x1C]; char *entry; } ModelSlot_4459B0;
typedef struct { char data[256]; } ModelRecord_4459B0;
typedef struct { char data[128]; } InstanceRecord_4459B0;
extern ModelSlot_4459B0 *g_path_l05_entry_table MACRO_ADDR;
extern ModelRecord_4459B0 *g_feltzin_target_mobys MACRO_ADDR;
extern InstanceRecord_4459B0 *g_linked_point_table MACRO_ADDR;
extern int IsPointInCuboid(void *, int);
extern float FastVecDot(char *, char *);
/* Tells whether the object is close enough to any of its twelve linked points to count as touching one. */
int path_is_touching_linked_point(void *arg)
{
    char *self = arg;
    char *entry;
    char *p;
    char *tbl;
    int count;
    float best = 0.0f;

    entry = g_path_l05_entry_table[*(short *)(self + 0x84)].entry;
    p = entry + 0x24;
    tbl = g_feltzin_target_mobys[*(int *)(entry + 0x20)].data;

    for (count = 0; count < 12; count++, p += 4) {
        if (*(int *)p < 0)
            continue;
        if (IsPointInCuboid(self + 0x30, *(int *)p) || IsPointInCuboid(tbl + 0x10, *(int *)p)) {
            if (FastVecDot(g_linked_point_table[*(int *)p].data, self) > best)
                return 1;
        }
    }
    return 0;
}

/* func_L05_00445B58 lives in L05_00445B58.c. */

/* func_L05_00445C38 lives in L05_00445C38-g8.c. */

/* func_L05_00445B58 is defined in L05_00445B58.c. */

/* func_L05_00445C38 is defined in L05_00445C38-g8.c. */

/* func_L05_00445D60 is defined in L05_00445D60-g8.c. */
