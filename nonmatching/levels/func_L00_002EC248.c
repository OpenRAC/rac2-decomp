/* 5 November 2026: Indexed emission, byte palette and colour/position FP-bank forms remain 964/956 bytes. Separate signed/unsigned remaining counters and reuse of the captured count for a real lifetime count give 972 bytes. Keep the 964-byte body; no candidate is promoted.
 */
/* Nonmatching reconstruction, 2 November 2026. Replaces the old opcode screen.
 * Default -O2 -G0 -ffunction-sections: three USA checks give 928, 964, 972
 * bytes against 956, all 0/7. Retained guarded do-loop form is 964 bytes with
 * retail's real 0xF0 frame. The explicit texture local hoists to the correct
 * stack slot, but its split constant has an extra partial store. Count/lifetime
 * allocation and palette dispatch/order still differ. A separate remaining
 * counter worsens to 972 bytes; no artificial stack or register steering used.
 * The five integer and five FP input slots, three 16-byte vector buffers,
 * full-width constructor parameters and pointer return follow the actual
 * callees. Position W is opaque; both endpoint W values are defined before
 * the constructor uses them as sizes. No W zero was invented for matching.
 * Reopen with natural count/constant lifetime or switch-layout evidence.
 * No alternate-release or linked build was run for these failed candidates.
 */
#include "common.h"

typedef struct { float x,y,z,w; } BurstVector;
extern void func_002A7A00(void *, float, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_00324F18(void *, void *, float, float, float);
extern void func_00283098(void *, void *, void *);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern void func_00282C88(void *);
extern int func_00283D38(int, int, float);
extern void *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);

void func_L00_002EC248(char *object, void *positionOffset, void *velocityOffset,
                     int count, int palette, float positionSpread, float velocitySpread,
                     float width, float gravity, float duration)
{
    BurstVector position, velocity, endpoint;
    int start, end;
    int first, middle, last;
    int texture = 0x1003C;
    float scale, small;
    gravity *= 0.00027777778f;
    palette &= 0xFF;
    if (count <= 0) return;
    do {
        func_002A7A00(&position, 0.0f, positionSpread);
        func_00282CC0(&position, &position, positionOffset);
        func_L00_00324F18(object, &position, position.x, position.y, position.z);
        func_002A7A00(&velocity, 0.0f, velocitySpread);
        func_00282CC0(&velocity, &velocity, velocityOffset);
        func_00283098(&velocity, &velocity, object + 0xC0);
        scale = duration * func_002A7878(0.5f, 1.5f);
        small = scale * 10.0f;
        first = func_00283CF0(small);
        middle = func_00283CF0(scale * 40.0f);
        last = func_00283CF0(small);
        velocity.w = width * func_002A7878(0.1f, 0.4f);
        func_00282C88(&endpoint);
        endpoint.z = -gravity * (float)(first + middle + last);
        func_00282CC0(&endpoint, &endpoint, &velocity);
        switch (palette) {
        case 1:
            start = func_00283D38(0x80102040, 0x801010A0, func_002A7878(0.0f, 1.0f));
            end = func_00283D38(0x00102040, 0x001010A0, func_002A7878(0.0f, 1.0f));
            break;
        case 3:
            start = func_00283D38(0x80201608, 0x80402510, func_002A7878(0.0f, 1.0f));
            end = func_00283D38(0x00201608, 0x00402510, func_002A7878(0.0f, 1.0f));
            break;
        case 2:
            start = func_00283D38(0x80104010, 0x8020A020, func_002A7878(0.0f, 1.0f));
            end = func_00283D38(0x00104010, 0x0020A020, func_002A7878(0.0f, 1.0f));
            break;
        default:
            start = func_00283D38(0x80004080, 0x80408080, func_002A7878(0.0f, 1.0f));
            end = func_00283D38(0x00004080, 0x00408080, func_002A7878(0.0f, 1.0f));
            break;
        }
        func_002BAA28(&position, &velocity, &endpoint, start, end,
                     first, middle, last, texture);
    } while (--count);
}
