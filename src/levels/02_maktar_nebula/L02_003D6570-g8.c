#include "include_asm.h"
#include "names.h"

/* func_L02_003D6570 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern float D_L02_001B0318 __attribute__((sda));
extern float D_L02_001B031C __attribute__((sda));
extern int D_L02_001B0320 __attribute__((sda));
extern unsigned int D_L02_001B0330 __attribute__((sda));
extern float D_L02_001B0334 __attribute__((sda));
extern float g_camera_l02_position[4];

extern void moby_transform_joint_to_world(char *, int, void *);
extern void moby_transform_joint_point(char *, int, void *);
extern void transform_vector(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void gfx_l00_draw_billboard_quad(void *, int, float, float);

/* Draws one glow flare at a joint, fading it out when the joint faces away from the camera. */
void chainblade_draw_joint_flare(char *self, int joint) {
    float origin[4];
    float originCopy[4];
    float matrix[16];
    float offset[4];
    float toCamera[4];
    float facing[4];
    float facingDot;
    unsigned int color;

    moby_transform_joint_to_world(self, joint, origin);
    *(TI128 *)originCopy = *(TI128 *)origin;
    moby_transform_joint_point(self, joint, matrix);
    transform_vector(offset, &D_L02_001B0320, matrix);
    FastVecAdd(origin, origin, offset);
    FastVecSub(toCamera, g_camera_l02_position, origin);
    vec_scale_to_length(toCamera, toCamera, 1.0f);
    *(TI128 *)facing = *(TI128 *)matrix;
    facingDot = FastVecDot(toCamera, facing);
    if (D_L02_001B0334 < facingDot) {
        color = D_L02_001B0330;
        facingDot = facingDot * facingDot;
        gfx_l00_draw_billboard_quad(origin, (color & 0xFFFFFF) | ((int)(facingDot * (float)(int)(color >> 24)) << 24),
                          D_L02_001B031C, D_L02_001B0318);
    }
}
