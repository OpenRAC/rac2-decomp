/* func_PAL_L01_003C3C80, the PAL copy of func_L01_003BFE48: the same C, where the f7c-f8c tuning
   values rise for 50 Hz (x1.2 for f7c and f80, x36/25 for f84-f8c) and the scale constants change. */
#include "common.h"

typedef struct {
    char pad0[24];
    float f18;
    char pad1c[24];
    unsigned short f34;
    char pad36[134];
    unsigned char fbc;
} L01_003BFE48_OBJ;

typedef struct {
    char pad0[40];
    unsigned char f28;
    unsigned char f29;
    unsigned char f2a;
    char pad2b[3];
    unsigned char f2e;
    char pad2f[1];
    float f30;
    char pad34[12];
    float f40;
    float f44;
    unsigned char f48;
    char pad49[1];
    unsigned char f4a;
    char pad4b[37];
    unsigned char f70;
    unsigned char f71;
    unsigned char f72;
    char pad73[3];
    unsigned char f76;
    unsigned char f77;
    char pad78[4];
    float f7c;
    float f80;
    float f84;
    float f88;
    float f8c;
    float f90;
    float f94;
    char pad98[4];
    float f9c;
    char pada0[8];
    int fa8;
    char padac[32];
    unsigned char fcc;
    unsigned char fcd;
    signed char fce;
    signed char fcf;
    char padd0[2];
    signed char fd2;
    signed char fd3;
    char padd4[3];
    unsigned char fd7;
    char padd8[4];
    int fdc;
    char pade0[80];
    float f130;
    float f134;
    float f138;
    float f13c;
    float f140;
    char pad144[24];
    float f15c;
    float f160;
    char pad164[8];
    int f16c;
    char pad170[336];
    int f2c0;
    int f2c4;
    int f2c8;
    char pad2cc[20];
    unsigned char f2e0;
    unsigned char f2e1;
    unsigned char f2e2;
    char pad2e3[5];
    float f2e8;
    float f2ec;
} L01_003BFE48_STATE;

extern int func_00283CF0(float);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_L01_003377C8(void *);
extern void func_L01_003A6280(void *, void *, int, float, float);
extern void func_002A7750(void *, int, int);
extern void func_L01_003BFDC8(void *, int, int, int);
extern char *D_L01_001FE180[];
extern float D_L01_001AFE50 __attribute__((sda));
extern float D_L01_001AFE5C __attribute__((sda));
extern float D_L01_001AFE74 __attribute__((sda));
extern float D_L01_001AFE78 __attribute__((sda));
extern float D_L01_001AFE7C __attribute__((sda));
extern float D_L01_001AFE80 __attribute__((sda));

void func_PAL_L01_003C3C80(L01_003BFE48_OBJ *obj)
{
    L01_003BFE48_STATE *s = *(L01_003BFE48_STATE **)((char *)obj + 0x68);

    s->fd7 = 1;
    s->f70 = 255;
    s->fa8 = 6;
    s->f71 = 19;
    s->f72 = 19;
    s->f76 = 20;
    s->f77 = 255;
    s->f7c = 0.275f;
    s->f80 = 0.18f;
    s->f84 = 0.019800002f;
    s->f88 = 0.0019f;
    s->f8c = 0.006f;
    s->f90 = 0.5f;
    s->f94 = 0.5f;
    s->f9c = 0.15f;
    s->fcc = 6;
    s->fcd = 25;
    s->fdc = s->f2c0;
    s->fce = -1;
    s->fcf = -1;
    s->fd2 = -1;
    s->fd3 = -1;
    s->f48 = func_00283CF0(40.0f);
    s->f4a = func_00283CF0(28.0f);
    s->f2a = 48;
    s->f28 = 4;
    s->f29 = 1;
    s->f2e = 1;
    s->f40 = 6.0f;
    s->f44 = 3.3f;
    s->f30 = 2.0f;
    obj->f34 |= 0x1000;
    s->f16c = s->f2c4;
    s->f130 = 4.0f;
    s->f134 = 0.35f;
    s->f138 = 0.1f;
    s->f13c = 0.1f;
    s->f140 = 0.3490659f;
    s->f160 = 0.52359885f;
    s->f15c = D_L01_001AFE50 * 0.00040000002f;
    func_002B60B0(obj, D_L01_001AFE74 * 0.00040000002f,
                 D_L01_001AFE80 * 0.020000001f,
                 D_L01_001AFE78 * 6.981318e-06f,
                 D_L01_001AFE7C * 0.0003490659f);
    s->f28 = 3;
    obj->fbc = 0;
    if (s->f2c8 != -1) {
        func_L01_003377C8(D_L01_001FE180[s->f2c8]);
    }
    if (s->f2c4 != -1) {
        func_L01_003377C8(D_L01_001FE180[s->f2c4]);
    }
    if (s->f2c0 != -1) {
        func_L01_003377C8(D_L01_001FE180[s->f2c0]);
    }
    func_L01_003A6280(obj, (char *)obj + 0x10, 11, 1.2f, 2.0f);
    s->f2e1 = 1;
    s->f2e0 = 0;
    s->f2e2 = 0;
    s->f2e8 = obj->f18;
    s->f2ec = D_L01_001AFE5C;
    func_002A7750(obj, 0, 1);
    func_L01_003BFDC8(obj, 0, 0, 2);
}
