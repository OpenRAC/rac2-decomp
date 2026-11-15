/* Draws the menu panel: header box, value line, count line and labels. */
#include "common.h"
extern void func_L11_00443940(void *,int);
extern int func_L11_00443CE0(int), func_L11_0043E108(int), func_L11_00442958(int), func_00288D58(void);
extern int func_00288FB8(int);
extern int func_001157AC(char *);
extern int func_00115DA8(char *,char *,...);
extern void func_0027F5B8(int,int,u64,char *,int), func_0027F538(int,int,u64,char *,int);
extern void func_002802E0(void *,int,int,int,int,int,int,int,int),func_00280270(void *,u64,char *,int);
extern int D_L11_001B1650 __attribute__((sda));
extern int D_L11_001B1654 __attribute__((sda));
extern int D_L11_001B1658 __attribute__((sda));
extern int D_L11_001B165C __attribute__((sda));
extern int D_L11_001B1660 __attribute__((sda));
extern int D_L11_001B1664;
extern int D_L11_001B1668;
extern int D_L11_001B166C;
extern int D_L11_001B1670 __attribute__((sda));
extern int D_L11_001B1674 __attribute__((sda));
extern int D_L11_001B1678 __attribute__((sda));
extern int D_L11_001B167C __attribute__((sda));
extern int D_L11_001B1680 __attribute__((sda));
extern int D_L11_001B1684 __attribute__((sda));
extern int D_L11_001B1688 __attribute__((sda));
extern int D_L11_001B168C __attribute__((sda));
extern int D_L11_001B1690 __attribute__((sda));
extern int D_L11_001B1694 __attribute__((sda));
extern int D_L11_001B1698 __attribute__((sda));
extern int D_L11_001B169C __attribute__((sda));
extern int D_L11_001B16A0 __attribute__((sda));
extern int D_L11_001B16A4 __attribute__((sda));
extern int D_L11_001B16A8 __attribute__((sda));
extern int D_L11_001B16AC __attribute__((sda));
extern int D_L11_001B16B0 __attribute__((sda));
extern int D_L11_001B16B4 __attribute__((sda));
extern int D_L11_001B16B8 __attribute__((sda));
extern int D_L11_001B16BC __attribute__((sda));
extern int D_L11_001B16C0 __attribute__((sda));
extern int D_L11_001B16C4 __attribute__((sda));
extern int D_L11_001B16C8 __attribute__((sda));
extern int D_L11_001B16CC __attribute__((sda));
extern int D_L11_001B16D0 __attribute__((sda));
extern int D_L11_001B16D4 __attribute__((sda));
extern int D_L11_001B16D8 __attribute__((sda));
extern int D_L11_001B16DC __attribute__((sda));
extern int D_L11_001B16E0 __attribute__((sda));

extern float D_L11_001B3E04;
extern char D_L11_001B15A0[],D_L11_001B16E8[];
extern unsigned char D_00139568[],D_001395B8[];
typedef struct { unsigned char pad[4]; unsigned char enabled; unsigned char rest[0xdb]; } MenuRecord;
extern unsigned char D_L11_00279BA0[];
extern int *D_L11_001B14F8[] SDATA(D_L11_001B14F8);
#define TABLE D_L11_001B14F8
#define SEL (*(short *)(state+0x1e8))
extern int D_L11_001B3E00;
static __inline__ int hud_coord(float value, float scale, float half)
{
    int mode = D_L11_001B3E00;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == 1)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}

