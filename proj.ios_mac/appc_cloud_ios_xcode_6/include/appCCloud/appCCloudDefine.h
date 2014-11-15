//
//  appCCloudDefine.h
//

#ifndef appC_appCCloudDefine_h
#define appC_appCCloudDefine_h

// 初期化オプション
#define APPC_CLOUD_AD                   0x00000000
#define APPC_CLOUD_GAMERS               0x00000001
#define APPC_CLOUD_PUSH                 0x00000010
#define APPC_CLOUD_DATA                 0x00000100
#define APPC_CLOUD_PURCHASE             0x00001000
#define APPC_CLOUD_REWARD               0x00010000

typedef enum : NSUInteger {
	appCReleaseStatusInDevelopment = 0,
	appCReleaseStatusInReview,
	appCReleaseStatusReadyForSale,
}	appCReleaseStatus;

#endif
