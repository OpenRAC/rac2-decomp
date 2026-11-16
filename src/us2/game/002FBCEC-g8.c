/* func_US2_002FBCEC, the v2.00 boot copy of func_002FAE68 and the C of func_US2_L00_0037A5D0, where D_001A7A20
 * is a plain extern read with lui/lw. */
#include "include_asm.h"
#include "names.h"

/* Measured from func_002FAE68: the state it steps and the status block it tests. */
typedef struct { char pad[0x38]; int st; } CardPrompt;
typedef struct {
    char p0[0x8]; int f8;
    char p1[0x8]; int f14;
    char p2[0x4]; int f1C;
    char p3[0x88]; int fA8;
    char p4[0x8]; int fB4;
    char p5[0x4]; int fBC;
    char p6[0x9C]; int f15C;
    char p7[0x4]; int f164;
    int f168;
} CardStatus;
extern void *D_0026DBE0[];
extern CardPrompt g_vendor_menu_state;
extern CardStatus g_memcard_state;
extern int g_special_items_bought_flags;
extern void shop_set_message_text(char *);
extern void shop_mark_bought_special_items_owned(void);
extern char *GetLocalizedString(int);

/* func_US2_002FBCEC, the v2.00 copy of func_002FAE68: the same state machine, where the
 * prompts are looked up in the text table. */
void func_US2_002FBCEC(void) {
    {
    static void *rc2_labels[] = {&&rc2_case_0, &&rc2_case_1, &&rc2_case_2, &&rc2_case_3, &&rc2_case_4, &&rc2_case_5, &&rc2_case_6};
    unsigned int rc2_selector = (unsigned int)(g_vendor_menu_state.st);
    if (rc2_selector > 6U) goto rc2_default;
goto *D_0026DBE0[rc2_selector];

    rc2_case_0:
    rc2_case_2:
        if (g_memcard_state.f15C < 3 && g_memcard_state.f164 < 0 && g_memcard_state.f8 == 2) {
            if (g_memcard_state.f14 != 0) {
                g_memcard_state.f164 = 0x18;
                g_vendor_menu_state.st = 3;
                g_memcard_state.f168 = 0;
                goto rc2_switch_end;
            }
        }
        if (g_vendor_menu_state.st != 0) {
            g_vendor_menu_state.st = 4;
        } else {
            g_vendor_menu_state.st = 6;
        }
        goto rc2_switch_end;
    rc2_case_1:
    rc2_case_3:
        if (g_memcard_state.f15C < 3 && g_memcard_state.f164 < 0) {
            if (g_special_items_bought_flags & 0x80) {
                if (g_memcard_state.f1C == 1) {
                    shop_set_message_text((char *)GetLocalizedString(0x313A));
                } else if (g_memcard_state.f1C >= 3) {
                    shop_set_message_text((char *)GetLocalizedString(0x3138));
                } else {
                    shop_set_message_text((char *)GetLocalizedString(0x3139));
                }
            } else {
                shop_set_message_text((char *)GetLocalizedString(0x3137));
            }
            shop_mark_bought_special_items_owned();
            if (g_vendor_menu_state.st != 0) {
                g_vendor_menu_state.st = 4;
            } else {
                g_vendor_menu_state.st = 6;
            }
        }
        goto rc2_switch_end;
    rc2_case_4:
        if (g_memcard_state.f15C < 3 && g_memcard_state.f164 < 0 && g_memcard_state.fA8 == 2 && g_memcard_state.fB4 != 0) {
            g_memcard_state.f164 = 0x18;
            g_memcard_state.f168 = 1;
            g_vendor_menu_state.st = 5;
            goto rc2_switch_end;
        }
        g_vendor_menu_state.st = 6;
        goto rc2_switch_end;
    rc2_case_5:
        if (g_memcard_state.f15C < 3 && g_memcard_state.f164 < 0) {
            if (g_special_items_bought_flags & 0x80) {
                if (g_memcard_state.fBC == 1) {
                    shop_set_message_text((char *)GetLocalizedString(0x313A));
                } else if (g_memcard_state.fBC >= 3) {
                    shop_set_message_text((char *)GetLocalizedString(0x3138));
                } else {
                    shop_set_message_text((char *)GetLocalizedString(0x3139));
                }
            } else {
                shop_set_message_text((char *)GetLocalizedString(0x3137));
            }
            shop_mark_bought_special_items_owned();
            g_vendor_menu_state.st = 6;
        }
        goto rc2_switch_end;
    rc2_case_6:
        if (g_memcard_state.f15C < 3 && g_memcard_state.f164 < 0) {
            if (g_memcard_state.f1C == 0) {
                int a = g_memcard_state.f8;
                if (a == 2 && g_memcard_state.f14 != 0) {
                    g_vendor_menu_state.st = a;
                    goto rc2_switch_end;
                }
            }
            if (g_memcard_state.fBC == 0 && g_memcard_state.fA8 == 2 && g_memcard_state.fB4 != 0) {
                g_vendor_menu_state.st = 4;
            }
        }
        goto rc2_switch_end;
    rc2_default:
        goto rc2_switch_end;

rc2_switch_end: ;
}
}
