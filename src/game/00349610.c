typedef struct { float a[3]; float b[3]; } Pair_349610;
/* Stores a start and an end value for one slot of an animation object. */
void func_00349610(char *widget, int index, float first, float second) {
    Pair_349610 *pairs = (Pair_349610 *)widget;
    pairs->a[index] = first;
    pairs->b[index] = second;
}
