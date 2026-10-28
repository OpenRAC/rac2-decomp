/* functional: medium. Near-miss C: same reads, writes and calls in retail order; only register allocation and scheduling differ. */
typedef struct {
    int word0;
    unsigned short half4;
    unsigned short half6;
    int word8;
    unsigned char byteC;
    unsigned char byteD;
    unsigned short halfE;
} TexSlot;

typedef struct {
    int word0;
    unsigned short half4;
} TexKey;

typedef struct {
    int word0;
    unsigned short half4;
    unsigned char byte6;
    unsigned char byte7;
} TexSize;

extern short *D_001B1890;
extern char *D_001B1898;
extern char *D_001B1894;
extern TexSlot D_001B9340[];
extern int D_001B15FC;
extern int D_001A72D0[] __attribute__((sda));
extern int D_001A72DC[] __attribute__((sda));

unsigned long long func_0028E640(int index)
{
    short *row = (short *)((index << 2) + (unsigned int)D_001B1890);
    TexKey *key = (TexKey *)((char *)D_001B1898 + (row[0] << 3));
    TexSize *size = (TexSize *)((char *)D_001B1894 + (row[1] << 3));
    int added = 0;
    int shift;
    int format;
    unsigned long long value;

    if (key->half4 == 0 || size->half4 == 0) {
        int count = D_001B15FC;
        D_001B9340[count].word0 = key->word0;
        D_001B9340[count].half4 = 0;
        D_001B9340[count].half6 = 0x3FF0;
        D_001B9340[count].word8 = key->word0;
        D_001B9340[count].halfE = 0x3FF0;
        D_001B9340[count].byteC = D_001B9340[count].byteD = 5;
    }
    if (key->half4 == 0) {
        int base = D_001A72D0[0];
        int count;
        key->half4 = base >> 8;
        D_001A72D0[0] = base + 0x400;
        count = D_001B15FC;
        if (count < 0x40) {
            D_001B9340[count].word0 = key->word0;
            D_001B9340[count].half4 = 0;
            D_001B9340[count].half6 = key->half4;
            added = 1;
        }
    }
    if (size->half4 == 0) {
        int base = D_001A72D0[0];
        unsigned char big;
        int count;
        size->half4 = base >> 8;
        big = size->byte7 < size->byte6 ? size->byte6 : size->byte7;
        D_001A72D0[0] = base + (1 << (big * 2));
        count = D_001B15FC;
        if (count < 0x40) {
            D_001B9340[count].word8 = size->word0;
            D_001B9340[count].byteC = size->byte6;
            D_001B9340[count].byteD = size->byte7;
            D_001B9340[count].halfE = size->half4;
            added = 1;
        }
    }
    if (added)
        D_001B15FC++;
    shift = size->byte6 - 6;
    shift = shift >= 0 ? shift : 0;
    value = (unsigned long long)size->half4 | ((unsigned long long)(1 << shift) << 14);
    format = size->half4 < (D_001A72DC[0] >> 8) ? 0x1B : 0x13;
    value |= (unsigned long long)format << 20;
    value |= (unsigned long long)size->byte6 << 26;
    value |= (unsigned long long)size->byte7 << 30;
    value |= (unsigned long long)key->half4 << 37;
    value |= 1ULL << 34;
    return value | 0x8000000000000000ULL;
}
