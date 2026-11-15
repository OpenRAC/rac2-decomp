#include "include_asm.h"
#include "names.h"


/* func_PAL_L00_00391958 lives in L00_00391958-g8.c. */


typedef int Quad __attribute__((mode(TI)));
extern int g_frame_l00_counter __attribute__((section(".sdata")));
extern void FastVecScale(void *, void *, float);
extern void vec_random_direction(float *, float, float);
extern void FastVecAdd(void *, void *, void *), vec_clear_128(Quad *);
extern float math_random_float_range(float, float);
extern int FastTweenColor(int, int, float), FloatToInt(float);
extern void gravity_offset_position(void *, float *, float *, float);
extern void *part_spawn_trail(void *, void *, void *, int, int, int, int, int, int);
/* func_PAL_L00_00392250, the PAL copy of func_L00_0038F178: the same C, where the kind, duration and size take the 50 Hz scale, 0.016666668f becomes 0.020000001f and 0.0011111111f becomes 0.0016000001f. */
void func_PAL_L00_00392250(char *actor) {
    char *state = *(char **)(actor + 0x68);
    float offset[4], velocity[4], jitter[4];
    float *jitterPoint, *velocityPoint;
    int firstColor, lastColor, kind, duration, size, count;
    if (g_frame_l00_counter & 7) return;
    jitterPoint = jitter;
    velocityPoint = velocity;
    count = 0;
    do {
        count--;
        FastVecScale(offset, state, 0.5f);
        vec_random_direction(jitterPoint, 0.0f, 0.020000001f);
        FastVecAdd(offset, jitterPoint, offset);
        vec_clear_128((Quad *)velocityPoint);
        offset[3] = math_random_float_range(0.25f, 0.15f);
        velocity[3] = math_random_float_range(0.15f, 0.05f);
        firstColor = FastTweenColor(0x804080FF, 0x8040FFFF, math_random_float_range(0.0f, 1.0f));
        lastColor = FastTweenColor(0x80104040, 0x80002080, math_random_float_range(0.0f, 1.0f));
        kind = FloatToInt(((math_random_float_range(0.0f, 1.0f) + 1.0f) * 5.0f + 2.0f) * 0.16666667f);
        duration = FloatToInt(((math_random_float_range(-0.5f, 0.5f) + 1.0f) * 150.0f + 2.0f) * 0.16666667f);
        size = FloatToInt(((math_random_float_range(-0.5f, 0.5f) + 1.0f) * 50.0f + 2.0f) * 0.16666667f);
        gravity_offset_position(actor + 0x10, velocityPoint, velocityPoint, (float)duration * 0.0016000001f);
        part_spawn_trail(actor + 0x10, offset, velocityPoint, firstColor, lastColor, kind, duration, size, 0x10019);
    } while (count >= 0);
}

extern int F6eb4f363_FUN_002A77E0(int mode);
extern float F6eb4f363_FUN_002A90F8(char *object, char *local);
extern void F6eb4f363_FUN_00282D30(char *local, int value, float scale);
extern float F6eb4f363_FUN_002A7878(float low, float high);
extern void F6eb4f363_FUN_002BF728(char *object, char *local, float amount, float base);

/* func_00303568 is defined in 00303568.c. */




/* func_00303E20 is defined in 00303E20.c. */

/* func_00304128 is defined in 00304128.c. */

/* func_00304210 is defined in 00304210-g8.c. */

/* func_00304AD0 uses the profile in 00304AD0-g8-qcopy.c. */

void func_PAL_L00_00392500(char *object)
{
    char local[16];
    float base;
    int value = *(int *)(object + 104);

    if (F6eb4f363_FUN_002A77E0(4))
        return;
    base = F6eb4f363_FUN_002A90F8(object + 16, local);
    F6eb4f363_FUN_00282D30(local, value, 0.25f);
    F6eb4f363_FUN_002BF728(object + 16, local, F6eb4f363_FUN_002A7878(0.05f, 0.1f) * 210000.0f, base);
}


