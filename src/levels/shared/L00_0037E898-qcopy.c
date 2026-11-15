#include "include_asm.h"
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad bits; float f[4]; } Vector;

extern char *slot_get_by_index(int);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void mat_transform_via_copy(void *, void *);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);

/* Builds a rotation from the input direction and places the owner's part with it, then fixes up its position. */
void moby_l00_place_part_from_direction(char *owner, char *input)
{
    Vector local[7];
    char *transform = slot_get_by_index(*(int *)(*(char **)(owner + 0x68) + 0x48));
    qcopy(&local[3], input);
    qcopy(&local[0], &local[3]);
    local[4].bits = 0;
    local[4].f[2] = 1.0f;
    FastVecCross(&local[1], &local[0], &local[4]);
    vec_scale_to_length(&local[1], &local[1], 1.0f);
    FastVecCross(&local[2], &local[1], &local[0]);
    mat_transform_via_copy(transform + 0x10, &local[0]);
    moby_transform_joint_to_world(owner, 0, &local[5]);
    matrix_mul_vec3(&local[3], input, owner + 0xC0);
    FastVecAdd(&local[6], &local[3], &local[5]);
}

/* Builds a rotation from the input direction and places the owner's part with it, then fixes up its position. */
void moby_l00_place_part_from_direction_2(char *owner, char *input)
{
    Vector local[7];
    char *transform = slot_get_by_index(*(int *)(*(char **)(owner + 0x68) + 0x48));
    qcopy(&local[3], input);
    qcopy(&local[0], &local[3]);
    local[4].bits = 0;
    local[4].f[2] = 1.0f;
    FastVecCross(&local[1], &local[0], &local[4]);
    vec_scale_to_length(&local[1], &local[1], 1.0f);
    FastVecCross(&local[2], &local[1], &local[0]);
    mat_transform_via_copy(transform + 0x10, &local[0]);
    moby_transform_joint_to_world(owner, 0, &local[5]);
    matrix_mul_vec3(&local[3], input, owner + 0xC0);
    FastVecAdd(&local[6], &local[3], &local[5]);
}

extern int math_fast_float_d(int *);
extern float IntToFloat(int);
extern int FloatToInt(float);
/* Fades the object's colour back toward grey as its countdown runs out. */
void moby_fade_colour_by_countdown(char *object)
{
    Vector colour;
    char *data = *(char **)(object + 0x68);
    float fraction;
    unsigned int r, g, b, c;
    colour.bits = 0;
    colour.f[0] = 128.0f;
    colour.f[1] = 128.0f;
    colour.f[2] = 128.0f;
    colour.f[3] = 255.0f;
    math_fast_float_d((int *)(data + 0x10));
    fraction = IntToFloat(*(int *)(data + 0x10));
    fraction /= IntToFloat(30);
    r = FloatToInt((colour.f[0] - 255.0f) * fraction + 255.0f);
    g = FloatToInt((colour.f[1] - 64.0f) * fraction + 64.0f);
    b = FloatToInt((colour.f[2] - 64.0f) * fraction + 64.0f);
    c = (g << 8) | 0xFF000000;
    *(unsigned int *)(object + 0x78) = ((b << 16) | c) | r;
}

extern int g_current_map_index[] __attribute__((sda));
extern int D_L00_001B90C4[];
extern float D_L00_001B90C8[];
extern int D_L00_001B273C[] __attribute__((sda));
extern Quad D_L00_001AECC0[4] SDATA(D_L00_001AECC0);
extern float lens_flare_get_visibility(void *);
extern void sparkle_init_table(void *);
extern void DrawLevelLensFlare(void *);
extern void gfx_add_draw_callback_first(void (*)(void *), void *);
/* Updates the lens flare object. At first it picks which sun to show for the current level; after that it measures how visible the sun is and draws the flare. */
void lens_flare_update(unsigned char *object)
{
    Quad *data=*(Quad **)(object+0x68);
    switch (object[0x20]) {
    case 0: {
        int level;
        int index=0;
        object[0x30]=255;
        object[0x20]=1;
        D_L00_001B90C4[0]=0;
        level=g_current_map_index[0];
        if (level==0) D_L00_001B273C[0]=0x49;
        else if (level==3) D_L00_001B273C[0]=0x40;
        else if (level==7) { D_L00_001B273C[0]=0x3F; index=1; }
        else if (level==12) { D_L00_001B273C[0]=0x41; index=2; }
        else if (level==14) { D_L00_001B273C[0]=0x4D; index=3; }
        *data=D_L00_001AECC0[index];
        sparkle_init_table(object);
        break;
    }
    case 1: {
        D_L00_001B90C8[0]=lens_flare_get_visibility(object);
        gfx_add_draw_callback_first(DrawLevelLensFlare,object);
        break;
    }
    }
}
