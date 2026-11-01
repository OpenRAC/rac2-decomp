#include "include_asm.h"

typedef struct { int items[21]; } Table_002AF0A8;
extern const Table_002AF0A8 D_0026CB30;
extern void func_US2_002B1880(int, int);
extern void func_002B0CE0(int, int, int);

/* Plays the entry of the 21-entry table the clamped index picks; entry 3 goes through the
   other player. */
void func_US2_002AFF10(int index)
{
    Table_002AF0A8 table = D_0026CB30;

    if (index < 0)
        index = 0;
    if (index > 20)
        index = 20;
    if (index == 3)
        func_US2_002B1880(table.items[3], 0xF0);
    else
        func_002B0CE0(8, table.items[index], 0xB4);
}
