extern unsigned char D_001AD030[27] __attribute__((sda));
extern unsigned char D_001AD04B[] __attribute__((sda));

/* Turns a cutscene number into a compact index by skipping the unused numbers in between. Numbers outside the normal range are shifted down. */
unsigned long func_002EF010(int cutsceneId)
{
    int i;
    int firstGapEnd;
    unsigned char gapSize;
    int outOfRange = (unsigned int)(cutsceneId - 0x20) >= 0x91;

    if (!outOfRange) {
        firstGapEnd = D_001AD04B[0];
        if (cutsceneId >= firstGapEnd) {
            cutsceneId -= firstGapEnd;
        } else {
            i = 0x1B;
        next:
            i--;
            if (i >= 0) {
                gapSize = D_001AD030[i];
                if (cutsceneId < gapSize)
                    goto next;
                cutsceneId -= gapSize;
            }
        }
    } else if (cutsceneId >= 0xB1) {
        cutsceneId -= 0x91;
    }
    return cutsceneId;
}
