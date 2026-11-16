#include "include_asm.h"

#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits;float f[4]; } Vector4;
#define FIELD(type,p,off) (*(type *)((char *)(p)+(off)))
extern s32 coll_test_point(void *,s32,void *,float);
extern void vec_scale_to_length(void *,void *,float);
extern char *g_tether_l10_hit_result NOT_SDA;
extern char *g_cloud_boss_actor __attribute__((sda));
extern Vector4 g_probe_hit_vector;

/* Tests the cloud object against a point; on a hit it gets a velocity, toward the boss for a class 0xFBF
   hit, otherwise bounced from the hit vector. */
void cloud_object_bounce_velocity_pal(char *object)
{
    Vector4 direction;
    char *work=FIELD(char *,object,0x68),*hit;
    if(!coll_test_point(object+0x10,16,object,0.8f))return;
    hit=g_tether_l10_hit_result;
    if(hit && FIELD(s16,hit,0xAA)==0xFBF) {
        if(!g_cloud_boss_actor)return;
        direction.bits=FIELD(Quadword,g_cloud_boss_actor,0xC0);
        vec_scale_to_length(&direction,&direction,0.32000002f);
        FIELD(Quadword,work,0)=direction.bits;
    }else {
        FIELD(Quadword,work,0)=g_probe_hit_vector.bits;
        vec_scale_to_length(work,work,0.040000003f);
    }
}
