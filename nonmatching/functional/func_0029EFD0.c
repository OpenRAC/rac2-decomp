/* functional: medium. Walks the 0x100-byte slot table from D_001B1B60 up to D_001B1B64 and claims the first free slot (state >= 0xFE and its stamp not newer than D_001B1688); the claimed slot is initialised through func_0029F0C8, gets its 0x80-byte record cleared and the free counter lowered. Field names are unknown; control flow, stores and calls follow retail. */
typedef unsigned char u8;

extern char *D_001B1B60;
extern char *D_001B1B64;
extern char *D_001B1B6C;
extern int D_001B1A80;
extern int D_001B1688;
extern char D_001A9DC0[];

extern void func_0029F0C8(char *slot, int arg);
extern void func_00282A60(char *dst, int val, int size);
extern void func_0026FEB8(char *msg, int arg);

char *func_0029EFD0(int a0)
{
    char *s = D_001B1B60;
    char *end = D_001B1B64;

    for (; (unsigned int)s < (unsigned int)end; s += 0x100) {
        u8 state = *(u8 *)(s + 0x20);
        if (state < 0xFE)
            continue;
        if ((unsigned int)D_001B1688 < *(unsigned int *)(s + 0xA0))
            continue;
        if (state == 0xFF)
            *(u8 *)(s + 0x120) = state;
        func_0029F0C8(s, a0);
        {
            char *rec = D_001B1B6C + (((s - D_001B1B60) >> 8) << 7);
            *(char **)(s + 0x68) = rec;
            func_00282A60(rec, 0, 0x80);
        }
        if (D_001B1A80 != 0)
            D_001B1A80 = D_001B1A80 - 1;
        return s;
    }
    func_0026FEB8(D_001A9DC0, D_001B1688);
    return 0;
}
