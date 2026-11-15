#include "common.h"

extern u8 *D_L16_001B2B1C[] __attribute__((sda));

extern u8 *D_L16_001B2B20[] __attribute__((sda));

extern u8 *moby_get_private_value_0(u8 *);

extern void moby_mark_spawned(void *);

/* Walks the level's entity list and reports the classes that need a second pass. */
void snivelak_clean_up_arena_mobys(u8 *moby)
{
    u8 *entity;
    u8 *record;
    u32 classId;
    s16 classShort;

    entity = D_L16_001B2B1C[0];
    if (D_L16_001B2B20[0] < entity)
        return;
    do {
        classId = *(u16 *)(entity + 0xAA);
        if (classId - 0xE71 < 3 || (s16)classId == 0xC87 || (s16)classId == 0xC86
            || (s16)classId == 0x113A || (s16)classId == 0x1162 || (s16)classId == 0x7FB) {
            moby_mark_spawned(entity);
        }
        classShort = *(s16 *)(entity + 0xAA);
        if (classShort == 0xF35 || classShort == 0xEA3 || classShort == 0xEA4 || classShort == 0xEBB) {
            record = moby_get_private_value_0(entity);
            if (record != 0) {
                if (*(u8 *)(record + 0xE) == 1) {
                    *(u16 *)(entity + 0xB6) = 0;
                    *(u16 *)(entity + 0xB4) = 0;
                    *(u8 *)(record + 0xE) = 2;
                } else {
                    moby_mark_spawned(entity);
                }
            }
        }
        entity += 0x100;
    } while (D_L16_001B2B20[0] >= entity);
}
