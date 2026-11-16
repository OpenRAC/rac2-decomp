/* func_PAL_L11_0044BC30, the PAL copy of func_L11_004461E8: the same C, where 0.01666666753590107f
   becomes 0.020000001f. */
#include "common.h"

#define S16(p,o) (*(short *)((p)+(o)))
#define I32(p,o) (*(int *)((p)+(o)))
#define F32(p,o) (*(float *)((p)+(o)))
typedef struct { u8 pad0[0x10]; float position[4]; u8 pad20[0x11]; u8 enabled; u16 mask, flags; u8 rest[0xCA]; } JobaRecord461E8;
typedef struct { u8 pad0[0x1bc]; float scale; } JobaState461E8;
#define SCALE(p) (((JobaState461E8 *)(p))->scale)
extern JobaRecord461E8 *g_moby_l11_table __attribute__((section(".sdata")));
extern JobaRecord461E8 *D_L11_001B359C_GP SDATA(D_L11_001B359C);
extern u8 *g_path_l11_table[];
extern float g_ribbon_scale_target_a __attribute__((sda)), g_ribbon_scale_target_b __attribute__((sda));
extern float g_ribbon_scale_approach_rate __attribute__((sda)), g_ribbon_phase_speed __attribute__((sda));
extern void set_identity_rotation_rows(void *);
extern float ApproachValue(float *,float,float);
extern float math_fabs(float);
extern void FastVecSub(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern float math_random_float_range(float,float);
void joba_update_ribbon_scale_pal(u8 *object)
{
    u8 *state = *(u8 **)(object+0x68);
    float previous = SCALE(state);
    float vector[4] __attribute__((aligned(16)));
    switch (S16(state,0x1fa)) {
    case 1: {
        int i;
        u8 *dst, *src;
        set_identity_rotation_rows((u8 *)&g_moby_l11_table[I32(state,0x1b8)]+0xc0);
        previous=1.0f;
        dst=g_path_l11_table[I32(state,0x1c8)];
        src=g_path_l11_table[I32(state,0x1cc)];
        for(i=0;i<I32(dst,0);i++) qcopy_nc(dst+16+i*16,src+16+i*16);
        g_moby_l11_table[I32(state,0x1b8)].flags&=0xfffe;
        g_moby_l11_table[I32(state,0x1b8)].enabled=1;
        g_moby_l11_table[I32(state,0x1b8)].mask=255;
        SCALE(state)=g_ribbon_scale_target_a;
        F32(state,0xd4)=0.5f;
        S16(state,0x1fa)=2;
        I32(state,0xd0)=0;
        /* Initialization deliberately advances the new animation immediately. */
    }
    case 2:
        ApproachValue(&SCALE(state),g_ribbon_scale_target_b,g_ribbon_scale_approach_rate);
        if (math_fabs(SCALE(state)-g_ribbon_scale_target_b)<0.01f) S16(state,0x1fa)=3;
        break;
    case 4:
        ApproachValue(&SCALE(state),g_ribbon_scale_target_a,g_ribbon_scale_approach_rate);
        if (math_fabs(SCALE(state)-g_ribbon_scale_target_a)<0.01f) {
            D_L11_001B359C_GP[I32(state,0x1b8)].flags|=1;
            D_L11_001B359C_GP[I32(state,0x1b8)].enabled=0;
            S16(state,0x1fa)=0;
        }
        break;
    case 5:
        SCALE(state)=g_ribbon_scale_target_a;
        g_moby_l11_table[I32(state,0x1b8)].flags|=1;
        g_moby_l11_table[I32(state,0x1b8)].enabled=0;
        S16(state,0x1fa)=0;
        break;
    }
    if (previous != SCALE(state)) {
        int i;
        u8 *dst, *vertex;
        dst=g_path_l11_table[I32(state,0x1c8)];
        for (i=0;i<I32(dst,0);i++) {
            vertex=dst+16+i*16;
            FastVecSub(vector,vertex,(u8 *)&g_moby_l11_table[I32(state,0x1b8)]+16);
            FastVecScale(vector,vector,SCALE(state)/previous);
            FastVecAdd(vertex,(u8 *)&g_moby_l11_table[I32(state,0x1b8)]+16,vector);
            F32(vertex,8)=F32((u8 *)&g_moby_l11_table[I32(state,0x1b8)],0x18);
        }
        vec_scale_to_length((u8 *)&g_moby_l11_table[I32(state,0x1b8)]+0xc0,(u8 *)&g_moby_l11_table[I32(state,0x1b8)]+0xc0,SCALE(state));
        vec_scale_to_length((u8 *)&g_moby_l11_table[I32(state,0x1b8)]+0xd0,(u8 *)&g_moby_l11_table[I32(state,0x1b8)]+0xd0,SCALE(state));
    }
    if (S16(state,0x1fa)==2) {
        int i = 0;
        float *phase = (float *)(state + 0xD0);
        float *weight = (float *)(state + 0xD8);
        for(;i<2;i++) {
            float *phase_row = phase + i;
            *phase_row+=g_ribbon_phase_speed*0.020000001f;
            if (*phase_row>1.0f) {
                float random;
                float *weight_row;
                float *opposite;
                *phase_row-=1.0f;
                random = math_random_float_range(0.3330000042915344f,0.6660000085830688f);
                weight_row = weight + i;
                opposite = weight + ((i+1)&1);
                *weight_row = *opposite + random;
                if(*weight_row>1.0f) *weight_row-=1.0f;
            }
        }
    }
}
