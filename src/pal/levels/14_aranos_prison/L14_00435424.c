#include "include_asm.h"


#include "common.h"
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecAdd(void *, void *, void *);
extern char g_hero_position[];
extern char g_identity_l14_matrix[] __attribute__((sda));
extern char *D_L14_001B259C_gp SDATA(D_L14_001B259C);
extern char *D_L14_001B259C_direct __asm__("D_L14_001B259C") __attribute__((sda));
extern int moby_count_group_not_in_state(int, int);
extern float vec_distance_xy(void *, void *);
extern int flag_is_third_pending_set(void *);
extern int IsPointInCuboid(void *, int);
extern void anim_start_blended_pal(void *, int, int, int);
extern int coll_test_point(void *, float, int, void *);
extern void SpawnExplosionEffects_pal(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void moby_mark_spawned(void *);
extern int prisonStartSound(int, int, void *) __asm__("func_002E5CF8");
extern u8 g_moby_group_flags[];
extern unsigned char *g_moby_l14_pool __attribute__((sda));
extern u8 g_moby_group_flags[];
extern char g_hero_position[];
extern u8 g_hero_state[];
extern u8 g_lift_scene_flag;
extern int IsPointInCuboid(void *, int);
extern void moby_mark_spawned(void *);
extern float math_fast_sin_or_cos_b(float);
extern unsigned char *g_group_entity_lists[];
typedef struct {
    int linked[4];
    int f10;
    int f14;
    int f18;
    int group;
} PrisonGateState;
typedef struct {
    char pad00[0x10];
    float pos[4];
    u8 mode;
    char pad21[3];
    int *next;
    char pad28[0xC];
    u16 flags;
    char pad36[0xD];
    u8 anim;
    char pad44[0x1C];
    u8 anim_flags;
    char pad61[7];
    PrisonGateState *state;
    char pad6C[0xC];
    int f78;
    char pad7C[0x19];
    u8 f95;
    char pad96[2];
    int f98;
    char pad9C[0x5C];
    float angle;
    char padFC[4];
} PrisonEntity;

/* Gate logic: opens when the player nears, is hit open by linked objects, and
   hands off to the next object when it slides clear. */
void prison_gate_update_pal(PrisonEntity *self)
{
    float temp[4] __attribute__((aligned(16)));
    float front[4] __attribute__((aligned(16)));
    float left[4] __attribute__((aligned(16)));
    float right[4] __attribute__((aligned(16)));
    /* Passed unwritten to the left/right additions below, as retail does; the matching code needs that. */
    float left_offset[4] __attribute__((aligned(16)));
    float right_offset[4] __attribute__((aligned(16)));
    PrisonGateState *state = self->state;
    int i;
    int list_entry;
    int group;
    PrisonEntity *other;
    char *base;

    if (self->mode == 0) {
        /* Mark the group's members busy. */
        if (g_group_entity_lists[group = state->group] && moby_count_group_not_in_state(group, -1) >= 2) {
            unsigned short *list;

            list = (unsigned short *)g_group_entity_lists[state->group];
            base = D_L14_001B259C_direct;
            do {
                list_entry = *list;
                other = (PrisonEntity *)(base + ((list_entry & 0x7FFF) << 8));
                other->flags |= 0x43;
            } while ((group = (short)*list++) >= 0);
        }

        if (vec_distance_xy(&self->pos, g_hero_position) < 6.0f && flag_is_third_pending_set(self) &&
            !IsPointInCuboid(g_hero_position, state->f14) &&
            !IsPointInCuboid(g_hero_position, state->f18)) {
            self->mode = 1;
            self->f78 = 0x24C102;
            if (self->anim != 1)
                anim_start_blended_pal(self, 1, 0, 0);
            self->f98 = 0;

            /* Release the group's members. */
            if (g_group_entity_lists[group = state->group] && moby_count_group_not_in_state(group, -1) >= 2) {
                unsigned short *list;

                list = (unsigned short *)g_group_entity_lists[state->group];
                base = D_L14_001B259C_direct;
                do {
                    list_entry = *list;
                    other = (PrisonEntity *)(base + ((list_entry & 0x7FFF) << 8));
                    other->flags &= 0xFFBC;
                } while ((group = (short)*list++) >= 0);
            }
        } else if (IsPointInCuboid(g_hero_position, state->f14)) {
            self->mode = 5;
        }

        for (i = 0; i < 4; i++) {
            int id = state->linked[i];

            if (id != -1) {
                other = (PrisonEntity *)(D_L14_001B259C_gp + (id << 8));
                if (other->f95 || (s8)other->mode < 0) {
                    if (state->f10) {
                        self->mode = 2;
                        qcopy(temp, self->pos);
                        temp[2] += 1.0f;
                        prisonStartSound(2, 0, self);
                        SpawnExplosionEffects_pal(self, g_identity_l14_matrix, temp, 0.0f, 0.0f, 10, 3, 16,
                            4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f, 0, 9, -1, 0, 0x810001);
                        return;
                    }
                    self->mode = 1;
                    if (self->anim != 1)
                        anim_start_blended_pal(self, 1, 0, 0);
                    self->f98 = 0;
                }
            }
        }
    }

    if (self->mode == 1 && (self->anim_flags & 2)) {
        self->mode = 3;
        self->f78 = 0x224C1;
        if (self->anim != 2)
            anim_start_blended_pal(self, 2, 0, 0);
    }

    if (self->mode == 2) {
        temp[0] = math_fast_sin_or_cos_a(self->angle - 1.57079649f) * 0.36f;
        temp[1] = math_fast_sin_or_cos_b(self->angle - 1.57079649f) * 0.36f;
        temp[2] = 0;
        FastVecAdd(self->pos, self->pos, temp);
        qcopy(front, self->pos);
        qcopy(left, self->pos);
        qcopy(right, self->pos);
        front[2] += 0.75f;
        left[2] += 0.75f;
        right[2] += 0.75f;
        temp[0] = math_fast_sin_or_cos_a(self->angle) * 0.8f;
        temp[1] = math_fast_sin_or_cos_b(self->angle) * 0.8f;
        temp[2] = 0;
        temp[0] = math_fast_sin_or_cos_a(self->angle + 3.14159298f) * 0.8f;
        temp[1] = math_fast_sin_or_cos_b(self->angle + 3.14159298f) * 0.8f;
        temp[2] = 0;
        FastVecAdd(left, left, left_offset);
        FastVecAdd(right, right, right_offset);
        if (coll_test_point(front, 0.6f, 0, self) || coll_test_point(left, 0.68f, 0, self) || coll_test_point(right, 0.68f, 0, self)) {
            prisonStartSound(2, 0, self);
            SpawnExplosionEffects_pal(self, g_identity_l14_matrix, front, 0.0f, 0.0f, 10, 3, 16,
                4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f, 0, 9, -1, 0, 0x810001);
            moby_mark_spawned(self);
            return;
        }
    }

    if (self->mode == 3 && IsPointInCuboid(g_hero_position, state->f14)) {
        self->mode = 4;
        if (self->anim != 3)
            anim_start_blended_pal(self, 3, 0, 0);
    }

    if (self->mode == 4 && (self->anim_flags & 2)) {
        self->mode = 5;
        self->f98 = self->next[4];
        if (self->anim)
            anim_start_blended_pal(self, 0, 0, 0);
    }
}
