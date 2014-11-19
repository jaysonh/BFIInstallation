//
//  SceneMetropolis.h
//  opencvExample
//
//  Created by jayson on 6/10/14.
//
//

#ifndef __opencvExample__SceneMetropolis__
#define __opencvExample__SceneMetropolis__

#include <iostream>
#include "ofMain.h"
#include "global.h"
#include "ofxOpenCv.h"
#include "FilmScene.h"
#include "CutSceneTime.h"
#include "ofQTKitPlayer.h"
#include "ofxAVFVideoPlayer.h"

//#define METROPOLIS_MOVIE_FILE           "assets/metropolis/Metropolis_Scenesetter_v03_grays.mov"
#define METROPOLIS_MOVIE_FILE           "assets/metropolis/METROPOLIS_SCENESETTER_PRORES.mov"
#define RINGS_MOVIE_FILE                "assets/metropolis/Metropolis_Rings_v04.mov"
#define METROPOLIS_OVERLAY_IMAGE_FILE   "assets/metropolis/Metropolis_Mask_v04.png"
#define METROPOLIS_OVERLAY_VIDEO_FILE   "assets/metropolis/Metropolis_Mask_ANIMATED_v01.mov"
#define METROPOLIS_MASK_IMAGE_FILE      "assets/metropolis/Metropolis_Face_V02.png"
#define METROPOLIS_MASK_VIDEO_FILE      "assets/metropolis/Metropolis_Mask_ANIMATED_v01.mov"
#define METROPOLIS_CUT_SCENE_TIMES_FILE "assets/metropolis/cutscene_times.txt"

#define METROPOLIS_FACE_IMAGE_1         "assets/metropolis/Metropolis_Mask_Dynamic_01.png"
#define METROPOLIS_FACE_IMAGE_2         "assets/metropolis/Metropolis_Mask_Dynamic_02.png"
#define METROPOLIS_FACE_IMAGE_3         "assets/metropolis/Metropolis_Mask_Dynamic_03.png"
#define METROPOLIS_FACE_IMAGE_4         "assets/metropolis/Metropolis_Mask_Dynamic_04.png"

#define METROPOLIS_FACE_CENTRE_X 640
#define METROPOLIS_FACE_CENTRE_Y 423

#define FADE_SPEED 0.02f

#define START_FADE_TIME 0.9f


#define TEXT1 "Robotic Stare"
#define TEXT2 "Evil stare"
#define TEXT3 "Evil smile"

#define EMOTION_GUIDELINES_TEXT1_POS_X 1085
#define EMOTION_GUIDELINES_TEXT1_POS_Y 150

#define EMOTION_GUIDELINES_TEXT2_POS_X 1135
#define EMOTION_GUIDELINES_TEXT2_POS_Y 150

#define EMOTION_GUIDELINES_TEXT3_POS_X 1140
#define EMOTION_GUIDELINES_TEXT3_POS_Y 150


class SceneMetropolis : public FilmScene
{
public:
    
    SceneMetropolis();
    void draw(ofxCvColorImage webCamImg, ofRectangle faceBoundingBox);
    float getVideoPosition();
    
    void setGreenScreenVals(int r,int g, int b);
    bool isFinished();
    void closeAssets();
private:
    
    void drawEmotionGuideLineText();
    void selectMetropolisFaceImage();
    int isShowBoothOnProjector();
    void drawBooth(ofxCvColorImage webCamImg, ofRectangle faceBoundingBox);
    void drawProjector();
    ofFbo fboBuffer;
    
    int _randomFlashFrame;
    int _randomFlashFrame2;
    ofxAVFVideoPlayer _projectorScreenVideo;
    ofQTKitPlayer _ringsVideo;
    
    ofImage       _overlayImg;
    ofImage       _metropolisFaceImg;

    
    float _faceFade;
    float _fadeSpeed;
    ofPoint * _lastCentre;
    ofRectangle _lastBounds;
    
    float _endFade;
    bool firstRun;
    
    int _currentMaskImgIndx;
        
};
#endif /* defined(__opencvExample__SceneMetropolis__) */
