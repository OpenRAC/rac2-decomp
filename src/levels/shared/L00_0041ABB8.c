#include "include_asm.h"

typedef int TI128 __attribute__((mode(TI)));

extern int func_2DB350(TI128 *dst, float f);

extern void func_L00_0041AEF8_1(void *dst);

extern long long func_0027C878(int id);

extern float func_00283248(float x, float y);

extern float func_00282E20(void *vec);

extern float func_00282E80(void *a, void *b);

extern void func_00282CF0(void *dst, void *a, void *b);

extern void func_00282F20(void *dst, void *src, float scale);

extern void func_00283410(void *dst, void *src);

extern void func_00282D30(void *dst, void *src, float scale);

extern void func_00280B90(void *dst, void *src, int flag);

extern float func_002A7940(void);

/* The parts of a moby that func_L00_004208C8 reads. */
typedef struct {
    char pad0[0x18];
    float height;                 /* 0x18 */
    char pad1C[0xAA - 0x1C];
    short type;                   /* 0xAA */
} GroundMoby;

/* The hero fields func_L00_004208C8 reads; ground is the moby the hero stands on. */
typedef struct {
    char pad0[0x33C];
    GroundMoby *ground;           /* 0x33C */
    char pad340[8];
    short flag348;                /* 0x348 */
    char pad34A[0x2294 - 0x34A];
    int state;                    /* 0x2294 */
} HeroMove;

/* The level object at D_L00_001B8E20, as func_L00_004208C8 reads it. */
typedef struct {
    char pad0[0x30];
    TI128 axis;                   /* 0x30 */
    char pad40[0x40];
    TI128 v80;                    /* 0x80 */
    char pad90[0x14];
    float fA4;                    /* 0xA4 */
} CamMove;

/* The view part of an object's state (state + 0x60). */
typedef struct {
    TI128 v00;                    /* 0x00 */
    TI128 v10;                    /* 0x10 */
    char pad20[0x10];
    TI128 v30;                    /* 0x30 */
    char pad40[0x20];
    TI128 v60;                    /* 0x60 */
    char pad70[0x20];
    TI128 v90;                    /* 0x90 */
    char padA0[0x58];
    GroundMoby *ground;           /* 0xF8 */
    float groundHeight;           /* 0xFC */
} MoveView;

/* The object's state (object + 0x70). */
typedef struct {
    TI128 v00;                    /* 0x00 */
    short h10;                    /* 0x10 */
    char pad12[0x60 - 0x12];
    MoveView view;                /* 0x60 */
    char pad160[0x1E0 - 0x160];
    float f1E0;                   /* 0x1E0 */
} MoveState;

/* The object whose position and state func_L00_004208C8 moves. */
typedef struct {
    char pad0[0x30];
    TI128 position;               /* 0x30 */
    char pad40[0x30];
    MoveState *state;             /* 0x70 */
} MoveObject;

extern HeroMove D_00189E20;

extern int D_L00_001A8FF0[] __attribute__((sda));

extern CamMove D_L00_001B8E20;

extern int D_L00_001B9084;

extern void func_00282CC0(void *dst, void *a, void *b);

extern float func_00282DB0(void *a, void *b);

#ifndef RAC2_T_OBJ_0014C80
#define RAC2_T_OBJ_0014C80
/* the resident object at D_0014C80; only its vector at +0x140 is read here */
typedef struct {
    char pad[0x140];
    float f140;
    float f144;
    float f148;
} OBJ_0014C80;
#endif

extern OBJ_0014C80 D_0014C80;

#ifndef RAC2_T_BLOCK_F043C77A5
#define RAC2_T_BLOCK_F043C77A5
typedef struct { int q[4]; } BLOCK_F043c77a5;
#endif

#ifndef RAC2_T_LOC_F043C77A5
#define RAC2_T_LOC_F043C77A5
typedef struct {
    BLOCK_F043c77a5 b0;
    BLOCK_F043c77a5 b1;
    BLOCK_F043c77a5 b2;
    BLOCK_F043c77a5 b3;
    int   k0, k1, k2, k3;
    int   z80, z84, z88;
    float f92, f96;
    int   z100;
    float f104, f108;
    long long v112;
    long long v120;
    long long v128;
    long long v136;
    float m00, m01, m02, m03;
    float m10, m11, m12, m13;
    float m20, m21, m22, m23;
    float v192, v196, v200, v204;
    float v208, f212, f216, v220;
} LOC_F043c77a5;
#endif

extern int func_002ABB78(char *object);

extern float *func_002AB1F0(char *object);

