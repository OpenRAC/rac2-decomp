/* func_PAL_L17_003CB770, the PAL copy of func_L17_003C7680: the same C, where each time X * 60 becomes (X * 300 + 2) / 6. */
#include "common.h"

typedef int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } Vec;

#define I(p, o) (*(int *)((char *)(p) + (o)))
#define F(p, o) (*(float *)((char *)(p) + (o)))
#define P(p, o) (*(char **)((char *)(p) + (o)))
#define U(p, o) (*(u8 *)((char *)(p) + (o)))

/* The platform's per-object variables (object + 0x68). */
typedef struct {
    char pad0[0x50];
    Vec bounds;   /* 0x50 */
    char pad60[0x30];
    int target;   /* 0x90: the byte at trigger + 0x20 that starts a controller */
    char pad94[8];
    float timer;  /* 0x9C: travel time in frames */
    int trigger1; /* 0xA0: 0x100-byte record index, -1 for none */
    int path1;    /* 0xA4: path index, -1 for none */
    int padA8;
    int state1;   /* 0xAC */
    int trigger2; /* 0xB0 */
    int path2;    /* 0xB4 */
    int padB8;
    int state2;   /* 0xBC */
    int gate;     /* 0xC0: record that must be in state 3, -1 for none */
    float speed;  /* 0xC4: fall speed */
    float wait;   /* 0xC8: hold time in frames */
    int player;   /* 0xCC */
} PlatformVars;

extern int g_flash_frame_counter;
extern char *g_path_l17_table[];
extern char *g_moby_l17_pool;
extern char g_hero_position[];
extern float g_platform_move_seconds_a __attribute__((sda));
extern float g_platform_move_seconds_b __attribute__((sda));
extern float g_platform_wait_seconds __attribute__((sda));
extern float g_platform_speed_step __attribute__((sda));
extern float g_platform_height NOT_SDA;
extern float math_fast_sin_or_cos_b(float);
extern u32 FastTweenColor(u32, u32, float);
extern void func_PAL_L17_003CB570(void *, void *, void *, float);
extern int IsPointInCuboid(void *, int);
extern int snd_play_from_class_bank(int, int, void *, int);
extern int PlayMobySound(int, int, void *);
extern int CollLine(void *, void *, int, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);

/* Pulses the colour, then runs the two controllers: timed travel along each path, and for the
 * second one a hold, a fall and a landing. */
void func_PAL_L17_003CB770(char *object)
{
    Vec old, delta, lower, upper;
    PlatformVars *state = (PlatformVars *)P(object, 0x68);
    float angle = (float)(g_flash_frame_counter % 150) * 0.006666667f * 2.0f * 3.1415927f;

    if (angle > 3.1415927f)
        angle -= 6.2831855f;
    I(object, 0x78) = FastTweenColor(0x80464646, 0x80828282, (math_fast_sin_or_cos_b(angle) + 1.0f) * 0.5f);
    old.q = *(Q *)(object + 16);
    if (U(object, 0x20) == 0) {
        U(object, 0x20) = 1;
        if (state->path1 != -1)
            *(Q *)(object + 16) = *(Q *)(g_path_l17_table[state->path1] + 16);
        else if (state->path2 != -1)
            *(Q *)(object + 16) = *(Q *)(g_path_l17_table[state->path2] + 16);
    }
    if (state->trigger1 != -1 && state->path1 != -1) {
        char *trigger = g_moby_l17_pool + state->trigger1 * 256;
        char *path = g_path_l17_table[state->path1];

        switch (state->state1) {
        case 0:
            if (!trigger || U(trigger, 0x20) == 254 || U(trigger, 0x20) == 253 ||
                U(trigger, 0x20) == state->target) {
                state->timer = 0;
                state->state1 = 1;
            }
            break;
        case 1:
            state->timer += 1.0f;
            if (state->timer >= (g_platform_move_seconds_a * 300.0f + 2.0f) * 0.16666667f)
                state->timer = (g_platform_move_seconds_a * 300.0f + 2.0f) * 0.16666667f;
            func_PAL_L17_003CB570(object, path, &old, g_platform_move_seconds_a);
            if (state->timer >= (g_platform_move_seconds_a * 300.0f + 2.0f) * 0.16666667f) {
                state->wait = 0;
                state->state1 = 2;
            }
            break;
        case 2:
            if (state->state2)
                break;
            state->wait += 1.0f;
            if (state->wait >= (g_platform_wait_seconds * 300.0f + 2.0f) * 0.16666667f) {
                state->state1 = 3;
                U(trigger, 0xbc) = 0;
                state->timer = (g_platform_move_seconds_a * 300.0f + 2.0f) * 0.16666667f;
            }
            break;
        case 3:
            state->timer -= 1.0f;
            if (state->timer <= 0.0f)
                state->timer = 0;
            func_PAL_L17_003CB570(object, path, &old, g_platform_move_seconds_a);
            if (state->timer <= 0.0f)
                state->state1 = 0;
            break;
        }
    }
    if (state->trigger2 != -1 && state->path2 != -1) {
        char *path = g_path_l17_table[state->path2];
        char *trigger = g_moby_l17_pool + state->trigger2 * 256;
        int allow;
        float height;

        switch (state->state2) {
        case 0:
            allow = 0;
            if (state->trigger1 == -1 || state->state1 == 2)
                allow = 1;
            if (allow) {
                int index = state->gate;

                if (index != -1 && U(g_moby_l17_pool + index * 256, 0x20) != 3)
                    allow = 0;
                if (allow && (!trigger || U(trigger, 0x20) == 254 || U(trigger, 0x20) == 253 ||
                              U(trigger, 0x20) == state->target)) {
                    state->timer = 0;
                    state->state2 = 1;
                }
            }
            break;
        case 1:
            state->timer += 1.0f;
            if (state->timer >= (g_platform_move_seconds_b * 300.0f + 2.0f) * 0.16666667f)
                state->timer = (g_platform_move_seconds_b * 300.0f + 2.0f) * 0.16666667f;
            func_PAL_L17_003CB570(object, path, &old, g_platform_move_seconds_b);
            if (state->timer >= (g_platform_move_seconds_b * 300.0f + 2.0f) * 0.16666667f) {
                state->wait = 0;
                state->state2 = 2;
            }
            break;
        case 2:
            state->wait += 1.0f;
            if (state->wait >= (g_platform_wait_seconds * 300.0f + 2.0f) * 0.16666667f) {
                if (!IsPointInCuboid(g_hero_position, state->player)) {
                    state->state2 = 3;
                    snd_play_from_class_bank(1, 0, object, 0x93b);
                    U(trigger, 0xbc) = 0;
                    state->speed = 0;
                } else {
                    state->speed -= 1.0f;
                }
            }
            break;
        case 3:
            qcopy(&lower, object + 16);
            lower.f[2] -= 20.01f;
            qcopy(&upper, object + 16);
            upper.f[2] += 0.5f;
            if (CollLine(&upper, &lower, 2, object, 0))
                height = g_platform_height;
            else
                height = 0.0f;
            if (height < F(object, 0x18)) {
                state->speed += g_platform_speed_step * 0.00040000002f;
                F(object, 0x18) -= state->speed;
            } else {
                state->speed = 0;
                F(object, 0x18) = height;
                state->state2 = 0;
                PlayMobySound(0, 0, object);
            }
            break;
        }
    }
    FastVecSub(&delta, object + 16, &old);
    mat_combine_and_store(&state->bounds, &delta, object + 0xf0, object + 0xf0);
}
