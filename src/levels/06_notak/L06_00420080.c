#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

extern int *g_path_list[];
extern char g_hero_position[];
typedef struct {
    char pad0[0x80];
    TI128 f80;
    char pad1[0x2290 - 0x90];
    char *f2290;
} L06Hero;

extern L06Hero g_hero_state;

extern int func_35A620(int);
extern int func_361930(char *, void *, int, int, void *, int, float);
extern int func_361728(char *, void *, float);
extern float func_32D7C0(void *, void *);
extern void func_36A798(char *, int, int, int, float, float);

/* Chooses where the actor should walk next and returns 0 if it has arrived, 1 if it must walk, or 2 if it is close. */
int actor_choose_path_goal(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    int *pathData;

    if (*(unsigned char *)(moby + 0x20) == 0 || func_35A620(7) == 0) {
        if (*(int *)(vars + 0x260) != -1) {
            char *goalPoint;

            if (*(unsigned char *)(moby + 0x20) < 3)
                pathData = g_path_list[*(int *)(vars + 0x260)];
            else
                pathData = g_path_list[*(int *)(vars + 0x264)];
            goalPoint = vars + 0x1C0;
            if (func_361930(moby, goalPoint, 0, 0, (char *)pathData + 0x10, *pathData, *(float *)(vars + 0x290)) != 2) {
                if (func_32D7C0(moby + 0x10, goalPoint) < 8.0f)
                    *(int *)(vars + 0x258) = 2;
                else
                    *(int *)(vars + 0x258) = 1;
            } else {
                *(TI128 *)goalPoint = *(TI128 *)g_hero_position;
                *(int *)(vars + 0x258) = 0;
            }
        } else {
            char *goalPoint = vars + 0x1C0;

            if (func_361728(moby, goalPoint, *(float *)(vars + 0x290)) == 2) {
                *(TI128 *)goalPoint = *(TI128 *)g_hero_position;
                *(int *)(vars + 0x258) = 0;
            } else if (func_32D7C0(moby + 0x10, goalPoint) < 8.0f) {
                *(int *)(vars + 0x258) = 2;
            } else {
                *(int *)(vars + 0x258) = 1;
            }
        }
    } else if (*(char **)(vars + 0x200) == g_hero_state.f2290) {
        *(TI128 *)(vars + 0x1C0) = g_hero_state.f80;
    }
    func_36A798(moby, -1, 0, 0, *(float *)(vars + 0x338) * 20.0f, 10.0f);
    return *(int *)(vars + 0x258);
}
