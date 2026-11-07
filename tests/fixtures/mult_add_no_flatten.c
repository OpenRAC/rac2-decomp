/* Authored controls for the optional unflattened giv expansion; no game code. */
typedef struct { int word[4]; } Slot;
extern Slot history[8][25];
extern int sink[8][25];

/* Shift one row up by a slot: the source cursor starts at row + (history - 16). */
void shift_row(int row, int last)
{
    int slot;

    for (slot = last; slot > 0; --slot)
        __asm__ __volatile__("lq $2,0x0(%1)\n\tsq $2,0x0(%0)"
                             : : "r"(&history[row][slot]), "r"(&history[row][slot - 1]) : "$2");
}

/* One cursor and no constant offset: the expansion has nothing to regroup. */
void clear_row(int row, int last)
{
    int slot;

    for (slot = last; slot > 0; --slot)
        sink[row][slot] = 0;
}
