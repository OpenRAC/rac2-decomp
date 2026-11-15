#include "names.h"
/* Constructs a menu grid: initializes its sprites, text, anchor and four-by-six selection. */
extern void func_003361E0(void *, void *, void *);
extern unsigned int *func_00335E20(void *);
extern void func_00336390(void *, void *, int);
extern int func_00336E40(void *);
extern int *func_00336DA8(int, int);
extern void func_003369A8(void *, void *, void *);
extern void func_00335E68(void *, int);
extern void func_00336710(void *, void *, void *);
extern void func_00335F88(void *, float, float, float, float);
extern void func_00336A38(void *, void *);
extern void func_00336408(void *, int, int, void *, void *);
extern void func_00336CC8(void *, int);
extern void func_00336B90(void *, int);
extern void func_00336B98(void *, int);
extern void func_00336498(void *, unsigned int, unsigned int);
extern void func_003364B0(void *, unsigned int, unsigned int);
extern void func_00336CE0(void *, unsigned int);
extern void func_00336CC0(void *, int);
extern char D_001ADFA0[], D_001ADFC0[], D_001ADFC8[], D_001AE030[], D_001ADFD8[], D_001AE040[];
extern char *D_001A8CFC[] __attribute__((sda));
int func_00341030(char *, unsigned int, void *);
void func_00340D68(char *self, void *parent)
{
    char *widgetE0=self+0xE0, *widget4C, *widget98, *iconWidget, *barWidget;
    int *allocation;
    InitDerivedArrays(widgetE0,D_001ADFA0,parent);
    *GetFieldC(widgetE0)=0x60241700;
    SetFieldAt40(widgetE0,D_001A8CFC[0]+0x8710,0x29);
    *(void **)(self+0x1B4)=parent;
    if(parent) {
    allocation=ReturnSecondArgument(16,AllocPoolCell(parent));
    *(int **)(self+0x1B0)=allocation;
    allocation[1]=0; allocation[2]=0; allocation[3]=0; allocation[0]=0;
    }
    *(int *)(self+0x200)=1;
    **(float **)(self+0x1B0)=0.0f;
    (*(float **)(self+0x1B0))[1]=0.0f;
    widget4C=self+0x4C; widget98=self+0x98; iconWidget=self+0x174; barWidget=self+0x12C;
    InitDerivedArrays(self,D_001ADFC0,parent);
    InitDerivedArrays(widget4C,D_001ADFC8,parent);
    InitWidgetDefaults(widget98,D_001AE030,parent);
    *GetFieldC(self)=0x55F0C070;
    *GetFieldC(widget4C)=0x70FFFEED;
    SetFieldAt40(self,D_001A8CFC[0]+0x8710,0x5D);
    SetFieldAt40(widget4C,D_001A8CFC[0]+0x8710,0x5E);
    SetFlagValue(widget4C,0);
    *(int *)(self+0x204)=0;
    *(int *)(self+0x208)=0;
    InitDerivedObjectC(iconWidget,D_001ADFD8,parent);
    *GetFieldC(iconWidget)=0x60F0F0B0;
    SetSecondFloat4(iconWidget,32.0f,32.0f,0.0f,0.0f);
    *GetFieldC(widget98)=0x80F0F0F0;
    self[0x1C0]=0;
    SetWidgetField40(widget98,self+0x1C0);
    *(float *)(self+0x1B8)=0.0f;
    *(float *)(self+0x1BC)=0.0f;
    *(int *)(self+0x214)=0;
    InitDerivedObjectB(barWidget,32,0,D_001AE040,parent);
    SetWidgetPositionY(barWidget,5);
    SetMeterMaximum(barWidget,100);
    SetMeterValue(barWidget,0);
    SetFirstPair(barWidget,0x6049C1FF,0x60001EFF);
    SetSecondPair(barWidget,0x50F0C070,0x50F0C070);
    SetTextAlignment(barWidget,0x80000000);
    SetWidgetField38(barWidget,0);
    *(int *)(self+0x20C)=4;
    *(int *)(self+0x210)=6;
    UpdateMenuGridSelection(self,0,0);
}
