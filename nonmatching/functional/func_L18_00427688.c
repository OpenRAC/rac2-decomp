/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* GPT-6.1 Sol (high), task v1028, 29 October 2026. Nonmatching.
 * Pinned upstream profile: -O2 -G32 -Wa,-G32 -ffunction-sections
 *                          -frac2-qcopy -frac2-qcopy-barrier.
 * USA v1.01: 1212/1212 bytes, 0 of 3 places match; first mismatch +0x20.
 * Replaces the previous 1196-byte draft. All declarations are retained below.
 * Capture six scalar motion defaults before stores, preserving the real
 * seven-float global's extent. This recovers the default load/store sequence.
 * Unsigned state bytes, case 0xec0 before the shared 0xed4/0xee1 switch body,
 * and the nonzero-first final branch recover retail's later control flow.
 * Use the existing D_L18_0021E7B0[][0x464] view for the lookup at +0x464.
 * Snapshot f18 before the post-random stores. Reverse the independent short
 * and 5.0f stores to recover their scheduled order; destination pointer
 * declaration precedes the source for the full aligned position capture.
 * Remaining: missing initial object[0xb0] reload, initializer constant allocation
 * (QI/SI 9 has two producers), and early independent scalar-store scheduling.
 * Typed initial-state fields tie; named constants, byte/word value forwarding,
 * and disabling either scheduler worsen output. keep-block-order plus
 * no-null-pointer-checks gives identical bytes to the profile above.
 * Reopen with evidence for the original constant/field lifetimes.
 * No linked build or runtime validation; US2/PAL not checked in this task.
 */
#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));

