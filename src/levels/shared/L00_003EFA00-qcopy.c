#include "include_asm.h"
#include "names.h"

/* func_L00_003EFA00 is a unit of its own: it needs the opt-in quadword-copy profile
   (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which gives retail's grouped
   `lq`/`sq` with register addresses for the 16-byte block copied out of the object. */

typedef int TI128 __attribute__((mode(TI)));

extern int save_is_record_value(int, int);

extern void effect_clear_records_and_flag(void);

extern void moby_mark_spawned(char *);

extern int math_fast_helper_a(char *, float);

extern void gfx_draw_quad_sphere_large(char *);

extern void gfx_draw_quad_sphere_small(char *);

extern void effect_draw_owner_records(char *);

/* Queries the object; on a null answer it resets it and returns, otherwise it works on a
   local copy of its 16-byte block and runs the three update steps. */
/* Runs one frame of the blast effect while the moby is near the camera, and removes the moby
   when its owner is gone. */
void blast_run_effect_frame(char *obj)
{
    char local[16];
    int r;

    r = save_is_record_value(*(short *)(obj + 0xAA), *(int *)(*(int *)(obj + 0x68) + 0x28));
    if (r == 0) {
        effect_clear_records_and_flag();
        moby_mark_spawned(obj);
        return;
    }
    *(TI128 *)local = *(TI128 *)(obj + 0x10);
    *(float *)(local + 0xC) = 2.0f;
    r = math_fast_helper_a(local, 100.0f);
    if (r == -1)
        return;
    gfx_draw_quad_sphere_large(obj);
    gfx_draw_quad_sphere_small(obj);
    effect_draw_owner_records(obj);
}
