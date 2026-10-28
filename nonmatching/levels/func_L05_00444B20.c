/* func_L05_00444B20 - retained C reconstruction, not an exact match.
 * Profile: -O2 -G8 -ffunction-sections.
 * Measured in src/levels/shared/L05_00444B20-g8.c: 580/576 bytes.
 * US: 0/4 local places; PAL: ABSENT; US2: 0/4 local places.
 * No strict linked build was run because no local placement matched.
 * The null-target path correctly joins audio cleanup; remaining entry flag, sound-entry pointer and cleanup block allocation/order differ. The angular literal is the measured word. Reopen with allocator evidence.
 */

#include "common.h"

extern void func_L05_00444D60(char *, int *, int *, int);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_L05_00444DF8(float, float, float, float, unsigned char, unsigned char, unsigned char, unsigned char);
extern float func_00283B98(float, float);
extern int func_002E5DA0(int, int, char *, int);
extern void func_002E59F8(int);
extern int D_L05_002A1968 MACRO_ADDR;
extern int D_L05_001B1B04 __attribute__((sda));
extern int D_L05_001B1B0C __attribute__((sda));
extern int D_L05_001B1B00 __attribute__((sda));
extern int D_L05_001B1B08 __attribute__((sda));
extern char D_00188660[];

void func_L05_00444B20(char *object)
{
    int x, y;
    char *state = *(char **)(object + 0x68);
    int threshold, duration;
    float progress, alpha, scale;
    float fx, fy;
    int handle;
    char *sound;
    unsigned char opacity;
    if (!*(char **)(state + 0x14)) goto cleanup;
    func_L05_00444D60(*(char **)(state + 0x14) + 0x10, &x, &y, 0);
    if (D_L05_002A1968) {
        threshold = D_L05_001B1B04;
        duration = D_L05_001B1B0C;
    } else {
        threshold = D_L05_001B1B00;
        duration = D_L05_001B1B08;
    }
    if (*(int *)(state + 0x1C) > threshold) {
        progress = func_00283CE0(*(int *)(state + 0x1C) - threshold) / func_00283CE0(duration);
        alpha = (1.0f - progress) * 2.0f;
        scale = progress * 5.0f + 1.0f;
        if (alpha > 1.0f) alpha = 1.0f;
        opacity = func_00283CF0(alpha * 96.0f);
        fx = func_00283CE0(x);
        fy = func_00283CE0(y);
        func_L05_00444DF8(fx, fy, scale, *(float *)(state + 0x27C), 255, 0, 0, opacity);
        *(float *)(state + 0x27C) = func_00283B98(*(float *)(state + 0x27C), 0.01745329424738884f);
        *(char **)(state + 0x18) = *(char **)(state + 0x14);
        handle = *(int *)(state + 0x270);
        sound = D_00188660 + handle * 112;
        if (*(char **)(sound + 0x88) == object && *(unsigned char *)(sound + 0x74)) return;
        *(int *)(state + 0x270) = func_002E5DA0(9, 4, object, 0xFBF);
    } else if (!*(int *)(state + 0x26C)) {
        func_002E5DA0(8, 0, object, 0xFBF);
        *(int *)(state + 0x26C) = 1;
        fx = func_00283CE0(x);
        fy = func_00283CE0(y);
        func_L05_00444DF8(fx, fy, 1.0f, 0.0f, 0, 255, 0, 96);
    } else {
cleanup:
        handle = *(int *)(state + 0x270);
        if (handle != -1) {
            sound = D_00188660 + handle * 112;
            if (*(char **)(sound + 0x88) == object && *(unsigned char *)(sound + 0x74)) func_002E59F8(handle);
        }
        *(int *)(state + 0x26C) = 0;
        *(int *)(state + 0x270) = -1;
    }
}