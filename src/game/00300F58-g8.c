#include "common.h"

#define B(p,o) (*(u8 *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
typedef struct PickupMoby PickupMoby;
typedef struct {
    float position[4], rotation[4], velocity[4], spin[4];
    u8 pad40[2], activated, pad43[5];
    float angleX, angleZ, random0;
    u8 flags54, flags55, hopLength, hopRemaining;
    float random1;
    PickupMoby *surface, *target;
    float acceleration, initialHeight;
} BoltVars;
struct PickupMoby {
    u8 pad00[0x10]; float position[4];
    u8 state, pad21[3]; char *pClass;
    u8 pad28[4]; float scale;
    u8 renderDistance, visible; u16 updateDistance, flags;
    u8 pad36[0x2D]; u8 opacity; u8 pad64[4]; BoltVars *pVars;
    u8 pad6C[0x3E]; u16 classId; u8 flagsAC[4]; u8 uid; u8 padB1; s16 mission;
    u8 padB4[0xC]; float orientation[12];
};
typedef struct {
    float position[4];
    u8 pad90[0x50]; float boltTarget[4];
    u8 padF0[0x60]; float velocity[4];
    u8 pad160[0x170]; float cameraPosition[4];
    u8 pad2E0[0x1FB0]; PickupMoby *moby;
    u8 pad2294[0x210]; float pickupRadius, pickupHeight;
    u8 pad24AC[0x20]; int magnetEnabled;
} BoltHeroMotion;
typedef struct {
    float matrix[16], rotation[4];
    u8 pad50[0x30]; BoltHeroMotion motion;
} BoltHero;
typedef struct {
    u8 pad00[0x18]; PickupMoby *surface; u8 pad1C[4];
    float position[4]; u8 pad30[0x10]; float normal[4];
} BoltCollision;
extern BoltHero D_00189E20;
extern BoltCollision D_001BAF80;
extern char D_001B19A0[] __attribute__((sda));
extern char D_0019B2E8[];
/* Only the prefix is fixed here; collection entries continue after it. */
typedef struct { u8 prefix[0x464]; u8 collected[0]; } BoltCollectionTable;
extern BoltCollectionTable D_00210D40, D_002119B0;
/* The 0x40-byte player-stat block is saved/restored by func_002DE990. */
typedef struct { int bolts; u8 prefix[0x18]; int pendingBolts; u8 suffix[0x20]; } BoltPlayerStats;
extern BoltPlayerStats D_001A79F8 __attribute__((sda));
typedef struct { PickupMoby *start, *end, *active; void *aux; } BoltMobyPool;
extern BoltMobyPool D_001B1B60 __attribute__((sda));
extern char *D_001AE8E0 SDATA(D_001AE8E0);
extern char *D_001B1B60_gp SDATA(D_001B1B60);
extern int D_001A79F0 SDATA(D_001A79F0);
extern float D_001AE8B0 SDATA(D_001AE8B0), D_001AE8B4 SDATA(D_001AE8B4);
extern float D_001AE8B8 SDATA(D_001AE8B8), D_001AE8BC SDATA(D_001AE8BC);
extern float D_001AE8C0 SDATA(D_001AE8C0), D_001AE8C4 SDATA(D_001AE8C4), D_001AE8C8 SDATA(D_001AE8C8);
extern int func_002A77E0(int);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *),func_00282CF0(void *,void *,void *);
extern int func_002761F8(void *,void *,int,int,int);
extern void func_00282C88(void *);
extern float func_00283248(float,float),func_00282E20(void *),func_00282E80(void *,void *),func_00282DF0(void *),func_00282C48(float);
extern int func_002AD0B0(void *);
extern void func_002AD5F8(void *,void *,void *,void *,void *,void *);
extern float func_002A7940(void),func_002A7878(float,float),func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_002AEC18(void *,void *),func_002A04B8(void *,int *,int *,int *);
extern void func_002A0468(void *,int,int,int,int),func_002A0488(void *,int,int,int);
extern void func_00283958(void *,void *),func_00283738(void *,void *,void *),func_00283028(void *,void *,void *);
extern int func_00277258(void *,int,void *,float),func_00278E78(void);
extern void func_002AB6D8(void *,void *),func_002A91F0(void *,void *);
extern void func_00301F18(void *,void *,int);
extern void func_00283810(void *,void *,void *,float),func_00282D08(void *,void *,void *,float);
extern int func_003022A0(void *,void *,float,float);
extern void func_0029F338(void *),func_00302848(void *,int),func_002830C0(void *,void *,void *);
extern void func_002AC9F8(void *,float),func_002AA2E8(void *,float,float),func_00283098(void *,void *,void *),func_002833F0(void *,void *);
extern void func_00301D10(void *);
extern int func_002E5CF8(int,int,void *);

