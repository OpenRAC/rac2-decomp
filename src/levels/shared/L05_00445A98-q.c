#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    char reserved00[0x1C];
    char *row;
} TableEntry;

extern char *g_hero_l05_moby;
extern TableEntry *g_path_l05_entry_table MACRO_ADDR;
extern char *g_feltzin_target_mobys MACRO_ADDR;
extern TI128 g_ship_saved_position MACRO_ADDR;
extern TI128 g_ship_saved_matrix_row0 MACRO_ADDR;
extern TI128 g_ship_saved_matrix_row1 MACRO_ADDR;
extern TI128 g_ship_saved_matrix_row2 MACRO_ADDR;
extern void cam_init_state(char *);

/* Saves the four 16-byte blocks of the state record and hands its bound block on. */
/* Saves the ship's position and direction when the camera is in ship mode, and copies its position to the linked record. */
void ship_save_transform_state(void)
{
    char *state = g_hero_l05_moby;

    if (*(short *)(state + 0x86) != 0x19)
        return;
    cam_init_state(state);
    g_ship_saved_position = *(TI128 *)(state + 0x30);
    g_ship_saved_matrix_row0 = *(TI128 *)(state + 0x00);
    g_ship_saved_matrix_row1 = *(TI128 *)(state + 0x10);
    g_ship_saved_matrix_row2 = *(TI128 *)(state + 0x20);
    {
        char *sub = g_path_l05_entry_table[*(short *)(state + 0x84)].row;
        char *dst = g_feltzin_target_mobys + (*(int *)(sub + 0x20) << 8) + 0x10;

        *(TI128 *)dst = *(TI128 *)(state + 0x30);
    }
}
