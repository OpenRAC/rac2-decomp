#include "include_asm.h"
#include "names.h"

/* Decodes the map screen occlusion data into the destination, using the compressed method when the first bit of the source is set. */
void func_00297730(char *destination, unsigned char *source, int argument)
{
    extern void func_00298170(void);
    extern void func_002977A8(char *, unsigned char *, int);
    extern void func_002979D8(char *, unsigned char *);
    extern int D_L00_001C93C8;
    EmptyMapStub();
    if (D_L00_001C93C8) {
        if (source[0] & 1)
            DecodeCompressedOcclusionMap(destination, source, argument);
        else
            ExpandMaskToPixels(destination, source);
    }
}
