#include "include_asm.h"
#include "names.h"

typedef struct { char pad[0x32C]; int base; int offset; int count; } Table26FE48;
extern Table26FE48 g_copy_setup_data;
extern char g_setup_entry_buffer[];
extern int g_pif_vram_address __attribute__((sda));
extern unsigned long long g_disc_table_pif_word __attribute__((sda));
extern int load_read_disc_with_pause(char *, int, int);
extern void LoadPifAsPSMT8H(char *, unsigned long long *, int, int);

void tex_load_pif_from_disc_table_pal(void)
{
    unsigned long long local[4];
    char *data = g_setup_entry_buffer;
    load_read_disc_with_pause(data, g_copy_setup_data.offset + g_copy_setup_data.base, g_copy_setup_data.count);
    LoadPifAsPSMT8H(data, local, g_pif_vram_address, 0x3FFC00);
    *(volatile unsigned long long *)&g_disc_table_pif_word = local[0];
}

