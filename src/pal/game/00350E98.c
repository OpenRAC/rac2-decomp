#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned int u32;
typedef struct {
    u8 pad00[8];
    u8 f08;
    u8 pad09[0x3f];
    u32 *f48[8];
} EntryTable;
typedef struct {
    u8 pad00[0x10];
    u8 f10;
    u8 pad11[2];
    u8 f13;
    u8 pad14[8];
    u32 f1c[8];
} Entry;
typedef struct {
    u8 pad00[0x24];
    EntryTable *f24;
    u8 pad28[0x18];
    u8 f40;
    u8 f41;
    u8 f42;
    u8 f43;
    u8 pad44[0x14];
    char *f58;
    char *f5c;
} SlotObject;
extern void func_0026F790(char *, long long);
extern void func_PAL_002A0F68(char *);
extern void func_002A1130(u32 *, u32, long long, u32);
extern void func_002A0F48(char *);

void func_PAL_00350E98(char *obj)
{
    char *sub = obj + 0xC00;
    SlotObject *s = (SlotObject *)sub;

    func_0026F790(sub, 0);
    func_PAL_002A0F68(sub);
    if (s->f42 != 0xFF) {
        EntryTable *table = s->f24;
        Entry *entry = table->f48[s->f42];
        u32 *target = (u32 *)((char *)&entry->f1c[entry->f10] + entry->f13 * 4);
        func_002A1130(target, entry->f1c[s->f40], (long long)obj, table->f08);
        s->f58 = obj;
    }
    if (s->f43 != 0xFF) {
        EntryTable *table = s->f24;
        Entry *entry = table->f48[s->f43];
        u32 *target = (u32 *)((char *)&entry->f1c[entry->f10] + entry->f13 * 4);
        func_002A1130(target, entry->f1c[s->f41], (long long)(obj + 0x600), table->f08);
        s->f5c = obj + 0x600;
    }
    func_002A0F48(sub);
}

