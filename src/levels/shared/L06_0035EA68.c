#include "include_asm.h"
#include "moby_classes.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef short s16;
typedef int s32;
typedef unsigned short u16;

typedef struct {
    s32 pad0;
    s32 pad1;
    s32 pad2;
    s32 fieldC;
} L06Entry;

extern L06Entry g_table_entries[];

extern s32 level_find_key_in_pair_table();

extern u8 g_map_visited_flags[] __attribute__((sda));
extern u8 g_progress_flag __attribute__((sda));
extern char g_hero_position[];
extern int g_game_l06_frame_counter __attribute__((sda));
extern void moby_set_state(void *, int, int);
extern float vec_distance_xy(void *, void *);
extern float FastVecLength(void *);
extern void moby_mark_flag_and_append_to_list(int);
extern float ApproachValue(float *, float, float);
extern void gfx_add_draw_callback_first(void *, void *);
extern void hud_show_pickup_notice(void);
extern int math_fast_float_d(int *);
extern void moby_mark_spawned(void *);
extern void vec_scale_to_length(void *, void *, float);


typedef struct { float point[4][4]; u32 color[4]; float uv[8]; unsigned long tag[4]; } L06Quad;
extern void VU1_addGSregister(int, unsigned long);
extern void gfx_init_quad_packet_state(void *, int, int, int);
extern void moby_compute_local_point(void *, void *, float, float, float);
extern void draw_world_quad(void *, int, int);

/* func_L06_0035EA68 is defined in L06_0035EA68-fall.c. */

/* Looks up a table entry from an id and stores a value in it. */
void table_set_entry_field(s32 id, s32 value) {
    s32 entryIndex = level_find_key_in_pair_table(id);
    if (entryIndex != -1)
        g_table_entries[entryIndex].fieldC = value;
}

/* func_L06_00382608 is defined in L06_00382608.c. */

extern float fast_vec_dist(char *, char *);
extern float math_fabs(float);

/* Finds the point in a list whose distance from a given point is closest to a wanted distance. Returns its index. */
s32 vec_find_point_nearest_wanted_distance(char *point, char *pointList, float wantedDistance) {
    s32 i;
    s32 best = 0;
    float bestValue = 1.0e11f;
    float baseDistance = wantedDistance;

    for (i = 0; i < *(s32 *)pointList; i++) {
        float distance = fast_vec_dist(pointList + 0x10 + i * 0x10, point);
        if (math_fabs(distance - baseDistance) < bestValue) {
            bestValue = distance;
            best = i;
        }
    }
    return best;
}


extern void ref_L06_0039A2F0_00(void *, s32, s32);

/* Looks for a matching record in a small list and updates it, or adds a new record at the end of the list. */
void record_add_or_update_entry(s32 valueA, s32 valueB, s32 owner, s32 mode, s32 *list)
{
    char *newEntry;
    s32 count;
    s32 index;
    s32 tag = mode;
    s16 key;
    s16 subtype = *(s16 *)(owner + 0xB2);
    s16 classId = *(s16 *)(owner + 0xAA);

    if (mode == 1)
        key = (s16)(valueA - owner);
    else
        key = (s16)(valueA - *(u16 *)(owner + 0x68));

    for (index = 0; index < list[0]; index++) {
        char *entry = (char *)list + 4 + index * 16;
        if (*(s32 *)entry != key) continue;
        if (*(u16 *)(entry + 8) != valueB) continue;
        if (subtype != *(s16 *)(entry + 0xC)) continue;
        if (classId != *(s16 *)(entry + 0xE)) continue;
        tag = *(s16 *)(entry + 0xA);
        if (tag != 0) {
            ref_L06_0039A2F0_00(entry + 4, valueA, valueB);
            return;
        }
    }
    count = list[0];
    newEntry = (char *)list + 4 + count * 16;
    list[0] = count + 1;
    *(s32 *)newEntry = key;
    ref_L06_0039A2F0_00(newEntry + 4, valueA, valueB);
    *(u16 *)(newEntry + 8) = valueB;
    *(s16 *)(newEntry + 0xA) = tag;
    *(s16 *)(newEntry + 0xC) = subtype;
    *(s16 *)(newEntry + 0xE) = classId;
}

