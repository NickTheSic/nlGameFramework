#include "../nl_vertex_attrib.h"

void setup_vertex_atrributes(size_t data_size, const vertex_atrribute_info* const attrib_info, const int attrib_count)
{
    for (int i = 0; i < attrib_count; ++i)
    {
        glVertexAttribPointer(
            i, 
            attrib_info[i].value_count, 
            attrib_info[i].type, 
            attrib_info[i].normalized, 
            data_size, 
            (const void*)attrib_info[i].offset // hate this but might be needed and hopefully doesn't cause problems
        );

        glEnableVertexAttribArray(i);  
    }
}
