/* Handles Joba class selection, confirmation, cancel and repeated directional input. */
#include "common.h"

extern int func_002B4BE8(void);
extern int func_00288D58(void);
extern int func_L02_003F9B70(unsigned int);
extern int func_L00_002C42E0(int, int);
extern int func_002E5E58(int, int, void *);
extern int func_00282978(short *);
extern void func_002A7750(u8 *, int, int);
extern void func_003355A8(int);
extern void func_L00_002C8BA8(int);
extern int func_002B49E0(int, int, int, int, u8 *);
extern void func_L02_003FCA80(u8 *);
extern void func_002B8518(void);
extern int func_L00_0032EF10(unsigned int, int, int *);
extern void func_L00_002E6CF0(void (*)(void *), void *);
extern void func_L02_003FE250(void *);
extern int D_0018C0B4[3], D_L02_002004A4[3];

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
extern unsigned char D_L02_00264A70[];
#define MENU ((MenuRecord *)D_L02_00264A70)
/* The class pointer table is addressed through gp. */
extern int D_L02_001B1190 __attribute__((sda));
#define TABLE ((int **)&D_L02_001B1190)
#define H(o) (*(short *)(state+(o)))

void func_L02_003FD8B8(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    int i, found;
    InputView *input;
    if (func_002B4BE8()==5) return;
    if (D_0018C0B4[0]!=0x6f) func_L00_002C42E0(0x6f,1);
    if (H(0x11a)==0) {
        if ((((InputView *)D_00138180)->field1c4&0x2000) && H(0x118)<13) {
            for (i=H(0x118)+1;i<14;i++) {
                if (!D_001395B8[func_L02_003F9B70(TABLE[i][2])]) continue;
                if (i>=12 && !func_00288D58()) continue;
                if (i==7) {
                    MenuRecord *choice = (MenuRecord *)(D_L02_00264A70 + D_00139568[0x1e] * 0xe0);
                    if (!choice->enabled) continue;
                }
                if (i==8) {
                    MenuRecord *choice = (MenuRecord *)(D_L02_00264A70 + D_00139568[0x2a] * 0xe0);
                    if (!choice->enabled) continue;
                }
                H(0x118)=i;
                H(0x11a)=15;
                H(0x128)=15;
                func_002E5E58(3,0,0);
                break;
            }
        } else if ((((InputView *)D_00138180)->field1c4&0x8000) && H(0x118)>0) {
            found=0;
            if (H(0x118)==1) {
                H(0x118)=0;
                found=1;
                func_002E5E58(3,0,0);
            } else for (i=H(0x118)-1;i>=0;i--) {
                if (!D_001395B8[func_L02_003F9B70(TABLE[i][2])]) continue;
                if (i>=12 && !func_00288D58()) continue;
                if (i==7) {
                    MenuRecord *choice = (MenuRecord *)(D_L02_00264A70 + D_00139568[0x1e] * 0xe0);
                    if (!choice->enabled) continue;
                }
                if (i==8) {
                    MenuRecord *choice = (MenuRecord *)(D_L02_00264A70 + D_00139568[0x2a] * 0xe0);
                    if (!choice->enabled) continue;
                }
                H(0x118)=i;
                found=1;
                break;
            }
            if (!found) H(0x118)=0;
            H(0x11a)=15;
            H(0x126)=15;
            func_002E5E58(3,0,0);
        }
    } else func_00282978((short *)(state+0x11a));
    input = (InputView *)D_00138180;
    if (input->field1c4&0x40) {
        if (H(0x118)==0) {
            H(0x120)=*(unsigned short *)(state+0x118);
            H(0x122)=0;
            D_001395B8[0x3c]=state[0x118];
            func_002A7750(object,8,-1);
            func_003355A8(2);
            func_L00_002C8BA8(0);
            func_002E5E58(4,0,0);
            input->field1c4=0;
            goto clear_buttons;
        } else {
            if (!D_001395B8[func_L02_003F9B70(TABLE[H(0x118)][2])]) return;
            if (H(0x118)>=12 && !func_00288D58()) return;
            if (H(0x118)==7 && !MENU[D_00139568[0x1e]].enabled) return;
            if (H(0x118)==8 && !MENU[D_00139568[0x2a]].enabled) return;
        }
        H(0x120)=*(unsigned short *)(state+0x118);
        H(0x122)=0;
        D_001395B8[0x3c]=state[0x118];
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
        func_L02_003FCA80(object);
        input->field1c4=0;
clear_buttons:
        input->field1a0=0;
        input->field1c0=0;
        input->field1a4=0;
        func_002B8518();
        return;
    } else if (D_L02_002004A4[0] &&
               func_L00_0032EF10(1,60,0) && func_L00_0032EF10(2,60,0) &&
               func_L00_0032EF10(4,60,0) && func_L00_0032EF10(8,60,0)) {
        H(0x120)=*(unsigned short *)(state+0x118);
        func_002A7750(object,5,-1);
        return;
    }
    func_L00_002E6CF0(func_L02_003FE250,object);
}
