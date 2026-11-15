#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef float f32;
typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    char pad[0xAA];
    short key;
} Obj_389848;

extern void level_list_add_key(Obj_389848 *);

extern void gfx_update_color_fade(char *, char *);

extern void *part_find_owned_effect_slot(char *, int, int);

extern int FastDecTimer(void *);

extern f32 moby_update_aim_target_strength(char *, char *);

extern int part_spawn_damage_debris(char *, char *, char *);

extern void vec_scale_to_length(f32 *, char *, f32);

extern void FastVecAdd(f32 *, f32 *, f32 *);

extern void moby_mark_spawned(char *);

extern char *SpawnExplosion(void *, int, int, int, int, int, int, int, int, int, int, int,
                          f32, f32);

/* Updates an enemy that loses health over time, and makes a small explosion and removes it when its health runs out. */
void decaying_enemy_update(char *a0)
{
    char *self = a0;
    char *ctl;
    unsigned char state;
    char *child;
    char *obj;
    f32 vec[4];
    f32 tmp1[4];
    f32 tmp2[4];
    f32 scale;

    ctl = *(char **)(self + 0x68);
    state = *(unsigned char *)(self + 0x20);
    switch (state) {
    case 0:
        level_list_add_key((Obj_389848 *)self);
        *(unsigned char *)(self + 0x20) = 1;
    case 1:
        gfx_update_color_fade(self, ctl + 0x50);
        child = (char *)part_find_owned_effect_slot(self, 1, 0);
        if (FastDecTimer(ctl + 0x26) == 0)
            child = 0;
        if (child != 0) {
            scale = *(f32 *)(child + 0x2C);
            if (*(f32 *)(ctl + 0xF8) != 0.0f) {
                obj = *(char **)(child + 0x20);
                if (obj != 0 && *(short *)(self + 0xAA) == *(short *)(obj + 0xAA))
                    *(f32 *)(child + 0x2C) = scale * *(f32 *)(ctl + 0xF8);
            }
        } else {
            child = (char *)part_find_owned_effect_slot(self, 0x10000, 0);
            if (child != 0) {
                scale = *(f32 *)(child + 0x2C);
                scale *= 0.5f;
                *(f32 *)(child + 0x2C) = scale;
                if (*(f32 *)(ctl + 0xF8) != 0.0f) {
                    obj = *(char **)(child + 0x20);
                    if (obj != 0 && *(short *)(self + 0xAA) == *(short *)(obj + 0xAA))
                        *(f32 *)(child + 0x2C) = scale * *(f32 *)(ctl + 0xF8);
                }
            }
        }
        scale = moby_update_aim_target_strength(self, child);
        *(unsigned char *)(self + 0xA8) = 0xFF;
        *(f32 *)(ctl + 0x20) -= scale;
        part_spawn_damage_debris(self, ctl + 0x100, ctl + 0x20);
        if (*(f32 *)(ctl + 0x20) <= 0.0f) {
            {
            f32 *v = vec;
            *(TI128 *)v = *(TI128 *)(self + 0x10);
            }
            vec_scale_to_length(tmp2, self + 0xD0, -2.0f);
            FastVecAdd(vec, tmp2, vec);
            vec_scale_to_length(tmp1, self + 0xC0, 1.5f);
            FastVecAdd(vec, tmp1, vec);
            SpawnExplosion(vec, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1, 0, 0, 0,
                          0.75f, 20.0f);
            moby_mark_spawned(self);
        }
    }
}
