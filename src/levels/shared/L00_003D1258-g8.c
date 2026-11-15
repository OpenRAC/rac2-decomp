/* Updates an ammo pickup: tests collection, awards ammo, then homes in and fades out. */
#include "common.h"
typedef unsigned int Quadword __attribute__((mode(TI)));
#define B(p,o) (*(u8 *)((char *)(p)+(o)))
#define S(p,o) (*(s16 *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
extern u8 D_00139568[];
extern int D_00139688[];
typedef struct {
    char pad_00[0x38]; s16 multiple_sound; s16 single_sound;
    char pad_3C[2]; s16 moby_class;
    char pad_40[0x4E]; u16 capacity;
    char pad_90[0x50];
} PickupResource;
extern PickupResource D_L00_00262570[];
typedef struct {
    char pad_00[0x20]; float axis[4];
    char pad_30[0x10]; float matrix[16];
    float position[4]; char pad_90[0x50]; float target[4];
    char pad_F0[0x60]; float motion[4];
    char pad_160[0x2162]; u8 override;
    char pad_22C3[0x1E1]; float range; float height;
    char pad_24AC[0x20]; int enabled;
} PickupPlayer;
extern char D_00189E20[];
#define PLAYER ((PickupPlayer *)D_00189E20)

extern int D_L00_001A8FF0[] __attribute__((sda));
extern int D_L00_001B19C8[] __attribute__((sda));
extern int D_L00_001B2ADC[] MACRO_ADDR;

