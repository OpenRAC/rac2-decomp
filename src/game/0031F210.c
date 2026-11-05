#include "include_asm.h"
#include "common.h"

extern long long func_0027C878(int id);
extern float func_002A7940(void);
extern void func_00282D30(char *dst, char *src, float scale);
extern float func_00283248(float x, float y);
extern float func_00282E80(char *p, float *v);
extern void func_00283410(float *matrix, float *quat);
extern void func_00282CF0(float *off, float *v, char *p);
extern void func_00282F20(float *dst, float *src, float angle);
extern void func_00280B90(char *pkt, float *matrix, int mode);
/* Camera position used by the facing-vector helpers. */
typedef struct {
    char pad_000[0x140];
    float x_140;
    float y_144;
    float z_148;
} BootAimVector;

extern signed char D_001B5200[];



extern char D_00189E20_9[];

extern float func_00282C88_1(float *buf);

extern float func_00282DF0(float *buf);

extern void func_002A91F0(void *, float *);

/* func_0031F210 is in 0031F210-ribbon.c. */


/* func_0031FC28 is in 0031F210-pickup-g8.c. */

/* func_003202E8 is in 0031F210-g8.c. */

extern void func_002A7750(unsigned char *, unsigned char, int);
extern char *func_0029EFD0(int);
extern void func_002A0F48(void *);
extern void func_00321F60(char *);
extern void func_00321E28(char *);
extern void func_00282C88(void *);
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern void func_002B60B0(char *, float, float, float, float);
extern void func_0029FCC0(char *, int, void *);
extern int func_002761F8(void *, void *, int, char *, int);
extern float func_002A89A8(void *, int, float);
extern void func_002A7470(char *, int, int, int);
extern int func_002A8508(int, int);
extern int func_002B3BA8(char *, int, float, float, int, int);
extern void func_002AC728(char *, void *, int, float, float);
extern void func_002A6C58(char *, int, int);
extern void func_002A93B0(char *);
extern void func_0029FC20(char *, int, float *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CC0(float *, float *, float *);
extern int func_002B0ED8(char *, void *, int);
extern float func_00282E48(void *, void *);
extern float D_001BAFA0[];
extern char *D_001B1C4C MACRO_ADDR;
extern char D_001B5340[];
extern int D_001B1B78 MACRO_ADDR;
extern short *D_001EE5A0[];
extern char *D_001B1B5C MACRO_ADDR;
#define F(p,o) (*(float *)((p)+(o)))
#define I(p,o) (*(int *)((p)+(o)))
#define U(p,o) (*(unsigned char *)((p)+(o)))
#define H(p,o) (*(unsigned short *)((p)+(o)))
int func_003216E8(char *object)
{
    float matrix[16];
    char *data = *(char **)(object + 0x68);
    int status, special;
    char *child;
    short *list;
    char *other;
    if (!U(object,0x20)) {
        F(object,0x2c) *= 1.1f;
        U(object,0x7e) |= 1;
        *(char **)(data+0x18)=data+0x110;
        F(data,0x284) *= 0.017453294f;
        U(data,0x48)=func_00283CF0(20.0f);
        U(data,0x4a)=func_00283CF0(16.0f);
        if(func_002A77E0(2)==1) H(object,0x34)|=0x8000;
        F(data,0x90)=0.5f;
        F(data,0x94)=0.5f;
        F(data,0x114)=0.5f;
        U(data,0x70)=15;
        I(data,0xa8)=5;
        U(data,0x71)=19;
        U(data,0x72)=21;
        U(data,0x76)=23;
        U(data,0x77)=24;
        F(data,0x7c)=0.10000001f;
        F(data,0x80)=1.0f/15.0f;
        F(data,0x84)=1.0f/240.0f;
        F(data,0x88)=1.0f/120.0f;
        F(data,0x8c)=1.0f/240.0f;
        F(data,0x9c)=0.4f;
        *(char *)(data+0xcc)=-1;*(char *)(data+0xcd)=-1;*(char *)(data+0xce)=-1;*(char *)(data+0xcf)=-1;*(char *)(data+0xd2)=-1;*(char *)(data+0xd3)=-1;
        I(data,0x2c0)=-1;
        F(data,0x110)=0.8f;
        F(data,0x118)=0.4f;
        F(data,0x11c)=0.4f;
        F(data,0x120)=1.134464144706726f;
        F(data,0x140)=0.52359885f;
        F(data,0x13c)=0.0055555557f;
        *(char **)(data+0x158)=data+0x3d0;
        *(char **)(data+0x15c)=data+0x450;
        func_002B60B0(object,0.0044444446f,1.0f/7.5f,0.0011635529808700085f,0.10471977f);
        qcopy(data+0x200,object+0x10);
        U(data,0x2e)=1;
        I(data,0x280)=0;
        F(data,0x210)=1.0f;
        F(data,0x21c)=5.0f;
        F(data,0x220)=10.0f;
        F(data,0x298)=(float)U(data,0x34);
        U(data,0x28)=3;
        func_0029FCC0(object,0,data+0x380);
        F(data,0x388)+=20.0f;
        func_0029FCC0(object,0,data+0x390);
        if(func_002761F8(data+0x390,data+0x380,0,object,0)) qcopy(data+0x380,D_001BAFA0);
        if(!I(data,0x27c) && I(data,0x288)==-1) {
            F(object,0x18)=func_002A89A8(object+0x10,0,0.5f);
            func_002A7750((unsigned char *)object,1,0);
            if(U(object,0x43)) func_002A7470(object,0,0,0);
        } else {
            func_002A7750((unsigned char *)object,3,2);
            if(U(object,0x43)!=11) func_002A7470(object,11,0,0);
            I(object,0x98)=0;F(data,0x30)=2.5f;
            child=func_0029EFD0(0xab7);
            *(char **)(data+0x2ac)=child;
            if(!child) return 1;
            U(child,0x30)=U(object,0x30);
            H(*(char **)(data+0x2ac),0x32)=H(object,0x32);
            U(*(char **)(data+0x2ac),0x31)=1;
            *(long long *)(*(char **)(data+0x2ac)+0x38)=*(long long *)(object+0x38);
            H(*(char **)(data+0x2ac),0x34)|=0x41;
            qcopy_nc(*(char **)(data+0x2ac)+0x10,object+0x10);
            func_002A0F48(*(char **)(data+0x2ac));
        }
        if(I(data,0x288)!=-1) {
            func_002A7750((unsigned char *)object,2,0);
            qcopy(data+0x380,D_001B1C4C+(I(data,0x288)<<7)+0x30);
            U(object,0x30)=0x80;
        }
    }
    if(U(object,0x31) && func_00282E48(object+0x10,D_001B5340)<24.0f) {
        func_002A93B0(object);U(object,0x6f)=22;
    }
    func_0029FCC0(object,0,data+0x390);
    func_0029FCC0(object,1,data+0x3a0);
    func_0029FCC0(object,2,data+0x3b0);
    func_0029FC20(object,3,matrix);
    func_00282C88(data+0x3c0);
    I(data,0x3c8)=0;F(data,0x3c0)=0.25f;
    func_002830C0(data+0x3c0,data+0x3c0,matrix);
    func_00282CC0((float *)(data+0x3c0),(float *)(data+0x3c0),matrix+12);
    special=0;
    if(U(data,0x2e)==2) special=1;
    status=func_002B0ED8(object,data+0x60,0);
    if(status || special) {
        F(data,0x30)=0.5f;
        if(status==5) {I(data,0xf0)=0;F(data,0xf4)=0.8377582f;}
        func_00321F60(object);
        if((status==4 || status==5 || special) && D_001B1B78>=U(object,0x21) && func_002A8508(U(object,0x21),-1)>=2) {
            list=D_001EE5A0[U(object,0x21)];
            for (;;) {
                other=(char *)(D_001B1B5C+((*list & 0x7fff)<<8));
                if (*(short *)(other+0xaa)==0xb0a) {
                    char *d=*(char **)(other+0x68);
                    if (!I(d,0x294)) {I(d,0x294)=1;break;}
                } else if (*(short *)(other+0xaa)==0xb0b) {
                    char *d=*(char **)(other+0x68);
                    if (!I(d,0x294)) {
                        I(d,0x294)=1;
                        if (!I(data,0x29c)) break;
                    }
                }
                if (*list++ < 0) break;
            }
        }
    }
    I(data,0x258)=func_002B3BA8(object,I(data,0x250),F(data,0x268),10.0f,0,0);
        I(data,0x25c)=func_002B3BA8(object,I(data,0x254),F(data,0x26c),10.0f,0,0);
        if(F(object,0x18)<90.0f) {
            func_002AC728(object,object+0x10,-1,0.5f,13.0f);
            func_002A6C58(object,0,3);return 1;
        }
    if(special) {func_00321E28(object);return 1;}
    return 0;
}


extern void func_0029F338(void *);
extern void func_00321F60(char *);

void func_00321E28(char *object)
{
    char *data = *(char **)(object + 0x68);
    char *child = *(char **)(data + 0x2AC);
    if (child != 0 && *(short *)(child + 0xAA) == 0xAB7) {
        func_0029F338(child);
        *(char **)(data + 0x2AC) = 0;
    }
    func_00321F60(object);
}

extern void func_002AB8C0(char *, char *);
extern int func_00282978(void *);
extern void func_002AEC48(void *, void *, int, float, float);
extern void func_002B0990(char *, char *, int, int, float);

void func_00321E80(char *object)
{
    char *data = *(char **)(object + 0x68);
    char *first;
    func_002AB8C0(object, data + 0x50);
    first = data + 0x3D0;
    func_00282978(data + 0x270);
    func_00282978(data + 0x272);
    func_002AEC48(object, first, 5, 0.03f, 0.3f);
    func_002AEC48(object, data + 0x450, 6, 0.03f, 0.3f);
    if (*(unsigned short *)(object + 0x96) < 65535)
        (*(unsigned short *)(object + 0x96))++;
    func_002B0990(object, first, 5, 1, 2.5f);
}

/* func_00321FE0 is in the -G8 sibling. */

void func_003220A8(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -2.0f;
    *(float *)(p + 24) = 2.0f;
    *(float *)(p + 40) = -2.0f;
    *(float *)(p + 56) = 2.0f;
    *(float *)(p + 4) = -2.0f;
    *(float *)(p + 36) = 2.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -2.0f;
    *(float *)(p + 52) = 2.0f;
    *(float *)(p + 60) = 1.0f;
}

/* func_00322138 is in 0031F210-q.c. */

void func_00322340(int unused, char *pos, int color, int first, int second, float scale)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;
    float dx, dy;

    func_003220A8(pkt);
    *(int *)(pkt + 80) = 0;
    *(float *)(pkt + 92) = 1.0f;
    *(float *)(pkt + 96) = 1.0f;
    *(float *)(pkt + 104) = 1.0f;
    *(float *)(pkt + 108) = 1.0f;
    *(int *)(pkt + 84) = 0;
    *(int *)(pkt + 88) = 0;
    *(int *)(pkt + 100) = 0;
    r = func_0027C878(11);
    *(long long *)(pkt + 112) = 0;
    *(long long *)(pkt + 120) = r;
    *(long long *)(pkt + 128) = 0xFF9000000260LL;
    *(long long *)(pkt + 136) = 0x8000000048LL;
    dx = ((BootAimVector *)D_001B5200)->x_140 - *(float *)pos;
    dy = ((BootAimVector *)D_001B5200)->y_144 - *(float *)(pos + 4);
    *(int *)(pkt + 76) = color + first;
    *(int *)(pkt + 72) = color + first;
    *(int *)(pkt + 68) = color + first;
    *(int *)(pkt + 64) = color + first;
    quat[3] = 0;
    quat[2] = func_00283248(dx, dy);
    quat[1] = -func_00283248(func_00282E80(pos, &((BootAimVector *)D_001B5200)->x_140),
                              ((BootAimVector *)D_001B5200)->z_148 - *(float *)(pos + 8));
    quat[0] = func_002A7940();
    func_00283410(m, quat);
    func_00282CF0(off, &((BootAimVector *)D_001B5200)->x_140, pos);
    func_00282F20(off, off, 0.5f);
    m[12] = *(float *)(pos) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;
    func_00282D30(pkt, pkt, scale);
    func_00282D30(pkt + 16, pkt + 16, scale);
    func_00282D30(pkt + 32, pkt + 32, scale);
    func_00282D30(pkt + 48, pkt + 48, scale);
    func_00280B90(pkt, m, 0);
    *(int *)(pkt + 76) = color + second;
    *(int *)(pkt + 72) = color + second;
    *(int *)(pkt + 68) = color + second;
    *(int *)(pkt + 64) = color + second;
    func_00282D30(pkt, pkt, 0.5f);
    func_00282D30(pkt + 16, pkt + 16, 0.5f);
    func_00282D30(pkt + 32, pkt + 32, 0.5f);
    func_00282D30(pkt + 48, pkt + 48, 0.5f);
    func_00280B90(pkt, m, 0);
}



