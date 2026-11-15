#include "names.h"
typedef struct { int a, b, c, d; } Ent;
extern Ent *ref_L00_003DC2D0_00 __attribute__((sda));
extern int func_00282948(void *);
/* Clears the entry with this key from a table of ten once it has finished. */
void func_L00_003DC2D0(int key) {
    int i;
    for (i = 0; i < 10; i++) {
        if (ref_L00_003DC2D0_00[i].b == key && FastFloatHelperD(&ref_L00_003DC2D0_00[i].c)) {
            ref_L00_003DC2D0_00[i].b = 0;
            ref_L00_003DC2D0_00[i].a = 0;
        }
    }
}
