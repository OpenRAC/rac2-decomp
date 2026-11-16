#include "include_asm.h"
#include "names.h"

/* The -G8 body of src/levels/shared/L00_0037DD80.c belongs here: its two words are
   reached through $gp, which the unit's own -G0 file cannot produce. Both words are
   also materialised absolutely at one site each, so each address needs two names:
   the plain one with `nosda` for the absolute access, a `_1` one (small data by the
   -G8 rule) for the $gp access.
     0x1B26B4: read absolutely as the gate, written through $gp as the 15.
     0x1B26B0: the float runs through $gp, the absolute site clears it.
   A near miss of the body is in nonmatching/levels/func_L00_0037E5F0.c. */

extern unsigned int g_fade_timer __attribute__((nosda));

extern unsigned int D_L00_001B26B4_1;

extern float D_L00_001B26B0_1;

extern int g_fade_level __attribute__((nosda));
