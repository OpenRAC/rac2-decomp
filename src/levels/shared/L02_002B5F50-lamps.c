#include "names.h"
#include "moby_classes.h"
/* Model-specific lamp glow rendering; calls retain all eight GPR inputs. */
typedef unsigned char u8;
typedef unsigned int u32;
extern int g_current_map_index __attribute__((sda));
extern float D_00189EA8;
extern u8 g_sound_state[];
extern float g_camera_l02_position[4];
extern int PlayMobySound(int, int, char *);
extern int FastDecTimer(void *);
extern u32 FastTweenColor(u32, u32, float);
extern float fast_vec_dist(void *, void *);
/* Retail consumes all eight GPR inputs, including the culling range in t3. */
extern void *part_spawn_object_following_effect(void *, void *, u32, int, int, float, float, int, int, int);

/* Draws the glow of lamp-style mobys and plays their hum sound. */
void UpdateLampGlowEffects(char *object) {
    char *data = *(char **)(object + 0x68);
    short kind = *(short *)(object + 0xAA);
    float distance;
    if (kind == MOBY_CLASS_SCENERY_SHIP || kind == 0x9B0 /* moby class 2480 */ || kind == 0xD2C /* moby class 3372 */ || kind == MOBY_CLASS_TRAIN_WITH_RAIL) {
        if (g_current_map_index != 13) {
            char *event = (char *)g_sound_state + *(int *)(data + 0x18) * 0x70;
            if (*(char **)(event + 0x88) != object || !((u8 *)event)[0x74])
                *(int *)(data + 0x18) = PlayMobySound(0, 4, object);
        }
    }
    if (*(short *)(object + 0xAA) == 0xD2C /* moby class 3372 */) {
        if (FastDecTimer(data + 0x74)) {
            *(short *)(data + 0x74) = 35;
            *(int *)(data + 0x8C) = *(int *)(data + 0x8C) == 0;
        }
        *(u32 *)(object + 0x78) = FastTweenColor(*(u32 *)(object + 0x78), 0x50000046, 0.15f);
    }
    if (g_current_map_index == 13 && D_00189EA8 > 89.0f)
        return;
    kind = *(short *)(object + 0xAA);
    switch (kind) {
    case 0x9B0 /* moby class 2480 */:
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
    case MOBY_CLASS_SCENERY_SHIP:
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
    case 0xB15 /* moby class 2837 */:
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
    case 0x134B /* moby class 4939 */:
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
    case 0xB13 /* moby class 2835 */:
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
    case MOBY_CLASS_TRAIN_WITH_RAIL:
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
    case 0x127D /* moby class 4733 */:
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
    case 0x1290 /* moby class 4752 */:
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
