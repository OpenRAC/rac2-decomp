/* functional: high. Near-miss draft within a few instructions of retail: differences are register allocation, scheduling and instruction shape. */
/* GPT-6.1 Sol high, task v0876: USA v1.01 game -O2 -G8 -ffunction-sections.
 * Best check.py: 1060/1060 bytes, 0/1 places. Three instructions at
 * +0x328..+0x330 differ: retail loads the entity-pool pointer before the index;
 * this source loads the index first. Other non-relocated instructions agree.
 * Macro absolute pool loads, both real GP pool views, TImode vector clear,
 * the typed hero and aim-state fields, and hero-position-relative active flag
 * recover the earlier allocation/size differences. Base local, 256-byte entity
 * indexing and reversed pointer addition tie; -g does not change the residue.
 * A split-address pool alias moves the load first but gives it v1, not v0.
 * No linked build: address bindings remain unqualified. Declarations below.
 */
#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
extern char *D_L03_001B2A1C_GP SDATA(D_L03_001B2A1C);
extern void func_0029F338(char *);
extern void func_002A7750(char *,int,int);
extern float func_00282E80(char *,char *);
extern void func_00283698(void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00283098(void *,void *,void *);
extern int func_002B38B8(char *);
extern int func_L03_0032AB20(int);
extern void func_002B0C28(int,int,int);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282C88(void *);
extern float func_00283B98(float,float);
extern void func_L00_002B9D60(void *,void *,int,int);
extern void func_L03_003C6E50(char *,void *,void *);
extern void func_00335438(void *,void *,int,int,int);
extern void func_L03_003C7A40(char *);
extern void func_L03_003C7A88(char *);
extern void func_003355A8(int);
extern void func_0029B810(int);
extern void func_00335370(void *);
extern void func_003353C8(void *);
extern int func_L03_0041F090(void *);
extern void func_L00_003294F0(void *,int);
extern void func_0029B7C0(void *,void *,int);
extern void func_L03_003C7018(void);
typedef struct { char pad0[0x80]; float pos[4]; float rot[4]; char padA0[0x13c]; short mode; char pad1DE[0x1652]; int field1830; } Hero6A28;
extern Hero6A28 D_00189E20;
extern char D_00189EA0[];

extern char *D_L03_001B2A1C[] MACRO_ADDR;
extern char *D_0018B650 NOT_SDA;
extern int D_00138324 NOT_SDA;
typedef struct { char pad[0x3d4]; float f; char pad2[0x10]; char b0,b1; } AimState6A28;
extern AimState6A28 D_L03_001B9840;
extern char D_L03_003C7010[];
void func_L03_003C6A28(char *obj)
{
    char mat[0x40] __attribute__((aligned(16)));
    float local[4] __attribute__((aligned(16)));
    float rot[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float cam1[4] __attribute__((aligned(16)));
    float cam2[4] __attribute__((aligned(16)));
    char *vars = *(char **)(obj+0x68);
    switch ((unsigned char)obj[0x20]) {
    case 0:
        if (*(int *)vars == -1) { func_0029F338(obj); break; }
        *(int *)(vars+0x30)=-1;
        *(int *)(obj+0x98)=0;
        *(unsigned short *)(obj+0x34)|=1;
        obj[0x31]=0;
        func_002A7750(obj,1,-1);
        break;
    case 1:
    case 2:
        if (func_00282E80(obj+0x10,D_00189EA0) < 6.0f && *(int *)(D_00189EA0+0x2C0)) {
            func_00283698(mat,obj+0xC0);
            func_00282CF0(local,D_00189EA0,obj+0x10);
            func_00283098(local,local,mat);
            if ((unsigned char)obj[0x20]==1 && func_002B38B8(obj)) func_002A7750(obj,2,-1);
            if (local[0]<4.0f && local[0]>0.0f && local[1]<2.5f && local[1]>-2.5f) {
                if ((unsigned char)obj[0x20]==1) {func_002B0C28(8,0x27BE,1); break;}
                func_002B0C28(8,0x27A8,1);
                if (func_L03_0032AB20(8) && (D_00138324&0x10)) {
                    func_002A7750(obj,3,-1);
                    *(Quad *)pos=0; pos[0]=2.0f;
                    func_00283098(pos,pos,obj+0xC0);
                    func_00282CC0(pos,pos,obj+0x10);
                    func_00282C88(rot);
                    rot[2]=func_00283B98(*(float *)(obj+0xF8),3.14159f);
                    func_L00_002B9D60(pos,rot,0x31,1);
                    D_0018B650=D_L03_001B2A1C[0]+(*(int *)vars<<8);
                    func_L03_003C6E50(obj,cam1,cam2);
                    func_00335438(cam1,cam2,1,0,0);
                    func_L03_003C7A40(D_L03_001B2A1C[0]+(*(int *)vars<<8));
                }
            }
        }
        break;
    case 3:
        D_00189E20.mode=5;
        if (D_00138324&0x10) {
            func_003355A8(0);
            func_L00_002B9D60(D_00189E20.pos,D_00189E20.rot,0,1);
            D_00189E20.field1830=0;
            func_L03_003C7A88(D_L03_001B2A1C[0]+(*(int *)vars<<8));
            D_L03_001B9840.f=64.42f;
            D_L03_001B9840.b1=1; D_L03_001B9840.b0=0;
            func_002A7750(obj,2,-1); func_0029B810(0);
        } else {
            func_L03_003C6E50(obj,mat,mat+0x10);
            func_00335370(mat); func_003353C8(mat+0x10);
            if (*(int *)(vars+0x1C)!=-1 && func_L03_0041F090(D_L03_001B2A1C_GP+(*(int *)(vars+0x1C)<<8))) {
                if (*(int *)(vars+0x20)!=-1) func_L00_003294F0(D_L03_001B2A1C_GP+(*(int *)(vars+0x20)<<8),1);
            }
            func_0029B7C0(D_L03_003C7010,func_L03_003C7018,0);
        }
        break;
    }
}
