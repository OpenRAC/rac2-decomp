#include "include_asm.h"
#include "names.h"

/* Small data reached through $gp: only one instruction at -G8. */
extern int D_L04_001B0710 __attribute__((sda));
extern int D_L04_001B0714 __attribute__((sda));
extern int D_L04_001B0718 __attribute__((sda));

extern char water_draw_ripple_surface[];

extern void set_moby_color(void *, int, int, int);
extern void gfx_add_draw_callback_first(void *, void *);

extern int D_L04_001BFAD8 __attribute__((nosda));
extern int g_hero_moby __attribute__((nosda));
extern char D_L04_001A8F20[1];
extern int D_L04_001B0CF8 __attribute__((sda));

extern int coll_sweep_from_object(void *, void *, int, int, float, float, float, int, int);
extern int coll_test_point(void *, int, float, void *);
extern void part_spawn_sparks_around_moby(void *owner, char *offset, void *filter);
extern int math_fast_float_d(void *);

extern int D_L04_001B07B0 __attribute__((sda));
extern int D_L04_001B07B4 __attribute__((sda));
extern int D_L04_001B07B8 __attribute__((sda));
extern char D_L04_001B9680[];
extern char water_draw_ripple_surface_second[];
extern void gfx_add_draw_callback_third(void *, void *);

/* Sets up the object on its first frame, then keeps registering its update routine and clearing its flags. */
void barlow_water_register_update(char *mobyArg)
{
    char *moby = mobyArg;

    if (*(unsigned char *)(moby + 0x20) == 0) {
        set_moby_color(moby, D_L04_001B0710, D_L04_001B0714, D_L04_001B0718);
        *(unsigned char *)(moby + 0x20) = 1;
    } else {
        set_moby_color(moby, D_L04_001B0710, D_L04_001B0714, D_L04_001B0718);
        gfx_add_draw_callback_first(water_draw_ripple_surface, moby);
        *(unsigned short *)(moby + 0x34) = (*(unsigned short *)(moby + 0x34) & ~1) | 1;
        *(unsigned short *)(moby + 0x32) = 0;
    }
}

extern int g_moby_l04_pool __attribute__((sda));
extern char g_moby_l04_group_lists[];

/* Checks if the object is hit and starts a 60 frame countdown, while it runs the countdown it keeps the effect going. */
void barlow_hit_countdown_update(char *mobyArg)
{
    char *moby = mobyArg;
    char *position = moby + 0x10;

    coll_sweep_from_object(moby, position, 0x10001, 5, 1.0f, 1.0f, 1.0f, 1, 0);
    if (coll_test_point(position, 1, 1.0f, moby) != 0) {
        if (D_L04_001BFAD8 != 0 && D_L04_001BFAD8 == g_hero_moby) {
            if (D_L04_001B0CF8 <= 0) {
                D_L04_001B0CF8 = 0x3C;
            }
        }
    }
    if (D_L04_001B0CF8 > 0) {
        part_spawn_sparks_around_moby(g_hero_moby, D_L04_001A8F20, 0xFFFF);
        math_fast_float_d(&D_L04_001B0CF8);
    }
}

typedef int TI128 __attribute__((mode(TI)));

/* The flat quad the effect submits: four positions, four colours, four uv
   pairs and the four GS words (primitive, texture, mode, registers). */
typedef struct {
    TI128 position[4];
    unsigned int color[4];
    float uv[4][2];
    unsigned long primitive, texture, mode, registers;
} EffectQuad;

typedef struct {
    TI128 saved;
    EffectQuad quad;
    float a[4];
    float b[4];
    float c[4];
    TI128 corner;
} EffectQuadFrame;

extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern unsigned long GetEffectTextureDescriptor(int);
extern void draw_world_quad(void *, void *, int);
extern char D_L04_001B9680[];
/* The two uv columns: macro-addressed tables, so each base is one la. */
extern float D_L04_001AFDA0[] __attribute__((sda));
extern float D_L04_001AFDA4[] __attribute__((sda));

/* The quad between the two end points at +0x260 and +0x270: each side
   is pulled a tenth of the way toward the level's anchor, then the four
   corners are crossed out from the span and submitted. */
