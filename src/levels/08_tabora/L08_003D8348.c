#include "common.h"

typedef struct {
    u8 pad00[0x20];
    float hit[4];
    float adjusted[4];
    float normal[4];
} CollisionResult;

extern CollisionResult D_L08_001BFF40;
extern int func_00277258(void *, int, void *, float);
extern void func_00283028(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_0029F338(void *);
extern int func_002761F8(void *, void *, int, void *, int);



typedef struct { u8 pad_0[0x20]; u8 flags; } FlareMoby;
typedef struct {
    FlareMoby *moby; s32 state; f32 intensity; s32 pad_c;
    s16 alpha[16]; s16 tex[16]; s32 color[16]; f32 dist[16]; f32 scale[16];
} LensFlare;
typedef struct {
    int width, height, half_width, half_height;
    int left, top, right, bottom;
} ScreenExtent;
extern LensFlare D_L08_001B9E00;
extern u8 D_L08_001B9B00[];
extern int D_L08_001B0DC0;
extern ScreenExtent D_001A7340 __attribute__((sda));
extern f32 func_00282E48(void *, void *);
extern f32 func_00283CE0(int);
extern void func_00279BD8(f32 *, void *);
extern long long func_0027C878(int);
extern f32 func_00282C48(f32);
extern int func_00283CF0(f32);
extern void func_002FC560(int, long long);
extern void func_0027E018(int, int, int, int, int, int, int, int, long long, long long);


extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7878(float, float);
extern float func_00283180(float);
extern float func_00283198(float);


extern int func_00283CF0(float);
extern char *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);
extern int func_001163B0(void);
extern void func_002A8D70(void *, int, int, int, int, int, float, float, float);
extern void func_00283658(void *, void *);
extern void func_0029FCC0(void *, int, void *);
extern void func_L03_00339128(void *, void *, int, int, int, int, int, float);
extern void func_L01_003120A8(void *, void *, void *, int, int, int, int, float, float);
extern float func_00283B98(float, float);
extern int D_0018C0BC;

/* the level's object-handle table entry: 0x100 bytes, indexed by the handle */
typedef struct {
    u8 pad00[0x20];
    u8 f20;
    u8 f21;
    u8 pad22[0x24 - 0x22];
    void *f24;
    u8 pad28[0x2C - 0x28];
    f32 f2C;
    u8 pad30[0x68 - 0x30];
    void *f68;
    u8 pad6C[0x95 - 0x6C];
    u8 f95;
    u16 f96;
    u8 pad98[0xBC - 0x98];
    u8 fBC;
    u8 padBD[0x100 - 0xBD];
} Ent;

/* what an entry points at; only the queue flag and its sound handle are named here */
typedef struct {
    u8  pad00[0x20];
    f32 f20;
    void *f24;
    u8  pad28[0x2C - 0x28];
    f32 f2C;
    u8  pad30[0x50 - 0x30];
    u8  f50[0x88 - 0x50];
    u16 f88;
    u8  pad8A[0xE4 - 0x8A];
    f32 fE4;
    u8  padE8[0x144 - 0xE8];
    s32 f144;
    u8  pad148[0x150 - 0x148];
    f32 f150[4];
    f32 f160;
    f32 f164;
    f32 f168;
    u8  pad16C[0x189 - 0x16C];
    u8  f189;
    u8  pad18A[0x18C - 0x18A];
    u8  f18C;
    u8  pad18D[0x1B0 - 0x18D];
    f32 f1B0;
    f32 f1B4;
    u8  f1B8[0x1BA - 0x1B8];
    s16 f1BA;
    s16 f1BC;
    u16 f1BE;
    u8  pad1C0[0x1CC - 0x1C0];
    s32 f1CC;
    f32 f1D0;
    f32 f1D4;
    s32 f1D8;
    s32 f1DC;
    u8  f1E0[0x254 - 0x1E0];
    s32 f254;
    u8  pad258[0x40E - 0x258];
    u16 f40E;
    u8  pad410[0x440 - 0x410];
    u8  f440[0x448 - 0x440];
    s32 f448;
    u8  f44C[0x484 - 0x44C];
    s32 f484;
    s32 f488;
    u8  f48C[8];
} Moby;

/* the 16-byte block at Ent+0x10 the driver works on */
typedef struct {
    f32 f0;
    f32 f4;
    f32 f8;
    f32 fC;
} Quad;

typedef int V4 __attribute__((mode(TI)));

/* a sub-object hung off Ent::f24 */
typedef struct {
    u8  pad00[0x24];
    f32 f24;
} Sub24;

