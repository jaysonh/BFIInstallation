//
//  FilmScene.h
//  opencvExample
//
//  Created by jayson on 6/10/14.
//
//

#ifndef __opencvExample__FilmScene__
#define __opencvExample__FilmScene__

#include "global.h"
#include <iostream>
#include "ofxOpenCv.h"
#include "CutSceneTime.h"
#include "ofMain.h"

class FilmScene
{
public:
    FilmScene();
    virtual void draw(ofxCvColorImage webCamImg, ofRectangle faceBoundingBox)=0;
    //virtual void init()=0;
    virtual void closeAssets()=0;
    virtual void setGreenScreenVals(int r,int g, int b)=0;
    virtual float getVideoPosition()=0;
    void toggleUI();
    
    void toggleHeightTracking();
    bool isAdjustingFaceHeight();
    virtual bool isFinished()=0;
    bool needsFaceTracking();
protected:
    
    ofImage _liveIcon,_notLiveIcon;
    
    ofTrueTypeFont	_font,_font2;
    bool _showUI;
    bool _needsTracking;
    bool _heightTracking;
    vector <CutSceneTime*> _cutSceneTimesList;
    vector <CutSceneTime*> _emotionGuideList;
};
#endif /* defined(__opencvExample__FilmScene__) */
