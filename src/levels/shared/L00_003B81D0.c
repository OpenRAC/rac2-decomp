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
extern char g_str_override_value_a[],g_str_override_value_b[],g_str_override_value_c[],g_str_override_value_d[];
extern char g_str_override_value_e[],g_str_override_value_f[],g_str_override_short_a[],g_str_override_short_b[];
extern char g_str_override_flag_a[],g_str_override_flag_b[],g_str_override_flag_c[],g_str_override_flag_d[];
extern char g_str_override_field_a[],g_str_override_field_b[],g_str_override_vector[];
extern void STUB_printf(const char *,...);
/* Copies every field that has been set in the settings object into the object it controls, and prints a debug message for each one. */
void field_override_apply_fields(unsigned char *object)
{
    UpdateFields *fields=*(UpdateFields **)(object+0x68);
    if(fields->field04!=-1.0f) {fields->destination->values[0]=fields->field04;STUB_printf(g_str_override_value_a);}
    if(fields->field08!=-1.0f) {fields->destination->values[1]=fields->field08;STUB_printf(g_str_override_value_b);}
    if(fields->field0C!=-1.0f) {fields->destination->values[2]=fields->field0C;STUB_printf(g_str_override_value_c);}
    if(fields->field10!=-1.0f) {fields->destination->values[3]=fields->field10;STUB_printf(g_str_override_value_d);}
    if(fields->field14!=-1.0f) {fields->destination->values[4]=fields->field14;STUB_printf(g_str_override_value_e);}
    if(fields->field18!=-1.0f) {fields->destination->values[5]=fields->field18;STUB_printf(g_str_override_value_f);}
    if(fields->field1C!=-1) {fields->destination->field18=fields->field1C;STUB_printf(g_str_override_short_a);}
    if(fields->field1E!=-1) {fields->destination->field1A=fields->field1E;STUB_printf(g_str_override_short_b);}
    if(fields->flags[0]) {fields->destination->flags[0]=fields->flags[0];STUB_printf(g_str_override_flag_a);}
    if(fields->flags[1]) {fields->destination->flags[1]=fields->flags[1];STUB_printf(g_str_override_flag_b);}
    if(fields->flags[2]) {fields->destination->flags[2]=fields->flags[2];STUB_printf(g_str_override_flag_c);}
    if(fields->flags[3]) {fields->destination->flags[3]=fields->flags[3];STUB_printf(g_str_override_flag_d);}
    if(fields->field24!=-1) {fields->destination->field30=fields->field24;STUB_printf(g_str_override_field_a);}
    if(fields->field26!=-1) {fields->destination->field32=fields->field26;STUB_printf(g_str_override_field_b);}
    if(fields->vector30.v[0]!=-1.0f) {fields->destination->vector20.q=fields->vector30.q;STUB_printf(g_str_override_vector);}
}
