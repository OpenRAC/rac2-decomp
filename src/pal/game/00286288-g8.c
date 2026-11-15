#include "include_asm.h"
#include "names.h"

extern char D_L00_001B8FF0[];
extern void multiply_matrix3x3(char *a, char *b, char *c);
extern void vec_set_direction_with_complement(char *a, char *b, float f);
extern void quaternion_to_rotation_basis(char *a, char *b);
extern float D_L00_001A8DD0 __attribute__((sda));

void func_PAL_00288638(float *arg0) { char temp[0x40]; float value = *arg0 * 0.0003490659f * D_L00_001A8DD0; vec_set_direction_with_complement(temp, D_L00_001B8FF0, value); quaternion_to_rotation_basis(temp, temp + 0x10); multiply_matrix3x3(D_L00_001B8FF0, temp + 0x10, D_L00_001B8FF0); }

typedef struct { char pad[48]; } Block48_F8c659bbc;
typedef struct { char pad[16]; } Block16_F8c659bbc;
extern char D_L00_001B1B10[] __attribute__((sda));
extern char g_camera_l00_position[];
extern char D_L00_001A8E30 __attribute__((sda));
extern void FastVecSub(char *a, char *b, char *c);
extern void vec_scale_to_length(char *a, char *b, float f);
extern void euler_rotation_basis(char *a, char *b);
extern void FastVecCross(char *a, char *b, char *c);
extern float FastVecLength(char *a);
extern void math_approach_target_with_braking(char *a, float f1, float f2, float f3, float f4);

void func_PAL_002884F0(char *arg0, int arg1)
{
    Block48_F8c659bbc a;
    Block48_F8c659bbc b;
    Block48_F8c659bbc c;
    Block16_F8c659bbc d;
    Block16_F8c659bbc e;
    float v;

    FastVecSub((char *)&e, g_camera_l00_position, D_L00_001B1B10);
    vec_scale_to_length((char *)&e, (char *)&e, 1.0f);
    euler_rotation_basis((char *)&c, (char *)&D_L00_001A8E30);
    multiply_matrix3x3((char *)&b, g_camera_l00_position + 560, (char *)&c);
    FastVecCross((char *)&d, (char *)&b, (char *)&e);
    v = FastVecLength((char *)&d) * 0.5f;
    if (arg1 != 0) {
        vec_set_direction_with_complement((char *)&d, (char *)&d, -v);
    } else {
        math_approach_target_with_braking(arg0, v, 0.0008377582f,
                0.0008377582f,
                0.062831864f);
        vec_set_direction_with_complement((char *)&d, (char *)&d, -*(float *)arg0);
    }
    quaternion_to_rotation_basis((char *)&d, (char *)&a);
    multiply_matrix3x3(D_L00_001B8FF0, (char *)&a, D_L00_001B8FF0);
}
