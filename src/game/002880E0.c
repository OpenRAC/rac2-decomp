#include "include_asm.h"

typedef struct { int id; int value; } MappingEntry;

typedef struct { int v[12]; } Blob;

typedef struct {
    unsigned int marker;
    unsigned char reserved04[0x38];
    unsigned short class_code;
    unsigned char reserved3E[0xa2];
} MappedClassEntry;

typedef int s32;

typedef unsigned char u8;

typedef unsigned int u32;

extern MappingEntry D_002403C0[];

extern Blob D_L00_001A8E60;

extern unsigned char D_00139568[];

extern MappedClassEntry D_L00_00262570[];

extern s32 func_00115484(u8 *, s32, s32);

extern void func_002889B8(unsigned char *);

typedef struct {
    int word00;
    unsigned char byte04;
    unsigned char pad05[7];
    int word0C;
    unsigned char pad10[0x3A];
    short child;
    short parent;
    unsigned char pad4E[0x32];
    int word80;
    unsigned char pad84[4];
    unsigned short half88;
    unsigned char pad8A[8];
    unsigned short half92;
    unsigned char pad94[0x4C];
} __attribute__((aligned(16))) ClassRecord;

/* a pending table row: five halfwords, the value compared at +6 */
typedef struct {
    short id;
    short pad0;
    short pad1;
    short value;
    short pad2;
} PendingEntry;

extern ClassRecord D_00239BA0[];

extern int D_001A73B8[] __attribute__((section(".sdata")));

extern PendingEntry D_0025E328[];

extern int func_00288188(int);

/* Find a mapped record by its unsigned halfword class and return its opaque word. */

/* func_002889B8 : clears three fields, initializes a block, then sets two flags */

/* 48-byte `ldl/ldr` → `sdl/sdr` stack copy of an absolute global, then a */
int func_002880E0(int x)
{
    Blob b;
    int i;
    b = D_L00_001A8E60;
    for (i = 0; b.v[i]; i++)
        if (x == b.v[i])
            return 1;
    return 0;
}


void func_00288208(int a0)
{
    ClassRecord *record;
    short *p;
    int i;

    if (func_00288188(a0) == 0)
        return;
    if (D_0025E328[0].value != -1) {
        p = &D_0025E328[0].value;
        do {
            if (a0 == *p)
                return;
            p += 5;
        } while (*p != -1);
    }
    record = &D_00239BA0[D_00139568[a0]];
    if (record->word0C != 0)
        return;
    if (func_002880E0(a0) != 0)
        return;
    for (i = 0; i < 8; i++) {
        if (D_001A73B8[i] == 0 || D_001A73B8[i] == a0)
            break;
    }
    if (i < 8)
        D_001A73B8[i] = a0;
}




/* search56 byte-mapped E0 records by U16class3C, return opaque32 marker0 elsezero */
unsigned int func_002884B0(unsigned int key)
{
    int i;
    for (i = 0; i < 56; i++) {
        MappedClassEntry *record = &D_L00_00262570[D_00139568[i]];
        if (record->class_code == key)
            return record->marker;
    }
    return 0;
}

/* the six action tables of the selector and its flag */
typedef struct {
    void *slot[6];
    int flag;
} SlotTable;

extern SlotTable ref_L00_00288508_00;

extern unsigned short D_0018C964;

extern int func_00288E18(int, int);

extern void func_002B0A18(int, int);

/* Pick the action of the mapped class of PARAM, then hand it to the game. */
void func_00288508(int param)
{
    SlotTable table;
    int code;
    int i;

    if (param == 10) {
        func_00288E18(0x9F8, 0x4F);
    } else if (param == 27) {
        func_00288E18(0x9F7, 0x4E);
    } else if (D_0018C964 == 0) {
        func_00288E18(0x9AA, 1);
    }

    code = -1;
    table = ref_L00_00288508_00;
    {
        MappedClassEntry *entry = &D_L00_00262570[D_00139568[param]];
        int *p = 0;
        if (entry->reserved04[0] < 6) {
            p = (int *)table.slot[((u8 *)entry)[4]];
        }
        if (p) {
            for (i = 0; p[i] != -1; i += 2) {
                if (p[i] == param) { code = p[i + 1]; break; }
            }
        }
    }
    if (param == 10) {
        u8 *entry2 = (u8 *)&D_L00_00262570[D_00139568[10]];
        int kind2 = entry2[4];
        if (kind2 >= 2) code = 0x1296;
        if (kind2 >= 3) code = 0x1297;
        if (kind2 >= 4) code = 0x1296;
        if (kind2 >= 5) code = 0x1297;
    }
    if (code >= 0)
        func_002B0A18(code, -1);
    else
        func_002B0A18(0, -1);
}

