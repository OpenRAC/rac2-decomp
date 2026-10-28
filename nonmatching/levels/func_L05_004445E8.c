/* func_L05_004445E8 - retained C reconstruction, not an exact match.
 * Profile: -O2 -G8 -ffunction-sections -g.
 * Corrected control flow measured in src/levels/shared/L05_004445E8-g8.c: 612/600 bytes.
 * US: 0/4 local places; US2: 0/4 local places; PAL: ABSENT. The former draft did not preserve all reset and return paths.
 * No strict linked build was run because no local placement matched.
 * A changed target resets progress before the common clamp. Invalid states and nonpositive health return directly. Angular/occlusion loss restores object+0x98 after clearing the target; zero-length loss skips that restore. Previous size/register observations do not qualify this corrected control flow.
 */

#include "common.h"

typedef struct { float x, y, z, w; } Vector;
extern int func_L05_0037AA88(int);
extern char *func_L05_00444840(void *, char **, char *);
extern int func_002AB1F0(unsigned char *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern float func_00282DB0(void *, void *);
extern float func_002831B0(float);
extern float func_00282C48(float);
extern int func_002761F8(void *, void *, unsigned int, void *, void *);
extern char D_L05_002A1800[];
extern int D_L05_001B1B0C __attribute__((sda));
extern int D_L05_001B1B08 __attribute__((sda));
extern float D_L05_001B1B14 __attribute__((sda));
extern int D_L05_001B2048 MACRO_ADDR;
extern Vector D_L05_001B96C0;

void func_L05_004445E8(char *object)
{
    Vector difference;
    char *state = *(char **)(object + 0x68);
    int selection = func_L05_0037AA88(1);
    int maximum;
    char *target;
    float *health;
    float length;
    float dot;
    if (selection < 0 || *(int *)(D_L05_002A1800 + selection * 40 + 0x14) <= 0) goto clear;
    maximum = *(int *)(D_L05_002A1800 + 0x168) ? D_L05_001B1B0C : D_L05_001B1B08;
    target = *(char **)(state + 0x18);
    if (!target) {
        char *next;
        *(int *)(object + 0x98) = 0;
        next = func_L05_00444840(state + 0x20, 0, *(char **)(state + 0x14));
        *(int *)(object + 0x98) = *(int *)(*(char **)(object + 0x24) + 0x10);
        if (next != *(char **)(state + 0x14)) {
            *(char **)(state + 0x14) = next;
            goto reset_progress;
        }
        if (++*(int *)(state + 0x1C) <= maximum) return;
        *(int *)(state + 0x1C) = maximum;
        goto finish;
    }
    if (*(unsigned char *)(target + 0x20) == 0xFE || *(unsigned char *)(target + 0x20) == 0xFD) {
        *(int *)(state + 0x1C) = 0;
        *(char **)(state + 0x18) = 0;
        return;
    }
    health = (float *)func_002AB1F0((unsigned char *)target);
    if (health && *health <= 0.0f) {
        *(int *)(state + 0x1C) = 0;
        *(char **)(state + 0x18) = 0;
        return;
    }
    func_00282CF0(&difference, *(char **)(state + 0x18) + 0x10, object + 0x10);
    length = func_00282DF0(&difference);
    dot = func_00282DB0(object + 0xC0, &difference);
    if (length == 0.0f) goto zero_length;
    *(int *)(object + 0x98) = 0;
    if (func_00282C48(1.57079632679f - func_002831B0(dot / length)) > D_L05_001B1B14 * 0.01745329424738884f) goto lost_restore;
    if (D_L05_001B2048 % 5 == 0) {
        target = *(char **)(state + 0x18);
        if (func_002761F8(&D_L05_001B96C0, target + 0x10, 16, target, 0)) goto lost_restore;
    }
    if (++*(int *)(state + 0x1C) > maximum) *(int *)(state + 0x1C) = maximum;
restore_visual:
    *(int *)(object + 0x98) = *(int *)(*(char **)(object + 0x24) + 0x10);
    goto finish;
lost_restore:
    *(char **)(state + 0x18) = 0;
    *(char **)(state + 0x14) = 0;
    *(int *)(state + 0x1C) = 0;
    goto restore_visual;
zero_length:
    *(char **)(state + 0x18) = 0;
    *(char **)(state + 0x14) = 0;
reset_progress:
    *(int *)(state + 0x1C) = 0;
finish:
    if (*(int *)(state + 0x1C) > maximum) *(int *)(state + 0x1C) = maximum;
    return;
clear:
    *(int *)(state + 0x1C) = 0;
    *(char **)(state + 0x18) = 0;
    *(char **)(state + 0x14) = 0;
}