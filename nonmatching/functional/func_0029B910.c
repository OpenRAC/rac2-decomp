/* functional: high. Same calls, arguments, reads and writes as retail; the near miss's C was already behaviourally retail's (byte differences are induction pointers and scheduling only). */

/* Fills the four rows of the mission list menu (D_00256418, 24-byte rows) when the HUD block D_001A8CFC is
 * loaded: for each of the four mission ids in D_001A9AC8, finds its record (func_002ED8A0) in D_00262940
 * (40-byte records); a found one sets the row's count (+0x1C, sign-extended), colour (0x6029A1FF when the
 * record's +0x24 flag is at least 1, else 0x60F0F0B0) and planet id (+0x20) and shows the row
 * (func_0033A9D0(D_001A8CFC + 0x3F138, i, 0)); a missing one hides it (mode 2). */

extern char *D_001A8CFC[] __attribute__((sda));
extern int D_001A9AC8[4] __attribute__((sda));
extern int func_002ED8A0(int);
extern void func_0033A9D0(char *, int, int);

typedef struct {
    unsigned short id;           /* +0x00 */
    short pad02;
    int next;                    /* +0x04 */
    int pad08[4];
    int state;                   /* +0x18 */
    short count;                 /* +0x1C */
    short pad1E;
    unsigned short level;        /* +0x20 */
    short pad22;
    int flag;                    /* +0x24 */
} MissionListRecord;

typedef struct {
    int first;                   /* +0x00 */
    int second;                  /* +0x04 */
    int color;                   /* +0x08 */
    float angle;                 /* +0x0C */
    short id;                    /* +0x10 */
    short pad12;
    int text;                    /* +0x14 */
} MissionListRow;

extern MissionListRecord D_00262940[];
extern MissionListRow D_00256418[];

void func_0029B910(void)
{
    int i;

    if (D_001A8CFC[0] == 0)
        return;
    for (i = 0; i < 4; i++) {
        int idx = func_002ED8A0(D_001A9AC8[i]);
        if (idx >= 0) {
            MissionListRecord *rec = &D_00262940[idx];
            D_00256418[i].color = rec->flag >= 1 ? 0x6029A1FF : 0x60F0F0B0;
            D_00256418[i].second = rec->count;
            D_00256418[i].id = rec->level;
            func_0033A9D0(D_001A8CFC[0] + 0x3F138, i, 0);
        } else {
            func_0033A9D0(D_001A8CFC[0] + 0x3F138, i, 2);
        }
    }
}
