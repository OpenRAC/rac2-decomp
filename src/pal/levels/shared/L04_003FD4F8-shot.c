#include "common.h"
typedef int QuadWord __attribute__((mode(TI)));
extern void *func_0029EFD0(int);
extern float func_002A7878(float, float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(char *, char *, float);
typedef struct { float v[4]; void *owner; int flags; unsigned char mode, enabled; unsigned short kind; float radius; int active; } SweepProbe;
extern float func_00282E20(void *);
extern float func_00283248(float, float);
extern void func_00282F70(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern char D_L04_001BFAE0[];
extern char D_L04_001BFB00[];
extern char D_L04_001A8F20[] __attribute__((sda));
extern void func_00283028(void *, void *, void *);
extern float func_00282DF0(void *);
extern int func_002A7820(int, int);
extern void func_L04_00358AE8(void *, void *, unsigned int, int, float);
extern void func_L04_00358868(void *, unsigned int, int, int, float);
extern unsigned char *func_L04_0035F3E0(void *, void *, int, float);
extern void func_PAL_L04_003FDE38(void *, int);
extern void func_0029F338(void *);
extern float func_002A7AA8(float, float, float, float, float);

/* func_PAL_L04_003FD4F8, the PAL copy of func_L04_003F9320: the same C, where the spark speed
 * range 0.05-0.1 becomes 0.06-0.12, the spark life 10-15 becomes 8-12, and the callee
 * func_L04_003F9C60 becomes func_PAL_L04_003FDE38. */

/* Spawns a shot moby at pos heading along velocity. If the sweep from the owner to pos is
 * blocked, it bursts into sparks and is deleted at once; otherwise it gets 17 trail particles.
 * The owner is kept as an int: a pointer parameter would let the start-vector load
 * be scheduled above the probe stores. */
unsigned char *func_PAL_L04_003FD4F8(int owner, float *pos, float *velocity, int life)
{
    float origin_buf[4], direction_buf[4];
    float *origin = origin_buf, *direction = direction_buf;
    SweepProbe probe;
    float start[4], temp[4], random[4];
    unsigned char *m, *v, *particle;
    int i, j;
    unsigned short kind;
    float t, alpha, numerator, denominator;
    *(QuadWord *)origin = *(QuadWord *)pos;
    *(QuadWord *)direction = *(QuadWord *)velocity;
    m = func_0029EFD0(0xABC);
    if (m) {
        v = *(unsigned char **)(m + 0x68);
        *(void **)(v + 0x18) = (void *)owner;
        m[0x30] = 0x7F;
        *(short *)(m + 0x32) = 0x7F;
        m[0x31] = 1;
        *(long *)(m + 0x38) = *(long *)(owner + 0x38);
        *(float *)(m + 0xF0) = 0;
        *(float *)(m + 0xF4) = -func_00283248(func_00282E20(direction), direction[2]);
        *(float *)(m + 0xF8) = func_00283248(direction[0], direction[1]);
        qcopy((m + 0x10), origin);
        qcopy(v, direction);
        *(int *)(v + 0x10) = life;
        *(int *)(v + 0x14) = life;
        probe.owner = *(void **)(v + 0x18);
        probe.flags = 0x30000;
        probe.radius = 13.0f;
        probe.active = 1;
        *(QuadWord *)probe.v = *(QuadWord *)v;
        func_00282F70(&probe, &probe, 1.0f);
        probe.v[2] = 1;
        probe.v[3] = 5627.9248046875f;
        probe.mode = 1;
        probe.enabled = 1;
        kind = *(unsigned short *)(m + 0xAA);
        *(QuadWord *)start = *(QuadWord *)(owner + 0x10);
        probe.kind = kind;
        start[2] = origin[2];
        if (func_002761F8(start, origin, 0, (void *)owner, &probe)) {
            qcopy((m + 0x10), D_L04_001BFAE0);
            for (i = 4; i >= 0; i--) {
                *(QuadWord *)random = 0;
                random[0] = func_002A7878(-1, 1);
                random[1] = func_002A7878(-1, 1);
                random[2] = func_002A7878(-1, 1);
                *(QuadWord *)temp = *(QuadWord *)random;
                func_00283028(random, v, D_L04_001BFB00);
                func_00282F20((char *)temp, (char *)temp, func_00282DF0(random) * 0.5f);
                func_00282CC0(random, random, temp);
                func_00282F20((char *)random, (char *)random, func_002A7878(0.060000002f, 0.120000005f));
                func_L04_00358AE8(m + 0x10, random, 0x7F2F4F6F, func_002A7820(8, 12), 15000);
            }
            func_PAL_L04_003FDE38(m, 0);
            func_0029F338(m);
            return 0;
        }
        func_L04_00358868(m, 0x2F4F7F7F, *(int *)(v + 0x10), -1, 100000);
        for (j = 0; j < 17; j++) {
            particle = func_L04_0035F3E0(m + 0x10, D_L04_001A8F20, 1, 0);
            if (particle) {
                *(float *)(particle + 0xC) = func_002A7878(15000, 25000);
                numerator = func_00283CE0(j);
                denominator = func_00283CE0(16);
                t = func_002A7AA8(-1.5f, 0, 1, 0, numerator / denominator);
                *(float *)(particle + 0xC) += (8000.0f - *(float *)(particle + 0xC)) * t;
                alpha = t * -64.0f + 128.0f;
                *(unsigned int *)(particle + 4) = (func_00283CF0(alpha) << 24) | 0xFFFFFF;
                *(void **)(v + 0x1C + j * 4) = particle;
            } else *(void **)(v + 0x1C + j * 4) = 0;
        }
    }
    return m;
}
