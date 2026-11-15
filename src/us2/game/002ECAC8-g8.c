#include "include_asm.h"
#include "names.h"
extern int ref_L00_00365F50_00 __attribute__((sda));
extern int ref_L00_00365F50_01;
typedef struct {
    unsigned int f00;
    unsigned char pad00[0x14];
    unsigned int f18;
    unsigned int f1c;
    unsigned char pad01[0x88];
    unsigned int fa8;
    unsigned int fac;
    unsigned int fb0;
} SelectionFlags;
extern SelectionFlags D_00139768;
extern char D_001A63A8_3[];
extern int PlayBonusReelWithGameLoop(int);
extern int mpeg_play_movie_by_id(int);

/* Acts on the state the program names: raises the flag bits that belong to
   that state in the resident state block, then has the two state machines
   take it (each one stops the rest when it answers that it is busy). The
   selector's pending byte is cleared on the way in and set on the way out,
   and the program is told the selection ended in state 6. */
void func_US2_002ED018(void)
{
    int v = ref_L00_00365F50_00;

    D_001A63A8_3[7] = 0;

    if (v == 0xA9) {
        D_00139768.f00 |= 2;
        D_00139768.fa8 |= 0x600;
        if (PlayBonusReelWithGameLoop(0xA9)) goto done;
        if (mpeg_play_movie_by_id(1)) goto done;
        PlayBonusReelWithGameLoop(0xAA);
    } else if (v == 0x17) {
        mpeg_play_movie_by_id(0x17);
    } else if (v == 0xAB) {
        D_00139768.fa8 |= 0x800;
        D_00139768.f18 = (D_00139768.f18 & 0xFEFFFFFF) | 0x1000000;
        D_00139768.fac |= 0x1000;
        if (PlayBonusReelWithGameLoop(0xAB)) goto done;
        if (mpeg_play_movie_by_id(0x18)) goto done;
        PlayBonusReelWithGameLoop(0xAC);
    } else if (v == 0xAD) {
        D_00139768.f18 = (D_00139768.f18 & 0xFDFFFFFF) | 0x2000000;
        D_00139768.fac |= 0x6000;
        if (PlayBonusReelWithGameLoop(0xAD)) goto done;
        if (mpeg_play_movie_by_id(0x19)) goto done;
        PlayBonusReelWithGameLoop(0xAE);
    } else if (v == 0x1A) {
        mpeg_play_movie_by_id(0x1A);
    } else if (v == 0x1B) {
        mpeg_play_movie_by_id(0x1B);
    } else if (v == 0xAF) {
        D_00139768.fac |= 0x8000;
        D_00139768.f1c = (D_00139768.f1c & 0xEFFFFFFF) | 0x10000000;
        D_00139768.fb0 = (D_00139768.fb0 & 0xFFFEFFFF) | 0x10000;
        if (PlayBonusReelWithGameLoop(0xAF)) goto done;
        if (mpeg_play_movie_by_id(0x1C)) goto done;
        PlayBonusReelWithGameLoop(0xB0);
    }
done:
    D_001A63A8_3[7] = 1;
    { int six = 6; ref_L00_00365F50_01 = six; }
}
