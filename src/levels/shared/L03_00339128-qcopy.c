#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern char *part_alloc(int);
extern int FloatToInt(float);
extern unsigned char *g_effect_type_table;

/* Creates a timed effect entry at a position and fills in its owner, color, lifetime and size. */
unsigned char *effect_create_timed(void *position, void *data, int type, int owner,
                        unsigned char flags, short timer, unsigned char marker, float scale)
{
    unsigned char *effect = (unsigned char *)part_alloc(0x29);
    unsigned char *payload;
    if (effect != 0) {
        payload = effect + 0x20;
        *(Quad *)(effect + 0x10) = *(Quad *)position;
        *(int *)(effect + 4) = owner;
        if (marker == 0xFF) {
            effect[9] = ((flags >> 5) << 4) + FloatToInt(4.0f);
            if (flags & 1)
                effect[3] = 0x48;
            else
                effect[3] = 0x44;
        } else {
            effect[9] = flags;
            effect[3] = marker;
        }
        effect[1] = 0;
        effect[2] = g_effect_type_table[type];
        *(float *)(effect + 0xC) = scale * 210000.0f;
        *(short *)(effect + 0xA) = timer;
        effect[8] = 0xA0;
        *(void **)payload = data;
    }
    return effect;
}
