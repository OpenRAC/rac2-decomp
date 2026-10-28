/* functional: high. Straight transcription of retail's stores, table lookups and call; only instruction order and temporaries differ. */
extern void func_00282A60(void *, int, int);
extern void func_0029F390(void *);

extern unsigned char D_001CE4E0[];
extern short D_001CE300[];
extern int D_001D04E0[];
extern int D_001CDF40[];
extern int D_001CDB80[];
extern int D_001B1B5C;

void func_0029F0C8(unsigned char *obj, int id)
{
    unsigned char *def;
    int k;
    int p;
    unsigned h;

    func_00282A60(obj, 0, 0x100);
    k = D_001CE4E0[id];
    obj[0x23] = 0x80;
    obj[0x22] = k;
    obj[0xA8] = 0xFF;
    obj[0x21] = 0xFF;
    obj[0x61] = 0xFF;
    obj[0x62] = 0xFF;
    *(long *)(obj + 0x38) = 0x40404000000000L;
    *(short *)(obj + 0x36) = 0x7F80;
    obj[0x6D] = 0xFF;
    obj[0xA5] = 0x7F;
    *(int *)(obj + 0xAC) = (((int)obj - D_001B1B5C) >> 8) << 16;
    obj[0xA7] = 0x80;
    *(short *)(obj + 0xAA) = id;
    obj[0x6E] = 0;
    obj[0x6C] = 0xFF;
    obj[0xA4] = 0x7F;
    obj[0xA6] = 0x80;

    if (D_001CE300[k] != id) {
        h = *(unsigned short *)(obj + 0x34) | 5;
        *(int *)(obj + 0x24) = 0;
        *(unsigned short *)(obj + 0x34) = h;
        *(int *)(obj + 0x98) = 0;
        p = D_001D04E0[obj[0x22]];
        *(int *)(obj + 0x64) = p;
        if (p == 0)
            *(unsigned short *)(obj + 0x34) = h | 2;
        return;
    }

    p = D_001CDF40[k];
    *(int *)(obj + 0x64) = p;
    if (p == 0)
        *(unsigned short *)(obj + 0x34) |= 2;
    def = (unsigned char *)D_001CDB80[obj[0x22]];
    *(unsigned char **)(obj + 0x24) = def;
    obj[0x62] = def[0xE];
    *(unsigned short *)(obj + 0x34) |= *(unsigned short *)(def + 0x44);
    *(int *)(obj + 0x98) = *(int *)(def + 0x10);
    *(float *)(obj + 0x2C) = *(float *)(def + 0x24);
    *(float *)(obj + 0x4C) = 1.0f;
    *(float *)(obj + 0x48) = 1.0f;
    if (*(int *)(def + 0x40) != 0) {
        *(unsigned short *)(obj + 0x34) |= 0x10;
        *(int *)(obj + 0x78) = *(int *)(def + 0x40);
    }
    def = *(unsigned char **)(obj + 0x24);
    if (def[0xF] != 0) {
        obj[0x6F] = 0x18;
        *(unsigned short *)(obj + 0x34) |= 0x400;
        *(int *)(obj + 0x70) = 0;
        *(int *)(obj + 0x74) = 0;
        obj[0xBD] = 0;
    }
    def = *(unsigned char **)(obj + 0x24);
    if (def[6] != 0)
        obj[0x63] = 0x18;
    def = *(unsigned char **)(obj + 0x24);
    if (*(int *)(def + 0x48) == 0)
        return;
    func_0029F390(obj);
    def = *(unsigned char **)(obj + 0x24);
    if (*(unsigned char *)(*(int *)(def + 0x48) + 0x10) >= 2)
        *(unsigned short *)(obj + 0x34) &= 0xFFFD;
    def = *(unsigned char **)(obj + 0x24);
    if (def[0xC] == 1) {
        unsigned char *sub = *(unsigned char **)(def + 0x48);
        if (sub[0x10] < 2) {
            *(int *)(obj + 0x48) = 0;
            sub = *(unsigned char **)(def + 0x48);
            if ((signed char)sub[0x11] < 0)
                *(unsigned short *)(obj + 0x34) |= 0x40;
        }
    }
}
