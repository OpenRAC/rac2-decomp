#include "include_asm.h"
#include "names.h"

/* Default -G0 profile, no cflags line. D_001A7B90 and the scalars are `sda`: cc1 emits them as
   bare symbols (one `la` for the buffer, a plain load or store for each scalar) and the
   assembler expands them in place, which is retail's shape. D_0014B540 is a struct global read
   through its members so that cc1 forms its base address in $s0 directly instead of copying it
   from a temporary. Measured: declaring func_002B7CE0 as void changes the schedule, and the
   five stores at the end are written in an order that schedules to retail's. */
typedef struct {
    char pad_00[0x32C];
    int f32C;
    char pad_330[0x10];
    int f340;
    int f344;
} Table_0014B540;
typedef struct {
    char pad_00[0x18];
    short f18;
    char pad_1A[0x162];
    int f17C;
} State_001393E0;
extern Table_0014B540 g_copy_setup_data;
extern State_001393E0 g_memcard_state;
extern char g_is_pal_video[] __attribute__((sda));
extern int g_current_map_index __attribute__((sda));
extern int D_001A7290 __attribute__((sda));
extern int D_001A72C0 __attribute__((sda));
extern int g_save_menu_flags __attribute__((sda));
extern int g_hero_moby_default[];

extern int mem_compute_sized_offset(int, void *);
extern int snd_pump_music_and_disc_read(int);
extern int load_read_disc_with_pause(int, int, int);
extern void mem_copy_aligned(void *, void *, int);
extern void save_load_packet(char *);

/* Loads the saved game data into memory, restores it, and then resets the save menu state back to its starting values. */
void save_load_game_data_reset_menu(void)
{
    char buf[40];
    char *p;
    char *data;

    mem_compute_sized_offset(g_copy_setup_data.f344 << 11, &p);
    snd_pump_music_and_disc_read(1);
    load_read_disc_with_pause((int)p, g_copy_setup_data.f340 + g_copy_setup_data.f32C, g_copy_setup_data.f344);
    data = p;
    data += *(int *)(data + 0x10);
    mem_copy_aligned(buf, g_is_pal_video, 40);
    save_load_packet(data);
    mem_copy_aligned(g_is_pal_video, buf, 40);
    g_current_map_index = 0;
    if (g_memcard_state.f17C != 0)
        g_memcard_state.f17C = 0;
    if (g_memcard_state.f18 >= 0)
        g_memcard_state.f18 = -1;
    D_001A7290 = -1;
    g_save_menu_flags &= ~0x200;
    D_001A72C0 = -1;
    g_hero_moby_default[12] = -1;
    g_hero_moby_default[6] = -1;
}
