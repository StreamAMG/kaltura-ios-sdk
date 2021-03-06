//
//  KPIMAPlayerViewController.h
//  KALTURAPlayerSDK
//
//  Created by Nissim Pardo on 1/26/15.
//  Copyright (c) 2015 Kaltura. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>
#import "NSMutableDictionary+AdSupport.h"
#import "KPViewControllerProtocols.h"

@protocol IMAWebOpenerDataSource <NSObject>
- (id)imaWebOpenerDelegate;
@end


@interface KPIMAPlayerViewController : UIViewController 



/**
 *  Loads the ads into the IMA SDK
 *
 *  @param  NSString adLink contains the link to the XML file of the vast 
 *  @param  Block adListener which notifies the KPlayerViewController on the events of the ads
 */
- (void)loadIMAAd:(NSString *)adLink withContentPlayer:(AVPlayer *)contentPlayer;


/// Releasing the memory of the IMA player
- (void)removeIMAPlayer;

- (void)contentCompleted;
/// Pauses the advertisement
- (void)pause;
/// Resumes the advertisement
- (void)resume;

@property (nonatomic) CGFloat adPlayerHeight;
@property (nonatomic, copy) NSString *locale;
@property (nonatomic, weak) id<IMAWebOpenerDataSource> datasource;
@property (nonatomic, weak) id<KPlayerDelegate> delegate;
@end
