/* functional: high. SAME on 1 call (w18v8; mode 0, both groups ran). Unrun modes 1-4 and 5-7 read against retail: the same group body eight times with offsets 0x68; 0x6C/0x74/0x78; 0x70; 0x7C. From the near-miss draft (1596/1596 bytes, register and scheduling
   differences only), rewritten as plain loops: same reads, writes and order; the `sda` matching
   attributes are dropped. Retail's jump table (L18 0x002C0850) sends modes 0-4 to the groups
   below and 5-7 to a bare return; a null member ends that group's walk (in the last group of a
   case, it returns, which is the same). */

extern unsigned short *D_L18_001FB320[];
extern char *D_L18_001B281C;
extern int D_L18_001B2838;

/* Each group is a stream of 15-bit actor indices; a negative halfword before an entry ends it.
   Every member gets bit 0x1000 in its +0x34 flags (bits 0x43 cleared) and its +0x98 word from
   (+0x24)->+0x10; unless the owner's +0xAA id is 0xB69, its +0x31 byte is cleared and bit 0x0001
   is set as well. */
#define DISABLE_GROUP(field) do { \
    char *member; \
    unsigned short *entry; \
    unsigned short flags; \
    entry = D_L18_001FB320[*(int *)(state + (field))]; \
    while ((*(int *)(state + (field)) & 0xff) != 0xff && \
           *(int *)(state + (field)) <= D_L18_001B2838 && entry != 0 && \
           ((short)entry[-1] >= 0 || entry == D_L18_001FB320[*(int *)(state + (field))])) { \
        member = D_L18_001B281C + (*entry & 0x7fff) * 0x100; \
        if (member == 0) \
            break; \
        flags = *(unsigned short *)(member + 0x34) & 0xffbc; \
        *(unsigned short *)(member + 0x34) = flags | 0x1000; \
        *(int *)(member + 0x98) = *(int *)(*(char **)(member + 0x24) + 0x10); \
        if (*(short *)(owner + 0xaa) != 0xb69) { \
            member[0x31] = 0; \
            *(unsigned short *)(member + 0x34) = flags | 0x1001; \
        } \
        entry++; \
    } \
} while (0)

void func_L18_003FA180(char *owner, unsigned int mode)
{
    char *state = *(char **)(owner + 0x68);

    if (mode >= 8)
        return;
    switch (mode) {
    case 0:
        DISABLE_GROUP(0x60);
        DISABLE_GROUP(0x64);
        break;
    case 1:
        DISABLE_GROUP(0x68);
        break;
    case 2:
        DISABLE_GROUP(0x6c);
        DISABLE_GROUP(0x74);
        DISABLE_GROUP(0x78);
        break;
    case 3:
        DISABLE_GROUP(0x70);
        break;
    case 4:
        DISABLE_GROUP(0x7c);
        break;
    default:
        break;
    }
}
#undef DISABLE_GROUP
