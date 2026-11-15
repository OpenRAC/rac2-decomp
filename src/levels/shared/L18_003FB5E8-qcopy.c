typedef int TI128 __attribute__((mode(TI)));

/* Copies a saved point from the object state and moves it down by one unit. */
void func_L18_003FB5E8(char *moby, char *out) {
    char *vars = *(char **)(moby + 0x68);

    *(TI128 *)out = *(TI128 *)vars;
    *(float *)(out + 8) = *(float *)(out + 8) - 1.0f;
}
