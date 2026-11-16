#include "include_asm.h"
#include "names.h"

typedef float f32;
typedef int TI128 __attribute__((mode(TI)));
typedef struct {
    char pad[0xAA];
    short key;
} Obj_389848;
extern void level_list_add_key(Obj_389848 *);
extern void gfx_update_color_fade_pal(char *, char *);
extern void *part_find_owned_effect_slot(char *, int, int);
extern int FastDecTimer(void *);
extern f32 moby_update_aim_target_strength_pal(char *, char *);
extern int part_spawn_damage_debris_pal(char *, char *, char *);
extern void vec_scale_to_length(f32 *, char *, f32);
extern void FastVecAdd(f32 *, f32 *, f32 *);
extern void moby_mark_spawned(char *);
extern char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, int, int, int, int,
                          f32, f32);

/* Updates an enemy that decays: it loses health from its attached effects and explodes when
 * the health runs out (PAL). */
void decaying_enemy_update_pal(char *moby_arg)
{
    char *moby = moby_arg;
    char *vars;
    unsigned char state;
    char *effect;
    char *owner;
    f32 pos[4];
    f32 forward[4];
    f32 back[4];
    f32 scale;

    vars = *(char **)(moby + 0x68);
    state = *(unsigned char *)(moby + 0x20);
    switch (state) {
    case 0:
        level_list_add_key((Obj_389848 *)moby);
        *(unsigned char *)(moby + 0x20) = 1;
    case 1:
        gfx_update_color_fade_pal(moby, vars + 0x50);
        effect = (char *)part_find_owned_effect_slot(moby, 1, 0);
        if (FastDecTimer(vars + 0x26) == 0)
            effect = 0;
        if (effect != 0) {
            scale = *(f32 *)(effect + 0x2C);
            if (*(f32 *)(vars + 0xF8) != 0.0f) {
                owner = *(char **)(effect + 0x20);
                if (owner != 0 && *(short *)(moby + 0xAA) == *(short *)(owner + 0xAA))
                    *(f32 *)(effect + 0x2C) = scale * *(f32 *)(vars + 0xF8);
            }
        } else {
            effect = (char *)part_find_owned_effect_slot(moby, 0x10000, 0);
            if (effect != 0) {
                scale = *(f32 *)(effect + 0x2C);
                scale *= 0.5f;
                *(f32 *)(effect + 0x2C) = scale;
                if (*(f32 *)(vars + 0xF8) != 0.0f) {
                    owner = *(char **)(effect + 0x20);
                    if (owner != 0 && *(short *)(moby + 0xAA) == *(short *)(owner + 0xAA))
                        *(f32 *)(effect + 0x2C) = scale * *(f32 *)(vars + 0xF8);
                }
            }
        }
        scale = moby_update_aim_target_strength_pal(moby, effect);
        *(unsigned char *)(moby + 0xA8) = 0xFF;
        *(f32 *)(vars + 0x20) -= scale;
        part_spawn_damage_debris_pal(moby, vars + 0x100, vars + 0x20);
        if (*(f32 *)(vars + 0x20) <= 0.0f) {
            {
            f32 *v = pos;
            *(TI128 *)v = *(TI128 *)(moby + 0x10);
            }
            vec_scale_to_length(back, moby + 0xD0, -2.0f);
            FastVecAdd(pos, back, pos);
            vec_scale_to_length(forward, moby + 0xC0, 1.5f);
            FastVecAdd(pos, forward, pos);
            SpawnExplosion_pal(pos, 0, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1, 0, 0, 0,
                          0.75f, 20.0f);
            moby_mark_spawned(moby);
        }
    }
}
