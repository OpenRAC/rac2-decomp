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

extern char D_L00_001BB9F0[];
#define SLOT(i) ((OverrideRecord *)(D_L00_001BB9F0 + (i) * 64))
extern int D_L00_001B1884 __attribute__((sda));
extern char D_00138180[];
extern void func_L00_002D7140(void *);
extern void func_0026FF08(int, int, float, float, float, float);
extern void func_L00_00424A08(int, float, float);
extern void func_L00_00424A50(float, float);
extern void func_L00_00424A88(int, float, float);
extern void func_L00_00424B20(float);
extern void func_L00_00424B48(int);
extern void func_L00_00424B70(float, float);
extern void ref_L00_002D71A0_01(float, float);
extern void func_L00_00424C00(void);
extern void func_L00_00424C28(void);
extern void func_L00_00424C60(void);
extern void ref_L00_002D71A0_00(void);
extern void func_L00_002D7938(float);
extern void func_L00_00424F00(void *, float, float);
extern int func_00282978(void *);
extern float func_00283CE0(int);
extern float func_00282C48(float);

/* Each frame, picks the highest-priority camera override, applies its settings to the camera and returns its slot (or -1 if none). */
int func_L00_002D71A0(void)
{
    int i;
    int priority = -1;
    int selected = -1;

    for (i = 0; i < 32; ++i) {
        OverrideRecord *scan = SLOT(i);
        if (scan->active != 0) {
            if (scan->expiry != 0 && --scan->expiry == 0) {
                EndCameraOverride(scan);
            } else if (scan->priority > priority) {
                priority = scan->priority;
                selected = i;
            }
        }
    }
    if (selected >= 0 && D_L00_001B1884 >= 0 && selected != D_L00_001B1884 &&
        SLOT(D_L00_001B1884)->blend >= 0.0f &&
        SLOT(selected)->blend < 0.0f)
        SetCameraValueTarget(0, 3, 1.1243411f, 0.005f, 0.2f, 0.0f);
    D_L00_001B1884 = selected;
    if (selected >= 0) {

    if (SLOT(selected)->primary >= 0.0f) {
        follow_camera_set_distance(0, SLOT(selected)->primary, 0.001f);
        if (SLOT(selected)->primary < 4.64f ||
            SLOT(selected)->primary > 6.0f)
            SetCameraSnapFlag();
    }
    if (SLOT(selected)->secondary >= 0.0f)
        follow_camera_set_height(SLOT(selected)->secondary, 0.001f);
    if (SLOT(selected)->roll >= 0.0f)
        SetCameraTuningValue(SLOT(selected)->roll);
    if (SLOT(selected)->offset >= 0.0f)
        SetCameraAimOffsetTarget(0, SLOT(selected)->offset, 0.005f);
    if (SLOT(selected)->extra >= 0.0f)
        SetCameraOverrideExtra(SLOT(selected)->extra);
    if (SLOT(selected)->flag26 != 0)
        SetCameraInputFlags();
    if (SLOT(selected)->flag60 != 0)
        ref_L00_002D71A0_00();
    if (SLOT(selected)->flag24 != 0) {
        SetCameraSnapFlag();
        set_follow_camera_orbit_clamp_mode(0);
        SetCameraLockFlag();
        ref_L00_002D71A0_01(0.01f, 0.2f);
        SetCameraSpeedsIfNonZero(0.03f, 0.2f);
    }
    if (SLOT(selected)->flag25 != 0) {
        SetCameraLockFlag();
        SetCameraSpeedsIfNonZero(0.03f, 0.2f);
        ref_L00_002D71A0_01(0.0075f, 0.2f);
    }
    if (SLOT(selected)->blend >= 0.0f)
        SetCameraValueTarget(0, 3, SLOT(selected)->blend, 0.005f, 0.2f, 0.0f);
    if ((float)SLOT(selected)->mode > 0.0f)
        SetCameraStrengthAndSteer(SLOT(selected)->point,
                         IntToFloat(SLOT(selected)->angle) * 0.017453294f, 0.0f);
    if ((float)SLOT(selected)->timed_mode > 0.0f) {
        if (FastDecTimer(&SLOT(selected)->timer) != 0)
            SetCameraStrengthAndSteer(SLOT(selected)->point,
                             IntToFloat(SLOT(selected)->angle) * 0.017453294f, 0.0f);
        if (FloatAbs(((InputState *)gPadState)->x) > 0.01f ||
            FloatAbs(((InputState *)gPadState)->y) > 0.01f)
            SLOT(selected)->timer = SLOT(selected)->reset_timer;
    }
    return selected;
    }
    return -1;
}
