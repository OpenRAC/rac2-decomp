#include "include_asm.h"

#include "common.h"
extern void func_00282CC0(void *, void *, void *);
extern void func_002B9180(void *);
extern int D_001A8BB0;
typedef struct {
    float vx, vy, vz;    
    char *owner;         
    float ox, oy, oz;    
    int *rec;            
} SparkMotion_C4D18;
extern float func_00283CE0(int);
extern void func_00282D30(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern int func_L00_0031C998(int, int, float);
extern int func_00282978(short *);

/* The velocity decays by 0.98 per frame. While D_001A8BB0 is clear the spark
   follows its owner (its offset moved by the velocity, then rotated by the
   owner's matrix at 0xC0) and dies with it; otherwise it drifts. */
void func_PAL_L00_0033E61C(char *self)
{
    float v[4], w[4], m[4];
    SparkMotion_C4D18 *p = (SparkMotion_C4D18 *)(self + 0x20);
    int *rec = p->rec;
    char *owner;

    *(float *)(self + 0xC) =
        func_00283CE0(*(short *)((char *)rec + 8) * (rec[3] - *(short *)(self + 0xA)) / rec[3]
                      + *(short *)((char *)rec + 0xA)) * 1000.0f;
    v[0] = p->vx;
    v[1] = p->vy;
    v[2] = p->vz;
    func_00282D30(v, v, 0.976f);
    p->vx = v[0];
    p->vy = v[1];
    p->vz = v[2];
    if (D_001A8BB0 == 0) {
        owner = p->owner;
        if (owner != 0 && *(unsigned char *)(owner + 0x20) != 0xFE && *(unsigned char *)(owner + 0x20) != 0xFD) {
            w[0] = p->ox;
            w[1] = p->oy;
            w[2] = p->oz;
            func_00282CC0(w, w, v);
            p->ox = w[0];
            p->oy = w[1];
            p->oz = w[2];
            func_00283098(m, w, p->owner + 0xC0);
            func_00282CC0(self + 0x10, p->owner + 0x10, m);
        } else {
            func_002B9180(self);
            return;
        }
    } else {
        func_00282CC0(self + 0x10, self + 0x10, v);
    }
    *(unsigned char *)(self + 8) = *(unsigned char *)(self + 8) + 1;
    *(int *)(self + 4) = func_L00_0031C998(rec[1], rec[0], (float)*(short *)(self + 0xA) / func_00283CE0(rec[3]));
    if (func_00282978((short *)(self + 0xA)) != 0)
        func_002B9180(self);
}
