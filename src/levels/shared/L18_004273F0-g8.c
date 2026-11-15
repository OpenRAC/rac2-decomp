#include "include_asm.h"
#include "names.h"

/* func_L18_004273F0 is a unit of its own: it needs the opt-in quadword-copy profile
   (-frac2-qcopy, #262), which gives retail's grouped `lq`/`sq` with register addresses. It reads $gp data, hence -G8. */

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int TI128 __attribute__((mode(TI)));

extern unsigned int D_L18_001FB320[];
extern char *g_moby_l18_table;
extern char *D_L18_001B281C_sda __attribute__((sda));
extern int D_L18_001B2838 __attribute__((sda));
extern const unsigned short D_L18_001B125C __attribute__((sda));
extern int D_L18_001B2348;
extern char D_L18_002C0A90[];
extern char g_hero_position[];
extern char *D_001FE480[];

extern void STUB_printf(char *fmt, int a1, int a2);
extern float path_find_best_point_by_id(void *a0, void *a1, void *a2, int a3, float f12);
extern void moby_set_state(u8 *a0, int a1, int a2);
extern void moby_wake_linked_enemy(u8 *a0);
extern float vec_distance_xy(void *a0, void *a1);

/* Picks the closest idle enemy to this spawner's target point and wakes it up with the spawner's settings. */
void spawner_activate_nearest_enemy(u8 *obj)
{
    u8 *vars = *(u8 **)(obj + 0x68);
    u8 *bestObject = 0;
    int foundPoint = 0;
    float bestDistance = 100000.0f;
    float targetPoint[4];
    u16 *listEntry;
    u8 *candidate;
    u8 *candidateState;
    float distance;

    if (*(int *)(vars + 0x378) == -1) {
        if (*(int *)(vars + 0x368) == -1) {
            STUB_printf(D_L18_002C0A90, *(s16 *)(obj + 0xB2), D_L18_001B2348);
        } else {
            path_find_best_point_by_id(targetPoint, obj + 0x10, g_hero_position, *(int *)(vars + 0x368), 0.0f);
            foundPoint = 1;
        }
    } else {
        *(TI128 *)targetPoint = *(TI128 *)(D_001FE480[*(int *)(vars + 0x378)] + 0x10);
    }

    listEntry = (u16 *)D_L18_001FB320[obj[0x21]];
    while (obj[0x21] != 0xFF && obj[0x21] <= D_L18_001B2838 && listEntry != 0 &&
           ((listEntry != 0 && (s16)listEntry[-1] >= 0) || listEntry == (u16 *)D_L18_001FB320[obj[0x21]])) {
        candidate = (u8 *)(g_moby_l18_table + ((*listEntry & 0x7FFF) << 8));
        if (candidate == 0)
            break;
        candidateState = *(u8 **)(candidate + 0x68);
        distance = vec_distance_xy(candidate + 0x10, targetPoint);
        if (candidateState != 0 && (candidateState[0x399] & 1) != 0 && distance < bestDistance) {
            bestDistance = distance;
            bestObject = candidate;
        }
        listEntry++;
    }

    if (bestObject != 0) {
        u8 *bestState;
        u16 timerValue;
        bestObject[0x31] = 1;
        *(u16 *)(bestObject + 0x34) &= 0xFFFE;
        bestState = *(u8 **)(bestObject + 0x68);
        timerValue = D_L18_001B125C;
        *(int *)(bestState + 0x36C) = *(int *)(vars + 0x36C);
        *(int *)(bestState + 0x370) = *(int *)(vars + 0x370);
        *(int *)(bestState + 0x374) = *(int *)(vars + 0x374);
        *(int *)(bestState + 0x378) = *(int *)(vars + 0x378);
        *(int *)(bestState + 0x360) = *(int *)(vars + 0x360);
        *(int *)(bestState + 0x364) = *(int *)(vars + 0x364);
        *(u16 *)(bestState + 0x390) = timerValue;
        *(int *)(bestState + 0x38C) = *(int *)(vars + 0x378);
        bestState[0x39A] = 1;
        bestState[0x399] = 2;
        *(u16 *)(bestState + 0x392) = vars[0x398];
        if (foundPoint) {
            moby_set_state(bestObject, 0, 4);
        } else if (bestState[0x3EA] != 0 && *(int *)(bestState + 0x3B4) != -1 &&
                   ((u8 *)((*(int *)(bestState + 0x3B4) << 8) + (int)D_L18_001B281C_sda))[0x20] != 0xFE &&
                   ((u8 *)((*(int *)(bestState + 0x3B4) << 8) + (int)D_L18_001B281C_sda))[0x20] != 0xFD) {
            moby_wake_linked_enemy(bestObject);
        } else {
            moby_set_state(bestObject, 0, 3);
        }
    }
}
