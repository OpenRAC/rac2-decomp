#include "include_asm.h"

/* func_PAL_002914E0, the PAL copy of func_00290C60 (RAC1's InitOnce): the same C, where D_001A7B90 is
   set to 1 and a switch on sceScfGetLanguage's result picks the game language first, as in RAC1. */
extern char D_001BAEC0[];
extern char D_02000000[];
extern char ref_L00_00290B48_00[];
extern int func_00290AB0(int source, int destination, int length);
extern void func_00290B48(void);

extern void func_00124418(void);
extern void func_00126F60(int);
extern void func_00284000(void);
extern void func_0029D050(void);
extern void func_0027B440(int);
extern void func_0011AE70(int);
extern void func_00126DC0(int (*)(void));
extern int func_001339B0(void);
extern void func_002FC138(void);
extern void func_002FC1D8(void);
extern void func_002FCD18(void);
extern void func_0027B858(void);
extern int func_00124E08(int);
extern int func_001250E8(int);
extern int func_0011EED8(char *);
extern int func_0011EEA0(void);
extern void func_0026FEB8(char *);
extern void func_0011CF78(int);
extern void func_0011F5E0(void);
extern void func_0011E7A0(void);
extern void func_0011F628(void);
extern void func_0011EAC8(void);
extern void func_001252E0(int);
extern void func_0011E0A0(void);
extern void func_00133A28(int, int, void *);
extern void func_0011AEA0(int);
extern void func_00298BB8(void *);
extern void func_002FC070(void *);
/* Takes an address in retail's call, though its body (src/core/001339F0.c) never reads it. */
extern void func_00133A78(void *);
extern void func_PAL_0029DE68(void *, void *);
extern int func_0011E828(int, int, int);
extern void func_0011E8A8(int);
extern void func_002EEBC8(void);
extern void func_002B8548(void);
extern void func_0029AE48(void);
extern void func_0027A9F0(void);
extern void func_0027AB40(void);
extern void func_002E48E8(void);
extern void func_002B68C8(void);
extern void func_002940C0(void);
extern int func_PAL_00131620(void);
extern int func_00131620(void);
extern void func_00282A60(void *, int, int);
extern void func_00126288(void *, int, int, int, int, int, int, int);
extern void func_001265B0(void *, void *);
extern void func_001244B8(int, int);
extern void func_PAL_0026FCB8(void);
extern void func_002889B8(void *);

extern char D_001A9048[];   /* path of the IOP reboot image */
extern char D_001A9060[];   /* "Rebooted IOP" */
extern char D_001A9070[];   /* "loaded irx modules" */
extern char D_PAL_001A9138[];   /* "Unsupported language" */
extern char D_0010E9E0[];
extern char D_001BB000[];
extern char D_001BAD40[];
extern int D_001A7BB8[] __attribute__((sda));
extern unsigned char D_001A7BB0[] __attribute__((sda));
extern int D_001A7B90 __attribute__((sda));
extern int D_001A7290[] __attribute__((sda));
extern int D_001A72F8 __attribute__((sda));
extern int D_001A72FC __attribute__((sda));
extern int D_00152C00[];

typedef struct {
    char pad000[0x32C];
    int base;
    char pad330[8];
    int offset;
    int count;
} Toc_00290C60;
extern Toc_00290C60 D_0014B540;

