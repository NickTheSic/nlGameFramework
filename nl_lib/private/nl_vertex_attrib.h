#ifndef __NL_VERTEX_ATTRIB_H__
#define __NL_VERTEX_ATTRIB_H__

/////////////////////////////////////////////////////////////////
//                To keep Atrrib Ptr calls generic             //
/////////////////////////////////////////////////////////////////
typedef struct vertex_atrribute_info vertex_atrribute_info;
struct vertex_atrribute_info
{
    // int idx; -> assumed from the loop
    int value_count;
    int type;
    int normalized;
    // size_t size -> assumed from call to function
    size_t offset; // not sure to use size_t for offset of or const void* for actual function
};

void setup_vertex_atrributes(size_t data_size, const vertex_atrribute_info* const attrib_info, const int attrib_count);

#endif//__NL_VERTEX_ATTRIB_H__