void func_L11_00443D78(unsigned char *moby) {
    unsigned char box[32]; char buffer[64];
    unsigned char *state; char *text,*label,*unit,*lineText,*labelText,*nextHintText,*t3,*t4,*t5; int i,value,valueY,countY,prevHintY,nextHintY,hintY1,hintY2,hintY3,one,bx,by,bh; u64 headerColor,valueColor,countColor,prevHintColor,nextHintColor,hintColor1,hintColor2,hintColor3; float half;
    one=1;
    DrawJobaMenuHelpPrompts(moby,1);
    state=*(unsigned char **)(moby+0x68);
    text=((char *)GetLocalizedString(GetChallengeTitleTextId(SEL)));
    bx=hud_coord((float)D_L11_001B1660, D_L11_001B3E04, 0.5f);
    by=hud_coord((float)D_L11_001B1664, D_L11_001B3E04, 0.5f);
    bh=hud_coord((float)D_L11_001B1658, D_L11_001B3E04, 0.5f);
    FontSetWindow(box,bx,by,D_L11_001B1668,D_L11_001B166C,D_L11_001B1654,bh,D_L11_001B1670,3);
    headerColor=D_L11_001B1650; DrawTextWindowLargeFont(box,headerColor,text,strlen_001157AC(text));
    if(SEL==0 && !D_001395B8[GetChallengeFlagIndex(0)]) goto counts;
    if(SEL==one && !D_001395B8[GetChallengeFlagIndex(one)]) goto counts;
    {
        do {
            text=((char *)GetLocalizedString(0x2f44)); unit=((char *)GetLocalizedString(0x2f5e)); value=func_L11_00442958(SEL);
            if(value<10000) { Sprintf(buffer,D_L11_001B15A0,text,value,unit); lineText=buffer; goto draw1; }
            Sprintf(buffer,D_L11_001B16E8,text,value);
        } while(0);
        lineText=buffer;
    draw1:
        valueY=hud_coord((float)D_L11_001B167C, D_L11_001B3E04, 0.5f); valueColor=D_L11_001B1680; DrawTextMediumFont(D_L11_001B1678,valueY,valueColor,lineText,strlen_001157AC(lineText));
    }
counts:
    if(D_001395B8[GetChallengeFlagIndex(SEL)]) {
        labelText=((char *)GetLocalizedString(0x2f3e));
        Sprintf(buffer,D_L11_001B16E8,labelText,D_001395B8[GetChallengeFlagIndex(SEL)]); lineText=buffer;
        countY=(int)((float)D_L11_001B16AC * D_L11_001B3E04 + 0.5f); do { countColor=D_L11_001B16B0; } while(0); DrawTextMediumFont(D_L11_001B16A8,countY,countColor,lineText,strlen_001157AC(lineText));
    }
    if(SEL!=0) { labelText=((char *)GetLocalizedString(0x2f40)); prevHintY=hud_coord((float)D_L11_001B168C, D_L11_001B3E04, 0.5f); prevHintColor=D_L11_001B1690; DrawTextSmallFont(D_L11_001B1688,prevHintY,prevHintColor,labelText,strlen_001157AC(labelText)); }
    for(i=SEL+1;i<13;i++) {
        half=0.5f;
        if(!D_001395B8[GetChallengeFlagIndex(TABLE[i][2])]) continue;
        if(i>=11 && !IsFlagByteSet()) continue;
        if(i==8 && !((MenuRecord *)(D_L11_00279BA0 + gItemSlotToRecord[0x1e] * 0xe0))->enabled) continue;
        nextHintText=((char *)GetLocalizedString(0x2f41)); nextHintY=hud_coord((float)D_L11_001B169C, D_L11_001B3E04, half); nextHintColor=D_L11_001B16A0; DrawTextSmallFont(D_L11_001B1698,nextHintY,nextHintColor,nextHintText,strlen_001157AC(nextHintText)); break;
    }
    half=0.5f;
    text=((char *)GetLocalizedString(0x2f3f)); hintY1=hud_coord((float)D_L11_001B16BC, D_L11_001B3E04, half); hintColor1=D_L11_001B16C0; DrawTextSmallFont(D_L11_001B16B8,hintY1,hintColor1,text,strlen_001157AC(text));
    text=((char *)GetLocalizedString(0x2f42)); hintY2=hud_coord((float)D_L11_001B16DC, D_L11_001B3E04, half); hintColor2=D_L11_001B16E0; DrawTextSmallFont(D_L11_001B16D8,hintY2,hintColor2,text,strlen_001157AC(text));
    text=((char *)GetLocalizedString(0x2f43)); hintY3=hud_coord((float)D_L11_001B16CC, D_L11_001B3E04, half); hintColor3=D_L11_001B16D0; DrawTextSmallFont(D_L11_001B16C8,hintY3,hintColor3,text,strlen_001157AC(text));
}
