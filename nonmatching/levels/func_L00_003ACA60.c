/* func_L00_003ACA60 - 548 bytes.  Worker attempt, 27 October 2026 (draft below).

   Structure right (v[4] array gives retail stack layout pos/vel/start/dir =
   0/0x10/0x20/0x30), size should be 548. Remaining diff is register
   allocation + scheduling:
   - retail: s1=actor, s2=&pos (sp), s3=count, s4=&start, s5=&vel(sp+0x10),
   s0=&dir(sp+0x30), fp=dir copy; 10.0f (lui 0x4120/mtc1 f12) hoisted above
   the prologue stores; first qcopy stores via $sp, later reads via s2.
   - mine: actor lands in s3, pos pointer in s1, count in s2.
   Tried: scale before/after qcopy, Qword locals vs v[4], a `Qword *pos = v`
   pointer (decl-init and later assigned), single call to func_00338518 with
   if/else only setting size/color/speed (the two-call variant was +44 bytes).
   Needs: #include "common.h" (qcopy). Externs in draft. */

#include "common.h"
typedef int Qword __attribute__((mode(TI)));

typedef struct {
    char pad0[0x18];
    float scale;
} BurstSource;

typedef struct {
    char pad0[0x10];
    Qword pos;
    char pad20[0x48];
    BurstSource *source;
} BurstActor;

typedef struct {
    char pad0[2];
    unsigned char b2;
    unsigned char b3;
} BurstPart;

extern struct {
    char pad0[0x5C];
    unsigned char *tint;
} D_L00_001EE940;
extern char D_L00_0018A0E0[];
extern int func_002EF250(float);
extern float func_002EF240(int);
extern void func_002EE138(void *, void *, void *);
extern void func_002EE3D0(void *, void *, float);
extern void func_002EE178(void *, void *, float);
extern void func_002EE108(void *, void *, void *);
extern float func_0031A820(float, float);
extern float func_0031A7C0(float, float);
extern int func_0031A768(int, int);
extern int func_001163B0(void);
extern BurstPart *func_00338518(void *, void *, int, int, int, int, float, float, float, float, float);

void func_L00_003ACA60(BurstActor *self, Qword *at)
{
    Qword v[4];
    Qword *pos;
    float scale;
    int count;
    int i;

    scale = self->source->scale;
    pos = v;
    qcopy(pos, at);
    count = func_002EF250(scale * 10.0f);
    qcopy(&v[2], pos);

    func_002EE138(&v[3], (char *)self + 0x10, pos);
    func_002EE3D0(&v[3], &v[3], scale / func_002EF240(count));
    for (i = count; i > 0; i--) {
        int life, tint, size, color;
        float speed;
        BurstPart *p;

        life = func_002EF250(func_0031A820(1.0f, 3.0f));
        func_002EE178(&v[1], D_L00_0018A0E0, -(func_0031A7C0(0.2f, 1.0f) * 0.016666668f));
        tint = func_0031A768(30, 45);
        speed = func_0031A7C0(200.0f, 1000.0f);
        if (func_001163B0() & 2) {
            size = 0x20;
            color = 0x404040;
            speed += speed;
        } else {
            size = 0x40;
            color = 0x7F7F7F;
        }
        p = func_00338518(&v[2], &v[1], tint, size, color, life, 21000.0f, speed, 1.0f, 0.0f, 0.0f);
        func_002EE108(&v[2], &v[2], &v[3]);
        if (p) {
            p->b2 = *D_L00_001EE940.tint;
            p->b3 = size == 0x40 ? 0x44 : 0x48;
        }
    }
}
