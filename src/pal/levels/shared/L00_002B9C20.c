#include "include_asm.h"

#include "common.h"
typedef struct {
    short pending;
    short id;
    short timer;
    short arg;
} DelayedSlot_9CA8;
extern struct {
    u8 pad0[0x149D];
    u8 b149D;
    u8 pad149e[0x23EC - 0x149E];
    DelayedSlot_9CA8 slots[8];
} D_00189E20_9CA8;
extern void hero_play_footstep_sound_dust_pal(int, int, int, int);

/* Ticks the timer of each of the eight entries; one whose timer reports 2 is cleared and
   fires: id 0x16 calls func_PAL_L00_002A6058 with the resident byte at +0x149D, any other id
   goes to func_L00_002B9B88 with the entry's argument. */
void UpdateDelayedSounds_pal(void)
{
    int i;
    short id;

    for (i = 0; i < 8; i++) {
        if (FastDecTimer(&D_00189E20_9CA8.slots[i].timer) == 2) {
            id = D_00189E20_9CA8.slots[i].id;
            D_00189E20_9CA8.slots[i].pending = 0;
            if (id == 0x16)
                hero_play_footstep_sound_dust_pal(D_00189E20_9CA8.b149D, 1, 1, 0x32);
            else
                hero_play_sound(id, D_00189E20_9CA8.slots[i].arg);
        }
    }
}


extern char g_hero_position[];
extern int g_hero_ledge_move_flag;
extern void euler_to_matrix(void *a, void *b);
extern void euler_rotation_basis(void *a, void *b);
extern void hero_reset_speeds_and_vectors(void);
extern void level_release_slot_list(void *p);
extern void cancel_hero_item_animation_pal(void);
extern void attachment_reset_all(void);
extern s32 hero_l00_set_move_state_pal(int a0, int a1);
extern void anim_start_object_at_frame(int a0, int a1);
extern void hero_l00_update_ground_contact(void);
extern float fast_vec_dist(void *a, void *b);
extern void tracked_moby_set_state_pal(int a0, int a1);
extern void global_object_start_pal(void *a, int b);
extern void cam_reset_default(void);
extern void level_apply_nearest_env_preset(void *p);
typedef struct {
    u8 pad000[0x34E];
    short h34E;
    u8 pad350[0x3A0 - 0x350];
    int i3A0;
    int flags3A4;
    u8 pad3a8[0x2290 - 0x3A8];
    char *object;
    u8 pad2294[0x229C - 0x2294];
    int i229C;
    u8 pad22a0[0x24EF - 0x22A0];
    u8 b24EF;
} ResidentState_9D60;

/* Reset the hero position and direction, the resident movement state and the related level objects. */
void hero_reset_position_and_direction_pal(void *position, void *direction, int sound, int refresh)
{
    ResidentState_9D60 *res;
    char *hero = g_hero_position;

    qcopy(hero, position);
    res = (ResidentState_9D60 *)(hero - 0x80);
    qcopy(res->object + 0x10, position);
    qcopy(hero + 0x10, direction);

    euler_to_matrix(res, hero + 0x10);
    euler_rotation_basis(res->object + 0xC0, hero + 0x10);
    hero_reset_speeds_and_vectors();
    level_release_slot_list(hero + 0x1860);
    level_release_slot_list(hero + 0x19B0);

    res->flags3A4 &= ~1;
    res->flags3A4 &= ~2;
    res->h34E = 1;
    res->i3A0 = 0;
    res->b24EF = 0;

    cancel_hero_item_animation_pal();
    attachment_reset_all();

    if (sound != -1)
        hero_l00_set_move_state_pal(sound, 2);

    anim_start_object_at_frame(*(u8 *)(res->object + 0x43), *(u8 *)(res->object + 0x41));

    if (res->i229C == 0x11)
        g_hero_ledge_move_flag = 1;
    else
        g_hero_ledge_move_flag = 0;

    hero_l00_update_ground_contact();

    if (fast_vec_dist(g_hero_position, g_hero_position + 0x250) < 1.0f)
        qcopy(g_hero_position, g_hero_position + 0x250);

    tracked_moby_set_state_pal(0, 0);
    global_object_start_pal(0, 0);

    if (refresh != 0)
        cam_reset_default();

    level_apply_nearest_env_preset(*(void **)(g_hero_position + 0x2210));
}