/* Update a bolt pickup through initialization, falling, hopping, idle and collection. */
void func_00300F58(PickupMoby *m)
{
    /* The matrix scratch overlaps vectors used in mutually exclusive states. */
    union {
        struct { float vector[4], other[4], basis[12]; } ground;
        struct { float basis[12], offset[4], angles[4]; } attract;
    } scratch;
    float matrix[12];
    int x,y,z;
    BoltVars *p=m->pVars;
#define hero D_00189E20
#define hit D_001BAF80
    switch(m->state) {
    case 0: {
        int collided;
        m->state=3;
        m->opacity=20;
        m->flags|=0x100;
        m->renderDistance=32;
        m->updateDistance=32;
        if(!RandomIntBelow(2)) p->flags55|=1;
        vec_scale_to_length(scratch.ground.vector,&m->orientation[8],0.2f);
        FastVecAdd(scratch.ground.vector,scratch.ground.vector,&m->position[0]);
        vec_scale_to_length(scratch.ground.other,&m->orientation[8],-3.0f);
        FastVecAdd(scratch.ground.other,scratch.ground.other,&m->position[0]);
        collided=CollLine(scratch.ground.vector,scratch.ground.other,0x22,0,0);
        if(!p->flags54&&collided) {
            qcopy_nc(p->position,&hit.position[0]);
            ClearVector128(&p->rotation[0]);
            p->rotation[2]=FastMatrixHelperA(hit.normal[0],hit.normal[1]);
            p->rotation[1]=FastMatrixHelperA(hit.normal[2],vec_length_xy(&hit.normal[0]));
            if(hit.surface&&GetMobyPrivateValue2(hit.surface)) {
                PickupMoby *surface=hit.surface;
                p->surface=surface;
                GetAttachmentRotationAngles(m,surface,p->position,&p->rotation[0],p->position,&p->rotation[0]);
            }
        }
        else {
            qcopy_nc(p->position,&m->position[0]);
            ClearVector128(&p->rotation[0]);
        }
        p->random0=RandomAngle();
        p->random1=RandomAngle();
        p->initialHeight=m->position[2];
        SetMobyLightColor(m,D_001AE8E0);
        get_moby_color(m,&x,&y,&z);
        PackRenderCommandFields(m,0,13,0,0);
        set_moby_color(m,x,y,z);
        switch((s16)(m->classId-13)) {
        case 0:m->scale=F(m->pClass,0x24)*D_001AE8B0;
            break;
        case 1:m->scale=F(m->pClass,0x24)*D_001AE8B4;
            break;
        case 2:m->scale=F(m->pClass,0x24)*D_001AE8B8;
            break;
        case 3:m->scale=F(m->pClass,0x24)*D_001AE8BC;
            break;
        case 4:m->scale=F(m->pClass,0x24)*D_001AE8C0;
            break;
        case 5:m->scale=F(m->pClass,0x24)*D_001AE8C4;
            break;
        case 6:m->scale=F(m->pClass,0x24)*D_001AE8C8;
            break;
        }
        break;
    }
    case 1: {
        float distance, t;
        distance=vec_distance_xy(&m->position[0],&hero.motion.position[0]);
        if(!p->activated&&distance<hero.motion.pickupRadius&&FloatAbs(m->position[2]-hero.motion.position[2])<hero.motion.pickupHeight) p->activated=1;
        p->velocity[2]-=0.003f;
        FastVecAdd(&m->position[0],&m->position[0],&p->velocity[0]);
        quaternion_to_rotation_basis(&p->spin[0],scratch.ground.basis);
        multiply_matrix3x3(&m->orientation[0],scratch.ground.basis,&m->orientation[0]);
        if(m->position[2]<p->initialHeight-2.0f&&m->position[2]<hero.motion.position[2]-2.0f) {
            t=RandomFloatRange(-15.0f,15.0f);
            StartPickupFlyToTarget(m,hero.motion.moby,t*0.017453294f,0);
            goto sparkle;
        }
        if(TestPointAgainstCollision(&m->position[0],0x22,m,0.25f)) {
            qcopy_nc(p->position,&hit.position[0]);
            ClearVector128(&p->rotation[0]);
            p->rotation[2]=FastMatrixHelperA(hit.normal[0],hit.normal[1]);
            p->rotation[1]=FastMatrixHelperA(hit.normal[2],vec_length_xy(&hit.normal[0]));
            FastVecSub(scratch.ground.vector,&m->position[0],&hit.position[0]);
            FastVectorNormalize(&p->velocity[0],&p->velocity[0],scratch.ground.vector);
            if(hero.motion.magnetEnabled && (p->activated ||
            (vec_distance_xy(&m->position[0],&hero.motion.position[0]) < hero.motion.pickupRadius &&
            FloatAbs(m->position[2]-hero.motion.position[2]) < hero.motion.pickupHeight) ||
            GetCollHitMaterial() != -1)) {
                vec_scale_to_length(&p->velocity[0],&p->velocity[0],0.13333334f);
                StartPickupFlyToTarget(m,hero.motion.moby,0,0);
            }
            else if(FastMatrixHelperA(scratch.ground.vector[2],vec_length_xy(scratch.ground.vector))<0.78539824f&&FastMatrixHelperA(hit.normal[2],vec_length_xy(&hit.normal[0]))<0.78539824f) {
                m->state=2;
                p->hopLength=p->hopRemaining=FloatToInt(RandomFloatRange(30,40));
                if(hit.surface&&GetMobyPrivateValue2(hit.surface)) {
                    PickupMoby *surface=hit.surface;
                    p->surface=surface;
                    GetAttachmentRotationAngles(m,surface,p->position,&p->rotation[0],p->position,&p->rotation[0]);
                }
                GetEulerAnglesFromMatrix(&m->orientation[0],scratch.ground.other);
                BuildRotationFromAngles(&p->spin[0],scratch.ground.other);
            }
        }
        goto sparkle;
    }
    case 2: {
        float distance, r, s;
        distance=vec_distance_xy(&m->position[0],&hero.motion.position[0]);
        if(!p->activated&&distance<hero.motion.pickupRadius&&FloatAbs(m->position[2]-hero.motion.position[2])<hero.motion.pickupHeight)p->activated=1;
        func_00301F18(m,scratch.ground.other,0);
        scratch.ground.other[2]+=0.25f;
        GetEulerAnglesFromMatrix(&m->orientation[0],scratch.ground.vector);
        BuildRotationFromAngles(scratch.ground.basis,scratch.ground.vector);
        r=1.0f/
        IntToFloat(p->hopRemaining);
        s=IntToFloat(p->hopRemaining) / IntToFloat(p->hopLength);
        FastVectorNormalize3(&p->spin[0],&p->spin[0],scratch.ground.basis,r);
        lerp_vector(&m->position[0],&m->position[0],scratch.ground.other,s);
        s-=0.5f;
        m->position[2]+=(0.25f-s*s)*0.025f*p->hopLength;
        quaternion_to_rotation_basis(&p->spin[0],&m->orientation[0]);
        if(--p->hopRemaining==0){
            m->state=3;
            p->hopLength=p->hopRemaining=FloatToInt(RandomFloatRange(10,20));
        }
        goto sparkle;
    }
    case 3: {
        int v;
        BoltHeroMotion *motion = &hero.motion;
        float distance, s;
        distance=vec_distance_xy(&m->position[0],motion->position);
        if(p->activated || (distance<hero.motion.pickupRadius&&FloatAbs(m->position[2]-hero.motion.position[2])<hero.motion.pickupHeight)) {
            StartPickupFlyToTarget(m,motion->moby,0,0);
        }
        else if((u32)D_001B1B60_gp<(u32)m&&distance>32.0f&&!m->visible) {
            switch((s16)(m->classId-13)) {
            default:case 0:v=1;
                break;
            case 1:v=5;
                break;
            case 2:v=20;
                break;
            case 3:v=50;
                break;
            case 4:v=100;
                break;
            case 5:v=500;
                break;
            case 6:v=1000;
                break;
            }
            gPlayerBolts.pendingBolts+=v;
            MarkMobySpawned(m);
            return;
        }
        else {
            if(m->visible||p->surface) {
                func_00301F18(m,0,0);
                if(p->hopRemaining){
                    s=IntToFloat(p->hopRemaining) / IntToFloat(p->hopLength);
                    s-=0.5f;
                    m->position[2]+=(0.25f-s*s)*0.0125f*p->hopLength;
                    --p->hopRemaining;
                }
            }
            else if(p->hopRemaining)--p->hopRemaining;
        }
    sparkle:
        if(m->visible)SpawnTrailPuff(m,1);
        break;
    }
    case 4: {
        int v;
        float speed;
        float t, s;
        v=0;
        if((s16)p->target->classId==0){
            FastVecSub(scratch.ground.vector,&m->position[0],&hero.motion.cameraPosition[0]);
            transform_vector(scratch.ground.vector,scratch.ground.vector,&hero.rotation[0]);
            if(scratch.ground.vector[2]<0)v=1;
        }
        if(v){
            vec_scale_to_length(scratch.ground.vector,&hero.matrix[8],0.13333334f);
            FastVecSub(scratch.ground.other,scratch.ground.vector,&p->velocity[0]);
            ClampVectorLength(scratch.ground.other,0.013888889f);
            FastVecAdd(&p->velocity[0],&p->velocity[0],scratch.ground.other);
        }
        else {
            t=0.006666667f;
            if(FastVecLength(&p->velocity[0])>t){
                vec_scale_to_length(scratch.ground.vector,&p->velocity[0],t);
                FastVecSub(&p->velocity[0],&p->velocity[0],scratch.ground.vector);
            }
            ApproachValue(&p->acceleration,0.53333336f,t);
        }
        speed=FastVecLength(&hero.motion.velocity[0]);
        if(speed>0.06666667f){
            vec_scale_to_length(scratch.ground.vector,&hero.motion.velocity[0],speed-0.06666667f);
            FastVecAdd(&m->position[0],&m->position[0],scratch.ground.vector);
        }
        quaternion_to_rotation_basis(&p->spin[0],scratch.attract.basis);
        multiply_matrix3x3(&m->orientation[0],scratch.attract.basis,&m->orientation[0]);
        FastVecAdd(&m->position[0],&m->position[0],&p->velocity[0]);
        if((s16)p->target->classId==0)FastVecSub(scratch.attract.offset,&hero.motion.boltTarget[0],&m->position[0]);
        else FastVecSub(scratch.attract.offset,p->target->position,&m->position[0]);
        if(FastVecLength(scratch.attract.offset)>p->acceleration) {
            if(p->angleZ!=0||p->angleX!=0){
                matrix_mul_vec3(scratch.attract.offset,scratch.attract.offset,&hero.rotation[0]);
                s=FastMatrixHelperA(scratch.attract.offset[0],scratch.attract.offset[1]);
                ClearVector128(scratch.attract.angles);
                scratch.attract.angles[1]=p->angleX;
                if(s<1.5707964f&&s>-1.5707964f)scratch.attract.angles[1]=-scratch.attract.angles[1];
                scratch.attract.angles[2]=p->angleZ;
                euler_rotation_basis(matrix,scratch.attract.angles);
                matrix_mul_vec3(scratch.attract.offset,scratch.attract.offset,matrix);
                matrix_mul_vec3(scratch.attract.offset,scratch.attract.offset,hero.matrix);
            }
            vec_scale_to_length(scratch.attract.offset,scratch.attract.offset,p->acceleration);
            FastVecAdd(&m->position[0],&m->position[0],scratch.attract.offset);
            goto sparkle_attract;
        }
        {
            CollectBolts(m);
            PlayMobySound(0,32,m);
            if(m<D_001B1B60.start){
                D_00210D40.collected[m->mission]=m->uid+2;
                {
                    int uid = m->uid;
                    if (uid != 255) {
                        int index = uid & 255;
                        if (B(D_001B19A0, index) & 128)
                            goto delete_pickup;
                        {
                            int row = 16 * gCurrentMapIndex;
                            if (!(B(D_0019B2E8, index + row) & 128))
                                goto delete_pickup;
                        }
                    }
                    D_002119B0.collected[m->mission] = uid + 2;
                }
            }
        delete_pickup:
            MarkMobySpawned(m);
            goto done;
        }
        break;
    }
    }
    return;
sparkle_attract:
    if(m->visible)SpawnTrailPuff(m,0);
done:;
}
