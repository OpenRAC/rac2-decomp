#include "include_asm.h"
#include "names.h"
typedef int TI128 __attribute__((mode(TI)));
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern char g_hero_position[];
extern char g_hero_state[];
extern char *g_hero_moby;
extern int g_enemy_relocate_slot_count __attribute__((sda));
extern int g_boss_part_index __attribute__((sda));
extern int g_enemy_relocate_count __attribute__((sda));
extern void *D_L23_002AB170[];
extern void mothership_project_point_onto_surface(char *, float);
extern int math_random_int_below(int);
extern void boss_find_nearest_path_point(char *, char *, int);
extern void enemy_reset_calm(char *);
extern void moby_set_state(char *, int, int);
extern void moby_play_anim_and_link(char *, int, int, int, int, float);

/* Eight ways to place the offset vector v[6] (which of the two vectors at 0xC0 and 0xD0 of the
   target, or the average of two of them), picked by func_002A77E0(8). The dispatch reads the
   level's own jump table (eight code addresses in the level's data at 0x2AB170); `cases` only
   keeps the labels alive. */
void enemy_relocate_near_hero_pal(char *arg0) {
    static void *cases[8] = {&&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7};
    char *state = *(char **)(arg0 + 0x68);
    TI128 v[7];
    unsigned int sel;

    v[1] = *(TI128 *)g_hero_position;
    mothership_project_point_onto_surface((char *)&v[1], 0.0f);
    FastVecScale((char *)&v[0], *(char **)(g_hero_position + 0x2210) + 0xE0, -80.0f);
    sel = math_random_int_below(8);
    if (sel < 8)
        goto *D_L23_002AB170[sel];
    goto tail;
c0:
    FastVecScale((char *)&v[6], g_hero_moby + 0xC0, 50.0f);
    goto tail;
c1:
    FastVecScale((char *)&v[6], g_hero_moby + 0xC0, -50.0f);
    goto tail;
c2:
    FastVecScale((char *)&v[6], g_hero_moby + 0xD0, 50.0f);
    goto tail;
c3:
    FastVecScale((char *)&v[6], g_hero_moby + 0xD0, -50.0f);
    goto tail;
c4: {
    char *b = g_hero_state;

    FastVecScale((char *)&v[4], *(char **)(b + 0x2290) + 0xD0, 50.0f);
    FastVecScale((char *)&v[2], *(char **)(b + 0x2290) + 0xC0, 50.0f);
    FastVecAdd((char *)&v[6], (char *)&v[4], (char *)&v[2]);
    FastVecScale((char *)&v[6], (char *)&v[6], 0.5f);
    goto tail;
}
c5: {
    char *b = g_hero_state;

    FastVecScale((char *)&v[2], *(char **)(b + 0x2290) + 0xC0, 50.0f);
    FastVecScale((char *)&v[5], *(char **)(b + 0x2290) + 0xD0, -50.0f);
    FastVecAdd((char *)&v[6], (char *)&v[2], (char *)&v[5]);
    FastVecScale((char *)&v[6], (char *)&v[6], 0.5f);
    goto tail;
}
c6: {
    char *b = g_hero_state;

    FastVecScale((char *)&v[5], *(char **)(b + 0x2290) + 0xD0, -50.0f);
    FastVecScale((char *)&v[3], *(char **)(b + 0x2290) + 0xC0, -50.0f);
    FastVecAdd((char *)&v[6], (char *)&v[5], (char *)&v[3]);
    FastVecScale((char *)&v[6], (char *)&v[6], 0.5f);
    goto tail;
}
c7: {
    char *b = g_hero_state;

    FastVecScale((char *)&v[3], *(char **)(b + 0x2290) + 0xC0, -50.0f);
    FastVecScale((char *)&v[4], *(char **)(b + 0x2290) + 0xD0, 50.0f);
    FastVecAdd((char *)&v[6], (char *)&v[3], (char *)&v[4]);
    FastVecScale((char *)&v[6], (char *)&v[6], 0.5f);
}
tail:
    FastVecAdd((char *)&v[0], (char *)&v[0], (char *)&v[6]);
    FastVecAdd((char *)&v[0], (char *)&v[0], (char *)&v[1]);
    boss_find_nearest_path_point(arg0 + 0x10, (char *)&v[0], 1);
    mothership_project_point_onto_surface(arg0 + 0x10, 0.0f);
    *(TI128 *)(state + 0x290) = *(TI128 *)(arg0 + 0x10);
    enemy_reset_calm(arg0);
    moby_set_state(arg0, 5, 0);
    moby_play_anim_and_link(arg0, 3, 0, 0x11, 3, 1.0f);
    g_boss_part_index = (g_boss_part_index + 1) % g_enemy_relocate_slot_count;
    g_enemy_relocate_count = g_enemy_relocate_count + 1;
}