typedef unsigned int JointEffectQuad __attribute__((mode(TI)));
extern void func_0029FC20(char *, int, float *);
extern void func_00282CC0(float *, float *, float *);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern int func_002A7820(int, int);
extern void func_002ACB48(float *, float);
/* Integer and FP arguments keep their order in the separate EE banks. */
extern int func_002A8C28(char *, float *, float, int, float, float, int, int, int);
extern void *func_002C65A0(float *, float *, float, float, float, int, int, int, int, int, int);
extern unsigned char *func_002C16C0(float *, float *, int, int, int, int,
                                    float, float, float, float, float);
extern unsigned char *D_001F2540[];

/* Effect at an object's joint: func_002A8C28 at the joint and at two points along its axis,
   three grey func_002C65A0 particles at the joint and one func_002C16C0 particle at the near
   point, which at random takes flags 0x48 and the 0x707070 tint. */
void func_00322690(char *object, float *position, int joint, float intensity)
{
    float matrix[16] __attribute__((aligned(16)));
    float axis[4] __attribute__((aligned(16)));
    float base[4] __attribute__((aligned(16)));
    float near[4] __attribute__((aligned(16)));
    float far[4] __attribute__((aligned(16)));
    float velocity[4] __attribute__((aligned(16)));
    float drift[4] __attribute__((aligned(16)));
    int i, j;
    float start, end, gravity;
    unsigned char *particle;

    func_0029FC20(object, joint, matrix);
    qcopy(axis, matrix + 4);
    func_00282CF0(base, matrix + 12, (char *)position);
    func_00282F20(near, axis, 0.85f);
    func_00282F20(far, axis, 1.6f);
    func_00282CC0(near, near, base);
    func_00282CC0(far, far, base);
    near[2] -= 0.1f;
    far[2] -= 0.1f;
    func_00282F20(velocity, matrix + 4, 0.25f);
    func_00282CC0(velocity, velocity, position);
    func_002A8C28(object, base, 0.3f, 1, intensity, 1.0f, 0, 1, 0);
    func_002A8C28(object, near, 0.3f, 1, intensity, 1.0f, 0, 1, 0);
    func_002A8C28(object, far, 0.3f, 1, intensity, 1.0f, 0, 1, 0);
    for (i = 0; i < 3; i++) {
        func_002ACB48(base, 0.1f);
        start = func_002A7878(0.2f, 0.4f) * 210000.0f;
        end = func_002A7878(1.0f, 1.5f) * 210000.0f;
        gravity = func_002A78D8(0.0f, 0.01f);
        func_002C65A0(base, velocity, start, end, gravity, 7, 0x808080, 30, 127, 32, 0);
    }
    *(JointEffectQuad *)drift = 0;
    drift[2] = 0.1f;
    drift[3] = 1.0f;
    func_00282CC0(drift, drift, position);
    for (j = 0; j < 1; j++) {
        particle = func_002C16C0(near, drift, 15, 60, 0x606060, 3,
                                 105000.0f, 21000.0f, 1.0f, -0.0002f, 0.0f);
        if (particle) {
            particle[2] = *D_001F2540[23];
            particle[3] = 0x44;
            if (func_002A7820(0, 1)) {
                unsigned char *payload;
                unsigned short alpha;
                particle[3] = 0x48;
                alpha = 127;
                *(unsigned int *)(particle + 4) = 0x70707F;
                payload = particle + 0x20;
                payload[0x11] = 0x70;
                payload[0x12] = 0x70;
                payload[0x13] = 0x70;
                *(unsigned short *)(payload + 0x1E) = alpha;
            }
        }
    }
}



