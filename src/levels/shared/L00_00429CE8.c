#include "names.h"
/* Test the camera trigger volumes, marking the descriptor done when none apply. */
#include "common.h"
extern char *D_L00_001B1844 __attribute__((section(".sdata")));
extern char *g_follow_camera_object;
extern char g_hero_position[];
extern float math_fabs(float);
extern float vec_distance_xy(char *, char *);
extern int IsPointInCuboid(char *, int);
extern int coll_point_inside_record_volume(char *, int);
extern int coll_is_point_inside_unit_sphere(char *, int);
typedef struct { char pad[0x30]; char pos[16]; char rest[0x40]; } Entry_b0898;
extern Entry_b0898 *D_L00_001B1F8C __attribute__((section(".sdata")));
typedef struct {
 char pad[0x80]; char position[16]; char pad90[0x174-0x90]; float speed; char pad178[0x2294-0x178]; int mode;
 char pad2298[0x22B4-0x2298]; unsigned char flag;
} Global_b0898;
extern Global_b0898 D_00189E20_b0898;
int cam_test_trigger_volumes(char *trigger)
{
    char *owner = g_follow_camera_object;
    char *sub = *(char **)(owner + 0x70);
    char *move = sub + 0x160;
    char *rot = sub + 0x1C0;
    char *desc = *(char **)(D_L00_001B1844 + *(short *)(trigger + 0x84) * 32 + 28);
    unsigned int mode;
    if (*(short *)(owner + 0x86) != 0) return 0;
    mode = D_00189E20_b0898.flag - 1U < 2U;
    if (*(short *)(desc + 0x4A) && !mode) return 0;
    if (*(short *)(desc + 0x48) && mode) return 0;
    if (*(int *)(desc + 0x34)) {
        if (math_fabs(*(float *)(move + 0x34)) > 0.01f) return 0;
        if (math_fabs(*(float *)(rot + 8)) > 0.01f) return 0;
    }
    if ((unsigned int)(D_00189E20_b0898.mode - 0x62) >= 2 && D_00189E20_b0898.speed > 0.016666668f) return 0;
    if (*(int *)(desc + 0xC) >= 0) {
        if (D_00189E20_b0898.mode == 0x62 && vec_distance_xy(D_00189E20_b0898.position, D_L00_001B1F8C[*(int *)(desc + 0xC)].pos) < 3.0f) return 1;
        if (IsPointInCuboid(g_hero_position, *(int *)(desc + 0xC))) return 1;
    }
    if (*(int *)(desc + 0x10) >= 0) {
        if (D_00189E20_b0898.mode == 0x62 && vec_distance_xy(D_00189E20_b0898.position, D_L00_001B1F8C[*(int *)(desc + 0x10)].pos) < 3.0f) return 1;
        if (coll_point_inside_record_volume(g_hero_position, *(int *)(desc + 0x10))) return 1;
    }
    if (*(int *)(desc + 8) >= 0) {
        if (D_00189E20_b0898.mode == 0x62 && vec_distance_xy(D_00189E20_b0898.position, D_L00_001B1F8C[*(int *)(desc + 8)].pos) < 3.0f) return 1;
        if (coll_is_point_inside_unit_sphere(g_hero_position, *(int *)(desc + 8))) return 1;
    }
    *(short *)(desc + 0x26) = 1;
    return 0;
}
