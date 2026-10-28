/* func_002D8338 - 372 bytes.  Worker attempt, 27 October 2026 (draft below).

   Logic is right (states 0/1, 20 bytes short: 344-360 depending on shape).
   Retail dispatch: s0=1 held in a saved reg for whole function; beq state,s0
   -> state1 block (placed after state0 block); slti state<2; beql -> return
   0; bnel state!=0 -> return 0; then lh 63AC test in each block. Blocks in
   retail order: state0 first, state1 second.
   Tried: if(0)/else if(1) -> 352 B; switch 0,1 -> 360; if(1) first -> 348;
   switch 1,0 -> 344. None reproduces s0=1 and the 3-step test. */

/* in src/game/002D5E98.c replacing the INCLUDE_ASM; uses D_001A63AC, D_001F2958, D_0014B540, D_001F2840, D_001B1840(sda), func_002B7B18 already declared above */
extern unsigned char D_001A7BB4;
extern void func_00282AB0(char *, char *, int);
extern char D_00254E78[];

int func_002D8338(char *object)
{
    int state = *(int *)(object + 0x50);

    switch (state) {
    case 1:
        if (D_001A63AC == 0) {
            char *base = (char *)&D_001F2840;
            char *data = *(char **)(base + 0x118);
            int *entry = (int *)(data + ((int *)data)[D_001A7BB4]);
            int count = entry[0];
            int size = entry[1];
            char *q;
            int i;

            func_00282AB0(data, (char *)(entry + 2), ((size + 3) & -4) - 8);
            *(int *)(object + 0x54) = D_001B1840;
            *(int *)(object + 0x38) = *(int *)(D_00254E78 + 0x2C);
            *(int *)(D_00254E78 + 0x2C) = count;
            D_001B1840 = *(int *)(base + 0x118);
            q = *(char **)(base + 0x118);
            for (i = 0; i < *(int *)(D_00254E78 + 0x2C); i++)
                *(int *)(q + i * 16) += (int)(q - 8);
            *(int *)(object + 0x10) &= ~4;
            *(int *)(object + 0x50) = 2;
        }
        break;
    case 0:
        if (D_001A63AC == 0) {
            if (func_002B7B18(D_001F2958, D_0014B540.start + D_0014B540.offset, D_0014B540.length) != 0)
                *(int *)(object + 0x50) = 1;
            else
                *(int *)(object + 0x50) = 3;
        }
        break;
    }
    return 0;
}
