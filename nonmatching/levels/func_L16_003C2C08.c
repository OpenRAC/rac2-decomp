/* Retained reconstruction; not linked. GPT-6.1 Sol high, 29 October 2026.
 * Profile: -O2 -G8 -ffunction-sections, dedicated -g8.c unit.
 * Current pinned v2 worker toolchain, USA v1.01: 1772/1776 bytes, 0/2 places.
 * Earlier 1776-byte draft: 50 identical unrelocated disassembly rows; this
 * draft: 221. This is a source improvement, not a match or linked-build credit.
 * MACRO_ADDR on the frame counters reproduces their mixed GP/absolute reads
 * with a typed ObjectState. Keep D_0018CC7C NOT_SDA and the sound table split.
 * A typed effect-control view prevents its address being hoisted over the
 * loop; ascending i=0..1 reproduces the retail loop's saved-register lifetimes.
 * Distinct branch-local sound variables reproduce the retail a0/v1 pointers
 * and owner-test branch slots; sharing one variable loses those allocations.
 * Initial speed snapshot and short-circuit state->amount reads fix their
 * scheduling. qcopy_nc copies only origin, disjoint from the following fields.
 * Remaining: object s2 instead of s3, effect rotation s3 instead of s2,
 * count s3 instead of s5, and missing message-buffer s2=s1 copy at +0x544.
 * Initial flag-index temporaries, two effect-call argument moves and the
 * final idle-color store/move/load order also differ. First word mismatch +4.
 * Palette offsets from D_L16_001B02C0 prevent GP loads in nonbare slots;
 * the whole palette declaration remains a source hypothesis, not link proof.
 * Separate/common color calls, typed Moby, long buffer handles, reordered
 * pointer additions and merged message-pointer scopes did not close the body.
 * Reopen with evidence for the message-buffer handle lifetime and the
 * original color-input alias model; do not retry equivalent pointer wordings.
 * 1 November 2026: with s2/s3 exchanged only a handful of rows differ. Retail's
 * object is s3 because a third call-crossing local of the message block takes s2:
 * text s1 and `daddu s2,s1` after the name lookup, with the later a0 from s2.
 * Copies of text through a local, a late copy or (int) all fold (89 rows); no
 * local at all gives 94. Find what keeps that copy and the rotation closes.
 * Wrapping the state call in do/while(0) gives 1776 bytes and 78 rows, but with an
 * alignment nop and still no copy, so that block boundary is not the mechanism.
 * Required declarations are retained below. PAL/US2 were not checked here.
 */

#include "common.h"
typedef struct {
    int tableIndex; u8 pad04[12]; float origin[4];
    float angle, angularSpeed; int counter, timer; u8 pad30[16];
    int flags, sound; float amount;
} ObjectState;
#define F(p,o) (*(float *)((u8 *)(p)+(o)))
#define I(p,o) (*(int *)((u8 *)(p)+(o)))
extern u8 D_0019B2E8[];
extern u8 D_00188660[];
extern int D_001A79F0 MACRO_ADDR;
extern u16 D_0018CC7C NOT_SDA;
extern int D_L16_001A8FF0 MACRO_ADDR;
extern u8 *D_L16_001B2B1C __attribute__((sda));
extern float D_L16_001B02B0 __attribute__((sda));
extern float D_L16_001B02B8 __attribute__((sda));
extern u32 D_L16_001B02C0[] MACRO_ADDR;
extern u32 colorFirst SDATA(D_L16_001B02C0);
extern float D_L16_001B02BC MACRO_ADDR;

