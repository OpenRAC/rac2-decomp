#include "common.h"

typedef float Vec[4] __attribute__((aligned(16)));
typedef struct { char pad[0x80]; Vec position; } PlayerView;
typedef struct {
    char pad0[0x20];
    char body[0x3C];
    int flags;
    Vec home;
    char pad70[0x10];
    int down;
    int timer;
    int sound;
    float travel;
    int startDown;
    float upperZ;
    float lowerZ;
    int active;
    float speed;
    int contact;
} Lift;
extern PlayerView g_hero_state;
typedef struct { char pad[0x74]; unsigned char active; char pad75[0x13]; void *owner; char pad8c[0x70-0x8c+0x70]; } SoundSlot;
extern struct { char pad[0x70]; } g_sound_state[];
extern unsigned char g_moby_group_flags[], g_moby_nibble_table[];
extern int g_current_map_index __attribute__((sda));
typedef struct { char pad[0x464]; unsigned char locked[1]; } Entry;
extern Entry g_level_save_state_backup;
extern int hero_is_current_selected_id(void *);
extern float math_fabs(float);
extern void FastVecSub(void *, void *, void *);
extern float fast_vec_dist(void *, void *);
extern void moby_set_state(void *, int, int);
extern float math_step_value_toward_target(float *, float *, float, float, float, float);
extern int IsPointInCuboid(void *, int);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern s32 flag_set_first_pending(void *);
extern int snd_is_voice_playing_for_owner(void *, int);
extern void snd_stop_voice(int);
extern int PlayMobySound(int, int, void *);

#define Z(o) (*(float *)((o) + 0x18))
#define W(o) (*(unsigned short *)((o) + 0xB2))
#define SLOT(id) ((SoundSlot *)&D_00188660[id])

