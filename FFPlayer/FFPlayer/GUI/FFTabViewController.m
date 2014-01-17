//
//  FFTabViewController.m
//  FFPlayer
//
//  Created by Coremail on 14-1-16.
//  Copyright (c) 2014年 Coremail. All rights reserved.
//

#import "FFTabViewController.h"
#import "FFLocalViewController.h"
#import "FFSettingViewController.h"
#import "FFHelper.h"
#import "FFSetting.h"

@interface FFTabViewController ()
{
    time_t      _lastClickTime;
    int         _clickLocalCount;
    int         _indexOfLocal;
}
@end

@implementation FFTabViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.

    _lastClickTime = 0;
    _indexOfLocal = 0;
    _clickLocalCount = 0;
    
    int c = self.viewControllers.count;
    for (int i = 0;i < c; ++i) {
        UIViewController * viewController = [self.viewControllers objectAtIndex:i];
        if ( [viewController isKindOfClass:[UINavigationController class]] ) {
            UINavigationController * nav = (UINavigationController *)viewController;
            UIViewController * root = [nav.viewControllers objectAtIndex:0];
            if ( [root isKindOfClass:[FFLocalViewController class]] ) {
                _indexOfLocal = i;
                viewController.tabBarItem.title = NSLocalizedString(@"Local", nil);
            } else if ( [root isKindOfClass:[FFSettingViewController class]] )
                viewController.tabBarItem.title = NSLocalizedString(@"Setting", nil);
        }
    }
    
    self.delegate = self;
    
    int nLastIndex = [[FFSetting default] lastSelectedTab];
    self.selectedIndex = nLastIndex;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (BOOL)tabBarController:(UITabBarController *)theTabBarController shouldSelectViewController:(UIViewController *)viewController
{
    BOOL boRes = (theTabBarController.selectedViewController != viewController);
    if ( !boRes && [theTabBarController selectedIndex] == _indexOfLocal )  {
        time_t now = time(NULL);
        if ( now > _lastClickTime + 1)
            _clickLocalCount = 1;
        else
            ++_clickLocalCount;
        _lastClickTime = now;
        if ( _clickLocalCount > 2 ) {
            _clickLocalCount = 0;
            UINavigationController * nav = (UINavigationController *)viewController;
            FFLocalViewController * local = [nav.viewControllers objectAtIndex:0];
            [local toggleLock];
        }
    }
    return boRes;
}

- (void)tabBarController:(UITabBarController *)tabBarController didSelectViewController:(UIViewController *)viewController {
    
    [[FFSetting default] setLastSelectedTab:[tabBarController selectedIndex]];
}

@end
