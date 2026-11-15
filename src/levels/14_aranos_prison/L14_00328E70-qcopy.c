typedef int TI128 __attribute__((mode(TI)));

/* Copies the position and the rotation out of an object into two separate vectors. */
void func_L14_00328E70(char *object, char *outPosition, char *outRotation) {
    *(TI128 *)outPosition = *(TI128 *)(object + 0x10);
    *(TI128 *)outRotation = *(TI128 *)(object + 0xF0);
}
