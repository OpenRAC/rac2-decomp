#include "common.h"
extern void func_0029F338(void *);
extern int func_L00_00324120(void *);
extern int func_002ACBC8(void *,int);
extern int func_L13_002CEF00(int,int);
extern void func_002ACEC0(void *,void *,void *,float);
extern float func_00282E80(void *,void *);
extern struct { char pad[0x348]; short state; } D_00189E20;
extern char D_00189EA0[];
void func_L13_003FE420(char *obj) {
    char *rec=*(char **)(obj+0x68);
    if (!rec) { func_0029F338(obj); return; }
    switch (*(u8 *)(obj+0x20)) {
    case 0:
        *(int *)(rec+0xC)=0;
        *(int *)(rec+4)=0;
        *(u16 *)(obj+0x34)|=0x100;
        if (*(int *)rec) *(u8 *)(obj+0x20)=1;
        else *(u8 *)(obj+0x20)=4;
        break;
    case 1:
        if (func_L00_00324120(obj)) {
            if (D_00189E20.state==1 && IsPointInCuboid((char *)&D_00189E20+0x80,*(int *)(rec+8))) {
                *(u16 *)(obj+0x96)=0;
                func_L13_002CEF00(0x6F,1);
                *(u8 *)(obj+0x20)=2;
            }
            if (*(int *)(rec+8)!=-1 || !*(char **)(rec+0xC)) break;
            if (*(u8 *)(*(char **)(rec+0xC)+0x20)==0xFE) goto opened;
            if (*(u8 *)(*(char **)(rec+0xC)+0x20)!=0xFD) break;
opened:
            if (D_00189E20.state==1) {
                *(u16 *)(obj+0x96)=0;
                *(u8 *)(obj+0x20)=2;
            }
        } else *(u16 *)(obj+0x96)=0;
        break;
    case 2:
        if (*(u16 *)(obj+0x96)<91) {
            func_002ACEC0(obj+0xC0,obj+0xC0,obj+0xD0,0.017453294f);
            func_002ACEC0(obj+0xE0,obj+0xE0,obj+0xD0,0.017453294f);
            (*(u16 *)(obj+0x96))++;
        } else {
            func_L13_002CEF00(0,1);
            *(u8 *)(obj+0x20)=7;
        }
        break;
    case 3:
        if (*(u16 *)(obj+0x96)<91 && *(int *)(rec+4)==0) {
            func_002ACEC0(obj+0xC0,obj+0xC0,obj+0xD0,-0.034906588f);
            func_002ACEC0(obj+0xE0,obj+0xE0,obj+0xD0,-0.034906588f);
            *(u16 *)(obj+0x96)+=2;
        }
        if (*(u16 *)(obj+0x96)>=91 || *(int *)(rec+4)) {
            *(int *)(rec+4)=1;
            *(u8 *)(obj+0x20)=1;
            *(u16 *)(obj+0x96)=0;
        }
        break;
    case 5:
        func_002ACEC0(obj+0xC0,obj+0xC0,obj+0xD0,-0.017453294f);
        func_002ACEC0(obj+0xE0,obj+0xE0,obj+0xD0,-0.017453294f);
        if (--*(u16 *)(obj+0x96)==0) {
            *(u16 *)(obj+0x96)=0;
            *(u8 *)(obj+0x20)=1;
        }
        break;
    case 7:
        if (vec_distance_xy(obj+0x10,D_00189EA0)<4.0f) *(short *)(D_00189EA0+0x194)=2;
        else *(short *)(D_00189EA0+0x194)=0;
    case 6:
        if (D_00189E20.state!=1) *(u8 *)(obj+0x20)=5;
        break;
    }
}
