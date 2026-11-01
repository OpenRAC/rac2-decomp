#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef struct { TI128 position, next, offset, origin; char *owner; int mode; float progress; int hit; } Entry05;
typedef struct { char pad[0x160]; float strength; int unused; int timer, mode; } Camera05;
extern Entry05 D_L05_002659E0[];
extern Camera05 D_L05_001B9580;
extern struct { char pad[0x18]; char *hit; } D_L05_001BFB00;
extern int D_L05_00221D10[];
extern char *func_002ED688(char *object);
extern void func_0029FCC0(char *object, int a1, char *out);
extern void func_00282CC0(void *dst, void *src, char *src2);
extern void func_00282D30(void *dst, void *src, float value);
extern void func_00282CF0(void *dst, void *src, char *src2);
extern void func_00282D08(char *, char *, char *, float);
extern float func_00282E48(char *, char *);
extern int func_002761F8(void *a0, void *a1, int a2, char *a3, int a4);
extern void func_PAL_L05_0037D3D0(float value);

void func_PAL_L05_0041AE80(char *obj)
{
    char a[16] __attribute__((aligned(16)));
    char b[16] __attribute__((aligned(16)));
    int i;
    char *position;
    for (i = 0; i < 128; i++) {
        Entry05 *p = &D_L05_002659E0[i];
        char *state;
        if (p->owner != obj) continue;
        position = (char *)&p->position;
        state = func_002ED688(obj);
        if (D_L05_00221D10[11] == 1 || *(int *)(state + 0x110) == 0) {
            p->owner = 0;
            continue;
        }
        func_0029FCC0(obj, 0, (char *)&p->origin);
        qcopy(a, *(char **)(state + 0x120) + 0x10);
        func_00282CC0(a, (char *)&p->offset, a);
        func_00282D30(b, *(char **)(state + 0x120) + 0xC0, 0.5f);
        func_00282CF0(a, a, b);
        switch (p->mode) {
        case 0: {
            float d;
            qcopy(position, (char *)&p->origin);
            func_00282D08((char *)&p->next, (char *)p, a, p->progress);
            d = func_00282E48((char *)&p->origin, a);
            if (d > 64.0f) d = 64.0f;
            else if (d < 1.0f) d = 1.0f;
            p->progress += 2.0f / d;
            if (p->progress >= 1.0f) {
                p->progress = 1.0f;
                p->mode = 1;
            }
            break;
        }
        case 1:
            qcopy((char *)&p->next, a);
            func_00282D08((char *)p, a, (char *)&p->origin, p->progress);
            p->progress -= 0.25f;
            if (p->progress <= 0.0f) p->owner = 0;
            break;
        }
        if (p->hit == 0 && func_002761F8(p, (char *)&p->next, 4, obj, 0)) {
            char *hit = D_L05_001BFB00.hit;
            if (hit && *(short *)(hit + 0xAA) == 0xFBF) {
                D_L05_001B9580.timer = 25;
                D_L05_001B9580.strength = 0.05f;
                D_L05_001B9580.mode = 0;
                func_PAL_L05_0037D3D0(1.0f);
                p->hit = 1;
            }
        }
    }
}
