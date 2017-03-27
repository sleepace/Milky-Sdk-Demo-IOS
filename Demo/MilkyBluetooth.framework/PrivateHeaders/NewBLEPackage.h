//
//  NewBLEPackage.h
//  Profession
//
//  Created by San on 16/4/7.
//  Copyright © 2016年 com.medica. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SDCCP.h"
#import "CRC.h"


//新ble协议帧序号
typedef enum
{
    SEQ_NEW_TIME_CHECK,
    SEQ_NEW_DEVICE_INFO,///
    SEQ_NEW_SYSTEM_VERSION,
    
    SEQ_NEW_USER_INFO_SET,
    SEQ_NEW_SLEEP_MONITOR_SET,
    
    SEQ_NEW_ALARM_INFO_SET,
    
    SEQ_NEW_BATTERY_INFO,
    SEQ_NEW_SLEEP_STATUS_INFO,
    
    SEQ_NEW_HISTORY_QUERY,
    SEQ_NEW_HISTORY_DOWNLOAD,
    
    SEQ_NEW_UPGRADE_INFO,
    SEQ_NEW_UPGRADE_CONENT,
    
    SEQ_NEW_SLEEP_STATUS_SET,
    
    SEQ_NEW_STATUS_COLLECTION_CHECK,//采集状态查询
    
}
NEWBLE_SENQUENCE;

//新ble协议消息类型
typedef enum
{
    NEW_TIME_CHECK=0x10,//时间校准
    NEW_DEVICE_INFO=0x11,///系统信息
    NEW_SYSTEM_VERSION=0x12,//系统版本信息
    
    NEW_USER_INFO_SET=0x20,//用户信息配置
    NEW_SLEEP_MONITOR_SET=0x21,//睡眠监测配置
    
    NEW_ALARM_INFO_SET=0x22,//闹铃设置
    
    NEW_BATTERY_INFO=0x40,//电池信息
    NEW_SLEEP_STATUS_INFO=0x41,//睡眠状态信息
    
    NEW_STATUS_COLLECTION_CHECK=0x42,//采集状态查询
    
    NEW_HISTORY_QUERY=0x50,//历史数据查询
    NEW_HISTORY_DOWNLOAD=0x51,//历史数据下载
    
    NEW_UPGRADE_INFO=0x52,//升级包信息
    NEW_UPGRADE_COUNT=0x53,//升级包内容
    
    NEW_SLEEP_STATUS_SET=0x30,//更改采集状态操作
    
}


NEWBLE_MSG_TYPE_T;




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 *消息头
 */
@interface NewBleHead : NSObject

@property (nonatomic) char version;//版本 1B
@property (nonatomic) char frameType;//帧类型 1B
@property (nonatomic) UInt8 frameCount;//帧数目 1B
@property (nonatomic) UInt8 frameNumber;//帧编号 1B
@property (nonatomic) UInt8 frameSenquence;//帧序号 1B
@property (nonatomic) unsigned short deviceType;//设备类型 2B

-(NewBleHead*)initWithFrameType:(char)frameType
                     devcieType:(unsigned short)devType
                 frameSenquence:(UInt8)frameSenquence;

- (ByteBuffer *)fillBuffer:(ByteBuffer *)buffer;

@end

/*
 *消息负载
 */
@interface NewBleMsg : NSObject
@property (nonatomic) UInt8 type;  //消息类型
@property (nonatomic, strong) PackageBase *content; //消息正文

-(NewBleMsg*)initWithMsgType:(UInt8)type
                         meg:(PackageBase*)content;

- (ByteBuffer *)fillBuffer:(NewBleHead *)head :(ByteBuffer *)buffer;

@end

/*
 *数据包
 */
@interface NewBlePackage : NSObject

@property (nonatomic, strong) ByteBuffer *buffer;
//@property (nonatomic) char *buffer;

@property(nonatomic,strong)NewBleHead *head;//头7个B

@property(nonatomic,strong)NewBleMsg *msg;//消息负载

@property(nonatomic) uint crc32;///校验4B

@property(nonatomic) UInt32 separate;//分隔符4B

-(void)fillWithFrameType:(char)frameType
              deviceType:(unsigned short)devType
          frameSenquence:(UInt8)senquence
                 msgType:(UInt8)mType
                     meg:(PackageBase*)content;


//判断是否有分隔符
+(NSArray *)separateData:(NSData *)orgData;

//解析数据包
+(void)bleParseData:(NSData *)orgData Head:(NSData **)head Msg:(NSData **)msg Crc:(NSData **)crcData;

///校验
+(BOOL)bleCheckCRC32WithData:(Byte *)byte length:(int)length crc:(Byte *)crc;//CRC32 校验

///获得帧类型
+(int)getType:(NSData *)data;

//获得消息类型
+(int)getMsgType:(NSData *)data;

//返回senquence
+(int)getSenquence:(NSData *)data;

///转换为大端数据
+(void)shortToBytes:(short) value byte:(Byte *)byte;

@end



