#include "include_asm.h"
#include "names.h"

/* func_US2_L00_003EC540, the USA v2.00 copy of func_L00_003EB0C0: the same C, where the entry
   count drops from 80 to 79 and the freed slot (0x40 + 79 * 0x50 = 0x18F0) keeps the z read at
   init, which replaces the -1.0f passed to func_002AEE70. */

extern int g_tutorial_points;

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
    float first_angle;
    float first_velocity;
    float second_angle;
    float second_velocity;
    float first_speed;
    float first_step;
    float second_speed;
    float second_step;
    char entries[0x4A];
    unsigned char present;
    char pad_8B[2];
    unsigned char update;
    char pad_8E[0x1862];
    float start_z;
} L00_003EC540_State;

/* Spins a set of attached parts around one or two axes, driven by the tutorial point counter (US2: 79 parts). */
void rotating_parts_update_us2(char *moby)
{
    float angles[4];
    char matrix[48];
    L00_003EC540_State *vars = *(L00_003EC540_State **)(moby + 0x68);
    int i;
    int last_flag;

    switch (*(unsigned char *)(moby + 0x20)) {
    case 0:
        if (vars->id == -1)
            break;
        {
            /* An int, not a byte constant: reload would otherwise reuse the -1 still in $v0. */
            int alpha = 255;
            *(unsigned char *)(moby + 0x30) = alpha;
        }
        BuildObjectAttachmentTransforms(moby, vars->entries, 0x4F, *((int *)&vars->id + 1), *(int *)&vars->id, vars->flags, 7, 0);
        if (!vars->present) {
            moby_mark_spawned(moby);
            break;
        }
        if (!vars->mode) {
            vars->update = 1;
            *(unsigned short *)(moby + 0x34) |= 0x104;
            euler_rotation_basis(moby + 0xC0, moby + 0xF0);
        }
        vars->start_z = *(float *)(moby + 0x18);
        if (vars->first_angle != 0.0f)
            vars->first_angle *= 0.01745329424738884f;
        vars->first_velocity = math_fast_sin_or_cos_b(vars->first_angle) * vars->first_speed;
        moby[0x20] = 1;
        break;
    case 1:
        if (g_tutorial_points != vars->level)
            break;
        if (vars->first_step > 0.0f)
            math_update_wrapped_angle_offset(moby, &vars->first_angle, &vars->first_velocity, vars->first_speed,
                          vars->first_step * 0.0002908882452175021f, vars->start_z);
        if (vars->second_step > 0.0f) {
            moby_scale_owner_words_by_angles(moby, vars->second_speed * 0.01745329424738884f, &vars->second_angle,
                          vars->second_step * 0.0002908882452175021f, &vars->second_velocity, 0.00581776537001133f);
            if (vars->update)
                euler_rotation_basis(moby + 0xC0, moby + 0xF0);
        }
        if (!vars->mode) {
            angles[0] = vars->angles[0] * 0.0002908882452175021f;
            angles[1] = vars->angles[1] * 0.0002908882452175021f;
            angles[2] = vars->angles[2] * 0.0002908882452175021f;
            euler_rotation_basis(matrix, angles);
            multiply_matrix3x3(moby + 0xC0, moby + 0xC0, matrix);
            if (vars->second_step > 0.0f)
                mat_get_euler_angles(moby + 0xC0, moby + 0xF0);
        } else {
            i = 0;
            do {
                angles[0] = vars->angles[0] * 0.0002908882452175021f;
                angles[1] = vars->angles[1] * 0.0002908882452175021f;
                angles[2] = vars->angles[2] * 0.0002908882452175021f;
                euler_rotation_basis(matrix, angles);
                multiply_matrix3x3(vars->entries + i * 0x50, vars->entries + i * 0x50, matrix);
                last_flag = *(unsigned char *)(vars->entries + i * 0x50 + 0x4A);
                i++;
            } while (last_flag != 1);
        }
        moby_update_attached_transforms(moby, vars->entries);
        break;
    }
}
