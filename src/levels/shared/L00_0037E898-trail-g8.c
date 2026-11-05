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
extern unsigned char D_00139591[];
extern int D_L00_001AEFA8 __attribute__((sda));
extern int D_L00_001AEF48 __attribute__((sda));

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

char *func_L00_00387CA8(Vector4 *position, Vector4 *velocity)
{
    Vector4 direction, forward, quaternion, axis;
    Vector4 rotation[3];
    char *object = func_0029EFD0(0x1366);
    TrailWork *work;
    float angle;
    if (object) {
        int initialState = 255;
        ((TrailMoby *)object)->scale *= 0.75f;
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
        work->owner = 0;
        work->f60 = (D_L00_00262570 + D_00139591[0])->f58;
        work->f64 = 0;
        work->f50 = 0;
        work->f44 = 0;
        work->f4C = 1;
        work->f40 = D_L00_001AEF48;
        func_00282C88(&work->basis[0]);
        *(float *)&work->basis[0] = 1;
        work->basis[2] = work->basis[0];
        work->basis[1] = work->basis[0];
        work->f58 = 0.026179943f;
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

char *func_L00_0038A748(void *owner, Vector4 *position, Vector4 *velocity)
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
        work->f40 = D_L00_001AEFA8;
        func_00282C88(&work->basis[0]);
        *(float *)&work->basis[0] = 1;
        work->basis[2] = work->basis[0];
        work->basis[1] = work->basis[0];
        work->f58 = 0.026179943f;
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
#define FIELD(type, p, off) (*(type *)((char *)(p) + (off)))

extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_002AEC18(void *, int);
extern void func_002A05A8(char *);
extern float func_002AA2E8(float *, float, float);
extern int func_00282948(int *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void *func_L00_00384CA8(void *, void *, void *, unsigned int);
extern int func_002E5CF8(int, int, char *);

extern char D_L00_001B8DC0[];
extern float D_L00_001AEDA0[2] __attribute__((sda));
extern int D_L00_001AEDA8[2] __attribute__((sda));
extern float D_L00_001AEDB0 __attribute__((sda));
extern float D_L00_001AEDB4 __attribute__((sda));
extern float D_L00_001AEDBC __attribute__((sda));
extern int D_L00_001AEDD0[2] __attribute__((sda));
extern Vector4 D_L00_001AEDC0 SDATA(D_L00_001AEDC0);
extern int D_L00_001B19C8;

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

typedef struct {
    Vector4 basis[2];
    Vector4 motion[2];
    int timers[2];
    char *objects[2];
} AttachmentWork;

/* The two returns give per-arm loads that jump2 cross-jumps into one lw. */
static inline int pad_buttons(int i)
{
    if (i)
        return D_00138180.buttons;
    return D_00138500.buttons;
}

/* Updates two objects held in the owner's work area: places them from their basis
   vectors, scales and animates them. Then, for each, eases basis[i].z by the input
   axis (clamped to [-0.45, 0.35]), sets its alpha to 128 or pulses it depending on
   func_00282948 of a global counter, and when func_00282948 of its own counter is
   true, its alpha is 128 and a button in 0xE0 is down, sets that counter to 45 and
   calls func_L00_00384CA8 with a position and velocity taken from the object. The copy source is set before the loop: it gets no
   register and reload rematerializes it at the copy. */
void func_L00_00384248(char *owner)
{
    AttachmentWork *work = FIELD(AttachmentWork *, owner, 0x68);
    Vector4 position, velocity;
    float scale, step, input, target, phase, period;
    int i, alpha;
    Vector4 *source;

    for (i = 0; i < 2; ++i) {
        func_00283098(work->objects[i] + 0x10, &work->basis[i], D_L00_001B8DC0 + 0x230);
        func_00282CC0(work->objects[i] + 0x10, work->objects[i] + 0x10, D_L00_001B8DC0);
        FIELD(float, work->objects[i], 0x2C) =
            FIELD(float, FIELD(char *, work->objects[i], 0x24), 0x24) * D_L00_001AEDA0[i];
        func_002AEC18(work->objects[i], D_L00_001AEDA8[i]);
        func_002A05A8(work->objects[i]);
        func_002A0F48(work->objects[i]);
    }
    scale = D_L00_001AEDB0 * 0.016666668f;
    step = D_L00_001AEDBC * 0.00027777778f;
    source = &D_L00_001AEDC0;
    for (i = 0; i < 2; ++i) {
        if (i)
            input = D_00138180.axis;
        else
            input = D_00138500.axis;
        if (input == 0.0f) {
            if (i)
                input = D_00138180.positive - D_00138180.negative;
            else
                input = D_00138500.positive - D_00138500.negative;
        }
        target = -input * scale;
        if (target != 0.0f)
            func_002AA2E8(&work->motion[i].f[2], target, step);
        else
            func_002AA2E8(&work->motion[i].f[2], 0.0f, step + step);
        work->basis[i].f[2] += work->motion[i].f[2];
        if (work->basis[i].f[2] > 0.35f) {
            work->basis[i].f[2] = 0.35f;
            if (work->motion[i].f[2] > 0.0f)
                work->motion[i].f[2] = 0.0f;
        } else if (work->basis[i].f[2] < -0.45f) {
            work->basis[i].f[2] = -0.45f;
            if (work->motion[i].f[2] < 0.0f)
                work->motion[i].f[2] = 0.0f;
        }
        if (func_00282948(&D_L00_001AEDD0[i])) {
            FIELD(unsigned char, work->objects[i], 0x23) = 128;
        } else {
            phase = func_00283CE0(D_L00_001B19C8 % 60);
            period = func_00283CE0(60);
            phase *= 6.2831855f;
            phase /= period;
            alpha = func_00283CF0(func_00283198(phase - 3.1415927f) * 10.0f) + 20;
            FIELD(unsigned char, work->objects[i], 0x23) = alpha;
        }
        if (func_00282948(&work->timers[i])
            && FIELD(unsigned char, work->objects[i], 0x23) == 128
            && (pad_buttons(i) & 0xE0)) {
            work->timers[i] = 45;
            position.bits = source->bits;
            if (!i)
                position.f[1] -= 0.05f;
            func_00283098(&position, &position, work->objects[i] + 0xC0);
            func_00282CC0(&position, &position, work->objects[i] + 0x10);
            func_00282F20(&velocity, work->objects[i] + 0xC0, D_L00_001AEDB4 * 0.016666668f);
            func_L00_00384CA8(work->objects[i], &position, &velocity, i);
            func_002E5CF8(0, 0, work->objects[i]);
        }
    }
}
