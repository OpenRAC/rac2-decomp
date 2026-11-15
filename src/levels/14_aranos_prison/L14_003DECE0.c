#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct {
    char pad[0x80];
    float pos[4];
    char gap[0x2AC];
    char *obj;
    int active;
    char gap2[0x1F70];
    unsigned char mode;
} PlayerState;
typedef struct { char pad[0x38]; float height; char tail[0x44]; } Projection;

extern PlayerState g_hero_state;
extern char g_sound_state[];
extern void func_321F58();
extern void func_328DA8(void *, void *, void *, void *);
extern float math_fabs(float);
extern int IsPointInCuboid(void *, int);
extern void math_step_value_toward_target(void *, void *, float, float, float, float);
extern int PlayMobySound(int, int, void *);
extern void snd_stop_voice(int);
extern void moby_mark_spawned(void *);
extern void gfx_draw_moby_edge_lines(char *, int);
extern void lift_clamp_group_riders(char *);
extern int group_is_linked_to_owner(char *), group_is_misaligned(char *);
extern void TryClaimNotice(int, int, int);
extern unsigned int D_00138324 NOT_SDA;
/* Retail reads the same projection-table pointer absolutely in state 1 and
 * through $gp in state 2. Both declarations bind the same storage. */
extern Projection *D_L14_001B268C __attribute__((sda));
extern Projection *D_L14_001B268C_gp SDATA(D_L14_001B268C);
extern char D_L14_001A8F20[] __attribute__((sda));
extern float vec_distance_xy(void *, void *);

/* Move between the initial height and the projection-table height, updating
 * the collision displacement and keeping the movement sound active. */
/* Updates moby classes 2792 and 2793: a platform that rises and lowers between two heights when the player calls it, and carries the player. */
void elevator_platform_update(char *self) {
    Vec moveDelta, velocity;
    char *vars = *(char **)(self + 0x68);
    float target, speed;
    int active, blocked;

    switch ((unsigned char)self[0x20]) {
    case 0:
        if (!vars || *(int *)(vars + 0x60) == -1) {
            moby_mark_spawned(self);
            return;
        }
        {
            float originalHeight = *(float *)(self + 0x18);
            *(int *)(vars + 0x7C) = 0;
            *(float *)(vars + 0x70) = originalHeight;
        }
        gfx_draw_moby_edge_lines(self, 0);
        func_321F58(self, 1, -1);
        break;
    case 1:
        active = 0;
        if (g_hero_state.obj == self && g_hero_state.active) {
            lift_clamp_group_riders(self);
            if (!*(int *)(vars + 0x6C) || group_is_linked_to_owner(self) || group_is_misaligned(self)) {
                TryClaimNotice(4, 0x279A, 1);
                {
                    int flags = D_00138324 & 0x10;
                    active = flags != 0;
                }
            }
        } else {
            /* Keeping the distance guard in each height case lets the
             * compiler share the floating-point branch, as retail does. */
            if (*(int *)(vars + 0x7C)) {
                if (g_hero_state.pos[2] - *(float *)(vars + 0x70) > -0.25f) {
                    if (vec_distance_xy(g_hero_state.pos, self + 0x10) < 24.0f)
                        active = 1;
                }
            } else {
                PlayerState *player = &g_hero_state;
                if (math_fabs(player->pos[2] - D_L14_001B268C[*(int *)(vars + 0x60)].height) < 1.0f) {
                    if (vec_distance_xy(player->pos, self + 0x10) < 24.0f)
                        active = 1;
                }
            }
        }
        if (active) {
            func_321F58(self, 2, -1);
            *(int *)(vars + 0x7C) = (*(int *)(vars + 0x7C) + 1) & 1;
            gfx_draw_moby_edge_lines(self, 1);
        }
        break;
    case 2:
        if (*(int *)(vars + 0x7C))
            target = D_L14_001B268C_gp[*(int *)(vars + 0x60)].height;
        else
            target = *(float *)(vars + 0x70);
        speed = 0.00111111114f;
        blocked = 0;
        if (*(int *)(vars + 0x7C) && g_hero_state.pos[2] < *(float *)(self + 0x18) - 1.0f &&
            IsPointInCuboid(g_hero_state.pos, *(int *)(vars + 0x60))) {
            blocked = 1;
            target += 1.5f;
            speed = 0.00222222228f;
        }
        if (!blocked && math_fabs(*(float *)(self + 0x18) - target) <= *(float *)(vars + 0x74)) {
            *(float *)(self + 0x18) = target;
            *(float *)(vars + 0x74) = 0.0f;
            func_321F58(self, 1, -1);
            gfx_draw_moby_edge_lines(self, 0);
            {
                char *collision = vars + 0x20;
                func_328DA8(collision, D_L14_001A8F20, self + 0xF0, self + 0xF0);
            }
        } else {
            math_step_value_toward_target(self + 0x18, vars + 0x74, target, 0.00055555557f, speed, 0.166666672f);
            velocity.q = 0;
            velocity.f[2] = *(float *)(vars + 0x74);
            moveDelta.q = velocity.q;
            func_328DA8(vars + 0x20, &moveDelta, self + 0xF0, self + 0xF0);
        }
        break;
    }
    if (math_fabs(*(float *)(vars + 0x74)) > 0.01f) {
        unsigned char *soundEntry = (unsigned char *)g_sound_state + *(int *)(vars + 0x78) * 0x70;
        if (*(char **)(soundEntry + 0x88) != self || !soundEntry[0x74])
            *(int *)(vars + 0x78) = PlayMobySound(0, 4, self);
    } else {
        int soundSlot = *(int *)(vars + 0x78);
        if (soundSlot != -1) {
            unsigned char *soundEntry = (unsigned char *)g_sound_state + soundSlot * 0x70;
            if (*(char **)(soundEntry + 0x88) == self && soundEntry[0x74])
                snd_stop_voice(soundSlot);
        }
        *(int *)(vars + 0x78) = -1;
    }
}
