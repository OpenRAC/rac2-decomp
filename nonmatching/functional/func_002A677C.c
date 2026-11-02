/* functional: medium. Plain C in place of MMI byte code; the saturating byte adds follow the halfword products as retail's do, and the 16-bit multiplies are signed. Retail also leaves s0 changed, which no caller reads (not covered by the gate). */
extern int func_002A6640(void *position, float *blend, int *region);
extern unsigned char D_001C1740[];

static int ftoi_002A677C(float f)
{
    if (f >= 2147483648.0f) {
        return 0x7FFFFFFF;
    }
    if (f <= -2147483648.0f) {
        return (int)0x80000000;
    }
    return (int)f;
}

/* For the object at object: finds the region at its position (+0x10) with func_002A6640; when the region's record (128 bytes each at D_001C1740) has bit 0 of its word +0x50 set, writes the two region colours (words +0x40 and +0x44 as four bytes each) blended by the region's weight into +0x3C as bytes, and +0x38 gets the record's words +0x48 and +0x4C (shifted 8) with the weight in bits 16 up. */
void func_002A677C(void *object)
{
    char *o = object;
    float blend;
    int region;
    unsigned char *rec;
    int t, i;
    short wa, wb;
    unsigned int packed = 0;

    if (func_002A6640(o + 16, &blend, &region) == 0) {
        return;
    }
    rec = D_001C1740 + (region << 7);
    if ((*(unsigned int *)(rec + 80) & 1) == 0) {
        return;
    }
    t = ftoi_002A677C(255.0f * blend);
    wa = (short)(255 - t);
    wb = (short)t;
    for (i = 0; i < 4; i++) {
        unsigned int pa = (unsigned int)((int)wa * (int)rec[64 + i]);
        unsigned int pb = (unsigned int)((int)wb * (int)rec[68 + i]);
        unsigned int s = ((pa >> 8) & 0xFF) + ((pb >> 8) & 0xFF);

        if (s > 255) {
            s = 255;
        }
        packed |= s << (i * 8);
    }
    *(unsigned int *)(o + 60) = packed;
    *(unsigned int *)(o + 56) = *(unsigned int *)(rec + 72) | (*(unsigned int *)(rec + 76) << 8) | ((unsigned int)t << 16);
}
