#include "include_asm.h"

typedef struct { int ids[2]; } SolTextPair;
extern SolTextPair D_L00_001AE110;
extern char D_L00_001AE118[];
extern void func_PAL_0033CE70(void *);
extern char *func_00288FB8(int);
extern int func_00115DA8(char *, const char *, ...);
extern void func_0027FAA8(int, int, unsigned long, char *, int);

void func_PAL_0033E248(char *object)
{
    char buffer[128];
    SolTextPair pair;
    char *first;
    char *second;
    char *format;
    func_PAL_0033CE70(object + 8);
    pair = D_L00_001AE110;
    format = D_L00_001AE118;
    first = func_00288FB8(0x10FC);
    second = func_00288FB8(pair.ids[*(unsigned char *)0x1A7C39 != 0]);
    func_00115DA8(buffer, format, first, second);
    func_0027FAA8(0x100, 0xAA, 0x80F0F0F0UL, buffer, -1);
}

void func_PAL_0033FBE0(char *object)
{
    char buffer[128];
    SolTextPair pair;
    char *first;
    char *second;
    char *format;
    func_PAL_0033CE70(object + 8);
    pair = D_L00_001AE110;
    format = D_L00_001AE118;
    first = func_00288FB8(0xBAB);
    second = func_00288FB8(pair.ids[*(unsigned char *)0x1A7C3A != 0]);
    func_00115DA8(buffer, format, first, second);
    func_0027FAA8(0x100, 0xAA, 0x80F0F0F0UL, buffer, -1);
}

extern void *func_PAL_0033CA78(void *);
extern void *func_00347EA0(void *);

void *func_PAL_00340118(char *object) {
    func_PAL_0033CA78(object + 0x8);
    func_00347EA0(object + 0x2E0);
    return object;
}

extern void *func_00336968(void *);

void *func_PAL_00340470(char *object) {
    func_PAL_0033CA78(object + 0x8);
    func_00336968(object + 0x2E0);
    return object;
}

void func_PAL_00340310(unsigned char *owner, float *records)
{
    extern void func_PAL_0034A230(unsigned char *, float *);
    func_PAL_0034A230(owner + 0x2E0, records);
    *(float **)(owner + 0x3B8) = records;
}

extern void func_PAL_0033CD50(char *);
extern void func_0033B018(char *, float, float);
extern void func_PAL_0033CD50(char *p);
extern void func_0033B018(char *p, float x, float y);

int func_PAL_003405B0(char *object, int flags)
{
    char *p = object + 8;
    float *v;
    func_PAL_0033CD50(p);
    v = *(float **)(object + 0x2D8);
    func_0033B018(p, v[0], v[1]);
    return (flags >> 6) & 1;
}

#include "common.h"
typedef struct { char pad[8]; short n; void (*fn)(char *); } ENTRY_F624a0727;
typedef struct {
    int x;
    int y;
    int text;
    float scale;
} Row_0033B910;
extern void func_00336320(char *);
extern void func_PAL_00338770(char *);
extern void func_00336828(char *);
extern void func_00335E38(void *, float, float, float, float);
extern void func_00336920(char *, int, int);
extern void func_00335F88(void *, float, float, float, float);
extern int *func_00335E20(char *);
extern float *func_00335E10(char *);
extern void func_0028FAB8(int, int, int, int, unsigned long long, int);
extern Row_0033B910 D_00265140[];
extern unsigned char D_001A7BC8[] MACRO_ADDR;
extern unsigned char D_001A7BE8[] MACRO_ADDR;
extern char D_001C4FA0[];
static __inline__ void SetColor_0033B910(char *w, int c)
{
    *func_00335E20(w) = c;
}

void func_PAL_0033D838(char *obj)
{
    int i;
    char *base;

    func_00336320(obj);
    func_00336320(obj + 0x4C);
    func_00336320(obj + 0x98);
    func_PAL_00338770(obj + 0x1D8);
    func_PAL_00338770(obj + 0x230);
    func_PAL_00338770(obj + 0x288);
    func_00336828(obj + 0x2E0);
    for (i = 0; i < 21; i++) {
        func_00335E38(obj + 0x31C, (float)D_00265140[i].x + (*(float **)(obj + 0x1C8))[0],
                      (float)D_00265140[i].y + (*(float **)(obj + 0x1C8))[1], 0.0f, 0.0f);
        func_00336920(obj + 0x31C, 0xE99E, D_00265140[i].text);
        func_00335F88(obj + 0x31C, D_00265140[i].scale, D_00265140[i].scale, 0.0f, 0.0f);
        if (D_001A7BE8[i] == 0)
            SetColor_0033B910(obj + 0x31C, 0x70A0C0C0);
        else
            SetColor_0033B910(obj + 0x31C, 0x7029A1FF);
        if (D_001A7BC8[i] != 0)
            func_00336828(obj + 0x31C);
    }
    base = D_001C4FA0;
    if (*(int *)(base + 0x230) < 21) {
        char *first = obj + 0xE4;
        char *mid = obj + 0x130;
        char *bar = obj + 0x17C;
        char *q = obj + 0x114;
        char *r = first;
        int k;

        for (k = 2; k >= 0; k--) {
            ENTRY_F624a0727 *t = *(ENTRY_F624a0727 **)q;
            t->fn(r + t->n);
            r += 76;
            q += 76;
        }
        func_0028FAB8((int)(func_00335E10(first)[0] + 1.0f),
                      (int)(func_00335E10(mid)[1] + 6.0f),
                      (int)(func_00335E10(first)[0] + 1.0f),
                      (int)(func_00335E10(first)[1] - 4.0f), 0x180000FF, 0);
        func_0028FAB8((int)(func_00335E10(bar)[0] + 8.0f),
                      (int)(func_00335E10(bar)[1] + 2.0f),
                      (int)(func_00335E10(bar)[0] + 304.0f),
                      (int)(func_00335E10(bar)[1] + 2.0f), 0x180000FF, 0);
        func_0028FAB8((int)(func_00335E10(first)[0] + 1.0f),
                      (int)(func_00335E10(mid)[1] + 6.0f),
                      (int)(func_00335E10(first)[0] + 1.0f),
                      (int)(func_00335E10(first)[1] - 4.0f), 0x180000FF, 0);
        func_0028FAB8((int)(func_00335E10(bar)[0] + 8.0f),
                      (int)(func_00335E10(bar)[1] + 2.0f),
                      (int)(func_00335E10(bar)[0] + 304.0f),
                      (int)(func_00335E10(bar)[1] + 2.0f), 0x180000FF, 0);
    }
}
