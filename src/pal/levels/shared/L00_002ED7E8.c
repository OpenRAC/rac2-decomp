#include "include_asm.h"

/* func_PAL_L00_002ED7E8, the PAL copy of func_L00_002EC248: the same C, where the gravity
   scale 0.00027777778f becomes 0.00040000002f and the two lifetimes are rescaled to 50 Hz
   in float, (scale * 10 * 5 + 2) / 6, written as (scale * 50 + 2) * (1 / 6). */

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

void func_PAL_L00_002ED7E8(char *object, void *positionOffset, void *velocityOffset,
                     int count, int palette, float positionSpread, float velocitySpread,
                     float width, float gravity, float duration)
{
    BurstVector position, velocity, endpoint;
    int start, end, i;
    int first, middle, last;
    int texture = 0x1003C;
    float scale, small;
    gravity *= 0.00040000002f;
    palette &= 0xFF;
    for (i = 0; i < count; i++) {
        func_002A7A00(&position, 0.0f, positionSpread);
        func_00282CC0(&position, &position, positionOffset);
        func_L00_00324F18(object, &position, position.x, position.y, position.z);
        func_002A7A00(&velocity, 0.0f, velocitySpread);
        func_00282CC0(&velocity, &velocity, velocityOffset);
        func_00283098(&velocity, &velocity, object + 0xC0);
        scale = duration * func_002A7878(0.5f, 1.5f);
        small = (scale * 50.0f + 2.0f) * 0.16666667f;
        first = func_00283CF0(small);
        middle = func_00283CF0((scale * 200.0f + 2.0f) * 0.16666667f);
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
        case 0:
        default:
            start = func_00283D38(0x80004080, 0x80408080, func_002A7878(0.0f, 1.0f));
            end = func_00283D38(0x00004080, 0x00408080, func_002A7878(0.0f, 1.0f));
            break;
        }
        func_002BAA28(&position, &velocity, &endpoint, start, end,
                     first, middle, last, texture);
    }
}
