//
//  SLPDownloadHistoryDataAssist.h
//  Profession
//
//  Created by Martin on 4/16/16.
//  Copyright © 2016 com.medica. All rights reserved.
//

#import <Foundation/Foundation.h>
//#import "BTHNetworkAssistHandle.h"
#import "SLPBHTHistoryQueryPlus.h"
#import "MilkyBleHelper.h"

@class SLPHistroryDataItem;
static const UInt32 kBHTHistoryDataDownloadMaxPacketCount = 30;
@interface SLPDownloadHistoryDataAssist : NSObject
@property (nonatomic,copy)SLPBHTRequestFailed failed;
@property (nonatomic,copy)SLPBHTHistoryDataQuerySucceed querySucceed;
@property (nonatomic,copy)SLPBHTHistoryDataRecieved dataRecieved;
@property (nonatomic,copy)SLPBHTRequestCompletion completion;


@property (nonatomic,assign) BOOL isDownload;
@property (nonatomic,assign) NSInteger itemIndex;
@property (nonatomic,readonly) NSMutableArray<SLPHistroryDataItem*> *dataDownloadList;//同一个Item里面的所有下载数据
@property (nonatomic,assign) NSInteger downloadIndex;
@property (nonatomic,strong) SLPBHTHistoryQueryPlus *queryPlusData;

- (void)clear;

//上一个item的开始时间
- (UInt32)lastItemStartTime;
//上一条数据是否已经下载完毕
- (BOOL)isLastItemDownloadFinished;
//当前是否已经下载完毕
- (BOOL)isDownloadFinished;
@end
