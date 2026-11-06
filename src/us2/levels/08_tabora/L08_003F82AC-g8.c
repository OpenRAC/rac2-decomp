/* func_US2_L08_003F82AC, the USA v2.00 copy of func_L08_003F6E18: the same C, where the 0x88 float
   is read as a member of D_00189E20 and a block runs after func_L01_002EABA8 while the mode word is
   0x31 and the level's object is class 0xEEF. D_00139568_1 is D_00139568: gcse numbers its reaching
   registers by a hash of the symbol's name, and the tied $s4/$s5 pair follows that order. */
#include "common.h"
typedef struct {
    u8 pad00[0x20]; u8 state; u8 pad21[0x68-0x21];
    void *data; u8 pad6c[0xB0-0x6c]; u8 id; u8 padB1;
    s16 index; u8 padB4[0x100-0xB4];
} TaboraMoby;
extern TaboraMoby *D_L08_001B29DC;
extern u8 D_001395B8[], D_00139568_1[];
typedef struct { u8 pad[0x50]; int flags[2]; } TaboraProgress;
extern TaboraProgress D_00139768;
typedef struct { int state; u8 pad[0x24]; float value; } FlareStatus;
extern FlareStatus D_L08_001CA080;
typedef struct { u8 pad[4]; u8 count; u8 rest[0xDB]; } StageStatus;
extern u8 D_L08_0026CCF0[];
typedef struct { u8 pad[0x464]; u8 flags[1]; } TaboraLevelFlags;
extern TaboraLevelFlags D_L08_0021EAF0, D_L08_0021DE80;
extern u8 D_0019B2E8[], D_0019B4A8[], D_0019B278[];
extern u8 D_L08_001B2840[] MACRO_ADDR;
extern int D_001A79F0, D_0018CD20 NOT_SDA;
extern u8 D_001A7AF8[] __attribute__((sda));
extern int D_L08_0021F758 NOT_SDA, D_L08_001A8F00, D_L08_001B2514;
extern float D_L08_001B2420 __attribute__((sda));
extern float D_L08_001B9E08 NOT_SDA;
extern char D_L08_001BFD00[], D_00189EA0[];
extern char D_L08_002B53E0[], D_L08_001B0BE8[], D_L08_001B0C00[], D_L08_001B0C28[], D_L08_001B0C50[], D_L08_001B0C70[], D_L08_001B0C90[], D_L08_001B0CC0[], D_L08_001B0CF0[], D_L08_001B0D08[], D_L08_001B0D30[], D_L08_001B0D48[], D_L08_001B0D70[], D_L08_001B0DA8[];
extern void func_0026FEB8(char *, ...);
extern void func_L00_002B9D60(void *,void *,int,int);
extern void func_L00_002E6CF0(void *,void *);
extern int func_00287FF8(int,int);
extern void func_00288508(int);
extern int func_00288AA0(void *,int);
extern int func_00288BE8(void *);
extern int func_00288D58(void);
extern int func_00288E18(int,int);
extern void func_L01_002EABA8(int,int,int,int,int);
extern void func_L08_0030A8F8(int);
extern void func_L00_00303530(int,int);
extern int func_0029B3E0(int,int);
extern void func_0029F338(void *);
extern void func_002A7750(void *,int,int);
extern int func_L00_00329520(void *,int);
extern void func_L08_0036EFC8(void);
extern void func_L00_003672F8(void);
extern void func_002F5CC8(void);
extern int func_002F5D10(void);
extern void func_L08_003F6D30(void *);
extern float func_L08_003F76C0(void *);
extern void func_L08_003F77C0(void *);
extern void func_L08_003F79E0(void *);
extern void func_L08_003F7A48(void *);
extern void func_L05_0030C930(int,int);
typedef struct { u8 pad[0x88]; float value; u8 pad8c[0x1830-0x8C]; u8 *object; u8 pad1834[0x2294-0x1834]; int mode; } LevelGlobals;
extern LevelGlobals D_00189E20;
extern int D_0018D074 NOT_SDA;
extern float D_L08_001B3244;

