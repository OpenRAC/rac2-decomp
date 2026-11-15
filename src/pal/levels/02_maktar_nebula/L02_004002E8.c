#include "include_asm.h"
#include "names.h"

typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
extern char *g_moby_l02_pool __attribute__((sda));
extern u32 g_entity_group_lists[];
extern void enemy_release_effect_record(char *);
extern void chainblade_reset_to_idle(char *);
extern void brawler_switch_off_actor(char *);
extern void actor_tear_down(char *);
extern void flamethrower_robot_knock_out(char *);
extern void blade_ball_explode(char *);
extern char *g_moby_l02_pool __attribute__((sda));
extern u32 g_entity_group_lists[];
extern char *g_moby_l02_pool __attribute__((sda));
extern u32 g_entity_group_lists[];
extern void enemy_release_effect_record(char *);
extern void chainblade_reset_to_idle(char *);
extern void brawler_switch_off_actor(char *);
extern void actor_tear_down(char *);
extern void flamethrower_robot_knock_out(char *);
extern void blade_ball_explode(char *);
extern char *g_moby_l02_pool __attribute__((section(".sdata")));
extern s16 moby_get_vars_counter(char *);

/* Walks the 16-bit stream the object's table entry points at and calls the handler of the
   entity type each word names; a negative word ends the stream. */
void func_PAL_L02_004002E8(char *a0) {
    char *state = *(char **)(a0 + 0x68);
    u32 index = *(u32 *)(state + 0x40);
    u32 entry;
    short *p;
    char *rec;
    s16 type;

    if (index == 0xFF)
        return;
    entry = g_entity_group_lists[index];
    if (entry == 0)
        return;
    p = (short *)entry;
    do {
        rec = g_moby_l02_pool + ((*(u16 *)p & 0x7FFF) << 8);
        type = *(s16 *)(rec + 0xAA);
        switch (type) {
        case 0x9CA:
            enemy_release_effect_record(rec);
            break;
        case 0xB22:
            actor_tear_down(rec);
            break;
        case 0xC3B:
            flamethrower_robot_knock_out(rec);
            break;
        case 0xC3E:
            blade_ball_explode(rec);
            break;
        case 0x9F8:
            chainblade_reset_to_idle(rec);
            break;
        case 0xA44:
            brawler_switch_off_actor(rec);
            break;
        }
    } while (*p++ >= 0);
}

