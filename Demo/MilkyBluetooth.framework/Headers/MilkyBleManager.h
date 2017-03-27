//
//  BleManager.h
//  MAIDIJIA
//
//  Created by Yajie Deng on 14-8-1.
//  Copyright (c) 2014年 chenchangrong. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>

#define SLPMilkyBleManager [MilkyBleManager sharedInstance]

//设备低电量通知(在需要提示低电量的View接收该通知)
#define BETTERYLOWNOTIFIY @"BETTERYLOWNOTIFIY"
//蓝牙类通知
#define kNotifyBluetoothPoweron @"kNotifyBluetoothPoweron" //系统蓝牙开启
#define kNotifyBluetoothPoweroff @"kNotifyBluetoothPoweroff"//系统蓝牙关闭
#define kNotifyBluetoothDisconnect @"kNotifyBluetoothDisconnect"//蓝牙连接断开
#define kNotifyBluetoothConnected @"kNotifyBluetoothConnected"//蓝牙已连接上设备

@interface MilkyBleManager : NSObject<CBCentralManagerDelegate,CBPeripheralDelegate>

@property(nonatomic,strong)CBCentralManager  *centerManager;
@property(nonatomic,strong)CBPeripheral      *currentPeripheral;
@property(nonatomic,strong)CBCharacteristic  *readCharactertic;
@property(nonatomic,strong)CBCharacteristic  *writeCharactertic;

+ (MilkyBleManager*) sharedInstance;

//销毁单例
-(void)destroy;

//是否已连接设备
- (BOOL)isConnected;

/**
 *  扫描并获取周边蓝牙设备
 *
 *  @param success 成功回调
 */
-(void)scanfPeripheralWithWithSuccess:(void(^)(NSString * ID, NSString *name, CBPeripheral *peripheral))success;

/**
 *  扫描并获取周边蓝牙设备(app进后台时调用)
 *
 *  @param success --
 */
-(void)scanfInBackgroungWithSuccess:(void(^)(NSString * ID, NSString *name, CBPeripheral *peripheral))success;

-(void)bleConnectWithPeripheral:(CBPeripheral *)peripheral
                    success:(void (^)(void))success
                    failure:(void (^)(NSString *error))failure;

//清除连接请求的block
- (void)clearConnectRequestHandle;

/**
 *  主动断开蓝牙连接,不触发重连操作
 */
-(void)bleDisconnectPeripheralWithsuccess:(void (^)(void))success;


@end
