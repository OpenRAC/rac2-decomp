#include "include_asm.h"

#include "common.h"
extern char *g_moby_l14_pool __attribute__((sda));
extern char g_hero_position[];
extern unsigned char g_sound_state[];
extern void moby_set_state(void *, int, int);
extern void FastVecSub(void *dst, void *a, void *b);
extern float FastVecLength(void *);
extern void FastVecCross(void *dst, void *a, void *b);
extern int moby_count_used_child_slots(char *);
extern int flag_set_first_pending(void *);
extern int IsPointInCuboid(void *, int);
extern void moby_wake_children(char *);
extern int math_fast_float_d(int *);
extern int hero_is_current_selected_id(void *);
extern float fast_vec_dist(void *, void *);
extern int PlayMobySound(int, int, void *);
extern void snd_stop_voice(int);
extern void moby_place_from_group_matrices(char *, float);
extern void moby_clear_dead_linked(char *);
extern void mat_combine_and_store(void *, void *, void *, void *);

/* A two-position mover. State 0 stores its two end points (which one is the current
   position depends on word 0x70) and each linked entity's distance to them; state 1 waits on
   func_002ACBC8; states 3 and 4 re-arm the timer at 0x8C and, once func_L00_00324120 says so
   or the player has moved to the other side of the object, start the turn (states 5 and 6),
   which steps func_L14_003DE360 until the angle at 0x80 reaches 0 or pi/2 and then stops the
   object's sound. */
void swinging_mover_update_pal(char *self)
{
    float pos[4] __attribute__((aligned(16)));
    float rot[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    float d1[4] __attribute__((aligned(16)));
    float d2[4] __attribute__((aligned(16)));
    char *vars = *(char **)(self + 0x68);
    char **ent;
    float *dist;
    int i;
    float length;
    int side;
    unsigned char *sound;

    qcopy(pos, self + 0x10);
    qcopy(rot, self + 0xF0);

    switch ((unsigned char)self[0x20]) {
    case 0:
        *(unsigned short *)(self + 0x34) |= 0x100;
        *(float *)(vars + 0x7C) = 0.0087266471f;
        *(int *)(vars + 0x78) = -1;
        *(int *)(vars + 0x5C) |= 1;
        if (*(int *)(vars + 0x70) != 0) {
            qcopy(vars + 0x90, self + 0x10);
            qcopy(vars + 0xA0, vars + 0x60);
            *(float *)(vars + 0x80) = 1.5707964f;
            moby_set_state(self, 4, -1);
        } else {
            qcopy(vars + 0xA0, self + 0x10);
            qcopy(vars + 0x90, vars + 0x60);
            *(float *)(vars + 0x80) = 0.0f;
            moby_set_state(self, 3, -1);
        }
        qcopy(vars + 0xB0, vars + 0xA0);
        *(float *)(vars + 0xB8) = *(float *)(vars + 0x98);
        FastVecSub(d1, vars + 0xA0, vars + 0xB0);
        *(float *)(vars + 0x84) = FastVecLength(d1);
        FastVecSub(d2, vars + 0x90, vars + 0xB0);
        *(float *)(vars + 0x88) = FastVecLength(d2);
        FastVecCross(vars + 0xC0, d2, d1);
        ent = (char **)(vars + 0xE0);
        dist = (float *)(vars + 0xF0);
        /* The four linked-entity ids are the words at st+0xD0, just before the distances at
           st+0xF0, so each one is read eight words back from its distance. */
        for (i = 3; i >= 0; i--) {
            if (*(int *)(dist - 8) > 0) {
                *ent = g_moby_l14_pool + (*(int *)(dist - 8) << 8);
                FastVecSub(d1, *ent + 0x10, vars + 0xB0);
                length = FastVecLength(d1);
                if ((unsigned char)self[0x20] == 4) {
                    dist[0] = length;
                    dist[4] = *(float *)(vars + 0x84) - *(float *)(vars + 0x88) + length;
                } else {
                    dist[4] = length;
                    dist[0] = *(float *)(vars + 0x88) - *(float *)(vars + 0x84) + length;
                }
            } else {
                *ent = 0;
            }
            ent++;
            dist++;
        }
        if (moby_count_used_child_slots(self) != 0 && *(int *)(vars + 0x74) >= 0) {
            moby_set_state(self, 1, -1);
        }
        break;
    case 1:
        flag_set_first_pending(self);
        if (IsPointInCuboid(g_hero_position, *(int *)(vars + 0x74)) != 0) {
            moby_set_state(self, 2, -1);
        }
        break;
    case 2:
        moby_set_state(self, 3, -1);
    case 3:
    case 4:
        if (flag_set_first_pending(self) != 0) {
            moby_wake_children(self);
            *(int *)(vars + 0x8C) = 83;
        }
        math_fast_float_d((int *)(vars + 0x8C));
        if (hero_is_current_selected_id(self) == 0) {
            if (!(fast_vec_dist(g_hero_position, self + 0x10) < 30.0f)) {
                break;
            }
            /* Which end the player is nearer; the object's own nearer end must differ. */
            side = fast_vec_dist(g_hero_position, vars + 0x90) > fast_vec_dist(g_hero_position, vars + 0xA0);
            if ((side ^ (fast_vec_dist(self + 0x10, vars + 0x90) > fast_vec_dist(self + 0x10, vars + 0xA0))) == 0) {
                break;
            }
        }
        if (moby_count_used_child_slots(self) == 0 && *(int *)(vars + 0x8C) <= 0) {
            if ((unsigned char)self[0x20] == 4) {
                moby_set_state(self, 5, -1);
            } else {
                moby_set_state(self, 6, -1);
            }
        }
        break;
    case 5:
        if (flag_set_first_pending(self) != 0) {
            *(int *)(vars + 0x78) = PlayMobySound(0, 4, self);
        }
        if (*(float *)(vars + 0x80) > 0.0f) {
            moby_place_from_group_matrices(self, -*(float *)(vars + 0x7C));
        } else {
            if (*(int *)(vars + 0x78) >= 0) {
                if (*(int *)(vars + 0x78) != -1) {
                    sound = g_sound_state + *(int *)(vars + 0x78) * 0x70;
                    if (*(char **)(sound + 0x88) == self && sound[0x74]) {
                        snd_stop_voice(*(int *)(vars + 0x78));
                    }
                }
                *(int *)(vars + 0x78) = -1;
            }
            if (hero_is_current_selected_id(self) == 0) {
                moby_set_state(self, 3, -1);
            }
        }
        break;
    case 6:
        if (flag_set_first_pending(self) != 0) {
            *(int *)(vars + 0x78) = PlayMobySound(0, 4, self);
        }
        if (*(float *)(vars + 0x80) < 1.5707964f) {
            moby_place_from_group_matrices(self, *(float *)(vars + 0x7C));
        } else {
            if (*(int *)(vars + 0x78) >= 0) {
                if (*(int *)(vars + 0x78) != -1) {
                    sound = g_sound_state + *(int *)(vars + 0x78) * 0x70;
                    if (*(char **)(sound + 0x88) == self && sound[0x74]) {
                        snd_stop_voice(*(int *)(vars + 0x78));
                    }
                }
                *(int *)(vars + 0x78) = -1;
            }
            if (hero_is_current_selected_id(self) == 0) {
                moby_set_state(self, 4, -1);
            }
        }
        break;
    }
    moby_clear_dead_linked(self);
    FastVecSub(delta, self + 0x10, pos);
    mat_combine_and_store(vars + 0x20, delta, rot, self + 0xF0);
}
