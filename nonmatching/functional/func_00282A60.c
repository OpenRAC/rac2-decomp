/* functional: medium. Carried from Ratchet & Clank (func_001F99B0, FastMemSet); same instructions as rac1's. Word fill: stores value at dst, dst + 4, ... while n (bytes) counts down by 4, always storing at least one word (the two-way unrolled loop checks n only after each store). */
void func_00282A60(void *dst, int value, int n) {
    int *p = (int *)dst;
    do {
        *p++ = value;
        n -= 4;
    } while (n > 0);
}
