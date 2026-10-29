/* Nonmatching: US/US2 712/720 bytes, 0/27; absent from PAL.
 * Three checks, profile -O2 -G0 -ffunction-sections -mno-split-addresses.
 * Keeping the real left/right rotation branches raises the unified-call
 * draft672 to712 bytes. Separating the initial sentinel counter removes its
 * accidental long lifetime. Remaining: configuration-array bases are kept in
 * registers, whereas retail emits each absolute halfword store separately;
 * vector/record pointers and saved-register priorities also differ.
 * Reopen with independently measured complete global identities or a valid
 * narrow address-model witness. No fabricated scalar/array SDA declarations,
 * volatile stores or individual assembler aliases were attempted.
 * All three scratch vectors occupy16 bytes. A7A00 initializes xyz only; CC0
 * ignores its second input's w lane. Preserve this real initialization rather
 * than invent a w store. Raw producer/consumer proof is recorded privately.
 */
#include "common.h"

/* Measured record width is five full vectors (80 bytes); owner counts are
 * not asserted by these incomplete declarations. */
typedef struct { float point[5][4]; } BeamPath;
extern BeamPath D_L00_00247310[] NOT_SDA;
extern short D_L00_001B2AE0[] NOT_SDA;
extern short D_L00_001B2AF0[] NOT_SDA;
extern short D_L00_001B2B00[][2] NOT_SDA;
extern short D_L00_001B2B10[][2] NOT_SDA;
extern float D_0018A560[][4] NOT_SDA;
extern void func_00282D30(void *,void *,float);
extern float func_002A7878(float,float);
extern void func_002ACEC0(void *,void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern float func_00283CE0(int);
extern void func_00282D08(void *,void *,void *,float);
extern void func_002A7A00(void *,float,float);

/* The first32-bit incoming GPR is unused; the second points to a full16B
 * origin. Only the xyz lanes of random displacement are consumed: A7A00
 * writes12 bytes, and CC0's vadd.xyz ignores the fourth displacement lane
 * while preserving the initialized interpolated point's w lane. */
void func_L00_003D2C00(int unused,float *origin)
{
    float direction[4] __attribute__((aligned(16)));
    float endpoint[4] __attribute__((aligned(16)));
    float displacement[4] __attribute__((aligned(16)));
    int i;
    {
        int n;
        for(n=3;n>=0;n--) D_L00_001B2AE0[n]=-1;
    }
    D_L00_001B2B00[0][0]=8;
    D_L00_001B2B00[0][1]=4;
    D_L00_001B2B00[1][0]=8;
    D_L00_001B2B00[1][1]=4;
    D_L00_001B2B00[2][0]=8;
    D_L00_001B2B00[2][1]=4;
    D_L00_001B2B10[0][0]=4;
    D_L00_001B2B10[0][1]=2;
    D_L00_001B2B10[1][0]=4;
    D_L00_001B2B10[1][1]=2;
    D_L00_001B2B10[2][0]=4;
    D_L00_001B2B10[2][1]=3;
    i=4;
    while(i<6) {
        int j,next;
        float angle;
        D_L00_001B2AE0[i]=8;
        D_L00_001B2AF0[i]=255;
        qcopy(D_L00_00247310[i].point[0],origin);
        func_00282D30(direction,D_0018A560[2],32.0f);
        angle=func_002A7878(10.0f,24.0f)*0.01745329424738884f;
        func_002ACEC0(direction,direction,D_0018A560[0],-angle);
        angle=func_002A7878(22.0f,30.0f)*0.01745329424738884f;
        if(i==5)
            func_002ACEC0(direction,direction,D_0018A560[1],-angle);
        else
            func_002ACEC0(direction,direction,D_0018A560[1],angle);
        func_00282CC0(endpoint,origin,direction);
        qcopy(D_L00_00247310[i].point[4],endpoint);
        next=i+1;
        for(j=1;j<4;j++) {
            float fraction=func_00283CE0(j)/func_00283CE0(4);
            func_00282D08(D_L00_00247310[i].point[j],origin,endpoint,fraction);
            fraction+=fraction;
            func_002A7A00(displacement,fraction,fraction);
            func_00282CC0(D_L00_00247310[i].point[j],D_L00_00247310[i].point[j],displacement);
        }
        i=next;
    }
}
