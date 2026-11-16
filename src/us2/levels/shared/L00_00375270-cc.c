/* func_US2_L00_00375270, the USA v2.00 copy of func_L00_00373F48: the same C, where rename func_002FB1A0 becomes func_US2_002FC008. */
#include "common.h"

/* Purchase confirmation states of the shop menu. Needs -G64 (gp-relative runtime menu parameters). */
typedef struct { int value; int pad[3]; } PurchaseRow;
typedef union {
    struct { char pad[0x80]; int index, state; } head;
    struct { char prefix[0x140]; PurchaseRow rows[0]; } category;
    struct { char prefix[0x144]; PurchaseRow rows[0]; } group;
    struct { char prefix[0x148]; PurchaseRow rows[0]; } cost;
} PurchaseModel;
extern PurchaseModel g_purchase_menu_model;
extern char g_pad_state[];
/* Retail rereads this byte between its bit test and update at 003742B0/003742C4. */
extern unsigned char g_movie_seen_flags[] MACRO_ADDR;
extern unsigned char g_item_slot_to_record[];
typedef struct { char pad[0x98]; int flag[3]; char tail[0x3C]; } Metadata;
extern char g_weapon_l00_table[];
/* Runtime menu parameters; the element count belongs to the selected menu. */
extern int g_spawn_second_mode_table[] SDATA(D_L00_001AD4F0);
extern void ref_L00_00373F48_00(void);
extern int save_count_items_above_baseline(void);
extern int PlayMobySound(int, int, char *);
extern char *GetLocalizedString(int);
extern void shop_set_message_text(void *);
extern int level_try_spend_counter(int);
extern void level_spawn_on_second_mode(int);
extern void BuildShopChannelList(void);
extern void PrepareVendorSelectionPreview_us2(void);

void UpdateItemPurchaseConfirmation_us2(int *answer) {
    PurchaseModel *model = &g_purchase_menu_model;
    int cost = model->cost.rows[model->head.index].value;
    int state = model->head.state;
    int category;
    int group;
    int enabled;
    if (state == 1) {
        if (*(int *)((char *)model + 0x740) != 0) {
            ref_L00_00373F48_00();
            g_purchase_menu_model.head.state = 2;
        } else g_purchase_menu_model.head.state = 0;
    } else if (state == 2) {
        if (*(unsigned int *)(g_pad_state + 0x1C4) & 0x10) {
            *answer = 0;
            g_purchase_menu_model.head.state = 4;
        } else if (*(unsigned int *)(g_pad_state + 0x1C4) & 0x40)
            g_purchase_menu_model.head.state = 3;
    } else if (state == 3) {
        *answer = 0;
        if (save_count_items_above_baseline() < cost) {
            PlayMobySound(2, 17, *(char **)((char *)model + 0x28));
            g_purchase_menu_model.head.state = 4;
        } else {
            int g = g_purchase_menu_model.group.rows[model->head.index].value;
            int c = g_purchase_menu_model.category.rows[model->head.index].value;
            if ((unsigned long)g_movie_seen_flags[g] & ((1U << (c * 2)) & 255UL)) *answer = 0;
            else *answer = 1;
            g_purchase_menu_model.head.state = 4;
        }
    } else if (state == 4) {
        if (*answer != 0) {
        if (save_count_items_above_baseline() >= cost) {
            shop_set_message_text((void *)GetLocalizedString(0x2c61));
            PlayMobySound(7, 17, *(char **)((char *)model + 0x28));
            level_try_spend_counter(cost);
            level_spawn_on_second_mode(g_spawn_second_mode_table[model->head.index]);
            category = g_purchase_menu_model.category.rows[g_purchase_menu_model.head.index].value;
            group = g_purchase_menu_model.group.rows[g_purchase_menu_model.head.index].value;
            switch (category) {
            case 0: enabled = ((Metadata *)(g_weapon_l00_table + g_item_slot_to_record[group] * 0xE0))->flag[0]; break;
            case 1: enabled = ((Metadata *)(g_weapon_l00_table + g_item_slot_to_record[group] * 0xE0))->flag[1]; break;
            case 2: enabled = ((Metadata *)(g_weapon_l00_table + g_item_slot_to_record[group] * 0xE0))->flag[2]; break;
            default: enabled = 0; break;
            }
            if (enabled) { int t = (1 << (category * 2)) | g_movie_seen_flags[group]; g_movie_seen_flags[group] = t; }
            {
            int category2 = g_purchase_menu_model.category.rows[g_purchase_menu_model.head.index].value;
            int group2 = g_purchase_menu_model.group.rows[g_purchase_menu_model.head.index].value;
            int enabled2;
            switch (category2) {
            case 0: enabled2 = ((Metadata *)(g_weapon_l00_table + g_item_slot_to_record[group2] * 0xE0))->flag[0]; break;
            case 1: enabled2 = ((Metadata *)(g_weapon_l00_table + g_item_slot_to_record[group2] * 0xE0))->flag[1]; break;
            case 2: enabled2 = ((Metadata *)(g_weapon_l00_table + g_item_slot_to_record[group2] * 0xE0))->flag[2]; break;
            default: enabled2 = 0; break;
            }
            if (enabled2) {
                unsigned long m = (1U << (category2 * 2)) & 255UL;
                if ((unsigned long)g_movie_seen_flags[group2] & m) {
                    int t = (1 << (category2 * 2 + 1)) | g_movie_seen_flags[group2];
                    g_movie_seen_flags[group2] = t;
                }
            }
            }
            BuildShopChannelList();
        } else {
            shop_set_message_text((void *)GetLocalizedString(0x2c62));
            PlayMobySound(0, 17, *(char **)((char *)model + 0x28));
        }
        } else PlayMobySound(0, 17, *(char **)((char *)model + 0x28));
        g_purchase_menu_model.head.state = 0;
        PrepareVendorSelectionPreview_us2();
    }
}
