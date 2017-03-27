//
//  NewBleRequest.h
//  Profession
//
//  Created by San on 16/4/11.
//  Copyright © 2016年 com.medica. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SDCCP.h"

////通用回复
@interface  NewMsgGeneralResponse : NSObject

@property (nonatomic) byte retCode;

-(NewMsgGeneralResponse*)initWithMessageData:(NSData*)msgData;

@end


/*
 *时间校准
 */
@interface  NewMsgStystemTimeCheckRequest : PackageBase

@property(nonatomic)UInt32 timestamp;//时间戳

@property(nonatomic)int32_t timeZoneOffSet;//时区偏移

@property(nonatomic)uint specialTime;//特殊时令

@property(nonatomic)int32_t specialTimeOffSet;//特殊时令偏移

-(NewMsgStystemTimeCheckRequest*)initwithTimestamp:(UInt32)timstamp timeZoneOffSet:(int32_t)timezone specialTime:(uint)specialTime  specialTimeOffSet:(int32_t)specialTimeOffSet;

@end


@interface  NewMsgStystemTimeCheckResponse : NSObject

@property (nonatomic) byte retCode;

-( NewMsgStystemTimeCheckResponse*)initWithMessageData:(NSData*)msgData;

@end



/*
 *系统信息
 */
@interface  NewMsgStystemRequest : PackageBase

@end


@interface NewMsgStystemResponse : NSObject

@property (nonatomic) byte retCode;

@property(strong,nonatomic)NSString *deviceName;

@property(strong,nonatomic)NSString *deviceId;

@property(nonatomic,assign)uint deviceType;

@property(nonatomic,assign)uint currentVersion;

@property(nonatomic,assign)uint originalVersion;


-(NewMsgStystemResponse*)initWithMessageData:(NSData*)msgData;


@end


/*
 *系统版本信息
 */
@interface  NewMsgStystemVersionRequest : PackageBase

@end


@interface NewMsgStystemVersionResponse : NSObject


@property (nonatomic) byte retCode;

@property(nonatomic,assign)uint version;

-(NewMsgStystemVersionResponse*)initWithMessageData:(NSData*)msgData;

@end


/*
 *睡眠监测配置
 */
@interface NewMsgSleepMonitorSetRequest : PackageBase

@property(nonatomic)uint direction;//方向位，0表示获取，1表示设置

@property(nonatomic) uint hour;

@property(nonatomic) uint miniutes;

@property(nonatomic) ushort times;

@property(nonatomic) byte weekCycle;

-(NewMsgSleepMonitorSetRequest*)initwithHour:(uint)hour mintues:(uint)minutes times:(uint)times weekArray:(NSMutableArray *)weekArr direction:(uint)direction;

@end

/*
 设置闹铃信息
 */
@interface NewMsgSetAlarmInfoRqeuest : PackageBase

@property(nonatomic) uint direction;//方向位，0表示获取，1表示设置;

@property(nonatomic) uint valid;

@property(nonatomic) uint offset;

@property(nonatomic) uint hour;

@property(nonatomic) uint miniutes;

@property(nonatomic) byte weekCycle;

- (id)initWith:(int)valid offset:(int)offset hour:(int)hour minutes:(int)min weekArr:(NSArray *)weekArr;

@end

/*
 设置枕扣采集状态.
 */
@interface NewMsgChangedSleepStatusRequest : PackageBase

@property (nonatomic) uint statusCode;

- (id)initWith:(int)statusCode;

@end


/*
 *  设置枕扣用户信息
 */
@interface NewMsgSetUserID : PackageBase

@property (nonatomic,assign)UInt32 userId;

@property (nonatomic) uint direction;//方向位，0表示获取，1表示设置;

- (id)initWithUserId:(UInt32)userID;

@end

@interface  NewMsgSetUserIdResponse : NSObject

@property (nonatomic) byte retCode;

-( NewMsgSetUserIdResponse*)initWithMessageData:(NSData*)msgData;

@end
 


@interface NewMsgSleepMonitorsetResponse : NSObject

@property (nonatomic) byte retCode;

