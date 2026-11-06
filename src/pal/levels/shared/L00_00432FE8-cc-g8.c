/* func_PAL_L00_00432FE8, the PAL copy of func_L00_0042D9D0: the same C. */

/* Clears the pending pointer the level keeps at +0x1FC0. */
void func_PAL_L00_00432FE8(void *a0) {
    int *p = *(int **)((char *)a0 + 0x1fe0);
    *p = 0;
}
