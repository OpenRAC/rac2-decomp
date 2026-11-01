#include "include_asm.h"

#include "common.h"
extern void func_002AFFD8(void *pos, void *out, int mode);
extern void func_00282CC0(void *dst, void *a, void *b);
extern void func_00282F20(void *dst, void *src, float scale);
extern int func_002761F8(void *from, void *to, int mode, int filter, void *hit);
extern int func_00277258(float radius, void *pos, int mode, int filter);
extern void func_002E5CF8(int a, int b, void *object);
extern int func_00283CF0(float x);
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int, float, float, float, float,
                          int, float, int, int, int, int, int);
extern void func_00277F48(void *pos, int kind, int filter, void *hit, float amount);
extern int func_00282948(void *timer);
extern void func_0029F338(void *object);
extern void func_PAL_L09_003B26B8(void *object);
#define I(p, o) (*(int *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))
#define B(p, o) (*(unsigned char *)((p) + (o)))
typedef struct {
    float v[4];
    void *object;
    int flags;
    u8 a, b;
    u16 id;
    float radius;
    int mode;
} Hit_L09_003AEA88;

/* Moves the projectile, then explodes it on a hit or when its timer runs out, and destroys
   it then or once it leaves the 2..1021 world box; otherwise refreshes its orientation. */
void func_PAL_L16_003AC4A8(char *object)
{
    char *data = *(char **)(object + 0x68);
    float old[4] __attribute__((aligned(16)));
    float scratch[4] __attribute__((aligned(16)));
    float start[4] __attribute__((aligned(16)));
    Hit_L09_003AEA88 hit __attribute__((aligned(16)));

    qcopy(old, object + 0x10);
    func_002AFFD8(object + 0x10, scratch, 1);
    qcopy(start, object + 0x10);
    if (B(object, 0x20) == 0) {
        func_00282CC0(object + 0x10, object + 0x10, data + 0x30);
        hit.object = object;
        hit.flags = 0x10001;
        hit.radius = F(data, 0x54);
        hit.mode = 1;
        qcopy(hit.v, data + 0x30);
        func_00282F20(hit.v, hit.v, F(data, 0x60));
        hit.v[3] = 5627.925f;
        hit.a = B(data, 0x64);
        hit.b = B(data, 0x68);
        hit.id = *(u16 *)(object + 0xAA);
        if (func_002761F8(start, object + 0x10, 0, I(data, 0x40), &hit)
            || func_00277258(0.2f, object + 0x10, 0, I(data, 0x40))) {
            int r, g, b;

            func_002E5CF8(0, 0, object);
            r = func_00283CF0(F(data, 0x50) * 5.0f);
            g = func_00283CF0(F(data, 0x50) * 4.0f);
            b = func_00283CF0(F(data, 0x50) * 10.0f);
            func_PAL_002AC718(object, data + 0x30, 0, 0.0f, 0.0f, r, g, b, 0.0f, 0.0f, 9.0f, F(data, 0x50),
                          -1, 0.0f, 0, 1, -1, 0, 0x810001);
            func_00277F48(object + 0x10, 16, I(data, 0x40), &hit, 1.0f);
            func_0029F338(object);
            return;
        }
    }
    if (func_00282948(data + 0x48)) {
        int r, g, b;

        r = func_00283CF0(F(data, 0x50) * 5.0f);
        g = func_00283CF0(F(data, 0x50) * 4.0f);
        b = func_00283CF0(F(data, 0x50) * 10.0f);
        func_PAL_002AC718(object, data + 0x30, 0, 2.0f, F(data, 0x54), r, g, b, 0.0f, 0.0f, 9.0f, F(data, 0x50),
                      -1, 0.0f, 0, 1, -1, 0, 0x810001);
        func_0029F338(object);
        return;
    }
    if (F(object, 0x10) < 2.0f || F(object, 0x10) > 1021.0f || F(object, 0x14) < 2.0f
        || F(object, 0x14) > 1021.0f || F(object, 0x18) < 2.0f || F(object, 0x18) > 1021.0f) {
        func_0029F338(object);
        return;
    }
    func_PAL_L09_003B26B8(object);
}

