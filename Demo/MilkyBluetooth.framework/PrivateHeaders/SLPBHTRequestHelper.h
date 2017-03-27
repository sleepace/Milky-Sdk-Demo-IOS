//
//  SLPBHTRequestHelper.h
//  Profession
//
//  Created by Martin on 5/13/16.
//  Copyright © 2016 com.medica. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "SLPRqMilkySetSleepTime.h"
#import "SLPRqQuryMilkyCollectStatus.h"

@interface SLPBHTRequestHelper : NSObject
@property (nonatomic,strong) SLPRqMilkySetSleepTime *milkySetSleepTimeHelper;
@property (nonatomic,strong) SLPRqQuryMilkyCollectStatus *milkyQueryCollectStatusHelper;

- (void)clear;
- (void)bhtDisconnected;
@end