extern s32 func_2F9A60();
extern void func_2F9A90();
extern void func_328A38(s32, s32);
extern s32 func_327898(s32, s32);
extern s32 func_2EA300(void *, void *, s32, s32, s32);
extern void func_3347E0(Ent *, void *, s32, s32, f32);
extern s32 func_3357E8(Ent *, void *, s32);
extern void func_329EC0(Ent *, f32);
extern f32 func_3278F0(f32, f32);
extern f32 func_2FA3C8(f32);
extern f32 func_2FA3E0(f32);
extern void func_2F9DF0(void *, void *, void *);
extern void func_2F9E20(void *, void *, void *);
extern void func_2FA0B8(void *, void *, f32);
extern void func_L08_00422B98(Ent *);
extern f32 D_L08_001BFF68;
extern f32 D_00189EA8;
extern char D_00189EA0[];

extern f32 func_L08_00422850(Quad *, f32, f32, f32, f32);
extern void func_L08_00422900(Ent *);
extern void func_L08_00422AD8(Ent *);

/* func_L08_003D8348 is defined in L08_003D8348-init.c. */

/* the entry's sound handle and both of the moby's own handles are released */
void func_L08_003D8A28(Ent *a0)
{
    Moby *s0 = a0->f68;
    s32 v0, v;

    if (a0->f21 != 0xFF) func_328A38(a0->f21, 1);
    if (s0->f484 != -1) func_328A38(s0->f484, 1);
    v = s0->f488;
    v0 = 1;
    if (v == -1) {
        v0 = 1;
    } else {
        func_328A38(s0->f484, 1);
        v0 = 1;
    }
    a0->fBC = v0;
}

/* func_L08_003D8AB0 uses -fno-gcse in L08_003D8AB0.c. */

/* func_L08_003D8CA8 is matched in its own unit, src/levels/08_tabora/L08_003D8CA8.c (-g). */

extern void func_002B60B0(u8 *, float, float, float, float);
extern int func_00282948(void *);
extern float func_002A7878(float, float);
extern float func_00282E80(void *, void *);
extern int func_002B4FF0(u8 *, void *, float);
extern float func_00282DF0(void *);
extern float func_00282C48(float);

int func_L08_003D9038(u8 *object, float accel, float unused1, float damping,
                     float speed, float unused4, float turn, float friction) {
    u8 *state = *(u8 **)(object + 0x68);
    int result;
    float amount;

    func_002B60B0(object, speed * 0.00027777778450399637f,
                  turn * 0.01666666753590107f,
                  accel * 4.848137450608192e-06f,
                  damping * 0.0002908882452175021f);
    *(float *)(state + 0x154) = friction;
    if (func_00282948(state + 0x474) != 0) {
        *(float *)(state + 0x46C) = -*(float *)(state + 0x46C);
        *(float *)(state + 0x470) = *(float *)(state + 0x46C) * 0.01745329424738884f;
        *(int *)(state + 0x474) = func_002A7878(30.0f, 90.0f);
    }
    if (*(int *)(state + 0x48C) != 0 ||
        (object[0x20] == 8 && object[0x95] != 0) ||
        func_00282E80(object + 0x10, state + 0x3F0) < 5.0f)
        *(float *)(state + 0x470) = 0;
    result = func_002B4FF0(object, state + 0x3F0, *(float *)(state + 0x470));
    amount = func_00282DF0(state + 0x1C0);
    amount += func_00282C48(*(float *)(state + 0x1D4));
    if (result & 15) {
        func_00282948(state + 0x448);
        amount = func_00282C48(*(float *)(state + 0x1D4)) + 0.010000000707805157f;
    }
    *(float *)(object + 0x48) = amount * 29.999998092651367f;
    if (*(float *)(object + 0x48) > 1.5f)
        *(float *)(object + 0x48) = 1.5f;
    else if (*(float *)(object + 0x48) < 0.0f)
        *(float *)(object + 0x48) = 0;
    return result;
}

/* the countdown runs while the entry is flagged, then the timer field saturates */
void func_L08_003D9208(Ent *a0)
{
    Moby *s0 = a0->f68;
    u16 v1;

    if (a0->fBC != 0) {
        a0->fBC = 0;
        if (s0->f448 < 200) {
            s0->f448 = func_327898(300, 360);
            s0->f40E = 12;
        }
    }
    v1 = a0->f96;
    if (s0->f254 == 2) {
        if (func_2F9A60(&s0->f448)) s0->f40E = 3;
    }
    v1 = a0->f96;
    if (v1 <= 0xFFFDu) a0->f96 = v1 + 1;
    if (a0->f20 == 8) {
        if (a0->f95 == 0) func_2F9A60(&s0->f48C);
    }
    func_2F9A60(&s0->f440);
    func_2F9A60(&s0->f44C);
}

