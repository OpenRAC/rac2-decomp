#include "include_asm.h"
#include "names.h"

/* func_L16_002F60B8 has a unit of its own (-G8, the quadword copy profile, gcse on): retail
   keeps the scene's %hi in $s7 for the whole body and adds %lo at each use, which is gcse's
   hoisted high part; D_001A79F0 is a bare symbol, $gp in the annulled slot and absolute after
   the first loop. In the particle loop one size variable carries both calls' pair of sizes:
   being set twice, loop does not hoist the constants (retail rebuilds each in $f12 and copies
   it to $f13), and the step call comes before the count decrement, which fills its slot. */

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
extern SnivelakScene g_snivelak_scene;
extern float g_snivelak_room_fade;
/* Partial view of the position and transform used by the scene effect. */
typedef struct {
    float position[4];
    unsigned char pad10[0x220];
    float matrix[16];
} SceneEffectTransform;
extern SceneEffectTransform g_scene_origin_transform;
extern char g_particle_template[] __attribute__((sda));
typedef struct { unsigned char prefix[0xD4]; u8 *material; } SceneEffectMaterial;
extern SceneEffectMaterial g_scene_effect_material;
extern void anim_start_startup_animations(void);
extern void UpdateEquipmentPieces(char *);
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
extern void part_spawn_masked_debris(char *, int, void *, float, float, float, float, u8);
extern void moby_mark_spawned(char *);

/* Updates the boss room scene each frame and spawns the smoke and flash effects at the key moments. */
void snivelak_room_scene_update(void)
{
    union { Quadword q; float f[4]; } position;
    float orientation[16], step[4], randomPosition[4];
    char *object;
    int i = 0;
    anim_start_startup_animations();
    for (; i < g_snivelak_scene.objectCount; i++) {
        char *entry = g_snivelak_scene.objects[i];
        if (entry && *(short *)(entry + 0xaa) == 0xe29)
            *(u16 *)(entry + 0x34) |= 0x800;
        if (*(short *)(entry + 0xaa) == 0xd54)
            UpdateEquipmentPieces(entry);
        if (entry && *(short *)(entry + 0xaa) == 4000 && *(char **)(entry + 0x68))
            math_store_angle_update_result(entry, (float *)(*(char **)(entry + 0x68) + 12), 0x80aaaad2, 0x80396464, 0.06108653545379639f);
    }
    if (g_current_map_index[0] == 16 && g_snivelak_scene.state == 1) {
        object = g_snivelak_scene.objects[6];
        *(int *)(object + 0x78) = 0xff0020ff;
        *(u16 *)(object + 0x34) |= 16;
        if (subtract_integer_with_clamp(g_snivelak_scene.frame - 0x334) < 4) {
            float fade = (float)subtract_integer_with_clamp(g_snivelak_scene.frame - 0x334) * 0.333f;
            if (fade > 1.0f) fade = 1.0f;
            else if (fade < 0.0f) fade = 0.0f;
            g_snivelak_room_fade = 1.0f - fade;
        }
        if (g_snivelak_scene.frame == 0x336) {
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
                part_spawn_gravity_fade(randomPosition, g_particle_template, 20, 0x808080, random, 127, 0, scale, scale, 0.0f, 0);
                scale = 273000.0f;
                particle = part_spawn_gravity_fade(&position, g_particle_template, 30, 0x406080, random, 16, 0, scale, scale, 0.0f, 0);
                if (particle) particle[2] = *g_scene_effect_material.material;
                FastVecAdd(&position, &position, step);
                particleIndex--;
            } while (particleIndex >= 0);
        } else if (g_snivelak_scene.frame == 0x366) {
            object = CreateMoby(0xa79);
            if (object) {
                moby_init_child_from_parent(object, 0);
                moby_set_light_color(object, 0x80000000);
                *(float *)(object + 0x2c) = *(float *)(*(char **)(object + 0x24) + 0x24) * 0.333f;
                position.q = 0;
                position.f[0] = -3.0f;
                position.f[1] = 2.0f;
                matrix_mul_vec3(&position, &position, g_scene_origin_transform.matrix);
                FastVecAdd(&position, &position, g_scene_origin_transform.position);
                *(Quadword *)(object + 0x10) = position.q;
                part_spawn_masked_debris(object, 0xfff, g_particle_template, 3.0f, 9.0f, -3.0f, 3.0f, 255);
                part_spawn_masked_debris(object, 0xfff, g_particle_template, 3.0f, 9.0f, -3.0f, 3.0f, 255);
                moby_mark_spawned(object);
            }
        }
    }
}
