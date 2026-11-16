#include "names.h"
typedef int Quadword __attribute__((mode(TI)));
typedef struct { float position[4]; float original[4]; } EmitterOrigin;
extern float g_boss_four_glow_local_offset[4] __attribute__((sda));
extern float g_boss_four_glow_size_b __attribute__((sda));
extern float g_boss_four_glow_size_a __attribute__((sda));
extern void moby_transform_joint_to_world(char *, int, char *);
extern void moby_transform_joint_point(char *, int, char *);
extern void transform_vector(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void gfx_l00_draw_billboard_quad(void *, int, float, float);

/* Emit at joint four after transforming the local offset into world space. */
/* Draws a glow at joint 4, moved by a fixed offset in the joint's own direction. */
void boss_draw_joint_four_glow(char *moby)
{
    EmitterOrigin emitter;
    float jointMatrix[16];
    float localOffset[4];
    char *vars = *(char **)(*(char **)(moby + 0xB8) + 0x68);

    moby_transform_joint_to_world(moby, 4, (char *)emitter.position);
    *(Quadword *)emitter.original = *(Quadword *)emitter.position;
    moby_transform_joint_point(moby, 4, (char *)jointMatrix);
    transform_vector(localOffset, g_boss_four_glow_local_offset, jointMatrix);
    FastVecAdd(emitter.position, emitter.position, localOffset);
    gfx_l00_draw_billboard_quad(emitter.position, *(int *)(vars + 0x250),
            g_boss_four_glow_size_b, g_boss_four_glow_size_a);
}
