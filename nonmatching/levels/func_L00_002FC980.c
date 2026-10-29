/* Bounded near miss, 2026-10-28: 600/616 bytes with the default game profile.
 * Seven forms cover natural for/while pool searches, named live context/pool
 * cursors and supported -fno-regmove/-fno-schedule-insns controls (both tie).
 * -fno-gcse worsens to548 bytes; it is not retained. The missing retail saved
 * fp and separate pool search base reflect address lifetime/coalescing.
 * Reopen with a measured genuine context/pool lifetime witness. No added
 * accesses, barriers, volatile or false callee signatures were introduced.
 */
#include "common.h"

struct AttachmentRule { short class_id, attachment; float scale; };
extern unsigned char D_001A7A40[] __attribute__((sda));
extern unsigned char D_L00_001BCAC0[];
extern unsigned char D_L00_0022F600[];
extern int D_001A79F0 __attribute__((sda));
extern float D_001A8FC8 __attribute__((sda));
extern void func_0029F978(unsigned char *, unsigned int, unsigned char *);

/* The retail literal is thirteen complete eight-byte records, including the
 * terminating zero. Each pool slot is 64 bytes, with seven usable entries. */
void func_L00_002FC980(void)
{
    if (D_001A7A40[0]) {
        struct AttachmentRule rules[13] = {
            {2714,0,2.5f},{2858,8,2.5f},{4884,0,2.5f},{3145,1,2.5f},
            {3296,1,2.5f},{3619,1,2.5f},{2485,7,2.5f},{2826,5,2.5f},
            {2506,4,2.5f},{3342,4,2.5f},{3747,1,2.5f},{3279,0,2.0f},
            {0,0,0.0f}
        };
        unsigned char *context = D_L00_001BCAC0;
        unsigned char **objects = (unsigned char **)(context + 0x18c);
        int i;
        for (i = 0; i < *(short *)(context + 0x44); ++i) {
            unsigned char *object = objects[i];
            if (*(unsigned char **)(object + 0x54) == 0) {
                unsigned char *pool = D_L00_0022F600;
                int j;
                for (j = 0; rules[j].class_id != 0; ++j) {
                    if (*(short *)(object + 0xaa) == rules[j].class_id) {
                        float scale = rules[j].scale;
                        int slot;
                        for (slot = 0; slot < 7; ++slot) {
                            if (!pool[slot*64+1]) break;
                        }
                        if (slot < 7) {
                            unsigned char *attachment = pool + slot*64;
                            func_0029F978(object, (unsigned int)rules[j].attachment, attachment);
                            *(float *)(attachment + 0x20) = scale;
                            *(float *)(attachment + 0x24) = scale;
                            *(float *)(attachment + 0x28) = scale;
                        }
                    }
                }
            }
        }
    }
    if (D_001A79F0 == 6 && *(int *)(D_L00_001BCAC0 + 0x30) == 1)
        D_001A8FC8 = -0.25f;
}
