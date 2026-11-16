#include "names.h"
/* func_L01_00324550: variadic, built with -mastra-quad-saves and -frac2-narrow-saves-below.
   register_precision keeps $ra's save at 64 bits; the narrower save takes the lower slot. */
#include "common.h"
extern char *GetLocalizedString(int);
extern void text_expand_number_template(char *, char *, int *);
extern void hud_play_sound_effect(int);
extern void STUB_printf(const char *, ...);
extern const char g_str_text_id_debug_fmt[];
void text_print_localized_formatted(int id, ...) __attribute__((register_precision(ra, 64)));
/* Prints a message from its text id with extra values filled in. If the text is missing, it logs the id instead. */
void text_print_localized_formatted(int id, ...)
{
    char text[0x200];
    char *format = (char *)GetLocalizedString(id);
    if (format) {
        /* The seven saved integer argument slots are forwarded. */
        text_expand_number_template(text, format, (int *)((char *)__builtin_next_arg(id) - 0x38));
        hud_play_sound_effect((int)text);
    } else STUB_printf(g_str_text_id_debug_fmt, id);
}
