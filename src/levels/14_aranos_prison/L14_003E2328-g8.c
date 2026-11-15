#include "include_asm.h"
#include "common.h"

typedef struct {
    char pad00[0x5C];
    int flags;
    int proximity;
    int contact;
    int mobIndex;
    unsigned char *linked;
    int openTime;
    int activeTime;
    int closeTime;
    int timer;
    int requested;
    int color;
    int emitTimer;
} FieldState;

typedef struct {
    char pad00[0x10];
    float position[4];
    unsigned char state;
    char pad21[3];
    char *model;
    char pad28[9];
    unsigned char active;
    char pad32[2];
    unsigned short flags;
    char pad36[0x32];
    FieldState *data;
    char pad6C[0xC];
    int color;
    char pad7C[0x1C];
    int animation;
} FieldMob;

typedef struct {
    float pos[4][4];
    u32 color[4];
    float uv[4][2];
    char tail[24];
    u64 regs;
} DrawPacket;

extern void get_moby_color(void *, int *, int *, int *);
extern void set_moby_color(void *, int, int, int);
extern void moby_set_state(void *, int, int);
extern int flag_set_first_pending(void *);
extern int math_fast_float_d(int *);
extern int FastTweenColor(int, int, float);
extern void gfx_add_draw_callback_third(void (*)(char *), char *);
extern int hero_is_current_selected_id(void *);
extern void moby_copy_pos_rot(void *, void *, void *);
extern void moby_pass_pos_rot_to_helper(void *, void *, void *);
extern void moby_rebuild_matrix_scaled(void *);
extern float moby_get_state_progress(void *);
extern void DrawFadingField(char *self);
extern void gfx_calc_wobble_quad_corner(void *, void *, int, void *, void *, void *, int, int);
extern void part_l14_spawn_flash(void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void transform_vector(void *, void *, void *);
extern void draw_world_quad(void *, void *, int);
extern void gfx_init_quad_packet_state(void *, int, int, int);
extern void VU1_addGSregister(int, u64);

/* The level's entity array, read as a bare symbol (lui/lw) as in the level's other units. */
extern unsigned char *D_L14_001B259C_base[3] __asm__("D_L14_001B259C") __attribute__((sda));
extern float D_00189EA8 NOT_SDA;
extern FieldMob *D_0018A0B4 NOT_SDA;
extern char D_0018A0E0[];
extern char D_L14_001B9500[];
/* sda keeps the 64-byte corner table one `la` macro at -G8. */
extern float D_L14_001AA250[4][4] __attribute__((sda));
extern float D_L14_001B04BC __attribute__((sda));
extern float D_L14_001B04C0 __attribute__((sda));
extern int D_L14_001B04C4 __attribute__((sda));
extern int D_L14_001B04C8 __attribute__((sda));
extern int D_L14_001B04CC __attribute__((sda));
extern int D_L14_001B04D0 __attribute__((sda));

/* A field that cycles off (1) -> rising (2) -> on (3) -> falling (4) -> off. Rising and
   falling run the same emitter, colour fade and draw (written out in both cases; the compiler
   cross-jumps the copies into one tail, as in retail); the on state can pass a request on to
   the linked entity when that is another field (class 0xAFE). */
/* Draws the field: a quad of four corners scaled by the fade, then an 8 x 8 grid of cells. */
void DrawFadingField(char *self) {
    DrawPacket p __attribute__((aligned(16)));
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float corners[4][4] __attribute__((aligned(16)));
    float x[4] __attribute__((aligned(16)));
    float y[4] __attribute__((aligned(16)));
    float off[4] __attribute__((aligned(16)));
    int i, j, k;

    qcopy(pos, self + 0x10);
    FastVecSub(a, D_L14_001B9500, pos);
    vec_scale_to_length(a, a, 1.0f);
    FastVecCross(b, a, D_0018A0E0);
    vec_scale_to_length(b, b, 1.0f);
    FastVecCross(c, b, a);
    FastVecScale(off, a, D_L14_001B04C0);
    FastVecAdd(pos, pos, off);
    for (i = 0; i < 4; i++) {
        FastVecScale(p.pos[i], D_L14_001AA250[i], D_L14_001B04BC * moby_get_state_progress(self));
        transform_vector(p.pos[i], p.pos[i], a);
        qcopy(corners[i], p.pos[i]);
    }
    gfx_init_quad_packet_state(&p, 0x3C, 1, 0x80);
    p.regs = 0x800000004AULL;
    p.color[0] = p.color[1] = p.color[2] = p.color[3] = 0x80808080;
    p.uv[0][0] = 0;
    p.uv[0][1] = 0;
    p.uv[1][0] = 0;
    p.uv[1][1] = 1;
    p.uv[2][0] = 1;
    p.uv[2][1] = 0;
    p.uv[3][0] = 1;
    p.uv[3][1] = 1;
    VU1_addGSregister(0x47, 0x31001);
    draw_world_quad(&p, 0, 0);
    gfx_init_quad_packet_state(&p, -1, 2, 0x80);
    p.regs = 0x8000000054ULL;
    VU1_addGSregister(0x47, 0x53001);
    FastVecSub(x, corners[2], corners[0]);
    FastVecSub(y, corners[1], corners[0]);
    for (j = 0; j < 8; j++) {
        for (k = 0; k < 8; k++) {
            gfx_calc_wobble_quad_corner(self, &p, 0, corners, x, y, j, k);
            gfx_calc_wobble_quad_corner(self, &p, 1, corners, x, y, j, k + 1);
            gfx_calc_wobble_quad_corner(self, &p, 2, corners, x, y, j + 1, k);
            gfx_calc_wobble_quad_corner(self, &p, 3, corners, x, y, j + 1, k + 1);
            draw_world_quad(&p, 0, 0);
        }
    }
    VU1_addGSregister(0x47, 0x5360B);
}
