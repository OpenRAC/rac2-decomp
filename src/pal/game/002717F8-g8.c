#include "include_asm.h"

typedef struct {float amplitude, offset; int frames, longest;} CameraShake;
typedef struct { char prefix[0x140]; float pos[4]; char pad[0x40]; char *current; char pad194[0x1dc]; float rows[12]; } CameraSystem;
extern CameraSystem D_001B5200;
extern float D_001A85B8 __attribute__((sda));
extern int func_00282948(void *);
extern float func_00283CE0(int);
extern float func_00283C28(float);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACE78(void *, void *, float);
extern void func_00283958(void *, void *);
extern void func_00283738(void *, void *, void *);

void func_PAL_002717F8(CameraShake *s, int mode)
{
    float buf[4], matrix[12];
    float ratio, cube, frequency, elapsed, ramp;
    if (D_001B5200.current != 0 && *(short *)(D_001B5200.current + 0x86) == 6) {
        s->frames = 0;
        s->longest = 0;
    } else if (s->frames != 0) {
        if (s->longest < s->frames) s->longest = s->frames;
        func_00282948(&s->frames);
        ratio = func_00283CE0(s->frames) / func_00283CE0(s->longest);
        switch (mode) {
        case 0: {
            float value = s->amplitude * func_00283180(func_00283C28(func_00283CE0(s->frames) * 2.0f)) * ratio * ratio;
            s->offset = value;
            func_00282F20(buf, (D_001B5200.rows + 8), value);
            func_00282CC0(D_001B5200.pos, D_001B5200.pos, buf);
            break;
        }
        case 1: {
            float value = s->amplitude * func_00283180(func_00283C28(func_00283CE0(s->frames) * 2.0f)) * ratio * ratio;
            s->offset = value;
            func_00282F20(buf, D_001B5200.rows, value);
            func_00282CC0(D_001B5200.pos, D_001B5200.pos, buf);
            break;
        }
        case 2: {
            float value;
            cube = ratio * ratio * ratio;
            frequency = D_001A85B8 * 0.017453294f;
            elapsed = func_00283CE0(s->longest - s->frames) * (0.019867549f);
            ramp = elapsed * 6.0f;
            if (ramp > 1.0f) ramp = 1.0f;
            value = s->amplitude * func_00283198(func_00283C28(elapsed * frequency - frequency * 8.0f)) * cube * ramp;
            s->offset = value;
            func_002ACE78(buf, D_001B5200.rows, value);
            func_00283958(buf, matrix);
            func_00283738(D_001B5200.rows, matrix, D_001B5200.rows);
            break;
        }
        }
    } else s->longest = 0;
}
