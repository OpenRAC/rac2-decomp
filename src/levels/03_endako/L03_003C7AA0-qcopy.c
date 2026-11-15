typedef int TI128 __attribute__((mode(TI)));

/* Copies the moby's position and a stored height value into a 3-float output. */
void func_L03_003C7AA0(char *moby, char *out) {
    char *vars = *(char **)(moby + 0x68);

    *(TI128 *)out = *(TI128 *)(moby + 0x10);
    *(float *)(out + 8) = *(float *)(vars + 0xF8);
}
