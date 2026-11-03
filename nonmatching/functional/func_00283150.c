/* functional: high. Byte sum, two bytes per pass as retail's loop does: at least one pass, so an odd count reads one byte past it and a count of 0 or less still adds the first two bytes. */
int func_00283150(unsigned char *p, int n)
{
    int s = 0;

    do {
        int a = p[0];
        int b = p[1];
        p += 2;
        s += a;
        n -= 2;
        s += b;
    } while (n > 0);
    return s;
}
