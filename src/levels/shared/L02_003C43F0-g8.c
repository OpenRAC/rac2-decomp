#include "include_asm.h"
#include "common.h"

extern void gfx_l00_draw_billboard_quad(void *, void *, float, float);

extern void *D_L02_001B17E8 __attribute__((sda));

extern float D_L02_001B17E4 __attribute__((sda));

extern float D_L02_001B17E0 __attribute__((sda));

extern float D_L02_001B17EC __attribute__((sda));

extern char *D_L02_001B1190[1] __attribute__((sda));

extern float IntToFloat(int);

extern int FloatToInt(float);

extern int arena_get_challenge_save_index(int);

extern int flag_is_byte_set(void);

extern unsigned char D_001395B8[0x100];

/* Runs the kind's placement helper with the kind's own angles. */
/* Places an object using its state: states 2 and 3 pick different angle values. */
void moby_place_by_state(char *object) {
    if (*(unsigned char *)(object + 0x20) == 3)
        gfx_l00_draw_billboard_quad(object + 0x10, D_L02_001B17E8, D_L02_001B17E4, D_L02_001B17E0);
    else if (*(unsigned char *)(object + 0x20) == 2)
        gfx_l00_draw_billboard_quad(object + 0x10, D_L02_001B17E8, D_L02_001B17EC, D_L02_001B17E0);
}

#ifndef RAC2_T_TI128_L02
#define RAC2_T_TI128_L02
typedef int TI128 __attribute__((mode(TI)));
#endif

extern float D_L02_001B0180 __attribute__((sda));

extern float D_L02_001B0188 __attribute__((sda));

extern int D_L02_001B0184 __attribute__((sda));

extern float D_L02_001B0178 __attribute__((sda));

extern float D_L02_001B017C __attribute__((sda));

extern char g_camera_l02_position[];

extern void FastVecScale(void *, void *, float);

extern void FastVecAdd(void *, void *, void *);

extern void FastVecSub(void *, void *, void *);

extern void vec_scale_to_length(void *, void *, float);

extern float FastVecDot(void *, void *);

/* The second declaration of the kind's helper in this unit: it takes the packed
   word where the call above takes a pointer. */
extern void func_L00_00325AE8_1(void *, int, float, float);

/* The 24-bit mask is written as 0xFFFFFF: the assembler expands `li` for 0xFF0000
   into `lui $v0,0xFF` and `ori $v0,$v0,0xFFFF`, so the register holds 0xFFFFFFFF. */
/* Spawns a fading spark from an object when the player is looking at it from far enough away. The spark color fades with distance. */
void part_spawn_fading_spark(void *owner)
{
    void *object = owner;
    void *direction = (char *)object + 0xE0;
    TI128 spawn_point;
    TI128 to_camera;
    float dot;
    int color_word;
    int alpha;

    FastVecScale(&spawn_point, direction, D_L02_001B0180);
    FastVecAdd(&spawn_point, &spawn_point, (char *)object + 0x10);
    FastVecSub(&to_camera, g_camera_l02_position, (char *)object + 0x10);
    vec_scale_to_length(&to_camera, &to_camera, 1.0f);
    dot = FastVecDot(&to_camera, direction);
    if (D_L02_001B0188 < dot) {
        color_word = D_L02_001B0184;
        dot = dot * dot;
        alpha = (int)(dot * (float)(color_word >> 24));
        func_L00_00325AE8_1(&spawn_point, (color_word & 0xFFFFFF) | (alpha << 24), D_L02_001B0178,
                            D_L02_001B017C);
    }
}

/* func_L02_004013C0 is defined in L02_004013C0-g8.c. */

/* The kind's table gives a count; the kind's own helper gives the kind's id. */

/* The byte table the count is read from, at its address in the boot's resident memory. */

/* Scales the kind's own angle at +0xC down by 0.3 once per count the kind's byte table
   gives, keeps it inside the kind's own range, scales it by ten when the global flag is
   set, and hands it to the angle setter. */