extern int math_random_int_below(int mode);
typedef int TI128 __attribute__((mode(TI)));
typedef unsigned char u8;
typedef float f32;
typedef struct {
    u8 pad00[0x23];
    u8 field23;
    u8 pad24[8];
    f32 field2C;
} NativeUpdate775View;
extern void moby_mark_spawned(NativeUpdate775View *object);
typedef union { TI128 quad; float f[4]; } ParticleUpdateVector;
typedef struct { int color[4]; } ParticleUpdateColors;
extern ParticleUpdateColors D_L00_001AF010;
extern float math_random_float_range(float, float);
extern void vec_scale_to_length(void *, void *, float);
extern int gfx_swap_packed_color_channels(int, int);
extern void part_spawn_scaling(void *, void *, int, int, int, int, int, int);
extern float FastAddRotations(float, float);
extern void FastVecAdd(void *, void *, void *);
extern void moby_mix_on_inner_data(void *, void *, void *, float);
extern float IntToFloat(int);
extern int FastDecTimer(short *);

void func_PAL_L00_00392718(char *object)
{
    ParticleUpdateColors colors;
    ParticleUpdateVector direction, random;
    char *state = *(char **)(object + 0x68);
    int enabled = 1;
    if (*(int *)(state + 0x20) != 0)
        if (math_random_int_below(2))
            enabled = 0;
    if ((*(unsigned char *)(object + 0xBC) & 1) && enabled) {
        int color;
        colors = D_L00_001AF010;
        random.quad = 0;
        random.f[0] = math_random_float_range(-1.0f, 1.0f);
        random.f[1] = math_random_float_range(-1.0f, 1.0f);
        random.f[2] = math_random_float_range(-1.0f, 1.0f);
        direction.quad = random.quad;
        vec_scale_to_length(&direction, &direction, 0.020000001f);
        if (*(unsigned char *)(object + 0xBC) & 0xFE) {
            color = gfx_swap_packed_color_channels(colors.color[math_random_int_below(4)],
                                *(unsigned char *)(object + 0xBC) >> 1);
            part_spawn_scaling(object + 0x10, &direction, color,
                         gfx_swap_packed_color_channels(0x4FFF, *(unsigned char *)(object + 0xBC) >> 1),
                         37, 50, 120, 1);
        } else {
            part_spawn_scaling(object + 0x10, &direction, colors.color[math_random_int_below(4)],
                         0x4FFF, 37, 50, 120, 1);
        }
    }
    *(float *)(object + 0xF0) = FastAddRotations(*(float *)(object + 0xF0), *(float *)(state + 0x10));
    *(float *)(object + 0xF4) = FastAddRotations(*(float *)(object + 0xF4), *(float *)(state + 0x14));
    FastVecAdd(object + 0x10, object + 0x10, state);
    moby_mix_on_inner_data(object, state, state, 0.00584f);
    if (*(float *)(object + 0x10) < 0.0f || *(float *)(object + 0x14) < 0.0f ||
        *(float *)(object + 0x18) < 0.0f) {
        moby_mark_spawned((NativeUpdate775View *)object);
        return;
    }
    if (*(short *)(state + 0x18) < *(short *)(state + 0x1A) / 4) {
        float amount = IntToFloat(*(short *)(state + 0x18));
        *(float *)(object + 0x2C) = *(float *)(state + 0x1C) * amount /
                                  IntToFloat(*(short *)(state + 0x1A) / 4);
    }
    if (FastDecTimer((short *)(state + 0x18)))
        moby_mark_spawned((NativeUpdate775View *)object);
}


