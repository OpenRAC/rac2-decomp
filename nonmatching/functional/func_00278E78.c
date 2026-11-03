/* functional: high. Same reads and result as retail. */
extern char D_001BAF80[];

/* The low five bits of the word at D_001BAF80 + 0x1C, or -1 when that word is negative or its low five bits are all set. */
int func_00278E78(void)
{
    int value = *(int *)(D_001BAF80 + 0x1C);

    if (value < 0) {
        return -1;
    }
    value &= 31;
    if (value == 31) {
        return -1;
    }
    return value;
}
