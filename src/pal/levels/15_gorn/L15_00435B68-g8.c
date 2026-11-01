#include "include_asm.h"

#include "common.h"
extern char *D_L15_001B261C;
extern char D_00188660[];
typedef struct { char pad[0x270]; int id; } GornData;
extern int D_L15_001A8F00 MACRO_ADDR;
extern int D_L15_001A904C __attribute__((sda));
extern int D_L15_001B15CC __attribute__((sda));
extern int D_L15_001B1520[4] __attribute__((sda));
extern int D_L15_001B15D8[4][3] __attribute__((sda));
extern int D_L15_001B157C __attribute__((sda)), D_L15_001B1578 __attribute__((sda));
extern int D_L15_001B15C8 __attribute__((sda)), D_L15_001B15BC __attribute__((sda));
extern int D_L15_001B36A4, D_001A79F8;
extern unsigned char D_001A7A0A;
extern int D_00138324 NOT_SDA;
extern int D_L15_001B1520_4[] MACRO_ADDR;
extern void func_002E59F8(int);
extern int func_00282948(void *);
extern void func_0027D330(int);
extern void func_PAL_0029C0F0(int, void *);
extern void func_PAL_L15_00435B68(void);
extern void func_L15_00432008(void);
extern void func_0029B3E0(int,int);
extern void func_L05_00379F48(int);
extern void func_L15_0042FD40(void *);
extern void func_002B49E0(int,int,int,int,int);

void func_PAL_L15_00436118(char *self, int stage)
{
    char *state = *(char **)(self + 0x68);
    char *obj = D_L15_001B261C + (*(int *)(state + 0x20) << 8);
    GornData *data = *(GornData **)(obj + 0x68);
    int id = data->id;
    if (id != -1) {
        char *entry = D_00188660 + id * 0x70;
        if (*(char **)(entry + 0x88) == obj && *(unsigned char *)(entry + 0x74))
            func_002E59F8(id);
    }
    data->id = -1;
    if (D_L15_001A8F00 == 2) {
        return;
    }
    if (!func_00282948(state + 0x6C)) {
        return;
    }
    if (D_L15_001A904C && !D_L15_001B15CC) {
        int count, value;
        func_0027D330(25);
        func_PAL_0029C0F0(0, func_PAL_L15_00435B68);
        count = D_L15_001B1520[stage];
        value = D_L15_001B15D8[stage][count < 3 ? count : 2];
        D_L15_001B15CC = 1;
        D_L15_001B36A4 = stage;
        D_L15_001B157C = 0;
        D_L15_001B1578 = 0;
        if (D_001A7A0A) value *= 10;
        D_L15_001B1520[stage] = count + 1;
        D_001A79F8 = D_001A79F8 + value;
        func_L15_00432008();
        func_0029B3E0(0, -1);
    }
    func_L05_00379F48(1);
    if (!func_00282948(state + 0x50)) {
        if (D_00138324 & 0x40) {
            D_L15_001B15CC = 0;
            *(int *)(state + 0x50) = 4500;
            func_0027D330(25);
            func_L05_00379F48(0);
            *(int *)(state + 0x6C) = 100;
            if (D_L15_001B1520[0]) {
                if (D_L15_001B1520_4[1] && D_L15_001B1520_4[2]) {
                    D_L15_001B15C8 = 3;
                } else if (D_L15_001B1520[0]) {
                    if (D_L15_001B1520_4[1]) {
                        D_L15_001B15C8 = 2;
                    } else {
                        D_L15_001B15C8 = 1;
                    }
                }
            }
            D_L15_001B15BC = 0;
            func_L15_0042FD40(self);
        } else if (D_00138324 & 0x10) {
            func_002B49E0(3, 1, 4, 0, 0);
        }
    } else {
        *(int *)(state + 0x50) = 4500;
    }
}
