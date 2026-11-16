#include "include_asm.h"

#include "common.h"
typedef struct {
    unsigned char pad0[4960];
    void *p1360;
    void *p1364;
    void *p1368;
    unsigned char pad1[4512];
    float f250C;
    float f2510;
    float f2514;
} Persistent_F882f1178;
typedef struct {
    unsigned char pad[120];
    int field120;
} Node_F882f1178;
extern Persistent_F882f1178 D_00189E20_11;
extern int g_game_l00_mode __attribute__((sda));
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern int FastTweenColor(int, int, float);
extern void math_store_angle_update_result(int, float *, int, int, float);
extern int ref_L00_002D4A38_00 __attribute__((sda));

/* Fades the colors of the level glow objects back and forth over time (PAL: 50 Hz step sizes). */
void level_fade_glow_colors_pal(void)
{
    Node_F882f1178 *node;

    node = (Node_F882f1178 *)D_00189E20_11.p1360;
    if (node != 0) {
        if (ref_L00_002D4A38_00 == 2)
            D_00189E20_11.f250C = FastAddRotations(D_00189E20_11.f250C, 0.024434613f);
        else
            D_00189E20_11.f250C = FastAddRotations(D_00189E20_11.f250C, 0.04188791f);
        node->field120 = FastTweenColor(0xd2d2d2, 0x285050,
                                 math_fast_sin_or_cos_b(D_00189E20_11.f250C) * 0.5f + 0.5f);
    }
    node = (Node_F882f1178 *)D_00189E20_11.p1364;
    if (node != 0) {
        if (g_game_l00_mode != 2) {
            float limit;
            int which;

            limit = FastAddRotations(D_00189E20_11.f2510, 0.059341207f);
            D_00189E20_11.f2510 = limit;
            which = 0x1ee628;
            if (limit > 0.0f && limit < 1.9198623895645142f) {
                which = 0x1e1ed2;
            }
            node->field120 = FastTweenColor(node->field120, which, 0.070000000298023224f);
        } else {
            D_00189E20_11.f2510 = FastAddRotations(D_00189E20_11.f2510, 0.031415932f);
            node->field120 = FastTweenColor(0x1e1ed2, 0x1e1e50,
                                     math_fast_sin_or_cos_b(D_00189E20_11.f2510) * 0.5f + 0.5f);
        }
    }
    if (D_00189E20_11.p1368 != 0) {
        if (g_game_l00_mode == 2)
            math_store_angle_update_result((int)D_00189E20_11.p1368, &D_00189E20_11.f2514, 0xdcdcdc, 0x323232,
                    0.031415932f);
        else
            math_store_angle_update_result((int)D_00189E20_11.p1368, &D_00189E20_11.f2514, 0xdcdcdc, 0x323232,
                    0.048869226f);
    }
}
