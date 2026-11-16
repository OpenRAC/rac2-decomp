/* Camera override selector: expires timed records, picks the highest
 * priority active one and applies its settings. -O2 -G8 (27 places). */
#include "include_asm.h"
#include "names.h"

typedef struct {
    float primary, secondary, offset, roll, blend, extra;
    unsigned char flag24, flag25;
    short flag26;
    unsigned char priority, active, mode, timed_mode;
    float point[4];
    short timer, reset_timer;
    int angle, expiry, flag60;
} OverrideRecord;

typedef struct { char pad[256]; float x, y; } InputState;

extern char g_cam_l00_override_slots[];
#define SLOT(i) ((OverrideRecord *)(D_L00_001BB9F0 + (i) * 64))
extern int g_cam_override_selected_slot __attribute__((sda));
extern char g_pad_state[];
extern void cam_end_override(void *);
extern void cam_set_value_target(int, int, float, float, float, float);
extern void follow_camera_set_distance(int, float, float);
extern void follow_camera_set_height(float, float);
extern void cam_set_aim_offset_target(int, float, float);
extern void cam_set_tuning_value(float);
extern void set_follow_camera_orbit_clamp_mode(int);
extern void cam_set_speeds_if_nonzero(float, float);
extern void ref_L00_002D71A0_01(float, float);
extern void cam_set_snap_flag(void);
extern void cam_set_lock_flag(void);
extern void cam_set_input_flags(void);
extern void ref_L00_002D71A0_00(void);
extern void cam_set_override_extra(float);
extern void cam_set_strength_and_steer(void *, float, float);
extern int FastDecTimer(void *);
extern float IntToFloat(int);
extern float math_fabs(float);

/* Each frame, picks the highest-priority camera override, applies its settings to the camera and returns its slot (or -1 if none). */
int cam_update_overrides(void)
{
    int i;
    int priority = -1;
    int selected = -1;

    for (i = 0; i < 32; ++i) {
        OverrideRecord *scan = SLOT(i);
        if (scan->active != 0) {
            if (scan->expiry != 0 && --scan->expiry == 0) {
                cam_end_override(scan);
            } else if (scan->priority > priority) {
                priority = scan->priority;
                selected = i;
            }
        }
    }
    if (selected >= 0 && g_cam_override_selected_slot >= 0 && selected != g_cam_override_selected_slot &&
        SLOT(g_cam_override_selected_slot)->blend >= 0.0f &&
        SLOT(selected)->blend < 0.0f)
        cam_set_value_target(0, 3, 1.1243411f, 0.005f, 0.2f, 0.0f);
    g_cam_override_selected_slot = selected;
    if (selected >= 0) {

    if (SLOT(selected)->primary >= 0.0f) {
        follow_camera_set_distance(0, SLOT(selected)->primary, 0.001f);
        if (SLOT(selected)->primary < 4.64f ||
            SLOT(selected)->primary > 6.0f)
            cam_set_snap_flag();
    }
    if (SLOT(selected)->secondary >= 0.0f)
        follow_camera_set_height(SLOT(selected)->secondary, 0.001f);
    if (SLOT(selected)->roll >= 0.0f)
        cam_set_tuning_value(SLOT(selected)->roll);
    if (SLOT(selected)->offset >= 0.0f)
        cam_set_aim_offset_target(0, SLOT(selected)->offset, 0.005f);
    if (SLOT(selected)->extra >= 0.0f)
        cam_set_override_extra(SLOT(selected)->extra);
    if (SLOT(selected)->flag26 != 0)
        cam_set_input_flags();
    if (SLOT(selected)->flag60 != 0)
        ref_L00_002D71A0_00();
    if (SLOT(selected)->flag24 != 0) {
        cam_set_snap_flag();
        set_follow_camera_orbit_clamp_mode(0);
        cam_set_lock_flag();
        ref_L00_002D71A0_01(0.01f, 0.2f);
        cam_set_speeds_if_nonzero(0.03f, 0.2f);
    }
    if (SLOT(selected)->flag25 != 0) {
        cam_set_lock_flag();
        cam_set_speeds_if_nonzero(0.03f, 0.2f);
        ref_L00_002D71A0_01(0.0075f, 0.2f);
    }
    if (SLOT(selected)->blend >= 0.0f)
        cam_set_value_target(0, 3, SLOT(selected)->blend, 0.005f, 0.2f, 0.0f);
    if ((float)SLOT(selected)->mode > 0.0f)
        cam_set_strength_and_steer(SLOT(selected)->point,
                         IntToFloat(SLOT(selected)->angle) * 0.017453294f, 0.0f);
    if ((float)SLOT(selected)->timed_mode > 0.0f) {
        if (FastDecTimer(&SLOT(selected)->timer) != 0)
            cam_set_strength_and_steer(SLOT(selected)->point,
                             IntToFloat(SLOT(selected)->angle) * 0.017453294f, 0.0f);
        if (math_fabs(((InputState *)g_pad_state)->x) > 0.01f ||
            math_fabs(((InputState *)g_pad_state)->y) > 0.01f)
            SLOT(selected)->timer = SLOT(selected)->reset_timer;
    }
    return selected;
    }
    return -1;
}
