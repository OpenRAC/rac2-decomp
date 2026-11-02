#include "common.h"

extern float func_00283B98(float, float);

extern float func_00283180(float);

extern float func_00283198(float);

extern void func_L04_003A21F8(char *, s32);

extern char D_L18_002A9C40[];

extern float D_L18_001B97C0[];

extern float func_002A7878(float, float);

extern void func_0029FCC0(void *, int, void *);

extern void func_00282CF0(float *, const float *, const float *);

extern void func_00282F20(char *, char *, float);

extern void func_00282CC0(char *, char *, char *);

extern int func_002A7820(int, int);

extern float func_002A7940(void);

extern int D_L18_001C9D40;

extern void func_L02_003FFC48(void *, int, float, int, float, int, int);

extern s32 func_002E59B0(void *, s32);

extern s32 func_002E5CF8(s32, s32, void *);

extern void *func_002A9640(void *, s32, s32);

extern float func_002A96A0(void *, void *);

extern void func_002AB800(void *, void *);

extern void func_002AB8C0(void *, void *);

extern void func_002A7750(void *, int, int);


extern int func_00283CF0(float);
extern int func_002B3868(void *);
extern void func_002E59F8(int);
extern void func_0029F338(void *);
extern void func_L00_00426478(void *);
extern void func_002B0A68(void *, int, void *, float, float, float, float, int);
extern void func_002A6C58(void *, int, int);
extern char D_00188660[], D_00189EA0[];
extern int func_002A77E0(int);
extern float func_002A78D8(float, float);
extern int func_001163B0(void);
extern void func_00282D30(void *, void *, float);
extern void func_002ACEC0(void *, void *, void *, float);
extern u8 *func_002C2210(void *, int, float, float, unsigned int, int, int, void *, int, float);

typedef int TI128 __attribute__((mode(TI)));

void func_L18_00435CC8(void) {
    func_L04_003A21F8(D_L18_002A9C40, 0x12);
}

void func_L18_00434128(u8 *obj) {
    u8 *state = *(u8 **)(obj + 0x68);
    s32 i;
    for (i = 0; i < 2; i++) {
        u8 *p = &state[i * 0xA0 + 0x610];
        s32 j;
        for (j = 1; j >= 0; j--) {
            float x;
            *(float *)(p + 0x40) = func_00283B98(*(float *)(p + 0x40), *(float *)(p + 0x60));
            *(float *)(p + 0x44) = func_00283B98(*(float *)(p + 0x44), *(float *)(p + 0x64));
            *(float *)(p + 0x48) = func_00283B98(*(float *)(p + 0x48), *(float *)(p + 0x68));
            x = func_00283180(*(float *)(p + 0x40));
            *(float *)(p + 0x20) = x * *(float *)(p + 0x80);
            *(float *)(p + 0x24) = func_00283198(*(float *)(p + 0x44)) * *(float *)(p + 0x84);
            *(float *)(p + 0x28) = -func_00283198(*(float *)(p + 0x48)) * *(float *)(p + 0x88);
            p += 0x10;
        }
    }
}

extern void func_0029FCC0(void *, int, void *);
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282CC0(char *, char *, char *);
extern void func_00282F20(char *, char *, float);
extern char D_00188660[];

#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(s32 *)((u8 *)(p)+(o)))
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))
extern void func_002A7A00(void *,float,float);
extern float func_00283CE0(int);
extern int func_002E59B0(void *,int),func_002E5CF8(int,int,void *);
extern void func_002E59F8(int);
extern int func_002A8C28(void *,void *,int,int,int,int,float,float,float);
extern void func_002A8C00(void *,void *,int,void *,float);

extern int func_002761F8(void *,void *,int,void *,void *);
extern void func_L18_00434A98(char *,int);