typedef struct {
    int mode;
    char pad4[8];
    int active;
    char pad10[0x18];
    float lower;
    char pad2C[12];
    float upper;
} HeightGate;
typedef struct {
    u8 pad0[0x80];
    V4 position;
    u8 pad90[0x40];
    V4 other;
    u8 padE0[0x21B0];
    int handle;
} HeroTarget;
extern HeroTarget D_00189E20;
extern HeightGate D_L08_001CA080;
extern char D_L08_001BFF80[];
extern int func_00278E78(void);
extern void func_002A93B0(void *);
extern void func_L08_003D82F0(void *);
extern void func_00283410(void *, void *);
extern void func_00283698(void *, void *);
extern float func_002A89A8(void *, int, float);
extern float func_00283248(float, float);
/* EE ABI interleaving of (f32 *, f32 *, s32, f32, f32, f32, f32): each bank keeps its order. */
extern float func_002AAA00(void *, void *, float, float, float, float, int);
extern float func_00283BE0(float, float);
extern void func_002AEC48(void *, void *, int, float, float);
extern void func_00283098(void *, void *, void *);

void func_L08_003D92D8(u8 *object)
{
    float point[4], angles[4], matrix[16], inverse[16], other[16];
    char *state = *(char **)(object + 0x68);
    float yaw, pitch, target;
    float pointX, pointY;
    float *pitchAngle, *rollAngle;
    int hit;

    if (D_L08_001CA080.active) {
        if (*(float *)(object + 0x18) < D_L08_001CA080.lower && D_L08_001CA080.mode == 1) return;
        if (D_L08_001CA080.lower < *(float *)(object + 0x18) && D_L08_001CA080.mode == 0) return;
        if (D_L08_001CA080.active == 2) {
            if (D_L08_001CA080.upper < *(float *)(object + 0x18) && D_L08_001CA080.mode == 1) return;
            if (*(float *)(object + 0x18) < D_L08_001CA080.upper && D_L08_001CA080.mode == 2) return;
        }
    }
    if (object[0x31] && func_00282E48(object + 0x10, D_L08_001B9B00) < 24.0f) {
        func_002A93B0(object);
        object[0x6F] = 22;
    }
    func_L08_003D82F0(object);
    if (*(float *)(object + 0x18) < *(float *)(state + 0x434) + 0.12f) {
        if (func_00278E78() == 1 || func_00278E78() == 11) {
            *(int *)(state + 0x20) = 0;
            object[0x20] = 11;
            return;
        }
    }
    *(float *)(object + 0x2C) +=
        (*(float *)(*(char **)(object + 0x24) + 0x24) * 1.7f - *(float *)(object + 0x2C)) * 0.05f;
    hit = func_3357E8((Ent *)object, state + 0x50, 0);
    if (hit) {
        if (hit == 5) *(int *)(state + 0xE0) = 0;
        *(int *)(state + 0x48C) = 240;
        func_L08_003D8A28((Ent *)object);
    }
    if (object[0x20] < 9 && object[0x20] != 4) {
        pitchAngle = (float *)(object + 0xF4);
        rollAngle = (float *)(object + 0xF0);
        *(V4 *)angles = 0;
        angles[2] = *(float *)(object + 0xF8);
        *(V4 *)point = *(V4 *)angles;
        func_00283410(matrix, point);
        func_00283698(inverse, matrix);
        func_00283698(other, object + 0xC0);
        func_002A89A8(object + 0x10, 0, 0.5f);
        func_2FA0B8(angles, D_L08_001BFF80, 1.0f);
        func_00283098(angles, angles, inverse);
        target = func_00283248(angles[2], angles[0]);
        func_002AAA00(pitchAngle, state + 0x460, target, 0.0017453294713050127f,
                      0.0017453294713050127f, 0.10471977293491364f, 0);
        target = -func_00283248(angles[2], angles[1]);
        func_002AAA00(rollAngle, state + 0x464, target, 0.0017453294713050127f,
                      0.0017453294713050127f, 0.10471977293491364f, 0);
    }
    if (object[0x20] == 8 && !object[0x95]) {
        func_0029FCC0(object, 1, point);
        if (*(int *)(state + 0x250) == D_00189E20.handle) {
            qcopy(state + 0x210, &D_00189E20.position);
            qcopy(state + 0x230, &D_00189E20.other);
        }
        pointY = point[1];
        pointX = point[0];
        yaw = func_00283248(*(float *)(state + 0x230) - pointX, *(float *)(state + 0x234) - pointY);
        pitch = func_00283248(func_00282E80(point, state + 0x230), *(float *)(state + 0x238) - point[2]);
        yaw = func_00283BE0(yaw, *(float *)(object + 0xF8)) * 0.5f;
        pitch = func_00283BE0(-pitch, *(float *)(object + 0xF4)) * 0.3333333432674408f;
        {
            int i;
            for (i = 0; i < 3; i++) {
                *(float *)(state + 0x2C8 + i * 0x80) = yaw;
                if (yaw > 0.523598849773407f) *(float *)(state + 0x2C8 + i * 0x80) = 0.523598849773407f;
                else if (yaw < -0.523598849773407f) *(float *)(state + 0x2C8 + i * 0x80) = -0.523598849773407f;
                *(float *)(state + 0x2C4 + i * 0x80) = pitch;
            }
        }
    } else {
        int i;
        for (i = 0; i < 3; i++) {
            *(float *)(state + 0x2C0 + i * 0x80) = 0;
            *(float *)(state + 0x2C4 + i * 0x80) = 0;
        }
    }
    {
        int i;
        for (i = 0; i < 3; i++) func_002AEC48(object, state + 0x260 + i * 0x80, 3, 0.02f, 0.4f);
    }
}

