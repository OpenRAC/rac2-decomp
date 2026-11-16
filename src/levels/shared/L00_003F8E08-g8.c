#include "include_asm.h"
#include "names.h"

/* Functions whose retail body reaches level data through $gp (small data area). */
extern void func_2EE5B0(void *, void *, void *);
extern void func_2EE108(void *, void *, void *);

extern int g_moby_offset_point_vec __attribute__((sda));

/* Turns a fixed offset by the moby's facing and moves it to the moby's position, giving a
   point in the world. */
void moby_compute_offset_point(char *source_moby, char *world_point)
{
    func_2EE5B0(world_point, &g_moby_offset_point_vec, source_moby + 0xC0);
    func_2EE108(world_point, world_point, source_moby + 0x10);
}
