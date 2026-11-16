#include "include_asm.h"
#include "names.h"

typedef int s32;
typedef unsigned char u8;
typedef float f32;
extern void menu_set_entry_table(unsigned char *owner, float *records);
extern u8 g_item_owned_flags[] __attribute__((section(".sdata")));
extern u8 g_movie_seen_flags[] __attribute__((section(".sdata")));

/* func_00347F80 is built from 00345358-wrap.c. */


/* Stores the entry table and counts its entries (until a non-positive first float), wrapping the selection if it is out of range. (PAL) */
void menu_set_entry_table_pal(u8 *menu,f32 *records) {
 f32 *end;
 *(f32 **)(menu+0x68)=records;
 *(s32 *)(menu+0xC0)=0;
 end=records+0x50;
 if(records[0]>0.0f) {
  do {
   records+=5;
   (*(s32 *)(menu+0xC0))++;
  } while(*records>0.0f && (s32)records<(s32)end);
 }
 if(*(s32 *)(menu+0x60)>=*(s32 *)(menu+0xC0)) *(s32 *)(menu+0x60)=0;
}
