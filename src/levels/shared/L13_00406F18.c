#include "common.h"

typedef struct {
    char pad0[0xC4];
    char *path;
    short cur;
    short goal;
} Walk_409840;

/* The state getter has identical copies whose placement differs between levels. */
extern Walk_409840 *ref_L13_00409840_00(char *);
extern int func_002B6228(void *, void *, int, int);
extern float func_00282E80(void *, void *);

/* Retail reloads the mutable movement flags at +0x88 for each update. */
typedef struct L13C3Flags { char pad[0x88]; volatile int flags; } L13C3Flags;
#define I(p,o) (*(int *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
#define H(p,o) (*(unsigned short *)((p)+(o)))
#define S(p,o) (*(short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
#define P(p,o) (*(char **)((p)+(o)))
extern int func_002A77E0(int);
extern void func_002B37E8(char *,char *);
extern void func_002B60B0(char *,float,float,float,float);
extern void func_002A7750(char *,int,int);
extern void func_002A7470(char *,int,int,int);
extern int func_00283CF0(float);
extern void func_002A93B0(char *);
extern void func_0029FC20(char *,int,void *);
extern void func_00283678(char *,void *);
extern void func_0029F338(char *);
extern int func_002B0ED8(char *,char *,int);
extern int func_002B3BA8(char *,int,float,float,int,int);
extern void func_002A6C58(char *,int,int);
extern void func_L13_0040CA70(u8 *);
extern char D_L13_001B98C0[];

