/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/*
 * GPT-6.1 Sol high, v0927, 2026-10-29. Near miss.
 * Pinned game EE-GCC: -O2 -G8 -ffunction-sections.
 * check.py us: 1048/1064 bytes, 0/28 placements; no linked-build claim.
 * Block-local entry pointers recover the selection arithmetic. The back action
 * now follows retail: a missing back page while locked leaves current unchanged.
 * An explicit bit result before the page guard retains sllv/and rather than an
 * extracted bit. D_0025A620 uses the existing array declaration; the default
 * preview field has its independently measured D_0025A714 address.
 * Remaining: cyclic s0/s1/s2 allocation, search setup scheduling, row addition
 * operand order, and the final map/root pointers. The second page guard and
 * later root-base reconstruction disappear, leaving four retail instructions absent.
 * A whole-function map pointer reduced the frame to 0x40 and regressed to
 * 1012 bytes. Moving search calls outside loops regressed to 1116 bytes.
 * A volatile page field inhibits retail's speculative loads and was rejected.
 * Declarations required by this attempt are included below.
 */
#include "common.h"
typedef struct { u8 prefix[0x30]; int field30,field34,field38,field3c,field40,field44; } BarlowUtilityQueueView;
typedef struct { u8 pad[8]; int pad8; u8 padc[8]; u8 *owner; int current; u8 pad1c[0xc]; int saved; u8 pad2c[0xaf]; u8 active; u8 paddc[0x18]; int page; u8 padf8[8]; u8 *savedOwner; int savedCurrent; u8 pad108[0x2c]; int lock; u8 pad138[8]; int savedMode; } PageRoot;
typedef struct { u8 pad[0x230]; int page; } PageMap;
typedef struct { u8 pad[0x1c4]; u32 buttons; } PagePad;
typedef struct { u8 pad[0x30]; int selection[28]; int count; } PageMenu;
extern PageRoot D_001F2840;
extern PageMap D_001C4FA0;
typedef struct { char pad[0x34]; int item, pad38, timer; } PagePreview;
extern PagePreview D_0025A6E0;
extern u8 D_0025E680[],D_001A7BC8[];
extern int D_00139768[];
extern int D_0025A620[];
extern int D_001A7478;
extern int D_0025A714 NOT_SDA;
extern int D_001A79F0 __attribute__((sda));
extern int D_001A72D4 __attribute__((sda));
extern BarlowUtilityQueueView D_001BAD40;
extern int func_00295A10(int),func_002E5E58(int,int,void *),func_0029DB28(int *,int *,int *,int);
extern void func_00295C50(int),func_0029D830(void),func_002C9E60(int);
extern int func_00288AA0(u8 *,int),func_00288BE8(BarlowUtilityQueueView *);
extern PagePad D_00138180;
static inline int previewPageIndex(int page)
{
    if (page == 0) return 21;
    if (page == 24) return 0;
    return page;
}

int func_002D7698(PageMenu *menu)
{
    int previous,count,old,next;
    u8 *owner=D_001F2840.owner;
    previous=D_001C4FA0.page;
    if (*(PageMenu **)(owner+0xe8)!=menu) {
        if (D_001C4FA0.page<28) menu->selection[D_001C4FA0.page]=-1;
        return 0;
    }
    if ((D_00138180.buttons&0xd00) && !D_001F2840.lock && owner!=D_0025E680) return 1;
    if (D_00138180.buttons&8) {
        next=D_001C4FA0.page+1;
        while (next<28) {
            if (*(u8 *)(next+(int)D_001A7BC8) || D_001A79F0==next) {
                if (func_00295A10(next)<0) return 0;
                func_00295C50(next);
                break;
            }
            next++;
        }

    }
previous_page:
    if (D_00138180.buttons&4) {
        next=D_001C4FA0.page-1;
        while (next>=0) {
            if (*(u8 *)(next+(int)D_001A7BC8) || D_001A79F0==next) {
                if (func_00295A10(next)<0) return 0;
                func_00295C50(next);
                break;
            }
            next--;
        }

    }
page_ready:
    {
    PageMap *map=&D_001C4FA0;
    if (map->page!=previous) {func_002E5E58(3,0,0);func_0029D830();}
    count=func_0029DB28((int *)0x70000000,0,(int *)0x70000100,1);menu->count=count;
    if (count) {
        u32 buttons=D_00138180.buttons;
        int *selections=menu->selection;
        {
            int *entry=&selections[map->page];
            old=*entry;
            if (buttons&0x1000) *entry=(old+count-1)%count;
        }
        if (buttons&0x4000) {int *entry=&selections[map->page];*entry=(*entry+1)%menu->count;}
        if (selections[map->page]!=old) func_002E5E58(3,0,0);
        if ((buttons&0x5000) || map->page!=previous) {
            int *entry;
            D_0025A6E0.timer=-576;entry=&selections[map->page];
            D_0025A6E0.item=((int *)0x70000000)[*entry];*D_0025A620=((int *)0x70000100)[*entry];
        }
    }
    else {D_0025A714=0;*D_0025A620=-1;}
    }
    if (D_00138180.buttons&16) {
        u8 *owner=D_001F2840.owner;
        if (owner!=D_0025E680) {
            int status, next;
            next=*(int *)(owner+0xe0);
            if (next) D_001F2840.current=next;
            else if (!D_001F2840.lock) {status=-1;goto back_done;}
            status=0;
back_done:
            return status;
        }
    }
    if ((D_00138180.buttons&32) && D_001C4FA0.page>=0) {
        int mapped;
        if (D_001F2840.active) return 0;
        mapped=previewPageIndex(D_001C4FA0.page);
        {
        PageMap *map=&D_001C4FA0;
        int bit=D_00139768[(unsigned)mapped>>2] & (1 << (mapped&31));
        if (map->page>=0 && bit) {
            PageRoot *root=&D_001F2840;
            D_001A72D4=root->saved;func_002C9E60(0);
            root->savedMode=D_001A7478;root->savedOwner=root->owner;
            root->page=map->page;root->savedCurrent=root->pad8;D_001A7478=2;
            func_00288AA0((u8 *)&D_001BAD40,mapped);func_00288BE8(&D_001BAD40);return 1;
        }
    }
    }
    return 0;
}
