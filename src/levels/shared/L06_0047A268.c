#include "common.h"

extern char g_hero_position[];
typedef struct { char pad[28]; char *st; } L06TriggerEntry;
extern char *g_path_list[];
extern s32 g_camera_l06_state_ptr;
extern L06TriggerEntry *g_trigger_volume_tables[] __attribute__((sda));
extern int g_hero_mode, g_hero_volume_mode;
extern int IsPointInCuboid(void *, int);
extern int coll_point_inside_record_volume(void *, int);
extern int coll_is_point_inside_unit_sphere(void *, int);
extern int point_in_path_xy(void *, void *, int);

/* Tells whether the hero is inside the camera volume of this camera moby. */
int cam_is_hero_in_volume(char *moby) {
    int force = 0;
    char *camera_state = (char *)g_camera_l06_state_ptr;
    int idx = *(s16 *)(moby + 0x84);
    char *volume = g_trigger_volume_tables[0][idx].st;
    int disabled = *(s16 *)(camera_state + 0x86);
    if (disabled) return 0;
    if (*(s16 *)(volume+0x2C)==2 && g_hero_mode==26 && *(s16 *)(volume+0x2E)>0) force=1;
    else if (*(s16 *)(volume+0x2C)==4 && g_hero_volume_mode==3) force=*(s16 *)(volume+0x2E)>0;
    if (*(int *)(volume+0xC)>=0 && (force || IsPointInCuboid(g_hero_position,*(int *)(volume+0xC)))) return 1;
    if (*(int *)(volume+0x4C)>=0 && (force || IsPointInCuboid(g_hero_position,*(int *)(volume+0x4C)))) return 1;
    if (*(int *)(volume+0x10)>=0 && (force || coll_point_inside_record_volume(g_hero_position,*(int *)(volume+0x10)))) return 1;
    if (*(int *)(volume+8)>=0 && (force || coll_is_point_inside_unit_sphere(g_hero_position,*(int *)(volume+8)))) return 1;
    if (*(int *)(volume+0x14)>=0) {
        if (force || point_in_path_xy(g_hero_position,
            g_path_list[*(int *)(volume+0x14)]+16,
            *(int *)g_path_list[*(int *)(volume+0x14)])) return 1;
    }
    return 0;
}
