typedef int TI128 __attribute__((mode(TI)));

extern void func_31B920(char *moby, int vector, int a2);

/* Clears two fields of the moby's private data, stores a vector there and switches the moby to state 3. */
void func_L03_003C8660(char *moby, char *vector) {
    char *vars = *(char **)(moby + 0x68);

    *(int *)(vars + 0xAC) = 0;
    *(int *)(vars + 0xA0) = 0;
    *(TI128 *)(vars + 0x80) = *(TI128 *)vector;
    func_31B920(moby, 3, -1);
}