/* Draws the red glowing beam strip between the two end points stored in the object. */
void gfx_draw_tether_beam_red(char *obj, void *q)
{
    EffectQuadFrame frame;
    char *vars;
    int i;

    frame.saved = *(TI128 *)q;
    vars = *(char **)(obj + 0x68);
    FastVecSub(frame.c, vars + 0x260, vars + 0x270);
    FastVecSub(frame.a, vars + 0x260, D_L04_001B9680);
    FastVecSub(frame.b, vars + 0x270, D_L04_001B9680);
    FastVecCross(frame.a, frame.a, frame.c);
    vec_scale_to_length(frame.a, frame.a, 0.1f);
    FastVecCross(frame.b, frame.b, frame.c);
    vec_scale_to_length(frame.b, frame.b, 0.1f);
    frame.quad.texture = GetEffectTextureDescriptor(7);
    frame.quad.mode = 0x0000ff9000000260UL;
    frame.quad.registers = 0x7000000048UL;
    frame.quad.primitive = 0;
    frame.quad.color[0] = frame.quad.color[1] = frame.quad.color[2] = frame.quad.color[3] = 0x2F0000FF;
    for (i = 0; i < 4; i++) {
        frame.quad.uv[i][0] = D_L04_001AFDA0[i * 2];
        frame.quad.uv[i][1] = D_L04_001AFDA4[i * 2];
    }
    FastVecSub(&frame.corner, vars + 0x260, frame.a);
    frame.quad.position[0] = frame.corner;
    FastVecAdd(&frame.corner, vars + 0x260, frame.a);
    frame.quad.position[1] = frame.corner;
    FastVecSub(&frame.corner, vars + 0x270, frame.b);
    frame.quad.position[2] = frame.corner;
    FastVecAdd(&frame.corner, vars + 0x270, frame.b);
    frame.quad.position[3] = frame.corner;
    draw_world_quad(&frame.quad, 0, 0);
}

extern char D_L04_001B9680[];
/* The two uv columns: macro-addressed tables, so each base is one la. */
extern float D_L04_001AFDA0[] __attribute__((sda));
extern float D_L04_001AFDA4[] __attribute__((sda));

/* The quad between the two end points at +0x260 and +0x270: each side
   is pulled a twentieth of the way toward the level's anchor, then the four
   corners are crossed out from the span and submitted (then drawn again as the overlay). */
/* Draws the white beam strip between the two end points, then draws it again as an overlay. */
void gfx_draw_tether_beam_white(char *obj, void *q)
{
    EffectQuadFrame frame;
    char *vars;
    int i;

    frame.saved = *(TI128 *)q;
    vars = *(char **)(obj + 0x68);
    FastVecSub(frame.c, vars + 0x260, vars + 0x270);
    FastVecSub(frame.a, vars + 0x260, D_L04_001B9680);
    FastVecSub(frame.b, vars + 0x270, D_L04_001B9680);
    FastVecCross(frame.a, frame.a, frame.c);
    vec_scale_to_length(frame.a, frame.a, 0.05f);
    FastVecCross(frame.b, frame.b, frame.c);
    vec_scale_to_length(frame.b, frame.b, 0.05f);
    frame.quad.texture = GetEffectTextureDescriptor(0x13);
    frame.quad.mode = 0x0000ff9000000260UL;
    frame.quad.registers = 0x8000000048UL;
    frame.quad.primitive = 0;
    frame.quad.color[0] = frame.quad.color[1] = frame.quad.color[2] = frame.quad.color[3] = 0x2FFFFFFF;
    for (i = 0; i < 4; i++) {
        frame.quad.uv[i][0] = D_L04_001AFDA0[i * 2];
        frame.quad.uv[i][1] = D_L04_001AFDA4[i * 2];
    }
    FastVecSub(&frame.corner, vars + 0x260, frame.a);
    frame.quad.position[0] = frame.corner;
    FastVecAdd(&frame.corner, vars + 0x260, frame.a);
    frame.quad.position[1] = frame.corner;
    FastVecSub(&frame.corner, vars + 0x270, frame.b);
    frame.quad.position[2] = frame.corner;
    FastVecAdd(&frame.corner, vars + 0x270, frame.b);
    frame.quad.position[3] = frame.corner;
    draw_world_quad(&frame.quad, 0, 0);
    frame.quad.texture = GetEffectTextureDescriptor(0x10);
    frame.quad.mode = 0x0000ff9000000260UL;
    frame.quad.registers = 0x8000000048UL;
    frame.quad.primitive = 0;
    draw_world_quad(&frame.quad, 0, 0);
}
