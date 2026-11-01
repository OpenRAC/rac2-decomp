#include "include_asm.h"

#include "common.h"
extern s32 D_L12_001B1828 __attribute__((sda));
extern s32 func_PAL_L09_003FC418(void *, s32);
extern s32 func_L09_003F7C50(void *, s32, s32);
extern s32 func_002A7820(s32, s32);
extern void func_PAL_L12_00417C90(void *, s32, s32, s32);
extern void func_002A7750(void *, s32, s32);
extern s32 func_L09_003F9928(void *);
extern s32 func_001163B0(void);
extern void func_PAL_002A7E68(void *, s32, s32, s32);

void func_PAL_L12_00419E70(u8 *self)
{
    u8 *v=*(u8 **)(self+0x68);
    s32 ready=1;
    if (*(s32 *)(v+0x2DC)!=-1) ready=func_PAL_L09_003FC418(self,*(s32 *)(v+0x2DC))!=0;
    if (ready) {
        switch(self[0x95]) {
        case 3:
            *(s32 *)(v+0x138)&=~4;
            if (v[0x302]&2) v[0x302]=0;
            func_L09_003F7C50(self,*(s32 *)(v+0x2BC),-1);
            if (v[0x30E]) {
                func_PAL_L12_00417C90(self,4,0,func_002A7820(7,12));
                func_002A7750(self,4,5);
            } else {
                func_PAL_L12_00417C90(self,12,0,func_002A7820(7,12));
                func_002A7750(self,8,5);
            }
            break;
        case 4:
            func_L09_003F7C50(self,*(s32 *)(v+0x2B4),-1);
            func_002A7750(self,5,1);
            break;
        case 5: {
            s32 r=func_L09_003F9928(self);
            if (!v[0x303] || r) {
                func_PAL_L12_00417C90(self,12,0,func_002A7820(7,12));
                func_002A7750(self,8,5);
                *(u16 *)(v+0x2E4)=((s32)(D_L12_001B1828) * 5 + 2) / 6;
            }
            break;
        }
        case 1:
        case 6:
            func_L09_003F9928(self);
            if(self[0x60]&2) {
                s32 side=func_001163B0()&1;
                func_PAL_L12_00417C90(self,side,0,func_002A7820(10,20));
                func_002A7750(self,5,-1);
            }
            break;
        }
    } else if(v[0x303] && self[0x95]==5) {
        u8 *h=*(u8 **)(v+0x2F8);
        if(h && *(s16 *)(h+0xAA)==0x114B && h[0x20]!=0xFE && h[0x20]!=0xFD) {
            v[0x30C]=0;
            v[0x30D]=1;
            if(h[0x42]==10) func_PAL_L12_00419BD8(self);
            else if(h[0x43]!=10) func_PAL_002A7E68(h,10,0,10);
        }
    }
}
