/* functional: high. Table at 0x14B540 with 8-byte entries; reads the int at +0x14F4 or +0x15D4 depending on bit 8 of arg. Retail's byte layout differs only in codegen. */
extern char D_0014B540_1[];
int func_00295870(int arg) {
    int idx = arg & 0xFF;
    int off = (arg & 0x100) ? 0x14F4 : 0x15D4;
    return *(int *)(D_0014B540_1 + idx * 8 + off) > 0;
}
