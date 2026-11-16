#include "include_asm.h"
#include "names.h"

extern int g_yeedil_forced_attack __attribute__((sda));
/* The five-entry state table is reached through $gp. */
extern int g_yeedil_attack_delay_table[5] __attribute__((sda));
extern int func_0032F680(int);

/* Picks which attack the enemy does next. It avoids repeating the same attack until all of them have been used. */
void yeedil_boss_choose_attack(char *moby) {
    char *vars = *(char **)(moby + 0x68);
    int mask, i, start_index, forced_choice;

    forced_choice = g_yeedil_forced_attack;
    *(float *)(vars + 0x1838) = 50.0f;
    if (forced_choice) {
        *(int *)(vars + 0x1834) = g_yeedil_attack_delay_table[forced_choice - 1];
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
        start_index = func_0032F680(4);
        for (i = 0; i < 4; i++) {
            int bit = 1 << ((start_index + i) % 4);

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
