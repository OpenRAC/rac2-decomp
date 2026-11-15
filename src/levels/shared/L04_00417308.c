#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

typedef unsigned short u16;

typedef unsigned int u32;

typedef short s16;

typedef int s32;

typedef float f32;

/* func_L04_00417308 is defined in L04_00417308-hud-g8.c. */

/* func_L04_00418A58 is defined in L04_00418A58-g8.c. */

/* func_L04_00418BF0 is in L04_00418BF0-g8.c. */

/* func_L04_004195E0 is defined in L04_004195E0-g8.c. */

/* func_L04_00419918 is defined in L04_00419918-g8.c. */

/* func_L04_0041AD18 is defined in L04_0041AD18-g8.c. */


/* func_L04_00432258 is defined in L04_00432258.c. */

/* func_L04_004323F8 is defined in L04_004323F8.c. */

/* func_L04_00432530 is defined in L04_00432530.c. */





/* func_L04_0043BC58 is defined in L04_0043BC58-g8.c. */

extern void euler_rotation_basis(char *a, char *b);

extern void FastVecScale(char *a, char *b, float f);

extern int FastTweenColor(int a, int b, float f);

extern void set_moby_color(void *a, u8 b, u8 c, u8 d);

extern void func_002A10E8(void *a);

/* Applies the fade size and colour of a linked object to the object it follows. */
void moby_apply_fade_color_to_linked(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    char *linked;
    char *linked2;
    char *linked3;
    char *linked4;
    float scale;
    s32 color;

    linked = *(char **)(vars + 0x48);
    *(u16 *)(linked + 0x34) &= 0xFFFE;
    *(u8 *)(*(char **)(vars + 0x48) + 0x31) = 1;
    linked2 = *(char **)(vars + 0x48);
    *(s32 *)(linked2 + 0x98) = *(s32 *)(*(s32 *)(linked2 + 0x24) + 0x10);
    linked3 = *(char **)(vars + 0x48);
    euler_rotation_basis(linked3 + 0xC0, linked3 + 0xF0);
    linked4 = *(char **)(vars + 0x48);
    scale = *(float *)(vars + 0x58);
    FastVecScale(linked4 + 0xE0, linked4 + 0xE0, scale);
    scale = *(float *)(vars + 0x58);
    color = FastTweenColor(0x800000FF, *(s32 *)(vars + 0x54), scale);
    set_moby_color(*(char **)(vars + 0x48), color & 0xFF, (color >> 8) & 0xFF, (color >> 16) & 0xFF);
    func_002A10E8(*(char **)(vars + 0x48));
}


/* func_L04_0043BEE8 is defined in L04_0043BEE8-g8.c. */

extern char D_L04_001B9680[];
extern void FastVecSub(float *, const float *, const float *);
extern void vec_scale_to_length(char *, char *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_float_range(float, float);
extern int math_random_int_below(int);
extern float math_random_signed_float_range(float, float);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern char *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, int, float);
extern int FloatToInt(float);

