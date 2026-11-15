#include "common.h"

extern int coll_test_point_against_shapes(void *, int, int, int, int);
extern int func_001163B0(void);
extern float vec_distance_xy(void *, void *);
extern int math_random_int_below(int);
extern s32 math_closest_point_on_polygon_edge(void *, void *,void *,int);
extern int CollLine(void *, void *, int, void *, int);
extern char *D_L01_001FE180[];
extern char g_coll_line_hit_point[];

typedef int TI128 __attribute__((mode(TI)));

typedef struct L01_003BDF28_BUF {
    float x;
    float y;
    int z;
} L01_003BDF28_BUF;

typedef struct L01_003BC490_OBJ {
    char pad[0x10];
    TI128 f10;
} L01_003BC490_OBJ;

typedef struct L01_003BDBB0_OWNED {
    char pad0[0x250];
    void *f250;
    int f254;
} L01_003BDBB0_OWNED;

typedef struct L01_003BDBB0_OBJ {
    char pad0[0x68];
    L01_003BDBB0_OWNED *f68;
} L01_003BDBB0_OBJ;

typedef struct L01_003BE488_OWNED {
    char pad0[0x202];
    short f202;
    int f204;
} L01_003BE488_OWNED;

typedef struct L01_003BE488_OBJ {
    char pad0[0x68];
    L01_003BE488_OWNED *f68;
} L01_003BE488_OBJ;

typedef struct L01_003BFDC8_OBJ {
    char pad0[0x43];
    unsigned char f43;
    char pad1[0x48 - 0x44];
    float f48;
} L01_003BFDC8_OBJ;

extern int math_fast_float_d(void *);

extern void gfx_free_point_light(int);

extern float math_random_float_range(float, float);

extern void func_002A0F48(char *);

extern void *CreateMoby(int);

extern float math_fast_sin_or_cos_a(float);

extern float math_fast_sin_or_cos_b(float);

extern void FastVecAdd(void *, void *, void *);

extern void FastVecSub(void *, void *, void *);

extern void vec_scale_to_length(void *, void *, float);

extern char g_hero_position[];

extern void moby_choose_wander_destination(void *);

extern float math_random_angle(void);

extern int math_random_int_range(int, int);

extern void *part_l01_spawn_glow(void *, int, int, float, float, int);

extern void anim_start_blended();

/* Picks a random spot near the moby's home position as its next move target. */
void moby_pick_random_home_target(char *moby)
{
    char *moby_ptr = moby;
    char *vars = *(char **)(moby_ptr + 0x68);
    char *target_pos = vars + 0x1E0;
    L01_003BDF28_BUF offset;

    *(float *)(vars + 0x1E0) = math_fast_sin_or_cos_a(math_random_float_range(-3.1415927f, 3.1415927f)) * (float)*(unsigned char *)(vars + 0x201);
    *(float *)(vars + 0x1E4) = math_fast_sin_or_cos_b(math_random_float_range(-3.1415927f, 3.1415927f)) * (float)*(unsigned char *)(vars + 0x201);
    *(int *)(vars + 0x1E8) = 0;
    FastVecAdd(target_pos, target_pos, vars + 0x1D0);
    *(float *)(vars + 0x1E8) = *(float *)(vars + 0x1E8) + 1.7f;
    if (*(int *)(vars + 0x23C) != 0) {
        FastVecSub(&offset, target_pos, g_hero_position);
        offset.z = 0;
        vec_scale_to_length(&offset, &offset, 8.0f);
        FastVecAdd(target_pos, target_pos, &offset);
    }
    moby_choose_wander_destination(moby_ptr);
}

/* func_L01_003BB9D0 is in L01_003BB9D0-ocean-g8.c. */

/* func_L01_003BBF68 is in L01_003BBF68-g8.c. */


/* func_L01_003BC540 is in L01_003BB9D0-debris-g8.c. */

/* func_L01_003BCA38 is in L01_003BCA38.c. */

/* func_L01_003BCEC8 is in L01_003BB9D0-g8.c. */


/* func_L01_003BD410 */
/* Spawns five small splash particles near the water surface under the moby. */
void part_spawn_water_splash_particles(char *moby)
{
    float position[4];
    float angle, radius, first, second;
    char *state;
    int life, i;

    state = *(char **)(moby + 0x68);
    for (i = 0; i < 5; i++) {
        angle = math_random_angle();
        radius = math_random_float_range(0.0f, 0.8f);
        first = math_random_float_range(0.0f, 1.5f);
        second = math_random_float_range(1.5f, 5.7f);
        life = math_random_int_range(100, 180);
        position[0] = math_fast_sin_or_cos_a(angle) * radius;
        position[1] = math_fast_sin_or_cos_b(angle) * radius;
        position[2] = 0.0f;
        FastVecAdd(position, position, moby + 0x10);
        position[2] = *(float *)(state + 0x224) + 0.025f;
        part_l01_spawn_glow(position, 0x38002028, 0x2020, first, second, life);
    }
}



