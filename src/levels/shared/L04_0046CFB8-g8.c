#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));

typedef struct {
    char pad[0x1C];
    char *definition;
} CameraEntry;

/* A fixed camera view: its rotation and its field of view at +0x18. */
typedef struct {
    Quad rotation;
    float pad[2];
    float fov;
    float unused;
} CameraPreset;

extern CameraEntry *D_L04_001B1E84;
extern char *g_moby_l04_pool;
extern int D_L04_001B1CB8 __attribute__((sda));
extern int D_L04_001B1CBC __attribute__((sda));
extern float D_L04_001B1CC0 __attribute__((sda));
extern int D_L04_001B1CC4 __attribute__((sda));
extern int D_L04_001B1CC8 __attribute__((sda));
extern int g_current_map_index;
extern CameraPreset D_L04_002C6F00[], D_L04_002C7100[];
extern char ref_L04_0046CFB8_00[];
extern float D_L04_001BDC30[];
extern int IsPointInCuboid(void *, int);
extern void cam_init_follow_offset(void *, int);
extern float math_fast_sin_or_cos_b(float);
extern float math_fast_sin_or_cos_a(float);
extern float math_random_float_range(float, float);
extern void UpdateViewContext(void);
extern void cam_look_at_player(void *);
extern void UpdatePlayerRelativeCameraPosition(void *);

/* Pick the camera for the region the target moby stands in: entering one of
 * the definition's sixteen cuboids either switches to that region's fixed
 * preset or flips the follow side; outside every region the follow camera runs. */
void UpdateRegionCamera(char *obj)
{
    char *definition = D_L04_001B1E84[*(short *)(obj + 0x84)].definition;
    char *moby = g_moby_l04_pool + (*(int *)(definition + 0x60) << 8);
    int follow = 0;
    int i;
    float sine;

    if (*(unsigned char *)(moby + 0x20) == 3) {
        D_L04_001B1CB8 = -1;
        for (i = 0; i < 16; i++) {
            if (*(int *)(definition + 0x20 + i * 4) != -1
                && IsPointInCuboid(moby + 0x10, *(int *)(definition + 0x20 + i * 4)))
                D_L04_001B1CB8 = i;
        }
        if (D_L04_001B1CB8 == -1) {
            if (D_L04_001B1CBC != -1) {
                if (D_L04_001B1CC4) D_L04_001B1CC4 = 0;
                else D_L04_001B1CC4 = 1;
                cam_init_follow_offset(obj, 1);
                sine = math_fast_sin_or_cos_b(0.562170565f);
                D_L04_001BDC30[0] = sine / math_fast_sin_or_cos_a(0.562170565f);
                UpdateViewContext();
                D_L04_001B1CC8 = 0;
                D_L04_001B1CBC = D_L04_001B1CB8;
            }
            follow = 1;
        } else {
            if (D_L04_001B1CB8 != D_L04_001B1CBC) {
                if (math_random_float_range(0, 1) < .65f) {
                    D_L04_001B1CC8 = 1;
                    if (g_current_map_index == 4 || (int)ref_L04_0046CFB8_00 == 40) {
                        CameraPreset *preset = &D_L04_002C6F00[D_L04_001B1CB8];
                        qcopy(obj + 0x30, preset);
                        D_L04_001B1CC0 = preset->fov;
                    } else {
                        CameraPreset *preset = &D_L04_002C7100[D_L04_001B1CB8];
                        qcopy(obj + 0x30, preset);
                        D_L04_001B1CC0 = preset->fov;
                    }
                } else {
                    if (D_L04_001B1CC4) D_L04_001B1CC4 = 0;
                    else D_L04_001B1CC4 = 1;
                    cam_init_follow_offset(obj, 1);
                    D_L04_001B1CC8 = 0;
                }
                D_L04_001B1CBC = D_L04_001B1CB8;
            }
            if (D_L04_001B1CC8) {
                float half = D_L04_001B1CC0 * .5f;
                float sine2 = math_fast_sin_or_cos_b(half);
                D_L04_001BDC30[0] = sine2 / math_fast_sin_or_cos_a(half);
                UpdateViewContext();
                cam_look_at_player(obj);
            } else {
                follow = 1;
            }
        }
    } else {
        follow = *(unsigned char *)(moby + 0xBC) != 0;
    }
    if (follow) {
        UpdatePlayerRelativeCameraPosition(obj);
        cam_look_at_player(obj);
    }
}
