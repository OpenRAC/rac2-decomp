/* func_00303DA8 (116 bytes, boot and every level): asks the vector unit whether the
   object's position, moved by delta in z, is inside the field, and gives the distance to
   a fixed point when it is (9999.0f when not). The position is copied with qcopy; the
   object pointer is then passed again from its saved copy, as in retail. */
#include "common.h"

extern int func_002761F8(void *a, void *b, int c, int d, int e);
extern float func_00282E80(void *a, void *b);

extern char ref_00303DA8_00[];

/* Checks whether a point moved up or down is still inside the surface and returns a distance (9999 if not). */
float func_00303DA8(void *obj, float delta)
{
    float local[4];
    float *f = &local[2];

    qcopy(local, obj);
    *f = *f + delta;
    if (CollLine(obj, local, 0x12, 0, 0) != 0)
        return vec_distance_xy(obj, ref_00303DA8_00);
    return 9999.0f;
}
