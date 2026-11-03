/* opus-1, Claude Opus 5.5 (xhigh) (v2130), USA v1.01, default -O2 -G0 profile.
 * Best check: 1588/1588 bytes; 0/28 placements match; ~85 instructions differ.
 * Builds on sol-high (v1177): typed archive/texture/moby records, incomplete sda
 * views for tied absolute accesses, int returns of func_002B7C10/func_00133580.
 * Size fix: retail keeps a copy of the class count (daddu v0,a2,zero) for the
 * UI-class index; `count = n++` on a user variable n makes that copy survive
 * cse (make_regs_eqv), giving the exact size. n++ after the uses: 1592 bytes.
 * Remaining: moby-special D_001D0E00 address reg (t1 vs a3); UI-class block keeps
 * &loadBuffers in s2 (retail s5), stores loadState.count late and loads
 * D_001CDB80[0] after the CE300/D0E00 stores (sched1 deps on the reg+reg stores);
 * D_001B1604 store vs header loads; func_00291CA8 arg order (retail a0 last);
 * size spill reload reg; C2B40/C2C40/F1D40 address order; sound-state -1/base
 * regs; 0xC000 in v1 (retail a1). Store reorders in the UI block tied or worse.
 * Inserting into src/game/002E7018.c: use `#define loadState (*(LoadState *)&D_00152C00)`
 * and `extern char D_0014B540[];` before the function, and drop the duplicate
 * D_00152C00/D_001B15A0/D_001B22B0/func_0011AEA0/func_002EAAA8/D_0014B540 externs
 * below. All other needed declarations follow.
 */
