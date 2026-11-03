/* func_L11_004461E8 (11_joba): scale state machine at state+0x1FA. Case 1 copies the source vertex rows and
 * opens the record; cases 2 and 4 ease the scale at 0x1BC toward its target; case 5 snaps it closed. A scale
 * change rescales the vertex rows and the record's two vectors, and state 2 advances the two phase/weight rows.
 * Retail loads the record table pointer $gp-relative only in case 4's finish (the bc1f delay slot), hence the
 * GP view there; the scale is a struct member, so case 5's record load can be scheduled before its store.
 */
#include "common.h"

#define S16(p,o) (*(short *)((p)+(o)))
#define U16(p,o) (*(unsigned short *)((p)+(o)))
#define I32(p,o) (*(int *)((p)+(o)))
#define F32(p,o) (*(float *)((p)+(o)))
typedef struct { u8 pad0[0x10]; float position[4]; u8 pad20[0x11]; u8 enabled; u16 mask, flags; u8 rest[0xCA]; } JobaRecord461E8;
typedef struct { u8 pad0[0x1bc]; float scale; } JobaState461E8;
#define SCALE(p) (((JobaState461E8 *)(p))->scale)
extern JobaRecord461E8 *D_L11_001B359C __attribute__((section(".sdata")));
extern JobaRecord461E8 *D_L11_001B359C_GP SDATA(D_L11_001B359C);
extern u8 *D_L11_001FF580[];
extern float D_L11_001B187C __attribute__((sda)), D_L11_001B1880 __attribute__((sda));
extern float D_L11_001B1884 __attribute__((sda)), D_L11_001B1888 __attribute__((sda));
extern void func_00283360(void *);
extern float func_002AA2E8(float *,float,float);
extern float func_00282C48(float);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern float func_002A7878(float,float);
void func_L11_004461E8(u8 *object)
{
    u8 *state = *(u8 **)(object+0x68);
    float previous = SCALE(state);
    float vector[4] __attribute__((aligned(16)));
    switch (S16(state,0x1fa)) {
    case 1: {
        int i;
        u8 *dst, *src;
        func_00283360((u8 *)&D_L11_001B359C[I32(state,0x1b8)]+0xc0);
        previous=1.0f;
        dst=D_L11_001FF580[I32(state,0x1c8)];
        src=D_L11_001FF580[I32(state,0x1cc)];
        for(i=0;i<I32(dst,0);i++) qcopy_nc(dst+16+i*16,src+16+i*16);
        D_L11_001B359C[I32(state,0x1b8)].flags&=0xfffe;
        D_L11_001B359C[I32(state,0x1b8)].enabled=1;
        D_L11_001B359C[I32(state,0x1b8)].mask=255;
        SCALE(state)=D_L11_001B187C;
        F32(state,0xd4)=0.5f;
        S16(state,0x1fa)=2;
        I32(state,0xd0)=0;
        /* Initialization deliberately advances the new animation immediately. */
    }
    case 2:
        func_002AA2E8(&SCALE(state),D_L11_001B1880,D_L11_001B1884);
        if (func_00282C48(SCALE(state)-D_L11_001B1880)<0.01f) S16(state,0x1fa)=3;
        break;
    case 4:
        func_002AA2E8(&SCALE(state),D_L11_001B187C,D_L11_001B1884);
        if (func_00282C48(SCALE(state)-D_L11_001B187C)<0.01f) {
            D_L11_001B359C_GP[I32(state,0x1b8)].flags|=1;
            D_L11_001B359C_GP[I32(state,0x1b8)].enabled=0;
            S16(state,0x1fa)=0;
        }
        break;
    case 5:
        SCALE(state)=D_L11_001B187C;
        D_L11_001B359C[I32(state,0x1b8)].flags|=1;
        D_L11_001B359C[I32(state,0x1b8)].enabled=0;
        S16(state,0x1fa)=0;
        break;
    }
    if (previous != SCALE(state)) {
        int i;
        u8 *dst, *vertex;
        dst=D_L11_001FF580[I32(state,0x1c8)];
        for (i=0;i<I32(dst,0);i++) {
            vertex=dst+16+i*16;
            func_00282CF0(vector,vertex,(u8 *)&D_L11_001B359C[I32(state,0x1b8)]+16);
            func_00282D30(vector,vector,SCALE(state)/previous);
            func_00282CC0(vertex,(u8 *)&D_L11_001B359C[I32(state,0x1b8)]+16,vector);
            F32(vertex,8)=F32((u8 *)&D_L11_001B359C[I32(state,0x1b8)],0x18);
        }
        func_00282F20((u8 *)&D_L11_001B359C[I32(state,0x1b8)]+0xc0,(u8 *)&D_L11_001B359C[I32(state,0x1b8)]+0xc0,SCALE(state));
        func_00282F20((u8 *)&D_L11_001B359C[I32(state,0x1b8)]+0xd0,(u8 *)&D_L11_001B359C[I32(state,0x1b8)]+0xd0,SCALE(state));
    }
    if (S16(state,0x1fa)==2) {
        int i = 0;
        float *phase = (float *)(state + 0xD0);
        float *weight = (float *)(state + 0xD8);
        for(;i<2;i++) {
            float *phase_row = phase + i;
            *phase_row+=D_L11_001B1888*0.01666666753590107f;
            if (*phase_row>1.0f) {
                float random;
                float *weight_row;
                float *opposite;
                *phase_row-=1.0f;
                random = func_002A7878(0.3330000042915344f,0.6660000085830688f);
                weight_row = weight + i;
                opposite = weight + ((i+1)&1);
                *weight_row = *opposite + random;
                if(*weight_row>1.0f) *weight_row-=1.0f;
            }
        }
    }
}