extern struct { u8 pad[24];u8 *object;u8 pad1[4];float position[4] __attribute__((aligned(16))); } D_L18_001BFC00;
extern int D_L18_001B2348 __attribute__((sda));
typedef struct {
 u8 pad[0x7e4]; u8 *attached; u8 gap[0x1c]; s16 timer, mode;
} DamoselBeamState;
void func_L18_00433460(u8 *obj) {
 float a[4] __attribute__((aligned(16))),b[4] __attribute__((aligned(16))),v[4] __attribute__((aligned(16)));
 struct { float direction[4] __attribute__((aligned(16))); int owner,mode; u8 type,flags;u16 id; float distance;int enabled; } hit;
 u8 *s=P(obj,0x68),*other;float t;
 func_0029FCC0(P(s,0x7c8),0,a);func_0029FCC0(P(s,0x7c8),1,b);F(s,0x7e0)=0;
 switch(H(s,0x806)) {
 case 0:
  qcopy(s+0x610,a);qcopy(s+0x620,b);qcopy(s+0x6b0,b);qcopy(s+0x6c0,a);
  if(I(s,0x7f0)!=-1) {
   u8 *entry=D_00188660+I(s,0x7f0)*0x70;
   if(P(entry,0x88)==obj && entry[0x74])func_002E59F8(I(s,0x7f0));
  }
  I(s,0x7f0)=-1;break;
 case 1:
  qcopy(s+0x610,a);qcopy(s+0x620,b);qcopy(s+0x6b0,b);qcopy(s+0x6c0,a);
  func_002A8C28(obj,a,0x10001,0,1,0,0.2f,(float)s[0x34],1);
  if(H(s,0x804)>=6) {
   u8 *target=s+0x760;
   u8 *p3=s+0x6a0,*p2=s+0x690,*p1=s+0x680,*p0=s+0x670;
   int i;
   for(i=1;i>=0;i--) {
    func_002A7A00(p0,0.232710599899292f,0.290888249874115f);
    func_002A7A00(p1,0.232710599899292f,0.290888249874115f);
    func_002A7A00(p2,2,5);func_002A7A00(p3,2,5);
    p0+=0xa0;p1+=0xa0;p2+=0xa0;p3+=0xa0;
   }
   H(s,0x804)=0;H(s,0x806)=2;
   if(!func_002E59B0(obj,I(s,0x7f0)))I(s,0x7f0)=func_002E5CF8(1,4,obj);
   if(P(s,0x7bc))qcopy(target,P(s,0x7bc)+0x10);else qcopy(target,s+0x1f0);
  } else F(s,0x7e0)=func_00283CE0(H(s,0x804))/func_00283CE0(5);
  break;
 case 2:
  qcopy(s+0x610,a);qcopy(s+0x6b0,b);
  func_002A8C28(obj,a,0x10001,0,1,0,0.2f,(float)s[0x34],1);
  if(H(s,0x804)<6) {
   t=func_00283CE0(H(s,0x804))/func_00283CE0(5);
   F(s,0x620)=a[0]+(F(s,0x760)-a[0])*t;
   F(s,0x624)=a[1]+(F(s,0x764)-a[1])*t;
   F(s,0x628)=a[2]+(F(s,0x768)-a[2])*t;
   qcopy(s+0x6c0,s+0x620);
   func_00282CF0(v,s+0x620,s+0x610);func_00282F20(v,v,1.0f/30.0f);
   func_002A8C00(&hit,obj,0x210001,v,(float)s[0x34]);
   hit.type=5;hit.flags=3;hit.id=*(u16 *)(obj+0xaa);
   if(func_002761F8(s+0x610,s+0x620,0,obj,&hit)) {
    func_L18_00434A98(s+0x620,15);qcopy(s+0x760,s+0x620);H(s,0x804)=0;
    if(D_L18_001BFC00.object) {
     float *point=D_L18_001BFC00.position;
     u8 *attached;
     H(s,0x806)=3;attached=D_L18_001BFC00.object;P(s,0x7e4)=attached;
     qcopy(s+0x620,point);qcopy(s+0x770,attached+0x10);
    } else H(s,0x806)=4;
   }
  } else {H(s,0x806)=4;func_L18_00434A98(s+0x620,10);}
  break;
 case 3:
  qcopy(s+0x610,a);qcopy(s+0x6b0,b);
  if(H(s,0x804)<51 && (other=P(s,0x7e4)) && other[0x20]!=254 && other[0x20]!=253) {
   func_00282CF0(v,other+0x10,s+0x770);func_00282CC0(s+0x620,s+0x620,v);
   qcopy(s+0x6c0,s+0x620);qcopy(s+0x770,P(s,0x7e4)+0x10);
   if((D_L18_001B2348&15)==(((int)obj>>8)&15))func_L18_00434A98(s+0x620,1);
  } else {
   DamoselBeamState *state=(DamoselBeamState *)s;
   state->attached=0;state->mode=4;state->timer=0;
  }
  break;
 case 4:
  qcopy(s+0x610,a);qcopy(s+0x6b0,b);
  if(H(s,0x804)<5) {
   t=func_00283CE0(H(s,0x804))/func_00283CE0(5);
   F(s,0x620)=F(s,0x760)+(a[0]-F(s,0x760))*t;
   F(s,0x624)=F(s,0x764)+(a[1]-F(s,0x764))*t;
   F(s,0x628)=F(s,0x768)+(a[2]-F(s,0x768))*t;
   F(s,0x6c0)=F(s,0x760)+(b[0]-F(s,0x760))*t;
   F(s,0x6c4)=F(s,0x764)+(b[1]-F(s,0x764))*t;
   F(s,0x6c8)=F(s,0x768)+(b[2]-F(s,0x768))*t;
  } else {
   H(s,0x804)=0;H(s,0x806)=0;
   { u8 *p3=s+0x6a0,*p2=s+0x690,*p1=s+0x680,*p0=s+0x670;
   int i;
   for(i=1;i>=0;i--) {
    func_002A7A00(p0,0.232710599899292f,0.290888249874115f);
    func_002A7A00(p1,0.232710599899292f,0.290888249874115f);
    func_002A7A00(p2,1,1.7f);func_002A7A00(p3,1,1.7f);
    p0+=0xa0;p1+=0xa0;p2+=0xa0;p3+=0xa0;
   } }
  }
 }
 func_L18_00434128(obj);
}

