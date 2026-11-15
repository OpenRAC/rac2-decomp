#include "names.h"
typedef unsigned int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float v[4]; } Vector;
typedef struct {
    float values[6];
    unsigned char field18, reserved19;
    unsigned short field1A;
    unsigned char flags[4];
    Vector vector20;
    unsigned short field30,field32;
} Destination;
typedef struct {
    int reserved00;
    float field04,field08,field0C,field10,field14,field18;
    short field1C,field1E;
    unsigned char flags[4];
    short field24,field26;
    int reserved28;
    Destination *destination;
    Vector vector30;
} UpdateFields;
extern char D_L00_001AFBD0[],D_L00_001AFBE0[],D_L00_001AFBF0[],D_L00_001AFC00[];
extern char D_L00_001AFC10[],D_L00_001AFC20[],D_L00_001AFC30[],D_L00_001AFC40[];
extern char D_L00_001AFC58[],D_L00_001AFC68[],D_L00_001AFC78[],D_L00_001AFC90[];
extern char D_L00_001AFCA8[],D_L00_001AFCB8[],D_L00_001AFCD0[];
extern void func_0026FEB8(const char *,...);
/* Copies every field that has been set in the settings object into the object it controls, and prints a debug message for each one. */
void func_L00_003B81D0(unsigned char *object)
{
    UpdateFields *fields=*(UpdateFields **)(object+0x68);
    if(fields->field04!=-1.0f) {fields->destination->values[0]=fields->field04;STUB_printf(D_L00_001AFBD0);}
    if(fields->field08!=-1.0f) {fields->destination->values[1]=fields->field08;STUB_printf(D_L00_001AFBE0);}
    if(fields->field0C!=-1.0f) {fields->destination->values[2]=fields->field0C;STUB_printf(D_L00_001AFBF0);}
    if(fields->field10!=-1.0f) {fields->destination->values[3]=fields->field10;STUB_printf(D_L00_001AFC00);}
    if(fields->field14!=-1.0f) {fields->destination->values[4]=fields->field14;STUB_printf(D_L00_001AFC10);}
    if(fields->field18!=-1.0f) {fields->destination->values[5]=fields->field18;STUB_printf(D_L00_001AFC20);}
    if(fields->field1C!=-1) {fields->destination->field18=fields->field1C;STUB_printf(D_L00_001AFC30);}
    if(fields->field1E!=-1) {fields->destination->field1A=fields->field1E;STUB_printf(D_L00_001AFC40);}
    if(fields->flags[0]) {fields->destination->flags[0]=fields->flags[0];STUB_printf(D_L00_001AFC58);}
    if(fields->flags[1]) {fields->destination->flags[1]=fields->flags[1];STUB_printf(D_L00_001AFC68);}
    if(fields->flags[2]) {fields->destination->flags[2]=fields->flags[2];STUB_printf(D_L00_001AFC78);}
    if(fields->flags[3]) {fields->destination->flags[3]=fields->flags[3];STUB_printf(D_L00_001AFC90);}
    if(fields->field24!=-1) {fields->destination->field30=fields->field24;STUB_printf(D_L00_001AFCA8);}
    if(fields->field26!=-1) {fields->destination->field32=fields->field26;STUB_printf(D_L00_001AFCB8);}
    if(fields->vector30.v[0]!=-1.0f) {fields->destination->vector20.q=fields->vector30.q;STUB_printf(D_L00_001AFCD0);}
}