/* Updates a lift platform: waits for the player, then rides up or down between two heights with sound. */
void lift_platform_update(unsigned char *obj)
{
    Vec old, oldRot, delta;
    Lift *lift = *(Lift **)(obj + 0x68);
    int id;
    unsigned char *p;
    int w;
    int v, v2;
    unsigned char *q;
    int w2;
    unsigned int u;

    qcopy(old, obj + 0x10);
    qcopy(oldRot, obj + 0xF0);
    switch (obj[0x20]) {
    case 0:
        lift->active = 0;
        lift->flags |= 1;
        qcopy(lift->home, obj + 0x10);
        obj[0x20] = 1;
        if (lift->startDown == 0) {
            lift->upperZ = lift->home[2];
            lift->lowerZ = lift->travel;
            lift->down = 0;
        } else {
            lift->down = 1;
            lift->upperZ = lift->travel;
            lift->lowerZ = lift->home[2];
        }
        lift->timer = 0;
        lift->sound = -1;
        break;
    case 1:
        if (hero_is_current_selected_id(obj)) {
            lift->active = 1;
            w = W(obj);
            if (w & 1) {
                p = &g_moby_nibble_table[((short)w >> 1) + (g_current_map_index << 10)];
                u = *p;
                if (((u >> 4) & 7) != 7) {
                    *p = u + 0x10;
                }
            } else {
                p = &g_moby_nibble_table[((short)w >> 1) + (g_current_map_index << 10)];
                u = *p;
                if ((u & 7) != 7) {
                    *p = u + 1;
                }
            }
            if (lift->down == 0) {
                moby_set_state(obj, 3, -1);
                if (!snd_is_voice_playing_for_owner(obj, lift->sound)) {
                    lift->sound = PlayMobySound(0, 4, obj);
                }
            } else {
                moby_set_state(obj, 2, -1);
                if (!snd_is_voice_playing_for_owner(obj, lift->sound)) {
                    lift->sound = PlayMobySound(0, 4, obj);
                }
            }
        }
        if (math_fabs(Z(obj) - g_hero_state.position[2]) > 3.0f && lift->down == 0 && Z(obj) > g_hero_state.position[2]) {
            if (lift->active != 1 && !(g_moby_group_flags[obj[0xB0] + (g_current_map_index << 4)] & 0x80)) {
                w2 = W(obj);
                if (g_level_save_state_backup.locked[(short)w2] == 0) {
                    v = g_moby_nibble_table[((short)w2 >> 1) + (g_current_map_index << 10)];
                    if (w2 & 1) {
                        if (((v >> 4) & 7) != 0) goto play;
                        goto second;
                    }
                    if ((v & 7) == 0) goto second;
                }
            }
play:
            if (!snd_is_voice_playing_for_owner(obj, lift->sound)) {
                lift->sound = PlayMobySound(0, 4, obj);
            }
            moby_set_state(obj, 3, -1);
            break;
        }
second:
        if (math_fabs(Z(obj) - g_hero_state.position[2]) > 3.0f && lift->down == 1 && g_hero_state.position[2] > Z(obj)) {
            if (lift->active != 1 && !(g_moby_group_flags[obj[0xB0] + (g_current_map_index << 4)] & 0x80)) {
                w2 = W(obj);
                if (g_level_save_state_backup.locked[(short)w2] == 0) {
                    v2 = g_moby_nibble_table[((short)w2 >> 1) + (g_current_map_index << 10)];
                    if (w2 & 1) {
                        if (((v2 >> 4) & 7) != 0) goto play2;
                        break;
                    }
                    if ((v2 & 7) == 0) break;
                }
            }
play2:
            if (!snd_is_voice_playing_for_owner(obj, lift->sound)) {
                lift->sound = PlayMobySound(0, 4, obj);
            }
            moby_set_state(obj, 2, -1);
        }
        break;
    case 2:
        qcopy(delta, obj + 0x10);
        delta[2] = lift->upperZ;
        if (fast_vec_dist(obj + 0x10, delta) > 0.04f) {
            math_step_value_toward_target((float *)(obj + 0x18), (float *)&lift->speed, delta[2], 0.00194444449f, 0.00166666671f, 0.100000009f);
            lift->timer++;
        } else if (!hero_is_current_selected_id(obj)) {
            id = lift->sound;
            lift->down = 0;
            if (id != -1 && SLOT(id)->owner == obj && SLOT(id)->active) {
                snd_stop_voice(id);
            }
            lift->sound = -1;
            moby_set_state(obj, 1, -1);
            qcopy(obj + 0x10, delta);
            lift->timer = 0;
        } else {
            id = lift->sound;
            if (id != -1 && SLOT(id)->owner == obj && SLOT(id)->active) {
                snd_stop_voice(id);
            }
            lift->sound = -1;
        }
        break;
    case 3:
        flag_set_first_pending(obj);
        if (lift->lowerZ < Z(obj)) {
            if (Z(obj) - g_hero_state.position[2] < 2.8f && Z(obj) > g_hero_state.position[2]) {
                if (IsPointInCuboid((char *)&g_hero_state + 0x80, lift->contact) == 0) {
                    math_step_value_toward_target((float *)(obj + 0x18), (float *)&lift->speed, lift->lowerZ, 0.00194444449f, 0.00166666671f, 0.100000009f);
                    lift->timer++;
                }
            } else {
                math_step_value_toward_target((float *)(obj + 0x18), (float *)&lift->speed, lift->lowerZ, 0.00194444449f, 0.00166666671f, 0.100000009f);
                lift->timer++;
            }
        } else if (!hero_is_current_selected_id(obj) && Z(obj) <= lift->lowerZ) {
            id = lift->sound;
            lift->down = 1;
            if (id != -1 && SLOT(id)->owner == obj && SLOT(id)->active) {
                snd_stop_voice(id);
            }
            lift->sound = -1;
            moby_set_state(obj, 1, -1);
            lift->timer = 0;
        } else {
            id = lift->sound;
            if (id != -1 && SLOT(id)->owner == obj && SLOT(id)->active) {
                snd_stop_voice(id);
            }
            lift->sound = -1;
        }
        break;
    }
    FastVecSub(delta, obj + 0x10, old);
    mat_combine_and_store(lift->body, delta, oldRot, obj + 0xF0);
}
