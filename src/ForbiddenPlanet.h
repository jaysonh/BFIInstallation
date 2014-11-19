//
//  ForbiddenPlanet.h
//  opencvExample
//
//  Created by jayson on 7/10/14.
//
//

#ifndef __opencvExample__ForbiddenPlanet__
#define __opencvExample__ForbiddenPlanet__

#include <iostream>
#include "FilmScene.h"
#include "ofxOpenCv.h"
#include "global.h"
#include "ofMain.h"
#include "ofxAVFVideoPlayer.h"

#define FORBIDDENPLANET_MAIN_VIDEO  "assets/forbidden_planet/ForbiddenPlanet_Scenesetter_v01.mov"
#define LASER_VIDEO                 "assets/forbidden_planet/ForbiddenPlanet_Lasers_v01.mov"
#define BACKGROUND_IMAGE            "assets/forbidden_planet/ForbiddenPlanet_Backdrop.png"

#define FACE_TARGET_POS_X 270
#define FACE_TARGET_POS_Y 242

#define TEXT1 "Howl and roar"
#define TEXT2 "Furious anger"

#define EMOTION_GUIDELINES_TEXT1_POS_X 1080
#define EMOTION_GUIDELINES_TEXT1_POS_Y 150

#define EMOTION_GUIDELINES_TEXT2_POS_X 1085
#define EMOTION_GUIDELINES_TEXT2_POS_Y 150


class ForbiddenPlanet : public FilmScene
{
public:
    
    ForbiddenPlanet();
    void draw(ofxCvColorImage webCamImg, ofRectangle faceBoundingBox);
    float getVideoPosition();
    
    void setGreenScreenVals(int r,int g, int b);
    bool isFinished();
    void closeAssets();
private:
    void drawContours(float contrast, ofImage img,float sizeMultX,float sizeMultY,ofRectangle faceBoundingBox);
    
    void drawEmotionGuideLineText();
    int isShowBoothOnProjector();
    void drawProjectorScreen();
    void drawBoothScreen(ofxCvColorImage webCamImg, ofRectangle faceBoundingBox);
    float _contrast;
    
    ofFbo fboBuffer;
    
    ofRectangle *_lastBounds;
    
    ofxAVFVideoPlayer        _mainVideo;
    ofVideoPlayer        _laserVideo;
    ofImage              _backdropImg;
    
    ofxCvContourFinder 	contourFinder;
    
    ofxCvGrayscaleImage 	grayImage;
    ofxCvGrayscaleImage 	grayBg;
    ofxCvGrayscaleImage 	grayDiff;
    
    bool                 learnBackground;
};
#endif /* defined(__opencvExample__ForbiddenPlanet__) */