static __inline__ int TaboraStageComplete(void)
{
    int threshold;
    if (func_00288D58()) threshold = 4;
    else threshold = 1;
    if (((StageStatus *)D_L08_0026CCF0)[D_00139568_1[0xA]].count >= threshold) return 1;
    return 0;
}

void func_US2_L08_003F82AC(u8 *o)
{
    u8 *s = *(u8 **)(o+0x68);
    TaboraMoby *p;
    int mode;
    int bits;
    unsigned int seen;
    switch ((u8)o[0x20]) {
    case 0:
        o[0x30]=255;
        *(u16 *)(o+0x96)=0;
        if (!D_001395B8[0x1C]) func_L00_003672F8();
        if (*(int *)(s+4)!=-1 && D_00189E20.value < D_L08_001CA080.value) {
            p=(D_L08_001B29DC+*(int *)(s+4));
            if (p->state || (D_0019B2E8[p->id+(D_001A79F0<<4)]&128) ||
                D_L08_0021EAF0.flags[p->index])
                goto relocate_child;
            bits = D_0019B4A8[(p->index>>1)+(D_001A79F0<<10)];
            if (((u16)p->index & 1) ? ((bits >> 4) & 7) : (bits & 7)) {
relocate_child:
                func_0026FEB8(D_L08_002B53E0);
                func_L00_002B9D60((u8 *)p+0x10,(u8 *)p+0xF0,0,1);
                func_002A7750(o,5,-1);
            }
        }
        if (TaboraStageComplete()) {
            if (*(int *)(s+0x30)!=-1) {
                func_0029F338((D_L08_001B29DC+*(int *)(s+0x30)));
                *(int *)(s+0x30)=-1;
            }
            if (D_00189E20.value < D_L08_001CA080.value) {
                mode=0;
                func_0026FEB8(D_L08_001B0BE8);
                D_L08_0021F758=0;
                func_L00_003672F8();
                func_002A7750(o,5,-1);
            } else {
                mode=1;
                func_0026FEB8(D_L08_001B0C00);
                D_L08_0021F758=mode;
                func_002A7750(o,5,-1);
            }
            func_L08_003F6D30(o);
        } else if (!(D_00139768.flags[0]&0x80000) || !(D_00139768.flags[1]&0x100000)) {
            mode=1;
            func_0026FEB8(D_L08_001B0C28);
            if (func_00288AA0(D_L08_001BFD00,0x53)) {
                func_00288AA0(D_L08_001BFD00,0x54);
                func_00288BE8(D_L08_001BFD00);
                func_002F5CC8();
                func_L00_003672F8();
                func_002A7750(o,1,-1);
            }
        } else if (D_00139768.flags[1]&0x200000) {
            mode=0;
            func_0026FEB8(D_L08_001B0C50);
            D_L08_0021F758=0;
            func_L00_003672F8();
            func_002A7750(o,3,-1);
        } else {
            mode=0;
            func_0026FEB8(D_L08_001B0C70);
            func_L00_003672F8();
            func_002A7750(o,1,-1);
            *(u16 *)(o+0x96)=6;
        }
        if (D_001A7AF8[0x15] && *(int *)(s+0x20)!=-1 &&
            (D_L08_001B29DC+*(int *)(s+0x20))->state!=0xFE &&
            (D_L08_001B29DC+*(int *)(s+0x20))->state!=0xFD &&
            *(int *)(s+0x24)!=-1 &&
            (D_L08_001B29DC+*(int *)(s+0x24))->state!=0xFE &&
            (D_L08_001B29DC+*(int *)(s+0x24))->state!=0xFD) {
            func_0026FEB8(D_L08_001B0C90);
            if (!D_0019B278[*(int *)D_L08_001B29DC[*(int *)(s+0x24)].data+(D_001A79F0<<2)]) {
                mode=1;
                D_L08_0021F758=mode;
                func_0026FEB8(D_L08_001B0CC0);
                {
                    TaboraMoby *replacement = D_L08_001B29DC + *(int *)(s+0x20);
                    func_L00_002B9D60((u8 *)replacement+0x10,(u8 *)replacement+0xF0,0,1);
                }
                func_L00_003672F8();
            }
            if (TaboraStageComplete()) {
                if (func_00288D58()) func_00287FF8(10,4);
                else func_00287FF8(10,1);
                func_L08_0030A8F8(1);
            }
            func_002A7750(o,5,-1);
        }
        func_0026FEB8(D_L08_001B0CF0,mode);
        func_L00_00303530(mode,0);
        func_L08_003F79E0(o);
        func_L08_003F77C0(o);
        break;
    case 1:
        if (!func_002F5D10() && *(u16 *)(o+0x96)>=6) {
            D_001395B8[0x19]=1;
            if (func_00288AA0(D_L08_001BFD00,0x55)) {
                func_00288BE8(D_L08_001BFD00);
                D_L08_0021F758=0;
                func_0026FEB8(D_L08_001B0D08);
                func_002F5CC8();
                D_L08_001B2514=1;
                D_L08_001B2420=1.2f;
                func_L08_0036EFC8();
                func_L00_00303530(0,0);
                func_002A7750(o,2,-1);
            }
        }
        break;
    case 2:
        if (!func_002F5D10() && *(u16 *)(o+0x96)>=6) {
            D_001395B8[0x1A]=1;
            func_0026FEB8(D_L08_001B0D30);
            func_0029B3E0(0,-1);
            func_002A7750(o,3,-1);
        }
        break;
    case 3:
        if (func_L00_00329520(D_00189EA0,*(int *)s)) {
            if (func_00288AA0(D_L08_001BFD00,0x56)) {
                func_00288BE8(D_L08_001BFD00);
                func_0026FEB8(D_L08_001B0D48);
                func_002A7750(o,4,-1);
            }
        }
        break;
    case 4:
        if (D_L08_001A8F00==2 && *(int *)(s+0x30)!=-1) {
            func_0029F338((D_L08_001B29DC+*(int *)(s+0x30)));
            *(int *)(s+0x30)=-1;
        }
        if (!func_002F5D10() && *(u16 *)(o+0x96)>=6) {
            if (func_00288D58()) func_00287FF8(10,4);
            else func_00287FF8(10,1);
            func_L08_0030A8F8(1);
            func_00288508(10);
            func_L08_003F6D30(o);
            if (*(int *)(s+8)!=-1) {
                p=D_L08_001B29DC + *(int *)(s+8);
                func_0026FEB8(D_L08_001B0D70);
                D_L08_0021DE80.flags[p->index]=p->id+2;
                {
                    int id = p->id;
                    if (id == 255 || (!(D_L08_001B2840[(u8)id] & 128) &&
                        (D_0019B2E8[(u8)id + (D_001A79F0 << 4)] & 128)))
                        D_L08_0021EAF0.flags[p->index]=id+2;
                }
            }
            func_0026FEB8(D_L08_001B0DA8);
            func_0029B3E0(0,-1);
            func_002A7750(o,5,-1);
        }
        break;
    }
    ++*(u16 *)(o+0x96);
    if (D_001395B8[0x1C]) {
        seen = (unsigned)D_0018CD20 & (1 << D_001A79F0);
        if (!seen) func_00288E18(0x9F9,0x50);
    }
    func_L01_002EABA8(0xA3A,0x91,0,*(int *)(s+0xC),-1);
    if (D_00189E20.mode==0x31 && D_00189E20.object && *(short *)(D_00189E20.object+0xAA)==0xEEF) {
        if (D_0018D074>=0) func_00288E18(0xA40,0x97);
        {
            float scale = -65.0f;
            func_L05_0030C930((int)(D_L08_001B3244 * scale + 0.5f), 2);
        }
    }
    if (D_L08_001CA080.state==1) {
        D_L08_001B9E08=func_L08_003F76C0(o);
        func_L00_002E6CF0(func_L08_003F7A48,o);
    }
}
