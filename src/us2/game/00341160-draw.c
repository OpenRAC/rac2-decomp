#include "include_asm.h"

extern int D_00138344[];
extern char *D_001A8CFC[] __attribute__((sda));
extern int func_002A9588(int, int, int, int, int);
extern int *func_00335E20(void *);
extern float *func_00335E18(void *);
extern void func_00336320(void *);
extern void func_US2_003378A0(void *);
extern void func_00335E68(void *, int);
extern void func_00340638(void *);
extern void func_US2_003413A8(void *);
extern void func_0034E2E0(void *, int, int, int);
typedef struct {
    char reserved00[8];
    short adjustment;
    short reserved0A;
    void (*draw)(void *);
} DrawMethod;

void func_US2_00341160(char *self)
{
    char *a, *b, *c, *d, *e, *f, *slot, *slot2;
    int i, j;
    float *v;
    int *color;
    if (*(int *)(self+0xAB8)) {
        if (D_00138344[0]&0xF000) func_002A9588(0,0,1,1,1);
        a=self+0x214; b=self+0x2A8; c=self+0x2F4;
        color=func_00335E20(a);
        f=self+0x5A0;
        *color=func_002A9588(0x60442D00,0x70FFFEED,20,1,0);
        d=self+0x340;
        func_00336320(self);
        slot=self+0x370;
        func_00336320(self+0x4C);
        func_00336320(self+0xE4);
        func_00336320(self+0x130);
        func_US2_003378A0(self+0x828);
        func_US2_003378A0(self+0x8D8);
        func_US2_003378A0(self+0x930);
        func_US2_003378A0(self+0x988);
        func_US2_003378A0(self+0x9E0);
        func_00335E68(self+0x880,0);
        func_00340638(self);
        func_US2_003413A8(self);
        func_00336320(a);func_00336320(b);func_00336320(c);
        v=func_00335E18(b); *v=-*v;
        v=func_00335E18(c); *v=-*v;
        func_00336320(b);func_00336320(c);
        v=func_00335E18(b); *v=-*v;
        v=func_00335E18(c); *v=-*v;
        for(i=7;i>=0;i--,d+=0x4C,slot+=0x4C) {
            DrawMethod *m=*(DrawMethod **)slot;
            m->draw(d+m->adjustment);
        }
        e=self+0x5EC;slot2=self+0x61C;
        for(j=7;j>=0;j--,e+=0x3C,slot2+=0x3C) {
            DrawMethod *m=*(DrawMethod **)slot2;
            m->draw(e+m->adjustment);
        }
        func_00336320(f);
        *func_00335E20(f)=0x80FFDE8D;
        func_0034E2E0(D_001A8CFC[0]+0x36F28,0xF3,0x2B,0x70);
    }
}
