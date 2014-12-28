#ifndef __mikumo_burst__JsonLoader__
#define __mikumo_burst__JsonLoader__

#include "core/picojson.h"


class JsonLoader
{
public:
    JsonLoader();
    virtual ~JsonLoader();
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
#endif /* defined(__mikumo_burst__JsonLoader__) */