extern int func_00273B70(char *);
extern void func_002A7750(unsigned char *, unsigned char, int);
void func_00322C10(char *object)
{
    char *data = *(char **)(object + 0x68);
    *(float *)(data + 4) -= 1.0f / 120.0f;
    switch (*(unsigned char *)(object + 0x20)) {
    case 0:
        if (func_00273B70(object)) {
            func_002A7750((unsigned char *)object, 1, -1);
            *(unsigned short *)(object + 0x34) |= 0x2800;
        }
        break;
    case 1:
        func_00273B70(object);
        if (*(unsigned char *)(object + 0x23) < 2)
            func_0029F338(object);
        else
            *(unsigned char *)(object + 0x23) -= 2;
        break;
    }
}

/* func_003248A8 is in 0031F210-init.c. */

extern void func_00325D30(char *, char *);
extern void func_00325320(char *);

void func_003250F8(char *object)
{
    char *data = *(char **)(object + 0x68);
    char *child;
    func_00325D30(object, data + 0x2A0);
    child = *(char **)(data + 0x2E0);
    if (child != 0 && *(short *)(child + 0xAA) == 0xAB7) {
        func_0029F338(child);
        *(char **)(data + 0x2E0) = 0;
    }
    func_00325320(object);
}

/* func_00325158 is in 0031F210-turn-g8.c. */

