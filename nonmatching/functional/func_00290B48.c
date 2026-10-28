/* functional: medium. fcheck SAME on all captured calls; same stores of the same values as retail, only allocation and store order differ. The two program-end references are the constants 0x351FC0 and 0x2000000 read off the retail words (boot build). */
extern void *func_00115484(void *, int, int);
extern char D_001BAEC0[];
extern int D_001B22B0;

void func_00290B48(void)
{
    int *state = (int *)D_001BAEC0;
    unsigned int start, first, second, third;
    unsigned int top, block1, block2, block3, block4, block5;

    func_00115484(state, 0, 0x9C);
    top = 0x2000000u - 0x8000;
    start = (0x351FC0u + 0x3FFF) & ~0x3FFF;
    block1 = top - 0x40000;
    block2 = block1 - 0x64000;
    first = start + D_001B22B0;
    block3 = block2 - 0x2C000;
    second = first + D_001B22B0;
    block4 = block3 - 0x8000;
    third = second + 0x100000;
    block5 = block4 - 0x14000;
    state[0x98 / 4] = 0x07200000;
    state[0] = 0;
    state[0x10 / 4] = first;
    state[0x74 / 4] = block4;
    state[0x68 / 4] = third;
    state[0x88 / 4] = 0x01FFC000;
    state[0x6C / 4] = block5;
    state[0x8C / 4] = 0x07000000;
    state[0x90 / 4] = 0x07100000;
    state[0x94 / 4] = 0x07180000;
    state[0x04 / 4] = 0x100000;
    state[0x08 / 4] = start;
    state[0x0C / 4] = start;
    state[0x14 / 4] = second;
    state[0x18 / 4] = third;
    state[0x84 / 4] = top;
    state[0x80 / 4] = block1;
    state[0x7C / 4] = block2;
    state[0x78 / 4] = block3;
    state[0x70 / 4] = block5;
}
