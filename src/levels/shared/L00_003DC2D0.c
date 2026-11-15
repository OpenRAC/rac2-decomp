#include "names.h"
typedef struct { int a, b, c, d; } Ent;
extern Ent *ref_L00_003DC2D0_00 __attribute__((sda));
extern int math_fast_float_d(void *);
/* Clears the entry with this key from a table of ten once it has finished. */
void effect_clear_finished_entry(int key) {
    int i;
    for (i = 0; i < 10; i++) {
        if (ref_L00_003DC2D0_00[i].b == key && math_fast_float_d(&ref_L00_003DC2D0_00[i].c)) {
            ref_L00_003DC2D0_00[i].b = 0;
            ref_L00_003DC2D0_00[i].a = 0;
        }
    }
}
