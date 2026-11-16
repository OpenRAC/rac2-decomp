#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
extern int PlayMobySound(int index, int a1, char *a2);
extern u8 D_001A63A8_4[];
extern int math_random_int_below(int a0);
extern u8 g_hero_state[];
extern void moby_mark_spawned(void *);
extern void *part_find_owned_effect_slot(void *a0, int a1, int a2);
extern int math_random_int_below(int a0);
extern int snd_play_from_class_bank(int index, int value, char *object, int kind);
extern void part_spawn_explosion_with_sparks_pal(void *a0, void *a1, int a2, float f12, float f13);
extern int PlayMobySound(int index, int a1, char *a2);
extern void vec_scale_to_length(float *a0, void *a1, float f12);
extern void part_spawn_masked_debris_pal(void *a0, int a1, void *a2, unsigned char a3,
                           float f12, float f13, float f14, float f15);
extern void moby_mark_spawned(void *object);
extern void moby_explode(u8 *a0, int a1, int a2);

/* Blows the object up: plays a random sound, adds an effect and a burst of sparks, then removes it. (PAL copy) */
void moby_explode_pal(u8 *moby, int arg1, int arg2) {
    u8 *obj = moby;
    void *owned_slot;
    int sound_base;
    int sound_bank;
    float velocity[4];

    owned_slot = part_find_owned_effect_slot(moby, -1, 0);
    if (owned_slot == 0)
        return;
    if (*(short *)(obj + 0xAA) == 0x1213) {
        sound_base = 0xB;
        sound_bank = 0xF7F;
    } else {
        sound_base = 0xC;
        sound_bank = 0xE0B;
    }
    snd_play_from_class_bank(sound_base + math_random_int_below(3), 0, obj, sound_bank);
    part_spawn_explosion_with_sparks_pal(obj, obj + 0x10, -1, 2.0f, 13.0f);
    PlayMobySound(0, 0, obj);
    vec_scale_to_length(velocity, owned_slot + 0x10, 0.28000003f);
    part_spawn_masked_debris_pal(obj, 3, velocity, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
    moby_mark_spawned(obj);
}
