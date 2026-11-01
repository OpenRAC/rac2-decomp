/* functional: medium. Carried from Ratchet & Clank (func_001F9A98, FastMemCopy); same instructions as rac1's. Quadword copy: copies 16 bytes at a time from src to dst until n (bytes) runs out, always copying at least one quadword. Retail uses lq/sq, which ignore the low four address bits; callers pass 16-byte-aligned buffers. */
void func_00282B50(void *dst, void *src, int n) {
    unsigned int *d = (unsigned int *)dst;
    const unsigned int *s = (const unsigned int *)src;
    do {
        d[0] = s[0];
        d[1] = s[1];
        d[2] = s[2];
        d[3] = s[3];
        d += 4;
        s += 4;
        n -= 16;
    } while (n > 0);
}
