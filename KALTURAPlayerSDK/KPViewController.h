//
//  KalPlayerViewController.h
//  HelloWorld
//
//  Created by Eliza Sapir on 9/11/13.
//
//

/* This class is responsible for player sdk
 in this class we have a player which contains a webview as subview, the webview reflects html5 NativeComponent */

// Copyright (c) 2013 Kaltura, Inc. All rights reserved.
// License: http://corp.kaltura.com/terms-of-use
//


@protocol KalturaPlayer;

#import "KPLog.h"
#import "KPViewControllerProtocols.h"
#import "KPPlayerConfig.h"
#import "KPController.h"
#import "KPCastProvider.h"

@class KPViewController;
@protocol KPViewControllerDelegate <NSObject>

@optional
- (void)updateCurrentPlaybackTime:(double)currentPlaybackTime;
- (void)kPlayer:(KPViewController *)player playerLoadStateDidChange:(KPMediaLoadState)state;
- (void)kPlayer:(KPViewController *)player playerPlaybackStateDidChange:(KPMediaPlaybackState)state;
- (void)kPlayer:(KPViewController *)player playerFullScreenToggled:(BOOL)isFullScreen;
- (void)kPlayer:(KPViewController *)player didFailWithError:(NSError *)error;
@end

@protocol KPSourceURLProvider <NSObject>

- (NSString *)urlForEntryId:(NSString *)entryId currentURL:(NSString*)current;

@end



@interface KPViewController : UIViewController

+ (void)setLogLevel:(KPLogLevel)logLevel;

/*!
 *  @method initWithURL:
 *  
 *  @abstract
 *  Initialize Player instance
 *
 *  @param url url of player content
 */
- (instancetype)initWithURL:(NSURL *)url;
 
/*!
 *  @method initWithConfiguration:
 *
 *  @abstract
 *  Initialize Player instance
 *
 *  @param configuration parameters of the player content
 */
- (instancetype)initWithConfiguration:(KPPlayerConfig *)configuration;

/*!
 *  @method loadPlayerIntoViewController:
 *
 *  @abstract
 *  Loads the player controller into the parent controller
 *
 *  @param parentViewController the controller which will call the player
 */
- (void)loadPlayerIntoViewController:(UIViewController *)parentViewController;


/*!
 *  @method removePlayer
 *
 *  @abstract
 *  Cleaning all the memory of the player
 *
 */
- (void)removePlayer;

/*!
 *  @method resetPlayer
 *
 *  @abstract
 *  Reset the player
 *
 */
- (void)resetPlayer;

/*!
 *  @method changeMedia:
 *
 *  @abstract
 *  Change the media without changing other parts of the configuration
 *
 *  @param media An arbirary object which is either:
 *  An NSString containing the entryId of the intended destination
 *  OR an NSDictionary
 *
 *
 */
- (void)changeMedia:(NSObject *)media;

/*!
 *  @method changeConfiguration:
 *
 *  @abstract
 *  Change the config with no need to recreate player instance
 *
 *  @param config set a new configuration
 */
- (void)changeConfiguration:(KPPlayerConfig *)config;

/*!
 *  @method prefetchPlayerResourcesWithConfig:
 *
 *  @abstract
 *  Prefetch player resources
 *
 *  @param config The new configuration object
 */
- (void) prefetchPlayerResourcesWithConfig:(KPPlayerConfig *)config;

@property (nonatomic, weak) id<KPViewControllerDelegate> delegate;

@property (nonatomic, weak) id<KPSourceURLProvider> customSourceURLProvider;

@property (nonatomic, strong) KPController *playerController;

/**
 *  Block which notifies that the full screen has been toggeled, when assigning to this block the default full screen behaviour will be canceled and the full screen handling will be your reponsibility. 
 */
@property (nonatomic, copy) void(^fullScreenToggeled)(BOOL isFullScreen);


/// Enables to change the player configuration
@property (nonatomic, strong) KPPlayerConfig *currentConfiguration;


// Kaltura Player External API

/// Change the source and returns the current source
@property (nonatomic, copy) NSURL *playerSource;

/// Signals that a internal or external web browser has been opened or closed
@property (nonatomic, weak) id kIMAWebOpenerDelegate;

/// Assigning this handler will disable the default share action and will supply the share params for custom use.
- (void)setShareHandler:(void(^)(NSDictionary *shareParams))shareHandler;


#pragma mark -
#pragma Kaltura Player External API - KDP API
// -----------------------------------------------------------------------------
// KDP API Types

typedef NS_ENUM(NSInteger, KDPAPIState) {
    /*  Player is not ready to work with the JavaScript API. */
    KDPAPIStateUnknown,
    /*  Player is ready to work with the JavaScript API (jsCallbackReady). */
    KDPAPIStateReady
};

