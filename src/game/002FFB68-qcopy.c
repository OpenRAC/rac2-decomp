#include "include_asm.h"
#include "common.h"

typedef float V4_F2FFB68[4] __attribute__((aligned(16)));

extern s16 g_effect_object_id MACRO_ADDR;
extern char g_weapon_table[];
extern char g_hero_state[];

/* Hero fields: a word in each 0x50-byte record from 0x1220 and a word table at 0x22E4. */
typedef struct { u8 pad[0x1220]; s32 word; } HeroRec50;
typedef struct { u8 pad[0x22E4]; s32 word[1]; } HeroTable;
extern s32 g_menu_choice_table[] MACRO_ADDR;

extern void shop_setup_preview_object(void);
extern void moby_mark_spawned(void *);
extern s32 load_is_class_cached(s32);
extern void LoadClassIntoFreeCacheSlot(s32);
extern s16 snd_pump_music_and_disc_read(s32);
extern void SwitchCachedDiscAsset(s32);
extern char *part_init_shared_effect_object(s32, s32);

/* Spawns the object for the current mode and hands it the caller's position and rotation. */
char *part_spawn_mode_effect_object(char *obj)
{
    V4_F2FFB68 pos, rot;
    s32 mode = -1;
    s16 id = g_effect_object_id;
    char *rec;
    char *spawned;
    s32 slot;

    qcopy(pos, obj + 0x10);
    qcopy(rot, obj + 0xF0);
    if (id == 0x4D || id == 0x6B || id == 0x6C) {
        shop_setup_preview_object();
        mode = 0;
    } else if (id == 0x3D || id == 0x49 || id == 0x5D || id == 0x5E) {
        shop_setup_preview_object();
        mode = 1;
    } else {
        moby_mark_spawned(obj);
        rec = g_weapon_table + id * 0xE0;
        if (load_is_class_cached(*(s32 *)(rec + 0x14)) == 0) {
            LoadClassIntoFreeCacheSlot(*(s32 *)(rec + 0x14));
            snd_pump_music_and_disc_read(1);
        }
        SwitchCachedDiscAsset(*(s32 *)(rec + 0x14));
    }
    rec = g_weapon_table + id * 0xE0;
    spawned = part_init_shared_effect_object(*(s32 *)(rec + 0x14), mode);
    if (spawned != 0) {
        qcopy(spawned + 0x10, pos);
        qcopy(spawned + 0xF0, rot);
        if (mode < 0) {
            slot = *(s32 *)(rec + 0xC);
            g_menu_choice_table[slot] = 0;
            ((HeroRec50 *)(g_hero_state + slot * 0x50))->word = 0;
            ((HeroTable *)g_hero_state)->word[slot] = 0;
        }
    }
    return spawned;
}
