#include "include_asm.h"
#include "names.h"
extern int map_screen_update_layout(char *, int);
extern void object_set_first_float4(char *, float, float, float, float);
extern float *object_get_first_field(char *);
extern float D_001ADD88 __attribute__((sda));
extern float D_001ADD8C;
extern float D_001ADD90;
extern float D_001ADD94;
extern float D_001ADD98;
extern float D_001ADD9C;
extern float D_001ADDA0 __attribute__((sda));
extern float D_001ADDA4;
extern float D_001ADDA8 __attribute__((sda));
extern float D_001ADDAC;
extern float D_001ADDB0 __attribute__((sda));
extern float D_001ADDB4;
extern float D_001ADDB8 __attribute__((sda));
extern float D_001ADDBC;
extern char g_map_overlay_state[];
typedef struct { int first, second, third; float scale; } Entry_0033B540;
extern Entry_0033B540 g_map_spot_table[];

/* Places the sprites of the object built by func_0033B170 around the anchor at +0x1C8 and returns
   0. While the word at D_001C4FA0 + 0x230 is below 0x15, the offset of the sprites at +0xE4 and
   +0x130 (horizontal, 5 at most per call) and of the one at +0x17C (vertical, 3 at most) is eased
   toward a cell of the 16-byte table D_00265140. g and g2 are two loads of the same base: the
   second branch rebuilds the address, as retail does. The second argument is not read. */
int func_PAL_0033D468(char *self, int unused)
{
    float dx, dy;
    float *anchor;
    char *g;

    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self, anchor[0], anchor[1], 0.0f, 0.0f);
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0x4C, anchor[0], anchor[1], 0.0f, 0.0f);
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0x98, anchor[0], anchor[1], 0.0f, 0.0f);
    dx = dy = 0.0f;
    g = g_map_overlay_state;
    if (*(int *)(g + 0x230) < 0x15) {
        float t;

        dx = object_get_first_field(self + 0xE4)[0] - (D_001ADD88 + (*(float **)(self + 0x1C8))[0]);
        if (object_get_first_field(self + 0xE4)[0] == 0.0f) {
            dx = 56.0f;
        } else {
            t = (float)g_map_spot_table[*(int *)(g + 0x230)].first + g_map_spot_table[*(int *)(g + 0x230)].scale * 0.5f - dx;
            if (t > 5.0f)
                t = 5.0f;
            else if (t < -5.0f)
                t = -5.0f;
            dx += t;
        }
        dy = object_get_first_field(self + 0x17C)[1] - (D_001ADD9C + (*(float **)(self + 0x1C8))[1]);
        if (object_get_first_field(self + 0x17C)[1] == 0.0f) {
            dy = -50.0f;
        } else {
            char *g2 = g_map_overlay_state;
            t = (float)g_map_spot_table[*(int *)(g2 + 0x230)].second + g_map_spot_table[*(int *)(g2 + 0x230)].scale * 0.5f - dy;
            if (t > 3.0f)
                t = 3.0f;
            else if (t < -3.0f)
                t = -3.0f;
            dy += t;
        }
    }
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0xE4, D_001ADD88 + anchor[0] + dx, D_001ADD8C + anchor[1], 0.0f, 0.0f);
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0x130, D_001ADD90 + anchor[0] + dx, D_001ADD94 + anchor[1], 0.0f, 0.0f);
    object_set_first_float4(self + 0x17C, D_001ADD98 + (*(float **)(self + 0x1C8))[0], D_001ADD9C + (*(float **)(self + 0x1C8))[1] + dy, 0.0f, 0.0f);
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0x1D8, D_001ADDA0 + anchor[0], D_001ADDA4 + anchor[1], 0.0f, 0.0f);
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0x230, D_001ADDA8 + anchor[0], D_001ADDAC + anchor[1], 0.0f, 0.0f);
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0x288, D_001ADDB0 + anchor[0], D_001ADDB4 + anchor[1], 0.0f, 0.0f);
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0x2E0, D_001ADDB8 + anchor[0], D_001ADDBC + anchor[1], 0.0f, 0.0f);
    return 0;
}
