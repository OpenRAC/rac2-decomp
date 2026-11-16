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
extern char g_camera_follow_state[];
extern int g_cam_collision_mask_alt __attribute__((section(".sdata")));
extern int g_cam_collision_mask_saved __attribute__((section(".sdata")));
extern int g_cam_collision_mask __attribute__((sda));
extern int g_current_map_index __attribute__((section(".sdata")));
extern float g_water_level_threshold[];
/* Chooses which things the camera collides with, based on what the hero is doing. */
void cam_select_coll_masks(void) {
    HeroView *hero = &g_hero_state;
    char *camState = g_camera_follow_state;
    g_cam_collision_mask_alt = 20;
    if ((unsigned)(hero->state-17)<2 || hero->mode==112) g_cam_collision_mask_alt = 52;
    {
        HeroView *heroWater = &g_hero_state;
        if (heroWater->state!=17 && heroWater->water<g_water_level_threshold[0]) g_cam_collision_mask_alt = 20;
    }
    if (g_current_map_index==6) {
        HeroView *heroArea = &g_hero_state;
        if (heroArea->x>485.7f && heroArea->x<570.7f && heroArea->y>250.0f && heroArea->y<334.5f) g_cam_collision_mask_alt = 52;
    }
    g_cam_collision_mask_saved = g_cam_collision_mask_alt;
    g_cam_collision_mask_alt = g_cam_collision_mask_alt|128;
    g_cam_collision_mask = 180;
    {
        HeroView *heroGround = &g_hero_state;
        if (((unsigned char *)heroGround)[0x1495]) {
            *(int *)(camState+0xc0) = 0x100;
            g_cam_collision_mask = 0x1b4;
        }
        else if (((unsigned char *)heroGround)[0x149b]) {
            *(int *)(camState+0xc0) = 0xb00;
            g_cam_collision_mask = 0xbb4;
        }
        else if (((unsigned char *)heroGround)[0x1496]) {
            *(int *)(camState+0xc0) = 0x300;
            g_cam_collision_mask = 0x3b4;
        }
        else if (((unsigned char *)heroGround)[0x149c]) {
            *(int *)(camState+0xc0) = 0xd00;
            g_cam_collision_mask = 0xdb4;
        }
        else if (((unsigned char *)heroGround)[0x1494]) {
            *(int *)(camState+0xc0) = 0;
            g_cam_collision_mask = 180;
        }
        else g_cam_collision_mask = *(int *)(camState+0xc0)|180;
    }
}