#include "common.h"
extern float D_001B15A0 __attribute__((sda));
extern int D_001B22B0 __attribute__((sda));
extern char D_00152C00[];
extern void func_0011AEA0(int),func_002EAAA8(void *,int *);
typedef struct { char pad[0x2c0]; int x,y;float time;char gap[0x1fc4];int flag; } LoadEngine;
extern LoadEngine loadEngine __asm__("D_00189E20_9");
typedef struct { char pad[0x1c]; union { int value; unsigned char bytes[4]; } count; short mode,selected; char gap[8];short a,b; char gap2[8]; unsigned long long packet; } LoadState;
#define loadState (*(LoadState *)D_00152C00)
extern char D_0014B540[];
extern void func_00290B48(),func_00282A60(),func_0027A9F0(),func_0027AB40(),func_002FC1D8(),func_0027D330(),func_00293000(),func_00291EC0(),func_00293890(),func_00292328(),func_00282A88(),func_00282B50(),func_0029F0C8(),func_0027B7E0(),func_002EA968();
extern int func_0029D4D0(),func_00282A18();
extern int func_002B7C10(int,int,int);
extern int func_00133580(int);
extern int func_00132828(void);
extern void func_002934B8(void *,void *);
extern void func_00291DE0(void *,int);
extern void func_00291CA8(void *,int,void *,int);
extern char D_001CE4E0[],D_001D1580[],D_001B1740[],D_001C2740[],D_001C2B40[],D_001C2C40[],D_001F1D40[];
extern int D_001A72F4[] __attribute__((sda));
extern int D_001A72D4[] __attribute__((sda));
extern int D_001A72D0[] __attribute__((sda));
extern int D_001B1B4C[] __attribute__((sda));
extern int D_001B1B40[] __attribute__((sda));
extern int D_001A7290[] __attribute__((sda));
extern char *D_001B1604[] __attribute__((sda));
extern int D_001B1B5C[] __attribute__((sda));
extern int D_001B1B6C[] __attribute__((sda));
extern int D_001B1D98[] __attribute__((sda));
extern int D_001B1D90[] __attribute__((sda));
extern int D_001B1D94[] __attribute__((sda));
extern int D_001B159C[] __attribute__((sda));
extern int D_001B1B74[] __attribute__((sda));
extern int D_001B2134[] __attribute__((sda));
extern int D_001B2138[] __attribute__((sda));
extern int D_001B213C[] __attribute__((sda));
extern int D_001B2140[] __attribute__((sda));
extern unsigned char *D_001B1B60[] __attribute__((sda));
extern unsigned char *D_001B1B64[] __attribute__((sda));
extern short D_001A7A18[] __attribute__((sda));
extern int D_001B1B4C_gp __asm__("D_001B1B4C") __attribute__((sda));
extern int D_001B1B40_gp __asm__("D_001B1B40") __attribute__((sda));
extern int D_001B159C_gp __asm__("D_001B159C") __attribute__((sda));
extern int D_001B15A4_gp __asm__("D_001B15A4") __attribute__((sda));
extern int D_001D0600[];
extern int D_001D0E00[];
extern char *D_001CDB80[];
extern short D_001CE300[];
extern unsigned long long D_001C4DC0[];
extern char D_001A91E0[];
extern int D_001ABEC0[] SDATA(D_001ABEC0);
extern int D_001B1D9C __attribute__((sda)),D_001B1DA0 __attribute__((sda));
extern int D_001B2130[] __attribute__((sda));
typedef struct {
 int texture, data, textureCount, textureInfo;
 int mobyCount, mobys, classCount, classes;
 int partCount, parts, pointCount, points;
 int classData, partData, textureData, partInfo;
 int unknown40, unknown44, sky;
 int unknown4c, unknown50, unknown54, unknown58, unknown5c, unknown60;
 int sound[5];
} ArchiveHeader;
typedef struct { int offset; unsigned short dimension, pad6; int pad8[2]; } TextureRecord;
typedef struct { int offset, id, special, padC; char map[16]; } MobyRecord;
typedef struct { char pad[0x18]; ArchiveHeader *header; char gap[0x1c]; char *firstClass; char gap2[0xc]; char *end; char gap3[0x24];char *uiClass;char gap4[4];char *uiInfo; } LoadBuffers;
extern LoadBuffers loadBuffers __asm__("D_001BAEC0");
extern char D_00188660[];
typedef struct { char pad[0x17b4]; unsigned int soundState; } SoundState;
typedef struct { char pad[0x28]; int left, right; } BankVolume;
void func_002EAB18(void) {
 char *base, *records, *p; unsigned char *entry;
 ArchiveHeader *header;
 TextureRecord *textures; MobyRecord *moby;
 int i=0,j,size; BankVolume *bank;
 loadEngine.time=-1.0f;
 loadState.mode=2; loadState.selected=-1;
 D_001B15A0=1.0f;D_001B22B0=0x100000;
 loadEngine.x=0;loadEngine.y=0;loadEngine.flag=0;
 D_001B15A4_gp=0;
 func_00290B48(); D_001A72D0[0]=D_001A72F4[0];D_001A72D4[0]=D_001A72F4[0];
 func_00282A60(D_001B1740,0x87654321,16);func_00282A60(D_001CE4E0,-1,0x2000);func_00282A60(D_001D1580,-1,0xf00);func_00282A60(D_001D0E00,0,0xf0);
 func_0027A9F0();func_0027AB40();func_002FC1D8();
 {
 char *disc=D_0014B540;
 int *sector=(int *)(disc+0x3e58);
 int *length=(int *)(disc+0x3e5c);
 int index=loadState.b*8;
 func_002B7C10((int)loadBuffers.header+0x400000,*(int *)(index+(int)sector)+*(int *)(disc+0x3e24),*(int *)(index+(int)length));
 }
 func_0027D330(6);func_00133580(0);func_0011AEA0(0);
 size=func_0029D4D0((int)loadBuffers.header+0x400000,(int)loadBuffers.header);func_0011AEA0(0);
 header=loadBuffers.header;
 func_00293000((char *)header+header->texture,header->textureCount,0,(char *)header+header->textureInfo);
 base=(char *)header+header->data;records=base+header->classData;textures=(TextureRecord *)((char *)header+header->classes);
 D_001B1B4C_gp=header->classCount;
 if(D_001B1B4C_gp>0) { TextureRecord *texture=textures; int *out=D_001D0600;do { int type=func_00282A18(texture->dimension);i++;*out=(int)records+texture->offset+(type<<28);texture++;out++; }while(i<D_001B1B4C[0]); }
 func_00291EC0(base+header->sky);moby=(MobyRecord *)((char *)header+header->mobys);D_001B1B40_gp=0;
 for(j=0;j<header->mobyCount;j++,moby++) {
 char *object=moby->offset?base+moby->offset:0;
 if(moby->special) {D_001C4DC0[0]=loadState.packet;D_001C4DC0[1]=0xFFA0000000E0ULL;D_001C4DC0[2]=0x0040000400004000ULL;func_00293890(object,0,D_001A91E0,moby->id);D_001D0E00[D_001B1B40[0]-1]=0xfffc0000;}
 else func_00293890(object,(char *)header+header->classes,moby->map,moby->id);
 }
 { int n=D_001B1B40[0]; int count; loadState.count.value=n; count=n++; D_001B1B40[0]=n;
 D_001CDB80[count]=loadBuffers.uiClass;D_001CE300[count]=0xd54;D_001CE4E0[0xd54]=loadState.count.bytes[0];D_001D0E00[count]=0xfffc0000;loadBuffers.firstClass=D_001CDB80[0]; }
 if(D_001A7290[0]!=D_001A7A18[0])func_00292328(D_001A7A18[0]);
 func_002934B8((void *)D_001CDB80[0],(void *)loadBuffers.uiInfo);D_001D0E00[0]=0xfffc0000;
 D_001B1604[0]=base+header->textureData;func_00291DE0((char *)header+header->points,header->pointCount);func_00291CA8((char *)header+header->partInfo,(int)base+header->partData,(char *)header+header->parts,header->partCount);
 p=(char *)loadBuffers.header+size;loadBuffers.end=p;
 func_00282A88(D_001C2B40,0x100);func_00282A88(D_001C2C40,0x180);func_00282A88(D_001C2740,0x400);func_00282B50(D_001C2740,D_001ABEC0,0x40);
 D_001B1B5C[0]=(int)p;func_00282A60(p,0,0x4000);p+=0x4000;
 entry=(unsigned char *)D_001B1B5C[0];D_001B159C_gp=(int)entry;func_0029F0C8(entry,0);entry[0x20]=0xfd;
 D_001B1B60[0]=(unsigned char *)D_001B159C[0]+0x100;D_001B1B60[0][0x20]=0xff;D_001B1B6C[0]=(int)p;p+=0x2000;D_001B1D98[0]=-1;D_001B1D90[0]=(int)p;D_001B1B64[0]=D_001B1B60[0]+0x3f00;D_001B1D94[0]=0;D_001B1D9C=0;
 func_00282A88(D_001F1D40,0x200);func_0027B7E0();D_001B1B74[0]=0x3c0;D_001B1DA0=0x1f4000;func_002EA968();{ SoundState *sound=(SoundState *)D_00188660; sound->soundState=0xffffffffU; }
 bank=(BankVolume *)(base+header->sound[4]+0x18);bank->left=0xc000;bank->right=0xc000;
 bank=(BankVolume *)(base+header->sound[3]+0x18);bank->left=0xc000;bank->right=0xc000;
 bank=(BankVolume *)(base+header->sound[2]+0x18);bank->left=0xc000;bank->right=0xc000;
 bank=(BankVolume *)(base+header->sound[1]+0x18);bank->left=0xc000;bank->right=0xc000;
 bank=(BankVolume *)(base+header->sound[0]+0x18);bank->left=0xc000;bank->right=0xc000;
 func_0011AEA0(0);func_002EAAA8(base+header->sound[4],&D_001B2140[0]);func_002EAAA8(base+header->sound[2],&D_001B2138[0]);func_002EAAA8(base+header->sound[3],&D_001B213C[0]);func_002EAAA8(base+header->sound[1],&D_001B2134[0]);func_002EAAA8(base+header->sound[0],&D_001B2130[0]);func_00132828();
}


