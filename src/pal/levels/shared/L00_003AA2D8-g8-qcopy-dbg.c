#include "include_asm.h"

#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
typedef struct { char pad[0x50]; float speed; char tail[0x8C]; } WeaponEntry;
typedef struct {
    char pad00[0x10];
    short frames, mode;
    float rate;
    short slot, handle;
    char *target;
    VectorBits velocity, origin;
} BeamState;
extern WeaponEntry g_weapon_l00_table[];
extern unsigned char g_beam_weapon_index[];
extern unsigned int g_beam_spawn_slot_counter __attribute__((sda));
extern char g_camera_l00_position[];
extern int save_is_record_value(int, int);
extern char *CreateMoby(int);
extern void vec_add_transformed_or_copy(void *, void *, void *);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern char *level_get_slot_body(int, int);
extern void cam_compute_view_direction(char *, char *, int);
extern void FastVecScale(void *, void *, float);
extern void moby_build_axis_vectors(char *, char *);
extern void func_PAL_L00_003AC5A8(void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern int beam_test_segment_hit_pal(char *, void *);

/* Spawn and configure one moving beam effect. */
char *func_PAL_L00_003AB368(void *position, void *velocity, int handle, int mode)
{
    float normal[4], previous[4];
    char *moby;
    BeamState *state;
    float speed;
    if (handle == -1 || !save_is_record_value(0x5CB, handle))
        return 0;
    moby = CreateMoby(0x5D6);
    if (moby != 0) {
        *(unsigned char *)(moby + 0x30) = 0xFF;
        *(unsigned short *)(moby + 0x32) = 0xFF;
        *(unsigned char *)(moby + 0x31) = 1;
        state = *(BeamState **)(moby + 0x68);
        qcopy(moby + 0x10, position);
        *(unsigned char *)(moby + 0x20) = 0;
        state->mode = mode;
        vec_add_transformed_or_copy(state, velocity, position);
        speed = (g_weapon_l00_table + g_beam_weapon_index[0])->speed * (0.020000001f);
        state->frames = ((s32)(FloatToInt(128.0f / speed)) * 5 + 2) / 6;
        state->rate = 1.0f / IntToFloat(state->frames);
        state->handle = handle;
        state->target = level_get_slot_body(0x5CB, handle);
        cam_compute_view_direction(moby + 0x10, (char *)normal, 1);
        FastVecScale(normal, normal, -1.0f);
        moby_build_axis_vectors(moby, (char *)normal);
        if (g_beam_spawn_slot_counter >= 4)
            g_beam_spawn_slot_counter = 0;
        state->slot = g_beam_spawn_slot_counter;
        g_beam_spawn_slot_counter = (int)(g_beam_spawn_slot_counter + 1) % 3;
        func_PAL_L00_003AC5A8(moby);
        if (mode == 1) {
            qcopy(&state->origin, g_camera_l00_position);
            vec_scale_to_length(&state->velocity, g_camera_l00_position + 0x230, FastVecLength(velocity));
        }
        if (mode == 2) {
            qcopy(previous, position);
            FastVecAdd(moby + 0x10, position, velocity);
            if (beam_test_segment_hit_pal(moby, previous))
                *(unsigned char *)(moby + 0x20) = 2;
        }
    }
    return moby;
}
