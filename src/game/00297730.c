#include "include_asm.h"
#include "names.h"

/* Decodes the map screen occlusion data into the destination, using the compressed method when the first bit of the source is set. */
void map_decode_occlusion(char *destination, unsigned char *source, int argument)
{
    extern void map_empty_stub(void);
    extern void map_decode_compressed_occlusion(char *, unsigned char *, int);
    extern void map_expand_mask_to_pixels(char *, unsigned char *);
    extern int g_map_occlusion_flag;
    map_empty_stub();
    if (g_map_occlusion_flag) {
        if (source[0] & 1)
            map_decode_compressed_occlusion(destination, source, argument);
        else
            map_expand_mask_to_pixels(destination, source);
    }
}
