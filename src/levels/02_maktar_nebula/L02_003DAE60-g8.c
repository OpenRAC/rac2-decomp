#include "include_asm.h"
#include "names.h"

/* func_L02_003DAE60 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern float D_L02_001B0410 __attribute__((sda));
extern float D_L02_001B0414 __attribute__((sda));
extern int D_L02_001B0420 __attribute__((sda));
extern float D_L02_001B0430 __attribute__((sda));
extern float g_camera_l02_position[4];

extern void moby_transform_joint_to_world(char *, int, void *);
extern void moby_transform_joint_point(char *, int, void *);
extern void transform_vector(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void gfx_l00_draw_billboard_quad(void *, int, float, float);

/* Draws a glow at a joint of the boss, brighter when it faces the camera. */
void boss_draw_joint_glow_facing_cam(char *moby, int jointIndex) {
    float jointPos[4];
    float jointPosCopy[4];
    float jointMatrix[16];
    float localOffset[4];
    float toCamera[4];
    float axisCopy[4];
    float alignment;
    unsigned int color;
    char *vars = *(char **)(*(char **)(moby + 0xB8) + 0x68);

    moby_transform_joint_to_world(moby, jointIndex, jointPos);
    *(TI128 *)jointPosCopy = *(TI128 *)jointPos;
    moby_transform_joint_point(moby, jointIndex, jointMatrix);
    transform_vector(localOffset, &D_L02_001B0420, jointMatrix);
    FastVecAdd(jointPos, jointPos, localOffset);
    FastVecSub(toCamera, g_camera_l02_position, jointPos);
    vec_scale_to_length(toCamera, toCamera, 1.0f);
    *(TI128 *)axisCopy = *(TI128 *)jointMatrix;
    alignment = FastVecDot(toCamera, axisCopy);
    if (D_L02_001B0430 < alignment) {
        color = *(unsigned int *)(vars + 0x250);
        alignment = alignment * alignment;
        gfx_l00_draw_billboard_quad(jointPos, (color & 0xFFFFFF) | ((int)(alignment * (float)(int)(color >> 24)) << 24),
                          D_L02_001B0414, D_L02_001B0410);
    }
}