/* func_L01_003BD6B0 is in L01_003BD6B0-g8.c. */

typedef struct {
    char pad0[0x280];
    int f280;
    int f284;
} L01_003BDB28_STATE;

extern void moby_set_byte_on_group(int, int);

/* Switches on the linked trigger groups of the moby and flags it as triggered. */
void moby_trigger_linked_groups(char *moby)
{
    L01_003BDB28_STATE *vars = *(L01_003BDB28_STATE **)(moby + 0x68);

    if (*(unsigned char *)(moby + 0x21) != 0xFF) {
        moby_set_byte_on_group(*(unsigned char *)(moby + 0x21), 1);
    }
    if (vars->f280 != -1) {
        moby_set_byte_on_group(vars->f280, 1);
    }
    if (vars->f284 != -1) {
        moby_set_byte_on_group(vars->f280, 1);
    }
    *(unsigned char *)(moby + 0xBC) = 1;
}

/* func_L01_003BDBB0 */

/* Gives back the attack slot the moby was using, so another enemy can attack. */
void moby_release_attack_slot(L01_003BDBB0_OBJ *moby)
{
    L01_003BDBB0_OWNED *vars = moby->f68;

    if (vars->f254 != 0) {
        math_fast_float_d(vars->f250);
        vars->f254 = 0;
    }
}

/* Chooses where the moby should fly next, keeping the spot clear of walls and away from the moby's own position. */
void moby_choose_wander_destination(void *object)
{
    char *moby = object;
    char *vars = *(char **)(moby + 0x68);
    int index = -1;
    float offset, coordinate;

    if (*(unsigned char *)(moby + 0x20) < 7) {
        index = (*(int *)(vars + 0x214) != -1) ? *(int *)(vars + 0x214) : *(int *)(vars + 0x210);
    } else {
        index = *(int *)(vars + 0x210);
    }
    *(int *)(vars + 0xCC) = index;
    if (!coll_test_point_against_shapes(vars + 0x1E0, index, *(int *)(vars + 0x218), *(int *)(vars + 0x21C), -1)) {
        if ((func_001163B0() & 1) || *(int *)(vars + 0x114) != 1 || *(int *)(vars + 0x23C)) {
            if (vec_distance_xy(vars + 0x1E0, moby + 0x10) < 0.5f || !math_random_int_below(1)) {
                qcopy(vars + 0x1E0, vars + 0x1D0);
                *(float *)(vars + 0x1E8) += 1.7f;
            }
            math_closest_point_on_polygon_edge(vars + 0x1E0, vars + 0x1E0, D_L01_001FE180[index] + 0x10, *(int *)D_L01_001FE180[index]);
        } else {
            *(float *)(vars + 0x1E0) = math_fast_sin_or_cos_a(math_random_float_range(-3.1415927f, 3.1415927f)) * 1.2f;
            *(float *)(vars + 0x1E4) = math_fast_sin_or_cos_b(math_random_float_range(-3.1415927f, 3.1415927f)) * 1.2f;
            *(int *)(vars + 0x1E8) = 0;
            FastVecAdd(vars + 0x1E0, vars + 0x1E0, g_hero_position);
            *(float *)(vars + 0x1E8) += 1.7f;
            math_closest_point_on_polygon_edge(vars + 0x1E0, vars + 0x1E0, D_L01_001FE180[index] + 0x10, *(int *)D_L01_001FE180[index]);
        }
        if ((*(int *)(vars + 0x23C) && vec_distance_xy(vars + 0x1E0, g_hero_position) < 3.0f) || vec_distance_xy(vars + 0x1E0, moby + 0x10) < 0.5f) {
            offset = math_random_float_range(3.0f, 5.0f);
            coordinate = *(float *)(vars + 0x1E0);
            *(float *)(vars + 0x1E0) = (func_001163B0() & 1) ? coordinate - offset : coordinate + offset;
            offset = math_random_float_range(3.0f, 5.0f);
            coordinate = *(float *)(vars + 0x1E4);
            *(float *)(vars + 0x1E4) = (func_001163B0() & 1) ? coordinate - offset : coordinate + offset;
        }
    }
    if (CollLine(moby + 0x10, vars + 0x1E0, 2, moby, 0)) {
        FastVecSub(vars + 0x1E0, g_coll_line_hit_point, vars + 0x1E0);
        vec_scale_to_length(vars + 0x1E0, vars + 0x1E0, 2.0f);
        FastVecAdd(vars + 0x1E0, vars + 0x1E0, g_coll_line_hit_point);
    }
}

