/* functional: medium. Same reads, writes and calls on the same conditions as retail; the retail branch tangle (the ladder over the state's current-handler word, 0x14) is written as nested ifs. Matching was not attempted within the time box. */
extern int D_001F2840[];
extern int D_00138344;
extern int D_001AB910 __attribute__((sda));
extern int (*D_00210ACC)(void);

extern void func_0029CE38(void);
extern void func_0029C290(int);
extern int func_002D6F38(int);
extern void func_0029C300(int);

int func_002CBAE0(void)
{
    int *s = D_001F2840;
    int cur = s[5];
    int ret = 0;

    if (cur == 0x259018) {
        if (D_00138344 & 0x910) {
            ret = 1;
            s[7] = (s[2] == 4) ? 2 : 1;
        } else {
            ret = D_00210ACC() >= 0;
        }
        return ret;
    }
    if (cur == 0x25A738) {
        func_0029CE38();
        return 0;
    }
    if (cur == 0x25A498 && D_001AB910 == 0) {
        func_0029C290(0);
        return 0;
    }
    cur = s[5];
    if (cur == 0x25A190 && D_001AB910 == 0) {
        if (func_002D6F38(0) != 0)
            s[7] = (s[2] == 4) ? 2 : 1;
        func_0029C300(D_00138344);
        return s[6] != 0x25A498;
    }
    return 0;
}
