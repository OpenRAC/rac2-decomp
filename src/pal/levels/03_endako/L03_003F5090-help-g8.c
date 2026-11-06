/* func_PAL_L03_003F5090, the PAL copy of func_L03_003F09C0: the same C, where each frame count
 * goes through the 50 Hz scale and its limits fall by a sixth. The scale divides by a register,
 * so its zero test stays wherever the division itself is reused: both `prev < scale` arms keep
 * two tests, which is why neither timer holds the scaled value in a local as USA's does.
 *
 * Its own unit: -G8 for the $gp-relative words and -frac2-zero-ti-por (config/cflags.txt) for
 * the local quadword clear, which retail keeps as `por` + `sq`.
 *
 * Two timers decide the shape of the help tests. `scaled - prev > 100` tests the long arm first:
 * the arm's cross-jumped tail then ends in a jump to a label where v0 is live, so reorg annuls
 * the `bnel` slot. The history[138] test is `!count && near`, else the timer, as near's failure
 * reaches the timer test in retail.
 */
#include "common.h"

typedef struct {
    u8 prefix[0x80]; float position[4];
    u8 pad90[0x128]; int field1B8;
    u8 pad1BC[0x20D8]; int field2294;
    u8 pad2298[0x1C]; u8 field22B4;
} Hero;
extern Hero D_00189E20;
typedef union {
    u8 bytes[0xA3];
    struct { u8 pad[0x78]; unsigned char bit0:1; unsigned char other:7; } bits;
} Flags;
extern Flags D_001395B8;
typedef struct { u8 pad00[0x70]; u32 field70; u8 pad74[0x7C]; u16 fieldF0; u16 padF2; u32 fieldF4; } HelpState;
extern HelpState D_0018C750;
/* Subtitle history records: count, last frame, and per-level flags. */
typedef struct { u16 count, pad; u32 time, levels; } SubtitleHistory;
extern SubtitleHistory D_0018C958[];
typedef struct {
    int active; u8 pad04[0x20]; int key; int type;
} VoiceState;
extern VoiceState D_L03_00282078;
extern u8 D_L03_001BFB80[];
extern u8 *D_L03_001B2B0C[] __attribute__((sda));
extern u8 *D_L03_001B2A1C[] __attribute__((sda));
extern u16 *D_L03_001FB5A0[];
extern int D_L03_001B2A38 __attribute__((sda));
extern int D_L03_001B0F20 __attribute__((sda));
extern u32 D_001A7390[] __attribute__((sda));
extern int D_001A79F0;
extern int D_L03_001B2548 __attribute__((nosda));
/* The published map identifies the persistent save block at this base. */
typedef struct { u8 pad00[0x12]; u8 field12; u8 pad13[0xFA]; u8 mapDataSet; u8 pad10E[0xD804 - 0x10E]; } PlayerProgress;
extern PlayerProgress D_001A79F8 __attribute__((sda));
extern u8 D_001A7BED[] __attribute__((sda));
extern void func_L00_003672F8(void);
extern void func_PAL_L00_002B9CD8(void *,void *,int,int);
extern int func_002AD860(int);
extern void func_0029F338(void *);
extern void func_002A7750(void *,int,int);
extern int func_002ACBC8(void *,int);
extern int func_00288AA0(void *,int);
extern int func_00288BE8(void *);
extern void func_002F5CB8(void *,void *);
extern void func_PAL_L03_003F5C58(void *);
extern int func_00282948(void *);
extern int func_PAL_00289730(int,int);
extern void func_00288D90(void);
extern void func_PAL_L01_002EBFB8(int,int,int,int,int);
extern float func_00282E48(void *,void *);
extern int func_L03_003112F8(void);
extern void func_L00_002E6CF0(void *,void *);
extern void func_L00_003E4948(void *);
#define I(p,n) (*(int *)((p)+(n)))
void func_PAL_L03_003F5090(u8 *entity) {
    u8 *state = *(u8 **)(entity+0x68);
    int mode = entity[0x20];
    u16 *p;
    u8 *record;
    union { float f[4]; unsigned int q __attribute__((mode(TI))); } point;
    switch (mode) {
    case 0:
        entity[0x30] = 0xFF;
        I(state,0x74) = 0;
        if (D_001A79F8.mapDataSet) {
            if (!D_001395B8.bytes[0xD]) {
                u8 *entry;
                func_L00_003672F8();
                entry = D_L03_001B2B0C[0] + I(state,0x70)*0x80;
                func_PAL_L00_002B9CD8(entry+0x30,entry+0x70,0,1);
                func_002AD860(13);
            }
            if (D_001A79F8.mapDataSet) {
                for(p=D_L03_001FB5A0[I(state,0x80)];
                    (I(state,0x80)&255)!=255 && I(state,0x80)<=D_L03_001B2A38 && p &&
                    ((p != 0 && (short)p[-1]>=0) || p==D_L03_001FB5A0[I(state,0x80)]); p++) {
                    record = D_L03_001B2A1C[0] + ((*p&0x7fff)<<8);
                    if(!record) break;
                    func_0029F338(record);
                }
            }
        }
        func_002A7750(entity,1,-1);
        break;
    case 1:
        if (!D_001395B8.bytes[0xD] && func_002ACBC8(D_00189E20.position,I(state,0x6C)))
            D_001395B8.bytes[0xD] = mode;
        if (!D_001395B8.bytes[9] && func_002ACBC8(D_00189E20.position,I(state,0x4C)) && func_00288AA0(D_L03_001BFB80,0x34)) {
            func_00288BE8(D_L03_001BFB80);
            D_001395B8.bytes[9]=1;
            func_002F5CB8(func_PAL_L03_003F5C58,entity);
        }
        if (!D_00189E20.field22B4 && func_002ACBC8(D_00189E20.position,I(state,8))) {
            if (func_00282948(state+0x60)) {
                func_PAL_00289730(0x9CB,0x22);
                I(state,0x60)=500;
            }
        } else if (func_002ACBC8(D_00189E20.position,I(state,0xC))) {
            if(D_0018C958[34].count!=65535) {
                D_0018C958[34].count=65535;
                if (D_L03_00282078.active || D_L03_00282078.key!=-1) {
                    if (D_L03_00282078.type==0x22) func_00288D90();
                }
            }
        }
        if(func_002ACBC8(D_00189E20.position,I(state,0x10)) && !D_L03_00282078.active && D_L03_00282078.key==-1) {
            u32 prev = D_0018C958[35].time;
            if (((s32)D_001A7390[0] * 5 + 2) / 6 - prev > 100) {
                func_PAL_00289730(0x9CC,0x23);
                if (D_0018C958[35].time < ((s32)D_001A7390[0] * 5 + 2) / 6) D_0018C958[35].time = ((s32)D_001A7390[0] * 5 + 2) / 6;
            } else {
                if (prev < ((s32)D_001A7390[0] * 5 + 2) / 6) D_0018C958[35].time = ((s32)D_001A7390[0] * 5 + 2) / 6;
            }
        } else if(func_002ACBC8(D_00189E20.position,I(state,0x14))) {
            if(D_0018C958[35].count!=65535) {
                D_0018C958[35].count=65535;
                if(D_L03_00282078.active || D_L03_00282078.key!=-1) func_00288D90();
            }
        }
        if(func_002ACBC8(D_00189E20.position,I(state,0x18))) {
            if(((s32)D_001A7390[0] * 5 + 2) / 6-D_0018C958[36].time>2000) func_PAL_00289730(0x9CD,0x24);
        } else if(func_002ACBC8(D_00189E20.position,I(state,0x1C))) {
            D_001395B8.bytes[0xA2]=1;
            D_0018C958[36].count=65535;
            if(D_L03_00282078.active || D_L03_00282078.key!=-1) func_00288D90();
        }
        if(func_002ACBC8(D_00189E20.position,I(state,0x64)) && !D_0018C958[123].count) {
            D_001395B8.bytes[0xA2]=1;
            func_PAL_00289730(0xA24,0x7B);
        }
        func_PAL_L01_002EBFB8(0x9D3,0x2A,0,I(state,0x20),-1);
        if(func_002ACBC8(D_00189E20.position,I(state,0x24)) && ((D_001395B8.bytes[0x78] ^ 1) & 1)) {
            u32 prev=D_0018C958[131].time;
            if(((s32)D_001A7390[0] * 5 + 2) / 6-prev>900 || !prev) func_PAL_00289730(0xA2C,0x83);
            else if(prev<((s32)D_001A7390[0] * 5 + 2) / 6) D_0018C958[131].time=((s32)D_001A7390[0] * 5 + 2) / 6;
        }
        func_PAL_L01_002EBFB8(0x9D5,0x2C,0,I(state,0x40),-1);
        func_PAL_L01_002EBFB8(0x9E5,0x3C,2,I(state,0x54),-1);
        if(func_002ACBC8(D_00189E20.position,I(state,0x2C))) D_0018C958[43].count=65535;
        else if(func_002ACBC8(D_00189E20.position,I(state,0x28))) {
            if(D_00189E20.field2294==0x23 && D_00189E20.field1B8==1) ++I(state,0x30);
            if(I(state,0x30)>=3 && D_00189E20.field2294==0x23) func_PAL_00289730(0x9D4,0x2B);
        }
        if(D_00189E20.position[2]<155.5f) {
            point.q = 0;
            point.f[0]=400.0f;
            point.f[1]=222.0f;
            point.f[2]=155.0f;
            if(func_00282E48(D_00189E20.position,point.f)<24.0f) D_0018C958[37].time=0;
        }
        func_PAL_L01_002EBFB8(0x9CE,0x25,1,I(state,0x28),I(state,0x2C));
        func_PAL_L01_002EBFB8(0x9CE,0x25,3,I(state,0x28),I(state,0x2C));
        if(func_002ACBC8(D_00189E20.position,I(state,0x7C))) {
            if(!D_0018C750.fieldF0 || ((s32)D_001A7390[0] * 5 + 2) / 6-D_0018C750.fieldF4>60000) {
                u32 seen = D_0018C958[32].levels & (1 << D_001A79F0);
                if (!seen) func_PAL_00289730(0x9C9,0x20);
            }
        }
        if(!D_001A79F8.field12 && D_L03_001B2548>0 && !(D_L03_001B2548&0x7F) && !D_001A7BED[0] && !func_L03_003112F8()) {
            u32 count = D_0018C958[138].count;
            if (count < 3) {
                if (!count && func_002ACBC8(D_00189E20.position,I(state,0x78))) func_PAL_00289730(0xA33,0x8A);
                else if (((s32)D_001A7390[0] * 5 + 2) / 6 - D_0018C958[138].time > 30000) func_PAL_00289730(0xA33,0x8A);
            }
        }
        if(((s32)D_001A7390[0] * 5 + 2) / 6-D_0018C750.field70>90000 && func_002ACBC8(D_00189E20.position,I(state,0x78))) {
            u32 seen = D_0018C958[12].levels & (1 << D_001A79F0);
            if (!seen) func_PAL_00289730(0x9B5,0xC);
        }
        break;
    }
    if(D_L03_001B0F20) func_L00_002E6CF0(func_L00_003E4948,entity);
}
