#include "include_asm.h"

extern int D_L20_001B20CC __attribute__((sda));
/* The five-entry state table is reached through $gp. */
extern int D_L20_001B20D8[5] __attribute__((sda));
extern int func_0032F680(int);

/* Picks which attack the enemy does next. It avoids repeating the same attack until all of them have been used. */
void func_L20_00442CD8(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    int mask, i, startIndex, forcedChoice;

    forcedChoice = D_L20_001B20CC;
    *(float *)(vars + 0x1838) = 50.0f;
    if (forcedChoice) {
        *(int *)(vars + 0x1834) = D_L20_001B20D8[forcedChoice - 1];
        if (*(int *)(vars + 0x1834) == 10)
            *(float *)(vars + 0x1838) = 30.0f;
    } else if (*(int *)(vars + 0x183C) == 0x12D3) {
        *(int *)(vars + 0x1834) = 11;
    } else {
        mask = 0;
        switch (*(int *)(vars + 0x182C)) {
        case 0:
            mask = 1;
            break;
        case 1:
            mask = 6;
            break;
        case 2:
            mask = 15;
            break;
        }
        if (*(int *)(vars + 0x184C) & mask)
            mask = *(int *)(vars + 0x184C) & mask;
        startIndex = func_0032F680(4);
        for (i = 0; i < 4; i++) {
            int bit = 1 << ((startIndex + i) % 4);

            if (bit & mask) {
                *(int *)(vars + 0x184C) &= ~bit;
                switch (bit) {
                case 1:
                    *(int *)(vars + 0x1834) = 7;
                    break;
                case 2:
                    *(int *)(vars + 0x1834) = 10;
                    break;
                case 4:
                    *(int *)(vars + 0x1834) = 9;
                    break;
                case 8:
                    *(int *)(vars + 0x1834) = 8;
                    break;
                }
                break;
            }
        }
    }
}
