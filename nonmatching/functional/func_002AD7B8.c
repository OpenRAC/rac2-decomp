/* functional: high. Same reads, writes and branches as retail; the empty 28-iteration loop (dead result) is dropped, the table is addressed at 0x00139948. */
typedef unsigned char u8;

extern u8 D_001A7BC8[];
extern int D_00139948[];

void func_002AD7B8(int a0)
{
    int i;
    int count;

    if (D_001A7BC8[a0] != 0)
        return;
    D_001A7BC8[a0] = 1;
    if (a0 >= 0x15 && a0 != 24)
        return;
    count = 0;
    for (i = 0; i < 28; i++)
        if (D_00139948[i] != 0)
            count++;
    D_00139948[count] = a0;
}
