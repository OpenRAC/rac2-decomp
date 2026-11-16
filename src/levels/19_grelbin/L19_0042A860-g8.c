#include "include_asm.h"
#include "names.h"

extern int moby_count_of_class(int);

extern int g_subtitle_total_length __attribute__((sda));

/* Sum of the three subtitles' lengths, kept for the next frame. */
int text_sum_subtitle_lengths(void) {
    int firstLength = moby_count_of_class(0x11C7);
    int secondLength = moby_count_of_class(0x1266);
    int thirdLength = moby_count_of_class(0xF57);
    int total = firstLength + secondLength + thirdLength;

    g_subtitle_total_length = total;
    return total;
}
