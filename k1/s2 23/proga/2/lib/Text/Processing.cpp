#include "Text.h"

Text Text::Processing()
{
    Text end;

    if (haveErorrs)
    {
        end.haveErorrs = true;
        return end;
    }
    
    SetSizes(end);
    SetData(end);

    return end;
}