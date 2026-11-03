/* functional: high. Same reads and writes in the same order; retail's `teq zero,zero` (an always-taken trap when a bit to clear is already clear) has no C spelling and is replaced by the return that follows it in retail, with no store, as retail's trap path does. */
extern unsigned char D_001EE4E0[];

/* Clear `count` bits of the D_001EE4E0 allocation bitmap, starting at bit `bit` (at least one bit, as retail's do-while). */
void func_002A0B88(int bit, int count)
{
    do {
        unsigned char *p = &D_001EE4E0[(unsigned int)bit >> 3];
        unsigned char old = *p;
        unsigned char v = old & ~(1 << (bit & 7));

        bit++;
        count--;
        if (v == old) {
            /* retail: teq zero,zero (the bit was not set) */
            return;
        }
        *p = v;
    } while (count > 0);
}
