#include "include_asm.h"
#include "names.h"

extern unsigned int g_path_l09_table[];
extern int path_follow_nodes(char *object, unsigned int entry);

/* Looks up the entry for an index in the level table and checks it against the object. Returns 0 if there is no entry. */
int path_check_entry_for_moby_pal(char *object, int index)
{
    unsigned int entry;

    if (index == -1)
        return 0;
    entry = g_path_l09_table[index];
    if (entry == 0)
        return 0;
    return path_follow_nodes(object, entry);
}

