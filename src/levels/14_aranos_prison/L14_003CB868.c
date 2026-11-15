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
extern void hero_l00_set_action(int a0, int a1);
extern unsigned short *g_group_entity_lists[];
extern unsigned char *g_moby_l14_pool MACRO_ADDR;
extern int D_L14_001B25B8 __attribute__((sda));
struct Projection { char pad[0x38]; float height; char tail[0x44]; };
extern struct Projection *D_L14_001B268C MACRO_ADDR;
extern char g_hero_state[];

/* Only the observed table/group fields are described. */
struct OwnerPrefix { char reserved00[0x60]; int tableIndex, groupIndex; };

/* Pushes group members and the player up through the launch volume when they step into it. */
void UpdateLaunchVolume(char *self) {
    float mtx[16] __attribute__((aligned(16)));
    float localOffset[4] __attribute__((aligned(16)));
    float projected[4] __attribute__((aligned(16)));
    float launchVelocity[4] __attribute__((aligned(16)));
    struct OwnerPrefix *state = *(struct OwnerPrefix **)(self + 0x68);
    unsigned short *listEntry;
    unsigned char *member;
    char *heroBase;
    char *heroNow;
    int inside;
    float topHeight;
    float riseHeight;
    float fallHeight;
    float duration;

    matrix_from_basis_rows(mtx, self + 0xC0);
    for (listEntry = g_group_entity_lists[state->groupIndex];
         (state->groupIndex & 0xFF) != 0xFF && state->groupIndex <= D_L14_001B25B8 &&
         listEntry != 0 && ((listEntry != 0 && (short)listEntry[-1] >= 0) || listEntry == g_group_entity_lists[state->groupIndex]);
         listEntry++) {
        member = ((*listEntry & 0x7FFF) << 8) + g_moby_l14_pool;
        if (member == 0)
            break;
        if (member[0x20] != 0xFE) {
            if (member[0x20] != 0xFD) {
                FastVecSub(localOffset, member + 0x10, self + 0x10);
                vec_transform_by_object_or_given(self, (char *)localOffset, (char *)localOffset, (char *)mtx);
                localOffset[3] = 1.0f;
                localOffset[0] = localOffset[0] + 2.0f;
                inside = math_fabs(localOffset[0]) < 1.0f && math_fabs(localOffset[1]) < 1.0f;
                if (inside) {
                    transform_vector(projected, localOffset, &D_L14_001B268C[state->tableIndex]);
                    entity_start_launch_to_target((char *)member, projected,
                                      D_L14_001B268C[state->tableIndex].height +
                                          math_random_float_range(1.0f, 2.0f),
                                      0.0055555557f, 0.0055555557f);
                }
            }
        }
    }
    heroBase = g_hero_state;
    if ((*(char **)(heroBase + 0x33C) == self && *(int *)(heroBase + 0x340) != 0) ||
        *(float *)(heroBase + 0x31C) < 0.5f) {
        FastVecSub(localOffset, g_hero_state + 0x80, self + 0x10);
        vec_transform_by_object_or_given(self, (char *)localOffset, (char *)localOffset, (char *)mtx);
        localOffset[3] = 1.0f;
        localOffset[0] = localOffset[0] + 2.0f;
        inside = math_fabs(localOffset[0]) < 1.0f && math_fabs(localOffset[1]) < 1.0f;
        if (inside) {
            transform_vector(projected, localOffset, &D_L14_001B268C[state->tableIndex]);
            heroNow = g_hero_state;
            topHeight = D_L14_001B268C[state->tableIndex].height + 1.5f;
            riseHeight = topHeight - *(float *)(heroNow + 0x88);
            riseHeight *= 2.0f; duration = square_root(riseHeight / 0.0055555557f);
            fallHeight = (topHeight - projected[2]) * 2.0f; duration += square_root(fallHeight / 0.0055555557f);
            FastVecSub(launchVelocity, projected, heroNow + 0x80); FastVecScale(launchVelocity, launchVelocity, 1.0f / duration);
            launchVelocity[2] = square_root(riseHeight * 0.0055555557f);
            hero_l00_set_action(0x44, 1);
            qcopy(heroNow + 0xF0, launchVelocity);
        }
    }
}
