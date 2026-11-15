#include "names.h"
/* Run the object's cache-slot list: for every record, hand the slot (offset from the cache
   pointer, read again at each site) to the engine with a random vector. The cache pointer is
   an sda word so each use is the assembler macro form (lui + lw), never hoisted. */
typedef unsigned char u8;

extern char *moby_get_motion_data(unsigned char *);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(float *, float, float, float);
extern void FastVecAdd(void *, void *, void *);
extern void follower_set_push_vector(void *, float *);

extern short *D_L05_001FB220[];
extern u8 *D_L05_001B251C __attribute__((sda));

/* Gives every piece in the object's slot list a small random push. */
void func_L05_0037D608(void *object, void *argument, float value)
{
    unsigned short *q = (unsigned short *)D_L05_001FB220[((unsigned char *)object)[0x21]];
    unsigned short *p;

    if (q != 0) {
        float vector[4];

        p = q;
        do {
            int offset = (*p & 0x7FFF) << 8;

            if (moby_get_motion_data(D_L05_001B251C + offset) != 0) {
                float a = math_random_angle();
                float b = math_random_angle();

                vec_build_spherical_offset(vector, value, a, b);
                FastVecAdd(vector, vector, argument);
                follower_set_push_vector(D_L05_001B251C + offset, vector);
            }
        } while ((short)*p++ >= 0);
    }
}