extern float func_002702C8_1(int *dst, float a, float b, float c, float d, float e);



/* shared native body of family 5a97ab89858c */
void func_L00_0041AEF8(char *p)
{
    *(long long *)(p + 112) = 0;
    *(float *)(p + 8) = -1.0f;
    *(float *)(p + 24) = 1.0f;
    *(float *)(p + 40) = -1.0f;
    *(float *)(p + 56) = 1.0f;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}

/* shared native body of family 9a8a2404 */
void func_L00_0041AF60(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 8) = 0;
    *(float *)(p + 24) = 2.0f;
    *(int *)(p + 40) = 0;
    *(float *)(p + 4) = -1.0f;
    *(float *)(p + 36) = 1.0f;
    *(float *)(p + 52) = 1.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 56) = 2.0f;
    *(float *)(p + 20) = -1.0f;
    *(float *)(p + 60) = 1.0f;
}


/* fills a local record with the level's fixed fields, measures two angles against the
   resident vector at D_0014C80, adds a quarter of the cross product of that vector with
   the position, and hands the record to the level's matrix builder */
void func_L00_0041AFD8(void *unused, float *a, int k, float f)
{
    LOC_F043c77a5 local;
    float v[3];
    float x;

    func_L00_0041AEF8_1(&local);
    local.z80 = 0;
    local.f92 = 1.0f;
    local.f96 = 1.0f;
    local.f104 = 1.0f;
    local.f108 = 1.0f;
    local.z84 = 0;
    local.z88 = 0;
    local.z100 = 0;
    local.v120 = func_0027C878(44);
    local.v128 = 0x0000FF9000000260LL;
    local.v136 = 0x0000008000000048LL;
    local.k3 = k;
    local.k2 = k;
    local.k1 = k;
    local.k0 = k;
    local.v112 = 0;
    local.v220 = 0.0f;
    local.f216 = func_00283248(D_0014C80.f140 - a[0], D_0014C80.f144 - a[1]);
    x = func_00282E80(a, &D_0014C80.f140);
    local.f212 = -func_00283248(x, D_0014C80.f148 - a[2]);
    local.v208 = func_002A7940();
    func_00283410(&local.m00, &local.v208);
    func_00282CF0(v, &D_0014C80.f140, a);
    func_00282F20(v, v, 0.25f);
    local.v192 = a[0] + v[0];
    local.v196 = a[1] + v[1];
    local.v200 = a[2] + v[2];
    local.v204 = 1.0f;
    func_00282D30(&local.b0, &local.b0, f);
    func_00282D30(&local.b1, &local.b1, f);
    func_00282D30(&local.b2, &local.b2, f);
    func_00282D30(&local.b3, &local.b3, f);
    func_00280B90(&local, &local.m00, 0);
}

INCLUDE_ASM("asm/levels", func_L00_0041B1B8);

/* func_L00_0041B840 is in L00_0041ABB8-ring-g8.c. */

INCLUDE_ASM("asm/levels", func_L00_0041BCC8);

/* Builds a 224-byte local record, writes a looked-up handle and fixed fields, calls bound float helpers, invokes one bound helper on each of four blocks, and passes the record to a final bound helper. */
void func_L00_0041C160(void *unused, float *b, float *a, int k, float f)
{
    LOC_F043c77a5 local;
    float x;

    func_L00_0041AEF8_1(&local);
    local.z80 = 0;
    local.f92 = 1.0f;
    local.f96 = 1.0f;
    local.f104 = 1.0f;
    local.f108 = 1.0f;
    local.z84 = 0;
    local.z88 = 0;
    local.z100 = 0;
    local.v120 = func_0027C878(11);
    local.v128 = 0xFF9000000260LL;
    local.v136 = 0x0000008000000048LL;
    local.k3 = k;
    local.k2 = k;
    local.k1 = k;
    local.k0 = k;
    local.v112 = 0;
    local.v220 = 0.0f;
    local.f216 = func_00283248(a[0], a[1]);
    x = func_00283248(func_00282E20(a), a[2]);
    local.f212 = -x;
    local.v208 = 0.0f;
    func_00283410(&local.m00, &local.v208);
    local.v192 = b[0];
    local.v196 = b[1];
    local.v200 = b[2];
    local.v204 = 1.0f;
    func_00282D30(&local.b0, &local.b0, f);
    func_00282D30(&local.b1, &local.b1, f);
    func_00282D30(&local.b2, &local.b2, f);
    func_00282D30(&local.b3, &local.b3, f);
    func_00280B90(&local, &local.m00, 0);
}




extern int func_L00_0032A088(int id, int index);

extern void func_002FEE50(int index);

