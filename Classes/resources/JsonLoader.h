#ifndef __mikumo_burst__JsonLoader__
#define __mikumo_burst__JsonLoader__

#include "core/picojson.h"


class JsonLoader
{
public:
    JsonLoader();
    virtual ~JsonLoader();
    std::string getCacheFilePath(const std::string filename);
    bool parseByFile(const std::string filename);
    bool parseByJsonString();
    void downloadResponseData(const std::string url, const std::string fileName = "");
    void writeCacheData(const std::string filename);

    enum DownloadStatus
    {
        BeforeDownload = 0, // ダウンロード処理前
        SendRequest,        // リクエスト送信時
        ResponseError,      // レスポンスデータ異常時（エラー）
        ResponseFailed,     // レスポンスコード失敗（エラー）
        SaveResponseData,   // レスポンスデータ保存時
        WritingCacheData,   // キャッシュ書き込み処理中
        WritedCacheData,    // キャッシュ書き込み完了
    };
    DownloadStatus downloadStatus;
    std::string responseData;
    picojson::value jsonResult;
};
#endif /* defined(__mikumo_burst__JsonLoader__) */
