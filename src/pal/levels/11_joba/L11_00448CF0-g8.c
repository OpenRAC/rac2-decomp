#include "include_asm.h"

#include "common.h"
extern int func_002B4BE8(void);
extern int func_00288D58(void);
extern int func_L11_0043E108(unsigned int);
extern int func_PAL_L11_002D9038(int, int);
extern int func_002E5E58(int, int, void *);
extern int func_00282978(short *);
extern void func_002A7750(u8 *, int, int);
extern void func_003355A8(int);
extern void func_L00_002C8BA8(int);
extern int func_002B49E0(int, int, int, int, u8 *);
extern void func_PAL_L11_00447E20(u8 *);
extern void func_002B8518(void);
extern int func_L00_0032EF10(unsigned int, int, int *);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern void func_PAL_L11_004495E8(void *);
extern int D_0018C0B4[3], D_L11_00200864[3];
typedef struct {
    u8 pad[0x1a0];
    int field1a0, field1a4;
    u8 gap[24];
    int field1c0, field1c4;
} InputView;
extern unsigned char D_00138180[];
extern unsigned char D_00139568[], D_001395B8[];
typedef struct {
    u8 pad[4];
    u8 enabled;
    u8 rest[0xdb];
} MenuRecord;
extern unsigned char D_L11_00279BA0[];
#define MENU ((MenuRecord *)D_L11_00279BA0)
extern int D_L11_001B14F8 __attribute__((sda));
#define TABLE ((int **)&D_L11_001B14F8)
#define H(o) (*(short *)(state+(o)))

void func_PAL_L11_00448CF0(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    int i, found;
    InputView *input;
    if (func_002B4BE8()==5) return;
    if (D_0018C0B4[0]!=0x6f) func_PAL_L11_002D9038(0x6f,1);
    if (H(0x1ea)==0) {
        if ((((InputView *)D_00138180)->field1c4&0x2000) && H(0x1e8)<12) {
            for (i=H(0x1e8)+1;i<13;i++) {
                if (!D_001395B8[func_L11_0043E108(TABLE[i][2])]) continue;
                if (i>=11 && !func_00288D58()) continue;
                if (i==8) {
                    MenuRecord *choice = (MenuRecord *)(D_L11_00279BA0 + D_00139568[0x1e] * 0xe0);
                    if (!choice->enabled) continue;
                }
                H(0x1e8)=i;
                H(0x1ea)=12;
                H(0x1f8)=12;
                func_002E5E58(3,0,0);
                break;
            }
        } else if ((((InputView *)D_00138180)->field1c4&0x8000) && H(0x1e8)>0) {
            found=0;
            if (H(0x1e8)==1) {
                H(0x1e8)=0;
                found=1;
            } else for (i=H(0x1e8)-1;i>=0;i--) {
                if (!D_001395B8[func_L11_0043E108(TABLE[i][2])]) continue;
                if (i>=11 && !func_00288D58()) continue;
                if (i==8) {
                    MenuRecord *choice = (MenuRecord *)(D_L11_00279BA0 + D_00139568[0x1e] * 0xe0);
                    if (!choice->enabled) continue;
                }
                H(0x1e8)=i;
                found=1;
                break;
            }
            if (!found) H(0x1e8)=0;
            H(0x1ea)=12;
            H(0x1f6)=12;
            func_002E5E58(3,0,0);
        }
    } else func_00282978((short *)(state+0x1ea));
    input = (InputView *)D_00138180;
    if (input->field1c4&0x40) {
        if (H(0x1e8)==0) {
            H(0x1f0)=*(unsigned short *)(state+0x1e8);
            H(0x1f2)=0;
            D_001395B8[0x49]=state[0x1e8];
            func_002A7750(object,8,-1);
            func_003355A8(2);
            func_L00_002C8BA8(0);
            func_002E5E58(4,0,0);
            input->field1c4=0;
            goto clear_buttons;
        } else {
            if (!D_001395B8[func_L11_0043E108(TABLE[H(0x1e8)][2])]) return;
            if (H(0x1e8)>=11 && !func_00288D58()) return;
            if (H(0x1e8)==8 && !MENU[D_00139568[0x1e]].enabled) return;
        }
        H(0x1f0)=*(unsigned short *)(state+0x1e8);
        H(0x1f2)=0;
        D_001395B8[0x49]=state[0x1e8];
        func_002A7750(object,8,-1);
        func_003355A8(2);
        func_L00_002C8BA8(0);
        func_002E5E58(4,0,0);
        input->field1c4=0;
        goto clear_buttons;
    } else if (input->field1c4&0x80) {
        func_002B49E0(5,1,0,0,0);
        return;
    } else if (input->field1c4&0x10) {
        func_PAL_L11_00447E20(object);
        input->field1c4=0;
clear_buttons:
        input->field1a0=0;
        input->field1c0=0;
        input->field1a4=0;
        func_002B8518();
        return;
    } else if (D_L11_00200864[0] &&
               func_L00_0032EF10(1,50,0) && func_L00_0032EF10(2,50,0) &&
               func_L00_0032EF10(4,50,0) && func_L00_0032EF10(8,50,0)) {
        H(0x1f0)=*(unsigned short *)(state+0x1e8);
        func_002A7750(object,5,-1);
        return;
    }
    func_L00_002E6CF0(func_PAL_L11_004495E8,object);
}
