#include "include_asm.h"

#include "common.h"
#define W(p,o) (*(s32 *)((p)+(o)))
#define P(p,o) (*(u8 **)((p)+(o)))
#define F(p,o) (*(f32 *)((p)+(o)))
#define H(p,o) (*(u16 *)((p)+(o)))
extern u8 D_00189EA0[] NOT_SDA;
extern u8 D_0013962A NOT_SDA;
extern u8 D_L07_001BF400[] NOT_SDA;
typedef struct { u8 pad[0x30]; f32 pos[4]; u8 rest[0x40]; } PathRec;
extern PathRec *D_L07_001B23CC[] __attribute__((sda));
extern u8 *D_L07_001B22DC[] __attribute__((sda));
extern f32 D_L07_001B2CB8;
extern s32 D_L07_001B104C;
extern s32 D_L07_001B1044;
extern s32 D_L07_001A8F00;
extern f32 D_0018C2C4 NOT_SDA;
extern s32 D_0018C0BC NOT_SDA;
extern void func_L07_003F7BF0(u8 *);
extern void func_L07_003F8780(u8 *);
extern void func_L00_002D7140(u8 *);
extern s32 func_002ACBC8(void *,s32);
extern s32 func_00288AA0(void *,s32);
extern void func_00288BE8(void *);
extern void func_002A7750(u8 *,s32,s32);
extern void func_L07_003F7968(u8 *,s32,s32);
extern void func_L01_00323310(s32,s32);
extern s32 func_002F5D10(void);
extern void func_00282F20(void *,void *,f32);
extern void func_00282CC0(void *,void *,void *);
extern f32 func_00283248(f32,f32);
extern void func_L00_002B9D60(void *,void *,s32,s32);
extern void func_L07_003F80B8(u8 *,f32);
extern s32 func_002B3868(u8 *);
extern void func_L07_003F9028(u8 *);
extern s32 func_L07_003F8908(u8 *);
extern void func_L07_003EF1E0(u8 *,s32,s32);
extern void func_L07_003F8828(u8 *,void *);
extern s32 func_00283CF0(f32);
extern void func_002E5CF8(s32,s32,u8 *);
extern void func_L07_003F9088(u8 *);
extern s32 func_US2_002AF9C8(u8 *,f32);
extern void func_L07_003F8AB0(u8 *);
extern void func_L07_003F8BB0(u8 *);
extern void func_L07_003F8C38(u8 *);
extern void func_L07_003F8CD0(u8 *);
extern s32 func_00282948(void *);
extern void func_002A7470(u8 *,s32,s32,s32);
extern f32 func_002AA2E8(f32 *,f32,f32);
extern void func_L07_003F78F8(u8 *);
extern void func_US2_002A7AA8(u8 *,s32,s32);
extern s32 func_002A8C28(u8 *,void *,s32,f32,f32,f32,s32,s32,s32);
extern void func_L07_003EECE0(u8 *);
extern void func_002AD7B8(s32);
extern void func_00288CB0(s32,s32);
extern void func_L07_003F8D90(u8 *);

