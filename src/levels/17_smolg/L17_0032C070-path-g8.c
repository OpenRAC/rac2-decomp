#include "common.h"
extern char g_hero_position[];
extern char *g_linked_moby_base;
extern float g_platform_path_reach_dist __attribute__((sda));
extern int func_003221C8(void *, int);
extern float func_002EF0B0(void *, void *);
extern float func_002EF4C8(float);
extern float func_002F00B0(int);
extern int func_002F00C0(float);
extern void func_002EEEE8(void *, void *, void *);
extern void func_002EEF40(void *, void *, float);
extern void func_002EEEB8(void *, void *, void *);
/* Puts a platform on its path at the spot that matches its travel timer, easing in and out. If
   the player is blocking it, the timer winds back by one frame instead. */
void platform_move_along_path_by_timer(char *moby, int *path, float duration) {
    char *vars = *(char **)(moby + 0x68);
    float eased, fraction, phase;
    int index;
    float delta[4];
    if (*(int *)(vars + 0xCC) != -1 && *(int *)(vars + 0xAC) == 1 &&
        func_003221C8(g_hero_position, *(int *)(vars + 0xCC)) &&
        *(float *)(g_hero_position + 8) <= *(float *)(moby + 0x18) + 0.05f &&
        func_002EF0B0(moby + 0x10, g_linked_moby_base + *(int *)(vars + 0xCC) * 128 + 0x30) <= g_platform_path_reach_dist) {
        *(float *)(vars + 0x9C) -= 1.0f;
        goto done;
    }
    phase = (*(float *)(vars + 0x9C) * 3.141593f) / (duration * 60.0f);
    eased = (1.0f - func_002EF4C8(phase)) * 0.5f;
    index = func_002F00C0(func_002F00B0(path[0] - 1) * eased);
    fraction = func_002F00B0(path[0] - 1) * eased - func_002F00B0(index);
    if (index == path[0] - 1) {
        qcopy(moby + 0x10, (char *)path + index * 16 + 0x10);
    } else {
        func_002EEEE8(delta, (char *)path + (index * 16 + 0x20), (char *)path + (index * 16 + 0x10));
        func_002EEF40(delta, delta, fraction);
        func_002EEEB8(moby + 0x10, delta, (char *)path + (index * 16 + 0x10));
    }
done:;
}