void func_L08_003D9798(char *object)
{
    float origin[4], end[4], start[4], step[4], matrix[12], point[4];
    float velocity[4], accel[4], position[4];
    char *state = *(char **)(object + 0x68), *particle;
    float heading, angle;
    int a, b, c;
    func_002A8D70(object,1,1,0,1,0,0.5f,(float)*(u8 *)(state+0x34),1.0f);
    func_00283658(matrix,object+0xC0);
    func_0029FCC0(object,1,point);
    qcopy_nc(origin,point);
    matrix[2]=0;
    qcopy_nc(start,origin);
    func_00282F20(end,matrix,3.0f);
    if (*(int *)(state+0x250)) {
        if ((unsigned)(D_0018C0BC-17)<2) end[2]=*(float *)(state+0x218)-start[2];
        else end[2]=*(float *)(state+0x248)-start[2];
        if (end[2]>1.2f) end[2]=1.2f;
        else if(end[2]<-1.2f) end[2]=-1.2f;
    }
    func_00282CC0(end,end,start);
    func_L03_00339128(end,object,1,0x808080,127,30,255,0.5f);
    func_L01_003120A8(object,start,end,1,0,1,0,(float)*(u8 *)(state+0x34),1.0f);
    func_00282F20(step,matrix+4,0.1f);
    func_00282CC0(start,start,step);
    func_00282CC0(end,end,step);
    end[2]+=func_002A7878(-0.2f,0.2f);
    func_L01_003120A8(object,start,end,1,0,1,0,(float)*(u8 *)(state+0x34),1.0f);
    func_00282F20(step,matrix+4,-0.2f);
    func_00282CC0(start,start,step);
    func_00282CC0(end,end,step);
    end[2]+=func_002A7878(-0.2f,0.2f);
    func_L01_003120A8(object,start,end,1,0,1,0,(float)*(u8 *)(state+0x34),1.0f);
    heading=*(float *)(object+0xF8);
    velocity[3]=0.6f; accel[3]=1.5f;
    { int i; for(i=1;i>=0;i--) {
        qcopy_nc(position,origin);
        position[0]+=func_002A7878(-0.065f,0.065f);
        position[1]+=func_002A7878(-0.065f,0.065f);
        position[2]+=func_002A7878(-0.065f,0.065f);
        velocity[0]=func_00283180(heading)*0.28333336114883423f;
        velocity[1]=func_00283198(heading)*0.28333336114883423f;
        velocity[2]=0;
        velocity[2]=func_002A7878(0,0);
        angle=func_002A7878(-90,90)*0.01745329424738884f;
        accel[0]=func_00283180(func_00283B98(heading,angle))*0.008333333767950535f;
        accel[1]=func_00283198(func_00283B98(heading,angle))*0.008333333767950535f;
        accel[2]=0;
        accel[2]=func_002A7878(0.015000000596046448f,0.01833333447575569f);
        a=func_00283CF0(func_002A7878(2,4));
        b=func_00283CF0(func_002A7878(12,14.40000057220459f));
        c=func_00283CF0(func_002A7878(200,240.00001525878906f));
        particle=func_002BAA28(position,velocity,accel,0x40101080,0x10101080,a,b,c,-1);
        if(particle && (func_001163B0()&1)) particle[3]=0x48;
    }
    }
    velocity[3]=0.05f; accel[3]=0.07f;
    { int i; for(i=1;i>=0;i--) {
        qcopy_nc(position,origin);
        position[0]+=func_002A7878(-0.2f,0.2f);
        position[1]+=func_002A7878(-0.2f,0.2f);
        position[2]+=func_002A7878(-0.2f,0.2f);
        angle=func_002A7878(-10,10)*0.01745329424738884f;
        velocity[0]=func_00283180(func_00283B98(heading,angle))*0.20000001788139343f;
        velocity[1]=func_00283198(func_00283B98(heading,angle))*0.20000001788139343f;
        velocity[2]=0;
        velocity[2]=func_002A7878(0,0);
        angle=func_002A7878(-90,90)*0.01745329424738884f;
        accel[0]=func_00283180(func_00283B98(heading,angle))*0.008333333767950535f;
        accel[1]=func_00283198(func_00283B98(heading,angle))*0.008333333767950535f;
        accel[2]=0;
        accel[2]=func_002A7878(0.011666666716337204f,0.02500000223517418f);
        a=func_00283CF0(func_002A7878(2,4));
        b=func_00283CF0(func_002A7878(20,24));
        c=func_00283CF0(func_002A7878(200,240.00001525878906f));
        particle=func_002BAA28(position,velocity,accel,0x801010FF,0x801010FF,a,b,c,-1);
        if(particle && (func_001163B0()&1)) particle[3]=0x48;
    }
    }
}


