#include "include_asm.h"
#include "names.h"


typedef unsigned char u8;
typedef unsigned short u16;
struct Fx {
    char pad[0x18];
    u8 kind;
    u8 sub;
    u16 id;
    char pad2[0x14];
};
struct Ent {
    int used;
    u8 mode;
    char pad[0xDB];
};
struct Globals {
    char pad[0x18];
    char *hero;
};
extern struct Globals g_collision_result;
extern char *g_collision_hero_owner;
extern u8 g_selected_weapon_index;
extern struct Ent g_weapon_l00_table[];
extern int CollLine(void *, void *, int, void *, int);
extern void vec_scale_to_length(void *, void *, float);
extern void make_hit_descriptor(void *, void *, float, int, void *);
extern void QueueMobyImpact(void *, void *);
extern int StartAttachedEffect_pal(void *, int, int);
extern void sheep_shot_spawn_hit_sparks_pal(void *, int, int);
extern int snd_play_from_class_bank(int, int, void *, int);

/* Checks if a sheep shot hit something on its way. If it did, it hurts the target, makes sparks and starts to blow up. */
void sheep_shot_resolve_hit_pal(char *moby, void *old_position) {
    char *st = *(char **)(moby + 0x68);
    float vec[4];
    struct Fx fx;
    struct Ent *weapon_entry;
    float scale;
    int is2;
    int is3;
    char *pos = moby + 0x10;

    if (CollLine(old_position, pos, 0, moby, 0) == 0) {
        return;
    }
    if (g_collision_result.hero != 0 && g_collision_result.hero != g_collision_hero_owner &&
        (*(short *)(*(char **)(g_collision_result.hero + 0x24) + 0x46) == 5 ||
         (*(u16 *)(g_collision_result.hero + 0x34) & 0x4000) != 0)) {
        vec_scale_to_length(vec, st, 1.0f);
        weapon_entry = &g_weapon_l00_table[g_selected_weapon_index];
        scale = 1.0f;
        is2 = weapon_entry->used != 0 && weapon_entry->mode == 2;
        if (is2) {
            scale = 10.0f;
        }
        is3 = weapon_entry->used != 0 && weapon_entry->mode == 3;
        if (is3) {
            scale = 15.0f;
        }
        make_hit_descriptor(&fx, moby, scale, 0x210000, vec);
        fx.sub = 3;
        fx.kind = 5;
        fx.id = *(u16 *)(moby + 0xAA);
        QueueMobyImpact(g_collision_result.hero, &fx);
        StartAttachedEffect_pal(g_collision_result.hero, 0x4E, *(int *)(*(char **)(st + 0x20) + 0xB8));
        sheep_shot_spawn_hit_sparks_pal(pos, 0xA, 1);
    }
    if (g_collision_result.hero == 0) {
        sheep_shot_spawn_hit_sparks_pal(moby + 0x10, 0xF, 0);
    }
    snd_play_from_class_bank(7, 0, moby, 0xE79);
    moby[0x20] = 2;
}