void func_PAL_002914E0(void)
{
    char buffer[2048];
    char *image;
    char *scratch;
    int *state;
    int handle;
    int mode;
    int lang;

    func_00124418();
    func_00126F60(1);
    D_001A7BB8[0] = 0;
    D_001A7BB0[1] = 0;
    func_00284000();
    func_0029D050();
    func_0027B440(1);
    func_0011AE70(3);
    func_00126DC0(func_001339B0);
    func_002FC138();
    func_00290B48();
    func_002FC138();
    func_002FC1D8();
    func_002FCD18();
    func_0027B858();
    func_00124E08(0);
    func_001250E8(0);
    while (!func_0011EED8(D_001A9048)) {
    }
    while (!func_0011EEA0()) {
    }
    func_0026FEB8(D_001A9060);
    func_0011CF78(0);
    func_0011F5E0();
    func_0011E7A0();
    func_0011F628();
    func_0011EAC8();
    func_00124E08(0);
    func_001250E8(0);
    func_001252E0(2);
    func_0011E0A0();
    func_00133A28(1000, 1, buffer);
    func_0011AEA0(0);
    D_001A7B90 = 1;
    func_00298BB8(buffer);
    func_002FC070(D_0010E9E0);
    func_00133A78(D_02000000 - 0xFE8C);
    image = (char *)((((unsigned int)ref_L00_00290B48_00 + 0x3FFF) & ~0x3FFF) + 0x2C0000);
    scratch = D_02000000 - 0x8000 - (D_0014B540.count << 11);
    func_00133A28(D_0014B540.offset + D_0014B540.base, D_0014B540.count, scratch);
    func_0011AEA0(0);
    func_PAL_0029DE68(scratch, image);
    func_0011AEA0(0);
    handle = func_0011E828(1, 0x55730, 0);
    func_00290AB0(*(int *)(image + 0x50) + (int)image, *(int *)(image + 0x54), handle);
    func_00290AB0(*(int *)(image + 0x48) + (int)image, *(int *)(image + 0x4C), handle);
    func_00290AB0(*(int *)(image + 0x18) + (int)image, *(int *)(image + 0x1C), handle);
    func_00290AB0(*(int *)(image + 0x20) + (int)image, *(int *)(image + 0x24), handle);
    func_00290AB0(*(int *)(image + 0x28) + (int)image, *(int *)(image + 0x2C), handle);
    func_00290AB0(*(int *)(image + 0x30) + (int)image, *(int *)(image + 0x34), handle);
    func_00290AB0(*(int *)(image + 0x38) + (int)image, *(int *)(image + 0x3C), handle);
    func_00290AB0(*(int *)(image + 0x40) + (int)image, *(int *)(image + 0x44), handle);
    func_00290AB0(*(int *)(image + 0x40) + (int)image, *(int *)(image + 0x44), handle);
    func_00290AB0(*(int *)(image + 0x58) + (int)image, *(int *)(image + 0x5C), handle);
    func_0011E8A8(handle);
    func_0026FEB8(D_001A9070);
    func_002EEBC8();
    func_001250E8(0);
    func_002B8548();
    state = (int *)D_001BAEC0;
    D_001A7290[0] = -1;
    D_001A7290[12] = -1;
    D_001A72F8 = 0;
    D_001A72FC = 0x60000;
    D_001A7290[28] = 0x70000;
    D_001A7290[29] = 0xB0000;
    D_001A7290[30] = 0x140000;
    D_001A7290[31] = 0x1D0000;
    D_001A7290[32] = 0x1E0000;
    D_001A7290[1] = state[0x78 / 4];
    D_00152C00[12] = -1;
    D_00152C00[6] = -1;
    func_001250E8(0);
    func_0029AE48();
    func_0027A9F0();
    func_0027AB40();
    func_002FC1D8();
    func_001250E8(0);
    func_002E48E8();
    func_002B68C8();
    func_002940C0();
    lang = func_PAL_00131620();
    switch (lang) {
    case 2:
        D_001A7BB0[4] = 2;
        break;
    case 4:
        D_001A7BB0[4] = 3;
        break;
    case 3:
        D_001A7BB0[4] = 4;
        break;
    case 5:
        D_001A7BB0[4] = 5;
        break;
    default:
        func_0026FEB8(D_PAL_001A9138);
        /* fallthrough */
    case 1:
        D_001A7BB0[4] = 0;
        break;
    }
    mode = func_00131620();
    switch (mode) {
    case 1:
        D_001A7BB0[1] = mode;
        break;
    case 0:
    case 2:
        D_001A7BB0[1] = 0;
        break;
    }
    func_00282A60(D_001BB000, 0x80808080, 0x100);
    func_00126288(buffer, 0x3FFB, 1, 0, 0, 0, 8, 8);
    func_0011AEA0(0);
    func_001265B0(buffer, D_001BB000);
    func_001244B8(0, 0);
    func_PAL_0026FCB8();
    *(volatile int *)0x10000810 = 0x82;
    *(volatile int *)0x10000800 = 0;
    func_002889B8(D_001BAD40);
}

void func_0027BA48(void);

void func_PAL_00291A20(void)
{
  func_00278EB0();
  return;
}


void func_PAL_00291A40(void)
{
  func_00278F80();
  return;
}

