Requisites
======

* iOS 8 build target
* [CocoaPods](http://cocoapods.org/)


Getting Started
======

##SDK CocoaPods Installation :

install KalturaPlayerSDKStreamamg. your `Podfile` should look like this:

```
#!ruby

target 'CCDemo' do
# Comment this line if you're not using Swift and don't want to use dynamic frameworks
use_frameworks!

pod 'KalturaPlayerSDKStreamamg', :git => 'https://bitbucket.org/sukdev/kaltura-ios-sdk/src/master/', :branch => 'master'
# Only if you are using Google Ads
pod "GoogleAds-IMA-iOS-SDK" , "~> 3.1.0"

end

```

* KalturaPlayerSDKStreamamg - Video SDK
* GoogleAds-IMA-iOS-SDK - SDK to show ads (you can remove if you don't need)
* google-cast-sdk - SDK to chromecast

then open a terminal windown and run:


```
#!

pod install
```

Next you need to go to the Target Build Settings and disable Bitcode:

```
#!

Enable Bitcode -> No
```

Go to your Info.plist file and add a new dictionary named:

```
#!

NSAppTransportSecurity
```

and add a bolean with the key *NSAllowsArbitraryLoads* with the value True (Yes).

##SDK Traditional Installation :

```
git clone https://{username}@bitbucket.org/sukdev/kaltura-ios-sdk.git
```


###Add the static library's .xcodeproj to the app's project

1. Find the _**`KALTURAPlayerSDK.xcodeproj`**_ from the subproject folder in _**`Finder`**_, and drag it into Xcode’s Navigator tree. Alternatively, add it with Xcode’s _**`Add Files`**_ File menu item.

![alt text](http://knowledge.kaltura.com/sites/default/files/styles/large/public/add_files.png)

Make sure to add the _**`KALTURAPlayerSDK.xcodeproj`**_ file only, **not the entire directory.** You can’t have the same project open in two different Xcode windows.If you find that you’re unable to navigate around the library project, check that you don’t have it open in another Xcode window. After you’ve added the subproject, it should appear below the main project in the Xcode’s Navigator tree:

![alt text](http://knowledge.kaltura.com/sites/default/files/styles/large/public/xcodetree.png)

###Configure the app target to build the static library target.


3. You will need to get the main project to build and link to the KALTURAPlayerSDK library.
4. In the main project app’s target settings, find the _**`Build Phases`**_ section. This is where you’ll configure the _**`KALTURAPlayerSDK`**_ target to automatically build and link to the _**`KALTURAPlayerSDK`**_ library.
5. After you’ve found the _**`Build Phases`**_ section, open the _**`Target Dependencies`**_ block and click the **`+`** button. In the hierarchy presented to you, the _**`KALTURAPlayerSDK`**_ target from the _**`KALTURAPlayerSDK`**_ project should be listed. Select it and click _**`Add`**_.![alt text](http://knowledge.kaltura.com/sites/default/files/styles/large/public/addDependencie.jpg)


###Configure the app target to link to the static library target.

1. You will need to set the app to link to the library when it’s built - just like you would a system framework you would want to use. Open the _**`Link Binary With Libraries`**_ section located a bit below the _**`Target Dependencies`**_ section, and click **`+`** in there too. At the top of the list there should be the _**`libKALTURAPlayerSDK.a`**_ static library that the main project target produces. Choose it and click _**`Add`**_.
![alt text](http://knowledge.kaltura.com/sites/default/files/styles/large/public/linkToSDK.jpg)
2. For Objective-C and Swift, in the main project target’s _**`Build Settings`**_ find the _**`Other Linker Flags`**_ line, and add _**`-ObjC`**_.![alt text](http://knowledge.kaltura.com/sites/default/files/styles/large/public/addingObjC_flag.jpg)


###Adding Resources Bundle

1. Choose the app target from the Targets  section.
2. Go to the _**`Products`**_ folder and drag the _**`KALTURAPlayerSDK.bundle`**_ to _**`Copy Bundle Resources`**_ section.![alt text](http://knowledge.kaltura.com/sites/default/files/styles/large/public/Bundle.png)

** If you click build now, you will see that the PlayerSDK library is built before the main project app, and they are linked together.**

** Please note if you're using Xcode 10 libstdc++ has been removed in iOS 12, migrate over to libc++ **

###Required Frameworks

•    SystemConfiguration
•    QuartzCore
•    CoreMedia
•    AVFoundation
•    AudioToolbox
•    AdSupport
•    WebKit
•    Social
•    MediaAccessibility
•    libSystem.dylib
•    libz.dylib
•    libstdc++.dylib
•    libstdc++.6.dylib
•    libstdc++.6.0.9.dylib
•    libxml2.dylib
•    libxml2.2.dylib
•    libc++.dylib
•    CoreFoundation
•    CFNetwork
•    MessageUI
•    Foundation
•    CoreGraphics
•    UIKit

**If you are using Xcode 7 notice that the extension "dylib" was changed to "tbd"*

Next you need to go to the Target Build Settings and disable Bitcode:

```
#!

Enable Bitcode -> No
```

Go to your Info.plist file and add a new dictionary named:

```
#!

NSAppTransportSecurity
```

###Additional for Swft

In your _**`project-name-Bridging-Header`**_ add:

```
#!swift

#import <KALTURAPlayerSDK/KPViewController.h>
#import <KALTURAPlayerSDK/KPCastProvider.h>
#import <KALTURAPlayerSDK/GoogleCastProvider.h>
```



Using Kaltura player
=====


In your view controller add the respective configuration constants, eg:


```
#!swift

import UIKit

class ViewController: UIViewController {

private let mediaServer = ""/// Set here your media server URL 
private let mediaUiConfID = "" /// Set here your UIConfigID
private let mediaPartnerID = "" /// Set here your Partner ID 

var player : KPViewController!

override func viewDidLoad() {
super.viewDidLoad()
let config = KPPlayerConfig(server: mediaServer, uiConfID: mediaUiConfID, partnerId: mediaPartnerID)
config!.entryId = "" /// Set here the video entryID 
config!.cacheSize = 0.8
player = KPViewController(configuration: config)
}

override func viewDidAppear(_ animated: Bool) {
super.viewDidLoad()

self.player.view.frame = CGRect(x: 0, y: 100, width: self.view.bounds.width, height: self.view.bounds.width / 16 * 9)
self.player.loadPlayer(into: self)

self.view.addSubview(player.view)
}
}

```

### Show the player in fullscreen ###
To show the player in fullscreen, you just need to present the Controller, eg:

```
#!swift

override func viewDidAppear(_ animated: Bool) {
super.viewDidLoad()

self.present(self.player, animated: true, completion: nil);
}
```

Build it and check if everything runs, the player appears and the video plays.

### Play audio in background ###

1 - Enable the Audio, Airplay, and Picture in the Picture background mode.

2 - In Xcode 8, select a target, and then under Capabilities > Background Modes, enable Audio, Airplay and Picture in Picture.

![alt text](https://vpaas.kaltura.com/documentation/Mobile-Video-Player-SDKs/v3-images/iOS/EnableAirPlay.png)

Implementation example: 

```
#!swift

// AppDelegate

    func applicationDidEnterBackground(_ application: UIApplication) {
        // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
        // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
        let enableAudioBackground = UserDefaults.standard.bool(forKey: kIsSwitchAudioBackgroundActivate)
        
        if enableAudioBackground {
            timer = Timer.scheduledTimer(timeInterval: 1, target: self,   selector: (#selector(AppDelegate.notifyplayerView)), userInfo: nil, repeats: true)
        }
    }
    
    @objc func notifyplayerView() {
        timer.invalidate()
        NotificationCenter.default.post(name: Notification.Name(kNotifyPlayerBackground), object: nil)
    }
	
// Your player class 

	override func viewDidLoad() {
        super.viewDidLoad()
        
        // Register to app notification
        NotificationCenter.default.addObserver(self, selector: #selector(PlayerViewController.notifyBackgroundMode), name: Notification.Name(kNotifyPlayerBackground), object: nil)
    }

    @objc func notifyBackgroundMode() {
        if player != nil, player?.kPlayer != nil {
            player?.kPlayer.play()
        }
    }
```

### Add the AirPlay and Chromecast functionality ###
1 - Enable the Audio, Airplay, and Picture in the Picture background mode.

2 - In Xcode 8, select a target, and then under Capabilities > Background Modes, enable Audio, Airplay and Picture in Picture.

![alt text](https://vpaas.kaltura.com/documentation/Mobile-Video-Player-SDKs/v3-images/iOS/EnableAirPlay.png)

## Add the AirPlay automatically on the view ##

If you want add the AirPlay button on the player bar (next to the logo) is bossible by adding:

```
#!swift

config?.addKey("airPlay.plugin", withValue: "true")
```

In this case is not possible change the AirPlay button color. 

## Add the AirPlay manually on the view ##

Import MediaPlayer, create an MPVolumeView, and then add it to your view as follows:

```
#!swift

let airPlayBtn = MPVolumeView(frame: CGRect(x: 0, y: 0, width: 44, height: 44))
airPlayBtn.showsVolumeSlider = false
container.addSubview(airPlayBtn)
```

Customize the image of the AirPlay button as follows:

```
#!swift

airPlayBtn.setRouteButtonImage(UIImage(named: "name"), for: UIControlState.normal)
```

Change the button tint/background color: 

```
#!swift

if let routeButton = airPlayBtn.subviews.last as? UIButton, let routeButtonTemplateImage  = routeButton.currentImage?.withRenderingMode(.alwaysTemplate) {
    airPlayBtn.setRouteButtonImage(routeButtonTemplateImage, for: .normal)
}
        
airPlayBtn.backgroundColor = UIColor.black
airPlayBtn.tintColor = UIColor.green
```

Install and import Google cast: 

Podfile:

```
#!swift

pod 'google-cast-sdk'
```

ViewController:

```
#!swift

import GoogleCast


var castProvider:GoogleCastProvider?


func preparePlayer() {

	...
	...

	castProvider = GoogleCastProvider.sharedInstance()
    castProvider?.delegate = self
    castProvider?.addCastObserver(self)
}


extension ViewController: KPCastProviderDelegate {
    
    func updateProgress(_ currentTime: TimeInterval) {
        
    }
    
    func ready(toPlay streamDuration: TimeInterval) {
        player?.castProvider = castProvider
    }
    
    func castPlayerState(_ state: String!) {
       
    }
    
    func startCasting() {
        player?.castProvider = castProvider
    }
    
    func stopCasting() {
        castProvider = GoogleCastProvider.sharedInstance()
        castProvider?.delegate = self
        castProvider?.addCastObserver(self)
    }
}
```


### How use DRM ###
For loading the DRM license of a video, the config must have the izsession.
izsession is an unique session that client gets after logging in to the website.
Throughout the izsession our service is recognizing if user is allowed to play content or not.

```
#!swift

config?.izsession = "izsessionvalue"
config?.addKey("izsession", withValue: "izsessionvalue")
```

### How to change media ###

For change media with the same configuration you can use: 

```
#!swift
player.changeMedia(media:"yourEntryID")
```

If you need to change the configuration of the player(i.e change ks), you can follow these steps: 

```
#!swift

        let config = KPPlayerConfig(server: mediaServer, uiConfID: mediaUiConfID, partnerId: mediaPartnerID)
        config!.entryId = "yourEntryID"
		config?.ks = "yourKs" // If needed 
		
		player.changeConfiguration(config)
```

### How remove unmute button on the player ###

You can remove the button by adding the following config: 

```
#!swift
    config.addConfig("unMuteOverlayButton.parent", "%27hideoverlay%27")
```

### How to enable Google Ad ###

Add the following configs: 

```
#!swift
    config?.addKey("doubleClick.plugin", withValue: "true")
    config?.addKey("doubleClick.leadWithFlash", withValue: "false")
    config?.addKey("doubleClick.adTagUrl", withValue: "tag-url")
```