void func_US2_L07_003F83E8(u8 *a)
{
    f32 pos[4];
    f32 rot[4];
    u8 *s = P(a,0x68);
    func_L07_003F7BF0(a);
    switch (a[0x95]) {
    case 0:
    case 1:
        if (a[0x20] != 3 && a[0x20] != 11) func_L07_003F8780(a);
        if (a[0x95] == 0) D_L07_001B2CB8 = 0.6981318f;
        break;
    case 2:
        if (P(s,0x450)) {
            func_L00_002D7140(P(s,0x450));
            P(s,0x450)=0;
        }
        break;
    }
    switch (a[0x20]) {
    case 1:
        if (func_002ACBC8(D_00189EA0,W(s,0x170))) {
            D_L07_001B104C=1;
            if (!D_0013962A) {
                if (func_00288AA0(D_L07_001BF400,0x4f)) {
                    func_00288BE8(D_L07_001BF400);
                    func_002A7750(a,2,-1);
                    goto start_path;
                }
            }
            func_L07_003F7968(a,0,2);
            qcopy_nc(s+0x3e0,D_L07_001B23CC[0][W(s,0x174)].pos);
            F(s,0x3e8)+=1.5f;
start_path:
            func_L01_00323310(W(s,0x18c),-1);
        }
        break;
    case 2:
        if (!func_002F5D10()) {
            D_0013962A=1;
            func_00282F20(pos,(u8 *)&D_L07_001B23CC[0][W(s,0x174)]+0x10,8.0f);
            func_00282CC0(pos,pos,D_L07_001B23CC[0][W(s,0x174)].pos);
            qzero_nc(rot);
            rot[2]=func_00283248(D_L07_001B23CC[0][W(s,0x174)].pos[0]-pos[0],D_L07_001B23CC[0][W(s,0x174)].pos[1]-pos[1]);
            func_L00_002B9D60(pos,rot,0,1);
            func_L07_003F7968(a,0,2);
            qcopy_nc(s+0x3e0,D_L07_001B23CC[0][W(s,0x174)].pos);
            F(s,0x3e8)+=1.5f;
        }
        break;
    case 3:
        func_L07_003F80B8(a,-1.0f);
        if (H(a,0x96)>=121) func_002A7750(a,4,-1);
        break;
    case 4:
        if (func_002B3868(a)) {
            func_L07_003F9028(a);
            W(s,0x42c)=60;
        }
        func_L07_003F80B8(a,-1.0f);
        if (!W(s,0x42c)) {
            W(s,0x43c)=func_L07_003F8908(a);
            func_002A7750(a,5,-1);
        }
        break;
    case 5:
        if (func_002B3868(a)) func_L07_003F9028(a);
        func_L07_003F80B8(a,-1.0f);
        if (H(a,0x96)==W(s,0x444)-W(s,0x448))
            func_L07_003EF1E0(P(s,0x414),W(s,0x448),W(s,0x448)+10);
        else if (H(a,0x96)==W(s,0x444)-D_L07_001B1044)
            func_L07_003F8828(a,s+0x140);
        else if (W(s,0x444)<H(a,0x96))
            func_002A7750(a,W(s,0x43c),-1);
        if (W(s,0x43c)==7) {
            s32 n = func_00283CF0(45.3f);
            if (H(a,0x96)==W(s,0x444)-n) func_002E5CF8(8,0,a);
        }
        break;
    case 6: case 7: case 8: case 9:
        if (func_002B3868(a)) func_L07_003F9088(a);
        func_L07_003F80B8(a,-1.0f);
        if (a[0x42]==a[0x43]) {
            if (func_US2_002AF9C8(a,1.0f)) {
                switch (a[0x20]) {
                case 7: func_L07_003F8AB0(a); break;
                case 6: func_L07_003F8BB0(a); break;
                case 9: func_L07_003F8C38(a); break;
                case 8: func_L07_003F8CD0(a); break;
                }
            } else if (a[0x60]&2) {
                if (func_00282948(s+0x438)) func_002A7750(a,4,-1);
                else func_002A7750(a,5,-1);
            }
        }
        break;
    case 10:
        if (func_002B3868(a)) {
            if (a[0x43]!=7) func_002A7470(a,7,0,20);
        }
        func_L07_003F80B8(a,-1.0f);
        if (a[0x60]&2) func_002A7750(a,11,-1);
        break;
    case 11:
        if (func_002B3868(a)) {
            if (a[0x43]!=4) func_002A7470(a,4,0,20);
            F(s,0x434)=1.0833334f;
        }
        func_L07_003F80B8(a,F(s,0x434));
        func_002AA2E8((f32 *)(s+0x434),0.0f,0.0055555557f);
        func_002AA2E8((f32 *)(s+0x3e8),18.0f,0.033333335f);
        if (!a[0x31]) {
            func_002A7750(a,1,2);
            func_L07_003F78F8(a);
        }
        break;
    case 12:
        if (func_002B3868(a)) {
            if (a[0x43]!=7) func_002A7470(a,7,0,20);
            F(s,0x3e8)+=1.0f;
            W(s,0x440)=600;
            if (F(s,0x20)==0.0f && !a[0x7f]) func_US2_002A7AA8(a,10,3);
        }
        func_L07_003F80B8(a,-1.0f);
        if (F(s,0x20)<=0.0f) {
            D_0018C2C4=40.0f;
            func_002A8C28(a,D_L07_001B23CC[0][W(s,0x174)].pos,0x10000,50.0f,100.0f,0.0f,0,1,0);
        }
        if (a[0x60]&2) {
            if (F(s,0x20)<=0.0f) func_002A7750(a,13,2);
            else {
                switch(W(s,0x420)) {
                case 3: break;
                case 4: func_L07_003EECE0(D_L07_001B22DC[0]+(W(s,0x178)<<8)); break;
                case 5: func_L07_003EECE0(D_L07_001B22DC[0]+(W(s,0x17c)<<8)); break;
                }
                func_002A7750(a,4,-1);
                W(s,0x440)=0;
            }
        }
        break;
    case 13:
        if (func_00288AA0(D_L07_001BF400,0x50)) {
            func_00288AA0(D_L07_001BF400,0x51);
            func_00288AA0(D_L07_001BF400,8);
            func_00288AA0(D_L07_001BF400,0x52);
            func_00288BE8(D_L07_001BF400);
            func_002A7750(a,14,-1);
        }
        break;
    case 14:
        if (((H(a,0x34)^1)&1) && D_L07_001A8F00==2) func_L07_003F78F8(a);
        func_002A8C28(a,D_L07_001B23CC[0][W(s,0x174)].pos,0x10000,50.0f,100.0f,0.0f,0,1,0);
        if (!func_002F5D10() && D_L07_001A8F00!=2 && D_L07_001A8F00!=1 && D_0018C0BC!=20) {
            func_002AD7B8(8);
            func_00288CB0(8,1);
        }
        break;
    }
    func_L07_003F8D90(a);
}
