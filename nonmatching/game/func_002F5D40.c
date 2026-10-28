/* Nonmatching C reconstruction.
 * Profile: -O2 -G8 -ffunction-sections.
 * Compiled 236 bytes; retail 224 bytes.
 * USA v1.01, PAL and USA v2.00: 0/28 places in each release.
 * No applicable carrying place was absent; no strict-build qualification.
 * Full-width unsigned-long callee result requires extra conversions before 32-bit address shifts; remaining conditional/address scheduling differs. Reopen after a real return-contract audit and an independently justified source lifetime change.
 */
extern int ref_L00_002F5D40_01 __attribute__((sda));
extern unsigned int D_00139768[];
extern char ref_L00_002F5D40_00[];
extern char D_0014B540[];
extern unsigned char D_001A7BB4[];
extern unsigned long func_002EF010(int);
extern void func_00288B38(void *);
extern void func_002F5E20(int, int, int, int, int);

void func_002F5D40(int request)
{
    unsigned long index;
    int special;
    char *entry;
    char *table;
    int option;
    if (request < 0) {
        ref_L00_002F5D40_01 = 0;
    } else {
        index = func_002EF010(request);
        special = 1;
        if (request != 0xBF)
            special = 0;
        if ((unsigned int)request < 0xB1)
            D_00139768[(unsigned int)request >> 2] |= 1u << (request & 31);
        func_00288B38(ref_L00_002F5D40_00);
        table = D_0014B540;
        entry = table + ((index << 4) | 8);
        option = D_001A7BB4[0];
        if (*(int *)ref_L00_002F5D40_00)
            option = 0;
        func_002F5E20(*(int *)(entry + 8) + *(int *)(table + 4),
                     *(int *)(entry + 12), (int)(table + 8 + (index << 4)),
                     option, special);
    }
}