typedef int Vector128 __attribute__((mode(TI)));
extern char *func_0029EFD0(int);
extern int func_00283DB8(void *, float);
extern float func_00282E48(void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_002831B0(float);
extern void func_L13_00412C18(char *, char *);
typedef struct Cam_00435CE8 Cam_00435CE8;
typedef struct CamMgr_00435CE8 {
    u8 pad000[0x140];
    f32 f140[4];
    u8 pad150[0x40];
    Cam_00435CE8 *cam;
} CamMgr_00435CE8;
extern CamMgr_00435CE8 D_L13_001B9780;
typedef struct SpawnState {
    short life;
    short timer;
    short delay;
    short pad06;
    float outer, inner, fade, size;
    int flags, control, kind, red, green, blue, enabled, extra;
} SpawnState;
typedef struct SpawnObject {
    char pad00[0x10];
    float position[4];
    char status;
    char pad21[0xf];
    unsigned char alpha;
    char pad31;
    short color;
    char pad34[0x34];
    SpawnState *state;
    char pad6c[0x54];
    float forward[4], right[4], up[4];
} SpawnObject;


extern void func_00282D30(void *dst, void *src, float value);

extern void func_00282CF0(void *, void *, void *);

extern void func_00282F20(char *, char *, float);

extern void func_00282DD8(char *, char *, char *);

extern float func_00282DF0(float *);

extern float func_00282C10(float);

extern void func_00283958(char *, char *);

extern void func_00283738(char *, char *, char *);

extern void func_00282AB0(void *, void *, int);

extern int func_00282948(void *);

extern int func_002AD0E0(void *, void *, void *, void *, void *, void *);

extern int func_002B0990(void *, void *, int, int, float);

extern void func_L13_004094D0(char *a0, char *a1, char *a2);

extern int ref_L13_0040A480_00(void *);

extern char D_00189EA0[];

extern void func_002AFFD8(void *, void *, int);

extern float func_002B0360(void *);

extern void func_00282C88(void *);

extern void func_00282CC0(char *, char *, char *);

extern int func_002761F8(void *, void *, int, void *, int);

extern int func_00277258(void *, int, void *, float);

extern void func_00283098(char *, char *, char *);

extern char D_L13_001BFD00[];

extern void func_L13_0040A540(u8 *);
int func_L13_00409008(char *obj) {
    char *s = P(obj,0x68);
    if (!B(obj,0x20)) {
        qcopy(s+0x370,obj+0x10);
        F(s,0x30)=1.25f;
        if (func_002A77E0(2)) H(obj,0x34)|=0x8000;
        I(s,0x288)=I(s,0x284)+func_002A77E0(2);
        B(s,0x150)=0x1a; I(s,0x188)=4;
        F(s,0x17c)=0.15f; B(s,0x155)=12;
        I(s,0x28c)=0; I(s,0x26c)=0;
        F(s,0x174)=F(s,0x170)=0.5f;
        if (I(s,0x36c)!=-1) I(s,0x1bc)=I(s,0x36c);
        if (!S(s,0x24)) { S(s,0x24)=1; F(s,0x20)=1.0f; }
        F(s,0x84)=0.5f; F(s,0x54)=0.2f; F(s,0x50)=0.825f;
        F(s,0x5c)=F(s,0x58)=0.75f;
        F(s,0x60)=1.5707964897155762f; F(s,0x80)=0.523598849773407f;
        if (I(s,0x2a0)) {
            ((L13C3Flags *)s)->flags|=4; F(s,0x5c)=F(s,0x58)=0.7f;
            H(obj,0x34)|=0x100; F(s,0x60)=12.56637191772461f;
            ((L13C3Flags *)s)->flags|=1;
        }
        if (I(s,0x2a8)) { ((L13C3Flags *)s)->flags|=5; F(s,0x50)=0; F(s,0x180)=97.5f; }
        func_002B60B0(obj,0.0033333334140479565f,0.10000000894069672f,0.006981317885220051f,0.8377581834793091f);
        func_002A7750(obj,1,0);
        if (B(obj,0x43)!=21) func_002A7470(obj,21,0,0);
        if (I(s,0x2b0)!=-1) {
            func_002A7750(obj,3,0); if (B(obj,0x43)!=3) func_002A7470(obj,3,0,0);
            func_002B60B0(obj,0.002222222276031971f,0.06666667014360428f,0.006981317885220051f,0.8377581834793091f);
        }
        if (I(s,0x294) && I(s,0x298)!=-1) func_002A7750(obj,27,5);
        if (I(s,0x2c4)) { func_002A7750(obj,5,0); if (B(obj,0x43)!=24) func_002A7470(obj,24,0,0); }
        if (I(s,0x2d0)) {
            I(obj,0x98)=0; H(obj,0x34)=(H(obj,0x34)|0x41)&0xefff;
            func_002A7750(obj,1,8);
        }
        B(s,0x48)=func_00283CF0(17.0f); B(s,0x4a)=func_00283CF0(12.0f); B(s,0x29)=1;
    }
    if (B(obj,0x31) && func_00282E48(obj+0x10,D_L13_001B98C0)<24.0f) { func_002A93B0(obj); B(obj,0x6f)=22; }
    if (func_002B0ED8(obj,s+0x140,0)) func_L13_0040A540((u8 *)obj);
    I(s,0x264)=func_002B3BA8(obj,I(s,0x260),0.0f,0.0f,0,0);
    I(s,0x278)=func_002B3BA8(obj,I(s,0x274),0.0f,0.0f,0,0);
    I(s,0x2b8)=func_002B3BA8(obj,I(s,0x2b4),0.0f,0.0f,0,0);
    I(s,0x250)=func_002B3BA8(obj,I(s,0x230),F(s,0x238),0.0f,0,0);
    I(s,0x254)=func_002B3BA8(obj,I(s,0x234),F(s,0x23c),0.0f,0,0);
    if (F(obj,0x18)<89.0f || (I(s,0x2a8) && F(obj,0x18)<98.0f)) {
        F(s,0x20)=0; func_002A6C58(obj,0,3); return 1;
    }
    return 0;
}
void func_L13_004094D0(char *a0, char *a1, char *a2)
{
    float out[12];
    float v[4];
    float m[4];
    float x;

    func_00282F20((char *)m, a1, 1.0f);
    func_00282DD8((char *)v, (char *)m, a0 + 0x20);
    func_00282D30(v, v, 0.05f);
    x = func_00282DF0(v);
    v[3] = -func_00282C10(1.0f - x * x);
    func_00283958((char *)v, (char *)out);
    func_00283738(a0, (char *)out, a0);
    if (a2 != 0) {
        func_00282AB0(a2, out, 0x30);
    }
}

void func_L13_004095A8(void *self, void *base, void *arg)
{
    float tmp[4];
    func_00282D30(tmp, base, -1.0f);
    func_L13_004094D0(self, tmp, arg);
}

/* func_L13_004095F8 lives in L13_004095F8.c. */

extern int func_L13_004094C0(char *, char *);

extern void func_003357C8(char *, char *, int, int);

extern int func_L13_004095F8(char *, char *);

extern float func_002F8938(char *, char *);

extern int D_001A79F0 __attribute__((section(".sdata")));

int func_L13_00409840(char *obj, char *path)
{
    Walk_409840 *w = ref_L13_00409840_00(obj);

    if (w == 0)
        return 0;
    if (path != w->path)
        func_002B6228(obj, path, -1, 0);
    if (D_001A79F0 == 0x45) {
        func_L13_004095F8(obj, path + (w->cur * 16 + 0x10));
        if (func_00282E80(obj + 0x10, path + (w->cur * 16 + 0x10)) <= 0.5f) {
            if (w->goal == w->cur)
                return 1;
            if (w->goal < w->cur)
                w->cur = w->cur - 1;
            else
                w->cur = w->cur + 1;
        }
    } else {
        func_L13_004095F8(obj, path + (w->goal * 16 + 0x10));
        if (func_00282E80(obj + 0x10, path + (w->goal * 16 + 0x10)) <= 0.5f) {
            if (w->goal == w->cur)
                return 1;
            if (w->goal < w->cur)
                w->cur = w->cur - 1;
            else
                w->cur = w->cur + 1;
        }
    }
    return 0;
}


void func_L13_00409AB8(char *a0, char *a1)
{
    if (*(int *)(a1 + 0x88) != 0) {
        if (func_002AD0E0(a0, *(int *)(a1 + 0x88), a0 + 0x10, a0 + 0xF0, a0 + 0x10,
                         a0 + 0xF0) != 0) {
            *(int *)(a1 + 0x94) |= 0x40;
        }
    }
}

void func_L13_00409B08(char *a0, char *a1)
{
    float tmp[4];
    float va[4];
    float vb[4];
    float f;
    char *base;
    char *q;

    func_002AFFD8(a0 + 0x10, (char *)tmp, 1);
    func_00282F20((char *)va, (char *)tmp, *(float *)(a1 + 8) + 0.1f);
    func_00282F20((char *)vb, (char *)tmp, -*(float *)(a1 + 0xC) - 0.1f);
    func_00282CC0((char *)va, (char *)va, a0 + 0x10);
    func_00282CC0((char *)vb, (char *)vb, a0 + 0x10);
    if (func_002761F8(va, vb, 0, a0, 0) != 0) {
        base = D_L13_001BFD00 + 0x20;
        f = func_002B0360(base);
        q = base - 0x20;
        *(float *)(a1 + 0x90) = f;
        *(int *)(a1 + 0x88) = *(int *)(q + 0x18);
        *(int *)(a1 + 0x8C) = *(int *)(q + 0x1C);
        func_00282F20(a1 + 0x50, base + 0x20, 1.0f);
    } else {
        *(float *)(a1 + 0x90) = 0.0f;
        *(int *)(a1 + 0x88) = 0;
        *(int *)(a1 + 0x8C) = 0;
        func_00282C88(a1 + 0x50);
    }
}

typedef union { Vector128 q; float f[4]; } MotionVector;
extern void func_L13_0040A3B0(char *, char *, char *, int);
extern float func_L02_00329C48(char *, Vector128 *, char *);
extern void func_L02_003294D8(char *, float *, float);
extern void func_002AFEB8(char *, char *, char *, float, char *);
extern void func_002AC9F8(float *, float);
extern float func_002AFF08(char *, char *, char *);
extern void func_L00_003253A0(u8 *, float *, float *, float);
extern float func_002AFF38(char *, char *, char *);
extern void func_002AAC80(float *, float, float, float, float);

void func_L13_00409C40(char *object, char *data, void *target, Vector128 *input, void *unused0, void *unused1, char *transform) {
    MotionVector desired, change;
    float vertical;
    float heading, distance, speed, height, drop;
    if (!(*(unsigned int *)(data + 0x38) & 0x10))
        func_L13_0040A3B0(object, data, (char *)input, (int)transform);
    heading = 0.0f;
    if (!(*(unsigned int *)(data + 0x38) & 0x10))
        heading = func_L02_00329C48(object, input, transform);
    if (*(float *)(data + 0x30) < heading) {
        func_00282C88(&desired.q);
    } else {
        float gap;
        distance = func_00282E48(object + 0x10, target);
        *(float *)(data + 0xCC) = distance;
        gap = *(float *)(data + 0x34);
        if (distance <= gap) {
            qzero(&desired);
        } else {
            gap = distance - gap;
            speed = func_00282C10((gap + gap) * *(float *)(data + 0x24));
            if (*(float *)(data + 0x28) < speed)
                speed = *(float *)(data + 0x28);
            func_L02_003294D8(object, desired.f, speed);
        }
    }
    func_00282CF0(change.f, desired.f, (float *)(data + 0xA0));
    func_002AFEB8(object, (char *)&change, (char *)&change, 0.0f, transform);
    if (func_00282DB0(&desired, data + 0xA0) > 0.0f)
        func_002AC9F8(change.f, *(float *)(data + 0x20));
    else
        func_002AC9F8(change.f, *(float *)(data + 0x24));
    func_00282CC0(data + 0xA0, data + 0xA0, &change);
    *(float *)(data + 0xB0) = func_002AFF08(object, data + 0xA0, transform);
    if (!(*(unsigned int *)(data + 0x38) & 4)) {
        height = func_002B0360(object + 0x10);
        if (*(float *)(data + 0x90) < height) {
            func_L00_003253A0((u8 *)object, (float *)(data + 0xA0), (float *)(data + 0xA0), *(float *)(data + 0x2C));
            if (*(short *)(data + 0xC0) == 0)
                *(unsigned int *)(data + 0x94) |= 0x20;
        } else {
            vertical = func_002AFF38(object, data + 0xA0, transform);
            drop = vertical;
            if (*(float *)(data + 0x90) - height < drop)
                vertical = *(float *)(data + 0x90) - height;
            else if (vertical < 0.0f)
                vertical = 0.0f;
            func_002AAC80(&vertical, *(float *)(data + 0x90) - height, 0.011111111380159855f, 0.011111111380159855f, 1.0f);
            func_002AFEB8(object, data + 0xA0, data + 0xA0, vertical, transform);
        }
    }
}

extern int func_L13_0040A2C8(char *, char *);
extern void func_002AFE58(char *, char *, char *, float, char *);
extern void func_002AFD88(char *, char *, float, float, float);
void func_L13_00409EE8(char *obj, char *data, char *target, char *unused, char *transform)
{
    Vector128 old;
    int any, hit, i;
    float height, speed;
    func_00282CC0(obj + 0x10, obj + 0x10, data + 0xA0);
    qcopy(&old, obj + 0x10);
    *(int *)(data + 0x84) = 0;
    qzero(data + 0x60);
    any = 0; hit = 0;
    for (i = 0; i < 8; i++) {
        hit |= func_L13_0040A2C8(obj, data);
        any |= hit;
        if (!hit) break;
    }
    if (any) {
        func_00282CF0(data + 0xA0, obj + 0x10, target);
        speed = func_002AFF08(obj, data + 0xA0, transform);
        if (*(float *)(data + 0xB0) < speed)
            func_002AFE58(obj, data + 0xA0, data + 0xA0, *(float *)(data + 0xB0), transform);
        else *(float *)(data + 0xB0) = speed;
        height = func_002B0360(obj + 0x10);
        if (height <= *(float *)(data + 0x90)) {
            func_002AFD88(obj, obj + 0x10, 0.0f, 0.0f, *(float *)(data + 0x90) - height);
            func_002AFEB8(obj, data + 0xA0, data + 0xA0, 0.0f, transform);
        }
        if (*(float *)(data + 0xB0) < *(float *)(data + 0x28) * 0.5f)
            (*(int *)(data + 0x80))++;
        else *(int *)(data + 0x80) = 0;
    } else *(int *)(data + 0x80) = 0;
    func_00282CF0(data + 0x70, obj + 0x10, &old);
}

/* func_L13_0040A0A0 is defined in L13_0040A0A0.c. */



extern float func_0032E870(char *, void *, char *);

extern float func_003281B8(void *, char *, int, float, float, float, float);

extern void func_002F8FA0(void *, void *);

extern void func_002F92E8(char *, char *, void *);

extern float func_002F86B0(float);

typedef int TI128 __attribute__((mode(TI)));

/* func_L13_0040A3B0 is matched in L13_0040A3B0.c (built with -frac2-zero-ti-barrier). */


void func_L13_0040A480(char *a0)
{
    char tmp[16];
    func_00282CF0(tmp, D_00189EA0, a0 + 0x10);
    func_L13_0040A3B0(a0, (void *)ref_L13_0040A480_00(a0), tmp, 0);
}

void func_L13_0040A4D0(char *a0)
{
    char *p = *(char **)(a0 + 0x68);
    u16 value;

    func_00282948(p + 0x240);
    func_00282948(p + 0x244);
    value = *(u16 *)(a0 + 0x96);
    if (value <= 0xFFFEu) {
        *(u16 *)(a0 + 0x96) = value + 1;
    }
    func_002B0990(a0, p + 0x2E0, 1, 1, 2.5f);
}

typedef struct L13State {
    char pad[0x244];
    int f244;
    int pad2;
    int f24C;
} L13State;

/* The per-entity state: the index at 0x2C0, the kind at 0x2C4 and the partner kind at 0x2CC. */
typedef struct L13EntState {
    u8 pad0[0x2C0];
    s32 f2C0;
    s32 f2C4;
    u8 pad1[4];
    s32 f2CC;
} L13EntState;

extern u16 *D_L13_001FB420[];
extern u8 *D_L13_001B291C __attribute__((section(".sdata")));
extern int D_L13_001B2938 __attribute__((section(".sdata")));

/* Raises the +0x24C flag of each entity of kind 0xEA3 or 0xEA4 in the object's group, and the
   +0x244 flag of kind 0xF35. The kinds are tested one by one, as retail's separate branches show. */
void func_L13_0040A540(u8 *a0)
{
    u16 *q;
    u16 *p;
    u8 *e;

    if (a0[0x21] == 0xFF)
        return;
    q = D_L13_001FB420[a0[0x21]];
    if (q == 0)
        return;
    for (p = q; a0[0x21] != 0xFF && a0[0x21] <= D_L13_001B2938 && p != 0 &&
           ((p != 0 && (s16)p[-1] >= 0) || p == D_L13_001FB420[a0[0x21]]);
         p++) {
        e = D_L13_001B291C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (*(s16 *)(e + 0xAA) == 0xEA3) {
            ((L13State *)*(u8 **)(e + 0x68))->f24C = 1;
        } else if (*(s16 *)(e + 0xAA) == 0xEA4) {
            ((L13State *)*(u8 **)(e + 0x68))->f24C = 1;
        } else if (*(s16 *)(e + 0xAA) == 0xF35) {
            ((L13State *)*(u8 **)(e + 0x68))->f244 = 1;
        }
    }
}

/* Compares the kind at +0x2C4 of the object's state with the kind the pointed-at entity's
   state carries (+0x2CC for a 0xEA3 entity, +0x2C4 for a 0xEA4 one): 1 when the second is the
   successor of the first in 0,1,2, 0 when it is the predecessor, and 2 otherwise. */
s32 func_L13_0040A638(u8 *a0)
{
    L13EntState *st = *(L13EntState **)(a0 + 0x68);
    u8 *e = D_L13_001B291C + (st->f2C0 << 8);
    s32 kind = *(s16 *)(e + 0xAA);
    s32 y, x;

    if (kind == 0xEA3) {
        y = st->f2C4;
        x = ((L13EntState *)*(u8 **)(e + 0x68))->f2CC;
    } else if (kind == 0xEA4) {
        y = st->f2C4;
        x = ((L13EntState *)*(u8 **)(e + 0x68))->f2C4;
    } else {
        x = st->f2C4;
        y = x;
    }
    if (y == x)
        return 2;
    if (y == 0) {
        if (x == 1)
            return 1;
    }
    if (y == 1) {
        if (x == 2)
            return 1;
    }
    if (y == 2) {
        if (x == 0)
            return 1;
    }
    if (y == 0) {
        if (x == 2)
            return 0;
    }
    if (y == 1) {
        if (x == 0)
            return 0;
    }
    if (y == 2) {
        if (x == 1)
            return 0;
    }
    return 2;
}

int func_L13_0040C3A0(char *obj) {
    char mat[0x40] __attribute__((aligned(16)));
    char *s = P(obj,0x68);
    int kind;
    if (!B(obj,0x20)) {
        qcopy(s+0x360,obj+0x10);
        B(s,0x2e)=1; F(s,0x30)=1.25f;
        I(s,0x274)=I(s,0x270)+func_002A77E0(4);
        I(s,0x284)=0; I(s,0x288)=0;
        if (func_002A77E0(2)) H(obj,0x34)|=0x8000;
        B(s,0x150)=0x1a; I(s,0x188)=3;
        F(s,0x174)=F(s,0x170)=0.5f; F(s,0x17c)=0.15f; B(s,0x155)=0xb;
        if (I(s,0x35c)!=-1) I(s,0x1bc)=I(s,0x35c);
        if (!S(s,0x24)) { S(s,0x24)=1; F(s,0x20)=1.0f; }
        P(s,0x25c)=func_0029EFD0(0xea9);
        if (P(s,0x25c) && S(P(s,0x25c),0xaa)==0xea9) {
            func_002B37E8(P(s,0x25c),obj);
            H(P(s,0x25c),0x32)=H(obj,0x32);
            H(P(s,0x25c),0x34)|=0x100;
        }
        F(s,0x84)=0.5f;
        F(s,0x54)=0.2f; F(s,0x50)=0.825f; F(s,0x5c)=F(s,0x58)=0.4f;
        F(s,0x60)=1.5707964897155762f; F(s,0x80)=0.523598849773407f;
        if (I(s,0x2a4)) {
            ((L13C3Flags *)s)->flags|=4; F(s,0x5c)=F(s,0x58)=0.7f;
            H(obj,0x34)|=0x100; F(s,0x60)=12.56637191772461f;
            F(s,0x84)=0.5f; ((L13C3Flags *)s)->flags|=1;
        }
        if (I(s,0x2a8)) { ((L13C3Flags *)s)->flags|=5; F(s,0x50)=0; F(s,0x180)=97.5f; }
        func_002B60B0(obj,0.0033333334140479565f,0.10000000894069672f,0.006981317885220051f,0.8377581834793091f);
        func_002A7750(obj,1,0);
        if (B(obj,0x43)!=13) func_002A7470(obj,13,0,0);
        kind=I(s,0x260);
        if (kind==1) { func_002A7750(obj,2,0); if (B(obj,0x43)!=18) func_002A7470(obj,18,0,0); }
        else if (kind==2) { func_002A7750(obj,3,0); if (B(obj,0x43)!=kind) func_002A7470(obj,2,0,0); }
        if (I(s,0x28c)) func_002A7750(obj,1,4);
        if (I(s,0x2b0)!=-1) {
            func_002A7750(obj,7,0); if (B(obj,0x43)!=2) func_002A7470(obj,2,0,0);
            func_002B60B0(obj,0.0016666667070239782f,0.0416666679084301f,0.006981317885220051f,0.8377581834793091f);
        }
        if (I(s,0x298) && I(s,0x29c)!=-1) func_002A7750(obj,28,6);
        if (I(s,0x2bc)) { func_002A7750(obj,9,0); if (B(obj,0x43)!=18) func_002A7470(obj,18,0,0); }
        if (I(s,0x2c8)) {
            I(obj,0x98)=0; H(obj,0x34)=(H(obj,0x34)|0x41)&0xefff;
            H(P(s,0x25c),0x34)|=0x41; H(P(s,0x25c),0x34)&=0xefff;
            I(P(s,0x25c),0x98)=0; func_002A7750(obj,1,8);
        }
        B(s,0x29)=1; B(s,0x48)=func_00283CF0(17.0f); B(s,0x4a)=func_00283CF0(12.0f);
    }
    if (B(obj,0x31) && func_00282E48(obj+0x10,D_L13_001B98C0)<24.0f) { func_002A93B0(obj); B(obj,0x6f)=22; }
    if (P(s,0x25c) && S(P(s,0x25c),0xaa)==0xea9) {
        func_0029FC20(obj,0,mat); func_00283678(P(s,0x25c)+0xc0,mat); qcopy(P(s,0x25c)+0x10,mat+0x30);
    }
    if (B(s,0x2e)==2) {
        if (P(s,0x25c) && S(P(s,0x25c),0xaa)==0xea9) func_0029F338(P(s,0x25c));
        func_0029F338(obj); return 1;
    }
    if (func_002B0ED8(obj,s+0x140,0)) func_L13_0040CA70((u8 *)obj);
    I(s,0x280)=func_002B3BA8(obj,I(s,0x27c),0.0f,0.0f,0,0);
    I(s,0x2b8)=func_002B3BA8(obj,I(s,0x2b4),0.0f,0.0f,0,0);
    I(s,0x250)=func_002B3BA8(obj,I(s,0x230),F(s,0x238),0.0f,0,0);
    I(s,0x254)=func_002B3BA8(obj,I(s,0x234),F(s,0x23c),0.0f,0,0);
    if (F(obj,0x18)<89.0f || (I(s,0x2a8) && F(obj,0x18)<98.0f)) {
        if (P(s,0x25c) && S(P(s,0x25c),0xaa)==0xea9) func_0029F338(P(s,0x25c));
        I(s,0x20)=0; func_002A6C58(obj,0,3); return 1;
    }
    return 0;
}
#undef I
#undef F
#undef H
#undef S
#undef B
#undef P


void func_L13_0040CA00(char *a0)
{
    char *p = *(char **)(a0 + 0x68);
    u16 value;

    func_00282948(p + 0x240);
    func_00282948(p + 0x244);
    value = *(u16 *)(a0 + 0x96);
    if (value <= 0xFFFEu) {
        *(u16 *)(a0 + 0x96) = value + 1;
    }
    func_002B0990(a0, p + 0x2D0, 4, 1, 2.5f);
}

/* Raises the +0x24C flag of each entity of kind 0xEA3 or 0xEA4 in the object's group, tested one
   by one as in func_L13_0040A540. */
void func_L13_0040CA70(u8 *a0)
{
    u16 *q;
    u16 *p;
    u8 *e;

    if (a0[0x21] == 0xFF)
        return;
    q = D_L13_001FB420[a0[0x21]];
    if (q == 0)
        return;
    for (p = q; a0[0x21] != 0xFF && a0[0x21] <= D_L13_001B2938 && p != 0 &&
           ((p != 0 && (s16)p[-1] >= 0) || p == D_L13_001FB420[a0[0x21]]);
         p++) {
        e = D_L13_001B291C + ((*p & 0x7FFF) << 8);
        if (e == 0)
            break;
        if (*(s16 *)(e + 0xAA) == 0xEA3) {
            ((L13State *)*(u8 **)(e + 0x68))->f24C = 1;
        } else if (*(s16 *)(e + 0xAA) == 0xEA4) {
            ((L13State *)*(u8 **)(e + 0x68))->f24C = 1;
        }
    }
}

/* func_L13_0040D930 is in L13_0040D930-g8.c. */

/* func_L13_0040DC20 is defined in L13_0040DC20-g8.c. */



char *func_L13_00412748(float size, char *position, int trigger, int kind, int red, int green, int blue, int enabled, int flags, int extra, int control)
{
    Vector128 direction[1], up[1], sphere[1], difference[1];
    char *object = func_0029EFD0(0xeae);
    SpawnState *state;
    SpawnObject *m;
    char *camera;
    float angle;
    if (object != 0) {
        m = (SpawnObject *)object;
        state = m->state;
        *(unsigned char *)(object + 0x30) = 0xff;
        *(short *)(object + 0x32) = 0xff;
        object[0x20] = 0;
        qcopy(object + 0x10, position);
        *(float *)(object + 0x1c) = 1.0f;
        camera = (char *)D_L13_001B9780.f140;
        func_00282CF0(direction, camera, object + 0x10);
        func_00282F20(direction, direction, 1.0f);
        func_002AFFD8(object + 0x10, (char *)up, 1);
        qcopy(object + 0xc0, direction);
        func_00282DD8(object + 0xd0, object + 0xc0, up);
        func_00282F20(object + 0xd0, object + 0xd0, 1.0f);
        func_00282DD8(object + 0xe0, object + 0xd0, object + 0xc0);
        m->forward[3] = m->right[3] = m->up[3] = 0.0f;
        /* Both countdowns start together. */
        state->timer = state->life = 60;
        state->outer = size + size;
        state->inner = size*4.0f;
        state->kind = kind;
        state->red = red;
        state->green = green;
        state->blue = blue;
        state->enabled = enabled;
        state->extra = extra;
        state->control = control;
        state->flags = flags;
        state->size = size;
        qcopy(sphere, object + 0x10);
        ((float *)sphere)[3] = size*3.0f;
        if (func_00283DB8(sphere, 128.0f) == 1) {
            state->delay = 10;
            state->fade = 0.1f;
            if (func_00282E48(position, camera) < 48.0f && trigger != 0) {
                char *manager = camera - 0x140;
                *(int *)(manager + 0x16c) = 0;
                *(volatile float *)(manager + 0x160) = 0.075f;
                *(volatile int *)(manager + 0x168) = 40;
            }
            if (state->flags != 0) {
                func_00282CF0(difference, object + 0x10, D_L13_001B9780.f140);
                func_00282F20(difference, difference, 1.0f);
                angle = func_002831B0(func_00282DB0(difference, (char *)&D_L13_001B9780 + 0x370));
                if (1.5707963705f - angle < 0.4537856579f)
                    state->flags = 1;
                else
                    state->flags = 0;
            }
        } else {
            state->delay = 0;
            state->flags = 0;
        }
        func_L13_00412C18(object, (char *)up);
    }
    return object;
}


/* func_L13_00412C18 is matched in L13_00412C18-g8.c. */

INCLUDE_ASM("asm/levels", func_L13_0041AB30);

INCLUDE_ASM("asm/levels", func_L13_0041AD00);
