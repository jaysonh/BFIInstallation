//
//  SceneFlashGordon.h
//  opencvExample
//
//  Created by jayson on 9/10/14.
//
//

#ifndef __opencvExample__SceneAliens__
#define __opencvExample__SceneAliens__

#include <iostream>
#include "FilmScene.h"
#include "ofxOpenCv.h"
#include "ofMain.h"
#include "global.h"
#include "ofxGreenscreen.h"
#include "ofxGui.h"
#include "ofxAVFVideoPlayer.h"

#include "ofQTKitPlayer.h"
#define MAIN_VIDEO_PATH "assets/alien/ALIEN_SCENESETTER_PRORES.mov"

#define NUM_ALIEN_SCENES 4
#define HELMET_OVELRAY_IMAGE            "assets/alien/ALIEN_HelmetCloseup_v08.png"
#define ALIEN_HEAD_OVERLAY_VIDEO_PATH   "assets/alien/ALIEN_aliencloseup_v04.mov"

#define CLOSE_UP_FACE_POS_X 640.0
#define CLOSE_UP_FACE_POS_Y 180.0
#define CLOSE_UP_FACE_SIZE_X 960
#define CLOSE_UP_FACE_SIZE_Y 540

#define SITDOWN_FACE_POS_X 450.0
#define SITDOWN_FACE_POS_Y 150.0
#define SITDOWN_FACE_SIZE_X 400
#define SITDOWN_FACE_SIZE_Y 250

#define ALIEN_CLOSE_FACE_POS_X 160
#define ALIEN_CLOSE_FACE_POS_Y 20.0
#define ALIEN_CLOSE_FACE_SIZE_X 1240
#define ALIEN_CLOSE_FACE_SIZE_Y 460

#define HARPOON_SHOT_FACE_POS_X 500
#define HARPOON_SHOT_FACE_POS_Y 150.0
#define HARPOON_SHOT_FACE_SIZE_X 700
#define HARPOON_SHOT_FACE_SIZE_Y 300

#define SITDOWN_OFF_SPEED_X 2.0f
#define SITDOWN_OFF_SPEED_Y 0.5f

#define TEXT1 "Relaxation, you have escaped."
#define TEXT2 "Fear and horror!"
#define TEXT3 "Sheer terror!"
#define TEXT4 "Ecstatic victory!"

#define EMOTION_GUIDELINES_TEXT1_POS_X 900
#define EMOTION_GUIDELINES_TEXT1_POS_Y 150

#define EMOTION_GUIDELINES_TEXT2_POS_X 1045
#define EMOTION_GUIDELINES_TEXT2_POS_Y 150

#define EMOTION_GUIDELINES_TEXT3_POS_X 1090
#define EMOTION_GUIDELINES_TEXT3_POS_Y 150

#define EMOTION_GUIDELINES_TEXT4_POS_X 1060
#define EMOTION_GUIDELINES_TEXT4_POS_Y 150

class SceneAliens : public FilmScene
{
public:
    SceneAliens();
    ~SceneAliens();
    void draw(ofxCvColorImage webCamImg, ofRectangle faceBoundingBox);
    
    float getVideoPosition();
    void toggleUI();
    
    bool isFinished();
    void setGreenScreenVals(int r,int g, int b);
    void closeAssets();
    
    void drawEmotionGuideLineText();
private:
    void drawBooth(ofxCvColorImage webCamImg, ofRectangle faceBoundingBox);
    void drawProjector();
    ofPoint _lastCentre,_lastSize;
    int isShowBoothOnProjector();
    ofFbo fboBuffer;
    ofxAVFVideoPlayer _mainVideo;
    //ofVideoPlayer _alienOverlayVideo[NUM_ALIEN_SCENES];
    int _currentPlayScene;
    
    ofxFloatSlider _rThresh;
    ofxFloatSlider _gThresh;
    ofxFloatSlider _bThresh;
    
    ofRectangle _lastBounds;
    
    ofImage img;
    ofxCvColorImage faceImg;
    ofPoint sitDownOff;
    
    
    ofImage _helmetOverlayImg;
    ofQTKitPlayer _alienHeadVid;
    
    
};
#endif /* defined(__opencvExample__SceneFlashGordon__) */
