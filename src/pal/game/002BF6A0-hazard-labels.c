#include "include_asm.h"

#include "common.h"
extern int func_00282978(void *timer);
extern void func_002B9180(void *particle);
extern int func_00283CF0(float f);
extern void func_0029FCC0(void *object, int joint, void *out);
extern void func_00282CF0(void *out, void *a, void *b);
extern void func_00282F20(void *out, void *a, float scale);
extern void func_00282CC0(void *out, void *a, void *b);
extern char D_001B5340[];
extern unsigned char *D_001F25B4;
#define SIZE   (*(float *)(p + 0xC))
#define ALPHA  (*(float *)(q + 4))
#define SPIN   (*(float *)(q + 8))
#define FRAME  (*(short *)(q + 0xC))
#define JOINT  (*(short *)(q + 0xE))
#define SPEED  (*(float *)(q + 0x10))
#define EASE   (*(float *)(q + 0x14))

void func_PAL_002BF8A8(char *p)
{
    char *q;
    float pos[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));

    if (p == 0)
        return;
    q = p + 0x20;
    if (func_00282978(p + 0xA) || *(char **)q == 0 || *(signed char *)(*(char **)q + 0x20) < 0) {
        func_002B9180(p);
        return;
    }
    FRAME = (*(unsigned short *)(q + 0xC) + 1) & 15;
    if (SIZE < 159600.0f) {
        SIZE += 4788.0f;
        if (SIZE > 159600.0f)
            SIZE = 159600.0f;
    } else if (SIZE > 159600.0f) {
        SIZE -= 19152.0f;
        if (SIZE < 159600.0f)
            SIZE = 159600.0f;
    }
    SPIN += 0.0012f;
    p[8] = func_00283CF0(SPIN * 255.0f);
    p[2] = D_001F25B4[FRAME];
    if (SIZE <= 159600.0f || SPEED > 0.0f)
        ALPHA += SPEED;
    if (SIZE <= 159600.0f) {
        if (ALPHA > 0.3f) {
            SPEED = -SPEED;
            ALPHA += SPEED;
        } else if (ALPHA < 0.0f) {
            func_002B9180(p);
            return;
        }
    } else {
        if (ALPHA > 0.15f) {
            SPEED = -SPEED;
            ALPHA += SPEED;
        } else if (ALPHA < 0.0f) {
            func_002B9180(p);
            return;
        }
    }
    *(int *)(p + 4) = (*(int *)(p + 4) & 0xFFFFFF) + (func_00283CF0(ALPHA * 256.0f) << 24);
    EASE += (1.0f - EASE) * 0.21000001f;
    if (JOINT != -1) {
        func_0029FCC0(*(void **)q, JOINT, pos);
        func_00282CF0(delta, D_001B5340, pos);
        func_00282F20(delta, delta, EASE);
        func_00282CC0(p + 0x10, pos, delta);
    }
}
