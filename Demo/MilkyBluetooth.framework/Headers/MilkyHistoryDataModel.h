//
//  UserObj.h
//  MAIDIJIA
//
//  Created by Yajie Deng on 14-9-1.
//  Copyright (c) 2014年 chenchangrong. All rights reserved.
//

#import <Foundation/Foundation.h>
@interface MilkyHistoryDataModel : NSObject

//起始时间日期"yyyy-MM-dd"
@property(nonatomic,strong)NSString  *date;

//时区
@property(nonatomic,strong)NSNumber  *timezone;

//睡眠总时长,实际睡觉总时长,除掉入睡时间和清醒时间。
@property(nonatomic,strong)NSNumber  *duration;

//上床时间的Unix时间戳(timeIntervalSince1970)
@property(nonatomic,strong)NSNumber  *startTime;

//睡眠得分
@property(nonatomic,strong)NSNumber  *score;

//浅睡眠时长(分钟)
@property(nonatomic,strong)NSNumber  *light;

//中睡眠时长(分钟)
@property(nonatomic,strong)NSNumber  *rem;

//深睡眠时长(分钟)
@property(nonatomic,strong)NSNumber  *deep;

//清醒时长(分钟)
@property(nonatomic,strong)NSNumber  *wake;

//深睡眠百分比
@property(nonatomic,strong)NSNumber *MdDeepSleepPerc;

//中睡百分比
@property(nonatomic,strong)NSNumber *MdRemSleepPerc;

//浅睡百分比
@property(nonatomic,strong)NSNumber *MdLightSleepPerc;

//清醒百分比
@property(nonatomic,strong)NSNumber *MdWakeSleepPerc;

//起床前的那段清醒时间(分钟)
@property (nonatomic,strong)NSNumber *MdWakeUpTime;

//清醒次数
@property(nonatomic,strong)NSNumber  *wake_times;

//时间步(60)保留,暂无用
@property(nonatomic,strong)NSNumber  *timeStep;

//总记录数(监测了多少分钟,一分钟一个点)
@property(nonatomic,strong)NSNumber  *recordCount;

/*结束方式
 *   0: 正常结束
 *   1: 自动结束
 *   2: 强制结束(如:关机)
 *   3: 错误结束(如:供电不足、系统异常)
 */
@property(nonatomic,strong)NSNumber  *stopMode;

//各个状态持续时间,(秒)
@property(nonatomic,strong)NSArray  *statusValueArray;

/*sleepStateArray 睡眠等级数据，说明：
 0	清醒
 1	浅睡
 2	中睡
 3	深睡
 */
@property(nonatomic,strong)NSArray  *sleepStateArray;

//体动强度（float类型,归一化体动强度，输出范围:0-255）
@property(nonatomic,strong)NSArray  *motionIntensityArray;

//入睡所花时间
@property(nonatomic,strong)NSNumber  *asleepTime;

//睡眠效率（有效睡眠时长所占的百分比）
@property (nonatomic,strong)NSNumber *SleepEfficient;

//体动等级(-2:极少:监测失败；-1:过少:信息丢失；+0:正常；+1:过多:躁动不安；+2:极多:严重躁动不安)
@property (nonatomic,strong)NSNumber *bodyMoveLevel;

//算法版本号
@property(nonatomic,strong)NSString *arithmeticVer;

//睡眠状态曲线（float类型,输出范围:0.0-3.0）
@property (nonatomic,strong)NSArray *SleepCurveArray;

/*sleepCurveStatusArray 睡眠曲线中的各类状态，值说明：
 0	一切正常
 1	初始化状态
 2	呼吸暂停(枕扣无该项)
 3	心跳暂停(枕扣无该项)
 4	体动
 5	离床(枕扣无该项)
 6	翻身(枕扣无该项)
 */
@property (nonatomic,strong)NSArray *sleepCurveStatusArray;

//数据异常标记(数据有效性标识，short类型,0-有效；bit1-体动过弱；bit2-体动过少)
@property (nonatomic,strong)NSNumber *flaginvalid;

//睡眠时间过长扣分
@property (nonatomic,strong)NSString *md_sleep_time_decrease_scale_long;

//睡眠时间过短扣分
@property (nonatomic,strong)NSString *md_sleep_time_decrease_scale_short;

//清醒次数扣分
@property (nonatomic,strong)NSString *md_wake_cnt_decrease_scale;

//体动扣分,也叫躁动不安扣分
@property (nonatomic,strong)NSString *md_body_move_decrease_scale;

//深睡眠扣分
@property (nonatomic,strong)NSString *md_perc_deep_decrease_scale;

//难以入睡扣分
@property (nonatomic,strong)NSString *md_fall_asleep_time_decrease_scale;

//睡觉时间扣分(太晚睡)
@property (nonatomic,strong)NSString *md_start_time_decrease_scale;

//良性睡眠扣分,(中睡/深睡 占入睡后时间百分比)
@property (nonatomic,strong)NSString *benignSleepLow;

//睡眠效率扣分
@property (nonatomic,strong)NSString *sleepaceEfficientLow;

//体动过少扣分,与躁动不安对应
@property (nonatomic,strong)NSString *bodyMoveLow;

//原始数据,状态0;
@property(nonatomic,strong)NSArray  *originFeatureValue0Array;

//原始数据,状态1;
@property(nonatomic,strong)NSArray  *originFeatureValue1Array;

//原始数据-tag
@property(nonatomic,strong)NSArray  *originTagArray;


@end
