/* functional: high. Near-miss draft that differs from retail in register allocation and scheduling only; fcheck SAME on all captured calls. */
/* USA trial: 220 bytes versus 224 expected, with 0 of 28 placements matching. */
extern int func_002E5E58(int, int, void *);

int func_00347F80(char *object, int flags)
{
    int direction = 0;
    int index;
    int last;
    int original;
    void **entries;

    if (flags & 0x1000) {
        direction = -1;
    } else if (flags & 0x4000) {
        direction = 1;
    } else if (flags & 0x40) {
        if (*(void **)(object + 0x5C + *(int *)(object + 0x50) * 4) != 0)
            return 1;
    }
    if (direction != 0) {
        original = *(int *)(object + 0x50);
        func_002E5E58(3, 0, 0);
        last = *(int *)(object + 0xB0) - 1;
        entries = (void **)(object + 0x5C);
        index = *(int *)(object + 0x50);
        do {
            index += direction;
            if (last < index)
                index = 0;
            if (index < 0)
                index = last;
            *(int *)(object + 0x50) = index;
        } while (entries[index] == 0 && index != original);
    }
    return 0;
}
