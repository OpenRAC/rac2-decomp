#include "common.h"
#define WBYTE(p, o) (*(unsigned char *)((char *)(p)+(o)))
#define WSHORT(p, o) (*(short *)((char *)(p)+(o)))
#define WINT(p, o) (*(int *)((char *)(p)+(o)))
#define WPTR(p, o) (*(char **)((char *)(p)+(o)))
typedef struct { unsigned int unknown; int data_offset, length, extra; } PackedHeaderCountView;
extern int gfx_get_packed_header_block_count(const PackedHeaderCountView *);
extern void water_select_table_slot(void *, int, int);
extern void STUB_printf(void *, ...);
extern void math_trap_always(void);
extern char g_str_water_header_msg[], g_str_water_header_fmt[], g_str_water_header_register[];
extern char g_str_water_header_count_fmt[], g_str_water_header_register_b[], g_str_water_header_size_fmt[];
extern void water_set_tag_bits(void *, int);
typedef struct { int id; int offsets[2]; int size; } WaterHeaderSlot;
/* Register a model header and initialize both alternating water buffers. */
int water_register_model_header(char *obj, int *count, int *used, WaterHeaderSlot *slots, int *buffer) {
    char *state = WPTR(obj, 0x68);
    int i = 0, size, twice, n;
    int *src, *dst, *dst2;
    for (; i < *count; i++) {
        if (slots[i].id == WSHORT(obj, 0xAA)) {
            WINT(state, 0x1C) = i;
            WPTR(obj, 0x98) = (char *)(buffer + slots[i].offsets[WBYTE(state, 0x14) & 1]);
            return i;
        }
    }
    if (!WPTR(obj, 0x98)) {
        STUB_printf(g_str_water_header_msg);
        STUB_printf(g_str_water_header_fmt, WSHORT(obj, 0xB2), WSHORT(obj, 0xAA));
        math_trap_always();
    }
    if (*count >= 6) {
        STUB_printf(g_str_water_header_register);
        STUB_printf(g_str_water_header_fmt, WSHORT(obj, 0xB2), WSHORT(obj, 0xAA));
        STUB_printf(g_str_water_header_count_fmt, *count, *used, 0x2000);
        math_trap_always();
    }
    i = *count;
    WINT(state, 0x1C) = i;
    size = gfx_get_packed_header_block_count((PackedHeaderCountView *)WPTR(obj, 0x98));
    twice = size * 2;
    if (*used + twice > 0x2000) {
        STUB_printf(g_str_water_header_register_b);
        STUB_printf(g_str_water_header_size_fmt, WSHORT(obj, 0xB2), WSHORT(obj, 0xAA), size);
        STUB_printf(g_str_water_header_count_fmt, *count, *used, 0x2000);
        math_trap_always();
    }
    slots[i].id = WSHORT(obj, 0xAA);
    slots[i].offsets[0] = *used;
    slots[i].offsets[1] = *used + size;
    slots[i].size = size;
    ++*count;
    *used += twice;
    src = (int *)WPTR(obj, 0x98);
    dst = buffer + slots[i].offsets[0];
    dst2 = buffer + slots[i].offsets[1];
    for (n = 0; n < size; n++) {
        *dst++ = *src;
        *dst2++ = *src++;
    }
    WPTR(obj, 0x98) = (char *)(buffer + slots[i].offsets[0]);
    water_set_tag_bits(obj, 0);
    WPTR(obj, 0x98) = (char *)(buffer + slots[i].offsets[1]);
    water_set_tag_bits(obj, 7);
    water_select_table_slot(obj, (int)slots, (int)buffer);
    return i;
}