/* The current kdp api state of the KDP API. (read-only)
 The kdp api state is affected by programmatic call to jsCallbackReady. */
@property (nonatomic, readonly) KDPAPIState kdpAPIState;

/*!
	@property	kPlayer
	@abstract	The player from which to source the media content for the view controller.
 */
@property (nonatomic, readonly) id<KPlayer> kPlayer;

/*!
	@property	kpCastProvider
	@abstract	cast provider
 */
@property (nonatomic, weak) id<KPCastProvider> castProvider;

/*!
 * @method registerReadyEvent
 *
 * @abstract
 * Registers to the players ready event
 *
 * @discussion
 * The registerReadyEvent function will notify that the player has been loaded
 * and it's possible to interact with it.
 *
 * Calls to registerReadyEvent will invoke the handler when the player is ready
 *
 *
 * @param handler
 * Callback for the ready event.
 *
 */
- (void)registerReadyEvent:(void(^)())handler;


/*!
 * @method addEventListener:eventID:handler:
 *
 * @abstract
 * Registers to one of the players events
 *
 * @param event name of One of the players events
 * @param eventID will enable to remove the current event by id
 * @param handler Callback for the ready event.
 */
- (void)addKPlayerEventListener:(NSString *)event eventID:(NSString *)eventID handler:(void(^)(NSString *eventName, NSString *params))handler;


/*!
 * @method removeEventListener:eventID:
 *
 * @abstract
 * Removes One of the players events by id
 *
 * @param event name of One of the players events.
 * @param eventID event id for removal.
 */
- (void)removeKPlayerEventListener:(NSString *)event eventID:(NSString *)eventID;



/*!
 * @method asyncEvaluate:expressionID:handler:
 *
 * @abstract
 * Evaluates values from the player
 *
 * @param expression @"{mediaProxy.entry.thumbnailUrl}:
 * @param expressionID expression id use for several expressions.
 * @param handler Callback with the value of the expression.
 */
- (void)asyncEvaluate:(NSString *)expression expressionID:(NSString *)expressionID handler:(void(^)(NSString *value))handler;



/*!
 * @method sendNotification:expressionID:forName
 *
 * @abstract
 * Notifies the player on specific events
 *
 * @param notificationName notification name
 * @param params json string for passing parameters to the controls layer (webview).
 */
- (void)sendNotification:(NSString *)notificationName withParams:(NSString *)params;



/*!
 * @method setKDPAttribute:propertyName:value
 *
 * @abstract
 * Controls elements in the player layer
 *
 * @param pluginName represents specific element
 * @param propertyName property of the plugin
 * @param value sets the property
 */
- (void)setKDPAttribute:(NSString *)pluginName propertyName:(NSString *)propertyName value:(NSString *)value;



/*!
 * @method triggerEvent:withValue
 *
 * @abstract
 * Triggers JavaScript methods on the player
 *
 * @param event methods name
 * @param value params for the method
 */
- (void)triggerEvent:(NSString *)event
           withValue:(NSString *)value;

- (void)releaseAndSavePosition;
- (void)releaseAndSavePositionWithPauseForCast:(BOOL)pause;
- (void)resumePlayer;
- (void)toggleFullscreen;

/// Wraps registerReadyEvent: method by block syntax.
@property (nonatomic, copy) void (^registerReadyEvent)(void(^readyCallback)());

/// Wraps addEventListener:eventID:handler: method by block syntax.
@property (nonatomic, copy, readonly) void (^addEventListener)(NSString *event, NSString *eventID, void(^)(NSString *eventName, NSString *params));

/// Wraps removeEventListener:eventID: method by block syntax.
@property (nonatomic, copy, readonly) void (^removeEventListener)(NSString *event, NSString *eventID);

/// Wraps asyncEvaluate:expressionID:handler: method by block syntax.
@property (nonatomic, copy, readonly) void (^asyncEvaluate)(NSString *expression, NSString *expressionID, void(^)(NSString *value));

/// Wraps sendNotification:expressionID:forName: method by block syntax.
@property (nonatomic, copy, readonly) void (^sendNotification)(NSString *notification, NSString *notificationName);

/// Wraps setKDPAttribute:propertyName:value: method by block syntax.
@property (nonatomic, copy, readonly) void (^setKDPAttribute)(NSString *pluginName, NSString *propertyName, NSString *value);

/// Wraps triggerEvent:withValue: method by block syntax.
@property (nonatomic, copy, readonly) void (^triggerEvent)(NSString *event, NSString *value);


@end

