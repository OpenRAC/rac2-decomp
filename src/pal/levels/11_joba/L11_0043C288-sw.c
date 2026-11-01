#include "include_asm.h"

#include "common.h"
extern int D_L11_001B359C __attribute__((sda));
extern char D_L11_001BA8C0[];
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282F20(char *, char *, float);
extern void func_00282CC0(char *, char *, char *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern void func_PAL_L11_0043EBD0(char *, char *);
extern void func_PAL_L11_0043E968(char *, int, int);
extern void func_L11_00439BF0(char *);
extern void func_PAL_L11_004400D0(char *);
extern void func_L11_00438F18(char *);
extern int func_PAL_L11_0043E660(char *);
extern int func_L11_00439D60(char *);
extern void func_L11_00438CD8(char *);
extern void func_PAL_L11_0043E278(char *);
extern void func_L11_00438248(char *);
extern void func_PAL_L11_0043D280(char *);
extern void func_PAL_L02_004009A0(char *, int, int);
extern int func_002B3868(char *);
extern int func_002E5CF8(int, int, char *);
extern void func_002E59F8(int);
extern int func_002E59B0(char *, int);
extern char D_00188660[];
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern void func_002833F0(char *, char *);
extern void func_002A7A00(float *, float, float);
extern void func_PAL_002B15D8(char *, int, float *, float, float, float, float, unsigned char);
typedef struct { char pad[0x330]; int children[10]; char gap[0x28]; unsigned char flags[10]; } ChildSlots;
#define CHILD(o,i) ((char *)(D_L11_001B359C + (((ChildSlots *)(*(char **)((o)+0x68)))->children[i] << 8)))
void func_PAL_L11_0043CB48(char *);

void func_PAL_L11_0043C500(char *obj)
{
    char *s=*(char **)(obj+0x68);
    float target[4], pos[4], direction[4], velocity[4], random[4];
    int i, count;
    char *p;
    func_PAL_L11_0043CB48(obj);
    qcopy(target,s+0x50);
    func_00282E80(obj+0x10,(char *)target);
    { float x=target[0], y=target[1];
      float ox=*(float *)(obj+0x10), oy=*(float *)(obj+0x14);
      x-=ox;
      y-=oy;
      func_00283C80(*(float *)(obj+0xF8),func_00283248(x,y)); }

    switch (*(unsigned char *)(obj+0x95)) {
    case 0: break;
    case 1:
        if (!func_002E59B0(obj,*(int *)(s+0x38C))) *(int *)(s+0x38C)=func_002E5CF8(0,4,obj);
        break;
    }
    switch (*(unsigned char *)(obj+0x20)) {
    case 2:
        if (func_002B3868(obj)) {
            if (*(unsigned char *)(obj+0x43)!=0) func_PAL_002A7E68(obj,0,0,8);
            func_L11_00438F18(obj);
            p=*(char **)(s+0x324);
            qcopy(obj+0x10,p+0x10);
            *(float *)(obj+0xF8)=func_00283248(*(float *)(p+0x20)-*(float *)(obj+0x10),*(float *)(p+0x24)-*(float *)(obj+0x14));
            func_002833F0(obj+0xC0,obj+0xF0);
            func_L11_00438248(obj);
        } else if (func_PAL_L11_0043E660(obj)==1) func_002A7750(obj,3,-1);
        break;
    case 3:
        if (func_002B3868(obj)) {
            if (*(unsigned char *)(obj+0x43)!=0) func_PAL_002A7E68(obj,0,0,8);
            func_L11_00438F18(obj);
        } else if (func_PAL_L11_0043E660(obj)==1)
            func_002A7750(obj,func_L11_00439D60(obj),-1);
        break;
    case 4:
        if (func_002B3868(obj)) {
            if (*(unsigned char *)(obj+0x43)!=0) func_PAL_002A7E68(obj,0,0,8);
            func_L11_00438F18(obj);
        } else {
            if (func_PAL_L11_0043E660(obj)==1) func_002A7750(obj,func_L11_00439D60(obj),-1);
            if (*(unsigned char *)(obj+0x31)) {
                if (*(short *)(s+0x374)==-1) func_L11_00438CD8(obj);
                func_PAL_L11_0043E278(obj);
            }
        }
        break;
    case 5:
        if (func_002B3868(obj)) {
            if (*(unsigned char *)(obj+0x43)!=4) func_PAL_002A7E68(obj,4,0,8);
            if (*(int *)(s+0x38C)!=-1) {
                char *entry=D_00188660+*(int *)(s+0x38C)*0x70;
                if (*(char **)(entry+0x88)==obj && *(unsigned char *)(entry+0x74)) func_002E59F8(*(int *)(s+0x38C));
            }
            *(int *)(s+0x38C)=-1;
        }
        if (*(unsigned char *)(obj+0x60)&2) {
            if (*(unsigned char *)(obj+0x43)!=0) func_PAL_002A7E68(obj,0,0,6);
        }
        if (func_PAL_L11_0043E660(obj)==1) func_002A7750(obj,func_L11_00439D60(obj),-1);
        break;
    case 7: break;
    case 6:
        if (func_002B3868(obj)) {
            *(unsigned short *)(obj+0x96)=0;
            if (*(unsigned char *)(obj+0x43)!=4) func_PAL_002A7E68(obj,4,0,8);
        }
        if (*(unsigned short *)(obj+0x96)>8) {
            func_00282CF0(direction,(float *)D_L11_001BA8C0,(float *)(obj+0x10));
            func_00282F20((char *)direction,(char *)direction,0.6f);
            qcopy(pos,s+0x100);
            func_PAL_L11_0043EBD0(obj,(char *)pos);
            func_002A7A00(random,0.040000003f,0.080000006f);
            func_00282CC0((char *)velocity,(char *)direction,(char *)random);
                count=0;
            func_PAL_002B15D8(obj,1,velocity,3,6,3,6,255);
            for (i=0;i<10;i++) {
                if (!((ChildSlots *)s)->flags[i]) {
                    if (count>=4) {
                        qcopy(pos,s+0x100+i*16);
                        func_002A7A00(random,0.20000002f,0.40000004f);
                        func_00282CC0((char *)velocity,(char *)direction,(char *)random);
                        func_PAL_002B15D8(CHILD(obj,i),3,velocity,3,6,3,6,255);
                        func_PAL_L11_0043EBD0(obj,(char *)pos);
                        func_PAL_L11_004400D0(CHILD(obj,i));
                    } else {
                        char *records=(char *)D_L11_001B359C;
                        (*(short *)(s+0x378))--;
                        count++;
                        func_PAL_L11_0043EBD0(obj,records+(((ChildSlots *)*(char **)(obj+0x68))->children[i]<<8)+0x10);
                        func_PAL_L11_0043E968(obj,i,0);
                    }
                }
            }
            qcopy(pos,s+0x1B0);
            func_002A7A00(random,0.40000004f,0.6f);
            func_00282CC0((char *)velocity,(char *)direction,(char *)random);
            func_PAL_002B15D8((char *)(D_L11_001B359C+(*(int *)(*(char **)(obj+0x68)+0x358)<<8)),7,velocity,3,6,3,6,255);
            func_PAL_L11_0043EBD0(obj,(char *)pos);
            func_PAL_L02_004009A0(obj,0,-1);
            func_L11_00439BF0(obj);
        }
        break;
    }
    func_PAL_L11_0043D280(obj);
}
