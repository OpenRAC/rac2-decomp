/* Nonmatching: US676/676 bytes, 0/1; absent from US2 and PAL.
 * Eight checks, including one unsupported -fno-if-conversion rejection.
 * Default profile. Measured hero fields recover the full saved-register set;
 * masking in separate source branches prevents the unwanted movn selection.
 * Remaining: early color literal/sentinel schedule, first signed-index GPRs,
 * mixed persistence-table address priorities, and tail store order. A common
 * color-base lifetime adds a saved register/40-byte frame and is rejected.
 * Broad GCSE off loses the measured hero-base retention; no-split-addresses
 * only improves the original untyped648-byte draft to660. No retained flags.
 * Reopen with real source-lifetime/address-model evidence. No local vectors;
 * ACBC8 reads a complete16-byte existing hero position. All record fields use
 * measured widths/offsets, and every real store/read is preserved.
 * B0CE0 returns integer status, L13_002CEF00 integer status, ACBC8 integer
 * predicate. The unused integer results retain truthful declarations.
 */
#include "common.h"

/* Measured prefix of the existing hero; allocation ownership is unspecified. */
extern struct {
    unsigned char reserved00[0x80];
    float position[4];
    unsigned char reserved90[0x1F2-0x90];
    short requestedAction;
    unsigned char reserved1F4[0x33C-0x1F4];
    unsigned char *owner;
    unsigned char reserved340[0x5B8-0x340];
    float value;
    unsigned char reserved5BC[0x2294-0x5BC];
    int currentAction;
} D_00189E20 NOT_SDA;
extern unsigned char D_0019B4A8[] NOT_SDA;
extern int D_001A79F0 NOT_SDA;
extern int D_001A79F0_gp SDATA(D_001A79F0);
extern unsigned char D_L17_0021EBB0[] NOT_SDA;
extern unsigned char *D_L17_001B2C1C;
extern unsigned char *D_L17_001B2C1C_gp SDATA(D_L17_001B2C1C);
extern float func_00283B98(float,float);
extern float func_00283198(float);
extern int func_00283CF0(float);
extern int func_002B3868(void *);
extern void func_002A7750(void *,int,int);
extern void func_L00_00429020(int);
extern void func_L00_003294F0(void *,int);
extern int func_002B0CE0(int,int,int);
extern int func_002ACBC8(void *,int);
extern int func_L13_002CEF00(int,int);

typedef struct {
    int item;
    float angle;
    int region;
    int linkedObject;
    float value;
} SmolgActivation;

void func_L17_0041EAA8(unsigned char *object)
{
    SmolgActivation *state=*(SmolgActivation **)(object+0x68);
    int shade;
    state->angle=func_00283B98(state->angle,0.10471977293491364f);
    shade=func_00283CF0(func_00283198(state->angle)*128.0f);
    if(shade>128) shade=128;
    else if(shade<32) shade=32;
    switch(object[0x20]) {
    case 0:
        if(func_002B3868(object)) *(unsigned short *)(object+0x34)|=0x10;
        func_002A7750(object,1,-1);
        break;
    case 1: {
        func_002B3868(object);
        if(D_00189E20.owner==object) {
            if(state->item!=-1) {
                unsigned short flags=*(unsigned short *)(object+0xB2);
                int value;
                if(D_L17_0021EBB0[0x464+(short)flags]) goto announce;
                value=D_0019B4A8[((short)flags>>1)+(D_001A79F0<<10)];
                if(flags&1) {
                    if((value>>4)&7) goto announce;
                } else if(value&7) goto announce;
                func_L00_00429020(state->item);
                {
                    unsigned short flags2=*(unsigned short *)(object+0xB2);
                    if(flags2&1) {
                        unsigned char *entry=D_0019B4A8+(((short)flags2>>1)+(D_001A79F0_gp<<10));
                        unsigned char old=*entry;
                        if(((old>>4)&7)!=7) *entry=old+0x10;
                    } else {
                        unsigned char *entry=D_0019B4A8+(((short)flags2>>1)+(D_001A79F0_gp<<10));
                        unsigned char old=*entry;
                        if((old&7)!=7) *entry=old+1;
                    }
                }
                if(state->linkedObject!=-1)
                    func_L00_003294F0(D_L17_001B2C1C_gp+(state->linkedObject<<8),1);
                state->item=-1;
            }
announce:
            func_002B0CE0(12,0x27F7,1);
            *(unsigned int *)(object+0x78)=(shade<<8)|0x80000000;
            D_00189E20.requestedAction=2;
            if(state->value!=0.0f) D_00189E20.value=state->value;
        } else
            *(unsigned int *)(object+0x78)=shade|0x80000000;
        break;
    }
    }
    if(state->region>=0 && func_002ACBC8(D_00189E20.position,state->region) &&
       D_00189E20.currentAction==0x82)
        func_L13_002CEF00(6,1);
}
