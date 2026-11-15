#include "include_asm.h"

#include "common.h"
typedef struct { int id, kind; int rest[4]; } ActionItem;
typedef struct { u8 pad[0x80]; int index, active; u8 gap[0xb8]; ActionItem items[0]; } ActionModel;
extern ActionModel g_purchase_menu_model;
#define MODEL ((u8 *)&D_L00_0022F7C0)
extern u8 g_item_slot_to_record[];
extern int g_item_ammo_counts[];
typedef struct {u8 pad[0x88]; unsigned short price; u8 pad2[4]; unsigned short limit; u8 rest[80];} ActionClass;
extern ActionClass g_weapon_l00_table[];
extern int g_player_bolts;
extern int g_is_pal_video;
extern float D_L00_001B25E0;
extern char *GetLocalizedString(int id);
extern int GetSelectedShopItemPrice(void);
extern int text_draw_centered_medium(int x, int y, unsigned long style, u8 *text, int length);
#define SELECTED (MODEL + D_L00_0022F7C0.index * 24)
#define KIND (*(int *)(SELECTED+0x144))
#define ENTRY (&D_L00_00262570[D_00139568[*(int *)(SELECTED+0x140)]])
#define CAPPED (D_00139688[*(int *)(SELECTED+0x140)] >= ENTRY->limit)
#define AFFORDABLE (D_001A79F8 >= ENTRY->price)
#define DRAW(X, ID) { \
    int baseRow = (int)(D_L00_001B25E0 * 164.0f + 0.5f); \
    int row = baseRow - 1; \
    if (!D_001A7B90) row = baseRow; \
    func_0027FB40((X), row, 0x80f0f0f0UL, (u8 *)func_00288FB8((ID)), -1); \
}

void func_US2_L00_00379000(void)
{
    if (g_purchase_menu_model.active) {
        if (KIND == 1 && CAPPED) {
            DRAW(420, 0x31B0);
        } else if (KIND == 1) {
            if (AFFORDABLE) {
                DRAW(80, 0x31B1);
            } else {
                DRAW(420, 0x31B0);
            }
        } else if (g_player_bolts >= GetSelectedShopItemPrice()) {
            DRAW(80, 0x31C7);
        } else {
            DRAW(420, 0x31B0);
        }
        if (KIND == 1 && CAPPED)
            return;
        if (KIND == 1) {
            if (!AFFORDABLE)
                return;
            DRAW(420, 0x31B0);
        } else {
            if (g_player_bolts < GetSelectedShopItemPrice())
                return;
            DRAW(420, 0x31C4);
        }
    } else {
        int stride = 24;
        u8 *kindBase = MODEL + 0x144;
        if ((*(int *)(kindBase + g_purchase_menu_model.index * stride) == 0 && g_player_bolts >= GetSelectedShopItemPrice()) ||
            (*(int *)(kindBase + g_purchase_menu_model.index * stride) == 1 && !CAPPED && AFFORDABLE)) {
            DRAW(80, 0x31B1);
        }
        DRAW(420, 0x2BE5);
    }
}
