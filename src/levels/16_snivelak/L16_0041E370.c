#include "names.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;
extern void moby_set_state(char *, s32, s32);
extern s32 part_find_owned_effect_slot(char *, u32, s32);
extern char D_L16_001A8F20[] __attribute__((sda));
extern void part_spawn_masked_debris(f32, f32, f32, f32, char *, s32, char *, s32);
extern void PlayMobySound(s32, s32, char *);
extern void part_spawn_scaled_bolts(char *, s32, f32);
extern void vec_local_offset_to_world(char *, char *, f32, f32, f32);
extern void matrix_mul_vec3(char *, char *, char *);
extern void part_l01_spawn_spark_burst(f32, f32, f32, char *, char *, s32, u32, s32);
extern void moby_mark_spawned(char *);
typedef int effect_quad __attribute__((mode(TI)));

/* Waits for activation, emits a burst and removes the spent object. */
void triggered_l16_burst_update(char *self) {
    char direction[16];
    char position[16];
    switch (*(u8 *)(self + 0x20)) {
    case 0:
        moby_set_state(self, 1, -1);
        break;
    case 1:
        if (part_find_owned_effect_slot(self, 0x04010000, 0))
            moby_set_state(self, 2, -1);
        *(u8 *)(self + 0xA8) = 255;
        break;
    case 2:
        part_spawn_masked_debris(1.0f, 3.0f, 3.0f, 7.0f, self, 0x5F, D_L16_001A8F20, 255);
        PlayMobySound(0, 0, self);
        part_spawn_scaled_bolts(self, 1, 0.0f);
        *(effect_quad *)direction = 0;
        *(f32 *)(direction + 8) = 0.05000000447034836f;
        vec_local_offset_to_world(self, position, 0.0f, 0.0f, *(f32 *)(self + 0x2C) * 20.0f);
        matrix_mul_vec3(direction, direction, self + 0xC0);
        part_l01_spawn_spark_burst(0.006666667293f, 1.0f, 1.03f, position, direction, 10, 0x3F7FFF3F, 0);
        moby_mark_spawned(self);
        break;
    }
}
