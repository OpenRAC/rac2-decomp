#include "names.h"
/* Select camera collision masks from the hero state, location and ground selectors. */
typedef struct {
    unsigned char a[0x80];
    float x, y;
    unsigned char b[0x2a8];
    float water;
    unsigned char c[0x1160];
    unsigned char flags[9];
    unsigned char d[0xdf7];
    int mode;
    int e;
    int state;
}
HeroView;
extern HeroView g_hero_state;
extern char D_001B53A0[];
extern int D_001B1510 __attribute__((section(".sdata")));
extern int D_001B1514 __attribute__((section(".sdata")));
extern int D_001B150C __attribute__((sda));
extern int g_current_map_index __attribute__((section(".sdata")));
extern float D_001B5348[];
/* Chooses which things the camera collides with, based on what the hero is doing. */
void cam_select_coll_masks(void) {
    HeroView *hero = &g_hero_state;
    char *camState = D_001B53A0;
    D_001B1510 = 20;
    if ((unsigned)(hero->state-17)<2 || hero->mode==112) D_001B1510 = 52;
    {
        HeroView *heroWater = &g_hero_state;
        if (heroWater->state!=17 && heroWater->water<D_001B5348[0]) D_001B1510 = 20;
    }
    if (g_current_map_index==6) {
        HeroView *heroArea = &g_hero_state;
        if (heroArea->x>485.7f && heroArea->x<570.7f && heroArea->y>250.0f && heroArea->y<334.5f) D_001B1510 = 52;
    }
    D_001B1514 = D_001B1510;
    D_001B1510 = D_001B1510|128;
    D_001B150C = 180;
    {
        HeroView *heroGround = &g_hero_state;
        if (((unsigned char *)heroGround)[0x1495]) {
            *(int *)(camState+0xc0) = 0x100;
            D_001B150C = 0x1b4;
        }
        else if (((unsigned char *)heroGround)[0x149b]) {
            *(int *)(camState+0xc0) = 0xb00;
            D_001B150C = 0xbb4;
        }
        else if (((unsigned char *)heroGround)[0x1496]) {
            *(int *)(camState+0xc0) = 0x300;
            D_001B150C = 0x3b4;
        }
        else if (((unsigned char *)heroGround)[0x149c]) {
            *(int *)(camState+0xc0) = 0xd00;
            D_001B150C = 0xdb4;
        }
        else if (((unsigned char *)heroGround)[0x1494]) {
            *(int *)(camState+0xc0) = 0;
            D_001B150C = 180;
        }
        else D_001B150C = *(int *)(camState+0xc0)|180;
    }
}