extern char D_L16_001B02D0[];
extern int D_L16_001B2648 MACRO_ADDR;
extern int D_L16_001B3814 MACRO_ADDR;
typedef struct {
    u8 pad[0x160]; float strength; int pad164;
    int duration, timer; u8 pad170[0x10];
    float damping; int pad184, lifetime;
} EffectControls;
extern EffectControls D_L16_001B99C0;
extern u8 D_L16_001A8F20[] MACRO_ADDR;
extern float D_L16_001B9B00[4];
extern void func_002A7750(u8 *,s32,s32);
extern float func_L16_003960E8(const u8 *);
extern void func_L14_004272D8(void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_002A8C28(u8 *,void *,int,int,int,int,float,float,float);
extern int func_002E5CF8(int,int,char *);
extern void func_002E59F8(s32);
extern int func_00288E18(int,int);
extern void func_L00_002E6CF0(void (*)(void *),void *);
extern void func_L16_003C32F8(void *);
extern void *func_002A9640(void *,u32,s32);
extern void func_00282CF0(void *,void *,void *);
extern void func_0032DA58(void *,void *,void *,float);
extern void func_002AB6D8(float *,float *);
extern void func_002B0A68(char *,int,float *,u8,float,float,float,float);
extern int func_002A8508(int,int);
extern s32 func_00288FB8(s32);
extern int func_00115DA8(char *,char *,...);
extern int func_L00_0030DD70(int,int);
extern int func_00282948(int *);
extern void func_002A0430(unsigned int);
extern void func_0029F338(void *);
extern float func_00283B98(float,float);
extern int func_L01_0031BC68(int,int,float);
void func_L16_003C2C08(u8 *object)
{
    float point[4],step[4],normal[4];
    char message[128];
    ObjectState *state=*(ObjectState **)(object+0x68);
    float amount,rate;
    int handle,count,i;
    u32 timer,oldTimer;
    switch (object[0x20]) {
    case 0: {
        float speed;
        if (D_0019B2E8[D_001A79F0*16+object[0xB0]]&0x80) goto remove;
        object[0x30]=255;
        *(u16 *)(object+0x32)=0x113;
        *(u16 *)(object+0x34)|=0x4000;
        qcopy_nc(state->origin,object+0x10);
        speed=D_L16_001B02B8*0.00029088825f;
        state->amount=0.0f;
        state->sound=-1;
        state->angularSpeed=speed;
        func_002A7750(object,1,-1);
        break;
    }
    case 1:
        if (!D_L16_001A8FF0) break;
        amount=func_L16_003960E8(D_L16_001B2B1C+(state->tableIndex<<8));
        if (amount!=0.0f || state->amount!=0.0f) {
            func_L14_004272D8(object);
            func_00282F20(point,object+0xE0,D_L16_001B02B0*amount*(F(object,0x2C)/F(*(u8 **)(object+0x24),0x24)));
            func_00282CC0(object+0x10,state->origin,point);
            if (amount<state->amount) func_002A8C28(object,object+0x10,0x10000,0,1,0,2.1f,3.0f,1.0f);
        }
        if (amount!=state->amount && amount!=1.0f && amount!=0.0f) {
            u8 *playingSound=D_00188660+state->sound*0x70;
            if (*(u8 **)(playingSound+0x88)!=object || !playingSound[0x74]) state->sound=func_002E5CF8(2,4,(char *)object);
        } else {
            handle=state->sound;
            if (handle!=-1) {
                u8 *stoppingSound=D_00188660+handle*0x70;
                if (*(u8 **)(stoppingSound+0x88)==object && stoppingSound[0x74]) func_002E59F8(handle);
            }
            state->sound=-1;
        }
        if (amount==1.0f && state->amount!=1.0f) func_00288E18(0x9EC,67);
        state->amount=amount;
        if (D_L16_001B3814!=D_L16_001B2648) {
            D_L16_001B3814=D_L16_001B2648;
            func_L00_002E6CF0(func_L16_003C32F8,object);
        }
        if (amount>=1.0f) {
            if (func_002A9640(object,0x10000,0)) {
                func_002E5CF8(0,0,(char *)object);
                object[0xA8]=255;
                func_002A7750(object,2,-1);
                D_0018CC7C=65535;
            }
        } else object[0xA8]=255;
        break;
    case 2:
        timer=*(u16 *)(object+0x96);
        oldTimer=timer++;
        *(u16 *)(object+0x96)=timer;
        if (oldTimer>=60) {
            func_00282F20(point,object+0xE0,-2.0f);
            func_00282F20(step,object+0xE0,5.0f);
            func_00282CC0(point,point,object+0x10);
            func_002A8C28(object,point,0x10000,0,1,0,6.0f,3.0f,1.0f);
            func_002E5CF8(1,0,(char *)object);
            for (i=0;i<2;i++) {
                func_00282CF0(normal,D_L16_001B9B00,point);
                func_00282F20(normal,normal,1.0f);
                func_0032DA58(object,point,normal,0.0f);
                func_00282CC0(point,point,step);
            }
            D_L16_001B99C0.damping=0.1f;
            D_L16_001B99C0.lifetime=90;
            D_L16_001B99C0.strength=0.2f;
            D_L16_001B99C0.duration=60;
            D_L16_001B99C0.timer=0;
            func_002AB6D8((float *)(object+0xC0),(float *)(object+0xF0));
            func_002B0A68((char *)object,0xFFF,(float *)D_L16_001A8F20,255,2.0f,4.0f,10.0f,20.0f);
            state->counter=0;
            state->timer=180;
            state->flags=0;
            I(object,0x98)=0;
            *(u16 *)(object+0x34)=(*(u16 *)(object+0x34)|0x41)&0xEFFF;
            count=func_002A8508(object[0x21],-1)-1;
            if (count!=0) {
                char *format=D_L16_001B02D0;
                char *text=message;
                handle=func_00288FB8(0x2F3A);
                func_00115DA8(text,format,(char *)handle,count);
                func_002A7750(object,4,-1);
                func_L00_0030DD70((int)text,180);
            } else {
                handle=func_00288FB8(0x2F3B);
                func_L00_0030DD70(handle,180);
                func_002A7750(object,5,-1);
            }
        } else {
            if (*(u16 *)(object+0x96)%20==10) func_002E5CF8(3,0,(char *)object);
        }
        break;
    case 4:
        if (func_00282948(&state->timer)) {
remove:
            func_0029F338(object);
            return;
        }
        break;
    case 5:
        if (func_00282948(&state->timer)) {
            if (object[0xB0]!=255) func_002A0430(object[0xB0]);
            func_0029F338(object);
            return;
        }
        break;
    }
    if (object[0x31]) {
        if (object[0x20]==2) {
            rate=func_00283B98(state->angle,D_L16_001B02BC*0.00029088825f);
            state->angle=rate;
            *(u32 *)(object+0x78)=func_L01_0031BC68(D_L16_001B02C0[2],D_L16_001B02C0[3],rate);
        } else {
            rate=func_00283B98(state->angle,D_L16_001B02B8*0.00029088825f);
            state->angle=rate;
            *(u32 *)(object+0x78)=func_L01_0031BC68(colorFirst,D_L16_001B02C0[1],rate);
        }

    }
    return;
}