/* func_L08_003D9F68 is defined in L08_003D9F68-g8.c. */

/* func_L08_003F6D30 is defined in L08_003F6D30-g8.c. */

/* func_L08_003F6E18 is defined in L08_003F6E18-g8.c. */




extern u32 D_L08_001B9E04;

/* 128-bit copies reach lq/sq only through TImode. */
typedef int TQ_003F79E0 __attribute__((mode(TI)));

/* func_L08_003F79E0 is defined in L08_003F79E0-qcopy-barrier.c. */

/* Projects the flare object to the screen and draws its 12 sprites along the line
   through the screen centre, faded by distance and by how far off-centre it is
   (RAC1 draw_lens_flare). The base size is read through a pointer: retail
   rematerializes its address inside the loop. */
void func_L08_003F7A48(u8 *object) {
    u8 *vars = *(u8 **)(object + 0x68);
    f32 scr[4], ctr[4], d[4], off[4], at[4];
    f32 dist, fade, fx, fy, half;
    int i, size, rgba, x, y;
    long long tex;
    int *base_size;

    if (D_L08_001B9E00.state != 1 || (D_L08_001B9E00.moby->flags & 0x80)) {
        D_L08_001B9E00.state = 0;
        return;
    }
    if (D_L08_001B9E00.intensity <= 0.0f)
        return;
    dist = func_00282E48(D_L08_001B9B00, vars + 0x10);
    ctr[0] = func_00283CE0(D_001A7340.half_width);
    ctr[1] = func_00283CE0(D_001A7340.half_height);
    base_size = &D_L08_001B0DC0;
    func_00279BD8(scr, vars + 0x10);
    scr[0] = (scr[0] - func_00283CE0(D_001A7340.left)) * 0.0625f;
    scr[1] = (scr[1] - func_00283CE0(D_001A7340.top)) * 0.0625f;
    d[0] = ctr[0] - scr[0];
    d[1] = ctr[1] - scr[1];
    for (i = 0; i < 12; i++) {
        tex = func_0027C878(D_L08_001B9E00.tex[i] + 0x45);
        off[0] = d[0] * D_L08_001B9E00.dist[i];
        off[1] = d[1] * D_L08_001B9E00.dist[i];
        at[0] = ctr[0] + off[0];
        at[1] = ctr[1] + off[1];
        fade = dist - 5.0f;
        if (fade > 1.0f)
            fade = 1.0f;
        else if (fade < 0.0f)
            fade = 0.0f;
        fx = func_00282C48(d[0]) / ctr[0] * -5.0f + 5.5f;
        if (fx > 1.0f)
            fx = 1.0f;
        else if (fx < 0.0f)
            fx = 0.0f;
        fy = func_00282C48(d[1]) / ctr[1] * -5.0f + 5.5f;
        if (fy > 1.0f)
            fy = 1.0f;
        else if (fy < 0.0f)
            fy = 0.0f;
        fade *= fx * fy * D_L08_001B9E00.intensity;
        rgba = (func_00283CF0(fade * D_L08_001B9E00.alpha[i]) << 24) | (D_L08_001B9E00.color[i] & 0xFFFFFF);
        size = func_00283CF0(*base_size * D_L08_001B9E00.scale[i]);
        func_002FC560(0x42, 0x8000000048LL);
        half = size >> 1;
        x = func_00283CF0(at[0] - half);
        y = func_00283CF0(at[1] - half);
        func_0027E018(x, y, size, size, 0, 0, 0x40, 0x40, rgba, tex);
    }
    D_L08_001B9E00.intensity = 0.0f;
}


