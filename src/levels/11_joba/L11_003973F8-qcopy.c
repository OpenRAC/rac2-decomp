typedef int TI128 __attribute__((mode(TI)));

extern char *func_3224B0(int);
extern void func_300D78(char *);

/* Creates a linked object that follows a parent and a target. It returns 1 if the object
   was made. */
int func_L11_003973F8(char *parentArg, char *targetArg, float valueA, float valueB)
{
    char *parent = parentArg;
    char *target = targetArg;
    char *child = func_3224B0(0x12B2);
    char *childVars;

    if (child != 0) {
        *(int *)(child + 0xB8) = (int)parent;
        *(unsigned char *)(child + 0x30) = 0xFF;
        *(TI128 *)(child + 0x10) = *(TI128 *)(parent + 0x10);
        *(TI128 *)(child + 0xF0) = *(TI128 *)(parent + 0xF0);
        func_300D78(child + 0xC0);
        childVars = *(char **)(child + 0x68);
        *(int *)(childVars + 0x10) = (int)parent;
        *(int *)(childVars + 0x24) = (int)target;
        *(float *)(childVars + 0x20) = valueA;
        *(float *)(childVars + 0x28) = valueB;
        return 1;
    }
    return 0;
}
