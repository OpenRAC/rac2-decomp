/* func_PAL_L00_0038D7E8, the PAL copy of func_L00_0038A748: the same C, where scale D_L00_001AEFA8. */
#include "common.h"

/* Trail object spawners. The object's 0x68 work block and the fields below are measured
 * views; the 0xFF written to both the alpha byte and +0x32 is one constant in retail. */
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits; float f[4]; } Vector4;

extern char *func_0029EFD0(int);
extern void func_0029F338(void *);
extern void func_002A0F48(void *);
extern void func_002833F0(void *, void *);
extern void func_002FE8D8(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern void func_00282D30(void *, void *, float);
extern float func_00283198(float);
extern float func_00283180(float);
extern void func_00283958(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_00282C88(void *);
extern int func_002FEC78(unsigned char *, unsigned int);
extern int func_002FED90(void *, void *, float, float, float);

extern char *D_0018C0B0[];
extern int D_L00_001AEFA8 __attribute__((sda));
typedef struct {
    char pad00[0x58];
    int f58;
    char pad5C[224 - 0x5C];
} TrailEntry;
extern TrailEntry D_L00_00262570[];

typedef struct {
    Quadword velocity;
    Quadword basis[3];
    int f40, f44, handle;
    short f4C;
    signed char f4E;
    unsigned char f4F;
    int f50;
    int pad54;
    float f58;
    int pad5C;
    int f60, f64;
    void *owner;
    int pad6C;
    int f70;
} TrailWork;

typedef struct {
    char pad00[0x10];
    Quadword position;
    unsigned char state;
    char pad21[0xB];
    float scale;
    unsigned char alpha;
    char pad31;
    unsigned short drawMask;
    unsigned short flags;
    char pad36[0x32];
    TrailWork *work;
} TrailMoby;

char *func_PAL_L00_0038D7E8(void *owner, Vector4 *position, Vector4 *velocity)
{
    Vector4 direction, forward, quaternion, axis;
    Vector4 rotation[3];
    char *object = func_0029EFD0(0x1367);
    TrailWork *work;
    float angle;
    if (object) {
        int initialState = 255;
        ((TrailMoby *)object)->flags |= 0x100;
        work = ((TrailMoby *)object)->work;
        ((TrailMoby *)object)->drawMask = initialState;
        ((TrailMoby *)object)->state = 0;
        ((TrailMoby *)object)->alpha = initialState;
        qcopy(&((TrailMoby *)object)->position, position);
        qcopy(&work->velocity, velocity);
        func_002833F0(object + 0xC0, D_0018C0B0[0] + 0xF0);
        func_002FE8D8(object + 0x10, &direction);
        func_00282F20(&forward, object + 0xE0, 1);
        func_00282DD8(&axis, &forward, &direction);
        angle = func_00282DB0(&forward, &direction) * 0.5f;
        func_00282D30(&quaternion, &axis, func_00283198(angle));
        quaternion.f[3] = func_00283180(angle);
        func_00283958(&quaternion, rotation);
        func_00283738(object + 0xC0, rotation, object + 0xC0);
        work->f64 = 0;
        work->f50 = 0;
        work->f44 = 0;
        work->f60 = 10;
        work->f4C = 1;
        work->f40 = (((int)(D_L00_001AEFA8) * 5 + 2) / 6);
        func_00282C88(&work->basis[0]);
        *(float *)&work->basis[0] = 1;
        work->basis[2] = work->basis[0];
        work->basis[1] = work->basis[0];
        work->f58 = 0.031415932f;
        work->owner = owner;
        work->handle = func_002FEC78((unsigned char *)object, 0);
        if (work->handle == -1) {
            func_0029F338(object);
            return 0;
        }
        work->f4F = func_002FED90(object, 0, 1, 1, 1);
        work->f4E = -1;
        work->f70 = 0;
        func_002A0F48(object);
    }
    return object;
}

/* Fields of objects whose layouts are not identified yet. */
extern Vector4 D_L00_001AEDC0 SDATA(D_L00_001AEDC0);
/* Measured input fields; other fields are not yet identified. */
typedef struct {
    char pad[0x10C];
    float axis;
    char pad110[8];
    float negative, positive;
    char pad120[0x80];
    int buttons;
} PlayerControl;
extern PlayerControl D_00138500, D_00138180;

/* The two returns give per-arm loads that jump2 cross-jumps into one lw. */

/* Updates two objects held in the owner's work area: places them from their basis
   vectors, scales and animates them. Then, for each, eases basis[i].z by the input
   axis (clamped to [-0.45, 0.35]), sets its alpha to 128 or pulses it depending on
   func_00282948 of a global counter, and when func_00282948 of its own counter is
   true, its alpha is 128 and a button in 0xE0 is down, sets that counter to 45 and
   calls func_L00_00384CA8 with a position and velocity taken from the object. The copy source is set before the loop: it gets no
   register and reload rematerializes it at the copy. */
