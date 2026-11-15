#include "common.h"

extern void *func_00270280(int target);
extern void func_00270598(void *target);
extern void func_L00_00428000(void *target, void *a1);
extern void func_L00_002D7958(void *target, void *a1, f32 f12);
extern void func_L00_002D7940(void *target);
extern void func_L00_00427C78(void *target);

/* Each helper accesses this five-float prefix only; the complete global
 * object extent remains unknown. GP access is proved independently by the
 * retail call sites, rather than inferred from this partial view size. */
typedef struct { f32 values[5]; } BlendPrefix;
extern BlendPrefix D_L00_001B15E0 __attribute__((sda));
extern BlendPrefix D_L00_001B15F8 __attribute__((sda));
extern BlendPrefix D_L00_001B1610 __attribute__((sda));

extern s16 D_L00_001B8F10 __attribute__((nosda));

/* Creates a new camera that follows the given target and sets up its starting blend values. Returns the new camera. */
void *func_L00_004282F0(u8 *target) {
    u8 *targetObj = target;
    u8 *camera;
    u8 *state;
    f32 zero;

    camera = FindRecordByHandleId(6);
    D_L00_001B8F10 = 0;
    SwitchActiveCamera(camera);
    UpdateCameraFollowTarget(camera, targetObj);
    state = *(u8 **)(camera + 0x70);
    qcopy(state + 0xB0, state + 0x80);
    zero = 0.0f;
    CopyVec5WithFirstBlended(state + 0x14, &D_L00_001B15E0, zero);
    CopyVec5WithFirstBlended(camera + 0x50, state + 0x14, zero);
    InitCameraBlendValues_L00_2(camera);
    *(int *)(state + 0x9C) = 1;
    CopyVec5WithFirstBlended(state + 0x28, &D_L00_001B15F8, zero);
    CopyVec5WithFirstBlended(state + 0x3C, &D_L00_001B1610, zero);
    ZeroFiveWords(state + 0x50);
    return camera;
}