extern void func_002A7750(void *, s32, s32);
extern u8 D_001A7B00[] __attribute__((sda));
extern u8 D_L08_001BFD00[];
extern s32 D_L08_001A8F00[] __attribute__((sda));
extern s32 D_L08_001B2700[] __attribute__((sda));
extern u8 *D_L08_001B2ACC[] __attribute__((sda));
extern s32 func_002ACBC8(void *, s32);
extern s32 func_00288AA0(void *, s32);
extern s32 func_00288BE8(void *);
extern void func_L01_003CEB00(u8 *);
extern s32 func_002F5D10(void);
extern void func_L00_002B9D60(u8 *, u8 *, s32, s32);
extern void func_00288308(s32);
extern void func_002B0A18(s32, s32);
extern void func_0029B3E0(s32, s32);

void func_L08_0040E9B8(u8 *self) {
    u8 *st = *(u8 **)(self + 0x68);
    u8 *ent;

    switch (self[0x20]) {
    case 0:
        if (D_001A7B00[13] != 0) {
            func_0029F338(self);
            break;
        }
        *(float *)(self + 0x18) = *(float *)(self + 0x18) + 0.75f;
        *(float *)(self + 0x2C) = *(float *)(*(u8 **)(self + 0x24) + 0x24) * 1.5f;
        func_002A7750(self, 1, -1);
        break;
    case 1:
        *(float *)(self + 0xF8) = func_00283B98(*(float *)(self + 0xF8), 0.07853982597589493f);
        if (func_002ACBC8(D_00189EA0, *(s32 *)(st + 4)) != 0) {
            if (func_00288AA0(D_L08_001BFD00, 0x5B) != 0) {
                func_00288BE8(D_L08_001BFD00);
                self[0x20] = 2;
            }
        }
        if (self[0x31] != 0)
            func_L01_003CEB00(self);
        break;
    case 2:
        D_L08_001B2700[10] = 1;
        if (D_L08_001A8F00[0] == 2) {
            self[0x31] = 0;
            *(u16 *)(self + 0x34) |= 1;
        }
        if (func_002F5D10() != 0)
            break;
        D_L08_001B2700[10] = 0;
        self[0x31] = 1;
        ent = D_L08_001B2ACC[0];
        *(u16 *)(self + 0x34) &= 0xFFFE;
        ent += *(s32 *)(st + 8) * 0x80;
        func_L00_002B9D60(ent + 0x30, ent + 0x70, 0, 1);
        func_00288308(0x15);
        func_002B0A18(0x122B, -1);
        func_0029B3E0(0, -1);
        func_0029F338(self);
        break;
    }
}

/* func_L08_0040F9D0 is matched in its own unit, src/levels/shared/L08_0040F9D0-qcopy.c (-frac2-qcopy -frac2-qcopy-barrier). */

void func_L08_0040FAE8(char *object)
{
    float position[4];
    char *state = *(char **)(object + 0x68);
    char *mount;
    int hit;

    func_00282CC0(position, object + 0x10, state);
    hit = func_002761F8(object + 0x10, position, 0, *(void **)(state + 0x18), 0);
    if (!hit) {
        position[2] += 0.3f;
        hit = func_00277258(position, 0, *(void **)(state + 0x18), 0.3f);
        position[2] -= 0.3f;
    } else {
        qcopy(D_L08_001BFF40.adjusted, D_L08_001BFF40.hit);
        D_L08_001BFF40.adjusted[2] += 0.3f;
    }
    if (hit) {
        qcopy(object + 0x10, D_L08_001BFF40.adjusted);
        *(float *)(object + 0x18) -= 0.3f;
        func_00283028(state, state, D_L08_001BFF40.normal);
        func_00282D30(state, state, 0.75f);
        if (func_00282DF0(state) < 0.01f) {
            func_0029F338(object);
            return;
        }
    } else {
        qcopy_nc(object + 0x10, position);
    }
    *(float *)(state + 8) -= *(float *)(state + 0x10);
    *(float *)(object + 0xF4) = func_00283B98(*(float *)(object + 0xF4), *(float *)(state + 0x14));
    mount = *(char **)(state + 0x1C);
    if (!mount || *(short *)(mount + 0xAA) != 0x326 ||
        (unsigned char)mount[0x20] == 0xFE || (unsigned char)mount[0x20] == 0xFD ||
        *(float *)(object + 0x10) < 2 || *(float *)(object + 0x10) > 1021 ||
        *(float *)(object + 0x14) < 2 || *(float *)(object + 0x14) > 1021 ||
        *(float *)(object + 0x18) < 2 || *(float *)(object + 0x18) > 1021) {
        func_0029F338(object);
        return;
    }
    qcopy_nc(mount + 0x10, object + 0x10);
    qcopy_nc(mount + 0xF0, object + 0xF0);
}


