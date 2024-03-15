#include "grid.h"

int get_value_at_coords(const Grid* const grid, int x, int y)
{
    if (x < 0 || y < 0)
    {
        NL_LOG("Invalid values were passed into %s", __FUNCTION__);
        return 0;
    }

    return grid->Data[y*grid->Width+x];
}
