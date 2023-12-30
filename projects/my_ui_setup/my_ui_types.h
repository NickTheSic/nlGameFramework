#ifndef __NL_MY_UI_TYPES_H__
#define __NL_MY_UI_TYPES_H__

#include "nl_lib.h"

/* Assumes 0,0 ----------- 1,0
            |               |
            |               |
            |               |
           0,1 ----------- 1,1
*/

typedef struct ui_element_data ui_element_data;
struct ui_element_data
{
    v2f position;
    v2f size;
    //v2i anchor;
    //colorf colour;
};



#endif //__NL_MY_UI_TYPES_H__