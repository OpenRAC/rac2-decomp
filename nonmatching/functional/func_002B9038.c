/* functional: medium. Carried from Ratchet & Clank (func_L00_00268760, create_part2); the globals and the bitmap have rac2's addresses, and rac2 clears the whole 64-byte record (rac1's cleared 32 bytes). Slot allocator: takes slot D_001B1D94 (returns 0 when it is >= 0x800), sets its bit in the bitmap D_001F1D40, advances the hint to the next clear bit (rescanning from the start of the hint's byte unless the slot was beyond the high-water mark D_001B1D98), raises the high-water mark, counts D_001B1D9C, zeroes the 64-byte record at D_001B1D90 + slot*64, stores the argument in its first byte and returns the record. The unreachable alternate scan code after the first jump is not modelled. */
extern char *D_001B1D90 __attribute__((sda));
extern int D_001B1D94 __attribute__((sda));
extern int D_001B1D98 __attribute__((sda));
extern int D_001B1D9C __attribute__((sda));
extern unsigned char D_001F1D40[];

char *func_002B9038(int tag) {
    int cur = D_001B1D94;
    int hw = D_001B1D98;
    char *base = D_001B1D90;
    int slot = cur;
    int *rec;
    unsigned char *bm = D_001F1D40;

    if (cur - 0x800 >= 0) {
        return 0;
    }
    bm[slot >> 3] |= (unsigned char)(1 << (slot & 7));
    cur = cur + 1;
    if (!(slot - hw > 0)) {
        int idx = cur >> 3;
        cur = idx << 3;
        for (;;) {
            unsigned int b, mask;
            if (cur - 0x800 >= 0) {
                break;
            }
            b = bm[idx];
            mask = 1;
            for (;;) {
                unsigned int t = b & mask;
                unsigned int nz;
                mask <<= 1;
                if (t == 0) {
                    goto done;
                }
                nz = mask & 0xFF;
                cur++;
                if (nz == 0) {
                    break;
                }
            }
            idx++;
        }
    }
done:
    D_001B1D94 = cur;
    if (hw < slot) {
        hw = slot;
    }
    D_001B1D98 = hw;
    D_001B1D9C = D_001B1D9C + 1;
    rec = (int *)(base + slot * 64);
    rec[0] = 0;
    rec[1] = 0;
    rec[2] = 0;
    rec[3] = 0;
    rec[4] = 0;
    rec[5] = 0;
    rec[6] = 0;
    rec[7] = 0;
    rec[8] = 0;
    rec[9] = 0;
    rec[10] = 0;
    rec[11] = 0;
    rec[12] = 0;
    rec[13] = 0;
    rec[14] = 0;
    rec[15] = 0;
    *(char *)rec = (char)tag;
    return (char *)rec;
}
