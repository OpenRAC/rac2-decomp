#include "include_asm.h"

#include "common.h"
extern int *D_001A7288 MACRO_ADDR;
extern int D_001B18B0[];
typedef struct {
    int *header;
    void *table04, *table08, *table10, *table0C;
} HudBankArena;
extern HudBankArena D_001B1888 MACRO_ADDR;
extern char D_001A91F0[], D_001A9200[], D_001A9210[], D_001A9220[], D_001A9230[];
extern int D_001BAEC0[];
extern void *func_0028B2B8(int, int, char *, int);
extern void func_00282B50(void *, void *, int);
extern void func_00292B20(int, void *);
extern int func_002EED58(void *, int, int, char *);
extern void func_0028B160(int, void *, int);
extern void func_0011AEA0(int);
extern void func_0028AE88(int, void *);

/* RAC1 loaders.c LoadHudBanks supplies the arena layout and bank sequence. */
void func_US2_00293138(void)
{
    int *root = D_001A7288;
    int i, bank_size;
    unsigned int bank1_qwords, bank3_qwords, bank4_qwords, bank5_qwords;
    int *resources;
    int *header;
    char *allocation_file;
    int *bank2_data;
    char *bank1_target;

    for (i = 0; i < 5; i++)
        D_001B18B0[i] = (root[9 + i * 2] + 63) & 0xffffffc0U;
    allocation_file = D_001A91F0;
    resources = D_001BAEC0;
    bank_size = (root[7]+63)&0xffffffc0U;
    header = func_0028B2B8(bank_size, 0, allocation_file, 0x305);
    func_00282B50(header, (void *)(root[6] + (int)root), bank_size);
    D_001B1888.header = header;
    D_001B1888.table04 = (int *)((char *)header + header[1]);
    bank1_target = (char *)(resources[4] + 0x60000);
    D_001B1888.table08 = (int *)((char *)header + header[2]);
    D_001B1888.table0C = (int *)((char *)header + header[3]);
    D_001B1888.table10 = (int *)((char *)header + header[4]);
    if (header[0x15]) {
        bank1_qwords = ((root[9] + 63) & 0xffffffc0U) >> 4;
        func_00292B20(0, bank1_target);
        D_001B1888.header[0x25] = func_002EED58((void *)(root[8] + (int)root), bank1_qwords, bank1_qwords, D_001A9200);
        func_0028B160(0, bank1_target, 1);
    }
    if (D_001B1888.header[0x16]) {
        bank2_data = func_0028B2B8(D_001B1888.header[0x16], 0, allocation_file, 0x32D);
        func_00292B20(1, bank2_data);
        func_0011AEA0(0);
        func_0028AE88(1, bank2_data);
    }
    if (D_001B1888.header[0x17]) {
        bank3_qwords = ((root[13] + 63) & 0xffffffc0U) >> 4;
        D_001B1888.header[0x27] = func_002EED58((void *)(root[12] + (int)root), bank3_qwords, bank3_qwords, D_001A9210);
    }
    if (D_001B1888.header[0x18]) {
        bank4_qwords = ((root[15] + 63) & 0xffffffc0U) >> 4;
        D_001B1888.header[0x28] = func_002EED58((void *)(root[14] + (int)root), bank4_qwords, bank4_qwords, D_001A9220);
    }
    if (D_001B1888.header[0x19]) {
        bank5_qwords = ((root[17] + 63) & 0xffffffc0U) >> 4;
        D_001B1888.header[0x29] = func_002EED58((void *)(root[16] + (int)root), bank5_qwords, bank5_qwords, D_001A9230);
    }
}
