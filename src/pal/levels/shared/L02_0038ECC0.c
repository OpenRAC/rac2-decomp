#include "include_asm.h"
#include "names.h"



typedef unsigned char u8;
typedef unsigned int u32;
extern int g_current_map_index __attribute__((sda));
extern float g_hero_height_limit;
extern u8 g_sound_state[];
extern float g_camera_l02_position[4];
extern int PlayMobySound(int, int, char *);
extern int FastDecTimer(void *);
extern u32 FastTweenColor(u32, u32, float);
extern float fast_vec_dist(void *, void *);
extern void *part_spawn_object_following_effect(void *, void *, u32, int, int, float, float, int, int, int);

/* Keeps a lamp or glowing prop alive: plays its hum, blinks some kinds, and while the camera is
   near spawns the glow effects that follow the object. */
void update_lamp_glow_effects_pal(char *object) {
    char *data = *(char **)(object + 0x68);
    short kind = *(short *)(object + 0xAA);
    float distance;
    if (kind == 0x9B7 || kind == 0x9B0 || kind == 0xD2C || kind == 0xD5C) {
        if (g_current_map_index != 13) {
            char *event = (char *)g_sound_state + *(int *)(data + 0x18) * 0x70;
            if (*(char **)(event + 0x88) != object || !((u8 *)event)[0x74])
                *(int *)(data + 0x18) = PlayMobySound(0, 4, object);
        }
    }
    if (*(short *)(object + 0xAA) == 0xD2C) {
        if (FastDecTimer(data + 0x74)) {
            *(short *)(data + 0x74) = 29;
            *(int *)(data + 0x8C) = *(int *)(data + 0x8C) == 0;
        }
        *(u32 *)(object + 0x78) = FastTweenColor(*(u32 *)(object + 0x78), 0x50000046, 0.18f);
    }
    if (g_current_map_index == 13 && g_hero_height_limit > 89.0f)
        return;
    kind = *(short *)(object + 0xAA);
    switch (kind) {
    case 0x9B0:
        distance = fast_vec_dist(g_camera_l02_position, object + 0x10);
        if (distance < (float)*(int *)(data + 0x90)) {
            part_spawn_object_following_effect(data + 0x30, object, 0x40804040, -1, 0, *(float *)(data + 0x78) * 756000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
            part_spawn_object_following_effect(data + 0x40, object, 0x40804040, -1, 0, *(float *)(data + 0x78) * 756000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
            part_spawn_object_following_effect(data + 0x50, object, 0x40804040, -1, 0, *(float *)(data + 0x78) * 756000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
        }
        if (distance < (float)*(int *)(data + 0x94)) {
            part_spawn_object_following_effect(data + 0x30, object, 0x20804040, -1, 1, *(float *)(data + 0x78) * 777000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
            part_spawn_object_following_effect(data + 0x40, object, 0x20804040, -1, 1, *(float *)(data + 0x78) * 777000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
            part_spawn_object_following_effect(data + 0x50, object, 0x20804040, -1, 1, *(float *)(data + 0x78) * 777000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
        }
        break;
    case 0x9B7:
        distance = fast_vec_dist(g_camera_l02_position, object + 0x10);
        if (distance < (float)*(int *)(data + 0x90)) {
            part_spawn_object_following_effect(data + 0x30, object, 0x405696FF, -1, 0, *(float *)(data + 0x78) * 756000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
            part_spawn_object_following_effect(data + 0x40, object, 0x405696FF, -1, 0, *(float *)(data + 0x78) * 756000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
        }
        if (distance < (float)*(int *)(data + 0x94)) {
            part_spawn_object_following_effect(data + 0x30, object, 0x205696FF, -1, 1, *(float *)(data + 0x78) * 777000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
            part_spawn_object_following_effect(data + 0x40, object, 0x205696FF, -1, 1, *(float *)(data + 0x78) * 777000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
        }
        break;
    case 0xB15:
        distance = fast_vec_dist(g_camera_l02_position, object + 0x10);
        if (distance < (float)*(int *)(data + 0x90)) {
            part_spawn_object_following_effect(data + 0x30, object, 0x405696FF, -1, 0, *(float *)(data + 0x78) * 756000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
            part_spawn_object_following_effect(data + 0x40, object, 0x405696FF, -1, 0, *(float *)(data + 0x78) * 756000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
        }
        if (distance < (float)*(int *)(data + 0x94)) {
            part_spawn_object_following_effect(data + 0x30, object, 0x205696FF, -1, 1, *(float *)(data + 0x78) * 777000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
            part_spawn_object_following_effect(data + 0x40, object, 0x205696FF, -1, 1, *(float *)(data + 0x78) * 777000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
        }
        break;
    case 0x134B:
        distance = fast_vec_dist(g_camera_l02_position, object + 0x10);
        if (distance < (float)*(int *)(data + 0x90)) {
            part_spawn_object_following_effect(data + 0x30, object, 0x40804040, -1, 0, *(float *)(data + 0x78) * 340200.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
            part_spawn_object_following_effect(data + 0x40, object, 0x40804040, -1, 0, *(float *)(data + 0x78) * 340200.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
        }
        if (distance < (float)*(int *)(data + 0x94)) {
            part_spawn_object_following_effect(data + 0x30, object, 0x20804040, -1, 1, *(float *)(data + 0x78) * 194250.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
            part_spawn_object_following_effect(data + 0x40, object, 0x20804040, -1, 1, *(float *)(data + 0x78) * 194250.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
        }
        break;
    case 0xB13:
        distance = fast_vec_dist(g_camera_l02_position, object + 0x10);
        if (distance < (float)*(int *)(data + 0x90)) {
            part_spawn_object_following_effect(data + 0x30, object, 0x40804040, -1, 0, *(float *)(data + 0x78) * 756000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
            part_spawn_object_following_effect(data + 0x40, object, 0x40804040, -1, 0, *(float *)(data + 0x78) * 756000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
        }
        if (distance < (float)*(int *)(data + 0x94)) {
            part_spawn_object_following_effect(data + 0x30, object, 0x20804040, -1, 1, *(float *)(data + 0x78) * 777000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
            part_spawn_object_following_effect(data + 0x40, object, 0x20804040, -1, 1, *(float *)(data + 0x78) * 777000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
        }
        break;
    case 0xD5C:
        distance = fast_vec_dist(g_camera_l02_position, object + 0x10);
        if (distance < (float)*(int *)(data + 0x90)) {
            part_spawn_object_following_effect(data + 0x30, object, 0x40804040, -1, 0, *(float *)(data + 0x78) * 756000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
            part_spawn_object_following_effect(data + 0x40, object, 0x40804040, -1, 0, *(float *)(data + 0x78) * 756000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
        }
        if (distance < (float)*(int *)(data + 0x94)) {
            part_spawn_object_following_effect(data + 0x30, object, 0x20804040, -1, 1, *(float *)(data + 0x78) * 777000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
            part_spawn_object_following_effect(data + 0x40, object, 0x20804040, -1, 1, *(float *)(data + 0x78) * 777000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
        }
        break;
    case 0x127D:
        distance = fast_vec_dist(g_camera_l02_position, object + 0x10);
        if (distance < (float)*(int *)(data + 0x90)) {
            part_spawn_object_following_effect(data + 0x30, object, 0x40202080, -1, 0, *(float *)(data + 0x78) * 294000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
            part_spawn_object_following_effect(data + 0x40, object, 0x40202080, -1, 0, *(float *)(data + 0x78) * 294000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
        }
        if (distance < (float)*(int *)(data + 0x94)) {
            part_spawn_object_following_effect(data + 0x30, object, 0x205696FF, -1, 1, *(float *)(data + 0x78) * 231000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
            part_spawn_object_following_effect(data + 0x40, object, 0x205696FF, -1, 1, *(float *)(data + 0x78) * 231000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
        }
        break;
    case 0x1290:
        distance = fast_vec_dist(g_camera_l02_position, object + 0x10);
        if (distance < (float)*(int *)(data + 0x90)) {
            part_spawn_object_following_effect(data + 0x30, object, 0x40804020, -1, 0, *(float *)(data + 0x78) * 210000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
            part_spawn_object_following_effect(data + 0x40, object, 0x40804020, -1, 0, *(float *)(data + 0x78) * 210000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
            part_spawn_object_following_effect(data + 0x50, object, 0x40804020, -1, 0, *(float *)(data + 0x78) * 210000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
        }
        if (distance < (float)*(int *)(data + 0x94)) {
            part_spawn_object_following_effect(data + 0x30, object, 0x20905010, -1, 1, *(float *)(data + 0x78) * 210000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
            part_spawn_object_following_effect(data + 0x40, object, 0x20905010, -1, 1, *(float *)(data + 0x78) * 210000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
            part_spawn_object_following_effect(data + 0x50, object, 0x20905010, -1, 1, *(float *)(data + 0x78) * 210000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
        }
        break;
    }
}


