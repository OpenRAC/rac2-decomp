#include "include_asm.h"
#include "names.h"
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern int FlushCache(int);
extern void mem_restore_scratch_area(void);
extern void mem_save_scratch_area(void);
extern int func_002A4E68(void *, void *, int, int);
extern char *ref_L00_002A0300_00;
extern int ref_L00_002A0300_01 __attribute__((sda));
/* Uploads a texture set for an object, swapping the shared buffer around the call and then stepping the buffer pointer back. */
void tex_upload_object_textures(void *object, int mode)
{
    VU1_addGSregister(0x47, 0x5360B);
    FlushCache(0);
    mem_restore_scratch_area();
    ref_L00_002A0300_01 = func_002A4E68(object, ref_L00_002A0300_00, mode, 0);
    mem_save_scratch_area();
    ref_L00_002A0300_00 -= 0x10;
}
extern void DrawMobysSetup(void);
extern void mem_fill_scratch_area(void);
extern int tex_run_upload_and_setup(void);
extern void STUB_printf(const char *, ...);
extern char *ref_L00_002A03C0_00;
extern char *ref_L00_002A03C0_01;
extern int ref_L00_002A03C0_02 __attribute__((sda));
extern int ref_L00_002A03C0_03;
extern int ref_L00_002A03C0_04;
extern char ref_L00_002A03C0_05[];
/* Runs the texture upload for the main set and prints a warning when the size passes its limit. */
void tex_upload_main_textures(void)
{
    DrawMobysSetup();
    mem_fill_scratch_area();
    ref_L00_002A03C0_02 = func_002A4E68(ref_L00_002A03C0_00, ref_L00_002A03C0_01, -1, 1);
    if (ref_L00_002A03C0_03 > ref_L00_002A03C0_04)
        STUB_printf(ref_L00_002A03C0_05);
    tex_run_upload_and_setup();
}
