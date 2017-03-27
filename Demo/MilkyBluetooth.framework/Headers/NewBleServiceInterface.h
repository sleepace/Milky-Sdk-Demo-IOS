//
//  NewBleServiceInterface.h
//  Profession
//
//  Created by San on 16/4/12.
//  Copyright © 2016年 com.medica. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "MilkyBleHelper.h"

@class BTHNetworkAssistHandle;
@class SLPDownloadHistoryDataAssist;
@class SLPBHTRequestHelper;
@class NewBlePackage;
@class NewBleRequest;
@class BLEHelper;

@interface NewBleServiceInterface : NSObject

/*
 *时间校准
 @timstamp 时间戳
 @timezone 时区偏移
 @specialTime 特殊时令
 @specialTimeOffSet 特殊时令偏移
 */
+(void)checkDeviceTimeWithTimestamp:(UInt32)timstamp timeZoneOffSet:(int32_t)timezone specialTime:(uint)specialTime  specialTimeOffSet:(int32_t)specialTimeOffSet;

/**
 *  枕扣时间校准快捷入口
 */
+(void)milkyTimeCalibration;

/**
 *  获取枕扣采集状态
 *
 *  @param success 成功返回  status: 1：正在采集状态,0：未处于采集状态
 *  @param failure 请求失败
 */
+ (void)queryMilkyCollectStatusWithSuccess:(void (^)(NSInteger status))success
                                   failure:(void (^)(void))failure;

/**
 *  获取枕扣ID
 *
 *  @param success 成功
 *  @param fail    失败
 */
+(void)getMilkyIdWithSuccess:(void(^)(NSString *milkyID))success fail:(void (^)())fail;

/*
 *系统版本信息
 */
+(void)newBleGetDeviceVersionWithSuccess:(void (^)(NSString *version))success
                           failure:(void (^)(void))failure;

/*
 *电池信息
 */
+(void)newBleGetDevicePowerStatusSuccess:(iBlock)success
                           failure:(void (^)(void))failure;

/*
 *睡眠监测配置
 @hour 小时
 @minutes 分
 @times 时长
 */
+(void)setMilkySleepMonitorWithHour:(uint)hour mintues:(uint)minutes duration:(uint)times WithSuccess:(void (^)(id responseObject))success fail:(void (^)())fail;

/**
 *  设置闹铃信息到枕扣
 *
 *  @param valid   闹铃是否可用
 *  @param offset  智能闹钟偏移(分钟)
 *  @param hour    时
 *  @param min     分
 *  @param weekArr 重复日
 */
+ (void)setAlarmInfoToMilkyWithValid:(int)valid andOffset:(int)offset andHour:(int)hour andMinutes:(int)min andWeekArr:(NSArray *)weekArr andSuccess:(void (^)(id responseObject))success fail:(void (^)())fail;

/**
 *  将当前用户id设置到枕扣,用于标记枕扣数据归属哪个用户
 */
+ (void)setUserIdToMilky:(int)userId WithSuccess:(void (^)(id responseObject))success fail:(void (^)())fail;

/**
 *  睡眠状态信息
 *
 *  @param success 获取成功 
 *  ^(int isAsleep, int isAwake) (isAsleep 0:未入睡 1:入睡 其他:无效) (isAwake 0:未清醒 1:清醒 其他:无效)
 *  @param fail    失败
 */
+(void)getSleepingStatusInfoWithSuccess:(milkySleepingStatusInfoBlock)success fail:(void (^)())fail;

/*
 *采集状态查询
 */
+(void)checkStateCollection;

/**
 *  更改采集状态操作
 *
 *  @param startOrStop  0x00:结束采集(已结束，则忽略该命令) 0x01:开始采集(已开始, 则忽略该命令) 其他：无效
 *  @param successBlock 成功回调
 */
+(void)changedSleepStatus:(int)startOrStop withSuccess:(changedMilkySleepStatusSuccessBlock)successBlock;

/*
 *历史数据下载
 @startTime 起始时间
 @startIndex 起始位置
 @count 下载数目
 */
+ (void)downloadHistoryDataFromTime:(UInt32)startTime
                            endTime:(UInt32)endTime
                             failed:(SLPBHTRequestFailed)failed
                       querySucceed:(SLPBHTHistoryDataQuerySucceed)querySucceed
                       dataRecieved:(SLPBHTHistoryDataRecieved)dataRecieved
                         completion:(SLPBHTRequestCompletion)completion;

#pragma mark -Private
+(void)downLoadHistoryDataStartTime:(UInt32)startTime startIndex:(ushort)startIndex count:(int)count;

+(void)queryHistoryDataStartTime:(UInt32)startTime endTime:(UInt32)endTime;

@end