/* func_PAL_L00_003929E0, the PAL copy of func_L00_0038F8B8: the same C, where 40, 23 and 60 become 33, 19 and 50, and the time stat takes the 50 Hz scale at each read. */
/* Partial resident view: only fields observed by the launch gate are named. */
typedef struct { char pad00[0xA8]; unsigned short launches; char padAA[2]; unsigned int bestTime, mask; } LaunchStats;
typedef struct {
    char pad00[0x33C]; char *support; int grounded; char pad344[0x434]; float heading;
    char pad77C[0xAB4]; unsigned int buttons; char pad1234[0xC]; int resource;
    char pad1244[0x2BC]; int special; char pad1504[0xD90]; int level;
    char pad2298[4]; int state; char pad22A0[0x1C]; unsigned char busy; char pad22BD[0x22F];
    short platform; char pad24EE[0x46]; int cooldown; char pad2538[8];
} TetherLaunchHero;
extern TetherLaunchHero g_hero_state;
extern LaunchStats D_0018C360;
extern int D_L00_001A8F00[] __attribute__((sda)), D_L00_001A8F08[] __attribute__((sda));
typedef struct { char pad00[0x1A4]; unsigned int buttons; } LaunchInput;
extern LaunchInput g_pad_state;
extern unsigned int D_001A7390 __attribute__((section(".sdata")));
extern unsigned int g_current_map_index[] __attribute__((sda));
extern char *g_follow_camera_object;
extern int math_fast_float_d(int *), weapon_spend_ammo(int, int);
extern float vec_length_xy(void *), mat_fast_helper_a(float, float);
extern void vec_build_spherical_offset(float *, float, float, float), FastVecAdd(void *, void *, void *);
extern void func_PAL_002A7E68(void *, int, int, int), func_PAL_L00_002F5D28(void);
extern char *func_PAL_L00_00394148(char *, char *, float, float);
extern int PlayMobySound(int, int, char *);
/* Starts the tether when the shared input and movement gates permit it. */
void func_PAL_L00_003929E0(char *actor) {
    int *state;
    int ready;
    float point[4];
    float heading, pitch;
    if (!actor) return;
    state = *(int **)(actor + 0x68);
    ready = 1;
    math_fast_float_d(state);
    if (g_hero_state.level == 29) { if (!math_fast_float_d(&g_hero_state.cooldown)) ready = 0; }
    else g_hero_state.cooldown = 33;
    if (D_L00_001A8F00[0] || D_L00_001A8F08[0] != -2 || !(g_pad_state.buttons & g_hero_state.buttons) || state[0] || state[1] || g_hero_state.busy) goto finish;
    if (g_hero_state.state == 7 || g_hero_state.state == 2 || g_hero_state.state == 3 || g_hero_state.state == 4 || g_hero_state.state == 5 || g_hero_state.state == 6 || g_hero_state.state == 16 || g_hero_state.state == 14 || g_hero_state.state == 9 || g_hero_state.state == 10 || g_hero_state.state == 11 || g_hero_state.state >= 13 || g_hero_state.level == 111 || g_hero_state.level == 98) goto finish;
    if ((g_follow_camera_object && *(short *)(g_follow_camera_object + 0x86) == 5) || !g_hero_state.grounded || g_hero_state.resource < 19) goto finish;
    if (g_hero_state.support && (*(short *)(g_hero_state.support + 0xAA) == 0x13E || *(short *)(g_hero_state.support + 0xAA) == 0x46F) && ready) goto finish;
    if (!weapon_spend_ammo(-1, 1)) goto denied;
    pitch = 0.0f;
    heading = g_hero_state.heading;
    if (g_hero_state.platform == 1 || g_hero_state.special) {
        pitch = mat_fast_helper_a(vec_length_xy(actor + 0xD0), *(float *)(actor + 0xD8));
        vec_build_spherical_offset(point, 0.6f, heading, -pitch);
        FastVecAdd(point, point, actor + 0x10);
    } else {
        vec_build_spherical_offset(point, 0.6f, heading, -pitch);
        FastVecAdd(point, point, actor + 0x10);
    }
    if (*(unsigned char *)(actor + 0x43) != 3) func_PAL_002A7E68(actor, 3, 0, 0);
    func_PAL_L00_002F5D28();
    *(char **)(state + 1) = func_PAL_L00_00394148(actor, (char *)point, heading, pitch);
    if (D_0018C360.launches < 0xFFFF) D_0018C360.launches++;
    if (D_0018C360.bestTime < (((int)(D_001A7390) * 5 + 2) / 6)) D_0018C360.bestTime = (((int)(D_001A7390) * 5 + 2) / 6);
    D_0018C360.mask |= 1U << g_current_map_index[0];
    D_0018C360.mask |= 0x80000000;
    state[0] = 50;
    goto finish;
denied:
    if (g_pad_state.buttons & g_hero_state.buttons) PlayMobySound(0, 0, actor);
finish:
    if ((*(unsigned char *)(actor + 0x60) & 2) && *(u8 *)(actor + 0x43) != 1) func_PAL_002A7E68(actor, 1, 0, 0);
    *(unsigned short *)(actor + 0x34) |= 4;
}
