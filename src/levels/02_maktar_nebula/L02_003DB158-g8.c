#include "include_asm.h"
#include "names.h"

/* func_L02_003DB158 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give
   retail's grouped `lq`/`sq` with register addresses and keep the instructions around the
   copy on their own side of it. */

typedef int s32;
typedef float f32;
typedef int TQ __attribute__((mode(TI)));

extern f32 g_boss_glow_quad_size_a __attribute__((sda));
extern f32 g_boss_glow_quad_size_b __attribute__((sda));
extern s32 g_boss_glow_quad_offset __attribute__((sda));

extern void moby_transform_joint_to_world(char *, int, void *);
extern void moby_transform_joint_point(char *, int, void *);
extern void transform_vector(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void gfx_l00_draw_billboard_quad(void *, int, float, float);

typedef struct { f32 x, y, z, w; } V4;
typedef struct { f32 v[16]; } M4;

/* Draws a glow at a joint of the boss, moved by a fixed offset in the joint's own direction. */
void boss_draw_joint_glow(char *moby, s32 jointIndex) {
    char *vars = *(char **)(*(char **)(moby + 0xB8) + 0x68);
    V4 jointPos, jointPosCopy;
    M4 jointMatrix;
    V4 localOffset;

    moby_transform_joint_to_world(moby, jointIndex, &jointPos);
    *(TQ *)&jointPosCopy = *(TQ *)&jointPos;
    moby_transform_joint_point(moby, jointIndex, &jointMatrix);
    transform_vector(&localOffset, &g_boss_glow_quad_offset, &jointMatrix);
    FastVecAdd(&jointPos, &jointPos, &localOffset);
    gfx_l00_draw_billboard_quad(&jointPos, *(s32 *)(vars + 0x250), g_boss_glow_quad_size_b, g_boss_glow_quad_size_a);
}
