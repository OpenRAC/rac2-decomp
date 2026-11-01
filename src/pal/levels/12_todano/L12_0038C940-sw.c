#include "include_asm.h"

#include "common.h"
extern void func_PAL_002AC718(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern int func_00277258(void *,int,void *,float);
extern void func_00283028(void *,void *,void *);
extern int func_00282948(void *);
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
extern Collision D_L12_001C0240;
extern float func_00283B98(float,float);
extern void func_0029F338(void *);

/* Mirrors its linked object, then moves and destroys the detached fragment. */
void func_PAL_L12_003A4158(u8 *object) {
    u8 *data=*(u8 **)(object+0x68);u8 *tracked=*(u8 **)(data+0x3C);
    if(tracked && *(short *)(tracked+0xAA)==0x184 && tracked[0x20]!=254 && tracked[0x20]!=253) {
        *(u16 *)(object+0x34)&=0xFFFC;
        *(u16 *)(object+0x34)|=*(u16 *)(*(u8 **)(data+0x3C)+0x34)&3;
        switch(object[0x20]) {
        case 0: object[0x20]=1; qzero_nc(data+0x20);break;
        case 1:
            tracked=*(u8 **)(data+0x3C);
            *(float *)(object+0x2C)=*(float *)(*(u8 **)(object+0x24)+0x24)**(float *)(tracked+0x2C) / *(float *)(*(u8 **)(tracked+0x24)+0x24);
            *(u64 *)(object+0x38)=*(u64 *)(*(u8 **)(data+0x3C)+0x38);break;
        case 2: return;
        default: break;
        case 3:
            func_00282CC0(object+0x10,object+0x10,data+0x10);
            func_00282D30(data+0x10,data+0x10,0.995f);
            if(func_00277258(object+0x10,0,object,2.0f)) {
                u8 *hit=D_L12_001C0240.hit;
                if(hit) {
                    int type=*(short *)(hit+0xAA);
                    if(type==0x191 || type==0x184 || type==0x185 || type==0x186 || type==0x187 || type==0x188 || type==0x189 || type==0x18A || type==0x18B || type==0x18C || type==0x18F || type==0x190) goto rotate;
                }
                func_00283028(data+0x10,data+0x10,D_L12_001C0240.normal.f);object[0x20]=4;
            }
rotate:
            *(float *)(object+0xF0)=func_00283B98(*(float *)(object+0xF0),*(float *)(data+0x30));
            *(float *)(object+0xF4)=func_00283B98(*(float *)(object+0xF4),*(float *)(data+0x34));
            *(float *)(object+0xF8)=func_00283B98(*(float *)(object+0xF8),*(float *)(data+0x38));
            *(float *)(data+0x30)*=0.999f;*(float *)(data+0x34)*=0.999f;*(float *)(data+0x38)*=0.999f;
            if(*(float *)(object+0x10)<10 || *(float *)(object+0x10)>1013 || *(float *)(object+0x14)<10 || *(float *)(object+0x14)>1013 || *(float *)(object+0x18)<10 || *(float *)(object+0x18)>1013 || (func_00282948(data+0x40) && !object[0x31])) {
destroy:
                func_0029F338(object);
            }
            break;
        case 4:
            func_PAL_002AC718(object,data+0x10,0,2,4,10,3,16,4,2,9,1,-1,15,1,1,-1,0,0x810001);
            func_0029F338(object);break;
        }
    } else goto destroy;
}