#undef F
#undef I
#undef H
#undef P

/* func_L18_00433B70 lives in L18_00433B70.c. */

INCLUDE_ASM("asm/levels", func_L18_00434510);

void func_L18_00434A98(char *pos, int count) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));
    int i, sign;
    float size, angle, speed;
    u8 *particle;

    *(TI128 *)axis = 0;
    axis[2] = 1.0f;
    func_00282CF0(direction, D_L18_001B97C0, (float *)pos);
    direction[2] = 0.0f;
    for (i = 0; i < count; i++) {
        size = func_002A7878(0.5f, 2.0f);
        sign = func_002A77E0(2);
        if (sign == 0)
            sign--;
        angle = func_002A7878(-1.0471977f, 1.0471977f);
        func_002ACEC0(velocity, direction, axis, angle);
        speed = func_002A7878(0.05f, 3.0f) * (1.0f / 60.0f);
        func_00282F20((char *)velocity, (char *)velocity, speed);
        velocity[2] = func_002A7878(1.0f, 5.0f) * (1.0f / 60.0f);
        qcopy(point, pos);
        point[0] += func_002A78D8(0.0f, 0.15f);
        point[1] += func_002A78D8(0.0f, 0.15f);
        point[2] += func_002A78D8(0.0f, 0.15f);
        if (!(func_001163B0() & 1)) {
            func_00282D30(velocity, velocity, 1.5f);
            particle = func_002C2210(point, 60, size * 0.35f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
            if (particle)
                particle[9] = func_00283CF0(4.0f) + 0x70;
            particle = func_002C2210(point, 60, size * 0.245f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        } else {
            func_00282CF0(extra, D_L18_001B97C0, point);
            func_00282F20((char *)extra, (char *)extra, speed);
            func_00282CC0((char *)velocity, (char *)velocity, (char *)extra);
            particle = func_002C2210(point, 40, size * 2.05f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
            if (particle)
                particle[9] = func_00283CF0(4.0f) + 0x70;
            particle = func_002C2210(point, 40, size * 1.43500006f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        }
        if (particle)
            particle[9] = func_00283CF0(4.0f) + 0x70;
    }
}

void func_L18_00434FC0(u8 *obj) {
    float v[4];
    float w[4];
    float a;

    a = func_002A7878(0.5f, 0.8f);
    func_0029FCC0(obj, 0, v);
    a = a * 0.5f;
    func_00282CF0(w, D_L18_001B97C0, v);
    w[2] = 0.0f;
    func_00282F20((char *)w, (char *)w, 0.2f);
    func_00282CC0((char *)v, (char *)v, (char *)w);
    func_L02_003FFC48(v, 0x807070, a, func_002A7820(0x50, 0x60), func_002A7940(), 0x31, 2);
    func_L02_003FFC48(v, 0x802020, 0.56f, func_002A7820(0x16, 0x32), func_002A7940(), 0xB, 2);
}

void func_L18_004350E0(char *pos, int count) {
    float velocity[4] __attribute__((aligned(16)));
    float point[4] __attribute__((aligned(16)));
    float direction[4] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));
    int i, sign;
    float size, angle, speed;
    u8 *particle;

    *(TI128 *)axis = 0;
    axis[2] = 1.0f;
    func_00282CF0(direction, D_L18_001B97C0, (float *)pos);
    direction[2] = 0.0f;
    for (i = 0; i < count; i++) {
        size = func_002A7878(0.5f, 2.0f);
        sign = func_002A77E0(2);
        if (sign == 0)
            sign--;
        angle = func_002A7878(-1.0471977f, 1.0471977f);
        func_002ACEC0(velocity, direction, axis, angle);
        speed = func_002A7878(0.05f, 3.0f) * (1.0f / 60.0f);
        func_00282F20((char *)velocity, (char *)velocity, speed);
        velocity[2] = func_002A7878(1.0f, 5.0f) * (1.0f / 60.0f);
        qcopy(point, pos);
        point[0] += func_002A78D8(0.0f, 0.15f);
        point[1] += func_002A78D8(0.0f, 0.15f);
        point[2] += func_002A78D8(0.0f, 0.15f);
        if (!(func_001163B0() & 1)) {
            func_00282D30(velocity, velocity, 1.5f);
            particle = func_002C2210(point, 60, size * 0.05f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
            if (particle)
                particle[9] = func_00283CF0(4.0f) + 0x70;
            particle = func_002C2210(point, 60, size * 0.035f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        } else {
            func_00282CF0(extra, D_L18_001B97C0, point);
            func_00282F20((char *)extra, (char *)extra, speed);
            func_00282CC0((char *)velocity, (char *)velocity, (char *)extra);
            particle = func_002C2210(point, 40, size * 0.15f, size, 0x7F800000, 0, sign, velocity, 0, 0.002f);
            if (particle)
                particle[9] = func_00283CF0(4.0f) + 0x70;
            particle = func_002C2210(point, 40, size * 0.105000004f, size * 0.7f, 0x7F7F7F7F, 1, -sign, velocity, 0, 0.002f);
        }
        if (particle)
            particle[9] = func_00283CF0(4.0f) + 0x70;
    }
}

INCLUDE_ASM("asm/levels", func_L18_004354F8);


/* func_L18_00435B10 is defined in L18_00435B10-g8.c. */

/* func_L18_00436B80 is in L18_00433460-f7-g8.c. */

/* func_L18_00437190 is defined in L18_00437190-g8.c. */

/* func_L18_00439960 lives in L18_00437AA0.c. */

extern int D_L18_001C9D40;

extern float func_00283B98(float, float);

extern s32 func_002E59B0(void *, s32);

extern s32 func_002E5CF8(s32, s32, void *);

extern void *func_002A9640(void *, s32, s32);

extern float func_002A96A0(void *, void *);

extern void func_002AB800(void *, void *);

extern void func_002AB8C0(void *, void *);


void func_L18_00439FC8(u8 *obj) {
    u8 *state;
    u8 *p;
    float f;

    if (D_L18_001C9D40 != 0) return;
    state = *(u8 **)(obj + 0x68);
    switch (*(u8 *)(obj + 0x20)) {
    case 0:
        *(short *)(state + 0x24) = 0x12;
        *(float *)(state + 0x20) = 18.0f;
        func_002A7750(obj, 1, -1);
        return;
    case 1:
        if (func_002E59B0(obj, *(s32 *)(state + 0x68)) == 0) {
            *(s32 *)(state + 0x68) = func_002E5CF8(0, 4, obj);
        }
        p = state + 0x50;
        *(float *)(obj + 0xF8) = func_00283B98(*(float *)(obj + 0xF8),
                                               *(float *)(state + 0x64) * 0.000290888245f);
        f = func_002A96A0(obj, func_002A9640(obj, 0x230000, 0));
        if (f > 0.0f) {
            *(u8 *)(state + 0x57) = 0xFF;
            *(u8 *)(state + 0x58) = 0x40;
            *(u8 *)(state + 0x59) = 0;
            func_002AB800(obj, p);
            *(float *)(state + 0x20) = *(float *)(state + 0x20) - f;
        }
        func_002AB8C0(obj, p);
        *(u8 *)(obj + 0xA8) = 0xFF;
        return;
    }
}


/* func_L18_0043C258 lives in L18_0043C258-g8.c. */

/* func_L18_0043C778 is defined in L18_0043C778-g64.c. */

/* func_L18_0043CAF8 is defined in L18_0043CAF8-g8.c. */

/* func_L18_0043F130 is defined in L18_0043F130-qcopy-barrier.c. */

void func_L18_0043F308(float *out, float *b, float *c, float *a, float *d, float t)
{
    float t2, t3, p, q, r;

    if (t == 0.0f) {
        qcopy(out, b);
        return;
    }
    if (t == 1.0f) {
        qcopy(out, c);
        return;
    }
    t2 = t * t;
    t3 = t2 * t;

    p = (d[0] - c[0]) - (a[0] - b[0]);
    q = (a[0] - b[0]) - p;
    r = c[0] - a[0];
    out[0] = p * t3 + q * t2 + r * t + b[0];

    p = (d[1] - c[1]) - (a[1] - b[1]);
    q = (a[1] - b[1]) - p;
    r = c[1] - a[1];
    out[1] = p * t3 + q * t2 + r * t + b[1];

    p = (d[2] - c[2]) - (a[2] - b[2]);
    q = (a[2] - b[2]) - p;
    r = c[2] - a[2];
    out[2] = p * t3 + q * t2 + r * t + b[2];
    out[3] = 0.0f;
}



INCLUDE_ASM("asm/levels", func_L18_0043FC70);

/* func_L18_00440718 is defined in L18_00440718-g8.c. */

/* func_L18_00441050 is defined in L18_00441050-g8.c. */

typedef struct { char pad[0x74]; unsigned char active; char gap[0x13]; void *owner; } DamoselSoundAnchor;
extern char D_00188660[];
extern char D_00189EA0[];
extern int func_002B3868(void *);
extern void func_002E59F8(int);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void func_002AFEB8(void *, void *, void *, void *, float);
extern void func_002B0A68(void *, int, void *, float, float, float, float, int);
extern void func_002A6C58(void *, int, int), func_0029F338(void *);
extern void func_L00_00426478(void *);

void func_L18_00441438(unsigned char *object)
{
    char *state = *(char **)(object + 0x68);
    char *hit;
    char *owner;
    int excluded;
    float zero, damage;
    float direction[4];
    switch (object[0x20]) {
    case 0:
        *(int *)(state + 0x100) = -1;
        *(unsigned short *)(object + 0x34) |= 0x1000;
        state[0x48] = func_00283CF0(15.0f);
        state[0x4a] = func_00283CF0(6.0f);
        func_002A7750(object, 1, -1);
        break;
    case 1:
        if (func_002B3868(object)) {
            if (*(int *)(state + 0x100) != -1 && ((DamoselSoundAnchor *)(D_00188660 + *(int *)(state + 0x100) * 112))->owner == object && ((DamoselSoundAnchor *)(D_00188660 + *(int *)(state + 0x100) * 112))->active)
                func_002E59F8(*(int *)(state + 0x100));
            *(int *)(state + 0x100) = -1;
        }
        hit = func_002A9640(object, 0x10000, 0);
        if (!hit) goto intact;
        owner = *(char **)(hit + 0x20);
        excluded = 0;
        if (owner && (*(short *)(owner + 0xaa) == 0xb69 || *(short *)(owner + 0xaa) == 0xf9e)) excluded = 1;
        if (excluded) break;
        zero = 0.0f;
        damage = func_002A96A0(object, hit);
        object[0xa8] = 255;
        *(float *)(state + 0x20) -= damage;
        if (*(float *)(state + 0x20) <= zero) {
            func_002ABBB8(object, object + 0x10, 0, zero, zero, 10, 3, 9,
                         4.0f, 2.0f, 9.0f, zero, -1, 15.0f, 1, 1, -1, 0, 0x810001);
            func_002E5CF8(0, 0, object);
            func_00282CF0(direction, (float *)(object + 0x10), (float *)D_00189EA0);
            func_002AFEB8(object, direction, direction, 0, zero);
            func_00282F20((char *)direction, (char *)direction, 0.10000001f);
            func_002B0A68(object, 0x1fff, direction, 3.0f, 6.0f, 3.0f, 6.0f, 255);
            func_002A6C58(object, 0, 3);
            func_0029F338(object);
        }
        break;
intact:
        func_L00_00426478(object);
        break;
    }
}

/* func_L18_00447128 is defined in L18_00447128-g8.c. */
