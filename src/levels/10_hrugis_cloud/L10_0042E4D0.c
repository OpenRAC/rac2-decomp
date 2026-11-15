#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits;float f[4]; } Vector4;
#define FIELD(type,p,off) (*(type *)((char *)(p)+(off)))
extern s32 coll_test_point(void *,s32,void *,float);
extern void vec_scale_to_length(void *,void *,float);
extern char *D_L10_001BFAD8 NOT_SDA;
extern char *D_L10_001B1780 __attribute__((sda));
extern Vector4 D_L10_001BFB00;
/* Probes ahead of a cloud object and sets its drift: along the ship's heading if the ship is
   in the way, otherwise a default push. */
void cloud_probe_object_obstacle(char *object)
{
    Vector4 direction;
    char *work=FIELD(char *,object,0x68),*hit;
    if(!coll_test_point(object+0x10,16,object,0.8f))return;
    hit=D_L10_001BFAD8;
    if(hit && FIELD(s16,hit,0xAA)==0xFBF /* moby class 4031 */) {
        if(!D_L10_001B1780)return;
        direction.bits=FIELD(Quadword,D_L10_001B1780,0xC0);
        vec_scale_to_length(&direction,&direction,0.26666668f);
        FIELD(Quadword,work,0)=direction.bits;
    }else {
        FIELD(Quadword,work,0)=D_L10_001BFB00.bits;
        vec_scale_to_length(work,work,0.033333335f);
    }
}
