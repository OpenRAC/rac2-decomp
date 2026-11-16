#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
extern void moby_set_state(char *, int, int);
extern float math_random_float_range(float,float);
extern int func_0035CBA0(char *,int,int);
extern void FastVecScale(void *,void *,float);
extern void FastVecSub(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern void func_00350388(char *);
extern void *part_spawn_object_following_effect(void *,void *,unsigned int,int,int,int,int,int,float,float);
extern void part_explode_object_into_pieces(void *,void *,void *,void *,int,int,int,int,int,int,int);
extern void part_spawn_scaled_bolts(char *,int,float);
extern void moby_compute_local_point(char *,void *,float,float,float);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void SpawnTintedEffects(char *,void *,int,float,int,void *,float,unsigned int,float,float,int);
extern char g_debris_param_b[] SDATA(D_L06_001B1C08);
extern char g_debris_param_c[] SDATA(D_L06_001B1C00);
extern char g_debris_param_a[] SDATA(D_L06_001B1C10);
extern char g_effect_vector[] MACRO_ADDR;
extern int g_debris_piece_color __attribute__((sda));

/* Updates a breakable object: once hit it throws out debris and sparks, then removes itself. */
void breakable_l06_debris_update(char *obj)
{
    float pos[4], vec_a[4], vec_b[4], vec_c[4];
    char *vars = *(char **)(obj + 0x68);
    char *hit;
    int state = *(unsigned char *)(obj + 0x20);
    int i;

    *(Quad *)vec_a = 0;
    vec_a[2] = *(float *)(obj + 0x2C) * 21.5f;
    *(Quad *)pos = *(Quad *)vec_a;
    switch (state) {
    case 0:
        part_spawn_object_following_effect(pos, obj, 0x50801420, -1, 0, -1, 0, 96, 430500.0f, 0.0f);
        part_spawn_object_following_effect(pos, obj, 0x40801420, -1, 1, -1, 0, 96, 73500.0f, 0.75f);
        moby_set_state(obj, 1, -1);
        break;
    case 1:
        hit = func_0035CBA0(obj, 0x4010000, 0);
        if (hit && !*(int *)vars) {
            *(Quad *)vec_a = 0;
            vec_a[1] = vec_a[0] = 3.0f;
            *(float *)(hit + 0x18) = 0.75f;
            FastVecScale(vec_b, hit + 0x10, math_random_float_range(6.0f, 8.0f));
            qcopy(vec_c, vec_b);
            FastVecSub(vec_b, vec_b, vec_a);
            FastVecAdd(vec_c, vec_c, vec_a);
            part_explode_object_into_pieces(obj, vec_b, g_debris_param_b, g_debris_param_c,
                             65535, -1, g_debris_piece_color, 9, state, 255, 0);
            moby_set_state(obj, 2, -1);
        }
        ((unsigned char *)obj)[0xA8] = 255;
        break;
    case 2:
        part_explode_object_into_pieces(obj, g_debris_param_a, g_debris_param_b, g_debris_param_c,
                         65535, 0, g_debris_piece_color, 7, 62, 255, 0);
        part_spawn_scaled_bolts(obj, 1, pos[2] * 0.33333334f);
        moby_compute_local_point(obj, vec_a, pos[0], pos[1], pos[2]);
        SpawnExplosionEffects(obj, g_effect_vector, vec_a, 0, 0, 8, 3, 3, 0, 0, 9, 0.35f,
                      -1, 0, 0, 0, -1, 0, 0x810001);
        for (i = 0; i < 4; i++) {
            vec_b[0] = (i / 2 * 2 - 1) * 0.0166666675f;
            vec_b[1] = (i % 2 * 2 - 1) * 0.0166666675f;
            vec_b[2] = 0.1166666746f;
            matrix_mul_vec3(vec_b, vec_b, obj + 0xC0);
            SpawnTintedEffects(obj, vec_a, 3, 0, 1, vec_b, 5, 0x7FFF8080, 0.45f, 0.6f, 0);
        }
        func_00350388(obj);
        break;
    }
}