int moby_compute_scaled_entry_value(int entry) {
    float value;
    int i = 0;

    value = IntToFloat(*(int *)(D_L02_001B1190[entry] + 0xC));
    while (i < D_001395B8[arena_get_challenge_save_index(entry)]) {
        value *= 0.3f;
        i++;
    }
    {
        float limit = (float)*(int *)(D_L02_001B1190[entry] + 0xC);

        if (limit < value)
            value = limit;
        else if (value < 500.0f)
            value = 500.0f;
    }
    if (flag_is_byte_set() != 0)
        value *= 10.0f;
    return FloatToInt(value);
}

/* Near miss: same body with the other entry parameter (draft beside this one). */
/* Same idea as the one above, but for the second entry value, shifted left by 5. */
int moby_compute_scaled_entry_value_shifted(int entry) {
    float value;
    int i = 0;

    value = IntToFloat(*(int *)(D_L02_001B1190[entry] + 0x10));
    while (i < D_001395B8[arena_get_challenge_save_index(entry)]) {
        value *= 0.33333f;
        i++;
    }
    {
        float limit = (float)*(int *)(D_L02_001B1190[entry] + 0x10);

        if (limit < value)
            value = limit;
        else if (value < 5.0f)
            value = 5.0f;
    }
    return FloatToInt(value) << 5;
}