typedef struct { float f0,f4,f8,fC,f10,f14,f18; } MotionDefaults;
extern MotionDefaults D_L18_001B1218 __attribute__((sda));
extern int D_001A79F0 __attribute__((sda));
extern unsigned char D_0019B2E8[];
extern unsigned char D_L18_0021E7B0[][0x464];
extern float func_002A7878(float,float);
extern void *func_002B60B0(unsigned char *,float,float,float,float);
extern int func_002A7820(int,int);
extern float func_L09_0033E7A0(int);
extern int func_L18_00427130(unsigned char *,int,int);
extern void func_L18_00426F78(unsigned char *);
extern void func_L18_00427010(unsigned char *);
extern int func_001163B0(void);
extern void func_L18_00426F28(unsigned char *,int,int,float);
extern void func_002A7750(unsigned char *,int,int);
int func_L18_00427688(unsigned char *object)
{
    unsigned char *state;
    float randomAngle;
    unsigned int ownerClass;
    if(object[0xb0]!=0xff && (D_0019B2E8[D_001A79F0*16+object[0xb0]]&0x80)!=0 && D_L18_0021E7B0[1][*(short *)(object+0xb2)]!=0) return 1;
    state=*(unsigned char **)(object+0x68);
    ownerClass=object[0x30];
    state[0x60]=10;
    *(float *)(state+0x6c)=0.1833333373f;
    *(float *)(state+0x70)=0.08333333582f;
    *(float *)(state+0x78)=0.008333333768f;
    *(float *)(state+0x8c)=0.4f;
    state[0xbd]=6;
    *(float *)(state+0x80)=0.4f;
    *(float *)(state+0x84)=0.4f;
    *(unsigned int *)(state+0x3e0)=ownerClass;
    state[0x66]=8; state[0x65]=9;
    *(float *)(state+0x7c)=0.004166666884f;
    state[0xbc]=3; state[0xc2]=5; state[0xc3]=11;
    state[0x28]=1;
    *(float *)(state+0x30)=0.75f;
    *(unsigned char *)(state+0x2f)=0xff;
    state[0x2a]=4; state[0x4a]=7;
    *(float *)(state+0x100)=0.7f;
    *(int *)(state+0x98)=9;
    state[0x61]=7; state[0x62]=8;
    *(unsigned char *)(state+0x67)=0xff;
    *(float *)(state+0x74)=0.004166666884f;
    state[0xbe]=5; state[0xbf]=11; state[0x2e]=1; state[0x4d]=0;
    *(float *)(state+0x104)=0.5f;
    *(float *)(state+0x108)=0.5f;
    *(float *)(state+0x10c)=0.5f;
    *(float *)(state+0x110)=1.22173059f;
    randomAngle=func_002A7878(20.0f,25.0f);
    { float speed=D_L18_001B1218.f18;
    *(float *)(state+0x134)=0.5f;
    state[0x1e8]=0; state[0x1e9]=0;
    *(float *)(state+0x130)=randomAngle*0.017453294f;
    *(float *)(state+0x12c)=speed*0.0002777777845f; }
    if(*(short *)(object+0xaa)==0xed4) *(float *)(state+0x100)=1.0f;
    if(*(short *)(object+0xaa)==0xee1) *(float *)(state+0x100)=1.1f;
    if(*(float *)(state+0x3c4)==0.0f && *(float *)(state+0x3c0)==0.0f && *(float *)(state+0x3cc)==0.0f && *(float *)(state+0x3c8)==0.0f) {
        float a=D_L18_001B1218.f0,b=D_L18_001B1218.f4;
        float c=D_L18_001B1218.f8,d=D_L18_001B1218.fC;
        float e=D_L18_001B1218.f10,f=D_L18_001B1218.f14;
        *(float *)(state+0x3c4)=a;
        *(float *)(state+0x3c0)=b;
        *(float *)(state+0x3cc)=c;
        *(float *)(state+0x3c8)=d;
        *(float *)(state+0x3d4)=e;
        *(float *)(state+0x3d0)=f;
        *(float *)(state+0x3dc)=e;
        *(float *)(state+0x3d8)=f;
    }
    func_002B60B0(object,*(float *)(state+0x3c4)*0.0002777777845f,*(float *)(state+0x3c0)*0.016666668f,*(float *)(state+0x3d4)*0.000004848137451f,*(float *)(state+0x3d0)*0.0002908882452f);
    randomAngle=func_002A7878(20.0f,40.0f);
    *(short *)(state+0x1e4)=120; *(short *)(state+0x1e2)=180;
    *(float *)(state+0x1dc)=randomAngle*0.017453294f;
    {
        void *initialPosition=state+0x1f0;
        void *position=object+0x10;
        qcopy(initialPosition,position);
    }
    *(float *)(state+0x200)=*(float *)(state+0x100);
    *(float *)(state+0x20c)=5.0f;
    *(float *)(state+0x210)=5.0f;
    *(int *)(state+0x37c)=*(int *)(state+0x360);
    *(short *)(state+0x392)=func_002A7820(0,45);
    func_L09_0033E7A0(*(int *)(state+0x368));
    func_L09_0033E7A0(*(int *)(state+0x13c));
    func_L09_0033E7A0(*(int *)(state+0xcc));
    func_L09_0033E7A0(*(int *)(state+0x380));
    func_L09_0033E7A0(*(int *)(state+0x384));
    *(int *)(state+0x13c)=*(int *)(state+0x380);
    func_L18_00427130(object,*(int *)(state+0x36c),-1);
    if(state[0x399]!=0) state[0x399]=1;
    func_L18_00426F78(object);
    func_L18_00427010(object);
    switch(*(short *)(object+0xaa)) {
    case 0xec0: state[0x39b]=0; *(int *)(state+0x1c)=0; break;
    case 0xed4:
    case 0xee1: state[0x39b]=2; break;
    }
    func_L18_00426F28(object,func_001163B0()&1,0,1.0f);
    if(state[0x3e8]!=0) {
        func_002A7750(object,0,1);
        *(int *)(object+0x48)=0;
    } else if(state[0x39c]!=0) {
        object[0x31]=0;
        *(unsigned short *)(object+0x34)|=1;
        func_002A7750(object,0,2);
    } else func_002A7750(object,2,2);
    return 0;
}
