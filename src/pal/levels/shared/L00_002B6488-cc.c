/* func_PAL_L00_002B6488, the PAL copy of func_L00_002B6560: the same C, where scale p- becomes entries[p->index].duration. */
#include "common.h"

extern int func_L00_002ADEA0(int);
extern void func_L00_002D34C0(void *, void *, float);
extern float func_L00_002D3B00(void *);
extern void func_L00_002D3B58(void *, void *, float);
extern void func_L00_002D38A0(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AA2E8(float *, float, float);
extern float func_00282C10(float);
extern void func_L00_002B9BB0(int, int, int);
extern void func_002E59F8(int);
/* The EE passes the three floats independently of the two integer arguments. */
extern void func_L00_002D36E0(void *, float, float, float, int);
extern int func_002761F8(void *, void *, int, int, int);

extern unsigned char D_001A7AF8[] MACRO_ADDR;
extern char D_00188660[];
extern char D_00189E20[];
extern int D_00138320[];
extern char D_00189EA0[];

typedef struct {
    float initial, acceleration;
    int duration;
} HeroMotionEntry;

typedef struct {
    char pad[20];
    HeroMotionEntry *entries;
    int index, ticks;
    float value;
} HeroMotionSequence;

/* Apply gravity and the current jump or hovering motion to the hero's velocity. */
void func_PAL_L00_002B6488(void)
{
    float v[4], w[4], u[4], len;
    float speed, distance;
    int near, clear;

    {
        char *g = (char *)&D_00189E20;
        int state = *(int *)(g + 0x2294), age;

        if (!((state == 27 && *(int *)(g + 0x1B8) < 8) ||
              (state == 137 && (age = *(int *)(g + 0x1B8)) < 12) ||
              (state == 72 && *(int *)(g + 0x1B8) < 11))) {
            if (*(int *)(g + 0x1B8) < *(short *)(g + 0x4AC)) {
                func_L00_002D3B58(g + 0xF0, g + 0xF0, 0.0f);
                func_L00_002D34C0(g + 0xF0, g + 0xF0, 0.0192f);
            } else if (*(unsigned char *)(g + 0x49C)) {
                func_L00_002D3B58(g + 0xF0, g + 0xF0, 0.0f);
                func_L00_002D34C0(g + 0xF0, g + 0xF0, 0.0216f);
            } else {
                float z;

                func_L00_002D34C0(g + 0xF0, g + 0xF0, *(float *)(g + 0x520));
                z = func_L00_002D3B00(g + 0xF0);
                if (z < -*(float *)(g + 0x4A0))
                    z = -*(float *)(g + 0x4A0);
                func_L00_002D3B58(g + 0xF0, g + 0xF0, z);
            }
        }
    }
    {
        char *g = (char *)&D_00189E20;

        if (*(int *)(g + 0x2294) == 14) {
            speed = 0.14000002f;
            near = 0;
            if (D_001A7AF8[2] && *(short *)(g + 0x24FC) == 0)
                near = func_L00_002ADEA0(3) == 3;
            {
                char *position = D_00189EA0;

                func_00282CF0(v, position, position + 0x3E0);
                distance = func_L00_002D3B00(v);
                clear = 1;
                if (near) {
                    char *g = position - 0x80;

                    if (!*(unsigned char *)(g + 0x49E)) {
                        func_L00_002B9BB0(4, *(int *)(g + 0x2290), 13);
                    } else {
                        int index = *(int *)(g + 0x243C);

                        if (index != -1) {
                            char *entry = D_00188660 + index * 112;

                            if (*(int *)(entry + 0x88) == *(int *)(g + 0x2290) &&
                                *(unsigned char *)(entry + 0x74)) {
                                func_002E59F8(index);
                            }
                        }
                        {
                            char *h = (char *)D_00189E20;

                            *(int *)(h + 0x243C) = -1;
                        }
                    }
                    func_L00_002D36E0(u, 0.0f, 0.0f, 1.0f, 1);
                    func_L00_002D36E0(w, 0.0f, 0.0f, 2.7f, 1);
                    if (func_002761F8(u, w, 2, 0, 0))
                        clear = 0;
                }
            }
            if (near && clear) {
                if (distance > 2.8f)
                    speed *= 0.47f;
                else if (distance > 2.2f)
                    speed *= 0.7f;
            } else {
                if (distance > 2.1f)
                    speed *= 0.45f;
                else if (distance > 1.7f)
                    speed *= 0.7f;
            }
            if (func_L00_002ADEA0(3) == 3) {
                char *g = (char *)D_00189E20;

                if (*(short *)(g + 0x24FC) == 0) {
                    if (clear)
                        speed *= 1.25f;
                }
            }
            {
                char *g = (char *)&D_00189E20;

                if (*(int *)(g + 0x1B8) < 7) {
                    len = func_L00_002D3B00(g + 0xF0);
                    if (len < speed)
                        func_002AA2E8(&len, speed, 0.060000002f);
                    func_L00_002D3B58(g + 0xF0, g + 0xF0, len);
                }
            }
        } else {
            int zero = 0;
            char *k;

            if (*(float *)(g + 0x4B0) == 0.0f && *(float *)(g + 0x4B4) == 0.0f)
                zero = 1;
            if ((D_00138320[0] & 0x40) || zero ||
                (k = (char *)D_00189E20, *(int *)(k + 0x2294) == 18)) {
                char *g = (char *)&D_00189E20;

                if (*(float *)(g + 0x4A8) < *(float *)(g + 0x50C) &&
                    *(int *)(g + 0x1B8) <= *(short *)(g + 0x518)) {
                    *(float *)(g + 0x4A8) +=
                        (*(float *)(g + 0x50C) - *(float *)(g + 0x508)) /
                        (float)*(short *)(g + 0x518);
                    if (*(float *)(g + 0x50C) < *(float *)(g + 0x4A8))
                        *(float *)(g + 0x4A8) = *(float *)(g + 0x50C);
                    *(float *)(g + 0x4B0) +=
                        func_00282C10(*(float *)(g + 0x4A8) * 2.0f * *(float *)(g + 0x520)) -
                        *(float *)(g + 0x4B4) - *(float *)(g + 0x4B0);
                }
            }
            {
                char *g = (char *)&D_00189E20;

                if (*(int *)(g + 0x1B8) >= *(short *)(g + 0x4AC) &&
                    *(float *)(g + 0x4B0) > 0.0f) {
                    func_L00_002D38A0(g + 0xF0, g + 0xF0, *(float *)(g + 0x4B0));
                    *(float *)(g + 0x4B4) += *(float *)(g + 0x4B0);
                    *(float *)(g + 0x4B0) = 0.0f;
                }
            }
            {
                char *g = (char *)&D_00189E20;

                if (*(unsigned char *)(g + 0x49D) &&
                    *(int *)(g + 0x1B8) >= *(int *)(g + 0x430) &&
                    *(int *)(g + 0x1B8) < *(int *)(g + 0x434)) {
                    HeroMotionSequence *p = (HeroMotionSequence *)(g + 0x430);

                    p->ticks++;
                    while (p->index == -1 || p->ticks >= (((int)(p->entries[p->index].duration) * 5 + 2) / 6)) {
                        p->ticks = 0;
                        p->index++;
                        if (p->entries[p->index].initial != -999999.0f)
                            p->value = p->entries[p->index].initial * 0.00040000002f;
                    }
                    if (p->ticks > 0)
                        p->value += p->entries[p->index].acceleration * 0.00040000002f;
                    func_L00_002D38A0((char *)&D_00189E20 + 0xF0,
                                     (char *)&D_00189E20 + 0xF0, p->value);
                }
            }
        }
    }
}
