#include "include_asm.h"

#include "common.h"
extern char D_001AC180[];
typedef struct { char pad[0xB0]; float value; } Camera;
extern Camera D_001B9040;
typedef struct { char pad[0x64]; int variant; } SceneMenu;
extern SceneMenu D_00152C00;
typedef struct { char pad[0x34]; int frame; char pad38[0x154]; char *first; } Scene;
extern Scene D_001B8840;
typedef struct { char pad[0x15C]; int mode; int pad160; int next; } Control;
extern Control D_001393E0;
extern char *D_001B2148 MACRO_ADDR;
extern int D_001B1598 MACRO_ADDR, D_001B1490 MACRO_ADDR;
extern int D_001B169C __attribute__((sda));
extern float D_001B15A0 MACRO_ADDR;
extern int D_001A7344;
extern void func_00284F40(int);
extern void func_00279D18(void);
extern void func_0029FB20(void);
extern void func_0027B858(void);
extern void func_0027AB40(void);
extern void func_002E35E0(void);
extern void func_0027C540(int);
extern void func_002E8190(void);
extern void func_0027C660(void);
extern void func_002A03C0(void);
extern void func_002FCF90(int);
extern void func_002E82C8(int);
extern void func_002E7B48(void *);
extern void func_PAL_002EDA88(void *);
extern void func_002ED4B8(void);
extern void func_0026FEB8(void *,int,int);
extern void func_PAL_002E89D0(void *);
extern void func_002FC560(unsigned int,unsigned long long);
extern void func_002FC3C0(unsigned long long);
extern void func_0029FEE0(void);
extern void func_0027DDC0(int,int,int,int);
extern unsigned long long func_0027C878(int);
extern int func_00283CF0(float);
extern void func_0027E018(int,int,int,int,int,int,int,int,unsigned long long,unsigned long long);
extern void func_0028F410(float,float,float,float,float,int,int,unsigned long long);
#define H(p,o) (*(short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))

/* Renders the transition scene, its loading indicator and the final fade. */
void func_PAL_002E99F0(void) {
    float saved;
    char *object;
    int alpha;
    func_00284F40(0);
    func_00279D18();
    func_0029FB20();
    func_0027B858();
    saved = D_001B9040.value;
    D_001B169C = -1;
    if (saved<0.62f) D_001B9040.value = 0.62f;
    func_0027AB40();
    func_00279D18();
    func_002E35E0();
    D_001B9040.value = saved;
    func_0027AB40();
    func_00279D18();
    if (D_00152C00.variant==4) {
        func_0027C540(1);
        func_002E8190();
        func_0027C660();
    }
    func_002A03C0();
    func_002FCF90(0x2080000);
    func_0027C540(1);
    if (D_00152C00.variant==4 && D_001B8840.frame>60) {
        alpha = (D_001B8840.frame-60)*2;
        if (alpha>128) alpha = 128;
        func_002E82C8(alpha);
    }
    if (!D_001B2148 || H(D_001B2148, 0xAA)==0xD54) {
        object = D_001B8840.first;
        if (B(object, 0x95)>16) {
            func_002E7B48(object);
            func_PAL_002EDA88(object);
            func_002ED4B8();
        }
        else func_0026FEB8(D_001AC180, B(object, 0x95), D_001B1598);

    } else if (B(D_001B8840.first, 0x95)>16) func_002ED4B8();
    if (D_001B2148 && ((unsigned short)(H(D_001B2148, 0xAA)-0x128C)<2 || H(D_001B2148, 0xAA)==0x1342)) func_PAL_002E89D0(D_001B2148);
    if ((unsigned int)(D_001393E0.mode-15)<2 || D_001393E0.next==15 || D_001B1490) {
        float y, angle;
        func_002FC560(0x47, 0x3004B);
        func_0027E018(0x2C, D_001A7344-0x60, 64, 64, 0, 0, 64, 64, 0x80808080ULL, func_0027C878(3));
        y = (float)((D_001A7344-0x40)<<4);
        angle = (D_001B1598%55)*-0.11423972994f;
        func_0028F410(1216.0f, y, 272.0f, 272.0f, angle, 64, 64, func_0027C878(4));
        if ((unsigned int)(D_001393E0.mode-15)<2 || D_001393E0.next==15) D_001B1490 = 25;
        else D_001B1490 = D_001B1490-1;
    }
    func_0027C660();
    if (D_001B15A0>0.0f) {
        if (D_001B15A0>1.0f) D_001B15A0 = 1.0f;
        func_0027DDC0(0, 0, 0, func_00283CF0(D_001B15A0*128.0f));
    }
    func_002FC3C0(16);
    func_0029FEE0();
}
