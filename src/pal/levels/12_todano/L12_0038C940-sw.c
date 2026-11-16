#include "include_asm.h"

#include "common.h"
extern void SpawnExplosionEffects_pal(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void FastVecAdd(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern int coll_test_point(void *,int,void *,float);
extern void vec_fast_normalize(void *,void *,void *);
extern int math_fast_float_d(void *);
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct { char pad[0x18]; char *hit; int count; Vec point; char gap[0x10]; Vec normal; } Collision;
extern Collision g_collision_l12_result;
extern float FastAddRotations(float,float);
extern void moby_mark_spawned(void *);

/* Mirrors its linked object, then moves and destroys the detached fragment. */
void mirrored_fragment_update_pal(u8 *moby) {
    u8 *vars=*(u8 **)(moby+0x68);u8 *tracked=*(u8 **)(vars+0x3C);
    if(tracked && *(short *)(tracked+0xAA)==0x184 && tracked[0x20]!=254 && tracked[0x20]!=253) {
        *(u16 *)(moby+0x34)&=0xFFFC;
        *(u16 *)(moby+0x34)|=*(u16 *)(*(u8 **)(vars+0x3C)+0x34)&3;
        switch(moby[0x20]) {
        case 0: moby[0x20]=1; qzero_nc(vars+0x20);break;
        case 1:
            tracked=*(u8 **)(vars+0x3C);
            *(float *)(moby+0x2C)=*(float *)(*(u8 **)(moby+0x24)+0x24)**(float *)(tracked+0x2C) / *(float *)(*(u8 **)(tracked+0x24)+0x24);
            *(u64 *)(moby+0x38)=*(u64 *)(*(u8 **)(vars+0x3C)+0x38);break;
        case 2: return;
        default: break;
        case 3:
            FastVecAdd(moby+0x10,moby+0x10,vars+0x10);
            FastVecScale(vars+0x10,vars+0x10,0.995f);
            if(coll_test_point(moby+0x10,0,moby,2.0f)) {
                u8 *hit=g_collision_l12_result.hit;
                if(hit) {
                    int class_id=*(short *)(hit+0xAA);
                    if(class_id==0x191 || class_id==0x184 || class_id==0x185 || class_id==0x186 || class_id==0x187 || class_id==0x188 || class_id==0x189 || class_id==0x18A || class_id==0x18B || class_id==0x18C || class_id==0x18F || class_id==0x190) goto rotate;
                }
                vec_fast_normalize(vars+0x10,vars+0x10,g_collision_l12_result.normal.f);moby[0x20]=4;
            }
rotate:
            *(float *)(moby+0xF0)=FastAddRotations(*(float *)(moby+0xF0),*(float *)(vars+0x30));
            *(float *)(moby+0xF4)=FastAddRotations(*(float *)(moby+0xF4),*(float *)(vars+0x34));
            *(float *)(moby+0xF8)=FastAddRotations(*(float *)(moby+0xF8),*(float *)(vars+0x38));
            *(float *)(vars+0x30)*=0.999f;*(float *)(vars+0x34)*=0.999f;*(float *)(vars+0x38)*=0.999f;
            if(*(float *)(moby+0x10)<10 || *(float *)(moby+0x10)>1013 || *(float *)(moby+0x14)<10 || *(float *)(moby+0x14)>1013 || *(float *)(moby+0x18)<10 || *(float *)(moby+0x18)>1013 || (math_fast_float_d(vars+0x40) && !moby[0x31])) {
destroy:
                moby_mark_spawned(moby);
            }
            break;
        case 4:
            SpawnExplosionEffects_pal(moby,vars+0x10,0,2,4,10,3,16,4,2,9,1,-1,15,1,1,-1,0,0x810001);
            moby_mark_spawned(moby);break;
        }
    } else goto destroy;
}
