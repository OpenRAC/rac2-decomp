#include "include_asm.h"
#include "names.h"
extern void func_002FC560(unsigned int, unsigned long long);
extern int func_0011AEA0(int);
extern void func_002A0220(void);
extern void func_002A01F0(void);
extern int func_002A4E68(void *, void *, int, int);
extern char *ref_L00_002A0300_00;
extern int ref_L00_002A0300_01 __attribute__((sda));
/* Uploads a texture set for an object, swapping the shared buffer around the call and then stepping the buffer pointer back. */
void func_002A0300(void *object, int mode)
{
    VU1_addGSregister(0x47, 0x5360B);
    FlushCache(0);
    RestoreScratchArea();
    ref_L00_002A0300_01 = func_002A4E68(object, ref_L00_002A0300_00, mode, 0);
    SaveScratchArea();
    ref_L00_002A0300_00 -= 0x10;
}
extern void func_002A0250(void);
extern void func_002A01C8(void);
extern int func_002A0380(void);
extern void func_0026FEB8(const char *, ...);
extern char *ref_L00_002A03C0_00;
extern char *ref_L00_002A03C0_01;
extern int ref_L00_002A03C0_02 __attribute__((sda));
extern int ref_L00_002A03C0_03;
extern int ref_L00_002A03C0_04;
extern char ref_L00_002A03C0_05[];
/* Runs the texture upload for the main set and prints a warning when the size passes its limit. */
void func_002A03C0(void)
{
    DrawMobysSetup();
    FillScratchArea();
    ref_L00_002A03C0_02 = func_002A4E68(ref_L00_002A03C0_00, ref_L00_002A03C0_01, -1, 1);
    if (ref_L00_002A03C0_03 > ref_L00_002A03C0_04)
        STUB_printf(ref_L00_002A03C0_05);
    RunTextureUploadAndSetup();
}
