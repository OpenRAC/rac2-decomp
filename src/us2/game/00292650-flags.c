/* func_US2_00292650, the USA v2.00 copy of func_00291DE0: the same C, where each entry's last two
   shorts become byte log2 dimensions and a pixel format (the layout func_US2_002ECC48 reads). A
   negative width marks a 4-bit texture (GS PSMT4, 0x14, against PSMT8, 0x13), and both dimensions
   then go through func_00282C30 first. This unit has no strength reduction, as the template's. */
typedef struct {
    long long clear;
} Pad8;

typedef struct {
    Pad8 head;
    short image;
    short palette;
    unsigned char width;
    unsigned char height;
    short format;
} Entry_001B9740;

extern int D_001B1600 __attribute__((sda));
extern Entry_001B9740 D_001B9740[];
extern int func_00282A18(int);
extern int func_00282C30(int);

void func_US2_00292650(int *p, int count) {
    for (D_001B1600 = 0; D_001B1600 < count; D_001B1600++) {
        int w0 = *p++;
        int w1 = *p++;
        int w2 = *p++;
        int w3 = *p++;
        D_001B9740[D_001B1600].palette = w0 >> 4;
        D_001B9740[D_001B1600].image = w1 >> 4;
        D_001B9740[D_001B1600].format = 0x13;
        if (w2 < 0) {
            D_001B9740[D_001B1600].format = 0x14;
            w2 = func_00282C30(w2);
            w3 = func_00282C30(w3);
        }
        D_001B9740[D_001B1600].width = func_00282A18(w2);
        D_001B9740[D_001B1600].height = func_00282A18(w3);
        D_001B9740[D_001B1600].head.clear = 0;
    }
}
