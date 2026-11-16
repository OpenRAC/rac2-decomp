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

extern CameraEntry *g_moby_definition_table;
extern char *g_moby_l04_pool;
extern int g_cam_follow_index __attribute__((sda));
extern int g_cam_prev_follow_index __attribute__((sda));
extern float g_cam_fov __attribute__((sda));
extern int g_cam_side_flip __attribute__((sda));
extern int g_cam_transition_flag __attribute__((sda));
extern int g_current_map_index;
extern CameraPreset g_camera_presets_a[], g_camera_presets_b[];
extern char ref_L04_0046CFB8_00[];
extern float g_projection_scale_float[];
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
    char *definition = g_moby_definition_table[*(short *)(obj + 0x84)].definition;
    char *moby = g_moby_l04_pool + (*(int *)(definition + 0x60) << 8);
    int follow = 0;
    int i;
    float sine;

    if (*(unsigned char *)(moby + 0x20) == 3) {
        g_cam_follow_index = -1;
        for (i = 0; i < 16; i++) {
            if (*(int *)(definition + 0x20 + i * 4) != -1
                && IsPointInCuboid(moby + 0x10, *(int *)(definition + 0x20 + i * 4)))
                g_cam_follow_index = i;
        }
        if (g_cam_follow_index == -1) {
            if (g_cam_prev_follow_index != -1) {
                if (g_cam_side_flip) g_cam_side_flip = 0;
                else g_cam_side_flip = 1;
                cam_init_follow_offset(obj, 1);
                sine = math_fast_sin_or_cos_b(0.562170565f);
                g_projection_scale_float[0] = sine / math_fast_sin_or_cos_a(0.562170565f);
                UpdateViewContext();
                g_cam_transition_flag = 0;
                g_cam_prev_follow_index = g_cam_follow_index;
            }
            follow = 1;
        } else {
            if (g_cam_follow_index != g_cam_prev_follow_index) {
                if (math_random_float_range(0, 1) < .65f) {
                    g_cam_transition_flag = 1;
                    if (g_current_map_index == 4 || (int)ref_L04_0046CFB8_00 == 40) {
                        CameraPreset *preset = &g_camera_presets_a[g_cam_follow_index];
                        qcopy(obj + 0x30, preset);
                        g_cam_fov = preset->fov;
                    } else {
                        CameraPreset *preset = &g_camera_presets_b[g_cam_follow_index];
                        qcopy(obj + 0x30, preset);
                        g_cam_fov = preset->fov;
                    }
                } else {
                    if (g_cam_side_flip) g_cam_side_flip = 0;
                    else g_cam_side_flip = 1;
                    cam_init_follow_offset(obj, 1);
                    g_cam_transition_flag = 0;
                }
                g_cam_prev_follow_index = g_cam_follow_index;
            }
            if (g_cam_transition_flag) {
                float half = g_cam_fov * .5f;
                float sine2 = math_fast_sin_or_cos_b(half);
                g_projection_scale_float[0] = sine2 / math_fast_sin_or_cos_a(half);
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
