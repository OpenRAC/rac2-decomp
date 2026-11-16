#include "include_asm.h"
#include "names.h"


typedef int V4_L23_418650 __attribute__((mode(TI)));
extern char g_camera_position[];
extern float g_mothership_surface_radius __attribute__((sda));
extern void FastVecSub(char *dst, char *src, char *arg);
extern void vec_scale_to_length(char *dst, char *src, float arg);
extern void FastVecAdd(char *dst, char *src, char *arg);

/* Same body as func_L23_00418650, with this function's own callees. */
extern float ref_L22_003A2988_00 __attribute__((sda));
/* Pushes a point away from the center of the round arena by the given extra distance. */
void arena_push_point_out(char *point, float extra) {
    char scratch[16];

    FastVecSub(scratch, point, g_camera_position);
    vec_scale_to_length(scratch, scratch, extra + ref_L22_003A2988_00);
    FastVecAdd(scratch, scratch, g_camera_position);
    *(V4_L23_418650 *)point = *(V4_L23_418650 *)scratch;
}