/* func_00325320 is in the -G8 sibling. */

void func_003253A0(char *p)
{
    *(long long *)(p + 112) = 0LL;
    *(int *)(p + 80) = 0;
    *(int *)(p + 84) = 0;
    *(float *)(p + 88) = 1.0f;
    *(int *)(p + 92) = 0;
    *(int *)(p + 96) = 0;
    *(float *)(p + 100) = 1.0f;
    *(float *)(p + 104) = 1.0f;
    *(float *)(p + 108) = 1.0f;
    *(float *)(p + 8) = -2.0f;
    *(float *)(p + 24) = 2.0f;
    *(float *)(p + 40) = -2.0f;
    *(float *)(p + 56) = 2.0f;
    *(float *)(p + 4) = -2.0f;
    *(float *)(p + 36) = 2.0f;
    *(int *)(p + 0) = 0;
    *(int *)(p + 16) = 0;
    *(int *)(p + 32) = 0;
    *(int *)(p + 48) = 0;
    *(float *)(p + 12) = 1.0f;
    *(float *)(p + 28) = 1.0f;
    *(float *)(p + 44) = 1.0f;
    *(long long *)(p + 128) = 0x0000FF9000000260LL;
    *(float *)(p + 20) = -2.0f;
    *(float *)(p + 52) = 2.0f;
    *(float *)(p + 60) = 1.0f;
}


