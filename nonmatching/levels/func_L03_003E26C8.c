/* Nonmatching: US/US2 668/672 bytes, 0/8 placements; absent from PAL.
 * Seven checks (one malformed-scope compile corrected immediately). Profile:
 * -O2 -G0 -ffunction-sections -fno-rerun-loop-opt. Explicit local index scopes
 * and next-row progression recover the full register-save set, indexed madd
 * and 128-bit compiler spill. Strength-reduction off regresses to632 bytes;
 * no-split-addresses ties668 but disturbs the prologue and is rejected.
 * Remaining: init-loop multiply scheduling/address GPR, pointer spill-slot
 * priorities, branch hazard padding and tail byte/short initialization order.
 * No register pins, barriers or volatile accesses. Reopen on a new narrow
 * scheduling or source-lifetime witness. All vector inputs are complete16B;
 * AB6D8 reads existing64B object matrix, A91F0 produces complete quaternion16B.
 * Unknown table owners remain incomplete; measured strides are16 and24B.
 */
#include "common.h"

/* Incomplete owners preserve the measured 16-byte vector and 24-byte row
 * strides without asserting either allocation's total extent. */
extern float D_L03_0029BBF0[][4] NOT_SDA;
extern int D_L03_0024A7B0[][6] NOT_SDA;
extern float D_L03_001B36B0[] NOT_SDA;
extern unsigned short D_L03_001B0B5C;
extern unsigned short D_L03_001B0B5C_gp SDATA(D_L03_001B0B5C);
extern void func_00282F20(void *,void *,float);
extern float func_00282DB0(void *,void *);
extern void func_002AB6D8(void *,void *);
extern void func_002A91F0(void *,void *);
extern void func_001163A0(unsigned int);
extern void func_L03_003E2968(void *);
extern void func_L03_003E2C08(void *);
extern void func_L03_003E3308(void *);
extern void func_L03_003E3430(void *);

void func_L03_003E26C8(unsigned char *object)
{
    unsigned char *state=*(unsigned char **)(object+0x68);
    {
        int i=0;
        float (*direction)[4]=D_L03_0029BBF0;
        unsigned char *neighbors=state+0x30;
        for(;i<14;i++,direction++) {
            func_00282F20(*direction,*direction,1.0f);
            neighbors[i]=255;
        }
    }
    state[0x3E]=255;
    {
        int i=0;
        while(i<14) {
            int next=i+1;
            int j;
            for(j=5;j>=0;j--) D_L03_0024A7B0[i][j]=-1;
            i=next;
        }
    }
    {
        int i=0;
        while(i<14) {
            int j=0;
            int next=i+1;
            int *neighbor=D_L03_0024A7B0[i];
            for(;j<14;j++) {
                if(i!=j) {
                    float *direction=D_L03_0029BBF0[i];
                    float dot=func_00282DB0(direction,D_L03_0029BBF0[j]);
                    float threshold=0.5f;
                    if(direction[0]!=0.0f && direction[1]!=0.0f && direction[2]!=0.0f)
                        threshold=-0.1f;
                    if(threshold<dot) *neighbor++=j;
                }
            }
            i=next;
        }
    }
    func_002AB6D8(object+0xC0,object+0xF0);
    func_002A91F0(D_L03_001B36B0,object+0xF0);
    func_001163A0(*(short *)(state+0x6C));
    func_L03_003E2968(object);
    func_L03_003E2C08(object);
    func_L03_003E3308(object);
    func_L03_003E3430(object);
    {
        int i;
        unsigned char *values=state+0x10;
        for(i=0;i<16;i++) {
            state[i]=255;
            values[i]=0;
        }
    }
    state[0]=0;
    state[0x10]=1;
    *(short *)(state+0x66)=-1;
    *(short *)(state+0x5E)=0;
    *(unsigned short *)(state+0x68)=D_L03_001B0B5C_gp;
    *(short *)(state+0x50)=0;
    *(short *)(state+0x5C)=0;
    *(short *)(state+0x52)=0;
    *(short *)(state+0x62)=0;
    *(short *)(state+0x64)=0;
}
