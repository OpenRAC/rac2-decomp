/* Authored controls for the optional same-block zero copy; no game code. */
extern int table[];
extern void touch(void);

/* The zero and its copy share a block: with the option `i = result` stays a register copy. */
int same_block(int value, int key)
{
    int result = 0;
    int i = result;

    while (table[i] != 0 && i < 8 && table[i] != key)
        i++;
    if (table[i] != 0)
        result = value == table[i + 1];
    return result;
}

/* Control: a call ends the block between the zero and the copy, so it is folded either way. */
int other_block(int value, int key)
{
    int result = 0;
    int i;

    touch();
    i = result;
    while (table[i] != 0 && i < 8 && table[i] != key)
        i++;
    if (table[i] != 0)
        result = value == table[i + 1];
    return result;
}
