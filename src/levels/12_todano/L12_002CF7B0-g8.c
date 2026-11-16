#include "include_asm.h"
#include "names.h"

extern int g_hero_l12_control_mode __attribute__((nosda));

extern int g_level_render_word __attribute__((nosda));

extern char *g_level_pointer_unused __attribute__((sda));

/* Clear the two flag bits on every object of the chain while a mode gate holds.
   Near miss: nonmatching/levels/func_L12_00388038.c */

extern int g_current_map_index;

extern void *tv_screen_find_nearest(float, float, float);

extern void matrix_mul_vec3(void *, void *, void *);

extern void FastVecScale(void *, void *, float);

extern void FastVecAdd(void *, void *, void *);

extern char g_trail_slice_mesh[];

extern int g_trail_slice_source __attribute__((sda));

typedef struct {
    char pad0[0x30];
    unsigned int mode;
    int count;
    char pad1[0x18];
    int mesh;
    char pad2[0x138];
    int *entries[4];
} L12_002FFF88_STATE;

extern L12_002FFF88_STATE g_trail_slice_state;

/* Builds the level's four trail slices for the mesh its state points at. */
void todano_build_trail_slice_meshes(void)
{
    int index;
    void *obj;
    float scale;
    char *srcRow;
    int i;
    int rowOffset;

    if (g_current_map_index != 12)
        return;

    obj = 0;
    index = -1;
    if (g_trail_slice_state.mode < 2) {
        obj = tv_screen_find_nearest(0.0f, 0.0f, 0.0f);
        index = 2;
    }
    if (index != -1 && obj != 0) {
        if (g_trail_slice_state.entries[index] != 0) {
            char *objPos = obj + 0x10;
            char *objRot = obj + 0xC0;
            g_trail_slice_state.mesh = (int)g_trail_slice_mesh;
            srcRow = (char *)&g_trail_slice_source;
            rowOffset = 0x20;
            i = 3;
            scale = *(float *)(obj + 0x2C) / *(float *)(*(int *)(obj + 0x24) + 0x24);
            for (; i >= 0; i--) {
                matrix_mul_vec3((char *)(g_trail_slice_state.mesh + rowOffset), srcRow, objRot);
                FastVecScale((char *)(g_trail_slice_state.mesh + rowOffset),
                              (char *)(g_trail_slice_state.mesh + rowOffset), scale);
                FastVecAdd((char *)(g_trail_slice_state.mesh + rowOffset),
                              (char *)(g_trail_slice_state.mesh + rowOffset), objPos);
                rowOffset += 0x10;
                srcRow += 0x10;
            }
            *(int *)(g_trail_slice_state.mesh + 0x68) = g_trail_slice_state.entries[index];
        }
    }
    if (g_trail_slice_state.mode == 0 && g_trail_slice_state.count >= 0x925)
        g_trail_slice_state.mesh = 0;
    if (g_trail_slice_state.mode == 1 && g_trail_slice_state.count < 0x3C)
        g_trail_slice_state.mesh = 0;
}

typedef int Quadword89F80 __attribute__((mode(TI)));

extern float FastVecDot(void *, void *);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void moby_set_state(void *, int, int);
extern int moby_transform_point_and_rotation_by_parent(void *, void *, void *, void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern int moby_is_state_two(char *);
extern char *ref_L12_00389F80_00 __attribute__((sda));
extern char *ref_L12_00389F80_01;
extern float ref_L12_00389F80_02 __attribute__((sda));
extern float ref_L12_00389F80_03 __attribute__((sda));

/* Moby class 4945 update. Per-state step of a homing object: state 0 starts it, state 1 steers it by the thing it
   follows (or just turns it) and then spins a short delay loop. */
void homing_follower_update(char *object) {
    char *state = *(char **)(object + 0x68);
    float targetOffset[4];
    float sideDir[4];
    float push[4];
    float sideSpeed;
    int spinCount;

    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        *(unsigned int *)(state + 0x5C) |= 4;
        *(short *)(object + 0x7C) = 3;
        moby_set_state(object, 1, -1);
        break;
    case 1:
        if (*(int *)(state + 0xE0) == -1 ||
            moby_is_state_two(ref_L12_00389F80_00 + (*(int *)(state + 0xE0) << 8)) == 0) {
            vec_scale_to_length(state + 0x30, object + 0xD0, -(ref_L12_00389F80_02 * 0.016666668f));
            *(float *)(object + 0x48) = ref_L12_00389F80_03;
        } else {
            moby_transform_point_and_rotation_by_parent(object, ref_L12_00389F80_01 + (*(int *)(state + 0xE0) << 8), object + 0x10,
                          object + 0xF0, targetOffset, sideDir);
            targetOffset[2] = 0.0f;
            FastVecSub(push, targetOffset, object + 0x10);
            *(Quadword89F80 *)targetOffset = *(Quadword89F80 *)push;
            targetOffset[2] = 0.0f;
            sideDir[0] = math_fast_sin_or_cos_a(*(float *)(object + 0xF8) + 4.7123895f);
            sideDir[1] = math_fast_sin_or_cos_b(*(float *)(object + 0xF8) + 4.7123895f);
            sideDir[2] = 0.0f;
            sideSpeed = FastVecDot(targetOffset, sideDir);
            push[0] = math_fast_sin_or_cos_a(*(float *)(object + 0xF8)) * sideSpeed * 0.1f;
            push[1] = math_fast_sin_or_cos_b(*(float *)(object + 0xF8)) * sideSpeed * 0.1f;
            push[2] = 0.0f;
            mat_combine_and_store(state + 0x20, push, object + 0xF0, object + 0xF0);
            *(float *)(object + 0x48) = sideSpeed * 59.999996f;
        }
        spinCount = 6;
        while (--spinCount >= 0)
            ;
        break;
    }
}