extern void func_0029F338(void *object);

extern int *func_L00_0032A0B8(int id, int index);

extern float func_002A7878(float a, float b);

extern int func_00283CF0(float value);

extern void func_L00_002EBE88(int a0, int a1, int a2, int a3, int a4, int a5,
                              float f12, float f13, float f14);

extern void func_L00_0041E648(void *self, int flags, int mode);

extern unsigned char D_00139568[];

extern unsigned char D_L00_00262570[];

#ifndef RAC2_T_ENTRY_262570
#define RAC2_T_ENTRY_262570
/* one 224-byte record of the level's table: the flag byte sits at +4 */
typedef struct {
    unsigned char pad000[4];
    unsigned char flag;
} Entry262570;
#endif

/* Looks the object's record up in the level's table (the resident byte at D_00139568 + 0x16
   is the record's number), asks the level's builder for a matrix with the flags the object's
   own word selects, then reads the record's two colour bytes and hands the level's renderer
   the object's record. */
void func_L00_0041E4A8(void *arg0)
{
    unsigned char *self = arg0;
    unsigned char *rec;
    int handle;
    int flags;
    int mode;
    int base;
    float scale;
    unsigned int c1;
    unsigned int c2;

    rec = *(unsigned char **)(self + 0x68);
    handle = func_L00_0032A088(*(int *)(rec + 0x50), *(int *)(rec + 0x3C));
    if (handle == 0) {
        func_002FEE50(*(int *)(rec + 0x6C));
        func_0029F338(self);
    } else {
        if (((Entry262570 *)(D_L00_00262570 + D_00139568[0x16] * 224))->flag != 0) {
            flags = 0x802080;
            if (*(int *)(rec + 0x68) != 0)
                flags = 0x802020;
            mode = 0x7F;
        } else {
            flags = 0x202080;
            mode = 0x50;
        }
        func_L00_0041E648(self, flags, mode);
        if (((Entry262570 *)(D_L00_00262570 + D_00139568[0x16] * 224))->flag == 0)
            return;
        base = handle + func_L00_0032A0B8(*(int *)(rec + 0x50), *(int *)(rec + 0x3C))[2];
        scale = func_002A7878(0.5f, 1.0f);
        c1 = (unsigned int)func_00283CF0(scale * 127.0f) << 24;
        c2 = (unsigned int)func_00283CF0(scale * 48.0f) << 24;
        func_L00_002EBE88(*(int *)((char *)base + *(int *)(rec + 0x30) * 4),
                          0x17, 0xE, 0x7,
                          0xFF5050 | c1, 0xFF1010 | c2,
                          0.0f, 3.0f, 0.0f);
    }
}


/* func_L00_0041EB38 is in L00_0041ABB8-shot-g8.c. */

INCLUDE_ASM("asm/levels", func_L00_0041EE58);



INCLUDE_ASM("asm/levels", func_L00_0041FC20);

extern float D_L00_001B8DC0[];

extern float func_002A7878(float a, float b);

extern float func_002A78D8(float a, float b);

extern int func_00283CF0(float a);

extern float func_00283B98(float a, float b);

extern void func_002AF000(float *p, float a, float b, float c);

extern void func_002C16C0(float *out, float *in, int a2, int a3, unsigned int a4, int a5,
                           float f1, float f2, float f3, float f4, float f5);

/* Points the level's fixed vector at the given position, then spawns twenty
   particles around it, each one a random offset along the fixed vector.
   `size` is written but never read: that second reference to 210000.0f is what
   makes the compiler hold the constant in a saved float register ($f29) instead
   of rematerialising it at the call, which is what the retail does. */
void func_L00_004200F0(float *pos)
{
    float v[4];
    float dir[4];
    float out[4];
    float f20;
    float f21;
    float f28;
    float size;
    float r;
    int n;
    int id;

    func_00282CF0(v, D_L00_001B8DC0, pos);
    f28 = func_00283248(v[0], v[1]);
    n = 19;
    do {
        n--;
        f21 = func_002A7878(0.5f, 1.0f);
        id = func_00283CF0(func_002A78D8(1.0f, 2.0f));
        size = func_002A7878(0.05f, 0.2f) * 210000.0f;
        f20 = func_002A7878(0.0f, 1.3962636f);
        r = func_00283B98(f28, func_002A78D8(0.0f, 1.3962636f));
        func_002AF000(dir, f21 * (1.0f / 60.0f), r, f20);
        r = func_002A78D8(0.0f, 0.1f);
        out[0] = pos[0] + r;
        r = func_002A78D8(0.0f, 0.1f);
        out[1] = pos[1] + r;
        r = func_002A78D8(0.0f, 0.1f);
        out[2] = pos[2] + r;
        func_002C16C0(out, dir, 30, 127, 0x7F7F7F, id,
                      func_002A7878(0.05f, 0.2f) * 210000.0f, 500.0f, 1.0f, 0.0f, 1.0f);
    } while (n >= 0);
}

