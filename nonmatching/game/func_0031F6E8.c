/* Closer C3, 1 November 2026: under the default profile (no -fno-gcse, which is not allowed) 1352/1340, 61 rows, and nearly all of
 * it is one thing: mode spills to the frame, retail keeps it in fp. PRE makes a pseudo for basis[1] (sp+0x30, r232 3 refs/231 live)
 * which beats mode (3 refs/275 live); retail leaves that pseudo without a register and rematerializes `addiu a2,sp,0x30`
 * in the loop, and has no spill slot (frame 0xD0). That needs a single set with a frame-address REG_EQUIV and mode ranking above
 * it. The copy `daddu s7,a1` of D_001B5340's high half shows gcse is on in retail. A pointer local for basis[1] keeps a register.
 */
/* sol-high, USA v1.01, game compiler -O2 -G8 -ffunction-sections -fno-gcse.
 * Best check.py: 1340/1340 bytes, 0/28 places, first mismatch +0x10.
 * The 0xD0 frame, mode in fp and main loop register roles now agree.
 * Initialize radial after the initial subtraction; use a direct basis access
 * for its zero store. The bank-preserving particle-call interleaving below
 * reproduces the four first-particle argument sequences.
 * Remaining: the D_001B5340 high half is rebuilt in the loop preheader rather
 * than retained from the initial call. The missing entry copy shifts the
 * initialization by one instruction, recovered at the preheader's extra lui.
 * The loop from +0x12C onward agrees structurally, apart from unresolved
 * relocation operands; binding is not qualified because check.py stops early.
 * Default flags restore the mode spill and 1352-byte body. No-rerun-loop-opt,
 * no-strength-reduce, grouped TI copy and unsplit GCSE edges did not solve it.
 * Next: recover the shared camera high-half lifetime without also retaining
 * the rotation-axis address. Do not repeat separate-vector/basis-array ties.
 * All required declarations follow. This is a near miss, never linked.
 */
#include "common.h"
extern float D_001B5340[], D_00189ED0[];
extern int D_001A8CA0;
extern float D_001AFE0C __attribute__((sda));
extern float D_001AFE10 __attribute__((sda));
extern float D_001AFE14 __attribute__((sda));
extern float D_001AFE18 __attribute__((sda));
extern float D_001AFE1C __attribute__((sda));
extern float D_001AFE20 __attribute__((sda));
extern float D_001AFE24 __attribute__((sda));
extern void func_00282CF0(void *,void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282D30(void *,void *,float);
extern float func_00282DB0(void *,void *);
extern void func_002ACEC0(void *,void *,void *,float);
extern float func_002A7878(float,float),func_002A78D8(float,float);
extern int func_002A77E0(int),func_001163B0(void),func_00283CF0(float);
extern char *func_002C2210(float *,int,float,float,int,int,int,float *,float,int);
void func_0031F6E8(float *position,int count,int mode)
{
    float dir[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float basis[3][4] __attribute__((aligned(16)));
    float *radial;
    int sign,i;
    float size,speed,angle;
    char *p;
    func_00282CF0(basis[0],D_001B5340,position);
    radial = basis[0];
    if (!D_001A8CA0) {
        basis[0][2] = 0;
        basis[1][0] = 0;
        basis[1][1] = 0;
        basis[1][2] = 1;
        basis[1][3] = 1;
    }
    else {
        func_00282CF0(basis[2],position,D_00189ED0);
        func_00282F20(basis[1],basis[2],1);
        func_00282D30(basis[2],basis[1],func_00282DB0(basis[1],radial));
        func_00282CF0(radial,radial,basis[2]);
    }
    if(count>0) {
        i=count;
        do {
            size=func_002A7878(D_001AFE20,D_001AFE24);
            sign = func_002A77E0(2);
            if (!sign)
                sign--;
            angle=func_002A7878(-1.0471977f,1.0471977f);
            func_002ACEC0(dir,radial,basis[1],angle);
            speed=func_002A7878(D_001AFE0C,D_001AFE10)*(1.0f/60.0f);
            func_00282F20(dir,dir,speed);
            dir[2]=func_002A7878(D_001AFE14,D_001AFE18)*(1.0f/60.0f);
            qcopy(pos,position);
            pos[0] += func_002A78D8(0, .15f);
            pos[1] += func_002A78D8(0, .15f);
            pos[2] += func_002A78D8(0, .15f);
            if(mode==0) {
                if(!(func_001163B0()&1)) {
                    func_00282D30(dir,dir,1.5f);
                    p=func_002C2210(pos,60,size*.35f,size,0x7F800000,0,sign,dir,D_001AFE1C,1);
                    if(p)p[9]=func_00283CF0(4)+0x70;
                    p=func_002C2210(pos,60,size*.245f,size*.7f,0x7F7F7F7F,1,-sign,dir,D_001AFE1C,1);
                }else {
                    func_00282CF0(basis[2], D_001B5340, pos);
                    func_00282F20(basis[2], basis[2], speed);
                    func_00282CC0(dir, dir, basis[2]);
                    p=func_002C2210(pos,40,size*2.05f,size,0x7F800000,0,sign,dir,D_001AFE1C,1);
                    if(p)p[9]=func_00283CF0(4)+0x70;
                    p=func_002C2210(pos,40,size*1.4350001f,size*.7f,0x7F7F7F7F,1,-sign,dir,D_001AFE1C,1);
                }
            }else {
                if(!(func_001163B0()&1)) {
                    func_00282D30(dir,dir,1.5f);
                    p=func_002C2210(pos,60,size*.3f,size,0x7F800000,0,sign,dir,D_001AFE1C,1);
                    if(p)p[9]=func_00283CF0(4)+0x70;
                    p=func_002C2210(pos,60,size*(.3f*.7f),size*.7f,0x7F7F7F7F,1,-sign,dir,D_001AFE1C,1);
                }else {
                    func_00282CF0(basis[2], D_001B5340, pos);
                    func_00282F20(basis[2], basis[2], speed);
                    func_00282CC0(dir, dir, basis[2]);
                    p=func_002C2210(pos,40,size*.25f,size,0x7F800000,0,sign,dir,D_001AFE1C,1);
                    if(p)p[9]=func_00283CF0(4)+0x70;
                    p=func_002C2210(pos,40,size*.175f,size*.7f,0x7F7F7F7F,1,-sign,dir,D_001AFE1C,1);
                }
            }
            if(p)p[9]=func_00283CF0(4)+0x70;
        }while(--i);
    }
}