/* Updates a collectable pickup (moby class 750): it waits for the hero to touch it, gives the item, then shrinks and fades away. */
void collectable_pickup_update(u8 *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float scale, inverse;
    switch ((u8)moby[0x20]) {
    case 0:
        moby[0x30] = 0xFF;
        if (!g_map_visited_flags[*(int *)vars]) moby_set_state(moby, 1, -1);
        else moby_mark_spawned(moby);
        break;
    case 1:
        if (vec_distance_xy(moby + 0x10, g_hero_position) < 2.0f &&
            math_fabs(*(float *)(moby + 0x18) - *(float *)(g_hero_position + 8)) < 2.0f) {
            moby_mark_flag_and_append_to_list(*(int *)vars);
            moby_set_state(moby, 2, -1);
            *(u16 *)(moby + 0x34) |= 0x100;
            *(int *)(vars + 8) = 180;
        }
        if (*(int *)vars == 24 && g_progress_flag) {
            moby_mark_flag_and_append_to_list(24);
            moby_set_state(moby, 2, -1);
            *(u16 *)(moby + 0x34) |= 0x100;
            *(int *)(vars + 8) = 180;
        }
        break;
    case 2:
        if ((*(u16 *)(moby + 0x34) ^ 1) & 1) {
            scale = FastVecLength(moby + 0xC0);
            ApproachValue(&scale, 0, 0.06666667014360428f);
            inverse = 2.0f - scale;
            vec_scale_to_length(moby + 0xC0, moby + 0xC0, scale);
            vec_scale_to_length(moby + 0xD0, moby + 0xD0, scale);
            vec_scale_to_length(moby + 0xE0, moby + 0xE0, inverse);
            if (scale <= 0) {
                moby[0x31] = 0;
                *(u16 *)(moby + 0x34) |= 1;
            }
        }
        gfx_add_draw_callback_first(hud_show_pickup_notice, moby);
        if ((g_game_l06_frame_counter ^ 1) & 1) (*(int *)(vars + 4))++;
        if (math_fast_float_d((int *)(vars + 8))) {
            ApproachValue((float *)(vars + 12), 0, 0.05000000447034836f);
            if (*(float *)(vars + 12) <= 0) moby_mark_spawned(moby);
        } else {
            ApproachValue((float *)(vars + 12), 1, 0.05000000447034836f);
        }
        break;
    }
}



/* Returns 1 if this is a Taxi moby that is in one of its flying states (2 to 6). */
s32 taxi_is_flying(u8 *moby) {
    if (*(s16 *)(moby + 0xAA) != MOBY_CLASS_TAXI)
        return 0;
    return (u32)(moby[0x20] - 2) < 5;
}







extern char g_path_l17_table[];
extern char g_path_point_template[];
extern u8 g_hero_state[];
extern void matrix_mul_vec3(void *, void *, void *);
extern void func_2EEEB8(void *, void *, void *);

/* Same body as func_L17_003C3250, with this function's own callees. */
/* Moves a set of seven local points to follow the moby, and stores them in a shared table entry. */
void path_update_attached_point_table(char *moby)
{
    char *vars;
    char *outPoint;
    char *sourcePoint;
    char *position;
    char *matrix;
    char *base;
    int tableEntry;
    int i;

    vars = *(char **)(moby + 0x68);
    tableEntry = *(int *)(vars + 0xF8);
    if (tableEntry == -1)
        return;
    tableEntry = *(int *)(g_path_l17_table + tableEntry * 4);
    if (*(int *)tableEntry != 7)
        return;
    matrix = moby + 0xC0;
    position = moby + 0x10;
    sourcePoint = g_path_point_template;
    outPoint = tableEntry + 0x10;
    for (i = 6; i >= 0; i--) {
        matrix_mul_vec3(outPoint, sourcePoint, matrix);
        sourcePoint += 0x10;
        func_2EEEB8(outPoint, outPoint, position);
        outPoint += 0x10;
    }
    base = g_hero_state;
    *(unsigned short *)(base + 0x24FE) = *(unsigned short *)(vars + 0xF8);
}



