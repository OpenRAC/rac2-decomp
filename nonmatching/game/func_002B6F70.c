/* func_002B6F70 - 276 bytes.  Worker attempt, 27 October 2026 (draft below).

   Size 244 vs 276. Missing: dsll32/dsra32 on call args a0,a1 (ptr->long sign-
   ext), dsll32/dsrl32 on sp18 arg (u32 ptr->u64); register alloc differs
   (retail t2=slot, t6=flag, t5=id, t7=9).
   Tried: (long)(int) casts, (long)(u8*) base+off, (unsigned long)(u8*),
   unsigned sums: gcc elides the ext every time. */

typedef struct { int off; int pad; } F70Entry;
typedef struct { u8 pad[0x52FC]; u8 *base; F70Entry e[1]; } F70Table;
extern F70Table D_0014B540;
extern void func_002B7F58(int, long);
extern void func_00133340(long, long, int, int, short, int, int, int, int, int, void (*)(int, long), unsigned long);

void func_002B6F70(int slot, int flag, int id) {
    u8 *state = D_001A63A8;
    int busy = *(s32 *)(state + 0x44);
    if (*(short *)(state + 0x4E) == 9 || busy == 0 || busy == -1)
        return;
    if (D_0014B540.e[slot + 1].off == 0)
        return;
    *(s32 *)(state + 0x5C) = 48000;
    *(short *)(state + 0x48) = slot;
    *(short *)(state + 0x4A) = id;
    *(short *)(state + 0x4C) = flag;
    *(short *)(state + 0x54) = 0;
    *(short *)(state + 0x4E) = 9;
    *(s32 *)(state + 0x58) = 10;
    func_00133340((long)(int)((unsigned)D_0014B540.e[slot + 3].off + (unsigned)D_0014B540.base), (long)(int)((unsigned)D_0014B540.e[slot + 2].off + (unsigned)D_0014B540.base),
                  0, 0, id, 0, 1, busy, 0, (flag & 1) << 2, func_002B7F58, (unsigned long)(state + 0x44));
}
