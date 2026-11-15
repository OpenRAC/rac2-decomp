#include "common.h"

/* The single on-screen notice slot: D_001A8C64 is its owner (0 = free), D_001B1D48 the text id.
 * A global that is both read and written here is reached under two names (the `_1` alias for the
 * write), as retail keeps a separate absolute address for each access. D_001A8C60 is stored both
 * $gp-relative and absolutely, so its `_1` name is the $gp view. */
extern int g_notice_owner MACRO_ADDR;
extern int D_001A8C64_1 MACRO_ADDR;
extern int D_001A8C60 MACRO_ADDR;
extern int D_001A8C60_1 __attribute__((sda));
extern int g_notice_text_id MACRO_ADDR;
extern int D_001B1D48_1 MACRO_ADDR;
extern int GetLocalizedString(int);
extern void func_0029CCD8(int, int);

/* Tries to take the notice slot for an owner and show a text. */
int TryClaimNotice(int owner, int text_id, int style)
{
    int current = g_notice_owner;

    if (current == owner) {
        if (text_id != 0)
            func_0029CCD8(GetLocalizedString(text_id), style);
        g_notice_text_id = text_id;
        D_001A8C60_1 = 2;
        return 2;
    }
    if (current == 0) {
        if (text_id != 0)
            func_0029CCD8(GetLocalizedString(text_id), style);
        D_001A8C64_1 = owner;
        D_001A8C60 = 2;
        D_001B1D48_1 = text_id;
        return 1;
    }
    return 0;
}

/* Like TryClaimNotice but takes over the slot when it is already used. */
int ForceClaimNotice(int owner, int text_id, int style)
{
    int result = TryClaimNotice(owner, text_id, style);

    if (result == 0) {
        if (text_id != 0) {
            func_0029CCD8(GetLocalizedString(text_id), style);
            D_001A8C60 = style;
            result = 3;
        } else {
            D_001A8C60_1 = style;
            result = 3;
        }
        D_001A8C64_1 = owner;
        D_001B1D48_1 = text_id;
    }
    return result;
}
