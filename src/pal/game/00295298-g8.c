#include "include_asm.h"

#include "common.h"
typedef struct { int id, sector, a, b, sound; } Slot;
typedef struct { char pad[0x4b40]; Slot slots[48]; } Disc;
extern Disc g_copy_setup_data;
typedef struct { char pad[20]; short current, active; char pad24[24]; int sound; int slots[3]; } Cache;
extern Cache g_load_slots NOT_SDA;
typedef struct { char pad[0x17b0]; int sound; } SoundGlobals;
extern SoundGlobals g_sound_state NOT_SDA;
extern char g_str_load_id_message[];
extern int g_object_default_state_words[8] __attribute__((sda));
extern char *g_sound_bank_buffer[] __attribute__((sda));
extern int g_packet_buffer_table NOT_SDA;
extern int g_packet_buffer_size[] __attribute__((sda));
extern void gfx_wait_for_dma_status_bits(int), load_class_into_cache_slot_synced_pal(int,int), func_0029CFB0(void *,void *,int), snd_send_cmd6(int);
extern void snd_send_cmd8(void);
extern int snd_Pump(void),snd_BankLoadFromIOP(char *);
extern void STUB_printf(char *,int),load_cached_moby_class(int,int,void *);

/* Makes sure the disc asset with this id is in a cache slot, loading it if needed, and switches to it. */
void SwitchCachedDiscAsset_pal(int id)
{
    int index=0,slot;
    char *data;
    int i;
    if(g_copy_setup_data.slots[0].id==id) goto found;
    while(++index<48) {
        if(g_copy_setup_data.slots[index].id==id) break;
    }
found:
    if(index==48)return;
    if(index==g_load_slots.current) return;
    slot=0;
    g_load_slots.current=index;
    if(g_load_slots.slots[0]==index)goto slotfound;
    while(++slot<3) {
        if(g_load_slots.slots[slot]==index)break;
    }
slotfound:
    gfx_wait_for_dma_status_bits(1);
    if(slot==3) {
        STUB_printf(g_str_load_id_message,id);
        slot=0;
        load_class_into_cache_slot_synced_pal(id,0);
    }
    g_load_slots.active=slot;
    data=(char *)((int)&g_load_slots+slot*0xc800)+64;
    if((int)data<0x100000) {
        char *dst=(char *)(g_packet_buffer_table+g_packet_buffer_size[0]-0xc800);
        func_0029CFB0(dst,data,0xc80);
        data=dst;
    }
    for(i=0;i<52;i++) {
        char *e=(char *)&g_sound_state+i*0x70;
        int *q=*(int **)(e+0x78);
        if(q && q[7]==4) *(int **)(e+0x78)=g_object_default_state_words;
    }
    if(g_load_slots.sound) {
        snd_send_cmd6(g_load_slots.sound);
        while(snd_Pump()) {}
    }
    if(g_copy_setup_data.slots[index].sound) {
        g_load_slots.sound=snd_BankLoadFromIOP(g_sound_bank_buffer[0]+slot*0xc800);
        g_sound_state.sound=g_load_slots.sound;
    } else g_load_slots.sound=0;
    snd_send_cmd8();
    load_cached_moby_class(id,index,data);
}
