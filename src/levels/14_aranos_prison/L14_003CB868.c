/* Project group members and the player through a launch volume.
 * The flight-time stages share source lines to preserve the measured -g division padding.
 */
#include "common.h"

extern void func_00283698(void *dst, void *src);
extern void func_00282CF0(void *dst, void *a, void *b);
extern void func_002AFDD8(char *a, char *b, char *c, char *d);
extern float func_00282C48(float a);
extern void func_002830C0(void *dst, void *a, void *b);
extern float func_002A7878(float a, float b);
extern float func_00282C10(float a);
extern void func_00282D30(void *dst, void *src, float s);
extern void func_L14_003C96E0(char *e, void *v, float a, float b, float c);
extern void func_L00_002C42E0(int a0, int a1);
extern unsigned short *D_L14_001FB060[];
extern unsigned char *D_L14_001B259C MACRO_ADDR;
extern int D_L14_001B25B8 __attribute__((sda));
struct Projection { char pad[0x38]; float height; char tail[0x44]; };
extern struct Projection *D_L14_001B268C MACRO_ADDR;
extern char D_00189E20[];

/* Only the observed table/group fields are described. */
struct OwnerPrefix { char reserved00[0x60]; int tableIndex, groupIndex; };

/* Pushes group members and the player up through the launch volume when they step into it. */
void func_L14_003CB868(char *self) {
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
    for (listEntry = gGroupEntityLists[state->groupIndex];
         (state->groupIndex & 0xFF) != 0xFF && state->groupIndex <= D_L14_001B25B8 &&
         listEntry != 0 && ((listEntry != 0 && (short)listEntry[-1] >= 0) || listEntry == gGroupEntityLists[state->groupIndex]);
         listEntry++) {
        member = ((*listEntry & 0x7FFF) << 8) + gMobyPool_L14;
        if (member == 0)
            break;
        if (member[0x20] != 0xFE) {
            if (member[0x20] != 0xFD) {
                FastVecSub(localOffset, member + 0x10, self + 0x10);
                TransformVectorByObjectOrGiven(self, (char *)localOffset, (char *)localOffset, (char *)mtx);
                localOffset[3] = 1.0f;
                localOffset[0] = localOffset[0] + 2.0f;
                inside = FloatAbs(localOffset[0]) < 1.0f && FloatAbs(localOffset[1]) < 1.0f;
                if (inside) {
                    transform_vector(projected, localOffset, &D_L14_001B268C[state->tableIndex]);
                    StartLaunchTowardTarget((char *)member, projected,
                                      D_L14_001B268C[state->tableIndex].height +
                                          RandomFloatRange(1.0f, 2.0f),
                                      0.0055555557f, 0.0055555557f);
                }
            }
        }
    }
    heroBase = gHeroState;
    if ((*(char **)(heroBase + 0x33C) == self && *(int *)(heroBase + 0x340) != 0) ||
        *(float *)(heroBase + 0x31C) < 0.5f) {
        FastVecSub(localOffset, gHeroState + 0x80, self + 0x10);
        TransformVectorByObjectOrGiven(self, (char *)localOffset, (char *)localOffset, (char *)mtx);
        localOffset[3] = 1.0f;
        localOffset[0] = localOffset[0] + 2.0f;
        inside = FloatAbs(localOffset[0]) < 1.0f && FloatAbs(localOffset[1]) < 1.0f;
        if (inside) {
            transform_vector(projected, localOffset, &D_L14_001B268C[state->tableIndex]);
            heroNow = gHeroState;
            topHeight = D_L14_001B268C[state->tableIndex].height + 1.5f;
            riseHeight = topHeight - *(float *)(heroNow + 0x88);
            riseHeight *= 2.0f; duration = square_root(riseHeight / 0.0055555557f);
            fallHeight = (topHeight - projected[2]) * 2.0f; duration += square_root(fallHeight / 0.0055555557f);
            FastVecSub(launchVelocity, projected, heroNow + 0x80); FastVecScale(launchVelocity, launchVelocity, 1.0f / duration);
            launchVelocity[2] = square_root(riseHeight * 0.0055555557f);
            SetHeroAction_L00(0x44, 1);
            qcopy(heroNow + 0xF0, launchVelocity);
        }
    }
}
