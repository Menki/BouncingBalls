//
//  BouncingBallsAppController.h
//  BouncingBalls
//
//  Created by Augusto Souza on 8/21/11.
//  Copyright Menki Mobile 2011. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController	*viewController;
}

@end

