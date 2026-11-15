#include "include_asm.h"
#include "names.h"

/* The first table column uses a GP address; the other columns use absolute
 * addresses. Keep the compiler at -G8 and assemble with -G64 for this table. */
typedef struct { unsigned char pad[0x9C]; unsigned char bits; } Flags;
extern Flags D_001395B8;
extern int g_current_map_index __attribute__((section(".sdata")));
extern int D_L00_001A9010 __attribute__((section(".sdata")));
extern int D_L00_001A99F0[] __attribute__((section(".sdata")));
extern int D_L00_001A9A00[] __attribute__((section(".sdata")));
extern int D_L00_001A9A10[16] __attribute__((sda));
extern int D_L00_001A9A14[] __attribute__((section(".sdata")));
extern int D_L00_001A9A18[] __attribute__((section(".sdata")));
extern int D_L00_001A9A1C[] __attribute__((section(".sdata")));
typedef struct { int x[4]; } IndexMap;
extern IndexMap D_L00_001A9A50;
extern void level_clear_grid_bits_in_rect(int, int, int, int);
extern int moby_get_current_variant_index(void);

/* Dispatch a level-specific event once for its corresponding state bit. */
int level_dispatch_event_once(void)
{
    IndexMap map = D_L00_001A9A50;
    if (g_current_map_index == 2 && D_L00_001A9010 && ((D_001395B8.bits ^ 1) & 1)) {
        level_clear_grid_bits_in_rect(D_L00_001A99F0[0], D_L00_001A99F0[1],
                            D_L00_001A99F0[2], D_L00_001A99F0[3]);
        D_001395B8.bits |= 1;
    } else if (g_current_map_index == 11 && D_L00_001A9010 && !(D_001395B8.bits & 2)) {
        level_clear_grid_bits_in_rect(D_L00_001A9A00[0], D_L00_001A9A00[1],
                            D_L00_001A9A00[2], D_L00_001A9A00[3]);
        D_001395B8.bits |= 2;
    } else if (g_current_map_index == 7 && moby_get_current_variant_index() >= 0) {
        int i = moby_get_current_variant_index();
        int bit = map.x[i];
        if ((unsigned)bit >= 8 || (((D_001395B8.bits >> bit) ^ 1) & 1)) {
            if ((unsigned)bit < 8) D_001395B8.bits |= 1 << bit;
            level_clear_grid_bits_in_rect(D_L00_001A9A10[i * 4], D_L00_001A9A14[i * 4],
                                D_L00_001A9A18[i * 4], D_L00_001A9A1C[i * 4]);
        }
    }
    return 0;
}
