#include "include_asm.h"

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
extern void moby_set_state();
extern void mat_combine_and_store(void *, void *, void *, void *);
extern float math_fabs(float);
extern int IsPointInCuboid(void *, int);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern int PlayMobySound(int, int, void *);
extern void snd_stop_voice(int);
extern void moby_mark_spawned(void *);
extern void gfx_draw_moby_edge_lines(char *, int);
extern void lift_clamp_group_riders(char *);
extern int group_is_linked_to_owner(char *), group_is_misaligned(char *);
extern int TryClaimNotice(int, int, int);
extern unsigned int g_pad_held_flags NOT_SDA;
extern Projection *g_platform_projection_table __attribute__((sda));
extern Projection *D_L14_001B268C_gp SDATA(D_L14_001B268C);
extern char g_identity_l14_matrix[] __attribute__((sda));
extern float vec_distance_xy(void *, void *);

/* Elevator platform update (USA v2.00): moves between the initial height and the projection-table height, updating
 * the collision displacement and keeping the movement sound active. */
void elevator_platform_update_us2(char *moby) {
    Vec delta, velocity;
    char *vars = *(char **)(moby + 0x68);
    float target, speed;
    int active, blocked;

    switch ((unsigned char)moby[0x20]) {
    case 0:
        if (!vars || *(int *)(vars + 0x60) == -1) {
            moby_mark_spawned(moby);
            return;
        }
        {
            float original_height = *(float *)(moby + 0x18);
            *(int *)(vars + 0x7C) = 0;
            *(float *)(vars + 0x70) = original_height;
        }
        gfx_draw_moby_edge_lines(moby, 0);
        moby_set_state(moby, 1, -1);
        break;
    case 1:
        active = 0;
        if (g_hero_state.obj == moby && g_hero_state.active) {
            lift_clamp_group_riders(moby);
            if (!*(int *)(vars + 0x6C) || group_is_linked_to_owner(moby) || group_is_misaligned(moby)) {
                TryClaimNotice(4, 0x12EC, 1);
                {
                    int flags = g_pad_held_flags & 0x10;
                    active = flags != 0;
                }
            }
        } else {
            /* Keeping the distance guard in each height case lets the
             * compiler share the floating-point branch, as retail does. */
            if (*(int *)(vars + 0x7C)) {
                if (g_hero_state.pos[2] - *(float *)(vars + 0x70) > -0.25f) {
                    if (vec_distance_xy(g_hero_state.pos, moby + 0x10) < 24.0f)
                        active = 1;
                }
            } else {
                PlayerState *player = &g_hero_state;
                if (math_fabs(player->pos[2] - g_platform_projection_table[*(int *)(vars + 0x60)].height) < 1.0f) {
                    if (vec_distance_xy(player->pos, moby + 0x10) < 24.0f)
                        active = 1;
                }
            }
        }
        if (active) {
            moby_set_state(moby, 2, -1);
            *(int *)(vars + 0x7C) = (*(int *)(vars + 0x7C) + 1) & 1;
            gfx_draw_moby_edge_lines(moby, 1);
        }
        break;
    case 2:
        if (*(int *)(vars + 0x7C))
            target = D_L14_001B268C_gp[*(int *)(vars + 0x60)].height;
        else
            target = *(float *)(vars + 0x70);
        speed = 0.00111111114f;
        blocked = 0;
        if (*(int *)(vars + 0x7C) && g_hero_state.pos[2] < *(float *)(moby + 0x18) - 1.0f &&
            IsPointInCuboid(g_hero_state.pos, *(int *)(vars + 0x60))) {
            blocked = 1;
            target += 1.5f;
            speed = 0.00222222228f;
        }
        if (!blocked && math_fabs(*(float *)(moby + 0x18) - target) <= *(float *)(vars + 0x74)) {
            *(float *)(moby + 0x18) = target;
            *(float *)(vars + 0x74) = 0.0f;
            moby_set_state(moby, 1, -1);
            gfx_draw_moby_edge_lines(moby, 0);
            {
                char *collision = vars + 0x20;
                mat_combine_and_store(collision, g_identity_l14_matrix, moby + 0xF0, moby + 0xF0);
            }
        } else {
            math_step_value_toward_target(moby + 0x18, vars + 0x74, target, 0.00055555557f, speed, 0.166666672f);
            velocity.q = 0;
            velocity.f[2] = *(float *)(vars + 0x74);
            delta.q = velocity.q;
            mat_combine_and_store(vars + 0x20, &delta, moby + 0xF0, moby + 0xF0);
        }
        break;
    }
    if (math_fabs(*(float *)(vars + 0x74)) > 0.01f) {
        unsigned char *e = (unsigned char *)g_sound_state + *(int *)(vars + 0x78) * 0x70;
        if (*(char **)(e + 0x88) != moby || !e[0x74])
            *(int *)(vars + 0x78) = PlayMobySound(0, 4, moby);
    } else {
        int n = *(int *)(vars + 0x78);
        if (n != -1) {
            unsigned char *e = (unsigned char *)g_sound_state + n * 0x70;
            if (*(char **)(e + 0x88) == moby && e[0x74])
                snd_stop_voice(n);
        }
        *(int *)(vars + 0x78) = -1;
    }
}
