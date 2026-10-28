/* functional: high. Clears the flags of every record of the 0x20-byte record list; same reads/writes as retail, only register allocation differs. */
extern int D_001B21B4;
extern int D_001B21B8;
extern int D_001B21C4;
extern int D_001B21E0;
extern int D_001B21E4;
extern int D_001BAED4;
extern int D_001B21E8 __attribute__((sda));

void func_002F0FA0(void)
{
    char *p = (char *)D_001B21B4;
    int v = D_001BAED4;

    D_001B21C4 = v;
    D_001B21E0 = 0;
    D_001B21E4 = 0;
    D_001B21E8 = 0;
    if (p == (char *)D_001B21B8)
        return;
    do {
        *(unsigned char *)(p + 0x1F) = 0xFF;
        *(unsigned short *)(p + 0x16) = 0;
        *(unsigned short *)(p + 0x14) = 0xFFFF;
        p += 0x20;
    } while (p != (char *)D_001B21B8);
}
