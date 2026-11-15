#include "common.h"
extern void SpawnExplosionEffects(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern int coll_test_point(void *,int,void *,float);
extern void vec_fast_normalize(void *,void *,void *);
extern int math_fast_float_d(void *);
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
extern Collision D_L12_001C0240;
extern float FastAddRotations(float,float);
extern void moby_mark_spawned(void *);

/* Mirrors its linked object, then moves and destroys the detached fragment. */
void mirrored_fragment_update(u8 *object) {
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
            FastVecAdd(object+0x10,object+0x10,data+0x10);
            FastVecScale(data+0x10,data+0x10,0.995f);
            if(coll_test_point(object+0x10,0,object,2.0f)) {
                u8 *hit=D_L12_001C0240.hit;
                if(hit) {
                    int type=*(short *)(hit+0xAA);
                    if(type==0x191 || type==0x184 || type==0x185 || type==0x186 || type==0x187 || type==0x188 || type==0x189 || type==0x18A || type==0x18B || type==0x18C || type==0x18F || type==0x190) goto rotate;
                }
                vec_fast_normalize(data+0x10,data+0x10,D_L12_001C0240.normal.f);object[0x20]=4;
            }
rotate:
            *(float *)(object+0xF0)=FastAddRotations(*(float *)(object+0xF0),*(float *)(data+0x30));
            *(float *)(object+0xF4)=FastAddRotations(*(float *)(object+0xF4),*(float *)(data+0x34));
            *(float *)(object+0xF8)=FastAddRotations(*(float *)(object+0xF8),*(float *)(data+0x38));
            *(float *)(data+0x30)*=0.999f;*(float *)(data+0x34)*=0.999f;*(float *)(data+0x38)*=0.999f;
            if(*(float *)(object+0x10)<10 || *(float *)(object+0x10)>1013 || *(float *)(object+0x14)<10 || *(float *)(object+0x14)>1013 || *(float *)(object+0x18)<10 || *(float *)(object+0x18)>1013 || (math_fast_float_d(data+0x40) && !object[0x31])) {
destroy:
                moby_mark_spawned(object);
            }
            break;
        case 4:
            SpawnExplosionEffects(object,data+0x10,0,2,4,10,3,16,4,2,9,1,-1,15,1,1,-1,0,0x810001);
            moby_mark_spawned(object);break;
        }
    } else goto destroy;
}
