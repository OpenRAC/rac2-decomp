#include "common.h"

typedef struct {
    char *object;
    unsigned char rgb[4];
    int unused;
    float fade;
    void (*callback)(char *);
    int rest[3];
} FadeEntry;

extern FadeEntry D_L00_0024EFC0[];
extern int D_L00_001B2B60[] __attribute__((sda));
extern float D_L00_001B065C __attribute__((sda));
extern int D_L00_001B0648[3] __attribute__((sda));
extern char *D_L00_001B0650[] __attribute__((sda));
extern void ref_L00_003E7C88_00(float *, float, float);
extern void func_L00_003E7E40(char *, void *, float);
extern void func_L00_003E80A8(int, char *);
extern void func_002A0488(char *, int, int, int);
extern void func_0029F338(char *);

void func_L00_003E7C88(void) {
    int i;
    i = 0;
    if (i < D_L00_001B2B60[0]) {
        FadeEntry *base = D_L00_0024EFC0;
        FadeEntry *prev = (FadeEntry *)((char *)base - 32);
        float zero = 0.0f;
        do {
            float *fade = (float *)((char *)base + (i * 32 + 12));
            FadeEntry *p = &D_L00_0024EFC0[i];
            char *o = p->object;
            if (*fade != zero) {
                ref_L00_003E7C88_00(fade, 0.0f, D_L00_001B065C * 0.01666666753590107f);
                func_L00_003E7E40(o, D_L00_001B0648, *fade);
                func_L00_003E80A8(i, D_L00_001B0650[0]);
            } else {
                int callbacks = (int)&base->callback;
                void (**callback)(char *) = (void (**)(char *))(i * 32 + callbacks);
                if (*callback) {
                    func_002A0488(o, p->rgb[0], p->rgb[1], p->rgb[2]);
                    *(unsigned char *)(o + 35) = 128;
                    *(unsigned short *)(o + 52) &= ~2;
                    (*callback)(o);
                } else func_0029F338(o);
                {
                    FadeEntry *end = (FadeEntry *)(D_L00_001B2B60[0] * 32 + (int)prev);
                    D_L00_001B2B60[0]--;
                    D_L00_0024EFC0[i] = *end;
                }
            }
            i++;
        } while (i < D_L00_001B2B60[0]);
    }
}
