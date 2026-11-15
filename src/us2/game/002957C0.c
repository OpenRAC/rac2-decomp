#include "include_asm.h"
#include "names.h"

/* func_US2_002957C0 lives in 002957C0-map-setup-g64.c. */

/* func_US2_00295D70, the v2.00 copy of func_002954C0: the same C with one added store,
   D_001C4FA0[0x2B8 / 4] = e. */
extern unsigned char D_001A7AFD __attribute__((section(".sdata")));
extern int D_001A79F0_3 __attribute__((sda));
extern int g_map_overlay_state[];

extern void map_empty_stub(void);
extern int g_pause_menu_state[];
extern void func_0029DEA8(int, int);
extern int load_read_disc_with_pause(void *, int, int);
extern short snd_pump_music_and_disc_read(int);
extern int gfx_send_buffer_slot_records(int, int, int, int);
extern int gfx_upload_records_to_buffer_slot(int, int, int, int, int);
extern int snd_play_from_global_bank(int, unsigned int, void *);

/* resets the map's cache slots and reloads the current level's entry */
typedef struct { int sector, size; } MapFile;
typedef struct {
    char pad0[0x36C];
    int base;           /* 0x36C */
    char pad370[0x14F0 - 0x370];
    MapFile files0[28]; /* 0x14F0 */
    MapFile files1[28]; /* 0x15D0 */
} MapToc;
extern MapToc g_copy_setup_data;

void func_US2_00295D70(void)
{
    int *arena;
    int a, b, c;
    int e;
    int *map;

    map_empty_stub();
    func_0029DEA8(g_map_overlay_state[0x230 / 4], 1);
    arena = g_pause_menu_state;
    a = arena[0x10C / 4];
    b = arena[0x110 / 4];
    g_map_overlay_state[0x248 / 4] = a;
    c = a + 0x9A800;
    g_map_overlay_state[0x288 / 4] = 0;
    g_map_overlay_state[0x28C / 4] = c;
    arena[0x10C / 4] = c + 0x48000;
    g_map_overlay_state[0x290 / 4] = b;
    arena[0x110 / 4] = b + 0x48000;
    g_map_overlay_state[0x294 / 4] = 0;
    g_map_overlay_state[0x298 / 4] = 0;
    g_map_overlay_state[0x29C / 4] = -1;
    g_map_overlay_state[0x2A0 / 4] = -1;
    g_map_overlay_state[0x2A4 / 4] = -1;
    g_map_overlay_state[0x2A8 / 4] = -1;
    g_map_overlay_state[0x2AC / 4] = -1;
    g_map_overlay_state[0x2B0 / 4] = -1;
    if (g_map_overlay_state[0x238 / 4] == -1) goto empty;
    if (g_map_overlay_state[0x23C / 4] == 0 && D_001A7AFD != 0) {
        MapToc *toc = &g_copy_setup_data;
        int size = toc->files1[g_map_overlay_state[0x230 / 4]].size;
        e = size << 7;
        load_read_disc_with_pause((void *)c, toc->files1[g_map_overlay_state[0x230 / 4]].sector + toc->base, size);
        snd_pump_music_and_disc_read(1);
        g_map_overlay_state[0x23C / 4] = 1;
        g_map_overlay_state[0x240 / 4] = e;
        g_map_overlay_state[0x2B8 / 4] = e;
        gfx_send_buffer_slot_records(g_map_overlay_state[0x28C / 4], g_map_overlay_state[0x238 / 4], 0, e);
        g_map_overlay_state[0x234 / 4] = -2;
        g_map_overlay_state[0x24 / 4] = 1;
        g_map_overlay_state[0x2A0 / 4] = D_001A79F0_3 + 0x100;
    } else {
        int size;
        map = g_map_overlay_state;
        if (map[0x238 / 4] == -1) goto empty;
        size = map[0x240 / 4];
        map[0x2B8 / 4] = size;
        gfx_upload_records_to_buffer_slot(map[0x28C / 4], map[0x238 / 4], 0, size, 0);
        map[0x24 / 4] = 1;
        map[0x2A0 / 4] = D_001A79F0_3 + (D_001A7AFD ? 0x100 : 0);
        map[0x234 / 4] = -2;
    }
    goto done;
empty:
    g_map_overlay_state[0x24 / 4] = 0;
done:
    snd_play_from_global_bank(0x11, 0, 0);
}
