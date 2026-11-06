/* func_PAL_L01_002EBFB8, the PAL copy of func_L01_002EABA8: the same C, where each read of the
   frame counter goes through the 50 Hz scale, ((s32)x * 5 + 2) / 6, 1080 becomes 900 and the
   queueing call is func_PAL_00289730. Own unit for -frac2-gcse-unsplit-edges, like the template. */
typedef struct {
    unsigned short count, pad;
    unsigned int time;
    int levels;
} SubtitleHistory;

extern SubtitleHistory D_0018C958[];
extern unsigned int D_001A7390[] __attribute__((sda));
extern int D_001A79F0[] __attribute__((sda));
extern char D_00189EA0[];
extern int func_002ACBC8(void *, int);
extern int func_PAL_00289730(int, int);

void func_PAL_L01_002EBFB8(int key, int selection, int mode, int area, int exclude)
{
    int limit = mode == 0 ? 1 : 65535;
    SubtitleHistory *entry = &D_0018C958[selection];

    if (entry->count < limit) {
        if (exclude != -1 && func_002ACBC8(D_00189EA0, exclude)) {
            entry->count = 65535;
            return;
        }
        if (func_002ACBC8(D_00189EA0, area)) {
            switch (mode) {
            case 0:
                func_PAL_00289730(key, selection);
                break;
            case 1:
                if (((int)D_001A7390[0] * 5 + 2) / 6 - D_0018C958[selection].time > 900 || D_0018C958[selection].time == 0)
                    func_PAL_00289730(key, selection);
                else if (D_0018C958[selection].time < ((int)D_001A7390[0] * 5 + 2) / 6)
                    D_0018C958[selection].time = ((int)D_001A7390[0] * 5 + 2) / 6;
                break;
            case 2:
                if (D_0018C958[selection].count != 0) {
                    if (((int)D_001A7390[0] * 5 + 2) / 6 - D_0018C958[selection].time > 900 || D_0018C958[selection].time == 0)
                        func_PAL_00289730(key, selection);
                    else if (D_0018C958[selection].time < ((int)D_001A7390[0] * 5 + 2) / 6)
                        D_0018C958[selection].time = ((int)D_001A7390[0] * 5 + 2) / 6;
                    break;
                }
                D_0018C958[selection].count++;
                if (D_0018C958[selection].time < ((int)D_001A7390[0] * 5 + 2) / 6)
                    D_0018C958[selection].time = ((int)D_001A7390[0] * 5 + 2) / 6;
                D_0018C958[selection].levels = (D_0018C958[selection].levels | (1 << D_001A79F0[0])) | 0x80000000;
                break;
            case 3:
                if (D_0018C958[selection].levels >= 0)
                    func_PAL_00289730(key, selection);
                break;
            }
        }
    }
}
