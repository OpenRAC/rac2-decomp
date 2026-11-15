#include "common.h"

typedef int L13_TI128 __attribute__((mode(TI)));

extern char *CreateMoby(int);
extern float mat_fast_helper_a(float, float);
extern float FastAddRotations(float, float);
extern float vec_length_xy(char *);
extern float math_random_angle(void);
extern void math_apply_axis_rotation_to_quat(char *, char *, char *, float);
extern void euler_rotation_basis(char *, char *);
extern float math_random_float_range(float, float);
/* The EE passes the seven integer and three float arguments in separate banks. */
extern void *part_spawn_ground_effect(void *, int, int, float, int, int, int, float, float, int);
extern int PlayMobySound(int, int, char *);

extern float D_L13_001B1360 __attribute__((sda));
extern int D_L13_001B1308 __attribute__((sda));
extern int D_L13_001B130C __attribute__((sda));
extern char D_L13_001A8F20[] __attribute__((sda));

typedef struct {
    unsigned char pad00[0x20];
    unsigned char active;
    unsigned char pad21[2];
    unsigned char opacity;
    unsigned char pad24[8];
    float scale;
    unsigned char alpha, enabled;
    unsigned short color, flags;
} DCObject;
/* Creates a projectile moby of class 3751 at the given position, aimed along the given direction, and starts its launch effects. */
char *SpawnEA7Moby(char *owner, char *direction, char *position, int unused, float speed)
{
    float angle, scale;
    char *p = position;
    char *q = owner;
    char *entity = CreateMoby(0xEA7 /* moby class 3751 */);

    if (entity != 0) {
        *(unsigned char *)(entity + 0x30) = 0xFF;
        *(unsigned short *)(entity + 0x32) = 0xFF;
        *(unsigned char *)(entity + 0x31) = 1;
        *(unsigned char *)(entity + 0x20) = 0;
        *(long long *)(entity + 0x38) = *(long long *)(q + 0x38);
        *(L13_TI128 *)(entity + 0x10) = *(L13_TI128 *)p;
        p = *(char **)(entity + 0x68);
        *(L13_TI128 *)p = *(L13_TI128 *)direction;
        *(char **)(p + 0x10) = q;
        *(float *)(p + 0x14) = speed;
        *(float *)(p + 0x20) = 0.1500000059604645f;
        ((DCObject *)entity)->flags |= 0x208;

        *(float *)(entity + 0xF8) =
            FastAddRotations(mat_fast_helper_a(*(float *)(direction + 0), *(float *)(direction + 4)), 1.5707964906692505f);
        *(float *)(entity + 0xF0) = -mat_fast_helper_a(vec_length_xy(direction), *(float *)(direction + 8));
        angle = math_random_angle();

        q = entity + 0xC0;
        math_apply_axis_rotation_to_quat(entity + 0xE0, entity + 0xE0, entity + 0xD0, angle);
        math_apply_axis_rotation_to_quat(q, q, entity + 0xD0, angle);
        euler_rotation_basis(q, entity + 0xF0);

        ((DCObject *)entity)->opacity = 0x80;
        ((DCObject *)entity)->flags |= 0x100;
        ((DCObject *)entity)->scale = D_L13_001B1360;
        *(int *)(p + 0x24) = 0;
        scale = math_random_float_range(8.0f, 10.0f);
        part_spawn_ground_effect(entity + 0x10, 0xF, D_L13_001B1308, scale * 0.30000001192092896f, 0, 0xA,
                    (int)D_L13_001A8F20, scale, 0.0f, 0);
        part_spawn_ground_effect(entity + 0x10, 0xF, D_L13_001B130C, scale * 0.03999999910593033f, 1, -0xA,
                    (int)D_L13_001A8F20, scale * 0.4000000059604645f, 0.0f, 0);
        PlayMobySound(0, 0, entity);
    }
    return entity;
}
