#include "include_asm.h"

#include "common.h"
extern int *g_level_data_ptr MACRO_ADDR;
extern int g_hud_bank_buffer_size_a[];
typedef struct {
    int *header;
    void *table04, *table08, *table10, *table0C;
} HudBankArena;
extern HudBankArena g_hud_group_size_table MACRO_ADDR;
extern char g_str_hud_alloc_file[], g_str_hud_bank_a[], g_str_hud_bank_b[], g_str_hud_bank_c[], g_str_hud_bank_d[];
extern int g_loader_memory[];
extern void *hud_alloc_mem(int, int, char *, int);
extern void mem_fast_helper_c(void *, void *, int);
extern void hud_unpack_bank_data(int, void *);
extern int gfx_alloc_buffer_slot(void *, int, int, char *);
extern void Hud_SendResidentBank(int, void *, int);
extern void FlushCache(int);
extern void LinkHudBank(int, void *);

/* RAC1 loaders.c hud_load_banks supplies the arena layout and bank sequence. */
void hud_load_banks_us2(void)
{
    int *root = g_level_data_ptr;
    int i, bank_size;
    unsigned int bank1_qwords, bank3_qwords, bank4_qwords, bank5_qwords;
    int *resources;
    int *header;
    char *allocation_file;
    int *bank2_data;
    char *bank1_target;

    for (i = 0; i < 5; i++)
        g_hud_bank_buffer_size_a[i] = (root[9 + i * 2] + 63) & 0xffffffc0U;
    allocation_file = g_str_hud_alloc_file;
    resources = g_loader_memory;
    bank_size = (root[7]+63)&0xffffffc0U;
    header = hud_alloc_mem(bank_size, 0, allocation_file, 0x305);
    mem_fast_helper_c(header, (void *)(root[6] + (int)root), bank_size);
    g_hud_group_size_table.header = header;
    g_hud_group_size_table.table04 = (int *)((char *)header + header[1]);
    bank1_target = (char *)(resources[4] + 0x60000);
    g_hud_group_size_table.table08 = (int *)((char *)header + header[2]);
    g_hud_group_size_table.table0C = (int *)((char *)header + header[3]);
    g_hud_group_size_table.table10 = (int *)((char *)header + header[4]);
    if (header[0x15]) {
        bank1_qwords = ((root[9] + 63) & 0xffffffc0U) >> 4;
        hud_unpack_bank_data(0, bank1_target);
        g_hud_group_size_table.header[0x25] = gfx_alloc_buffer_slot((void *)(root[8] + (int)root), bank1_qwords, bank1_qwords, g_str_hud_bank_a);
        Hud_SendResidentBank(0, bank1_target, 1);
    }
    if (g_hud_group_size_table.header[0x16]) {
        bank2_data = hud_alloc_mem(g_hud_group_size_table.header[0x16], 0, allocation_file, 0x32D);
        hud_unpack_bank_data(1, bank2_data);
        FlushCache(0);
        LinkHudBank(1, bank2_data);
    }
    if (g_hud_group_size_table.header[0x17]) {
        bank3_qwords = ((root[13] + 63) & 0xffffffc0U) >> 4;
        g_hud_group_size_table.header[0x27] = gfx_alloc_buffer_slot((void *)(root[12] + (int)root), bank3_qwords, bank3_qwords, g_str_hud_bank_b);
    }
    if (g_hud_group_size_table.header[0x18]) {
        bank4_qwords = ((root[15] + 63) & 0xffffffc0U) >> 4;
        g_hud_group_size_table.header[0x28] = gfx_alloc_buffer_slot((void *)(root[14] + (int)root), bank4_qwords, bank4_qwords, g_str_hud_bank_c);
    }
    if (g_hud_group_size_table.header[0x19]) {
        bank5_qwords = ((root[17] + 63) & 0xffffffc0U) >> 4;
        g_hud_group_size_table.header[0x29] = gfx_alloc_buffer_slot((void *)(root[16] + (int)root), bank5_qwords, bank5_qwords, g_str_hud_bank_d);
    }
}
