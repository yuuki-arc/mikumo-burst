#ifndef __mikumo_burst__JsonLoader__
#define __mikumo_burst__JsonLoader__

#include "core/picojson.h"


class JsonLoader
{
public:
    JsonLoader();
    virtual ~JsonLoader();
    bool readFile(const std::string filename);
    void downloadData(const std::string url, const std::string filename);

    enum DownloadStatus
    {
        BeforeDownload = 0,
        SendRequest,
        ResponseError,
        ResponseFailed,
        DownloadSuccess,
    };
    DownloadStatus downloadStatus;
    picojson::value jsonResult;
};
#endif /* defined(__mikumo_burst__JsonLoader__) */
