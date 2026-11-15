/* func_L30_003E1BA0 has a unit of its own (-O2 -G8 -ffunction-sections -Wa,-G32 in
 * config/cflags.txt): the assembler's -G32 makes the two 16-byte sda vectors $gp-relative.
 * The saved home position/rotation and the vector zeroed in state 0 are sda incomplete arrays: cc1
 * keeps their addresses whole and the assembler builds them absolute (lui/addiu, lui $at for
 * the store of its z), while the boot vector D_00189EA0 is split into %hi/%lo. */
#include "common.h"
extern char D_L30_001B3AE0[] __attribute__((sda)), D_L30_001B3AF0[] __attribute__((sda)), D_00189EA0[];
extern float D_L30_001B3B20[] __attribute__((sda));
extern float D_L30_001B0B78 __attribute__((sda));
extern float D_L30_001B0B7C __attribute__((sda));
extern float D_L30_001B0B80 __attribute__((sda));
extern float D_L30_001B0BB0 __attribute__((sda));
extern float D_L30_001B0BBC __attribute__((sda));
extern float D_L30_001B0BC0 __attribute__((sda));
extern float D_L30_001B0BC4 __attribute__((sda));
extern int D_L30_001B0BB4 __attribute__((sda));
extern int D_L30_001B0BB8 __attribute__((sda));
extern char D_L30_001B0B90[16] __attribute__((sda)), D_L30_001B0BA0[16] __attribute__((sda));
extern void func_002A7750(void *,int,int);
extern int func_002A9640(void *,int,int), func_00273B70(void *);
extern void func_00282C88(void *),func_00282C98(void *),func_00282CF0(void *,void *,void *),func_00282DD8(void *,void *,void *),func_00283098(void *,void *,void *),func_00282CC0(void *,void *,void *),func_002833F0(void *,void *);
extern void func_00282F70(void *,void *,float),func_00282F20(void *,void *,float);
extern float func_00283198(float),func_00283180(float);
extern void func_L00_003263D0(void *,void *,float,int,int,void *,unsigned,int,float,float,float);
extern void func_00273978(void *,int,int,void *,void *,int,float);
/* Updates a museum gadget (moby class 3142). When triggered it fires an effect from a fixed spot, waits for it to end, then fades and returns to its home place. */
void func_L30_003E1BA0(unsigned char *obj) {
    struct { float v[4], axis[4], up[4], pos[4]; } f;
    switch(obj[0x20]) {
    case 0:
        obj[0x30]=255; SetMobyState(obj,1,-1);
        *(unsigned short *)(obj+0x34)|=0x100;
        qcopy(D_L30_001B3AE0,obj+0x10); qcopy(D_L30_001B3AF0,obj+0xF0);
        ClearVector128(D_L30_001B3B20); D_L30_001B3B20[2]=0.4f;
        break;
    case 1:
        if(FindOwnedEffectSlot(obj,0x10000,0)) {
            float frameTime=0.016666668f;
            float angleScale;
            FastVecSub(f.v,obj+0x10,gHeroPosition);
            angleScale=0.00029088825f;
            FastVectorNormalizeHelper(f.v,f.v,D_L30_001B0B78*frameTime);
            f.v[2]=D_L30_001B0B7C*frameTime;
            VectorCopyHelperA(f.up);
            FastVecCross(f.axis,f.v,f.up);
            vec_scale_to_length(f.axis,f.axis,FastSinOrCosB(-D_L30_001B0B80*angleScale));
            f.axis[3]=FastSinOrCosA(D_L30_001B0B80*angleScale);
            matrix_mul_vec3(f.pos,D_L30_001B0B90,obj+0xC0);
            FastVecAdd(f.pos,f.pos,obj+0x10);
            SpawnTintedEffects(obj,f.pos,D_L30_001B0BB0,D_L30_001B0BB4,D_L30_001B0BB8,D_L30_001B0BA0,0x50404040,0,D_L30_001B0BBC,D_L30_001B0BC0,D_L30_001B0BC4);
            InitCameraTracking(obj,0,-1,f.v,f.axis,255,15.0f);
            *(int *)(obj+0x98)=0; SetMobyState(obj,2,-1);
        }
        break;
    case 2: if(UpdateCameraMoby(obj)) SetMobyState(obj,3,-1); break;
    case 3:
        if(obj[0x23]<2) {
            qcopy(obj+0x10,D_L30_001B3AE0); euler_rotation_basis(obj+0xC0,D_L30_001B3AF0);
            obj[0x23]=128; *(int *)(obj+0x98)=*(int *)(*(char **)(obj+0x24)+0x10); SetMobyState(obj,1,-1);
        } else obj[0x23]-=2;
        break;
    }
    obj[0xA8]=255;
}
