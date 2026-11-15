#include "include_asm.h"
#include "names.h"

/* func_PAL_L00_003EF3D8, the PAL copy of func_L00_003EB0C0: the same C at 50 Hz (rates scale
   by 6/5), where the entry count goes from 80 to 79 and the freed last slot, entries + 79 * 0x50,
   keeps the object's height, which replaces -1.0f as func_002AEE70's last argument. */

extern int D_L00_001C9340;

extern void BuildObjectAttachmentTransforms(char *, void *, int, int, int, int, int, int);

extern void moby_mark_spawned(char *);

extern void euler_rotation_basis(void *, void *);

extern float math_fast_sin_or_cos_b(float);

extern void math_update_wrapped_angle_offset(char *, void *, void *, float, float, float);

extern void moby_scale_owner_words_by_angles(char *, float, void *, float, void *, float);

extern void multiply_matrix3x3(void *, void *, void *);

extern void mat_get_euler_angles(void *, void *);

extern void moby_update_attached_transforms(char *, void *);

typedef struct {
    long long id;
    int flags;
    int level;
    float angles[3];
    int mode;
    float firstAngle;
    float firstVelocity;
    float secondAngle;
    float secondVelocity;
    float firstSpeed;
    float firstStep;
    float secondSpeed;
    float secondStep;
    char entries[0x4A];
    unsigned char present;
    char pad_8B[2];
    unsigned char update;
    char pad_8E[0x18F0 - 0x8E];
    float height;
} L00_003EB0C0_State;

void func_PAL_L00_003EF3D8(char *self)
{
    float angles[4];
    char mat[48];
    L00_003EB0C0_State *st = *(L00_003EB0C0_State **)(self + 0x68);
    int i;
    int last;

    switch (*(unsigned char *)(self + 0x20)) {
    case 0:
        if (st->id == -1)
            break;
        {
            /* An int, not a byte constant: reload would otherwise reuse the -1 still in $v0. */
            int alpha = 255;
            *(unsigned char *)(self + 0x30) = alpha;
        }
        BuildObjectAttachmentTransforms(self, st->entries, 79, *((int *)&st->id + 1), *(int *)&st->id, st->flags, 7, 0);
        if (!st->present) {
            moby_mark_spawned(self);
            break;
        }
        if (!st->mode) {
            st->update = 1;
            *(unsigned short *)(self + 0x34) |= 0x104;
            euler_rotation_basis(self + 0xC0, self + 0xF0);
        }
        st->height = *(float *)(self + 0x18);
        if (st->firstAngle != 0.0f)
            st->firstAngle *= 0.01745329424738884f;
        st->firstVelocity = math_fast_sin_or_cos_b(st->firstAngle) * st->firstSpeed;
        self[0x20] = 1;
        break;
    case 1:
        if (D_L00_001C9340 != st->level)
            break;
        if (st->firstStep > 0.0f)
            math_update_wrapped_angle_offset(self, &st->firstAngle, &st->firstVelocity, st->firstSpeed,
                          st->firstStep * 0.0003490659f, st->height);
        if (st->secondStep > 0.0f) {
            moby_scale_owner_words_by_angles(self, st->secondSpeed * 0.01745329424738884f, &st->secondAngle,
                          st->secondStep * 0.0003490659f, &st->secondVelocity, 0.0069813184f);
            if (st->update)
                euler_rotation_basis(self + 0xC0, self + 0xF0);
        }
        if (!st->mode) {
            angles[0] = st->angles[0] * 0.0003490659f;
            angles[1] = st->angles[1] * 0.0003490659f;
            angles[2] = st->angles[2] * 0.0003490659f;
            euler_rotation_basis(mat, angles);
            multiply_matrix3x3(self + 0xC0, self + 0xC0, mat);
            if (st->secondStep > 0.0f)
                mat_get_euler_angles(self + 0xC0, self + 0xF0);
        } else {
            i = 0;
            do {
                angles[0] = st->angles[0] * 0.0003490659f;
                angles[1] = st->angles[1] * 0.0003490659f;
                angles[2] = st->angles[2] * 0.0003490659f;
                euler_rotation_basis(mat, angles);
                multiply_matrix3x3(st->entries + i * 0x50, st->entries + i * 0x50, mat);
                last = *(unsigned char *)(st->entries + i * 0x50 + 0x4A);
                i++;
            } while (last != 1);
        }
        moby_update_attached_transforms(self, st->entries);
        break;
    }
}
