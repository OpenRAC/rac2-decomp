#include "include_asm.h"
#include "names.h"

/* func_L23_00418650 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give
   retail's grouped `lq`/`sq` with register addresses and keep the instructions around the
   copy on their own side of it. */

typedef int V4_L23_418650 __attribute__((mode(TI)));

extern char g_camera_position[];
extern float g_mothership_surface_radius __attribute__((sda));
extern void FastVecSub(char *dst, char *src, char *arg);
extern void vec_scale_to_length(char *dst, char *src, float arg);
extern void FastVecAdd(char *dst, char *src, char *arg);

/* Moves a point onto the round planet surface, at the given height above it. */
void mothership_project_point_onto_surface(char *pos, float heightOffset) {
    char local[16];

    FastVecSub(local, pos, g_camera_position);
    vec_scale_to_length(local, local, heightOffset + g_mothership_surface_radius);
    FastVecAdd(local, local, g_camera_position);
    *(V4_L23_418650 *)pos = *(V4_L23_418650 *)local;
}
