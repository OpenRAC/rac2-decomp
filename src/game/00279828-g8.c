#include "common.h"

/* A -G8 unit (the profile from the file's name): a plain extern of at most eight bytes is then
   one assembler operand, and with its .extern only at the end of the file the assembler
   expands it to the retail's absolute lui + load through the destination register. -G0
   splits the address into a high-part register of its own. */

extern u8 g_language;
extern char Fd8e166aa_D_001B7F80[];

/* Turns the offsets in a loaded data table into real addresses so the entries can be used directly. */
void load_relocate_data_table_offsets(void)
{
    char *g = Fd8e166aa_D_001B7F80;
    int i = 0;
    int *table = *(int **)(g + 8);
    char *p = (char *)table + table[g_language];
    int n = *(int *)p;

    *(char **)(g + 12) = p + 8;
    *(int *)(g + 16) = n;
    for (i = 0; i < *(int *)(g + 16); i++) {
        char *q = *(char **)(g + 12);
        char *r = q - 8;

        *(int *)(q + i * 16) = *(int *)(q + i * 16) + (int)r;
    }
}
