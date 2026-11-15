#include "include_asm.h"
#include "names.h"

/* func_L23_003C1B58 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it. */

typedef int TI128 __attribute__((mode(TI)));

extern void FastVecScale(void *, void *, float);

extern void FastVecAdd(void *, void *, void *);

extern char g_hero_position[];

extern char g_hero_state[];

extern char *g_hero_moby;

extern int D_L23_001B1644 __attribute__((sda));

extern int D_L23_001B164C __attribute__((sda));

extern int D_L23_001B36AC __attribute__((sda));

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
/* Moves the enemy to a random spot near the hero and restarts its attack. The spawn counters go up by one. */
void enemy_relocate_near_hero(char *moby) {
    static void *cases[8] = {&&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7};
    char *vars = *(char **)(moby + 0x68);
    TI128 vec[7];
    unsigned int choice;

    vec[1] = *(TI128 *)g_hero_position;
    mothership_project_point_onto_surface((char *)&vec[1], 0.0f);
    FastVecScale((char *)&vec[0], *(char **)(g_hero_position + 0x2210) + 0xE0, -80.0f);
    choice = math_random_int_below(8);
    if (choice < 8)
        goto *D_L23_002AB170[choice];
    goto tail;
c0:
    FastVecScale((char *)&vec[6], g_hero_moby + 0xC0, 50.0f);
    goto tail;
c1:
    FastVecScale((char *)&vec[6], g_hero_moby + 0xC0, -50.0f);
    goto tail;
c2:
    FastVecScale((char *)&vec[6], g_hero_moby + 0xD0, 50.0f);
    goto tail;
c3:
    FastVecScale((char *)&vec[6], g_hero_moby + 0xD0, -50.0f);
    goto tail;
c4: {
    char *heroBase = g_hero_state;

    FastVecScale((char *)&vec[4], *(char **)(heroBase + 0x2290) + 0xD0, 50.0f);
    FastVecScale((char *)&vec[2], *(char **)(heroBase + 0x2290) + 0xC0, 50.0f);
    FastVecAdd((char *)&vec[6], (char *)&vec[4], (char *)&vec[2]);
    FastVecScale((char *)&vec[6], (char *)&vec[6], 0.5f);
    goto tail;
}
c5: {
    char *heroBase = g_hero_state;

    FastVecScale((char *)&vec[2], *(char **)(heroBase + 0x2290) + 0xC0, 50.0f);
    FastVecScale((char *)&vec[5], *(char **)(heroBase + 0x2290) + 0xD0, -50.0f);
    FastVecAdd((char *)&vec[6], (char *)&vec[2], (char *)&vec[5]);
    FastVecScale((char *)&vec[6], (char *)&vec[6], 0.5f);
    goto tail;
}
c6: {
    char *heroBase = g_hero_state;

    FastVecScale((char *)&vec[5], *(char **)(heroBase + 0x2290) + 0xD0, -50.0f);
    FastVecScale((char *)&vec[3], *(char **)(heroBase + 0x2290) + 0xC0, -50.0f);
    FastVecAdd((char *)&vec[6], (char *)&vec[5], (char *)&vec[3]);
    FastVecScale((char *)&vec[6], (char *)&vec[6], 0.5f);
    goto tail;
}
c7: {
    char *heroBase = g_hero_state;

    FastVecScale((char *)&vec[3], *(char **)(heroBase + 0x2290) + 0xC0, -50.0f);
    FastVecScale((char *)&vec[4], *(char **)(heroBase + 0x2290) + 0xD0, 50.0f);
    FastVecAdd((char *)&vec[6], (char *)&vec[3], (char *)&vec[4]);
    FastVecScale((char *)&vec[6], (char *)&vec[6], 0.5f);
}
tail:
    FastVecAdd((char *)&vec[0], (char *)&vec[0], (char *)&vec[6]);
    FastVecAdd((char *)&vec[0], (char *)&vec[0], (char *)&vec[1]);
    boss_find_nearest_path_point(moby + 0x10, (char *)&vec[0], 1);
    mothership_project_point_onto_surface(moby + 0x10, 0.0f);
    *(TI128 *)(vars + 0x290) = *(TI128 *)(moby + 0x10);
    enemy_reset_calm(moby);
    moby_set_state(moby, 5, 0);
    moby_play_anim_and_link(moby, 3, 0, 0x14, 3, 1.0f);
    D_L23_001B164C = (D_L23_001B164C + 1) % D_L23_001B1644;
    D_L23_001B36AC = D_L23_001B36AC + 1;
}
