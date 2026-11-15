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
extern char *func_002BDCE8(void *, int, float, float, float, void *, int, int, float);
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
/* Applies damage to the thing a shot hit and makes a small spray of sparks when the target is
   a special one. */
void func_L05_003D1368(char *obj, char *input, float *output)
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
    vec_scale_to_length(&hit, &hit, 1.0f);
    table = D_L05_001BFB00;
    hit.pos[3] = 5627.9248046875f;
    hit.type = 3;
    hit.subtype = 2;
    hit.id = *(unsigned short *)(obj + 0xAA);
    if (*(char **)(table + 0x18))
        QueueMobyImpact(*(char **)(table + 0x18), &hit);
    func_L05_003D1E60(obj + 0x10, 0, 0);
    if (*(char **)(table + 0x18) && *(short *)(*(char **)(table + 0x18) + 0xAA) == 0x956) {
        float count = 20.0f, scale = 3.0f, spread = 2.0f;
        qcopy(pos, obj + 0x10);
        for (i = 0; (float)i < count; i++) {
            float a, b;
            char *p;
            output[0] = pos[0] + RandomSignedFloatRange(0.0f, spread);
            output[1] = pos[1] + RandomSignedFloatRange(0.0f, spread);
            output[2] = pos[2] + RandomSignedFloatRange(0.0f, spread);
            a = RandomAngle();
            b = RandomAngle();
            BuildSphericalOffset(vel, 0.05000000447034836f, a, b);
            p = SpawnSpinningSparkParticle(output, RandomIntRange(-3, 3), 0.0f, 1.0f, 1.0f, vel, 0x7FFFFFFF, 0, scale * 210000.0f);
            if (p) {
                char *q = p + 0x20;
                *(short *)(p + 0xA) = 120;
                *(unsigned char *)(p + 8) = RandomIntBelow(255);
                p[3] = 0x44;
                *(int *)(q + 4) = 2;
                q[0xA] = 127;
                q[0xB] = *(unsigned char *)(p + 0xA);
            }
        }
    }
}
