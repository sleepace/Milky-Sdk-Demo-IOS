#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

#define SLPMilkyBleHelper [MilkyBleHelper share]
#define SLPMilkyBleRQHelper [MilkyBleHelper share].requestHelper

@class AllSleepData;
@class SDCCP;
@class BLEMatchHead;
@class UpdateSummary;
@class UpdateDetail;
@class SLPDownloadHistoryDataAssist;
@class SLPBHTRequestHelper;

typedef unsigned char byte;
typedef unsigned char *pbyte;

typedef void (^nothingBlock)();
typedef void (^iBlock)(NSInteger status);
typedef void (^iiBlock)(NSInteger count, NSInteger total);
typedef void (^strBlock)(NSString * str);
typedef void (^dictBlock)(NSDictionary * dict);
typedef void (^sleepdataBlock)(AllSleepData * sleepData);
typedef void (^milkySleepingStatusInfoBlock)(int isAsleep,int isAwake);
typedef void (^changedMilkySleepStatusSuccessBlock)();
typedef void (^newBleResponseSuccessBlock)(id responseObject);
typedef void (^newBleResponseFailBlock)();
typedef void (^SLPBHTRequestFailed)(id error);
typedef void (^SLPBHTRequestSucceed)(int status,id data);
typedef void (^SLPBHTRequestCompletion)(void);

#pragma mark Download History data
typedef void(^SLPBHTHistoryDataQuerySucceed)(int count);
typedef void(^SLPBHTHistoryDataRecieved)(id data);


@interface MilkyBleHelper:NSObject

#pragma mark -Private
@property(nonatomic,copy) strBlock getMilkyVersionSuccessBlock;
@property(nonatomic,copy)nothingBlock getMilkyVersionFailureBlock;
@property(nonatomic,copy) iBlock getMilkyPowerStatusSuccessBlock;
@property(nonatomic,copy)nothingBlock getMilkyPowerStatusFailureBlock;
@property(nonatomic,copy)milkySleepingStatusInfoBlock iMilkySleepStatusBlock;
@property(nonatomic,copy)nothingBlock getSleepStatusFailBlock;
@property(nonatomic,copy)changedMilkySleepStatusSuccessBlock iChangedMilkySleepStatusSuccessBlock;
@property(nonatomic,copy)newBleResponseSuccessBlock myBleResponseSuccessBlock;
@property(nonatomic,copy)newBleResponseFailBlock myBleResponseFailBlock;
@property (nonatomic,strong) SLPBHTRequestHelper *requestHelper;
@property (nonatomic,strong) SLPDownloadHistoryDataAssist *downloadHistoryDataAssist;
@property (nonatomic,copy)iBlock getSampleStatusSuccessBlock;
@property (nonatomic,copy)nothingBlock getSampleStatusFailBlock;
@property (nonatomic,copy)nothingBlock setAlarmInfoSuccessBlock;
@property (nonatomic,copy)nothingBlock setAlarmInfoFailBlock;
@property (nonatomic,copy)nothingBlock setUserInfoSuccessBlock;
@property (nonatomic,copy)nothingBlock setUserInfoFailBlock;
@property (nonatomic,copy)nothingBlock setAutoMonitorTimeSuccessBlock;
@property (nonatomic,copy)nothingBlock setAutoMonitorTimeFailBlock;


#pragma mark -Public

@property(nonatomic,readonly)CBPeripheral *peripheral;//蓝牙服务
@property(nonatomic,readonly)CBCharacteristic *readCharactertic;//特征

/*
 share： 第一次调用时务必要调initWithPeripheral:readCharactertic:接口，用以初始化蓝牙的参数
 参数：
 peripheral 蓝牙服务
 readCharactertic 蓝牙读特征
 */
+(MilkyBleHelper *)share;

//与share相对，清空成员变量
+(void)deshare;

/*
 initWithPeripheral：初始化， 第一次调用share接口时务必要调用本接口，用以初始化蓝牙的参数
 参数：
 peripheral 蓝牙服务
 readCharactertic 蓝牙读特征
 */
- (void) initWithPeripheral:(CBPeripheral *)peripheral readCharactertic:(CBCharacteristic *)readCharactertic;






#pragma mark -Private
- (void)initial;

- (void)setAllNecessaryInfoToMilky;

//蓝牙断开连接
- (void)bluetoothHasDisconnected;

/*
 *发送数据
 */
//-(void)newBleSendData:(NSData*)data;
-(void)newBleSendData:(NSData*)data success:(void (^)(id responseObject))success fail:(void (^)())fail;

/*
 *解析数据
 */
-(void)newBleParaseData:(NSData*)data;


@end
