/* Nonmatching: 616/620 bytes, US 0/2, US2 0/2; absent from PAL.
 * Profile: -O2 -G0 -ffunction-sections -g -frac2-zero-ti-por
 *          -mno-split-addresses -fno-gcse. -G8 ties byte for byte.
 * The guarded positive-count loop preserves the original division before
 * testing count. -fno-gcse prevents invariant object-position and duration
 * addresses being hoisted into two additional saved registers; the narrower
 * -fno-rerun-loop-opt control still produces 640 bytes.
 * Remaining: the indexed GP size-table load folds its base into the memory
 * operand, whereas retail materializes the GP base first (one extra word).
 * Reopen with a supported address-model control preserving the real unknown
 * table extent, not a fabricated small bound or a volatile access.
 * BAA28 returns a particle pointer and consumes complete 16-byte vectors;
 * 83D38 returns a packed 32-bit color. The payloads are fully initialized.
 */
#include "common.h"
typedef int EmissionQuad __attribute__((mode(TI)));
typedef union { EmissionQuad q; float f[4]; } EmissionVector;

/* These configuration allocations are not sized here. Only the separately
 * documented GP address views carry small-address metadata. */
extern float D_L22_001B0A20[] NOT_SDA;
extern float D_L22_001B0A20_gp[] SDATA(D_L22_001B0A20);
extern int D_L22_001B0A28[] NOT_SDA;
extern int D_L22_001B0A28_gp[] SDATA(D_L22_001B0A28);
extern int D_L22_001B0A2C[] NOT_SDA;
extern int D_L22_001B0A30[] NOT_SDA;
extern int D_L22_001B0A34[] NOT_SDA;
extern float D_L22_001B0A38[] NOT_SDA;
extern float D_L22_001B0A38_gp[] SDATA(D_L22_001B0A38);
extern int D_L22_001B0A48[] NOT_SDA;
extern int D_L22_001B0A48_gp[] SDATA(D_L22_001B0A48);
extern int D_L22_001B0A4C[] NOT_SDA;
extern int D_L22_001B0A50[] NOT_SDA;
extern int D_L22_001B0A44[] NOT_SDA;
extern int D_L22_001B0A44_gp[] SDATA(D_L22_001B0A44);
extern float func_00283CE0(int);
extern float func_002A78D8(float,float);
extern void func_00283098(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern float func_002A7878(float,float);
extern int func_00283D38(int,int,float);
extern int func_002A77E0(int);
extern void func_00282C88(void *);
extern int func_002A7820(int,int);
/* BAA28 consumes three complete vectors, five register ints and a ninth stack int. */
extern void *func_002BAA28(void *,float *,float *,int,int,int,int,int,int);

void func_L22_003F5688(unsigned char *object,int fullDensity)
{
    EmissionVector position,scratch,to;
    unsigned char *state=*(unsigned char **)(object+0x68);
    float height=*(float *)(state+0xA0);
    float count=(height*7.2900004386901855f)*D_L22_001B0A20_gp[0];
    float step;
    float zero;
    float baseWidth=2.7f;
    int i;
    if(!fullDensity)
        count*=0.2f;
    i=0;
    step=height/count;
    if((float)i<count) {
        zero=(float)i;
        do {
            float progress=func_00283CE0(i)*step;
            float spread=baseWidth+progress*0.1f;
            int firstColor,secondColor,kind,duration;
            float size;
            scratch.q=0;
            scratch.f[0]=func_002A78D8(zero,spread);
            scratch.f[1]=func_002A78D8(zero,spread);
            scratch.f[2]=progress;
            position.q=scratch.q;
            func_00283098(position.f,position.f,object+0xC0);
            func_00282CC0(position.f,position.f,object+0x10);
            firstColor=func_00283D38(D_L22_001B0A28_gp[0],D_L22_001B0A2C[0],func_002A7878(zero,1.0f));
            secondColor=func_00283D38(D_L22_001B0A30[0],D_L22_001B0A34[0],func_002A7878(zero,1.0f));
            size=D_L22_001B0A38_gp[func_002A77E0(2)];
            func_00282C88(scratch.f);
            scratch.f[3]=size;
            func_00282C88(to.f);
            to.f[3]=size;
            kind=func_002A7820(1,D_L22_001B0A48_gp[0]);
            duration=func_002A7820(D_L22_001B0A4C[0],D_L22_001B0A50[0]);
            func_002BAA28(position.f,scratch.f,to.f,firstColor,secondColor,kind,duration,60,D_L22_001B0A44_gp[0]);
            ++i;
        } while((float)i<count);
    }
}