/* Emits paired particles with opposite spin and randomized velocities. */
void part_l04_spawn_spinning_pairs(float *pos, int count) {
    float velocity[4], origin[4], direction[4], axis[4], offset[4];
    float size, angle;
    int i;
    int sign;
    char *particle;
    FastVecSub(direction, (float *)D_L04_001B9680, pos);
    vec_scale_to_length((char *)offset, (char *)direction, 0.3f);
    direction[2] = 0;
    axis[0] = 0;
    axis[1] = 0;
    axis[2] = 1.0f;
    axis[3] = 1.0f;
    for (i = 0; i < count; i++) {
        size = math_random_float_range(0.5f, 2.0f);
        sign = math_random_int_below(2);
        if (!sign) sign--;
        angle = math_random_float_range(-1.0471977f, 1.0471977f);
        math_apply_axis_rotation_to_quat(velocity, direction, axis, angle);
        vec_scale_to_length((char *)velocity, (char *)velocity, math_random_float_range(0.05f, 3.0f) * 0.0166666675f);
        velocity[2] = math_random_float_range(1.0f, 5.0f) * 0.0166666675f;
        FastVecAdd(origin, pos, offset);
        pos[0] += math_random_signed_float_range(0, 0.15f);
        pos[1] += math_random_signed_float_range(0, 0.15f);
        pos[2] += math_random_signed_float_range(0, 0.15f);
        particle = part_spawn_ground_effect(origin, 60, size * 0.1f, size, 0x7F207F7F, 0, sign, velocity, 0, 0.002f);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
        particle = part_spawn_ground_effect(origin, 60, size * 0.07f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        if (particle) particle[9] = FloatToInt(4.0f) + 0x70;
    }
}

/* func_L04_00454BF8 is matched in L04_00454BF8.c (built with -g). */

/* func_L04_00455418 is in L04_00455418.c. */

/* Smooth step: eases a value from 0 to 1 (3x^2 - 2x^3). */
/* evaluates the ordered scalar cubic value squared times negative two times value plus three */
f32 math_smooth_step(f32 value) {
    f32 squared = value * value;
    value = value * -2.0f;
    value = value + 3.0f;
    return squared * value;
}

extern void func_33B9B0(char *a0, int a1, int a2);

extern void *func_33E6B0(char *a0, int a1, int a2);

extern void func_348788(char *a0, int a1, float f12);

extern void func_382DF8(int a0, int a1, char *a2);

extern void func_345860(char *a0, int a1, float f12, float f13, float f14, float f15);

extern void func_3317E8(char *a0);

/* Waits for a trigger, then plays a short effect sequence once it has fired. */
void triggered_effect_update(char *moby)
{
    char *vars = *(char **)(moby + 0x68);

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        func_33B9B0(moby, 1, -1);
        break;
    case 1:
        if (func_33E6B0(moby, 0x4010000, 0) != 0 && *(int *)vars == 0)
            func_33B9B0(moby, 2, -1);
        *(unsigned char *)(moby + 0xA8) = 0xFF;
        break;
    case 2:
        func_348788(moby, 1, 0.0f);
        func_382DF8(0, 0, moby);
        func_345860(moby, 0x1E, 0.4f, 4.4f, 1.0f, 0.083333333f);
        func_3317E8(moby);
        break;
    }
}



/* func_L04_00459408 is defined in L04_00459408.c. */

/* rac1-decomp src/game/stub.c: func_001E97C8 */
/* Takes an argument (callers pass one, e.g. r1_func_001EC210) and ignores
   it -- the unused parameter costs no codegen, still 0/8. */
int stub_l04_return_zero(void *unused) {
    return 0;
}

/* func_L04_0046CD68 is defined in L04_00417308-g8.c (this unit has no $gp access for it). */



/* func_L04_0046CE68 is defined in L04_0046CE68.c. */

/* func_L04_0046CFB8 is defined in L04_0046CFB8-g8.c. */

/* func_L04_0046D250 is in L04_0046D250-g8.c. */


extern s32 D_L04_001B1E84 __attribute__((sda));

extern s32 g_moby_l04_pool __attribute__((sda));

/* Tells whether the object linked to this one is in state 2 or 3. */
int moby_is_linked_in_state_two_or_three(u8 *moby)
{
    s32 entryAddr = (*(s16 *)(moby + 0x84) << 5) + D_L04_001B1E84;
    u8 *linked = (u8 *)(g_moby_l04_pool + (*(s32 *)(*(s32 *)(entryAddr + 0x1C) + 0x60) << 8));
    return (u32)(*(u8 *)(linked + 0x20) - 2) < 2;
}

/* Empty handler that does nothing. */
void moby_l04_empty_handler(void)
{
}

/* Empty handler that does nothing. */
void moby_l04_empty_handler_2(void)
{
}



/* Empty handler that does nothing. */
void moby_l04_empty_handler_3(void)
{
}

/* Empty handler that does nothing. */
void moby_l04_empty_handler_4(void)
{
}


/* Empty handler that does nothing. */
void moby_l04_empty_handler_5(void)
{
}
