#include "common.h"

extern void *moby_find_record_by_handle_id(int target);
extern void cam_switch_active(void *target);
extern int cam_follow_update_target(void *target, void *a1);
extern void vec_copy5_blend_first(void *target, void *a1, f32 f12);
extern void moby_zero_five_words(void *target);
extern void cam_l00_init_blend_values_2(void *target);

/* Each helper accesses this five-float prefix only; the complete global
 * object extent remains unknown. GP access is proved independently by the
 * retail call sites, rather than inferred from this partial view size. */
typedef struct { f32 values[5]; } BlendPrefix;
extern BlendPrefix D_L00_001B15E0 __attribute__((sda));
extern BlendPrefix D_L00_001B15F8 __attribute__((sda));
extern BlendPrefix D_L00_001B1610 __attribute__((sda));

extern s16 D_L00_001B8F10 __attribute__((nosda));

/* Creates a new camera that follows the given target and sets up its starting blend values. Returns the new camera. */
void *cam_follow_create(u8 *target) {
    u8 *target_obj = target;
    u8 *camera;
    u8 *state;
    f32 zero;

    camera = moby_find_record_by_handle_id(6);
    D_L00_001B8F10 = 0;
    cam_switch_active(camera);
    cam_follow_update_target(camera, target_obj);
    state = *(u8 **)(camera + 0x70);
    qcopy(state + 0xB0, state + 0x80);
    zero = 0.0f;
    vec_copy5_blend_first(state + 0x14, &D_L00_001B15E0, zero);
    vec_copy5_blend_first(camera + 0x50, state + 0x14, zero);
    cam_l00_init_blend_values_2(camera);
    *(int *)(state + 0x9C) = 1;
    vec_copy5_blend_first(state + 0x28, &D_L00_001B15F8, zero);
    vec_copy5_blend_first(state + 0x3C, &D_L00_001B1610, zero);
    moby_zero_five_words(state + 0x50);
    return camera;
}
