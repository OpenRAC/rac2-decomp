#include "common.h"

/* D_L05_001B34E0 is read both ways: its first float through $gp (the _gp view, also the address passed to
   func_002833F0), the other fields absolutely. */
typedef struct { float x, y, z; int flags; } Rotation;
typedef struct { float x, y, z, w; } Vector;
typedef struct { Vector rows[3]; } Matrix;
extern int g_wobbling_light_slot __attribute__((sda));
extern char g_wobbling_light_table[];
extern Rotation g_wobbling_light_rotation;
extern Rotation D_L05_001B34E0_gp SDATA(D_L05_001B34E0);
extern Vector g_light_spot_sum;
extern float g_light_spot_count;
extern float FastAddRotations(float, float);
extern void vec_clear_128(void *);
extern void euler_rotation_basis(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void divide_vector_xyz(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);

/* Moves a small light next to the object with a wobble. When other objects have added to the shared light spot it also places a brighter, larger light there. */
void wobbling_light_update(char *object)
{
    Vector value;
    Matrix rotation;
    char *entry = g_wobbling_light_table + g_wobbling_light_slot * 32;
    char *position = object + 0x10;
    char *output = entry + 0x10;
    g_wobbling_light_rotation.flags = 0;
    D_L05_001B34E0_gp.x = FastAddRotations(D_L05_001B34E0_gp.x, 0.1f);
    g_wobbling_light_rotation.y = FastAddRotations(g_wobbling_light_rotation.y, 0.09f);
    g_wobbling_light_rotation.z = FastAddRotations(g_wobbling_light_rotation.z, 0.11f);
    vec_clear_128(&value);
    value.x = 0.4f;
    euler_rotation_basis(&rotation, &D_L05_001B34E0_gp);
    matrix_mul_vec3(&value, &value, &rotation);
    FastVecAdd(&value, &value, position);
    qcopy(output, &value);
    *(float *)(entry + 0x1C) = 3.0f;
    if (g_light_spot_count > 0.0f) {
        divide_vector_xyz(&g_light_spot_sum, &g_light_spot_sum, g_light_spot_count);
        FastVecSub(&g_light_spot_sum, &g_light_spot_sum, position);
        vec_scale_to_length(&g_light_spot_sum, &g_light_spot_sum, 5.0f);
        FastVecAdd(&g_light_spot_sum, &g_light_spot_sum, position);
        qcopy(output, &g_light_spot_sum);
        *(float *)(entry + 0x1C) = 10.0f;
    } else {
        *(float *)(entry + 0x1C) = 0.0f;
    }
    vec_clear_128(&g_light_spot_sum);
    g_light_spot_count = 0.0f;
}