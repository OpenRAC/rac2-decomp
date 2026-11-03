/* functional: high. Plain C in place of MMI pextlh/psraw and VU0 vitof0: the four halfwords of the 64-bit value v, x lowest, sign-extended and converted to floats. */
void func_00283130(void *dst, unsigned long v)
{
    float *d = dst;
    unsigned int lo = (unsigned int)v;
    unsigned int hi = (unsigned int)(v >> 32);

    d[0] = (float)(short)(lo & 0xFFFF);
    d[1] = (float)(short)(lo >> 16);
    d[2] = (float)(short)(hi & 0xFFFF);
    d[3] = (float)(short)(hi >> 16);
}