extern void *D_0018C0B0 NOT_SDA;
extern void func_00282C90(void *);
extern void func_00273B70(void *);
extern float func_00282E48(void *,void *);
extern int func_00282948(void *);
extern float func_00282C48(float);
extern float func_00282E80(void *,void *);
extern float func_002B0360(void *);
extern int func_L00_002D3FB8(int,int);
extern void func_L00_00326200(int,int,int);
extern void func_002A7750(void *,int,int);
extern void func_00282C88(void *);
extern int func_00282C30(int);
extern int func_002E5CF8(int,int,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00283098(void *,void *,void *);
extern void func_002AA2E8(void *,float,float);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern float func_00282DF0(void *);
extern void func_0029F338(void *);
extern void func_00282DD8(void *,void *,void *);
extern void func_002ACE78(void *,void *,float);
extern void func_00283958(void *,void *);
extern void func_00283738(void *,void *,void *);
extern int func_00282ED8(void *,void *);
/* Per-frame update of a dropped pickup (ammo and similar). It picks up its item when the player is close and not full, plays the pickup sound, and while collected flies toward the player before disappearing. */
void func_L00_003D1258(char *moby)
{
    char *vars=*(char **)(moby+0x68);
    PickupResource *resource;
    int j,i,canPickUp,changed,oldCount,delta,sound;
    float speed,timeLeft,targetSpeed;
    float work[4] __attribute__((aligned(16)));
    float push[4] __attribute__((aligned(16)));
    float toTarget[4] __attribute__((aligned(16)));
    float axisCross[4] __attribute__((aligned(16)));
    float before[4] __attribute__((aligned(16)));
    float after[4] __attribute__((aligned(16)));
    float shift[4] __attribute__((aligned(16)));
    float up[4] __attribute__((aligned(16)));
    char matrix[48] __attribute__((aligned(16)));
    switch(B(moby,0x20)) {
    case 0:
        B(moby,0x20)=1;
        for(j=0;j<56;j++) {
            resource=&gWeaponTable_L00[gItemSlotToRecord[j]];
            if(resource->moby_class==S(moby,0xaa))I(vars,0x68)=j;
        }
        break;
    case 1:
        if(B(vars,0x5c)==3 && (gFrameCounter_L00[0]&15)==(((int)moby>>8)&15)) {
            qzero(vars);StoreVectorHelper(vars+0x10);B(vars,0x5c)=0;
        }
        qcopy(work,vars);
        UpdateCameraMoby(moby);
        changed=0;
        if(fast_vec_dist(work,vars)>F(vars,0x48)*2.0f)changed=1;
        canPickUp=1;
        if(B(vars,0x5c)||changed) {
            if(FastFloatHelperD(vars+0x7c)) {
                if(FloatAbs(F(moby,0x18)-PLAYER->position[2])>PLAYER->height)canPickUp=0;
                else if(vec_distance_xy(moby+0x10,PLAYER->position)>PLAYER->range)canPickUp=0;
            }
        } else {
            canPickUp=0;
            if(FloatAbs(F(moby,0x18)-PLAYER->position[2])<PLAYER->height &&
               vec_distance_xy(moby+0x10,PLAYER->position)<PLAYER->range)I(vars,0x7c)=3;
        }
        if(gItemAmmoCounts[I(vars,0x68)] >=
           ((PickupResource *)(gItemSlotToRecord[I(vars,0x68)] * 224 + (unsigned int)gWeaponTable_L00))->capacity)canPickUp=0;
        if(D_L00_001A8FF0[0]) {
            if(GetDistanceFromGravityCenter(moby+0x10)<F(vars,0x78)-2.0f)goto force_pickup;
        } else if(F(moby,0x18)<F(vars,0x78)-2.0f)goto force_pickup;
        if(!PLAYER->override)goto check_enabled;
force_pickup:
        canPickUp=1;
check_enabled:
        if(!PLAYER->enabled)canPickUp=0;
        if(canPickUp) {
            i=I(vars,0x68);oldCount=gItemAmmoCounts[i];
            AddWeaponAmmo(i,I(vars,0x60));
            if(oldCount<gItemAmmoCounts[i]) {
                delta=gItemAmmoCounts[i]-oldCount;
                if(delta==1) {
                    resource=&gWeaponTable_L00[gItemSlotToRecord[i]];
                    sound=resource->single_sound;
                } else {
                    resource=&gWeaponTable_L00[gItemSlotToRecord[i]];
                    sound=resource->multiple_sound;
                }
                ResetEffects(sound,delta,-1);
            }
            SetMobyState(moby,2,-1);
            F(vars,0x74)=0.13333334f;
            ClearVector128(vars);
            if(subtract_integer_with_clamp(gFrameCounter_L00[0]-D_L00_001B2ADC[0])>10) {
                PlayMobySound(0,0,moby);D_L00_001B2ADC[0]=gFrameCounter_L00[0];
            }
        }
        break;
    case 2:
        FastVecSub(work,moby+0x10,PLAYER->position);
        matrix_mul_vec3(work,work,PLAYER->matrix);
        targetSpeed=8.0f;
        if(work[2]>0.0f)targetSpeed=0.0f;
        ApproachValue(vars+0x74,targetSpeed,0.0066666668f);
        vec_scale_to_length(push,PLAYER->axis,F(vars,0x74));
        FastVecAdd(moby+0x10,moby+0x10,push);
        FastVecAdd(moby+0x10,moby+0x10,PLAYER->motion);
        speed=FastVecLength(vars);
        ApproachValue(&speed,1.0666667f,0.0066666668f);
        FastVecSub(toTarget,PLAYER->target,moby+0x10);
        timeLeft=FastVecLength(toTarget)/speed;
        if(timeLeft<30.0f)ApproachValue(moby+0x2c,0.0f,F(*(char **)(moby+0x24),0x24)*0.033333335f);
        if(F(moby,0x2c)==0.0f) {MarkMobySpawned(moby);return;}
        if(timeLeft<=1.0f) {MarkMobySpawned(moby);return;}
        vec_scale_to_length(vars,toTarget,speed);
        FastVecAdd(moby+0x10,moby+0x10,vars);
        FastVecCross(axisCross,PLAYER->axis,vars);
        SetDirectionWithComplement(axisCross,axisCross,0.087266475f);
        *(Quadword *)up=0;up[2]=0.3f;
        matrix_mul_vec3(before,up,moby+0xc0);
        quaternion_to_rotation_basis(axisCross,matrix);
        multiply_matrix3x3(moby+0xc0,matrix,moby+0xc0);
        matrix_mul_vec3(after,up,moby+0xc0);
        FastVecSub(shift,after,before);
        FastVecSub(moby+0x10,moby+0x10,shift);
        break;
    }
    if(B(moby,0x20)==1 && FastVectorHelperD(moby,gHeroMoby_0018C0B0)) {
        B(moby,0x23)=B(moby,0x23)>36?B(moby,0x23)-4:36;
    } else {
        B(moby,0x23)=B(moby,0x23)<124?B(moby,0x23)+4:128;
    }
    if(*(s8 *)(moby+0x23)>=0)*(u16 *)(moby+0x34)|=0x2000;
    else *(u16 *)(moby+0x34)&=0xdfff;
}
