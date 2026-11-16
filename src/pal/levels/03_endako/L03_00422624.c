#include "include_asm.h"
#include "names.h"


typedef unsigned char u8;
typedef unsigned int u32;
extern void vec_copy_helper_a(void *);
extern void FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastVecDot(void *, void *);
extern void lerp_vector(void *, void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float vec_distance_xy(void *, void *);
extern float fast_vec_dist(void *, void *);
extern float ApproachValue(void *, float, float);
extern int PlayMobySound(int, int, void *);
extern void snd_stop_voice(int);
extern int moby_l01_turn_toward_target_pal(void *, void *);
extern u8 g_sound_l03_slot_table[];
extern u32 func_31CFF8(void *a, void *b, u32 c);
extern u8 *g_moby_record_base __attribute__((sda));
extern u8 *g_entity_id_lists[];
typedef struct {
    u32 field00;
    u8 pad04[0x0C];
    u8 field10[1];
} Entry41D1D8;
extern Entry41D1D8 *g_path_l03_entry_table[];
extern u8 g_status_flag_b[0x40] __attribute__((sda));

/* Projects the state position onto its path, clamps lateral displacement,
 * advances the path blend nearby, and maintains its movement sound. */
void func_PAL_L03_00423128(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    u8 *entry = (u8 *)g_path_l03_entry_table[*(int *)(state + 0x210)];
    float delta[4], along[4], across[4], axis[4], point[4], scaled[4];
    float distance;
    float side;
    vec_copy_helper_a(axis);
    FastVecSub(along, entry + 0x20, entry + 0x10);
    along[2] = 0;
    FastVecCross(across, along, axis);
    vec_scale_to_length(across, across, 1.0f);
    vec_scale_to_length(along, along, 1.0f);
    FastVecSub(delta, state + 0x1F0, entry + 0x10);
    delta[2] = 0;
    distance = FastVecDot(delta, across);
    if (distance > *(float *)(state + 0x218)) distance = *(float *)(state + 0x218);
    else if (distance < -*(float *)(state + 0x218)) distance = -*(float *)(state + 0x218);
    lerp_vector(point, entry + 0x10, entry + 0x20, *(float *)(state + 0x340));
    vec_scale_to_length(scaled, across, distance);
    FastVecAdd(point, point, scaled);
    FastVecSub(delta, state + 0x1F0, point);
    delta[2] = 0;
    side = FastVecDot(delta, along);
    if (vec_distance_xy(state + 0x1F0, point) < 6.0f) {
        float target = (side < 0.0f);
        ApproachValue(state + 0x340, target, 0.020000001f);
    }
    if (fast_vec_dist(entity + 0x10, point) >= 0.5f) {
        u8 *sound = g_sound_l03_slot_table + *(int *)(state + 0x350) * 0x70;
        if (*(u8 **)(sound + 0x88) != entity || !sound[0x74])
            *(int *)(state + 0x350) = PlayMobySound(0, 4, entity);
    } else {
        int slot = *(int *)(state + 0x350);
        if (slot != -1) {
            u8 *sound = g_sound_l03_slot_table + slot * 0x70;
            if (*(u8 **)(sound + 0x88) == entity && sound[0x74]) snd_stop_voice(slot);
        }
        *(int *)(state + 0x350) = -1;
    }
    moby_l01_turn_toward_target_pal(entity, point);
    *(int *)(state + 0x1A8) = 0;
}





