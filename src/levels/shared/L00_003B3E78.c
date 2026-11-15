#include "include_asm.h"
#include "common.h"

typedef int Quadword_L00_003B3E78 __attribute__((mode(TI)));
typedef union {
    Quadword_L00_003B3E78 bits;
    float f[4];
} Vec4_L00_003B3E78;

typedef struct {
    unsigned char pad0[4];
    int w4;
    unsigned char pad8[2];
    unsigned char ba;
    unsigned char bb;
} Sub_L00_003B3E78;

extern float D_001AF908 __attribute__((sda));
extern int D_001AF918 __attribute__((sda));
extern unsigned short D_001AF91C __attribute__((sda));
extern float D_001AF920 __attribute__((sda));
extern float D_001AF924 __attribute__((sda));
extern int D_001AF928 __attribute__((sda));
extern unsigned char D_001AF92C __attribute__((sda));
extern float D_001AF930 __attribute__((sda));
extern float g_camera_l00_position[];

extern void FastVecSub(void *, void *, void *);
extern float IntToFloat(int);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void vec_scale_to_length(void *, void *, float);
extern int math_random_int_below(int);
extern u8 *SpawnSpinningSparkParticle(u8 *p, float fa, float fb, float fc, float fd, int v, void *local, int a3, int t0);

/* Throws out a ring of spark particles in all directions around the object. */
void part_l00_spawn_spark_ring(u8 *obj)
{
    Vec4_L00_003B3E78 axis;
    Vec4_L00_003B3E78 w;
    Vec4_L00_003B3E78 a;
    Vec4_L00_003B3E78 b;
    float step;
    int i;

    axis.bits = 0;
    axis.f[2] = D_001AF908;
    FastVecSub(&w, g_camera_l00_position, obj + 0x10);
    step = 6.2831855f / IntToFloat(D_001AF918);
    for (i = 0; i < D_001AF918; i++) {
        u8 *e;
        int r;
        math_apply_axis_rotation_to_quat(&a, &axis, &w, (float)i * step);
        vec_scale_to_length(&b, &a, D_001AF920 * 0.016666668f);
        r = math_random_int_below(16);
        if (math_random_int_below(2) != 0) {
            r = -r;
        }
        e = SpawnSpinningSparkParticle(obj + 0x10, 0.5f, 1.0f, D_001AF930, D_001AF924 * 210000.0f, r, &b, D_001AF928, 0);
        if (e != 0) {
            Sub_L00_003B3E78 *q = (Sub_L00_003B3E78 *)(e + 0x20);
            *(unsigned short *)(e + 0xA) = D_001AF91C;
            q->w4 = 2;
            q->ba = D_001AF92C;
            q->bb = e[0xA];
        }
    }
}