void func_00325638(int unused, char *pos, int color, int first, int second, float scale)
{
    char pkt[144];
    float m[16];
    float quat[4];
    float off[4];
    long long r;
    float dx, dy;

    func_003253A0(pkt);
    *(int *)(pkt + 80) = 0;
    *(float *)(pkt + 92) = 1.0f;
    *(float *)(pkt + 96) = 1.0f;
    *(float *)(pkt + 104) = 1.0f;
    *(float *)(pkt + 108) = 1.0f;
    *(int *)(pkt + 84) = 0;
    *(int *)(pkt + 88) = 0;
    *(int *)(pkt + 100) = 0;
    r = func_0027C878(11);
    *(long long *)(pkt + 112) = 0;
    *(long long *)(pkt + 120) = r;
    *(long long *)(pkt + 128) = 0xFF9000000260LL;
    *(long long *)(pkt + 136) = 0x8000000048LL;
    dx = ((BootAimVector *)D_001B5200)->x_140 - *(float *)pos;
    dy = ((BootAimVector *)D_001B5200)->y_144 - *(float *)(pos + 4);
    *(int *)(pkt + 76) = color + first;
    *(int *)(pkt + 72) = color + first;
    *(int *)(pkt + 68) = color + first;
    *(int *)(pkt + 64) = color + first;
    quat[3] = 0;
    quat[2] = func_00283248(dx, dy);
    quat[1] = -func_00283248(func_00282E80(pos, &((BootAimVector *)D_001B5200)->x_140),
                              ((BootAimVector *)D_001B5200)->z_148 - *(float *)(pos + 8));
    quat[0] = func_002A7940();
    func_00283410(m, quat);
    func_00282CF0(off, &((BootAimVector *)D_001B5200)->x_140, pos);
    func_00282F20(off, off, 0.5f);
    m[12] = *(float *)(pos) + off[0];
    m[13] = *(float *)(pos + 4) + off[1];
    m[14] = *(float *)(pos + 8) + off[2];
    m[15] = 1.0f;
    func_00282D30(pkt, pkt, scale);
    func_00282D30(pkt + 16, pkt + 16, scale);
    func_00282D30(pkt + 32, pkt + 32, scale);
    func_00282D30(pkt + 48, pkt + 48, scale);
    func_00280B90(pkt, m, 0);
    *(int *)(pkt + 76) = color + second;
    *(int *)(pkt + 72) = color + second;
    *(int *)(pkt + 68) = color + second;
    *(int *)(pkt + 64) = color + second;
    func_00282D30(pkt, pkt, 0.5f);
    func_00282D30(pkt + 16, pkt + 16, 0.5f);
    func_00282D30(pkt + 32, pkt + 32, 0.5f);
    func_00282D30(pkt + 48, pkt + 48, 0.5f);
    func_00280B90(pkt, m, 0);
}



