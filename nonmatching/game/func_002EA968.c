/* func_002EA968 - 320 bytes.  Worker attempt, 27 October 2026 (draft below).

   draft.c goes to src/game/002E7018-g8-qcopy.c with cflags line `-O2 -G8
   -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier`; marker removed from
   002E7018.c.
   Size matches (320). Remaining diff (boot place):
   - memset calls on D_001B1390/D_001B13D0: retail `lui a0; addiu a0; daddu
   a1,zero`, mine `lui a0; daddu a1; addiu a0`.
   - retail loads D_001BAEC0 +0x18,+0xC,+0x10 up front, then type (0x64($s0));
   mine loads +0x10,+0xC, type, then +0x18 later.
   - retail keeps table ptr in a0 and copies it to t1 (daddu t1,a0,zero)
   before loop; mine computes t1 = hdr+tableoff and counter in a2/t0 swapped.
   - retail does `lui at; sw a2,0x22B0(at)` right after `addu a0,v1,v0`, mine
   later.
   Tried: header read first, D_001B22B0 store before/after table, int vs char
   arrays, 2D array for the two buffers (worse), sda int for the gp quad
   (char[16]/struct 16 are not sda in -G8). */

#include "include_asm.h"
#include "common.h"

extern int ref_L00_002EA968_00 __attribute__((sda));
extern int ref_L00_002EA968_01 __attribute__((sda));

typedef struct { char pad[0x64]; int type; int zero; } Menu2EA968;
typedef struct { char pad[0x6C]; int start; int destination; int rows[0x46]; } List2EA968;
typedef struct { char pad[0xC]; int start; int end; int gap; int *header; } Range2EA968;
typedef struct { int offset; int count; } Entry2EA968;

extern Menu2EA968 D_00152C00;
extern List2EA968 D_001B8840;
extern Range2EA968 D_001BAEC0;
extern int D_001B1390[0x10];
extern int D_001B13D0[0x10];
extern int D_001B22B0;

extern int func_001163B0(void);
extern void func_00282A60(void *, int, int);
extern void func_00294070(int);

void func_002EA968(void)
{
    int *header;
    int *table;
    Entry2EA968 *entry;
    int base;
    int i;

    D_00152C00.type = (func_001163B0() >> 16) & 3;
    D_00152C00.zero = 0;
    qcopy(&ref_L00_002EA968_01, &ref_L00_002EA968_00);
    func_00282A60(&D_001B8840, 0, 0x1D0);
    func_00282A60(D_001B1390, 0, 0x40);
    func_00282A60(D_001B13D0, 0, 0x40);
    header = D_001BAEC0.header;
    base = D_001B22B0 - 0x60000;
    D_001B8840.start = D_001BAEC0.start + base;
    D_001B8840.destination = D_001BAEC0.end + base;
    table = header + 0x14 + D_00152C00.type;
    D_001B22B0 = base;
    header = (int *)((char *)header + header[1]);
    entry = (Entry2EA968 *)((char *)header + *table);
    if (entry->count != 0) {
        i = 0;
        do {
            D_001B8840.rows[i] = (int)header + *table + (entry->offset + 0x800);
            entry++;
            i++;
        } while (i < 0x46 && entry->count != 0);
    }
    func_00294070(0);
}
