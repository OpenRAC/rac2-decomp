int ReadIndirect68Plus18(char *a) {
    char *b = *(char **)(a + 0x68);
    return *(int *)(b + 0x18);
}