/* func_00325A88 (cursor bookkeeping and a 16-byte copy) is a near miss:
   nonmatching/game/func_00325A88.c */
void func_00325A88(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);

    *(int *)(state + 0x2B8) = 0;
    *(int *)(state + 0x2B4) = (*(int *)(state + 0x2B4) + 1) % 4;
    if (*(int *)(state + 0x2B0) < 4)
        (*(int *)(state + 0x2B0))++;
    func_002A91F0(state + (*(int *)(state + 0x2B4) * 16 + 0x420), (float *)(arg0 + 0xF0));
    qcopy(state + *(int *)(state + 0x2B4) * 16 + 0x320,
          (char *)(*(int *)(state + 0x2A4) + 0x10));
}


/* func_00325B28 is in the -G8 sibling. */

extern char *func_0029EFD0(int);
extern void func_002B37E8(void *, void *);
extern void func_002AF1D0(void *, void *, int, int);
extern void func_002A0F48(void *);

void func_00325B70(char *self, char **children, int first, int second)
{
    int i;
    for (i = 0; i < 2; i++, children++) {
        *children = func_0029EFD0(0xAA2);
        if (*children != 0) {
            func_002B37E8(*children, self);
            *(float *)(*children + 0x2C) *= 0.75f;
            {
                char *child = *children;
                if (i != 0)
                    child[0xBC] = second;
                else
                    child[0xBC] = first;
            }
            *(unsigned short *)(*children + 0x32) = *(unsigned short *)(self + 0x32);
            func_002AF1D0(self, *children, *(unsigned char *)(*children + 0xBC), 0);
            func_002A0F48(*children);
        }
    }
}


/* func_00325D30 and func_00325DA0 are in 0031F210-group-g8.c. */

/* func_00325EC0 is in 0031F210-effects-g8.c. */

/* func_00326198 is in 0031F210-state-g8.c. */

INCLUDE_ASM("asm/game", func_00326A10);




/* negates two floats read from a fixed global table, clamps each to [-1,1] into an object reached through the parameter's +104 pointer, packs the pair into a two-float stack buffer, passes it to two callees and stores the second callee's float return value at object+48 */
void func_00326CB8(char *obj)
{
    float buf[2];
    char *d = D_00189E20_9;
    char *e = *(char **)(obj + 104);
    float a, b, x;

    a = -*(float *)(d + 8112);
    *(float *)(e + 20) = a;
    b = -*(float *)(d + 8116);
    *(float *)(e + 16) = b;

    if (a > 1.0f) {
        *(float *)(e + 20) = 1.0f;
    } else if (a < -1.0f) {
        *(float *)(e + 20) = -1.0f;
    }

    x = *(float *)(e + 16);
    if (x > 1.0f) {
        *(float *)(e + 16) = 1.0f;
    } else if (x < -1.0f) {
        *(float *)(e + 16) = -1.0f;
    }
    func_00282C88_1(buf);
    buf[0] = *(float *)(e + 16);
    buf[1] = *(float *)(e + 20);
    *(float *)(e + 48) = func_00282DF0(buf);
}



/* func_00326EC0 is in 0031F210-basis-g8.c. */
