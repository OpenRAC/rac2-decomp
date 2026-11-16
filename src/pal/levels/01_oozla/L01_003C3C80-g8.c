/* func_PAL_L01_003C3C80, the PAL copy of func_L01_003BFE48: the same C, where the f7c-f8c tuning
   values rise for 50 Hz (x1.2 for f7c and f80, x36/25 for f84-f8c) and the scale constants change. */
#include "common.h"

typedef struct {
    char pad0[24];
    float f18;
    char pad1c[24];
    unsigned short f34;
    char pad36[134];
    unsigned char fbc;
} L01_003BFE48_OBJ;

typedef struct {
    char pad0[40];
    unsigned char f28;
    unsigned char f29;
    unsigned char f2a;
    char pad2b[3];
    unsigned char f2e;
    char pad2f[1];
    float f30;
    char pad34[12];
    float f40;
    float f44;
    unsigned char f48;
    char pad49[1];
    unsigned char f4a;
    char pad4b[37];
    unsigned char f70;
    unsigned char f71;
    unsigned char f72;
    char pad73[3];
    unsigned char f76;
    unsigned char f77;
    char pad78[4];
    float f7c;
    float f80;
    float f84;
    float f88;
    float f8c;
    float f90;
    float f94;
    char pad98[4];
    float f9c;
    char pada0[8];
    int fa8;
    char padac[32];
    unsigned char fcc;
    unsigned char fcd;
    signed char fce;
    signed char fcf;
    char padd0[2];
    signed char fd2;
    signed char fd3;
    char padd4[3];
    unsigned char fd7;
    char padd8[4];
    int fdc;
    char pade0[80];
    float f130;
    float f134;
    float f138;
    float f13c;
    float f140;
    char pad144[24];
    float f15c;
    float f160;
    char pad164[8];
    int f16c;
    char pad170[336];
    int f2c0;
    int f2c4;
    int f2c8;
    char pad2cc[20];
    unsigned char f2e0;
    unsigned char f2e1;
    unsigned char f2e2;
    char pad2e3[5];
    float f2e8;
    float f2ec;
} L01_003BFE48_STATE;

extern int FloatToInt(float);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern float path_l01_compute_segment_lengths(void *);
extern void *moby_spawn_linked_helper(void *, void *, int, float, float);
extern void moby_set_state(void *, int, int);
extern void moby_set_animation_and_speed(void *, int, int, int);
extern char *g_path_l01_table[];
extern float g_swamp_monster_init_param __attribute__((sda));
extern float g_swamp_monster_range_near __attribute__((sda));
extern float g_swamp_monster_limit_speed_a __attribute__((sda));
extern float g_swamp_monster_limit_angular_a __attribute__((sda));
extern float g_swamp_monster_limit_turn_a __attribute__((sda));
extern float g_swamp_monster_limit_step_a __attribute__((sda));

/* Sets up a Swamp Monster II when it first appears: its speeds, health and sizes, and its starting animation (PAL: 50 Hz timings). */
void swamp_monster_init_pal(L01_003BFE48_OBJ *moby)
{
    L01_003BFE48_STATE *state = *(L01_003BFE48_STATE **)((char *)moby + 0x68);

    state->fd7 = 1;
    state->f70 = 255;
    state->fa8 = 6;
    state->f71 = 19;
    state->f72 = 19;
    state->f76 = 20;
    state->f77 = 255;
    state->f7c = 0.275f;
    state->f80 = 0.18f;
    state->f84 = 0.019800002f;
    state->f88 = 0.0019f;
    state->f8c = 0.006f;
    state->f90 = 0.5f;
    state->f94 = 0.5f;
    state->f9c = 0.15f;
    state->fcc = 6;
    state->fcd = 25;
    state->fdc = state->f2c0;
    state->fce = -1;
    state->fcf = -1;
    state->fd2 = -1;
    state->fd3 = -1;
    state->f48 = FloatToInt(40.0f);
    state->f4a = FloatToInt(28.0f);
    state->f2a = 48;
    state->f28 = 4;
    state->f29 = 1;
    state->f2e = 1;
    state->f40 = 6.0f;
    state->f44 = 3.3f;
    state->f30 = 2.0f;
    moby->f34 |= 0x1000;
    state->f16c = state->f2c4;
    state->f130 = 4.0f;
    state->f134 = 0.35f;
    state->f138 = 0.1f;
    state->f13c = 0.1f;
    state->f140 = 0.3490659f;
    state->f160 = 0.52359885f;
    state->f15c = g_swamp_monster_init_param * 0.00040000002f;
    moby_set_controller_speed_limits(moby, g_swamp_monster_limit_speed_a * 0.00040000002f,
                 g_swamp_monster_limit_step_a * 0.020000001f,
                 g_swamp_monster_limit_angular_a * 6.981318e-06f,
                 g_swamp_monster_limit_turn_a * 0.0003490659f);
    state->f28 = 3;
    moby->fbc = 0;
    if (state->f2c8 != -1) {
        path_l01_compute_segment_lengths(g_path_l01_table[state->f2c8]);
    }
    if (state->f2c4 != -1) {
        path_l01_compute_segment_lengths(g_path_l01_table[state->f2c4]);
    }
    if (state->f2c0 != -1) {
        path_l01_compute_segment_lengths(g_path_l01_table[state->f2c0]);
    }
    moby_spawn_linked_helper(moby, (char *)moby + 0x10, 11, 1.2f, 2.0f);
    state->f2e1 = 1;
    state->f2e0 = 0;
    state->f2e2 = 0;
    state->f2e8 = moby->f18;
    state->f2ec = g_swamp_monster_range_near;
    moby_set_state(moby, 0, 1);
    moby_set_animation_and_speed(moby, 0, 0, 2);
}
