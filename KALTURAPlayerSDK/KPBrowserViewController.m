//
//  SKShareBrowserViewController.m
//  KALTURAPlayerSDK
//
//  Created by Nissim Pardo on 11/6/14.
//  Copyright (c) 2014 Kaltura. All rights reserved.
//

#import "KPBrowserViewController.h"
#import "DeviceParamsHandler.h"

@interface KPBrowserViewController () {
    
   // __weak IBOutlet UIWebView *webview;
    __weak IBOutlet UIView *loadingView;
}

@end

@implementation KPBrowserViewController

+ (id)currentBrowser {
    NSString *nibName = @"KPWebKitBrowserViewController";
    return [[NSClassFromString(nibName) alloc] initWithNibName:nibName bundle:nil];
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    NSBundle *playerBundle = [NSBundle bundleWithURL:[[NSBundle bundleForClass:[self class]] URLForResource:@"KALTURAPlayerSDKResources" withExtension:@"bundle"]];
    self = [super initWithNibName:nibNameOrNil bundle:playerBundle];
    if (self) {
        return self;
    }
    return nil;
}

- (void)setCompletionHandler:(KPBrowserCompletionHandler)completionHandler {
    _completionHandler = completionHandler;
}


- (IBAction)cancelPressed:(UIBarButtonItem *)sender {
    if (_completionHandler) {
        _completionHandler(KPBrowserResultSuccess, nil);
    } else {
        [self dismissViewControllerAnimated:YES completion:nil];
    }
}


@end
