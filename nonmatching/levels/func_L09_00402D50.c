/* Retained C, 30 October 2026; not matching and no exact-C credit.
 * Profile: game -O2 -G8 -ffunction-sections. US: 820/816 bytes, 0/1.
 * Corrected func_002B60B0 to its verified pointer return, with one object
 * pointer and four FP arguments. The typed-state prefix still agrees for
 * 244 bytes; byte/int constants at +0xC6/+0x98 materialize separate ones,
 * and initializer stores/constants are reordered. Chained initialization
 * ties the previous source. No linked-build claim for this candidate.
 * Next: an independently measured initializer field/lifetime witness.
 */
#include "common.h"
extern float D_L09_001B13BC SDATA(D_L09_001B13BC);
extern unsigned char *D_L09_001FE6C0[];
extern float func_002A89A8(void *, int, float);
extern float func_002A78D8(float, float);
extern int func_00283CF0(float);
extern void *func_002B60B0(void *, float, float, float, float);
extern void func_002A7750(void *, int, int);
extern void func_002A7470(void *, int, int, int);
struct DobboState {
    char pad0[0x28];
    unsigned char mode;
    char pad29[0x7];
    int timer;
    char pad34[0x14];
    unsigned char turn;
    char pad49[0x1];
    unsigned char speed;
    char pad4b[0x15];
    unsigned char count;
    unsigned char f61;
    unsigned char f62;
    char pad63[0x3];
    unsigned char f66;
    unsigned char f67;
    char pad68[0x4];
    float f6c;
    float f70;
    float f74;
    float f78;
    float f7c;
    float f80;
    float f84;
    char pad88[0x4];
    float f8c;
    char pad90[0x8];
    int i98;
    char pad9c[0x20];
    signed char bbc;
    signed char bbd;
    signed char bbe;
    signed char bbf;
    char padc0[0x2];
    signed char bc2;
    signed char bc3;
    char padc4[0x2];
    signed char bc6;
    char padc7[0x39];
    float f100;
    float f104;
    float f108;
    float f10c;
    float f110;
    char pad114[0x18];
    float f12c;
    float f130;
    char pad134[0x4];
    int i138;
    int i13c;
    char pad140[0x9c];
    float f1dc;
    char pad1e0[0x2];
    short h1e2;
    short h1e4;
    char pad1e6[0xa];
    float position[4];
    float f200;
    char pad204[0x8];
    float f20c;
    float f210;
    char pad214[0x2c];
    int i240;
    char pad244[0xc];
    int i250;
    int i254;
    int i258;
    char pad25c[0x4];
    float f260;
    float f264;
    char pad268[0xc];
    short h274;
    char pad276[0x12];
    float f288;
    int i28c;
    char pad290[0x4];
    float f294;
};
void func_L09_00402D50(unsigned char *m)
{
    struct DobboState *p = *(struct DobboState **)(m + 0x68);
    float height = func_002A89A8(m + 0x10, 0, 0.5f);
    p->f288 = height;
    p->f294 = height + D_L09_001B13BC;
    if (p->f294 < p->f264) p->f294 = p->f264;
    p->h274 = -1;
    if (p->f260 == -1.0f) p->f260 = 0.01745329424738884f * func_002A78D8(25.0f, 100.0f);
    else p->f260 *= 0.01745329424738884f;
    p->turn = func_00283CF0(15.0f);
    p->speed = func_00283CF0(2.4f);
    p->count = 9;
    p->f61 = 0;
    p->f62 = 0;
    p->f66 = 0;
    p->f67 = 0;
    p->f6c = 0.10000000894069672f;
    p->f70 = 0.06666667014360428f;
    p->f78 = 0.008333333767950535f;
    p->f7c = 0.004166666883975267f;
    p->f80 = 0.5f;
    p->f84 = D_L09_001B13BC;
    p->f8c = 0.4000000059604645f;
    p->bc3 = -1;
    p->i98 = p->bc6 = 1;
    p->f100 = 1.0f;
    p->f104 = 1.100000023841858f;
    p->f10c = 2.799999952316284f;
    p->f110 = 3.1415927410125732f;
    p->f130 = 25.13274383544922f;
    p->f12c = 0.000777777808252722f;
    p->f74 = 0.004166666883975267f;
    p->bbc = -1;
    p->bbd = -1;
    p->bbe = -1;
    p->bbf = -1;
    p->bc2 = -1;
    p->f108 = 2.8f;
    if (p->i258 != -1) p->i13c = p->i258;
    else p->i13c = p->i254;
    p->f1dc = p->f260 * 0.01745329424738884f;
    p->h1e4 = 240;
    p->h1e2 = 120;
    p->i138 |= 0x10;
    func_002B60B0(m, 0.006666666828095913f, 0.06666667014360428f, 0.8377581834793091f, 0.8377581834793091f);
    qcopy(p->position, m + 0x10);
    p->f200 = 1.0f;
    p->f20c = 5.0f;
    p->f210 = 10.0f;
    p->mode = 3;
    p->i28c = p->i240;
    p->timer = 0;
    if (p->i250 != -1) {
        qcopy(m + 0x10, D_L09_001FE6C0[p->i250] + 0x10);
        func_002A7750(m, 1, 0);
    } else func_002A7750(m, 2, 2);
    if (m[0x43]) func_002A7470(m, 0, 0, 1);
}