extern int func_00288D58(void);

/* True when the id is in the mapping table and its value is at or past the
   table's bound while still inside the small id range. */
int func_002886C8(int id, int value)
{
    int i;

    if (id == 9 && func_00288D58() != 0)
        return 1;
    for (i = 0; D_002403C0[i].id != -2; i++) {
        if (id == D_002403C0[i].id && value >= D_002403C0[i].value && value < 0x15)
            return 1;
    }
    return 0;
}

int func_00288768(int value) {
    int i;
    for (i = 0; D_002403C0[i].id != -2; i++)
        if (value == D_002403C0[i].id) return 1;
    return 0;
}


/* Walks to the root of the chain index is in, then depth links down it, and
   copies that entry to dst when its kind byte equals depth.  Returns 1 when
   copied. */
int func_00288870(ClassRecord *dst, int index, int depth)
{
    int ret = 0;
    int i;
    int n;

    if (depth < 0xFF) {
        i = index;
        while (D_00239BA0[i].parent != 0)
            i = D_00239BA0[i].parent;
        for (n = 0; n < depth && D_00239BA0[i].child != 0; n++)
            i = D_00239BA0[i].child;
        if (D_00239BA0[i].byte04 == depth) {
            ret = 1;
            *dst = D_00239BA0[i];
        }
    }
    return ret;
}



void func_002889B8(u8 *a0) {
    *(s32 *)(a0 + 0x30) = 0;
    *(s32 *)(a0 + 0x34) = 0;
    *(s32 *)(a0 + 0x38) = 0;
    func_00115484(a0 + 8, 0xcd, 0x28);
    *(s32 *)(a0 + 0x44) = 0;
    *(s32 *)(a0 + 0x40) = 1;
}

s32 func_00288A00(u8 *a0,s32 *a1,s32 *a2) {
 s32 *values,*flags; s32 idx;
 if(*(s32 *)(a0+0x38)==0) return 0;
 if(--*(s32 *)(a0+0x38)==0) *(s32 *)(a0+0x44)=0;
 values=(s32 *)(a0+8); flags=(s32 *)(a0+12);
 *a1=*(s32 *)((u32)values+(*(s32 *)(a0+0x34)<<3));
 *a2=*(s32 *)((u32)flags+(*(s32 *)(a0+0x34)<<3));
 values=(s32 *)((u32)values+(*(s32 *)(a0+0x34)<<3)); *values=-1;
 flags=(s32 *)((u32)flags+(*(s32 *)(a0+0x34)<<3)); *flags=-1;
 idx=*(s32 *)(a0+0x34)+1;
 if(idx==5) idx=0;
 *(s32 *)(a0+0x34)=idx;
 return 1;
}

s32 func_00288AA0(u8 *a0,s32 a1) {
 s32 v;
 if(*(s32 *)(a0+0x38)==5 || *(s32 *)(a0+0x44)!=0) return 0;
 *(s32 *)((u32)a0+(*(s32 *)(a0+0x30)<<3)+8)=a1;
 *(u32 *)((u32)a0+(*(s32 *)(a0+0x30)<<3)+12)=(u32)(a1-0x20U)<0x91;
 v=*(s32 *)(a0+0x30)+1;
 if(v==5) v=0;
 *(s32 *)(a0+0x38)=*(s32 *)(a0+0x38)+1;
 *(s32 *)(a0+0x30)=v;
 return 1;
}
