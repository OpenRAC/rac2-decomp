/* Nonmatching reconstruction, 2026-10-28. No C coverage credit.
 * Measured US: 596 / 608 bytes, 0/1 places, with
 * -O2 -G0 -ffunction-sections -frac2-gcse-unsplit-edges.
 * Six bounded checks: ordinary profile 588; scoped/unsplit profile 596;
 * broad -fno-gcse 584 (rejected); explicit field reloads and narrower CSE
 * controls 596; loop scopes plus -fno-gcse 584; retained scopes 596.
 * Frame 0x70 matches, but an extra saved FP register, hero high-part lifetime,
 * empty-loop mode load, and snapshot-address allocation differ. Three
 * scoped/narrow trials converge to 596. Reopen with independent lifetime evidence.
 *
 * Callee audit: 002FC980 reads no incoming arguments and defines no return;
 * 002E64A0 consumes a0 actor and has no common result; 00326458 consumes a0
 * actor and has no common result. 00326048 writes actor+0x78 and updates the
 * float at a1; its one f12 scalar follows a0..a3. 0029FCC0 consumes actor,
 * signed 32-bit joint index and output pointer, writes the complete 16-byte
 * vector through scale/transform/add helpers, and has void return.
 * Both locals receive whole 16-byte writes before any possible read. The
 * table is populated at offsets [0,0xC0) before its snapshot loop; unknown
 * allocation sizes remain incomplete. Repeated snapshots are observed
 * transfers, implemented by the approved memory-clobbering qcopy helper.
 * The early actor kind read preceding its null test is present in retail.
 */

#include "common.h"

/* Observed storage views only; the hero and joint table extents are unknown. */
extern unsigned char D_L03_001BD680[];
extern unsigned char D_L03_001C64A0[];
/* A single macro-addressed scalar permits the actual absolute / delay-slot GP mix. */
extern int D_001A79F0 __attribute__((sda));
extern float D_L03_001A9420 SDATA(D_L03_001A9420);
extern int D_L03_001A9424 SDATA(D_L03_001A9424);
extern void func_L00_002FC980(void);
extern void func_002E64A0(void *);
extern void func_L00_00326048(void *, float *, int, int, float);
extern void func_L03_00326458(void *);
extern void func_0029FCC0(void *, int, void *);

void func_L03_002FDE30(void)
{
    float first[4] __attribute__((aligned(16)));
    float second[4] __attribute__((aligned(16)));
    unsigned char *hero;
    unsigned char **slot;
    unsigned char *object;
    int i;

    i = 0;
    func_L00_002FC980();
    {
    unsigned char *hero = D_L03_001BD680;
    if (*(short *)(hero + 0x44) > 0) {
    slot = (unsigned char **)(hero + 0x18C);
    do {
        object = *slot;
        if (object && *(short *)(object + 0xAA) == 0xE29) {
            *(unsigned short *)(object + 0x34) |= 0x800;
            }
        if (*(short *)(object + 0xAA) == 0xD54) func_002E64A0(object);
        if (object && *(short *)(object + 0xAA) == 0xFA0 && *(void **)(object + 0x68))
            func_L00_00326048(object, (float *)(*(unsigned char **)(object + 0x68) + 0xC),
                              (int)0x80AAAAD2, (int)0x80396464, 0.061086535f);
        i++;
        slot++;
    } while (i < *(short *)(hero + 0x44));
    }
    }
    if (D_001A79F0 != 3) return;
    hero = D_L03_001BD680;
    if (*(unsigned int *)(hero + 0x30) < 3) {
        object = *(unsigned char **)(hero + 0x190);
        *(float *)(object + 0x2C) = *(float *)(*(unsigned char **)(object + 0x24) + 0x24) * D_L03_001A9420;
    }
    if (*(int *)(hero + 0x30) == 6) func_L03_00326458(*(void **)(hero + 0x190));
    if (*(int *)(hero + 0x30) == 8) func_L03_00326458(*(void **)(hero + 0x198));
    if (*(int *)(hero + 0x30) == 7 && *(int *)(hero + 0x34) == 0x424) {
        unsigned char *target = *(unsigned char **)(hero + 0x194);
        int row;
        unsigned char *at;
        unsigned char *middle;
        unsigned char *last;
        unsigned char *end;
        D_L03_001A9424 = *(int *)(hero + 0x34);
        for (row = 0; row < 4; row++) {
            int i;
            at = D_L03_001C64A0 + row * 0x30;
            for (i = 0; i < 3; i++, at += 0x10)
                func_0029FCC0(target, row * 3 + i, at);
        }
        {
        unsigned char *at = D_L03_001C64A0;
        middle = at + 0x10;
        last = at + 0x20;
        end = at + 0xC0;
        do {
            qcopy(first, at);
            qcopy(second, middle);
            qcopy(first, at);
            qcopy(second, last);
            at += 0x30;
            last += 0x30;
            middle += 0x30;
        } while ((int)at < (int)end);
        }
    }
}
