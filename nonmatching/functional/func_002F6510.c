/* functional: high. Written from the assembly (the near miss named level 0's copies of the data): same reads, calls and result; retail's jump table (12, 14, 17, 18, 53 give mode 1, the other values 12..53 and those outside it mode 2) is a switch, and the record buffer is a plain 0xE0-byte local. */
extern char D_0021F240[];          /* +0x80: row index; rows of 0x18 with +0x140 type, +0x150, +0x154 flags */
extern unsigned char D_00139568[]; /* type -> record index */
extern char D_00239BA0[];          /* 0xE0-byte records, +0x80 the value */
extern int func_00288870(void *record, int type, int mode);

int func_002F6510(void)
{
    int record[56];                /* 0xE0 bytes; the value is at +0x80 */
    char *row = D_0021F240 + *(int *)(D_0021F240 + 128) * 24;
    int mode;
    int ok;

    if (*(int *)(row + 340) != 0) {
        switch (*(int *)(row + 320)) {
        case 12:
        case 14:
        case 17:
        case 18:
        case 53:
            mode = 1;
            break;
        default:
            mode = 2;
            break;
        }
        ok = func_00288870(record, *(int *)(D_0021F240 + *(int *)(D_0021F240 + 128) * 24 + 320), mode);
        return ok ? record[128 / 4] : 0;
    }
    if (*(int *)(row + 336) != 0)
        return 0;
    return *(int *)(D_00239BA0 + D_00139568[*(int *)(row + 320)] * 224 + 128);
}
