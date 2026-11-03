/* functional: high. Plain C in place of MMI pextlb/pextlh and VU0 vitof0: the four bytes of the word c, x lowest, zero-extended and converted to floats. The one caller declares the second argument a float pointer and passes a word it read; only its value is used. */
void func_002830F0(void *dst, unsigned int c)
{
    float *d = dst;
    int i;

    for (i = 0; i < 4; i++) {
        d[i] = (float)(int)((c >> (i * 8)) & 0xFF);
    }
}
