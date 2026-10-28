/* Nonmatching reconstruction. Profile: -O2 -G0 -ffunction-sections.
 * 564/564 bytes; 0/27 in US, US2 and PAL. Only the initial adjacent hero-position and list-cursor address preparations are reversed. Helper declarations interleave integer and float arguments while preserving each physical bank and all arguments. A separate guarded cursor initialization ties. Reopen with measured pointer lifetime/scheduling evidence.
 * No complete strict linked validation or matching credit.
 */
#include "common.h"

typedef struct { u8 before[0xE0]; f32 position[4]; u8 gap[0x22C3 - 0xF0]; u8 aiming; } HeroFields;
extern HeroFields D_00189E20;
extern u8 *D_L00_001FACE0[];
extern u8 D_L00_001B8FF0[];
extern void func_00283698(void *, void *);
extern s32 func_002AB1F0(u8 *);
extern f32 func_L00_002AE5F0(u8 *, void *, f32, f32, f32, s32 *, void *);
extern f32 func_L00_002AE388(u8 *, f32, f32, f32, f32, s32 *);
extern void func_00282F20(void *, void *, f32);
extern void func_00282CC0(void *, void *, void *);
extern s32 func_002761F8(void *, void *, s32, s32, s32);

u8 *func_L00_002AE888(void *direction, s32 filter, s32 collide,
                     f32 distance, f32 yaw, f32 horizontal, f32 vertical)
{
    f32 matrix[16] __attribute__((aligned(16)));
    f32 origin[4] __attribute__((aligned(16)));
    f32 endpoint[4] __attribute__((aligned(16)));
    s32 rejected;
    u8 **cursor;
    u8 *object;
    u8 *selected = 0;
    f32 best = 100000000.0f;
    f32 score;
    f32 *health;
    if (D_00189E20.aiming != 0)
        func_00283698(matrix, D_L00_001B8FF0);
    object = D_L00_001FACE0[0];
    if (object != 0) {
        cursor = D_L00_001FACE0;
        do {
        if (filter != -1 && *(short *)(*(u8 **)(object + 0x24) + 0x46) != filter)
            goto next;
        if (filter == 5) {
            health = (f32 *)func_002AB1F0(object);
            if (health == 0)
                goto next;
            if (health[0] == 0.0f)
                goto next;
        }
        if ((*(u16 *)(object + 0x34) & 0x1000) != 0) {
            if (D_00189E20.aiming != 0)
                score = func_L00_002AE5F0(object, direction, distance, horizontal, vertical,
                                         &rejected, matrix);
            else
                score = func_L00_002AE388(object, yaw, distance, horizontal, vertical, &rejected);
            if (rejected == 0 && score < best) {
                if (collide != 0) {
                    qcopy(origin, D_00189E20.position);
                    func_00282F20(endpoint, object + 0xE0, 1.0f);
                    func_00282CC0(endpoint, endpoint, object + 0x10);
                    if (func_002761F8(origin, endpoint, 2, 0, 0) != 0)
                        goto next;
                }
                best = score;
                selected = object;
            }
        }
next:
        cursor++;
        object = *cursor;
        } while (object != 0);
    }
    return selected;
}