extern void func_00283098(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_00283CF0(float);
extern char *func_002BAA28(void *, void *, void *, int, int, int, int, int, int);
extern int func_001163B0(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern void func_00282CC0(void *, void *, void *);

void func_L08_00422190(char *m, void *position, int count,
                      float speed, float rise, float maxRadius, float minRadius,
                      float size, float endSize)
{
    float offset[4], velocity[4], accel[4];
    int a, b, c;
    char *particle;

    {
        int i;
        for (i = 0; i < count; i++) {
            float x, y;
            x = func_00283180(func_002A7878(-3.1415927410125732f, 3.1415927410125732f));
            offset[0] = x * func_002A7878(minRadius, maxRadius);
            y = func_00283198(func_002A7878(-3.1415927410125732f, 3.1415927410125732f));
            y *= func_002A7878(minRadius, maxRadius);
            offset[1] = y;
            offset[2] = 0;
            func_00283098(offset, offset, m + 0xC0);
            {
                float range = speed * ((maxRadius - func_00282DF0(offset)) * 0.01666666753590107f) / maxRadius;
                func_00282F20(velocity, offset, func_002A7878(range * 0.25f, range));
            }
            velocity[2] += func_002A7878(rise * 0.25f, rise) * 0.01666666753590107f;
            qzero_nc(accel);
            func_00282CC0(offset, offset, position);
            velocity[3] = size;
            accel[3] = endSize;
            a = func_00283CF0(func_002A7878(15.0f, 25.0f));
            b = func_00283CF0(func_002A7878(20.0f, 40.0f));
            c = func_00283CF0(func_002A7878(30.0f, 60.0f));
            particle = func_002BAA28(offset, velocity, accel, 0x50204050, 0x7F7F7F, a, b, c, -1);
            if (particle && (func_001163B0() & 1))
                particle[3] = 0x48;
        }
    }
}


extern f32 func_002A7940(void);
extern s32 func_002A7820(s32, s32);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern void func_00282CC0(void *, void *, void *);
extern void func_L01_0032EF38(void *, int, int, float, float, int);

/* five rounds: each picks a direction, two spreads and a life time */
void func_L08_00422428(Ent *a0)
{
    Moby *s3 = a0->f68;
    f32 position[4];
    f32 angle, radius, first, second;
    int life, i;

    for (i = 4; i >= 0; i--) {
        angle = func_002A7940();
        radius = func_002A7878(0.0f, 0.8f);
        first = func_002A7878(0.0f, 1.5f);
        second = func_002A7878(1.5f, 5.7f);
        life = func_002A7820(100, 180);
        position[0] = func_00283180(angle) * radius;
        position[1] = func_00283198(angle) * radius;
        position[2] = 0.0f;
        func_00282CC0(position, position, (char *)a0 + 0x10);
        position[2] = s3->f1B0 + 0.025f;
        func_L01_0032EF38(position, 0x38002028, 0x2020, first, second, life);
    }
}




/* the entry's own two handles and its sound handle are released */
void func_L08_00422AD8(Ent *a0)
{
    Moby *s0 = a0->f68;
    s32 v0, v;

    if (a0->f21 != 0xFF) func_328A38(a0->f21, 1);
    if (s0->f1D8 != -1) func_328A38(s0->f1D8, 1);
    v = s0->f1DC;
    v0 = 1;
    if (v == -1) {
        v0 = 1;
    } else {
        func_328A38(s0->f1D8, 1);
        v0 = 1;
    }
    a0->fBC = v0;
}

/* the queued sound of the entry is released and the flag cleared */
void func_L08_00422B60(Ent *a0)
{
    Moby *s0 = a0->f68;

    if (s0->f18C != 0) {
        func_2F9A60(s0->f1CC);
        s0->f18C = 0;
    }
}

extern char D_L08_001BFF60[];
extern void func_00282CF0(void *, void *, void *);
extern char *D_L08_001FE7BC;
extern char *D_L08_001B29DC[] __attribute__((sda));
extern void func_L01_00337A60(void *, void *, void *, int);
extern int func_L01_003165E8(void *, int, int, int, int);
extern float func_002A89A8(void *, int, float);

void func_L08_00422B98(Ent *object) {
    char *state = object->f68;

    if (!func_L01_003165E8(state + 0x160, *(int *)(state + 0x1A8), -1, -1, -1)) {
        if ((func_001163B0() & 1) || *(int *)(state + 0x144) == 2 || *(short *)(state + 0x1BC)) {
            if (*(int *)(state + 0x184) == -1 || (func_001163B0() & 1)) {
                qcopy(state + 0x160, state + 0x150);
            } else {
                *(float *)(state + 0x160) = func_00283180(func_002A7878(-3.1415927f, 3.1415927f)) * 3.0f;
                {
                    float y = func_00283198(func_002A7878(-3.1415927f, 3.1415927f)) * 3.0f;
                    int handle = *(int *)(state + 0x184);
                    char *entry = D_L08_001B29DC[0];
                    *(float *)(state + 0x168) = 0;
                    *(float *)(state + 0x164) = y;
                    func_00282CC0(state + 0x160, state + 0x160, entry + (handle << 8) + 0x10);
                }
            }
            *(float *)(state + 0x168) += 1.7f;
        } else {
            *(float *)(state + 0x160) = func_00283180(func_002A7878(-3.1415927f, 3.1415927f)) * 1.2f;
            {
                float y = func_00283198(func_002A7878(-3.1415927f, 3.1415927f)) * 1.2f;
                *(float *)(state + 0x168) = 0;
                *(float *)(state + 0x164) = y;
                func_00282CC0(state + 0x160, state + 0x160, D_00189EA0);
            }
            *(float *)(state + 0x168) += 1.7f;
        }
        if (*(short *)(state + 0x1BC) && func_00282E80(state + 0x160, D_00189EA0) < 3.0f) {
            float offset = func_002A7878(3.0f, 5.0f);
            float value = *(float *)(state + 0x160);
            *(float *)(state + 0x160) = (func_001163B0() & 1) ? value - offset : value + offset;
            offset = func_002A7878(3.0f, 5.0f);
            value = *(float *)(state + 0x164);
            *(float *)(state + 0x164) = (func_001163B0() & 1) ? value - offset : value + offset;
        }
    } else if (*(int *)(state + 0x1A8) == -1) {
        func_L01_00337A60(state + 0x160, state + 0x160, D_L08_001FE7BC + 0x10, *(int *)D_L08_001FE7BC);
    }
    if (func_002761F8((char *)object + 0x10, state + 0x160, 2, object, 0)) {
        func_00282CF0(state + 0x160, D_L08_001BFF60, state + 0x160);
        func_00282F20(state + 0x160, state + 0x160, 2.0f);
        func_00282CC0(state + 0x160, state + 0x160, D_L08_001BFF60);
    }
    *(float *)(state + 0x168) = func_002A89A8(state + 0x160, 0, 4.0f) + 1.7f;
}

/* the swing angle is folded into the moby's frame and the subobject is ticked */
void func_L08_00422EE0(Ent *a0)
{
    Moby *s0 = a0->f68;
    Quad local;
    f32 f21 = -3.1415927f;
    f32 f20 = 3.1415927f;
    f32 t;

    t = func_3278F0(f21, f20);
    s0->f160 = func_2FA3C8(t) * (f32)s0->f189;
    t = func_3278F0(f21, f20);
    s0->f164 = func_2FA3E0(t) * (f32)s0->f189;
    s0->f168 = 0.0f;
    func_2F9DF0((char *)s0 + 0x160, (char *)s0 + 0x160, (char *)s0 + 0x150);
    s0->f168 = s0->f168 + 1.7f;
    if (s0->f1BC != 0) {
        func_2F9E20(&local, (char *)s0 + 0x160, (void *)D_00189EA0);
        *(s32 *)((char *)&local + 8) = 0;
        func_2FA0B8(&local, &local, 8.0f);
        func_2F9DF0((char *)s0 + 0x160, (char *)s0 + 0x160, &local);
    }
    func_L08_00422B98(a0);
}

/* func_L08_00423010 is in its own unit. */

/* func_L08_004233E0 is defined in L08_004233E0-init.c. */

/* func_L08_004237F0 is matched in its own unit, src/levels/08_tabora/L08_004237F0.c (default flags). */

/* the driver is primed, the entry follows its mount and then its own update runs */
void func_L08_004238A0(Ent *a0)
{
    Moby *s0 = a0->f68;
    Sub24 *q;
    f32 f0;
    s32 r;

    func_3347E0(a0, s0->f1E0, 2, 1, 2.5f);
    func_L08_00422900(a0);
    q = a0->f24;
    f0 = q->f24 * 0.5f;
    a0->f2C = f0;
    r = func_3357E8(a0, s0->f50, 0);
    if (r != 0) {
        if (s0->f20 <= 0.0f) {
            s0->f88 |= 2;
            s0->fE4 = 0.8377582f;
        } else {
            s0->f1BE = 330;
        }
        func_L08_00422B60(a0);
        func_L08_00422AD8(a0);
    }
}
