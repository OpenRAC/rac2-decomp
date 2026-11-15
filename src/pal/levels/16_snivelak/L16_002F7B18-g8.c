#include "include_asm.h"
#include "names.h"

/* func_PAL_L16_002F7B18, the PAL copy of func_L16_002F60B8: the same C, where the frame numbers
   820, 822 and 870 and the particle lifetimes 20 and 30 go through the 50 Hz scale, the effect
   call's 0.0610865f becomes 0.0733038f, func_002E64A0 and func_002B0A68 take their PAL names,
   and PAL adds the D_001A79F0 test. That test takes the first loop to 51 RTL insns; with `id` set
   before the load, 4000 has the lifetime for loop's first pass, so it stays ahead of the giv init
   while 0x33 waits for the second pass. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef int Quadword __attribute__((mode(TI)));
extern int g_current_map_index[] __attribute__((sda));
typedef struct SnivelakScene {
    unsigned char pad0[0x30];
    int state;
    int frame;
    unsigned char pad38[0xC];
    short objectCount;
    unsigned char pad46[0x146];
    char *objects[0];
} SnivelakScene;
extern SnivelakScene D_L16_001BD800;
extern float D_L16_001B2564;
/* Partial view of the position and transform used by the scene effect. */
typedef struct {
    float position[4];
    unsigned char pad10[0x220];
    float matrix[16];
} SceneEffectTransform;
extern SceneEffectTransform D_L16_001B9B00;
extern char D_L16_001A8F20[] __attribute__((sda));
typedef struct { unsigned char prefix[0xD4]; u8 *material; } SceneEffectMaterial;
extern SceneEffectMaterial D_L16_001FF680;
extern void anim_start_startup_animations(void);
extern void func_PAL_002E7270(char *);
extern void math_store_angle_update_result(char *, float *, int, int, float);
extern int subtract_integer_with_clamp(int);
extern void moby_transform_joint_point(char *, int, char *);
extern void transform_vector(void *, void *, void *);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern float math_random_signed_float_range(float, float);
extern int math_random_int_below(int);
extern char *part_spawn_gravity_fade(void *, void *, int, int, int, int, int, float, float, float, int);
extern char *CreateMoby(short);
extern void moby_init_child_from_parent(char *, char *);
extern void moby_set_light_color(void *, int);
extern void matrix_mul_vec3(void *, void *, void *);
extern void func_PAL_002B15D8(char *, int, void *, float, float, float, float, u8);
extern void moby_mark_spawned(char *);

void func_PAL_L16_002F7B18(void)
{
    union { Quadword q; float f[4]; } position;
    float orientation[16], step[4], randomPosition[4];
    char *object;
    int i = 0;
    anim_start_startup_animations();
    for (; i < D_L16_001BD800.objectCount; i++) {
        char *entry = D_L16_001BD800.objects[i];
        if (entry && *(short *)(entry + 0xaa) == 0xe29)
            *(u16 *)(entry + 0x34) |= 0x800;
        if (*(short *)(entry + 0xaa) == 0xd54)
            func_PAL_002E7270(entry);
        if (entry) {
            int id = 4000;
            if (*(short *)(entry + 0xaa) == id && g_current_map_index[0] != 0x33 && *(char **)(entry + 0x68))
                math_store_angle_update_result(entry, (float *)(*(char **)(entry + 0x68) + 12), 0x80aaaad2, 0x80396464, 0.07330384f);
        }
    }
    if (g_current_map_index[0] == 16 && D_L16_001BD800.state == 1) {
        object = D_L16_001BD800.objects[6];
        *(int *)(object + 0x78) = 0xff0020ff;
        *(u16 *)(object + 0x34) |= 16;
        if (subtract_integer_with_clamp(D_L16_001BD800.frame - 683) < 4) {
            float fade = (float)subtract_integer_with_clamp(D_L16_001BD800.frame - 683) * 0.333f;
            if (fade > 1.0f) fade = 1.0f;
            else if (fade < 0.0f) fade = 0.0f;
            D_L16_001B2564 = 1.0f - fade;
        }
        if (D_L16_001BD800.frame == 685) {
            int particleIndex;
            position.q = 0;
            position.f[0] = 0.2f;
            position.f[3] = 1.0f;
            moby_transform_joint_point(object, 0, (char *)orientation);
            transform_vector(&position, &position, orientation);
            FastVecScale(step, orientation + 8, 0.15f);
            FastVecAdd(&position, &position, step);
            FastVecScale(step, orientation + 8, -0.03333333507180214f);
            particleIndex = 29;
            do {
                int random;
                float scale;
                char *particle;
                randomPosition[0] = position.f[0] + math_random_signed_float_range(0.0f, 0.05f);
                randomPosition[1] = position.f[1] + math_random_signed_float_range(0.0f, 0.05f);
                randomPosition[2] = position.f[2] + math_random_signed_float_range(0.0f, 0.05f);
                random = math_random_int_below(255);
                scale = 42000.0f;
                part_spawn_gravity_fade(randomPosition, D_L16_001A8F20, 17, 0x808080, random, 127, 0, scale, scale, 0.0f, 0);
                scale = 273000.0f;
                particle = part_spawn_gravity_fade(&position, D_L16_001A8F20, 25, 0x406080, random, 16, 0, scale, scale, 0.0f, 0);
                if (particle) particle[2] = *D_L16_001FF680.material;
                FastVecAdd(&position, &position, step);
                particleIndex--;
            } while (particleIndex >= 0);
        } else if (D_L16_001BD800.frame == 725) {
            object = CreateMoby(0xa79);
            if (object) {
                moby_init_child_from_parent(object, 0);
                moby_set_light_color(object, 0x80000000);
                *(float *)(object + 0x2c) = *(float *)(*(char **)(object + 0x24) + 0x24) * 0.333f;
                position.q = 0;
                position.f[0] = -3.0f;
                position.f[1] = 2.0f;
                matrix_mul_vec3(&position, &position, D_L16_001B9B00.matrix);
                FastVecAdd(&position, &position, D_L16_001B9B00.position);
                *(Quadword *)(object + 0x10) = position.q;
                func_PAL_002B15D8(object, 0xfff, D_L16_001A8F20, 3.0f, 9.0f, -3.0f, 3.0f, 255);
                func_PAL_002B15D8(object, 0xfff, D_L16_001A8F20, 3.0f, 9.0f, -3.0f, 3.0f, 255);
                moby_mark_spawned(object);
            }
        }
    }
}
