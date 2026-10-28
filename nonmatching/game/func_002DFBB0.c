/* Nonmatching C reconstruction.
 * Profile: -O2 -G8 -ffunction-sections.
 * Compiled 476 bytes; retail 472 bytes.
 * Carrying checks: 0/28 in us, pal and us2. No strict linked qualification.
 * A named scratchpad symbol creates an additional address lifetime and saved register; packet-pointer macro loads and loop scheduling also differ. No numeric scratchpad address or invented volatile reload was introduced. Reopen with a permitted hardware-address representation and measured pointer lifetimes.
 */
#include "common.h"
extern char *ref_L00_002DFBB0_00[] MACRO_ADDR;
extern char *ref_L00_002DFBB0_01 __attribute__((sda));
extern void *ref_L00_002DFBB0_02[] MACRO_ADDR;
extern char D_001390B0[];
extern char D_70000000[];
extern int D_001A72DC[] MACRO_ADDR;
extern void func_002DF838(void);
extern void func_002DF640(void *, float);
extern char *func_002DF750(char *);
extern void func_002E0BA8(void *, void *);
extern void func_002E0088(void *, void *, int);
extern void func_002DF7A8(int, int, int);
extern void func_002FC560(unsigned int, unsigned long);
extern void func_002DF9E0(unsigned long);

void func_002DFBB0(char *record)
{
    float lower[4];
    float upper[4];
    char *next;
    int i;
    func_002DF838();
    *(unsigned int *)(ref_L00_002DFBB0_00[0] + 0) = 0x30000007;
    *(char **)(ref_L00_002DFBB0_00[0] + 4) = D_001390B0;
    *(unsigned int *)(ref_L00_002DFBB0_00[0] + 8) = 0x13000000;
    *(unsigned int *)(ref_L00_002DFBB0_00[0] + 12) = 0x50000007;
    ref_L00_002DFBB0_01 = ref_L00_002DFBB0_00[0] + 0x10;
    while (*(int *)record) {
        float x, y, z;
        func_002DF640(record + 0x20, 1000.0f);
        next = record + 0x30;
        x = *(float *)(record + 0x10);
        lower[0] = upper[0] = x;
        y = *(float *)(record + 0x14);
        lower[1] = upper[1] = y;
        z = *(float *)(record + 0x18);
        lower[2] = upper[2] = z;
        lower[3] = -*(float *)(record + 8) - *(float *)(record + 12);
        upper[3] = *(float *)(record + 12) - *(float *)(record + 8);
        for (i = 0; i < *(int *)record; i++) {
            next = func_002DF750(next);
            func_002E0BA8(lower, upper);
            func_002E0088(D_70000000, ref_L00_002DFBB0_02[0], *(int *)(record + 4));
            func_002DF7A8(2, 1, 2);
            func_002DF7A8(1, 0, 2);
        }
        record = next;
    }
    func_002FC560(0x4C, (D_001A72DC[0] >> 13) | 0x80000);
    func_002FC560(0x42, 0x2000000064UL);
    func_002DF9E0(0);
    func_002FC560(0x47, 0x5360B);
    func_002FC560(0x42, 0x8000000044UL);
}