/* func_L06_003E5D30 is defined in L06_003E5D30-g8.c. */

/* func_L06_004009B8 is defined in L06_004009B8-g8.c. */

/* func_L06_00402570 is defined in L06_00402570.c. */

/* func_L06_00403130 is defined in L06_00403130.c. */

/* func_L06_00403710 is defined in L06_00403710-g8.c. */

/* func_L06_00403DA8 is defined in L06_00403DA8.c. */


/* func_L06_00444D00 is defined in L06_00444D00.c. */

/* func_L06_004638F0 is defined in L06_004638F0.c. */


/* Draws a flat textured square twice, the second one slightly in front, as the look of the swaying effect moby. */
void gfx_draw_double_layer_quad(char *moby)
{
    L06Quad q;
    u8 *vars = *(u8 **)(moby + 0x68);
    if (vars[0x4D]) {
        q.uv[0] = 0; q.uv[1] = 0; q.uv[2] = 0; q.uv[3] = 1;
        q.uv[4] = 1; q.uv[5] = 0; q.uv[6] = 1; q.uv[7] = 1;
    } else {
        q.uv[0] = 0; q.uv[1] = 0; q.uv[2] = 1; q.uv[3] = 0;
        q.uv[4] = 0; q.uv[5] = 1; q.uv[6] = 1; q.uv[7] = 1;
    }
    *(u32 *)(vars + 0x58) &= 0xFFFFFF;
    *(u32 *)(vars + 0x58) += (u8)moby[0x23] << 24;
    q.color[0] = q.color[1] = q.color[2] = q.color[3] = *(u32 *)(vars + 0x58);
    q.tag[0] = 0;
    VU1_addGSregister(0x42, 0x8000000048UL);
    VU1_addGSregister(0x14, 0xFF9000000260UL);
    VU1_addGSregister(0x47, 0x50000);
    gfx_init_quad_packet_state(&q, vars[0x4E], 0, 0x80);
    moby_compute_local_point(moby, q.point[0], 0, *(float *)(vars + 0x50), -*(float *)(vars + 0x54));
    moby_compute_local_point(moby, q.point[1], 0, *(float *)(vars + 0x50), *(float *)(vars + 0x54));
    moby_compute_local_point(moby, q.point[2], 0, -*(float *)(vars + 0x50), -*(float *)(vars + 0x54));
    moby_compute_local_point(moby, q.point[3], 0, -*(float *)(vars + 0x50), *(float *)(vars + 0x54));
    draw_world_quad(&q, 0, 0);
    gfx_init_quad_packet_state(&q, vars[0x4F], 0, 0x80);
    VU1_addGSregister(0x47, 0x50000);
    moby_compute_local_point(moby, q.point[0], -0.001f, *(float *)(vars + 0x50), -*(float *)(vars + 0x54));
    moby_compute_local_point(moby, q.point[1], -0.001f, *(float *)(vars + 0x50), *(float *)(vars + 0x54));
    moby_compute_local_point(moby, q.point[2], -0.001f, -*(float *)(vars + 0x50), -*(float *)(vars + 0x54));
    moby_compute_local_point(moby, q.point[3], -0.001f, -*(float *)(vars + 0x50), *(float *)(vars + 0x54));
    draw_world_quad(&q, 0, 0);
}

extern s32 g_camera_l06_state_ptr;

/* Sets a camera distance value, unless the camera is switched off. */
void cam_set_follow_distance(float distance) {
    s32 cameraState = g_camera_l06_state_ptr;
    if (*(s16 *)(cameraState + 0x86) == 0)
        *(float *)(*(s32 *)(cameraState + 0x70) + 0x24C) = distance;
}



/* func_L06_0047A408 is defined in L06_0047A408.c. */

/* func_L06_0047AC68 is defined in L06_0047AC68-g8.c. */

/* Separate camera activate, update and exit entries, shared by seven levels. */
/* Empty camera activate entry. */
void cam_activate_noop(void *camera)
{
}

/* Empty camera update entry. */
void cam_update_noop(void *camera)
{
}

/* Empty camera exit entry. */
void cam_exit_noop(void *camera)
{
}
