#ifndef __mikumo_burst__SheetLoader__
#define __mikumo_burst__SheetLoader__

#include "core/picojson.h"


class SheetLoader
{
public:
    SheetLoader();
    virtual ~SheetLoader();
    bool readFile(const std::string filename);
    void downloadSheet(const std::string url, const std::string filename);

    enum DownloadStatus
    {
        DownloadBefore = 0,
        SendRequest,
        ResponseError,
        ResponseFailed,
        DownloadSuccess,
    };
    DownloadStatus status = DownloadStatus::DownloadBefore;
    picojson::value jsonResult;
};
#endif /* defined(__mikumo_burst__SheetLoader__) */
