#include "include_asm.h"
#include "common.h"

extern void func_002F0538(int);

extern void func_002E7D48(int, int, int, int);

extern unsigned int g_screen_overlay_color;

extern short g_screen_overlay_active;

extern void func_002E5C40(void);

/* Clears the screen effects and sets the screen overlay colour from a flag, then applies it. */
void gfx_reset_screen_overlay(void)
{
    func_002F0538(0);
    func_002E7D48(0, 0, 0, 0x80);
    if (g_screen_overlay_active != 0)
        g_screen_overlay_color = 0x100FF;
    else
        g_screen_overlay_color = 0x70;
    func_002E5C40();
}

typedef int Quad __attribute__((mode(TI)));
extern int func_001163B0(void);
extern void func_001163A0(int);
extern float math_random_signed_float_range(float,float);
extern float math_random_float_range(float,float);
extern int FastTweenColor(int,int,float);
extern int math_random_int_below(int);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void *part_spawn_hero_relative(void *,void *,int,int,float,int,int);
extern int g_burst_l00_particle_count __attribute__((sda));
extern int g_burst_color_pair[2];
extern float g_burst_y_velocity_range __attribute__((sda));
extern float g_burst_z_velocity_range;
extern float g_burst_speed_range[2];
extern char g_camera_l00_position[];
extern char g_default_vector[] MACRO_ADDR;

/* Throws a burst of randomly aimed, randomly coloured particles from the controller's position. */
void part_l00_spawn_random_burst(char *object)
{
    union { Quad q; float f[4]; } vectors[2];
    char *state=*(char **)(object+0x68);
    int saved=func_001163B0();
    int i=0;
    func_001163A0(*(int *)(state+0x68));
    while(i<g_burst_l00_particle_count) {
        float speed,blend;
        int color;
        unsigned char random;
        vectors[1].q=0;
        vectors[1].f[0]=20.0f;
        i++;
        vectors[1].f[1]=math_random_signed_float_range(0.0f,g_burst_y_velocity_range);
        vectors[1].f[2]=math_random_signed_float_range(0.0f,g_burst_z_velocity_range);
        vectors[0].q=vectors[1].q;
        matrix_mul_vec3(&vectors[0],&vectors[0],g_camera_l00_position + 0x230);
        FastVecAdd(&vectors[0],&vectors[0],g_camera_l00_position);
        speed=math_random_float_range(g_burst_speed_range[0],g_burst_speed_range[1]);
        blend=math_random_float_range(0.0f,1.0f);
        color=FastTweenColor(g_burst_color_pair[0],g_burst_color_pair[1],blend);
        random=math_random_int_below(255);
        part_spawn_hero_relative(&vectors[0],g_default_vector,color,2,speed,random,0);
    }
    func_001163A0(saved);
}

extern int sprintf(char *buffer, char *format, ...);

extern void text_draw_coloured(int x, int y, unsigned long colour, char *text, int length);

extern char g_str_burst_value_format[];

extern char g_str_burst_index_format[];

/* A six-word block of x/y pairs and a three-word block of colours. Retail reads
 * element 0 of each through $gp and the other elements as absolute macro loads at
 * an offset from the block, which keeps them out of the call delay slots
 * (docs/build/compiler-notes.md, "reorg: which global loads may fill a slot"). */
extern int g_burst_text_params_a[] MACRO_ADDR;

extern int D_L00_001AEE98_gp SDATA(D_L00_001AEE98);

extern int g_burst_text_params_b[] MACRO_ADDR;

extern int D_L00_001AEEB0_gp SDATA(D_L00_001AEEB0);

/* Draws "Score: %d" (data+0x60), "Level: %d" (data+0x70 plus one) and "Score: %d"
 * (data+0x64) from the object's data (object+0x68), each at its own position and
 * colour. */
void DrawThreeObjectCounters(void *object)
{
    char buffer[0x100];
    char *state = *(char **)((char *)object + 0x68);

    sprintf(buffer, g_str_burst_value_format, *(int *)(state + 0x60));
    text_draw_coloured(D_L00_001AEE98_gp, g_burst_text_params_a[1], g_burst_text_params_b[2], buffer, -1);
    sprintf(buffer, g_str_burst_index_format, *(int *)(state + 0x70) + 1);
    text_draw_coloured(g_burst_text_params_a[2], g_burst_text_params_a[3], g_burst_text_params_b[1], buffer, -1);
    sprintf(buffer, g_str_burst_value_format, *(int *)(state + 0x64));
    text_draw_coloured(g_burst_text_params_a[4], g_burst_text_params_a[5], D_L00_001AEEB0_gp, buffer, -1);
}


