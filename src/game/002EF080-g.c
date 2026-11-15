#include "names.h"
/* Converts the three tfrag LOD distances to fixed point and builds the 4x4 blend matrix
   that fades between them (rac1's set_tfrag_dists). Retail compiles this with -g (the
   nop pairs before div.s). */
extern float D_001B2180[3];
extern int D_001B2190[3];
extern float D_001B9260[];
extern float D_002634F0[4][4];
extern int FloatToInt(float);
extern void mem_fast_helper_b(void *, int);

/* Sets up the distances at which terrain detail changes, and the blending numbers used to fade between the three detail levels. */
void SetTfragDists(void)
{
    float scaled_far_range, scaled_middle_range, scaled_near_range, ab, bc;

    D_001B2190[0] = FloatToInt(D_001B2180[0] * 1024.0f);
    D_001B2190[1] = FloatToInt(D_001B2180[1] * 1024.0f);
    D_001B2190[2] = FloatToInt(D_001B2180[2] * 1024.0f);
    scaled_far_range = D_001B2180[0] * D_001B9260[0];
    scaled_middle_range = D_001B2180[1] * D_001B9260[0];
    scaled_near_range = D_001B2180[2] * D_001B9260[0];
    ab = 1.0f / (scaled_far_range - scaled_middle_range);
    bc = 1.0f / (scaled_middle_range - scaled_near_range);
    mem_fast_helper_b(D_002634F0, 0x40);
    D_002634F0[0][0] = ab * 0.5f;
    D_002634F0[0][1] = -ab;
    D_002634F0[1][0] = bc * 0.5f;
    D_002634F0[1][1] = -bc;
    D_002634F0[2][0] = scaled_middle_range * ab * -0.5f;
    D_002634F0[2][1] = scaled_far_range * ab;
    D_002634F0[3][0] = scaled_near_range * bc * -0.5f;
    D_002634F0[3][1] = scaled_middle_range * bc;
    D_002634F0[1][3] = scaled_middle_range;
    D_002634F0[0][3] = scaled_far_range;
}
