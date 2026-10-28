/* func_0029BB30 - 408 bytes.  Worker attempt, 27 October 2026 (draft below).

   func_0029BB30 400B vs 408B in the -g8 sibling. Control flow, gp/abs forms
   (two names for 0x1A8CFC), clamp, movn return all match. Left: register
   pressure: retail keeps only 0x3C950 in $s1 across the calls and rebuilds
   0x3F138 (lui/ori) at each of its three uses; mine keeps both constants
   (s1,s2) and uses s4 for the flag, so frame/saves differ (retail saves s0-s3
   only); the B==1 flag test uses the hoisted $s3=hi(D_00138180) in retail.
   Tried plain pointer +const and struct-member addressing. */

/* goes in src/game/0029AE78-g8.c (the -G8 sibling, after func_0029BA58; remove the marker in 0029AE78.c). Needs extern of func_0029B910/func_0029BA58/D_001A9A54 already there. D_001A8CFC read abs via incomplete sda array [0] and gp via the sized name D_001A8CFC_sda */
typedef struct { char pad[0x3C950]; char audio[0x3F138 - 0x3C950]; char music[1]; } Mixer29BB30;
typedef struct { char pad[0x1C0]; unsigned flags; char pad2[0x1CC - 0x1C4]; int state; } Obj29BB30;
extern Obj29BB30 D_00138180;
extern Mixer29BB30 *D_001A8CFC_sda __attribute__((sda));
extern int D_001A9A50 __attribute__((sda));
extern int D_001A9A58 __attribute__((sda));
extern int D_001A9AD8 __attribute__((sda));
extern int D_001A9AC8[] __attribute__((sda));
extern int D_001A8C64[] __attribute__((sda));
extern void func_0033A688(void *);
extern void func_0033A9F8(void *, int);
extern int func_00349190(void *, void *);
extern int func_002ED8A0(int);
extern void func_00349488(void *);

int func_0029BB30(void)
{
    int s0;
    int s2;

    if (D_001A9A50 == 0)
        return -1;
    if (D_001A8C64[0] != 0)
        return -1;
    if (D_001A8CFC_sda == 0) {
        D_001A9A50 = D_001A9A50 - 1;
        if (D_001A9A50 < 0)
            D_001A9A50 = 0;
        return 0;
    }
    func_0029BA58();
    s0 = D_001A9A54;
    if (s0 == 0)
        return -1;
    s2 = 0;
    if (s0 == 1) {
        func_0029B910();
        if (D_00138180.flags & 0x10) {
            D_001A9AD8 = s0;
            D_00138180.state = 2;
        } else if (D_001A9AD8 != 0) {
            D_001A9AD8 = 0;
            s2 = 1;
        }
        func_0033A688(((Mixer29BB30 *)D_001A8CFC[0])->music);
    }
    func_0033A9F8(((Mixer29BB30 *)D_001A8CFC[0])->music, D_001A9AD8);
    s0 = func_00349190(((Mixer29BB30 *)D_001A8CFC[0])->audio, &D_00138180);
    if (s0 >= 0) {
        if (func_002ED8A0(D_001A9AC8[s0]) < 0)
            s0 = -1;
    }
    if (s2 != 0)
        func_00349488(D_001A8CFC_sda->audio);
    if (D_001A9A58 < 0)
        D_001A9A58 = s0;
    func_0033A9E0(((Mixer29BB30 *)D_001A8CFC[0])->music, s0);
    return s2 != 0 ? s0 : -1;
}
