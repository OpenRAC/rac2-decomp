#include "include_asm.h"

#include "common.h"
typedef int Vector __attribute__((mode(TI)));
extern float g_sliding_platform_local_offset[4] __attribute__((sda));
extern void moby_set_state(char *, int, int);
extern void func_PAL_002A7E68(char *, int, int, int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char *CreateMoby(int);
extern void moby_transform_joint_to_world(char *, int, char *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void func_002A0F48(char *);
extern void mat_normalize_columns(void *);
extern void func_002A10E8(char *);
extern int flag_set_first_pending(char *);
extern int FastDecTimer(void *);
extern float IntToFloat(int);
extern void chainblade_release_held_actors_pal(char *);

void sliding_l02_platform_update_pal(char *self) {
    float offset[4] __attribute__((aligned(16)));
    /* Separate initial and final query events use four measured local vectors. */
    float updated[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float transformed[4] __attribute__((aligned(16)));
    char *state = *(char **)(self + 0x68);
    Vector *source;
    Vector *destination;
    int i;
    qcopy(offset, self + 0x10);
    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        *(int *)(state + 0x10) = 0;
        *(int *)(state + 0x14) = 0;
        *(int *)(state + 0x18) = 0;
        moby_set_state(self, 2, -1);
        if (*(unsigned char *)(self + 0x43) != 0) func_PAL_002A7E68(self, 0, 0, 0);
        *(float *)(self + 0x48) = 0.0f;
        vec_scale_to_length(updated, self + 0xD0, 2.0f);
        FastVecAdd(self + 0x10, self + 0x10, updated);
        qcopy(state, self + 0x10);
        *(char **)(state + 0x1C) = CreateMoby(0x1172);
        if (*(char **)(state + 0x1C) == 0) return;
        *(unsigned short *)(*(char **)(state + 0x1C) + 0x34) |= 0x41;
        *(unsigned char *)(*(char **)(state + 0x1C) + 0x30) = *(unsigned char *)(self + 0x30);
        *(short *)(*(char **)(state + 0x1C) + 0x32) = 0;
        moby_transform_joint_to_world(self, 0, (char *)position);
        matrix_mul_vec3(transformed, g_sliding_platform_local_offset, self + 0xC0);
        FastVecAdd(position, transformed, position);
        {
            char *child = *(char **)(state + 0x1C);
            qcopy(child + 0x10, position);
            func_002A0F48(child);
        }
        {
            Vector *row = (Vector *)(self + 0xC0);
            Vector *out = (Vector *)(*(char **)(state + 0x1C) + 0xC0);
            int count = 0;
            do {
                qcopy(out, row);
                count++;
                row++;
                out++;
            } while (count < 3);
        }
        mat_normalize_columns(*(char **)(state + 0x1C) + 0xC0);
        func_002A10E8(*(char **)(state + 0x1C));
        *(unsigned short *)(*(char **)(state + 0x1C) + 0x34) |= 6;
        break;
    case 1:
        if (flag_set_first_pending(self)) *(short *)(state + 0x22) = 16;
        if (!FastDecTimer(state + 0x22)) {
            vec_scale_to_length(updated, self + 0xD0, 2.0f / IntToFloat(16));
            FastVecAdd(self + 0x10, self + 0x10, updated);
        }
        if (*(unsigned char *)(self + 0x60) & 2) {
            qcopy(self + 0x10, state);
            *(float *)(self + 0x48) = 0.0f;
            moby_set_state(self, 2, -1);
        }
        break;
    case 3:
        if (flag_set_first_pending(self)) *(short *)(state + 0x22) = 16;
        if (!FastDecTimer(state + 0x22)) {
            vec_scale_to_length(updated, self + 0xD0, -2.0f / IntToFloat(16));
            FastVecAdd(self + 0x10, self + 0x10, updated);
        }
        if (*(unsigned char *)(self + 0x60) & 2) {
            *(float *)(self + 0x48) = 0.0f;
            moby_set_state(self, 4, -1);
        }
        break;
    case 4:
        moby_set_state(self, 5, -1);
        *(float *)(self + 0x48) = 1.0f;
        if (*(unsigned char *)(self + 0x43) != 1) func_PAL_002A7E68(self, 1, 0, 0);
        chainblade_release_held_actors_pal(self);
        break;
    case 5:
        if (*(unsigned char *)(self + 0x60) & 2) {
            *(short *)(state + 0x20) = 75;
            *(float *)(self + 0x48) = 0.0f;
            moby_set_state(self, 6, -1);
        }
        break;
    case 6:
        if (!*(short *)(state + 0x20)) {
        *(float *)(self + 0x48) = 1.0f;
        if (*(unsigned char *)(self + 0x43) != 2) func_PAL_002A7E68(self, 2, 0, 0);
        moby_set_state(self, 7, -1);
        } else {
            FastDecTimer(state + 0x20);
        }
        break;
    case 7:
        if (*(unsigned char *)(self + 0x60) & 2) {
            if (*(unsigned char *)(self + 0x43) != 3) func_PAL_002A7E68(self, 3, 0, 0);
            moby_set_state(self, 1, -1);
        }
        break;
    }
    if (*(char **)(state + 0x1C) && *(float *)(self + 0x48) != 0.0f) {
        moby_transform_joint_to_world(self, 0, (char *)updated);
        matrix_mul_vec3(position, g_sliding_platform_local_offset, self + 0xC0);
        FastVecAdd(updated, position, updated);
        {
            char *child = *(char **)(state + 0x1C);
            qcopy(child + 0x10, updated);
            func_002A0F48(child);
        }
        {
        char *childMatrix = *(char **)(state + 0x1C);
        source = (Vector *)(self + 0xC0);
        destination = (Vector *)(childMatrix + 0xC0);
        for (i = 0; i < 3; i++) {
            *destination = *source;
            source++;
            destination++;
        }
        mat_normalize_columns(childMatrix + 0xC0);
        }
        func_002A10E8(*(char **)(state + 0x1C));
        *(unsigned short *)(*(char **)(state + 0x1C) + 0x34) |= 6;
    }
}
