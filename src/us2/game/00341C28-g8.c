#include "include_asm.h"

extern void func_003361E0(void *, void *, void *);
extern unsigned int *func_00335E20(void *);
extern void func_00336390(void *, void *, int);
extern int func_00336E40(void *);
extern int *func_00336DA8(int, int);
extern void func_US2_003377B0(void *, void *, void *);
extern void func_00335E68(void *, int);
extern void func_00336710(void *, void *, void *);
extern void func_00335F88(void *, float, float, float, float);
extern void func_00336A38(void *, void *);
extern void func_00336408(void *, int, int, void *, void *);
extern void func_00336CC8(void *, int);
extern void func_US2_00337A38(void *, int);
extern void func_00336B98(void *, int);
extern void func_00336498(void *, unsigned int, unsigned int);
extern void func_003364B0(void *, unsigned int, unsigned int);
extern void func_00336CE0(void *, unsigned int);
extern void func_00336CC0(void *, int);
extern char D_001ADFA0[], D_001ADFC0[], D_001ADFC8[], D_001AE030[], D_001ADFD8[], D_001AE040[];
extern char *D_001A8CFC[] __attribute__((sda));
int func_US2_00341F40(char *, unsigned int, void *);

void func_US2_00341C78(char *self, void *parent)
{
    char *a=self+0xF0, *b, *c, *d, *e;
    int *v;
    func_003361E0(a,D_001ADFA0,parent);
    *func_00335E20(a)=0x60241700;
    func_00336390(a,D_001A8CFC[0]+0x8710,0x29);
    *(void **)(self+0x1C4)=parent;
    if(parent) {
    v=func_00336DA8(16,func_00336E40(parent));
    *(int **)(self+0x1C0)=v;
    v[1]=0; v[2]=0; v[3]=0; v[0]=0;
    }
    *(int *)(self+0x210)=1;
    **(float **)(self+0x1C0)=0.0f;
    (*(float **)(self+0x1C0))[1]=0.0f;
    b=self+0x4C; c=self+0x98; d=self+0x184; e=self+0x13C;
    func_003361E0(self,D_001ADFC0,parent);
    func_003361E0(b,D_001ADFC8,parent);
    func_US2_003377B0(c,D_001AE030,parent);
    *func_00335E20(self)=0x55F0C070;
    *func_00335E20(b)=0x70FFFEED;
    func_00336390(self,D_001A8CFC[0]+0x8710,0x5D);
    func_00336390(b,D_001A8CFC[0]+0x8710,0x5E);
    func_00335E68(b,0);
    *(int *)(self+0x214)=0;
    *(int *)(self+0x218)=0;
    func_00336710(d,D_001ADFD8,parent);
    *func_00335E20(d)=0x60F0F0B0;
    func_00335F88(d,32.0f,32.0f,0.0f,0.0f);
    *func_00335E20(c)=0x80F0F0F0;
    self[0x1D0]=0;
    func_00336A38(c,self+0x1D0);
    *(float *)(self+0x1C8)=0.0f;
    *(float *)(self+0x1CC)=0.0f;
    *(int *)(self+0x224)=0;
    func_00336408(e,32,0,D_001AE040,parent);
    func_00336CC8(e,5);
    func_US2_00337A38(e,100);
    func_00336B98(e,0);
    func_00336498(e,0x6049C1FF,0x60001EFF);
    func_003364B0(e,0x50F0C070,0x50F0C070);
    func_00336CE0(e,0x80000000);
    func_00336CC0(e,0);
    *(int *)(self+0x21C)=4;
    *(int *)(self+0x220)=6;
    func_US2_00341F40(self,0,0);
}
