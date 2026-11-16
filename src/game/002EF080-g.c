#include "names.h"
/* Converts the three tfrag LOD distances to fixed point and builds the 4x4 blend matrix
   that fades between them (rac1's set_tfrag_dists). Retail compiles this with -g (the
   nop pairs before div.s). */
extern float g_lod_range_scales[3];
extern int g_lod_range_fixed[3];
extern float g_range_scale[];
extern float g_projection_matrix[4][4];
extern int FloatToInt(float);
extern void mem_fast_helper_b(void *, int);

/* Sets up the distances at which terrain detail changes, and the blending numbers used to fade between the three detail levels. */
void SetTfragDists(void)
{
    float scaled_far_range, scaled_middle_range, scaled_near_range, ab, bc;

    g_lod_range_fixed[0] = FloatToInt(g_lod_range_scales[0] * 1024.0f);
    g_lod_range_fixed[1] = FloatToInt(g_lod_range_scales[1] * 1024.0f);
    g_lod_range_fixed[2] = FloatToInt(g_lod_range_scales[2] * 1024.0f);
    scaled_far_range = g_lod_range_scales[0] * g_range_scale[0];
    scaled_middle_range = g_lod_range_scales[1] * g_range_scale[0];
    scaled_near_range = g_lod_range_scales[2] * g_range_scale[0];
    ab = 1.0f / (scaled_far_range - scaled_middle_range);
    bc = 1.0f / (scaled_middle_range - scaled_near_range);
    mem_fast_helper_b(g_projection_matrix, 0x40);
    g_projection_matrix[0][0] = ab * 0.5f;
    g_projection_matrix[0][1] = -ab;
    g_projection_matrix[1][0] = bc * 0.5f;
    g_projection_matrix[1][1] = -bc;
    g_projection_matrix[2][0] = scaled_middle_range * ab * -0.5f;
    g_projection_matrix[2][1] = scaled_far_range * ab;
    g_projection_matrix[3][0] = scaled_near_range * bc * -0.5f;
    g_projection_matrix[3][1] = scaled_middle_range * bc;
    g_projection_matrix[1][3] = scaled_middle_range;
    g_projection_matrix[0][3] = scaled_far_range;
}
