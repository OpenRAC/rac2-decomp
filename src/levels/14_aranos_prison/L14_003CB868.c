#include "names.h"
/* Project group members and the player through a launch volume.
 * The flight-time stages share source lines to preserve the measured -g division padding.
 */
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
extern s32 hero_l00_set_action(int a0, int a1);
extern unsigned short *g_group_entity_lists[];
extern unsigned char *g_moby_l14_pool MACRO_ADDR;
extern int g_group_link_limit __attribute__((sda));
struct Projection { char pad[0x38]; float height; char tail[0x44]; };
extern struct Projection *g_platform_projection_table MACRO_ADDR;
extern char g_hero_state[];

/* Only the observed table/group fields are described. */
struct OwnerPrefix { char reserved00[0x60]; int tableIndex, groupIndex; };

/* Pushes group members and the player up through the launch volume when they step into it. */
void UpdateLaunchVolume(char *self) {
    float mtx[16] __attribute__((aligned(16)));
    float local_offset[4] __attribute__((aligned(16)));
    float projected[4] __attribute__((aligned(16)));
    float launch_velocity[4] __attribute__((aligned(16)));
    struct OwnerPrefix *state = *(struct OwnerPrefix **)(self + 0x68);
    unsigned short *list_entry;
    unsigned char *member;
    char *hero_base;
    char *hero_now;
    int inside;
    float top_height;
    float rise_height;
    float fall_height;
    float duration;

    matrix_from_basis_rows(mtx, self + 0xC0);
    for (list_entry = g_group_entity_lists[state->groupIndex];
         (state->groupIndex & 0xFF) != 0xFF && state->groupIndex <= g_group_link_limit &&
         list_entry != 0 && ((list_entry != 0 && (short)list_entry[-1] >= 0) || list_entry == g_group_entity_lists[state->groupIndex]);
         list_entry++) {
        member = ((*list_entry & 0x7FFF) << 8) + g_moby_l14_pool;
        if (member == 0)
            break;
        if (member[0x20] != 0xFE) {
            if (member[0x20] != 0xFD) {
                FastVecSub(local_offset, member + 0x10, self + 0x10);
                vec_transform_by_object_or_given(self, (char *)local_offset, (char *)local_offset, (char *)mtx);
                local_offset[3] = 1.0f;
                local_offset[0] = local_offset[0] + 2.0f;
                inside = math_fabs(local_offset[0]) < 1.0f && math_fabs(local_offset[1]) < 1.0f;
                if (inside) {
                    transform_vector(projected, local_offset, &g_platform_projection_table[state->tableIndex]);
                    entity_start_launch_to_target((char *)member, projected,
                                      g_platform_projection_table[state->tableIndex].height +
                                          math_random_float_range(1.0f, 2.0f),
                                      0.0055555557f, 0.0055555557f);
                }
            }
        }
    }
    hero_base = g_hero_state;
    if ((*(char **)(hero_base + 0x33C) == self && *(int *)(hero_base + 0x340) != 0) ||
        *(float *)(hero_base + 0x31C) < 0.5f) {
        FastVecSub(local_offset, g_hero_state + 0x80, self + 0x10);
        vec_transform_by_object_or_given(self, (char *)local_offset, (char *)local_offset, (char *)mtx);
        local_offset[3] = 1.0f;
        local_offset[0] = local_offset[0] + 2.0f;
        inside = math_fabs(local_offset[0]) < 1.0f && math_fabs(local_offset[1]) < 1.0f;
        if (inside) {
            transform_vector(projected, local_offset, &g_platform_projection_table[state->tableIndex]);
            hero_now = g_hero_state;
            top_height = g_platform_projection_table[state->tableIndex].height + 1.5f;
            rise_height = top_height - *(float *)(hero_now + 0x88);
            rise_height *= 2.0f; duration = square_root(rise_height / 0.0055555557f);
            fall_height = (top_height - projected[2]) * 2.0f; duration += square_root(fall_height / 0.0055555557f);
            FastVecSub(launch_velocity, projected, hero_now + 0x80); FastVecScale(launch_velocity, launch_velocity, 1.0f / duration);
            launch_velocity[2] = square_root(rise_height * 0.0055555557f);
            hero_l00_set_action(0x44, 1);
            qcopy(hero_now + 0xF0, launch_velocity);
        }
    }
}
