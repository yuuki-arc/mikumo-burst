#ifndef __mikumo_burst__SheetLoader__
#define __mikumo_burst__SheetLoader__

#include "core/picojson.h"

class SheetLoader
{
public:
    SheetLoader();
    virtual ~SheetLoader();
    static picojson::value getSheet(const std::string filename);
    static bool downloadSheet(const std::string url, const std::string filename);
};
#endif /* defined(__mikumo_burst__SheetLoader__) */
