#include "include_asm.h"

extern int func_US2_0033FAB0(char *, int);
extern char D_001ADC88[];
extern char *func_00288FB8(int);
extern void func_00336A38(void *, void *);
extern int func_00336E40(void *);
extern int *func_00336DA8(int, int);
extern void func_US2_0033BC20(void *, void *, void *);
extern void func_US2_003377B0(void *, void *, void *);
extern void func_003361E0(void *, void *, void *);
extern void func_00335F88(void *, float, float, float, float);
extern void func_00336A30(void *, int);
extern unsigned int *func_00335E20(void *);
extern void func_00336710(void *, void *, void *);
extern void func_00336920(void *, int, int);
extern void func_00336390(void *, void *, int);
extern int D_001ADF00[2] __attribute__((sda));
extern char *D_001A8CFC;
extern char D_001ADF08[], D_001ADF10[], D_001ADF18[], D_001ADF20[];

void func_US2_0033F720(char *object, void *owner)
{
    int *allocation;
    char *a;
    char *b;
    char *c;
    char *d;
    char *e;
    char *f;
    char *g;
    char *h;
    char *i;
    char *j;
    char *k;
    char *table;
    unsigned int color;
    *(void **)object = owner;
    if (owner) {
        allocation = func_00336DA8(16, func_00336E40(owner));
        *(int **)(object + 0x2D8) = allocation;
        allocation[1] = 0;
        allocation[2] = 0;
        allocation[3] = 0;
        allocation[0] = 0;
    }
    (*(float **)(object + 0x2D8))[0] = 255.0f;
    (*(float **)(object + 0x2D8))[1] = 200.0f;
    a = object + 0x318;
    b = object + 0x370;
    c = object + 0x3C8;
    d = object + 0x628;
    e = object + 0x5D0;
    f = object + 0x420;
    g = object + 0x578;
    h = object + 0x2DC;
    color = 0x80F0F0F0;
    func_US2_0033BC20(object + 8, owner, D_001ADF00);
    table = D_001ADC88;
    func_US2_003377B0(a, table, owner);
    func_US2_003377B0(b, table, owner);
    i = object + 0x470;
    j = object + 0x4C8;
    func_US2_003377B0(c, table, owner);
    k = object + 0x520;
    func_US2_003377B0(d, table, owner);
    func_US2_003377B0(e, table, owner);
    func_003361E0(f, table, owner);
    func_US2_003377B0(g, table, owner);
    func_00336A38(e, object + 0x680);
    func_00336A38(g, func_00288FB8(0x333E));
    func_00335F88(g, 0.9f, 0.9f, 0.0f, 0.0f);
    func_00336A38(a, func_00288FB8(0x2BE5));
    func_00336A38(b, func_00288FB8(0x3129));
    func_00336A38(c, func_00288FB8(0x2C67));
    func_00336A30(a, 0);
    func_00336A30(b, 0);
    func_00336A30(c, 0);
    *func_00335E20(a) = color;
    *func_00335E20(b) = color;
    *func_00335E20(c) = color;
    *func_00335E20(d) = color;
    *func_00335E20(e) = color;
    *func_00335E20(g) = color;
    *func_00335E20(f) = 0x55F0C070;
    func_00336710(h, table, owner);
    func_00336920(h, 0xEAA2, 0);
    func_00335F88(h, 32.0f, 32.0f, 0.0f, 0.0f);
    *func_00335E20(h) = 0x60F0F0B0;
    func_00336390(f, D_001A8CFC + 0x8710, 0x5D);
    func_US2_003377B0(i, D_001ADF10, *(void **)object);
    func_US2_003377B0(j, D_001ADF18, *(void **)object);
    func_US2_003377B0(k, D_001ADF20, *(void **)object);
    *func_00335E20(i) = color;
    *func_00335E20(j) = color;
    *func_00335E20(k) = color;
    func_00336A38(i, object + 0x6C0);
    func_00336A38(j, object + 0x6D8);
    func_00336A38(k, object + 0x6F0);
    func_US2_0033FAB0(object, 0);
}

extern void func_US2_0033BE70(void *);
extern void func_0033B018(void *, float, float);
extern void func_00335E38(void *, float, float, float, float);
extern char *func_002DF1F8(char *, int);
extern void func_US2_0033FCE8(void *);
extern void func_US2_002D7BA0(int);
extern char D_001C4FA0[], D_001ADC88[];
extern int D_00258D70[];
extern float D_001ADF28 __attribute__((sda));
extern float D_001ADF2C[] __attribute__((sda));
extern float D_001ADF30 __attribute__((sda));
extern float D_001ADF34[] __attribute__((sda));
extern float D_001ADF38 __attribute__((sda));
extern float D_001ADF3C[] __attribute__((sda));
extern float D_001ADF40 __attribute__((sda));
extern float D_001ADF44[] __attribute__((sda));
extern float D_001ADF48 __attribute__((sda));
extern float D_001ADF4C[] __attribute__((sda));
extern float D_001ADF50 __attribute__((sda));
extern float D_001ADF54[] __attribute__((sda));
extern float D_001ADF58 __attribute__((sda));
extern float D_001ADF5C[] __attribute__((sda));

int func_US2_0033FAB0(char *object, int flags)
{
    char *child = object + 8;
    char *label = object + 0x628;
    char *state;
    int text;
    float x, y;

    func_US2_0033BE70(child);
    func_0033B018(child, (*(float **)(object + 0x2D8))[0], (*(float **)(object + 0x2D8))[1]);
    x = D_001ADF28 + (*(float **)(object + 0x2D8))[0];
    y = D_001ADF2C[0] + (*(float **)(object + 0x2D8))[1];
    func_00335E38(object + 0x318, x, y, 0.0f, 0.0f);
    x = D_001ADF30 + (*(float **)(object + 0x2D8))[0];
    y = D_001ADF34[0] + (*(float **)(object + 0x2D8))[1];
    func_00335E38(object + 0x370, x, y, 0.0f, 0.0f);
    x = D_001ADF38 + (*(float **)(object + 0x2D8))[0];
    y = D_001ADF3C[0] + (*(float **)(object + 0x2D8))[1];
    func_00335E38(object + 0x3C8, x, y, 0.0f, 0.0f);
    x = D_001ADF50 + (*(float **)(object + 0x2D8))[0];
    y = D_001ADF54[0] + (*(float **)(object + 0x2D8))[1];
    func_00335E38(object + 0x2DC, x, y, 0.0f, 0.0f);
    x = D_001ADF58 + (*(float **)(object + 0x2D8))[0];
    y = D_001ADF5C[0] + (*(float **)(object + 0x2D8))[1];
    func_00335E38(object + 0x420, x, y, 0.0f, 0.0f);
    x = D_001ADF48 + (*(float **)(object + 0x2D8))[0];
    y = D_001ADF4C[0] + (*(float **)(object + 0x2D8))[1];
    func_00335E38(label, x, y, 0.0f, 0.0f);
    x = D_001ADF40 + (*(float **)(object + 0x2D8))[0];
    y = D_001ADF44[0] + (*(float **)(object + 0x2D8))[1];
    func_00335E38(object + 0x5D0, x, y, 0.0f, 0.0f);
    state = D_001C4FA0;
    func_002DF1F8(object + 0x680, *(int *)(state + 0x230));
    text = D_00258D70[*(int *)(state + 0x230) * 2 + 1];
    if (text >= 0)
        func_00336A38(label, func_00288FB8(text));
    else
        func_00336A38(label, D_001ADC88);
    func_US2_0033FCE8(object);
    func_US2_002D7BA0(0);
    return (flags >> 6) & 1;
}