/* func_L01_003BE058 is in L01_003BB9D0-steer.c. */

/* func_L01_003BE488 */

/* Turns off the moby's glow light and clears its light slot. */
void moby_free_glow_light(L01_003BE488_OBJ *moby)
{
    L01_003BE488_OWNED *vars = moby->f68;

    if (vars->f202 != -1) {
        vars->f204 = 0;
        gfx_free_point_light(vars->f202);
        vars->f202 = -1;
    }
}

typedef struct L01_003BE4D0_OBJ {
    char pad0[0x20];
    unsigned char f20;
    char pad21[0x68 - 0x21];
    struct L01_003BE4D0_STATE *f68;
    char pad6C[0x96 - 0x6C];
    unsigned short f96;
    char pad98[0xBC - 0x98];
    unsigned char fBC;
} L01_003BE4D0_OBJ;

typedef struct L01_003BE4D0_STATE {
    char pad0[0x114];
    int f114;
    char pad118[0x230 - 0x118];
    int timer230;
    char pad234[0x238 - 0x234];
    int timer238;
    int timer23C;
    char pad240[0x290 - 0x240];
    int f290;
} L01_003BE4D0_STATE;

extern void get_moby_color(void *, int *, int *, int *);
extern void set_moby_color(void *, int, int, int);
extern int func_002E4600(unsigned int, unsigned int, float);

/* Counts down the moby's timers and fades its colour towards the glow colour or back to dark. */
void firefly_update_timers_and_color(L01_003BE4D0_OBJ *moby)
{
    L01_003BE4D0_STATE *vars = moby->f68;
    int red, green, blue;
    unsigned int target;
    int color;

    if (moby->fBC != 0) {
        moby->fBC = 0;
        if (vars->timer238 < 200) {
            vars->timer238 = math_random_int_range(300, 360);
        }
    }
    if (vars->f114 != 1) {
        math_fast_float_d(&vars->timer238);
    }
    if (moby->f96 <= 0xFFFD) {
        moby->f96 = moby->f96 + 1;
    }
    math_fast_float_d(&vars->timer230);
    math_fast_float_d(&vars->timer23C);
    /* Pack the current colour as 0x80BBGGRR, then blend it towards the target. */
    get_moby_color(moby, &red, &green, &blue);
    {
        unsigned int alpha_green = (green << 8) | 0x80000000u;
        unsigned int alpha_blue_green = (blue << 16) | alpha_green;
        color = alpha_blue_green | red;
    }
    if (vars->f290 != 0 && moby->f20 < 9) {
        target = 0x8040E0F0;
        color = func_002E4600(color, target, 0.05f);
    } else {
        target = 0x00404040;
        color = func_002E4600(color, target, 0.08f);
    }
    red = color & 0xFF;
    green = (color >> 8) & 0xFF;
    blue = (color >> 16) & 0xFF;
    set_moby_color(moby, red, green, blue);
}

/* func_L01_003BE628 is in L01_003BE628.c. */

/* func_L01_003BFDC8 */

/* Switches the moby to a new animation when it is not already playing it and sets its animation speed. */
void moby_set_animation_and_speed(L01_003BFDC8_OBJ *moby, int anim_index, int unused_param, int blend_frames)
{
    L01_003BFDC8_OBJ *obj = moby;

    if (obj->f43 != anim_index) {
        anim_start_blended(moby);
    }
    if (anim_index != 12) {
        obj->f48 = 0.6666667f;
    }
    if ((unsigned int)(anim_index - 6) < 3) {
        obj->f48 = obj->f48 * 1.25f;
    }
}

/* func_L01_003BFE48 is in L01_003BFE48-g8.c. */

/* func_L01_003C01C0 is in L01_003C01C0-g8.c. */

/* func_L01_003C0408 is in L01_003C0408-g8.c. */

/* func_L01_003C08A0 is in L01_003C08A0.c. */


/* func_L01_003C2680 is in L01_003C2680-g8.c. */


/* func_L01_003C97D8 is in L01_003C97D8-draw.c. */

/* func_L01_003C9D00 is in L01_003C9D00.c. */
