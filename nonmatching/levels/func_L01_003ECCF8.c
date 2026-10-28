/* Nonmatching: US/US2 624/644 bytes; absent from PAL. Default profile.
 * Five attempts. Scoped persistence offset arithmetic reproduces the first
 * conditional byte update exactly; the color expression also now agrees.
 * The visibility nibble tests are merged into one shared exit by jump
 * optimization, saving five words but changing branch/GPR order. Explicit
 * branch-local boolean and goto forms do not recover retail; the narrow
 * keep-block-order and no-thread-jumps controls tie byte for byte.
 * Reopen with an independently supported control-flow hypothesis. Local
 * point[4] is fully produced by FCC0 and consumed through full-vector reads.
 * E5DA0 returns an integer index (four 32-bit GPR arguments); the float
 * math inputs/return banks and CF0 integer return are verified from retail.
 */
#include "common.h"

/* Only measured fields of the existing hero allocation are described here. */
extern struct {
    unsigned char reserved00[0x80];
    float position[4];
    unsigned char reserved90[0x33C-0x90];
    unsigned char *owner;
    int active;
} D_00189E20 NOT_SDA;
extern int D_001A79F0 NOT_SDA;
extern int D_001A79F0_gp SDATA(D_001A79F0);
extern unsigned char D_0019B4A8[] NOT_SDA;
extern unsigned char D_L01_0021E4B0[] NOT_SDA;
extern unsigned char *D_L01_001B255C;
extern unsigned char *D_L01_001B255C_gp SDATA(D_L01_001B255C);
extern float func_00283B98(float,float);
extern void func_0029FCC0(void *,int,void *);
extern float func_00282E80(void *,void *);
extern float func_00283198(float);
extern int func_00283CF0(float);
extern int func_002E5DA0(int,int,void *,int);

typedef struct {
    int linkedObject;
    float angle;
    int announced;
} OozlaActivation;

void func_L01_003ECCF8(unsigned char *object)
{
    float point[4] __attribute__((aligned(16)));
    OozlaActivation *state=*(OozlaActivation **)(object+0x68);
    if(!state) return;
    state->angle=func_00283B98(state->angle,0.10471977293491364f);
    if(object[0x20]==0) {
        float distance;
        int shade;
        func_0029FCC0(object,0,point);
        distance=func_00282E80(D_00189E20.position,point);
        state->announced=0;
        if(D_00189E20.owner==object && D_00189E20.active && distance<0.5f) {
            unsigned short flags=*(unsigned short *)(object+0xB2);
            if(flags&1) {
                unsigned char *entry=D_0019B4A8+(((short)flags>>1)+(D_001A79F0_gp<<10));
                unsigned char value=*entry;
                if(((value>>4)&7)!=7) *entry=value+0x10;
            } else {
                unsigned char *entry=D_0019B4A8+(((short)flags>>1)+(D_001A79F0_gp<<10));
                unsigned char value=*entry;
                if((value&7)!=7) *entry=value+1;
            }
        }
        if(object[0xB0]!=255) {
            unsigned short flags=*(unsigned short *)(object+0xB2);
            if(!D_L01_0021E4B0[0x464+(short)flags]) {
                int value=D_0019B4A8[((short)flags>>1)+(D_001A79F0<<10)];
                if(flags&1) {
                    if(!((value>>4)&7)) goto visible;
                } else if(!(value&7)) goto visible;
            }
            {
                int enabled=1;
                object[0x20]=enabled;
                object[0xBC]=enabled;
                if(state->linkedObject!=-1)
                    D_L01_001B255C_gp[(state->linkedObject<<8)+0xBC]=enabled;
            }
        }
visible:
        shade=func_00283CF0((func_00283198(state->angle)*4.0f-3.0f)*128.0f);
        if(shade>128) shade=128;
        else if(shade<32) shade=32;
        {
            unsigned int green=(shade<<8)|0x80000000;
            unsigned int blue=shade<<16;
            blue|=green;
            *(unsigned int *)(object+0x78)=blue|shade;
        }
    } else {
        if(!state->announced) {
            func_002E5DA0(0,0,object,0x8A1);
            state->announced=1;
        }
        *(unsigned int *)(object+0x78)=0x80208010;
    }
}
