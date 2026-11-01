#include "include_asm.h"

#include "common.h"
extern float D_L05_001AFC58 __attribute__((sda));
extern float D_L05_001AFC54 __attribute__((sda));
extern char D_L05_001BFB00[];
extern void func_00282F20(void *, void *, float);
extern void func_002A8E20(void *, void *);
extern char *func_L05_003D1E60(void *, int, int);
extern float func_002A78D8(float, float);
extern float func_002A7940(void);
extern void func_002AF000(void *, float, float, float);
extern int func_002A7820(int, int);
extern char *func_PAL_002BE9A8(void *, int, float, float, float, void *, int, int, float);
extern int func_002A77E0(int);
struct HitRecord {
    float pos[4];
    void *obj;
    int flags;
    unsigned char type, subtype;
    unsigned short id;
    float damage;
    int one;
    char pad[12];
};

void func_PAL_L05_003D50B0(char *obj, char *input, float *output)
{
    struct HitRecord hit __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    int i;
    char *table;
    hit.flags = 0x810000;
    hit.obj = obj;
    if (*(int *)(input + 0x24))
        hit.damage = D_L05_001AFC58;
    else
        hit.damage = D_L05_001AFC54;
    hit.one = 1;
    qcopy(hit.pos, input);
    func_00282F20(&hit, &hit, 1.0f);
    table = D_L05_001BFB00;
    hit.pos[3] = 5627.9248046875f;
    hit.type = 3;
    hit.subtype = 2;
    hit.id = *(unsigned short *)(obj + 0xAA);
    if (*(char **)(table + 0x18))
        func_002A8E20(*(char **)(table + 0x18), &hit);
    func_L05_003D1E60(obj + 0x10, 0, 0);
    if (*(char **)(table + 0x18) && *(short *)(*(char **)(table + 0x18) + 0xAA) == 0x956) {
        float count = 20.0f, scale = 3.0f, spread = 2.0f;
        qcopy(pos, obj + 0x10);
        for (i = 0; (float)i < count; i++) {
            float a, b;
            char *p;
            output[0] = pos[0] + func_002A78D8(0.0f, spread);
            output[1] = pos[1] + func_002A78D8(0.0f, spread);
            output[2] = pos[2] + func_002A78D8(0.0f, spread);
            a = func_002A7940();
            b = func_002A7940();
            func_002AF000(vel, 0.060000002f, a, b);
            p = func_PAL_002BE9A8(output, func_002A7820(-3, 3), 0.0f, 1.0f, 1.0f, vel, 0x7FFFFFFF, 0, scale * 210000.0f);
            if (p) {
                char *q = p + 0x20;
                *(short *)(p + 0xA) = 100;
                *(unsigned char *)(p + 8) = func_002A77E0(255);
                p[3] = 0x44;
                *(int *)(q + 4) = 2;
                q[0xA] = 127;
                q[0xB] = *(unsigned char *)(p + 0xA);
            }
        }
    }
}

typedef int TI128 __attribute__((mode(TI)));
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002ACB48(void *, float);
extern float func_002A7878(float, float);
extern void func_L00_0033C0D0(void *, void *, void *, void *, int);
extern float D_L05_001AFC60[] SDATA(D_L05_001AFC60);
extern float D_L05_001AFC70[] SDATA(D_L05_001AFC70);
extern float D_L05_001AFC80[] SDATA(D_L05_001AFC80);

/* For each of two points in the object's frame, either side of it in Y, makes three copies of the
   point and passes each to func_L00_0033C0D0 with a random speed. */
void func_PAL_L05_003D5800(char *obj)
{
    float a[4] __attribute__((aligned(16)));
    float speed[4] __attribute__((aligned(16)));
    float p[4] __attribute__((aligned(16)));
    float p1[4] __attribute__((aligned(16)));
    float p2[4] __attribute__((aligned(16)));
    float p3[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float factor;
    float y;

    *(TI128 *)a = 0;
    a[0] = -0.21f;
    a[1] = 0.061f;
    *(TI128 *)speed = 0;
    a[2] = 0.045f;
    a[3] = 1.0f;
    func_00283098(p, a, obj + 0xC0);
    factor = 0.4f;
    func_00282CC0(p, p, obj + 0x10);
    p[3] = 0;
    qcopy(p1, p);
    qcopy(p2, p);
    qcopy(p3, p);
    func_002ACB48(p, 0.1f);
    func_002ACB48(p1, 0.1f);
    func_002ACB48(p2, 0.1f);
    func_002ACB48(p3, 0.1f);
    speed[0] = -(func_002A7878(30.0f, 40.0f) * (0.020000001f)) * factor;
    func_L00_0033C0D0(obj, p1, speed, D_L05_001AFC60, 1);
    speed[0] = -(func_002A7878(30.0f, 40.0f) * (0.020000001f)) * factor;
    func_L00_0033C0D0(obj, p2, speed, D_L05_001AFC70, 1);
    speed[0] = -(func_002A7878(30.0f, 40.0f) * (0.020000001f)) * factor;
    func_L00_0033C0D0(obj, p3, speed, D_L05_001AFC80, 1);
    y = -0.061f;
    *(TI128 *)b = 0;
    b[0] = -0.21f;
    b[1] = y;
    b[2] = 0.045f;
    b[3] = 1.0f;
    func_00283098(p, b, obj + 0xC0);
    func_00282CC0(p, p, obj + 0x10);
    p[3] = 0;
    qcopy(p1, p);
    qcopy(p2, p);
    qcopy(p3, p);
    func_002ACB48(p, 0.1f);
    func_002ACB48(p1, 0.1f);
    func_002ACB48(p2, 0.1f);
    func_002ACB48(p3, 0.1f);
    speed[0] = -(func_002A7878(30.0f, 40.0f) * (0.020000001f)) * factor;
    func_L00_0033C0D0(obj, p1, speed, D_L05_001AFC60, 1);
    speed[0] = -(func_002A7878(30.0f, 40.0f) * (0.020000001f)) * factor;
    func_L00_0033C0D0(obj, p2, speed, D_L05_001AFC70, 1);
    speed[0] = -(func_002A7878(30.0f, 40.0f) * (0.020000001f)) * factor;
    func_L00_0033C0D0(obj, p3, speed, D_L05_001AFC80, 1);
}
