#include "common.h"
#define WBYTE(p, o) (*(unsigned char *)((char *)(p)+(o)))
#define WSHORT(p, o) (*(short *)((char *)(p)+(o)))
#define WINT(p, o) (*(int *)((char *)(p)+(o)))
#define WPTR(p, o) (*(char **)((char *)(p)+(o)))
typedef struct { unsigned int unknown; int data_offset, length, extra; } PackedHeaderCountView;
extern int func_L04_003A1540(const PackedHeaderCountView *);
extern void func_L04_003A1578(void *, int, int);
extern void func_0026FEB8(void *, ...);
extern void func_00282A28(void);
extern char D_L04_001AD968[], D_L04_001AD998[], D_L04_002C9880[];
extern char D_L04_001AD9B0[], D_L04_002C98D0[], D_L04_001AD9E0[];
extern void func_L04_003A14B8(void *, int);
typedef struct { int id; int offsets[2]; int size; } WaterHeaderSlot;
/* Register a model header and initialize both alternating water buffers. */
int func_L04_003A15C0(char *obj, int *count, int *used, WaterHeaderSlot *slots, int *buffer) {
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
        STUB_printf(D_L04_001AD968);
        STUB_printf(D_L04_001AD998, WSHORT(obj, 0xB2), WSHORT(obj, 0xAA));
        func_00282A28();
    }
    if (*count >= 6) {
        STUB_printf(D_L04_002C9880);
        STUB_printf(D_L04_001AD998, WSHORT(obj, 0xB2), WSHORT(obj, 0xAA));
        STUB_printf(D_L04_001AD9B0, *count, *used, 0x2000);
        func_00282A28();
    }
    i = *count;
    WINT(state, 0x1C) = i;
    size = func_L04_003A1540((PackedHeaderCountView *)WPTR(obj, 0x98));
    twice = size * 2;
    if (*used + twice > 0x2000) {
        STUB_printf(D_L04_002C98D0);
        STUB_printf(D_L04_001AD9E0, WSHORT(obj, 0xB2), WSHORT(obj, 0xAA), size);
        STUB_printf(D_L04_001AD9B0, *count, *used, 0x2000);
        func_00282A28();
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
    func_L04_003A14B8(obj, 0);
    WPTR(obj, 0x98) = (char *)(buffer + slots[i].offsets[1]);
    func_L04_003A14B8(obj, 7);
    func_L04_003A1578(obj, (int)slots, (int)buffer);
    return i;
}
