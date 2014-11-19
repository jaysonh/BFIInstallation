//
//  SceneFlashGordon.h
//  opencvExample
//
//  Created by jayson on 9/10/14.
//
//

#ifndef __opencvExample__SceneFlashGordon__
#define __opencvExample__SceneFlashGordon__

#define OF_VIDEO_PLAYER_QUICKTIME
#include <iostream>
#include "FilmScene.h"
#include "ofxOpenCv.h"
#include "ofMain.h"
#include "global.h"
#include "ofxGreenscreen.h"
#include "ofxGui.h"
#include "ofQTKitPlayer.h"
#include "ofxAVFVideoPlayer.h"

//#define MAIN_VIDEO_PATH "assets/flashgordon/Flash.Gordon_Scenesetter.mov"
#define MAIN_VIDEO_PATH "assets/flashgordon/FLASHGORDON_SCENESETTER_PRORES.mov"
#define BACKDROP1_PATH  "assets/flashgordon/FlashGordon_Backdrop_1.png"
#define BACKDROP2_PATH  "assets/flashgordon/FlashGordon_Backdrop_2.png"
#define BACKDROP3_PATH  "assets/flashgordon/FlashGordon_Backdrop_3.png"
#define HOVERBIKE_LAYER "assets/flashgordon/FlashGordon_Hoverbike_lasers_v03.mov"

#define NUM_BACKDROP_IMAGES 3


#define TEXT1 "Cavalier bravery"
#define TEXT2 "You are hit"
#define TEXT3 "Cocky laughter"

#define EMOTION_GUIDELINES_TEXT1_POS_X 1055
#define EMOTION_GUIDELINES_TEXT1_POS_Y 150

#define EMOTION_GUIDELINES_TEXT2_POS_X 1095
#define EMOTION_GUIDELINES_TEXT2_POS_Y 150

#define EMOTION_GUIDELINES_TEXT3_POS_X 1080
#define EMOTION_GUIDELINES_TEXT3_POS_Y 150

class SceneFlashGordon : public FilmScene
{
public:
    void draw(ofxCvColorImage webCamImg, ofRectangle faceBoundingBox);
    SceneFlashGordon();
    float getVideoPosition();
    
    bool isFinished();
    void setGreenScreenVals(int r,int g, int b);
    
    void closeAssets();
private:
    
    void drawEmotionGuideLineText();
    void drawBooth(ofxCvColorImage webCamImg, ofRectangle faceBoundingBox);
    void drawProjector();
    
    int isShowBoothOnProjector();
    
    
    int newPixsSize;
    unsigned char *newPixs ;
    
    ofFbo fboBuffer;
    ofxAVFVideoPlayer _mainVideo;
    ofVideoPlayer _hoverBikeVideo;
    
    ofImage _backdropImg[NUM_BACKDROP_IMAGES];
    
    int _currentBackdrop;
    
    
    
    ofImage heroImg;
	ofxGreenscreen greenscreen;
    
    
    float _rThresh;
    float _gThresh;
    float _bThresh;
    
    ofImage _camImg;
};
#endif /* defined(__opencvExample__SceneFlashGordon__) */