/* 128-bit stack vectors reach lq/sq only through TImode. */
typedef int FlareQuad __attribute__((mode(TI)));
typedef union { FlareQuad bits; float f[4]; } FlareVec;
typedef struct { char pad[0x20]; unsigned char flags; } FlareTarget;

extern float fast_vec_dist(void *, void *);
extern float IntToFloat(int);
extern void gfx_project_world_point_to_screen(void *, void *);
extern unsigned long GetEffectTextureDescriptor(int);
extern float math_fabs(float);
extern int FloatToInt(float);
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern void DrawTexturedQuad(int, int, int, int, int, int, int, int,
                         unsigned long, unsigned long);

typedef struct {
    FlareTarget *target;
    int active;
    float intensity;
    int pad;
    short alpha[16];
    short texture[16];
    unsigned int color[16];
    float offset[16];
    float scale[16];
} FlareState;
extern FlareState g_flare_state;
extern int g_reticle_screen_params[] __attribute__((sda));
/* Effect texture base (.bss, set by func_L00_00382AE8); read as retail's tied lui/lw. */
extern int g_lens_flare_textures[] __attribute__((sda));
/* Base sprite size, 64. */
extern int g_burst_base_size[];

/* Projects the flare target to the screen and draws its 14 sprites along the line
   through the screen centre, faded by distance and by how far off-centre it is
   (RAC1 draw_lens_flare; func_L08_003F7A48 draws 12). Both table bases are read
   through pointers set before the loop: reload rematerializes them inside it. */
void DrawLevelLensFlare(char *object)
{
    char *work = *(char **)(object + 0x68);
    FlareVec screen;
    float center[4], delta[4], offset[4], location[4];
    float distance, fade, horizontal, vertical;
    unsigned long texture;
    int color;
    int i, size, left, top;
    int *baseSize;
    int *texBase;

    if (g_flare_state.active != 1 || (g_flare_state.target->flags & 0x80)) {
        g_flare_state.active = 0;
        return;
    }
    if (g_flare_state.intensity <= 0.0f)
        return;
    distance = fast_vec_dist(g_camera_l00_position, work);
    baseSize = g_burst_base_size;
    center[0] = IntToFloat(g_reticle_screen_params[0]);
    center[1] = IntToFloat(g_reticle_screen_params[1]);
    gfx_project_world_point_to_screen(&screen, work);
    screen.f[0] = (screen.f[0] - IntToFloat(g_reticle_screen_params[2])) * 0.0625f;
    screen.f[1] = (screen.f[1] - IntToFloat(g_reticle_screen_params[3])) * 0.0625f;
    delta[0] = center[0] - screen.f[0];
    delta[1] = center[1] - screen.f[1];
    for (i = 0, texBase = g_lens_flare_textures; i < 14; ++i) {
        texture = GetEffectTextureDescriptor(*texBase + g_flare_state.texture[i]);
        offset[0] = delta[0] * g_flare_state.offset[i];
        offset[1] = delta[1] * g_flare_state.offset[i];
        location[0] = center[0] + offset[0];
        location[1] = center[1] + offset[1];
        fade = distance - 5.0f;
        if (fade > 1.0f)
            fade = 1.0f;
        else if (fade < 0.0f)
            fade = 0.0f;
        horizontal = math_fabs(delta[0]) / center[0] * -5.0f + 5.5f;
        if (horizontal > 1.0f)
            horizontal = 1.0f;
        else if (horizontal < 0.0f)
            horizontal = 0.0f;
        vertical = math_fabs(delta[1]) / center[1] * -5.0f + 5.5f;
        if (vertical > 1.0f)
            vertical = 1.0f;
        else if (vertical < 0.0f)
            vertical = 0.0f;
        fade *= horizontal * vertical * g_flare_state.intensity;
        color = (int)(((unsigned int)FloatToInt(fade * g_flare_state.alpha[i]) << 24)
                      | (g_flare_state.color[i] & 0xFFFFFF));
        size = FloatToInt(*baseSize * g_flare_state.scale[i]);
        VU1_addGSregister(66, 0x8000000048ULL);
        left = FloatToInt(location[0] - (float)(size >> 1));
        top = FloatToInt(location[1] - (float)(size >> 1));
        DrawTexturedQuad(left, top, size, size, 0, 0, 64, 64, color, texture);
    }
    g_flare_state.intensity = 0.0f;
}
