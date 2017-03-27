//
//  ShowFuctionViewController.m
//  Demo
//
//  Created by mac on 16/6/12.
//  Copyright © 2016年 com.medica. All rights reserved.
//

#import "ShowFuctionViewController.h"
#import <MilkyBluetooth/MilkyBleHelper.h>
#import <MilkyBluetooth/MilkyBleManager.h>
#import <MilkyBluetooth/NewBleServiceInterface.h>
#import <MilkyBluetooth/MilkyHistoryDataModel.h>

//屏幕大小
#define SCREEN_HEIGHT   [[UIScreen mainScreen] bounds].size.height
#define SCREEN_WIDTH   [[UIScreen mainScreen] bounds].size.width
@interface ShowFuctionViewController ()

@property (strong, nonatomic) IBOutlet UIButton *scanAndConnectedDevBtn;
@property (strong, nonatomic) IBOutlet UIButton *getDeviceWorkingStatusBtn;
@property (strong, nonatomic) IBOutlet UIButton *startDeviceWorkingBtn;
@property (strong, nonatomic) IBOutlet UIButton *stopDeviceWorkingBtn;
@property (strong, nonatomic) IBOutlet UIButton *getBatteryStatusBtn;
@property (strong, nonatomic) IBOutlet UIButton *getHistoryDataBtn;
@property (strong, nonatomic) IBOutlet UIButton *playRealTimeDataBtn;
@property (strong, nonatomic) IBOutlet UIButton *stopRealTimeDataBtn;
@property (strong, nonatomic) IBOutlet UIButton *disConnectedBtn;
@property (strong, nonatomic) IBOutlet UIButton *getDeviceVersionBtn;
@property (strong, nonatomic) IBOutlet UIButton *setAutoStartWorkingBtn;
@property (strong, nonatomic) IBOutlet UIButton *setAlarmInfoBtn;
@property (strong, nonatomic) IBOutlet UIButton *setUserIdBtn;
@property (strong, nonatomic) IBOutlet UIButton *getSleepStatusBtn;


@property (strong, nonatomic) IBOutlet UILabel *scanAndConnectedDevResultLaebel;
@property (strong, nonatomic) IBOutlet UILabel *loginDeviceStatusLabel;
@property (strong, nonatomic) IBOutlet UILabel *getDeviceWorkingStatusResultLabel;
@property (strong, nonatomic) IBOutlet UILabel *startDeviceWorkingResultLabel;
@property (strong, nonatomic) IBOutlet UILabel *stopDeviceWorkingResultLabel;
@property (strong, nonatomic) IBOutlet UILabel *batteryStatusResultLabel;
@property (strong, nonatomic) IBOutlet UILabel *getHistoryDataResultLabel;
@property (strong, nonatomic) IBOutlet UILabel *getDeviceVersionResultLabel;
@property (strong, nonatomic) IBOutlet UILabel *setAutoStartWorkingResultLabel;
@property (strong, nonatomic) IBOutlet UILabel *setAlarmInfoResultLabel;
@property (strong, nonatomic) IBOutlet UILabel *setUserIdResultLabel;
@property (strong, nonatomic) IBOutlet UILabel *getSleepStatusResultLabel;


@property (strong, nonatomic) IBOutlet UIView *fuctionView;
@property (strong, nonatomic) IBOutlet UIScrollView *contentScrollView;



@end

@implementation ShowFuctionViewController
{
    //设备名
    NSString *deviceName_;
    
    //设备ID
    NSString *deviceId_;
    
    // 待连接的外设
    CBPeripheral *peripheralWaitForConnect_;
}

- (id)initWithDeviceName:(NSString *)deviceName andDeviceID:(NSString *)deviceID
{
    self = [super init];
    if (self) {
        deviceName_ = deviceName;
        deviceId_ = deviceID;
    }
    return self;
}


- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [self initUI];
    
    //设备低电量通知
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(betteryLowNotify) name:BETTERYLOWNOTIFIY object:nil];
    
    //系统蓝牙开启通知
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(systemBluetoothPowerOnNotify) name:kNotifyBluetoothPoweron object:nil];
    
    //系统蓝牙关闭通知
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(systemBluetoothPowerOffNotify) name:kNotifyBluetoothPoweroff object:nil];
    
    //蓝牙连接断开通知
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(deviceDisconnectNotify) name:kNotifyBluetoothDisconnect object:nil];
    
    //蓝牙已连接上设备
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(deviceConnectedNotify) name:kNotifyBluetoothConnected object:nil];
}