@property(nonatomic)uint direction;

-(NewMsgSleepMonitorsetResponse*)initWithMessageData:(NSData*)msgData;

@end


/*
 *电池信息
 */

@interface NewMsgBatteryRequest : PackageBase

@end


@interface NewMsgBatteryResponse : NSObject

@property (nonatomic) byte retCode;

@property(nonatomic)uint battery;

-(NewMsgBatteryResponse*)initWithMessageData:(NSData*)msgData;

@end


/*
 设置闹铃
 */
@interface NewMsgSetAlarmResponse : NSObject
@property (nonatomic) byte retCode;

-(NewMsgSetAlarmResponse *)initWithMessageData:(NSData*)msgData;

@end

/*
 *睡眠状态信息
 */
@interface NewMsgSleepingStatusInfoRequest : PackageBase

@end


@interface NewMsgSleepingStatusInfoResponse : NSObject

@property (nonatomic) byte retCode;

@property(nonatomic,assign)uint fallSleep;

@property(nonatomic,assign)uint wake;

-(NewMsgSleepingStatusInfoResponse*)initWithMessageData:(NSData*)msgData;

@end

/*
 *采集状态查询
 */
@interface NewMsgCheckStateCollectionRequest : PackageBase

@end


@interface NewMsgCheckStateCollectionResponse : NSObject

@property (nonatomic) byte retCode;

@property(nonatomic,assign)uint status;//采集状态

@property(nonatomic)UInt32  startTime;//起始时间

@property(nonatomic)ushort collectionTime;//采集时长

-(NewMsgCheckStateCollectionResponse*)initWithMessageData:(NSData*)msgData;

@end



/* 升级包概要结构(发送) */
@interface NewMsgUpgradeSummary: PackageBase

@property(nonatomic)ushort hVerion;//固件版本
@property(nonatomic)UInt32 length;//升级包长度
@property(nonatomic)UInt32 desCrc32;//加密校验值
@property(nonatomic)UInt32 binCrc32;//原始校验值

-(NewMsgUpgradeSummary*)initWithHVersion:(ushort)hVersion length:(UInt32)length desCrc32:(UInt32)desCrc32 binCrc32:(UInt32)binCrc32;

@end



/* 升级包内容结构(发送) */
@interface NewMsgUpgradeDetail: PackageBase

@property (nonatomic) UInt32 startIndex;
@property (nonatomic) ushort count;
@property (nonatomic) byte *content;

-(NewMsgUpgradeDetail*)initWith:(UInt32)startIndex count:(ushort)count con:(byte*)content;


@end


/* 升级包请求结构(发送) */
@interface NewMsgUpgradePackageRequest : PackageBase

@property (nonatomic, strong) PackageBase* updateData;

-(NewMsgUpgradePackageRequest*)initWithPackage:(PackageBase*)updateData;

@end


/* 升级包回复结构(接收) */
@interface NewMsgUpgradePackageResponse : NSObject

@property (nonatomic) byte retCode;

//@property (nonatomic) int count;

-(NewMsgUpgradePackageResponse*)initWithMessageData:(NSData*)msgData;


@end


/*
 *历史数据查询
 */
@interface NewMsgHistoryDataQueryRequest : PackageBase

@property(nonatomic)UInt32 startTime;///其始时间
@property(nonatomic)UInt32 endTime;//截止时间

-(NewMsgHistoryDataQueryRequest*)initWithStarttime:(UInt32)startTime endTime:(UInt32)endTime;

@end


@interface NewMsgHistoryDataQueryResponse : NSObject

@end


/*
 *历史数据下载
 */
@interface NewMsgHistoryDataDownloadRequest : PackageBase

@property(nonatomic)UInt32 startTime;///其始时间
@property(nonatomic)ushort startIndex;//起始位置
@property(nonatomic)uint downLoadCount;//下载数目

-(NewMsgHistoryDataDownloadRequest*)initWithStartTime:(UInt32)startTime startIndex:(ushort)startIndex count:(uint)count;

@end

@interface NewMsgHistoryDataDownloadResponse : NSObject

@end



