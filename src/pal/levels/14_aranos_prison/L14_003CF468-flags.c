#include "include_asm.h"

#include "common.h"
extern void matrix_from_basis_rows(void *dst, void *src);
extern void FastVecSub(void *dst, void *a, void *b);
extern void vec_transform_by_object_or_given(char *a, char *b, char *c, char *d);
extern float math_fabs(float a);
extern void transform_vector(void *dst, void *a, void *b);
extern float math_random_float_range(float a, float b);
extern float square_root(float a);
extern void FastVecScale(void *dst, void *src, float s);
extern void entity_start_launch_to_target(char *e, void *v, float a, float b, float c);
extern s32 hero_l00_set_action_pal(int a0, int a1);
extern unsigned short *g_group_entity_lists[];
extern unsigned char *g_moby_l14_pool MACRO_ADDR;
extern int g_group_link_limit __attribute__((sda));
struct Projection { char pad[0x38]; float height; char tail[0x44]; };
extern struct Projection *g_platform_projection_table MACRO_ADDR;
extern char g_hero_state[];
struct OwnerPrefix { char reserved00[0x60]; int tableIndex, groupIndex; };

/* Launch volume of a platform: throws every entity of its group that stands inside the box to the platform height, and does the same for the hero. */
void UpdateLaunchVolume_pal(char *self) {
    float mtx[16] __attribute__((aligned(16)));
    float off[4] __attribute__((aligned(16)));
    float tmp[4] __attribute__((aligned(16)));
    float vec[4] __attribute__((aligned(16)));
    struct OwnerPrefix *state = *(struct OwnerPrefix **)(self + 0x68);
    unsigned short *list;
    unsigned char *rider;
    char *hero;
    char *hero2;
    int inside;
    float target_height;
    float rise;
    float fall;
    float duration;

    matrix_from_basis_rows(mtx, self + 0xC0);
    for (list = g_group_entity_lists[state->groupIndex];
         (state->groupIndex & 0xFF) != 0xFF && state->groupIndex <= g_group_link_limit &&
         list != 0 && ((list != 0 && (short)list[-1] >= 0) || list == g_group_entity_lists[state->groupIndex]);
         list++) {
        rider = ((*list & 0x7FFF) << 8) + g_moby_l14_pool;
        if (rider == 0)
            break;
        if (rider[0x20] != 0xFE) {
            if (rider[0x20] != 0xFD) {
                FastVecSub(off, rider + 0x10, self + 0x10);
                vec_transform_by_object_or_given(self, (char *)off, (char *)off, (char *)mtx);
                off[3] = 1.0f;
                off[0] = off[0] + 2.0f;
                inside = math_fabs(off[0]) < 1.0f && math_fabs(off[1]) < 1.0f;
                if (inside) {
                    transform_vector(tmp, off, &g_platform_projection_table[state->tableIndex]);
                    entity_start_launch_to_target((char *)rider, tmp,
                                      g_platform_projection_table[state->tableIndex].height +
                                          math_random_float_range(1.0f, 2.0f),
                                      0.008f, 0.008f);
                }
            }
        }
    }
    hero = g_hero_state;
    if ((*(char **)(hero + 0x33C) == self && *(int *)(hero + 0x340) != 0) ||
        *(float *)(hero + 0x31C) < 0.5f) {
        FastVecSub(off, g_hero_state + 0x80, self + 0x10);
        vec_transform_by_object_or_given(self, (char *)off, (char *)off, (char *)mtx);
        off[3] = 1.0f;
        off[0] = off[0] + 2.0f;
        inside = math_fabs(off[0]) < 1.0f && math_fabs(off[1]) < 1.0f;
        if (inside) {
            transform_vector(tmp, off, &g_platform_projection_table[state->tableIndex]);
            hero2 = g_hero_state;
            target_height = g_platform_projection_table[state->tableIndex].height + 1.5f;
            rise = target_height - *(float *)(hero2 + 0x88);
            rise *= 2.0f; duration = square_root(rise / 0.008f);
            fall = (target_height - tmp[2]) * 2.0f; duration += square_root(fall / 0.008f);
            FastVecSub(vec, tmp, hero2 + 0x80); FastVecScale(vec, vec, 1.0f / duration);
            vec[2] = square_root(rise * 0.008f);
            hero_l00_set_action_pal(0x44, 1);
            qcopy(hero2 + 0xF0, vec);
        }
    }
}