extern void vec_copy_helper_a(void *);
extern void FastVecCross(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_fast_normalize_helper(void *, void *, float);
extern void path_clamp_move_to_area(void *, char *, char *, int, float);

/* The level's 0x80-byte placement records, whose direction sits at +0x30. */
extern char *D_L02_001B368C;

/* Aligns the actor with the record its state names: the -1 case builds a direction from the
   +0x1F0 axis and the +0x340 vector and picks the 1.5-scaled or negated one by the sign of the
   dot product; the other case uses the 0x80-byte record from the boot table. The shared tail
   copies the +0x340 vector to the stack and hands it to the level's nine-place routine. */
int moby_compute_aligned_direction(char *object, char *output)
{
    char *vars = *(char **)(object + 0x68);
    TI128 a, b, c, d, e;
    int result;

    if (*(int *)(vars + 0x334) == -1) {
        FastVecSub((float *)&a, (float *)(vars + 0x1F0), (float *)(vars + 0x340));
        vec_copy_helper_a(&b);
        FastVecCross(&c, &a, &b);
        vec_scale_to_length((char *)&c, (char *)&c, 1.5f);
        FastVecScale(&d, &c, -1.0f);
        FastVecSub((float *)&e, object + 0x10, (float *)(vars + 0x340));
        if (FastVecDot(&e, &c) < 0.0f) {
            FastVecAdd(output, &c, vars + 0x340);
            result = 1;
        } else {
            FastVecAdd(output, &d, vars + 0x340);
            result = 0;
        }
    } else {
        FastVecSub((float *)&a, (float *)(vars + 0x1F0),
                      (float *)(D_L02_001B368C + (*(int *)(vars + 0x334) << 7) + 0x30));
        result = 1;
        vec_fast_normalize_helper((char *)&a, (char *)&a,
                      FastVecLength(D_L02_001B368C + (*(int *)(vars + 0x334) << 7)));
        FastVecAdd(output, &a, D_L02_001B368C + (*(int *)(vars + 0x334) << 7) + 0x30);
        FastVecSub((float *)&b, output, object + 0x10);
        if (!(0.0f <= FastVecDot(&b, object + 0xD0)))
            result = 0;
    }
    a = *(TI128 *)(vars + 0x340);
    path_clamp_move_to_area(&a, output, output, *(int *)(vars + 0x318), *(float *)(vars + 0x100));
    return result;
}


extern char *g_moby_l02_pool __attribute__((sda));

extern int g_current_map_index[] __attribute__((sda));
extern unsigned char D_0019B2E8[];
extern unsigned char D_001395B8[];
struct PortalPlayer {
    char pad0[0x80];
    float pos[4];
    char pad90[0x182];
    short state;
    char pad214[0x128];
    char *portal;
    int active;
    char pad344[0x21ac];
    unsigned char flag;
};
extern struct PortalPlayer g_hero_state;
extern unsigned char g_hero_position[];
extern unsigned char D_001A7BC8[] __attribute__((sda));
extern unsigned int D_00138324 __attribute__((nosda));
extern unsigned char D_L02_001C0700[];
extern void anim_start_blended(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern void moby_set_flag_bit(void *, int);
extern void state_set_flag_one(void);
extern void part_start_record_effect_by_index(int, int);
extern void level_capture_checkpoint_state(void *, void *);
extern void snd_play_indexed(int);
extern void vec_transform_by_object_or_given(void *, void *, void *, int);
extern int TryClaimNotice(int, int, int);
extern void data_set_small_value_and_refresh(int, int);
extern int req_push_queue(void *, int);
extern int req_launch_queued(void *);
extern void moby_call_helper_two_one(void);
extern void game_set_stored_value_pair(void (*)(void), void *);
extern void moby_mark_flag_and_append_to_list(int);

/* Update for a portal moby. On the first frame it sets up its look and level link; later it sends the hero to the linked level when they step into it. */
void portal_update(char *obj) {
    char *vars = *(char **)(obj + 0x68);
    float delta[4];
    int dest_level;

    switch (*(unsigned char *)(obj + 0x20)) {
    case 0: {
        int level_row;
        if (*(unsigned char *)(obj + 0x43) != 2) anim_start_blended(obj, 2, 0, 1);
        moby_set_state(obj, 1, -1);
        *(unsigned char *)(obj + 0x30) = 255;
        if (g_current_map_index[0] == 26) *(short *)(obj + 0x32) = 255;
        qcopy(vars + 0x20, obj + 0x10);
        qcopy(vars + 0x30, obj + 0xf0);
        level_row = g_current_map_index[0] << 4;
        *(short *)(vars + 0x1e) = D_0019B2E8[*(unsigned char *)(obj + 0xb0) + level_row] >> 7;
        if (D_0019B2E8[*(unsigned char *)(obj + 0xb0) + level_row] & 0x80) {
            if (*(int *)(vars + 4)) moby_set_flag_bit(g_moby_l02_pool + (*(int *)(vars + 4) << 8), 1);
        }
        if (g_current_map_index[0] == 2 && D_001395B8[0x71] == 26) {
            state_set_flag_one();
            D_001395B8[0x71] = 1;
            part_start_record_effect_by_index(*(int *)(vars + 0x14), *(int *)(vars + 0x10));
            level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
            if (D_001A7BC8[4] && !D_001395B8[0xa5]) {
                D_001395B8[0xa5] = 1;
                snd_play_indexed(4);
            }
        }
    }
    case 1:
        if (g_hero_state.portal == obj && g_hero_state.active) {
            FastVecSub(delta, g_hero_state.pos, obj + 0x10);
            vec_transform_by_object_or_given(obj, delta, delta, 0);
            if (delta[2] < -0.6f) {
                int currentLevel;
                currentLevel = g_current_map_index[0];
                g_hero_state.state = 2;
                dest_level = 2;
                if (currentLevel == 26) {
                    TryClaimNotice(8, 0x27b1, 1);
                } else {
                    TryClaimNotice(8, D_0019B2E8[*(unsigned char *)(obj + 0xb0) + (currentLevel << 4)] & 0x80 ? 0x27cd : 0x27b0, 1);
                    dest_level = 26;
                }
                if (D_00138324 & 0x10) {
                    level_capture_checkpoint_state(g_hero_position, g_hero_position + 0x10);
                    data_set_small_value_and_refresh(dest_level, 1);
                    if (dest_level == 26) D_001395B8[1] = 1;
                }
            }
        }
        if (g_current_map_index[0] == 26 && (D_0019B2E8[0x1a0 + *(unsigned char *)(obj + 0xb0)] & 0x80)) {
            if (D_001A7BC8[4]) return;
            if (req_push_queue(D_L02_001C0700, 0xa7)) {
                req_push_queue(D_L02_001C0700, 4);
                req_push_queue(D_L02_001C0700, 0xa8);
                req_launch_queued(D_L02_001C0700);
                game_set_stored_value_pair(moby_call_helper_two_one, obj);
                g_hero_state.flag = 0;
                moby_mark_flag_and_append_to_list(4);
                moby_set_state(obj, 3, -1);
            }
        }
        break;
    }
}
