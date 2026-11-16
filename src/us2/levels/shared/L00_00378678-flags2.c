#include "include_asm.h"
#include "names.h"

extern int g_purchase_menu_model[];
extern float g_menu_slide_scale __attribute__((sda));
extern int g_player_bolts __attribute__((sda));
extern char *GetLocalizedString(int id);
extern void text_draw_medium(int sprite, int x, unsigned long color, int id, int y);
extern void text_draw_right_aligned_medium(int sprite, int x, unsigned long color, int id, int y);
typedef struct {
    int first;
    int second;
    int third;
} L00_003781B0_Cell;
#define L00_003781B0_X ((int)(D_L00_001B25E0 * 312.0f + 0.5f))

void func_US2_L00_00379560(void)
{
    if (g_purchase_menu_model[0x84 / 4] != 0) {
        L00_003781B0_Cell *cell = (L00_003781B0_Cell *)((char *)g_purchase_menu_model + 0x144);
        if (g_player_bolts >= cell[g_purchase_menu_model[0x80 / 4]].first) {
            text_draw_medium(0x28, L00_003781B0_X, 0x80F0F0F0UL, GetLocalizedString(0x31C7), -1);
            text_draw_right_aligned_medium(0x118, L00_003781B0_X, 0x80F0F0F0UL, GetLocalizedString(0x31C4), -1);
        } else {
            text_draw_right_aligned_medium(0x118, L00_003781B0_X, 0x80F0F0F0UL, GetLocalizedString(0x31B0), -1);
        }
    } else {
        L00_003781B0_Cell *cell = (L00_003781B0_Cell *)((char *)g_purchase_menu_model + 0x144);
        if (cell[g_purchase_menu_model[0x80 / 4]].first > 0)
            text_draw_medium(0x28, L00_003781B0_X, 0x80F0F0F0UL, GetLocalizedString(0x31B1), -1);
        text_draw_right_aligned_medium(0x118, L00_003781B0_X, 0x80F0F0F0UL, GetLocalizedString(0x2BE5), -1);
    }
}
