#include "names.h"
/* Copies the xyz of the first vector of the object's 32-byte entry in the D_L05_001B1EC4
   table (index at +0x84) to its record's +0x20 with w cleared and on into +0x30, then
   hands the entry's second vector, w cleared, to func_002833F0. */
#include "include_asm.h"
#include "names.h"

#define MACRO_ADDR __attribute__((section(".sdata")))

typedef int TI128 __attribute__((mode(TI)));

extern char *g_path_l05_entry_table MACRO_ADDR;
extern void euler_rotation_basis(void *, void *);

typedef struct {
    float x;
    float y;
    float z;
    unsigned int w;
} V4;

void cam_load_entry_vectors(char *object)
{
    char buf[16];
    int table = (int)g_path_l05_entry_table;
    char *record = *(char **)(object + 0x70);
    V4 *dst = (V4 *)(record + 0x20);
    V4 *src = (V4 *)(*(short *)(object + 0x84) * 32 + table);
    V4 *second;
    V4 *sp = (V4 *)buf;

    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
    dst->w = 0;
    *(TI128 *)(object + 0x30) = *(TI128 *)dst;
    second = (V4 *)(*(short *)(object + 0x84) * 32 + table);
    second++;
    sp->x = second->x;
    sp->y = second->y;
    sp->z = second->z;
    sp->w = 0;
    euler_rotation_basis(object, buf);
}