- (void)initUI
{
    CGRect scrollRect = self.contentScrollView.frame;
    scrollRect.size.height = SCREEN_HEIGHT - scrollRect.origin.y;
    self.contentScrollView.frame = scrollRect;
    self.contentScrollView.contentSize = CGSizeMake(SCREEN_WIDTH, self.fuctionView.frame.size.height + 20);
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark -NSNotify

- (void)betteryLowNotify
{
    NSLog(@"您的设备电量过低,请及时充电");
}

- (void)systemBluetoothPowerOnNotify
{
    NSLog(@"系统蓝牙已开启");
}

- (void)systemBluetoothPowerOffNotify
{
    NSLog(@"系统蓝牙已关闭");
}

- (void)deviceDisconnectNotify
{
    [self refreshUIwithUnConnected];
}

- (void)deviceConnectedNotify
{
    NSLog(@"设备已连接");
}

#pragma mark -UIRefresh

- (void)refreshUIwithUnConnected
{
    self.fuctionView.alpha = 0.5;
    self.fuctionView.userInteractionEnabled = NO;
    self.scanAndConnectedDevResultLaebel.text = @"未连接";
    self.loginDeviceStatusLabel.text = @"未登录";
}


#pragma mark -ButtonAction

- (IBAction)getDeviceVersionBtnPess:(id)sender
{
    __weak typeof(self) weakSelf = self;
    
    [NewBleServiceInterface newBleGetDeviceVersionWithSuccess:^(NSString *version) {
        weakSelf.getDeviceVersionResultLabel.text = version;
    } failure:^{
        weakSelf.getDeviceVersionResultLabel.text = @"获取失败";
    }];
}


- (IBAction)scanAndConnectedDevBtnPress:(id)sender
{
    __weak typeof(self) weakSelf = self;
    [SLPMilkyBleManager scanfPeripheralWithWithSuccess:^(NSString *ID, NSString *name, CBPeripheral *peripheral) {
        
        NSMutableString *devIDstr = [NSMutableString stringWithString:[NSString stringWithFormat:@"%@",ID]];
        if (devIDstr && devIDstr.length > 3)
        {
            [devIDstr insertString:@"-" atIndex:2];
        }
        if ([devIDstr isEqualToString:deviceName_])
        {
            //找到设备
            weakSelf.scanAndConnectedDevResultLaebel.text = @"设备已找到";
            peripheralWaitForConnect_ = peripheral;
            [SLPMilkyBleManager.centerManager stopScan];
            
            if (SLPMilkyBleManager.currentPeripheral && SLPMilkyBleManager.currentPeripheral != peripheralWaitForConnect_)//断开旧蓝牙连接
            {
                [SLPMilkyBleManager.centerManager cancelPeripheralConnection:SLPMilkyBleManager.currentPeripheral];
            }
            
            //连接设备
            [SLPMilkyBleManager bleConnectWithPeripheral:peripheralWaitForConnect_ success:^{
                
                weakSelf.scanAndConnectedDevResultLaebel.text = @"设备已连接";
                weakSelf.fuctionView.alpha = 1.0;
                weakSelf.fuctionView.userInteractionEnabled = YES;
                
                
            } failure:^(NSString *error) {

                weakSelf.scanAndConnectedDevResultLaebel.text = @"连接设备失败";
            }];
        }
    }];
}

- (IBAction)setUserIdBtnPress:(id)sender
{
    __weak typeof (self) weakSelf = self;
    [NewBleServiceInterface setUserIdToMilky:0 WithSuccess:^(id responseObject) {
        weakSelf.setUserIdResultLabel.text = @"设置成功";
    } fail:^{
        weakSelf.setUserIdResultLabel.text = @"设置失败";
    }];
}

- (IBAction)getDeviceWorkingStatusBtnPress:(id)sender
{
    __weak typeof(self) weakSelf = self;
    [NewBleServiceInterface queryMilkyCollectStatusWithSuccess:^(NSInteger status) {
        if (status == 1)//1 已经处于采集状态
        {
            weakSelf.getDeviceWorkingStatusResultLabel.text = @"设备正在采集数据";
        }
        else
        {
            weakSelf.getDeviceWorkingStatusResultLabel.text = @"设备未采集";
        }
    } failure:^{
        
    }];
}

- (IBAction)stopDeviceWorkingBtnPress:(id)sender
{
    __weak typeof(self) weakSelf = self;
    
    [NewBleServiceInterface changedSleepStatus:0 withSuccess:^{
        weakSelf.stopDeviceWorkingResultLabel.text = @"停止采集成功";
    }];
}

- (IBAction)getBatteryStatusBtnPress:(id)sender
{
    __weak typeof(self) weakSelf = self;
    
    [NewBleServiceInterface newBleGetDevicePowerStatusSuccess:^(NSInteger status) {
        weakSelf.batteryStatusResultLabel.text = [NSString stringWithFormat:@"电量剩余%d%%",status];
    } failure:^{
        weakSelf.batteryStatusResultLabel.text = @"获取电量失败";
    }];
}

- (IBAction)getHistoryDataBtnPress:(id)sender
{
    __weak typeof(self) weakSelf = self;
    long startTime = 0  ;
    long endTime = [[NSDate date] timeIntervalSince1970];
    __block NSInteger historySum = 0;
    __block NSInteger downLoadedDataCount = 0;
    
    [NewBleServiceInterface downloadHistoryDataFromTime:startTime endTime:endTime failed:^(id error) {
        
    } querySucceed:^(int count) {
        //返回数据总数
        historySum = count;
        if (0 == count)
        {
            weakSelf.getHistoryDataResultLabel.text = @"暂无历史数据";
            
        }
    } dataRecieved:^(id data) {
        //在此处处理下载的数据...
        downLoadedDataCount++;
        MilkyHistoryDataModel *milkyHistoryDataModel = (MilkyHistoryDataModel *)data;
        weakSelf.getHistoryDataResultLabel.text = [NSString stringWithFormat:@"已下载%d/%d",downLoadedDataCount,historySum];

    } completion:^{
        //数据下载完毕
        weakSelf.getHistoryDataResultLabel.text = @"下载完成";
    }];
    
}

- (IBAction)setAutoStartWorkingBtnPress:(id)sender
{
    __weak typeof(self) weakSelf = self;
    //设枕扣每天23:00开始自动监测,
    [NewBleServiceInterface setMilkySleepMonitorWithHour:23 mintues:0 duration:8 WithSuccess:^(id responseObject) {
        weakSelf.setAutoStartWorkingResultLabel.text = @"设置成功";
    } fail:^{
        weakSelf.setAutoStartWorkingResultLabel.text = @"设置失败";
    }];
}

- (IBAction)setAlarmInfoBtnPress:(id)sender
{
    __weak typeof(self) weakSelf = self;
    //设置RestOn闹铃信息,闹铃时间7:20 响起时间为6:50 - 7:20,工作日生效
    NSMutableArray *repeatTimeArr = [NSMutableArray arrayWithObjects:@"0",@"0",@"1",@"1",@"1",@"1",@"1", nil];
    
    [NewBleServiceInterface setAlarmInfoToMilkyWithValid:1 andOffset:30 andHour:7 andMinutes:20 andWeekArr:repeatTimeArr andSuccess:^(id responseObject) {
        weakSelf.setAlarmInfoResultLabel.text = @"设置成功";
    } fail:^{
        weakSelf.setAlarmInfoResultLabel.text = @"设置失败";
    }];
}

- (IBAction)getSleepStatusBtnPress:(id)sender
{
    __weak typeof(self) weakSelf = self;
    [NewBleServiceInterface getSleepingStatusInfoWithSuccess:^(int isAsleep, int isAwake) {
        
        weakSelf.getSleepStatusResultLabel.text = [NSString stringWithFormat:@"入睡:%d 清醒:%d",isAsleep,isAwake];

    } fail:^{
        weakSelf.getSleepStatusResultLabel.text = @"获取失败";
    }];
}


- (IBAction)disConnectedBtnPress:(id)sender
{
    __weak typeof(self) weakSelf = self;
    [SLPMilkyBleManager bleDisconnectPeripheralWithsuccess:^{
        [weakSelf refreshUIwithUnConnected];
    }];//断开与设备连接
}

- (IBAction)backBtnPress:(id)sender
{
    [SLPMilkyBleManager bleDisconnectPeripheralWithsuccess:^{
        
    }];//断开与设备连接
    [self.navigationController popViewControllerAnimated:YES];
}

@end
