//
//  ALMoviePlayerControls.h
//  ALMoviePlayerController
//
//  Created by Anthony Lobianco on 10/8/13.
//  Copyright (c) 2013 Anthony Lobianco. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MediaPlayer/MPMoviePlayerController.h>


@protocol ALMoviePlayerInterface <NSObject>

-(BOOL)isFullscreen;
-(BOOL)isPlaying;

-(CGFloat) getDuration; //return the full time
-(CGFloat) getCurrentPlaybackRate;
-(void) setCurrentPlaybackRate:(CGFloat) v;
-(void) switchScalingMode;

-(void)setFullscreen:(BOOL)bo animated:(BOOL)animated;

-(void) onPause;
-(void) setCurrentPlaybackTime:(CGFloat)pos;
-(void) onPlay;
-(void) onForward:(CGFloat)f;
-(void) onRewind:(CGFloat)f;
-(void) onNext;
-(void) onPrev;
-(void) onDone;
-(void) onHUD:(BOOL)display;

@end

@class ALMoviePlayerController;

typedef enum {
    /** Controls will appear in a bottom bar */
    ALMoviePlayerControlsStyleEmbedded,
    
    /** Controls will appear in a top bar and bottom bar */
    ALMoviePlayerControlsStyleFullscreen,
    
    /** Controls will appear as ALMoviePlayerControlsStyleFullscreen when in fullscreen and ALMoviePlayerControlsStyleEmbedded at all other times */
    ALMoviePlayerControlsStyleDefault,
    
    /** Controls will not appear */
    ALMoviePlayerControlsStyleNone,
    
} ALMoviePlayerControlsStyle;

typedef enum {
    /** Controls are not doing anything */
    ALMoviePlayerControlsStateIdle,
    
    /** Controls are waiting for movie to finish loading */
    ALMoviePlayerControlsStateLoading,
    
    /** Controls are ready to play and/or playing */
    ALMoviePlayerControlsStateReady,
    
} ALMoviePlayerControlsState;

@interface ALMoviePlayerControls : UIView

/** 
 The style of the controls. Can be changed on the fly.
 
 Default value is ALMoviePlayerControlsStyleDefault
 */
@property (nonatomic, assign) ALMoviePlayerControlsStyle style;

/** 
 The state of the controls.
 */
@property (nonatomic, readonly) ALMoviePlayerControlsState state;

/**
 The color of the control bars. 
 
 Default value is black with a hint of transparency.
 */
@property (nonatomic, strong) UIColor *barColor;

/**
 The height of the control bars. 
 
 Default value is 70.f for iOS7+ and 50.f for previous versions.
 */
@property (nonatomic, assign) CGFloat barHeight;

/**
 The amount of time that the controls should stay on screen before automatically hiding.
 
 Default value is 5 seconds.
 */
@property (nonatomic, assign) NSTimeInterval fadeDelay;

/**
 The rate at which the movie should fastforward or rewind.
 
 Default value is 3x.
 */
@property (nonatomic, assign) float seekRate;

/** 
 Should the time-remaining number decrement as the video plays?
 
 Default value is NO.
 */
@property (nonatomic) BOOL timeRemainingDecrements;

/**
 Are the controls currently showing on screen?
 */
@property (nonatomic, readonly, getter = isShowing) BOOL showing;


/** 
 The default initializer method. The parameter may not be nil.
 */
-(id)initWithMoviePlayer:(id<ALMoviePlayerInterface>)moviePlayer style:(ALMoviePlayerControlsStyle)style;

-(void) setDurationSliderMaxMinValues:(CGFloat)duration;
-(void) updateMoviePlayback:(CGFloat)cur total:(CGFloat)totalTime;
-(void) showControls:(void(^)(void))completion;
-(void) hideControls:(void(^)(void))completion;
-(void) updatePlayState:(BOOL)playing hasNext:(BOOL)hasNext hasPrev:(BOOL)hasPrev scallingMod:(int)scallingMode;

-(BOOL) isLoadingIndicators;
-(void) showLoadingIndicators;
-(void) hideLoadingIndicators;

@end


@protocol FFMovieCallback <NSObject>

-(BOOL) hasNext;
-(BOOL) hasPre;
-(void) onNext:(UIViewController *)control curPos:(CGFloat)curPos;
-(void) onPre:(UIViewController *)control curPos:(CGFloat)curPos;
-(void) onFinish:(UIViewController *)control curPos:(CGFloat)curPos;

@end



