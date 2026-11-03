/* functional: high. Plain C in place of the MMI plzcw: plzcw counts the leading bits that equal the sign bit, less one; the result is 30 minus that count (floor(log2(x)) for x > 0, -1 for 0 and -1). */
int func_00282A18(int x)
{
    unsigned int u = (unsigned int)x;
    int n = 0;

    if (x < 0) {
        u = ~u;
    }
    while (n < 31 && (u & (0x40000000u >> n)) == 0) {
        n++;
    }
    return 30 - n;
}
