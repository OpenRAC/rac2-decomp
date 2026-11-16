#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern char *g_path_l05_entry_table MACRO_ADDR;
extern char *g_feltzin_target_mobys MACRO_ADDR;
extern char g_ship_record_position[] MACRO_ADDR;
extern TI128 g_projectile_pos_scratch;
extern void FastVecScale(char *, char *, char *, float);
extern void FastVecAdd(char *, char *, char *);
extern int coll_process_hit(char *, int, char *, int, float);

/* Builds the object's 0x30 block from a bound record and, when the lookup succeeds,
   its colour constant. */
/* Moves the ship's saved position back by a given amount and sets the ship's color if the model lookup works. */
void ship_update_record_transform(char *object, float strength)
{
    float local[4];
    char *entry = (char *)((*(short *)(object + 0x84) << 5) + (int)g_path_l05_entry_table);
    char *sub = *(char **)(entry + 0x1C);
    char *record = g_feltzin_target_mobys + (*(int *)(sub + 0x20) << 8);

    FastVecScale((char *)local, object, entry, -strength);
    FastVecAdd(g_ship_record_position, g_ship_record_position, (char *)local);
    if (coll_process_hit(object + 0x30, 0x10, record, 0, 0.25f) != 0)
        *(TI128 *)(object + 0x30) = *(TI128 *)&g_projectile_pos_scratch;
}