/* calls two guards and returns 1 only when both succeed and the object's float field is not positive */
int func_L00_00420310(char *object)
{
    float *p;

    if (func_002ABB78(object) != 0)
        return 0;
    p = func_002AB1F0(object);
    if (p == 0)
        return 0;
    if (0.0f < *p)
        return 0;
    return 1;
}


int func_L00_004204A0(TI128 *src)
{
    TI128 local;

    local = *src;
    return func_2DB350(&local, 0.0f) != 0;
}

/* Moves the object, its state's vectors and the view by the input step. While the hero
   stands on the same moby (hero +0x33C), a rise of that moby's height (+0x18) since the
   last frame raises the step's height. Then the step's component along the axis at
   D_L00_001B8E20 + 0x30 goes to the view's vector at +0x10, and in hero states 11 and 12
   the off-axis part is cancelled again with the vector at +0x80 scaled by +0xA4. */
void func_L00_004208C8(MoveObject *object, TI128 *input)
{
    TI128 delta, projected, correction, remainder;
    TI128 *step = &delta;
    CamMove *cam = &D_L00_001B8E20;
    MoveState *state = object->state;
    MoveView *view = &state->view;
    GroundMoby *ground;
    float height, along;

    delta = *input;
    ground = D_00189E20.ground;
    if (ground != 0) {
        if (D_L00_001A8FF0[0] == 0) {
            if (D_00189E20.flag348 == 0) {
                if (ground == view->ground) {
                    height = ground->height - view->groundHeight;
                    if (height > 0.0f && ((float *)step)[2] < height)
                        ((float *)step)[2] = height;
                    view->groundHeight = D_00189E20.ground->height;
                } else {
                    view->ground = ground;
                    view->groundHeight = D_00189E20.ground->height;
                }
            } else
                view->ground = 0;
        } else
            view->ground = 0;
    } else
        view->ground = 0;

    func_00282CC0(&object->position, step, &object->position);
    func_00282CC0(&view->v60, step, &view->v60);
    func_00282CC0(&view->v00, step, &view->v00);
    func_00282CC0(&view->v90, step, &view->v90);
    func_00282CC0(&view->v30, step, &view->v30);
    func_00282CC0(&state->v00, step, &state->v00);
    along = func_00282DB0(step, &cam->axis);
    func_00282D30(&projected, &cam->axis, along);
    func_00282CC0(&view->v10, &view->v10, &projected);
    if (D_00189E20.flag348 == 0 &&
        !(D_00189E20.ground != 0 && D_00189E20.ground->type == 0x22D &&
          D_L00_001B9084 < 31))
        object->state->f1E0 = ((float *)step)[3];
    if ((unsigned int)(D_00189E20.state - 11) < 2) {
        MoveState *next = object->state;

        next->h10 = 0;
        func_00282D30(&correction, &cam->v80, cam->fA4);
        along = func_00282DB0(&cam->axis, step);
        func_00282D30(&remainder, &cam->axis, along);
        func_00282CF0(&remainder, step, &remainder);
        func_00282CF0(&correction, &correction, &remainder);
        func_00282CC0(&object->position, &correction, &object->position);
        func_00282CC0(&view->v60, &correction, &view->v60);
        func_00282CC0(&view->v00, &correction, &view->v00);
        func_00282CC0(&view->v90, &correction, &view->v90);
        func_00282CC0(&next->v00, &correction, &next->v00);
    }
}

INCLUDE_ASM("asm/levels", func_L00_00420C38);


/* reads a base pointer from a0+112 and pushes three consecutive tweak slots through the same five-float interpolation helper, writing each result back over the first float vector while forwarding three trailing floats unchanged. */
void func_L00_004219D8(char *a0, float *a1, float *a2,
                                        float f12, float f13, float f14)
{
    int *p = *(int **)(a0 + 112);

    a1[0] = func_002702C8_1(p + 64, a1[0], a2[0], f12, f13, f14);
    a1[1] = func_002702C8_1(p + 65, a1[1], a2[1], f12, f13, f14);
    a1[2] = func_002702C8_1(p + 66, a1[2], a2[2], f12, f13, f14);
}



/* func_L00_00422268 is in L00_0041ABB8-g8.c. */
