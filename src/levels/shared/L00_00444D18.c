#include "include_asm.h"
#include "names.h"

/* These four resident thunks need the -mno-split-addresses profile to come out exact:
 * without it this cc1 schedules the constant's `lui` between retail's `lui $v0,%hi` /
 * `lw $v0,%lo($v0)` pair and loads into $v1. The flag cannot cover the whole source unit
 * (func_L00_004450C0 in L00_00433560.c only matches with the default profile), so they
 * live here, in a unit of their own. */

extern char *D_L00_001B272C[];

extern int mpeg_is_audio_primed(char *);

extern void mpeg_update_audio_if_active(int *);

extern void mpeg_save_ipu_dma_state(char *);

extern void mpeg_restore_ipu_dma_state(char *);

/* Loads the resident pointer word, adds 0xD9100, and calls the update helper with it. */
int load_call_resident_update(void)
{
    return mpeg_is_audio_primed(D_L00_001B272C[0] + 0xD9100);
}

/* The release twin of func_L00_00444D18. */
void load_call_resident_release(void)
{
    mpeg_update_audio_if_active((int *)(D_L00_001B272C[0] + 0xD9100));
}

/* The same thunk with the first sub-object's lookup helper and a constant of 0xD9090. */
int load_call_first_lookup(void)
{
    mpeg_save_ipu_dma_state(D_L00_001B272C[0] + 0xD9090);
    return 1;
}

/* The twin of func_L00_00447678 with the second sub-object's lookup helper. */
int load_call_second_lookup(void)
{
    mpeg_restore_ipu_dma_state(D_L00_001B272C[0] + 0xD9090);
    return 1;
}
