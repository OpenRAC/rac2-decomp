/* functional: high. Same sector pair, -1 sentinel, zero arg and 64-bit user data as retail; only register allocation and instruction order differ. */
extern char D_00188660[];
extern int D_0014B540[];
extern void func_002B6770(int, long);
extern void func_00132498(void *, int, void (*)(int, long), unsigned long);

void func_002B6828(int index)
{
    char *b = D_00188660;
    int *d = D_0014B540;
    int lbn = d[0x14B8 + index * 2];

    if (lbn != 0) {
        char *slot = b + (index + 1) * 4;
        *(unsigned int *)(slot + 0x17A0) = 0xFFFFFFFFu;
        func_00132498((void *)(lbn + d[0x14A7]), 0, func_002B6770,
                      (unsigned long)(unsigned int)(b + index * 4 + 0x17A4));
    } else {
        char *slot = b + (index + 1) * 4;
        *(unsigned int *)(slot + 0x17A0) = 0;
    }
}
