/* Closer b, 2026-11-01: retail has a real next index: `lw s7, 0x88(sp)` at the loop end, set in the `continue` path's delay
 * slot and again after the test, and the inner loop has `daddu fp, s4`. `for (i = 0; i < 7; i = next)` with next set
 * in both paths gives retail's s7/fp and most of the head, at 2240 bytes; with the inner `nj` as well, 2228. Still open:
 * `addiu v0, sp, 0x30` is hoisted out of the outer loop here and not in retail; scoping the arrays doesn't change that. */
/* GPT-6.1 Sol (high effort), task v1398, USA v1.01.
 * Retained draft: 2244/2244 bytes, 0/27 places; first mismatch at +0x44.
 * Profile: -O2 -G8 -ffunction-sections, in a dedicated -g8.c unit.
 * The 0xF0 frame, GP cinematic/timestep accesses, saved-pose transfers,
 * scale stores and glow-color packing now agree with retail. The old draft
 * was 2212 bytes. All required declarations are below.
 * Remaining: i/j occupy fp/s7 rather than s7/fp; the matrix stack pointer is
 * hoisted before the outer loop, and the other stack-pointer spills differ
 * in scheduling. Initial mode/root setup, spawn-frame transfer registers,
 * joint-definition setup and modulo-120 setup still differ. Binding of
 * level-dependent externs has not been qualified past the first mismatch.
 * Measured: -g was neutral; -fno-rerun-loop-opt gave 2224 bytes/0xE0 frame;
 * qcopy+qcopy-barrier gave 2268 bytes. An explicit shared slot offset enlarged
 * the frame to 0x100. A typed slots[7] root shifted the working base by 0x1200
 * and gave 2236 bytes. A nested mode test fixed loop registers but grew to 2260.
 * Three source forms tied: this draft, scratch arrays scoped inside the outer
 * loop, and a typed partial slot view plus named modulo result (identical bytes).
 * Next: recover an independently supported full root/slot and scratch lifetime
 * model that changes loop allocation without adding artificial references.
 * Corresponding public RAC1 logic: src/overlays/shared/hero_animation_slots.c,
 * func_L00_0020FC18 in /home/t3/ref/rac1-decomp. RAC2 adds the default argument,
 * third attachment, cinematic scaling and quaternion/position blending.
 * No handwritten-code evidence. UpdateHeroItemAttachments already exists in
 * include/names.h. Final check.py: 0 of 27 places match; no linked build run.
 */
#include "common.h"
typedef struct {
    u8 prefix[0x12E8];
    int item2;
    u8 rest[0x2290-0x12EC];
    u8 *moby;
} AttachmentRoot;
extern AttachmentRoot D_00189E20 NOT_SDA;
extern int D_0018C0B0 NOT_SDA;
extern int D_L00_001A8F00[] __attribute__((sda));
extern u8 D_00139568[];
extern u8 D_L00_00262570[];
extern int D_L00_001A7CEC __attribute__((sda));
extern float D_L00_001A7CE4 __attribute__((sda));
extern float D_L00_001A7CE0 __attribute__((sda));
extern int D_L00_001B19C8[] __attribute__((sda));
extern u8 D_L00_0025BDC0[], D_L00_001B2E00[];
extern u8 D_L00_001A7D08[], D_L00_001B3000[];
extern u8 D_L00_001A7D18[], D_L00_001B3200[];
extern u8 D_L00_001A7D30[], D_L00_001B3300[];
extern u8 D_L00_001B2D80[], D_L00_0025C0F0[];
extern void func_002AB6D8(void *, void *);
extern void func_002A05A8(void *), func_002A0F48(void *), func_002A10E8(void *);
extern void func_L00_002B0528(void *, void *, int);
extern int func_L00_002ADED8(int), func_L00_002ADF10(int), func_L00_002ADF38(int);
extern void func_00283678(void *, void *), func_002AB028(void *);
extern void func_00283098(void *, void *, void *);
extern float func_00282E20(void *), func_00283248(float, float);
extern void func_L00_002AA200(void *, void *, int, int, int);
extern float func_002AA548(float *, float *, float, float, float, float);
extern void func_00282CC0(void *, void *, void *), func_00282D08(void *, void *, void *, float);
extern void func_002A91F0(void *, void *), func_00283810(void *, void *, void *, float), func_00283958(void *, void *);
extern u8 *func_0029EFD0(int);
extern void func_0029FC20(void *, int, void *), func_L00_002A7A10(void);
extern float func_00283CE0(int), func_00283198(float);
extern int func_00283CF0(float);

