/* functional: high. Same loads, compares, call and stores in retail's order (including the flags read at p+0x34 before the null test, as retail does); only the branch layout differs. */
/*
 * func_L00_0037E000 (192 bytes): walks the 32 links of D_L00_00231340 (16
 * bytes: moby, owner, handle at +8) and, for each link owned by `owner`,
 * drops the link (owner = 0) when its moby's flag 0x1000 at +0x34 is clear,
 * the moby is null, its state byte +0x20 is 0xFE or 0xFD, or
 * func_00282948(&link->handle) returns non-zero.
 */
typedef struct {
    unsigned char *moby;
    void *owner;
    int handle;
    int pad;
} Link_37E000;

extern Link_37E000 D_L00_00231340[];
extern int func_00282948(void *p);

void func_L00_0037E000(void *owner)
{
    Link_37E000 *e = D_L00_00231340;
    int i;

    for (i = 0; i < 32; i++, e++) {
        unsigned char *p;
        unsigned char state;

        if (e->owner != owner)
            continue;
        p = e->moby;
        if ((*(unsigned short *)(p + 0x34) & 0x1000) == 0) {
            e->owner = 0;
            continue;
        }
        if (p == 0) {
            e->owner = 0;
            continue;
        }
        state = p[0x20];
        if (state == 0xFE || state == 0xFD) {
            e->owner = 0;
            continue;
        }
        if (func_00282948(&e->handle) != 0)
            e->owner = 0;
    }
}
