#include "common.h"
extern void func_0029FCC0(void *,int,void *);
extern void func_002AF1D0(void *,void *,int,int);
extern void func_002A05A8(void *);
extern void func_002A0F48(void *);
extern void func_002833F0(void *,void *);
extern void func_002A10E8(void *);
extern void func_L18_00433460(void *);
extern void func_L18_00433B70(void *);
extern void func_L18_00432F18(void *);
extern void func_L18_00434FC0(void *);
extern void func_L00_002E6EF8(void (*)(void *),void *);
extern int func_002A77E0(int);
extern int func_002A7820(int,int);
extern void func_L18_004350E0(void *,int);
extern float func_00282E48(void *,void *);
extern float D_L18_001B97C0[];
extern void func_002A93B0(void *);
extern void func_002B0990(void *,float *,float,int,int);

void func_L18_00432310(unsigned char *object)
{
    float position[4] __attribute__((aligned(16)));
    unsigned char *state=*(unsigned char **)(object+0x68);
    if(*(unsigned short *)(object+0x96)<0xFFFF)
        ++*(unsigned short *)(object+0x96);
    if(*(short *)(state+0x804)<0x7FFF)
        ++*(unsigned short *)(state+0x804);
    if(*(void **)(state+0x7C0)) {
        func_0029FCC0(object,0,position);
        {
            unsigned char *child=*(unsigned char **)(state+0x7C0);
            qcopy(child+0x10,position);
            *(float *)(child+0x48)=*(float *)(object+0x48);
        }
        if(*(void **)(state+0x7C8))
            func_002AF1D0(*(void **)(state+0x7C0),*(void **)(state+0x7C8),2,0);
        if(*(void **)(state+0x7C4)) {
            *(float *)(*(unsigned char **)(state+0x7C4)+0x48)=*(float *)(object+0x48);
            func_0029FCC0(*(void **)(state+0x7C0),0,position);
            {
                unsigned char *child=*(unsigned char **)(state+0x7C4);
                qcopy(child+0x10,position);
                qcopy(child+0xF0,*(unsigned char **)(state+0x7C0)+0xF0);
                func_002A05A8(child);
            }
            func_002A0F48(*(void **)(state+0x7C4));
            {
                unsigned char *child=*(unsigned char **)(state+0x7C4);
                func_002833F0(child+0xC0,child+0xF0);
            }
            func_002A10E8(*(void **)(state+0x7C4));
        }
    }
    if(object && object[0x20]!=0xFE && object[0x20]!=0xFD && object[0x20]>=2) {
        if(*(short *)(state+0x7FC)==0 && *(void **)(state+0x7C8)) {
            func_L18_00433460(object);
            func_L00_002E6EF8(func_L18_00433B70,object);
        }
        if(object[0x31])
            func_L00_002E6EF8(func_L18_00432F18,object);
        if(!*(void **)(state+0x7C0)) {
            func_0029FCC0(object,0,position);
            if(func_002A77E0(20)==0)
                func_L18_004350E0(position,func_002A7820(10,15));
            func_L00_002E6EF8(func_L18_00434FC0,object);
        }
    }
    if(object[0x31] && func_00282E48(object+0x10,D_L18_001B97C0)<24.0f) {
        func_002A93B0(object);
        object[0x6F]=22;
    }
    {
        void *child=*(void **)(state+0x7C4);
        *(short *)(state+0x808)=0;
        if(child)
            func_002B0990(child,(float *)(state+0x810),2.5f,5,1);
    }
}
