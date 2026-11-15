#include "names.h"
/* Keep the key lookup as a canonical call rather than inlining its level copy. */
extern int level_find_key_in_pair_table(int key);
extern void level_mark_table_entry_used(int index);

/* Looks up the table index for a key and then acts on that index. */
void level_apply_index_for_key(int key)
{
    level_mark_table_entry_used(level_find_key_in_pair_table(key));
}