typedef int ItemQuad __attribute__((mode(TI)));
extern struct { u8 pad[0x2E0]; float scale0[3]; u8 gap[0x390-0x2EC]; float scale1[3]; } D_L00_0025BE10;
void func_L00_002B0968(int value)
{
    union { float direction[4]; ItemQuad saved[2]; } scratch __attribute__((aligned(16)));
    float quaternion[4] __attribute__((aligned(16)));
    float matrix[4][4] __attribute__((aligned(16)));
    int i,j,joint,first,second,third;
    u8 *moby;
    if (!value) value = D_0018C0B0;
    for (i=0;i<7;i++) {
        if ((D_L00_001A8F00[0]==2 || D_L00_001A8F00[0]==6)
            && !(i==2 && D_00189E20.item2==47) && i!=1 && i!=4) continue;
        { u8 *slot_mobys = (u8 *)&D_00189E20+i*80;
        for (j=0;j<3;j++) {
            if(j>0 && i!=1 && i!=3 && i!=4) break;
            moby=*(u8 **)(slot_mobys+0x1220);
            if (j==1) moby=*(u8 **)(slot_mobys+0x1224);
            else if (j==2) moby=*(u8 **)(slot_mobys+0x1228);
            if (moby) {
            u8 *slot = (u8 *)&D_00189E20+i*80;
            *(u64 *)(moby+0x38)=*(u64 *)(D_00189E20.moby+0x38);
            {
                u8 *def=D_L00_00262570+D_00139568[*(int *)(slot+0x1248)]*224;
                joint=*(int *)(def+0x10);
                if(i==1 && j==1) joint=3;
                if(slot[0x123A]) {
                    qcopy((u8 *)&D_00189E20+0x1200+i*80,(u8 *)&D_00189E20+0xC80+joint*64);
                    func_002AB6D8((u8 *)&D_00189E20+0xC50+joint*64,(u8 *)&D_00189E20+0x1210+i*80);
                    func_002A05A8(moby);
                    func_002A0F48(moby);
                    *(u16 *)(moby+0x34)&=0xFFFB;
                } else {
                    qcopy(moby+0x10,(u8 *)&D_00189E20+0xC80+joint*64);
                    if(!D_L00_001A7CEC || !*(int *)(def+0x1C)) {
                        if(i==0) func_L00_002B0528(moby,(u8 *)&D_00189E20+0xC50+joint*64,0);
                        first=func_L00_002ADED8(i);
                        second=func_L00_002ADF10(i);
                        third=func_L00_002ADF38(i);
                        if(!first && !second && !third) func_002A05A8(moby);
                        func_002A0F48(moby);
                        func_00283678(moby+0xC0,(u8 *)&D_00189E20+0xC50+joint*64);
                        if(!first && !second && !third) func_002AB028(moby+0xC0);
                        scratch.direction[0]=1.0f; scratch.direction[1]=0; scratch.direction[2]=0;
                        func_00283098(scratch.direction,scratch.direction,moby+0xC0);
                        *(float *)(moby+0xF4)=-func_00283248(func_00282E20(scratch.direction),scratch.direction[2]);
                        *(float *)(moby+0xF8)=func_00283248(scratch.direction[0],scratch.direction[1]);
                        func_002A10E8(moby);
                        *(u16 *)(moby+0x34)|=6;
                        if(first) {
                            func_L00_002AA200(D_L00_0025BDC0,D_L00_001B2E00,*(int *)(moby+0x24),0,value);
                            *(int *)(moby+0x44)=0; *(int *)(moby+0x40)=0;
                            *(u8 **)(moby+0x58)=D_L00_001B2E00; *(u8 **)(moby+0x5C)=D_L00_001B2E00;
                        } else if(second) {
                            func_L00_002AA200(D_L00_001A7D08,D_L00_001B3000,*(int *)(moby+0x24),0,value);
                            *(int *)(moby+0x44)=0; *(int *)(moby+0x40)=0;
                            *(u8 **)(moby+0x58)=D_L00_001B3000; *(u8 **)(moby+0x5C)=D_L00_001B3000;
                        } else if(third) {
                            int k;
                            if(D_L00_001A8F00[0]==2 || D_L00_001A8F00[0]==6) {
                                u8 *p=D_L00_001B2D80;
                                for(k=1;k>=0;k--,p+=64) { *(float *)(p+32)=1; *(float *)(p+36)=1; *(float *)(p+40)=1; }
                            } else {
                                u8 *saved_pose=D_L00_0025C0F0;
                                scratch.saved[0]=*(ItemQuad *)saved_pose;
                                scratch.saved[1]=*(ItemQuad *)(saved_pose+0xB0);
                                D_L00_0025BE10.scale0[0]=1; D_L00_0025BE10.scale0[1]=1; D_L00_0025BE10.scale0[2]=1;
                                D_L00_0025BE10.scale1[0]=1; D_L00_0025BE10.scale1[1]=1; D_L00_0025BE10.scale1[2]=1;
                            }
                            if(!j) {
                                func_L00_002AA200(D_L00_001A7D18,D_L00_001B3200,*(int *)(moby+0x24),0,value);
                                *(u8 **)(moby+0x58)=D_L00_001B3200; *(u8 **)(moby+0x5C)=D_L00_001B3200;
                            } else {
                                func_L00_002AA200(D_L00_001A7D30,D_L00_001B3300,*(int *)(moby+0x24),0,value);
                                *(u8 **)(moby+0x58)=D_L00_001B3300; *(u8 **)(moby+0x5C)=D_L00_001B3300;
                            }
                            *(int *)(moby+0x40)=0; *(int *)(moby+0x44)=0;
                            if(D_L00_001A8F00[0]==2 || D_L00_001A8F00[0]==6) {
                                u8 *p=D_L00_001B2D80;
                                for(k=1;k>=0;k--,p+=64) { *(float *)(p+32)=0.01f; *(float *)(p+36)=0.01f; *(float *)(p+40)=0.01f; }
                            } else {
                                *(ItemQuad *)D_L00_0025C0F0=scratch.saved[0]; *(ItemQuad *)(D_L00_0025C0F0+0xB0)=scratch.saved[1];
                            }
                        }
                    } else {
                        u8 *p;
                        func_002A05A8(moby);
                        if(!D_L00_001A7CEC || i!=0) func_002AB6D8((u8 *)&D_00189E20+0xC50+joint*64,moby+0xF0);
                        else func_L00_002B0528(moby,(u8 *)&D_00189E20+0xC50+joint*64,1);
                        p=(u8 *)&D_00189E20;
                        if(*(float *)(p+0x14F8)>0 && !*(int *)(p+0x1500)) {
                            float step=D_L00_001A7CE4*0.00027777778f;
                            func_002AA548((float *)(p+0x14F8),(float *)(p+0x14FC),0.0f,step,step,D_L00_001A7CE0*0.016666668f);
                            func_00283098(scratch.direction,p+0x14A0,p);
                            func_00282CC0(scratch.direction,scratch.direction,p+0x80);
                            func_00282D08(moby+0x10,moby+0x10,scratch.direction,*(float *)(p+0x14F8));
                            func_002A91F0(&scratch.saved[1],moby+0xF0);
                            func_00283810(quaternion,&scratch.saved[1],p+0x14C0,*(float *)(p+0x14F8));
                            func_00283958(quaternion,moby+0xC0);
                            func_002AB6D8(moby+0xC0,moby+0xF0);
                        }
                        func_002A0F48(moby); func_002A10E8(moby); *(u16 *)(moby+0x34)|=6;
                    }
                }
            }
            }
            if(i==3 && j==1 && moby) {
                u8 *p=(u8 *)&D_00189E20;
                u8 *effect;
                u8 *created;
                if(!*(u8 **)(p+0x131C)) {
                    *(u8 **)(p+0x131C)=func_0029EFD0(0x4B4);
                    if(!*(u8 **)(p+0x131C)) goto next_attachment;
                    *(int *)(*(u8 **)(p+0x131C)+0x78)=0x801432D7;
                    created=*(u8 **)(p+0x131C);
                    qcopy(created+0x10,p+0x80); qcopy(created+0xF0,p+0x90);
                    *(u16 *)(created+0x32)=0x40;
                    (*(u8 **)(p+0x131C))[0x31]=1; (*(u8 **)(p+0x131C))[0x30]=0;
                    *(u16 *)(*(u8 **)(p+0x131C)+0x34)=0;
                    *(float *)(*(u8 **)(p+0x131C)+0x2C)*=1.3f;
                    func_002A0F48(*(u8 **)(p+0x131C));
                }
                if(*(u8 **)(p+0x131C)) {
                effect=*(u8 **)(p+0x131C);
                if(((*(u16 *)(effect+0x34)^1)&1) != 0) {
                    float angle,range;
                    int red,green,blue,color_red;
                    func_0029FC20(moby,8,matrix);
                    qcopy(p+0x2010,matrix[3]); func_L00_002A7A10();
                    qcopy(effect+0x10,matrix[3]); func_00283678(effect+0xC0,matrix); func_002A0F48(effect);
                    *(u64 *)(effect+0x38)=*(u64 *)(*(u8 **)(p+0x2290)+0x38);
                    range=func_00283CE0(120);
                    angle=func_00283198(((float)(D_L00_001B19C8[0]%120)/range*2.0f)*3.1415927f+(-3.1415927f));
                    color_red=func_00283CF0(angle*90.0f); green=func_00283CF0(angle*50.0f); blue=func_00283CF0(angle*10.0f);
                    blue=((blue+20)<<16)|0x80000000;
                    red=color_red+215; if(red>255)red=255;
                    *(u16 *)(effect+0x34)|=16;
                    *(int *)(effect+0x78)=blue|((green+50)<<8)|red;
                }
                }
            }
next_attachment:

        }
        }
    }
}
