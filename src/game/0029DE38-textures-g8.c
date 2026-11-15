#include "include_asm.h"
#include "names.h"

extern int ref_0029FDF0_00[] __attribute__((sda));
extern int ref_0029FDF0_01[] __attribute__((sda));
extern int ref_0029FDF0_02[1] __attribute__((sda));
extern void func_002A4AD8(int);
extern void func_002FC748(void);
extern char D_0010FFC0[];
extern unsigned short D_0010FFB0[];
extern char D_00100080[];
extern int ref_002A0250_00[] __attribute__((sda));
extern int ref_002A0250_01[] __attribute__((sda));
extern int ref_002A0250_02[] __attribute__((sda));
extern int ref_002A0250_03[] __attribute__((sda));
extern int ref_002A0250_04[] __attribute__((sda));
extern int ref_002A0250_05[] __attribute__((sda));
extern int ref_002A0250_06[] __attribute__((sda));
extern int ref_002A0250_07[] __attribute__((sda));
extern int D_001A72D0;
extern int D_001A72D4;
extern void func_002FC410(unsigned int, unsigned int);
extern void func_002FC070(int);
extern void func_002FC560(unsigned int, unsigned long long);

/* Splice texture uploads into the DMA chain using NEXT tags. The integer
 * cursor advances before publication while the original tag remains saved.
 */
void func_0029FDF0(void)
{
    unsigned int *saved;
    int next = ref_0029FDF0_00[0];
    saved = (unsigned int *)next;
    next += 16;
    ref_0029FDF0_00[0] = next;
    ((unsigned int *)ref_0029FDF0_01[0])[0] = 0x20000000;
    ((unsigned int *)ref_0029FDF0_01[0])[1] = (unsigned int)ref_0029FDF0_00[0];
    ((unsigned int *)ref_0029FDF0_01[0])[2] = 0;
    ((unsigned int *)ref_0029FDF0_01[0])[3] = 0;
    upload_used_moby_textures(ref_0029FDF0_02[0]);
    AppendVu1DmaChainTable1();
    ((unsigned int *)ref_0029FDF0_00[0])[0] = 0x20000000;
    ((unsigned int *)ref_0029FDF0_00[0])[1] = (unsigned int)(ref_0029FDF0_01[0] + 16);
    ((unsigned int *)ref_0029FDF0_00[0])[2] = 0;
    ((unsigned int *)ref_0029FDF0_00[0])[3] = 0;
    ref_0029FDF0_00[0] += 16;
    saved[0] = 0x20000000;
    saved[1] = (unsigned int)ref_0029FDF0_00[0];
    saved[2] = 0;
    saved[3] = 0;
}

/* Reserve the moby texture tag and snapshot the render setup cursors. */
void func_002A0250(void)
{
    int p;
    int limit;
    int frame;
    int anim;

    VU1_addDataRef((unsigned int)D_0010FFC0, D_0010FFB0[0]);
    ref_002A0250_00[0] = 6;
    StartDmaChannel0AndWait((int)D_00100080);
    VU1_addGSregister(0x47, 0x5360B);
    p = ref_002A0250_01[0];
    limit = ref_002A0250_02[0] + 0xFFFF0000;
    frame = D_001A72D4;
    ref_002A0250_04[0] = p;
    anim = ref_002A0250_03[0];
    p += 0x10;
    D_001A72D0 = frame;
    ref_002A0250_01[0] = p;
    ref_002A0250_06[0] = limit;
    ref_002A0250_05[0] = anim;
    ref_002A0250_07[0] = 0;
}
