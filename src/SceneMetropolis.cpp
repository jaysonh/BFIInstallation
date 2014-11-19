//
//  SceneMetropolis.cpp
//  opencvExample
//
//  Created by jayson on 6/10/14.
//
//

#include "SceneMetropolis.h"

SceneMetropolis::SceneMetropolis()
{
    _needsTracking=true;
    _currentMaskImgIndx=0;
    _lastCentre = NULL;
    _heightTracking = true;
    _fadeSpeed=FADE_SPEED;
    _faceFade=0.0f;
    
    
    ofQTKitDecodeMode decodeMode = OF_QTKIT_DECODE_TEXTURE_ONLY;
	
    _ringsVideo.setPixelFormat(OF_PIXELS_RGBA);
    _ringsVideo.loadMovie(RINGS_MOVIE_FILE, decodeMode);
    
    _projectorScreenVideo.loadMovie(METROPOLIS_MOVIE_FILE);
    _projectorScreenVideo.setLoopState(OF_LOOP_NONE);
    
    _overlayImg.loadImage(METROPOLIS_OVERLAY_IMAGE_FILE);
    
    
    selectMetropolisFaceImage();
    
    _fadeSpeed = ofRandom(1.0,125.0);
    _randomFlashFrame=0;
    _randomFlashFrame2=0;
    
    _cutSceneTimesList.push_back(new CutSceneTime(14.23, 21.00, 60.00));
    _cutSceneTimesList.push_back(new CutSceneTime(27.16, 35.00, 60.00));
    _cutSceneTimesList.push_back(new CutSceneTime(43.03, 49.19, 60.00));
    _cutSceneTimesList.push_back(new CutSceneTime(56.09, 59.23, 60.00));
    
    _emotionGuideList.clear();
    _emotionGuideList.push_back(new CutSceneTime(0.0, 21.00, 60.00));
    _emotionGuideList.push_back(new CutSceneTime(21.00, 35.00, 60.00));
    _emotionGuideList.push_back(new CutSceneTime(35.00, 60.00, 60.00));
    
    fboBuffer.allocate(BOOTH_SCREEN_SIZE_X,BOOTH_SCREEN_SIZE_Y);
    firstRun = true;
    
   // _metropolisFaceVid.play();
    _projectorScreenVideo.play();
    _ringsVideo.play();
    //_overlayVid.play();
    _lastBounds.x=0;
    _lastBounds.y=0;

}

void SceneMetropolis::selectMetropolisFaceImage()
{
    int indx = (int)ofRandom(0,4);
    switch(indx)
    {
        case 0:
            _metropolisFaceImg.loadImage(METROPOLIS_FACE_IMAGE_1);
            break;
        case 1:
            _metropolisFaceImg.loadImage(METROPOLIS_FACE_IMAGE_2);
            break;
        case 2:
            _metropolisFaceImg.loadImage(METROPOLIS_FACE_IMAGE_3);
            break;
        case 3:
            _metropolisFaceImg.loadImage(METROPOLIS_FACE_IMAGE_4);
            break;
    }
}

void SceneMetropolis::draw(ofxCvColorImage webCamImg, ofRectangle faceBoundingBox)
{
    _projectorScreenVideo.update();
    _ringsVideo.update();
    if(!_projectorScreenVideo.isPlaying() && _projectorScreenVideo.isLoaded())
    {
        _projectorScreenVideo.play();
    }
    drawBooth(webCamImg,faceBoundingBox);
   drawProjector();
    
    if(_projectorScreenVideo.getPosition() > START_FADE_TIME)
    {
        ofFill();
        ofSetColor(0,0,0,_endFade);
        ofRect(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
        
        if(_endFade < 255.0f)
            _endFade += 5.0f;
    }
    
    if(_projectorScreenVideo.getPosition()>= 1.0f)
    {
        _endFade=1.0f;
    }
}


void SceneMetropolis::drawBooth(ofxCvColorImage webCamImg, ofRectangle faceBoundingBox)
{
    if(ofRandom(0,200) < 25.0f)
        selectMetropolisFaceImage();
    
    ofSetColor(255,255,255,255);
    
    ofxCvGrayscaleImage bwImg;
    bwImg= webCamImg;
    //bwImg.resize(BOOTH_SCREEN_SIZE_X,BOOTH_SCREEN_SIZE_Y);
    
       fboBuffer.begin();
    //ofEnableAlphaBlending();
    ofFill();
    //ofClear(0,0,0);
    //bwImg.draw(BOOTH_SCREEN_POS_X,0,BOOTH_SCREEN_SIZE_X,BOOTH_SCREEN_SIZE_Y);
    ofSetColor(255,255,255,255);
    
    if(_heightTracking && faceBoundingBox.width>0)
    {
        ofPoint faceCentre = faceBoundingBox.getCenter();
        
        float faceCentreDiffY = BOOTH_SCREEN_SIZE_Y/2.0-25.0f-faceCentre.y;
        float faceCentreDiffX = BOOTH_SCREEN_SIZE_X/2.0-faceCentre.x;
        
        float faceSizeDiff = 384.000000 / faceBoundingBox.width;        
        
        float w = faceSizeDiff * (float)BOOTH_SCREEN_SIZE_X;
        float h = faceSizeDiff * (float)BOOTH_SCREEN_SIZE_Y * 1.25f;
        
        float xPos = (BOOTH_SCREEN_SIZE_X/2) - w/2 + faceCentreDiffX;
        float yPos = (BOOTH_SCREEN_SIZE_Y/2) - h/2 + faceCentreDiffY;
        
        ofRectangle faceBounds;
        
        float currentMult = 0.25f;
        float prevMult = 0.75f;
        
        if(_lastBounds.x != 0 && _lastBounds.y!=0)
        {
            faceBounds = ofRectangle(xPos* currentMult + _lastBounds.x*prevMult,yPos * currentMult + _lastBounds.y * prevMult,w * currentMult + _lastBounds.width * prevMult,h * currentMult + _lastBounds.height*prevMult );
           
        }else
        {
            faceBounds = ofRectangle(xPos,yPos,w,h);
        }
        
        bwImg.draw(faceBounds.x,faceBounds.y,faceBounds.width,faceBounds.height);
        
        _lastBounds.x = faceBounds.x;
        _lastBounds.y = faceBounds.y;
        _lastBounds.width=faceBounds.width;
        _lastBounds.height=faceBounds.height;
    }else
        bwImg.draw(BOOTH_SCREEN_POS_X,0,BOOTH_SCREEN_SIZE_X,BOOTH_SCREEN_SIZE_Y);
    
    
    ofSetColor(255,255,255,_faceFade);
    _metropolisFaceImg.draw(BOOTH_SCREEN_POS_X,0,BOOTH_SCREEN_SIZE_X,BOOTH_SCREEN_SIZE_Y);
    
    
    
    ofFill();
    ofSetColor(255,255,255,255);

    _overlayImg.draw(BOOTH_SCREEN_POS_X,0,BOOTH_SCREEN_SIZE_X,BOOTH_SCREEN_SIZE_Y);
    
    _ringsVideo.draw(BOOTH_SCREEN_POS_X,0,BOOTH_SCREEN_SIZE_X,BOOTH_SCREEN_SIZE_Y);
    
    fboBuffer.end();
    fboBuffer.draw(BOOTH_SCREEN_POS_X,0,BOOTH_SCREEN_SIZE_X,BOOTH_SCREEN_SIZE_Y);
    
    
    _faceFade += _fadeSpeed;
    
    if(_faceFade > 255.0f *0.75)
    {
        _faceFade=255.0f * 0.75;
        _fadeSpeed = -1.0f*abs(_fadeSpeed);
    }
    if(_faceFade <= 0.0f)
    {
        _faceFade=0.0f;
        if(ofGetFrameNum()%50==0)
             _fadeSpeed = ofRandom(2.5,25.0);
        
        
       
    }
    
    
    /*
    if(_randomFlashFrame2 == 0 || ofGetFrameNum() >= _randomFlashFrame2)
    {
        ofFill();
        if(_randomFlashFrame2+1 == ofGetFrameNum())
            _randomFlashFrame2 = ofGetFrameNum() + (int)ofRandom(25,150);
        ofSetColor(255,255,255);
        ofRect(BOOTH_SCREEN_POS_X,0,BOOTH_SCREEN_SIZE_X,BOOTH_SCREEN_SIZE_Y);
    }*/
    /*if(isShowBoothOnProjector())
        fboBuffer.draw(25,25,BOOTH_SCREEN_SIZE_X/4,BOOTH_SCREEN_SIZE_Y/4);
    else
        _projectorScreenVideo.draw(25,25,BOOTH_SCREEN_SIZE_X/4,BOOTH_SCREEN_SIZE_Y/4);*/
    _font.drawString("Outside Feed:", OUTSIDE_FEED_TEXT_POS_X, OUTSIDE_FEED_TEXT_POS_Y);
    
    _font2.drawString("LIVE",LIVE_TEXT_POS_X,LIVE_TEXT_POS_Y);
    
    if(isShowBoothOnProjector() >= 0)
    {
        ofSetColor(0,0,0);
        ofRect(LIVE_ICON_POS_X,LIVE_ICON_POS_Y,_liveIcon.getWidth()/4,_liveIcon.getHeight()/4);
        ofSetColor(255,255,255);
        _liveIcon.draw(LIVE_ICON_POS_X,LIVE_ICON_POS_Y,_liveIcon.getWidth(),_liveIcon.getHeight());
        fboBuffer.draw(BOOTH_PREVIEW_WINDOW_POS_X,BOOTH_PREVIEW_WINDOW_POS_Y,BOOTH_PREVIEW_WINDOW_SIZE_X,BOOTH_PREVIEW_WINDOW_SIZE_Y);
    }else
    {
        _notLiveIcon.draw(LIVE_ICON_POS_X,LIVE_ICON_POS_Y);
        _projectorScreenVideo.draw(BOOTH_PREVIEW_WINDOW_POS_X,BOOTH_PREVIEW_WINDOW_POS_Y,BOOTH_PREVIEW_WINDOW_SIZE_X,BOOTH_PREVIEW_WINDOW_SIZE_Y);
    }
    drawEmotionGuideLineText();
    
}

float SceneMetropolis::getVideoPosition()
{
    if(_projectorScreenVideo.isPlaying())
        return _projectorScreenVideo.getPosition();
    else
        return 0.0f;
}

int SceneMetropolis::isShowBoothOnProjector()
{
    int indx=-1;
    for(int i = 0; i < _cutSceneTimesList.size();i++)
    {
        CutSceneTime * cutSceneTime = _cutSceneTimesList[i];
        
        if(cutSceneTime->isWithIn(_projectorScreenVideo.getPosition() ))
            indx=i;
    }
    return indx;
}


void SceneMetropolis::drawEmotionGuideLineText()
{
    int indx=0;
    
    for(int i = 0; i < _emotionGuideList.size() ;i++)
    {
        CutSceneTime * cutSceneTime = _emotionGuideList[i];
        
        if(cutSceneTime->isWithIn(_projectorScreenVideo.getPosition()))
        {
            indx=i ;
        }
    }
    _font.drawString("Notes:",EMOTION_GUIDELINES_TEXT_POS_X,EMOTION_GUIDELINES_TEXT_POS_Y);
    switch(indx)
    {
        case 0:
            _font.drawString(TEXT1,EMOTION_GUIDELINES_TEXT1_POS_X,EMOTION_GUIDELINES_TEXT1_POS_Y);
            break;
        case 1:
            _font.drawString(TEXT2,EMOTION_GUIDELINES_TEXT2_POS_X,EMOTION_GUIDELINES_TEXT2_POS_Y);
            break;
        case 2:
            _font.drawString(TEXT3,EMOTION_GUIDELINES_TEXT3_POS_X,EMOTION_GUIDELINES_TEXT3_POS_Y);
            break;
    }
}

void SceneMetropolis::drawProjector()
{
    if(isShowBoothOnProjector() >=0)
        fboBuffer.draw(PROJECTOR_SCREEN_POS_X,0,PROJECTOR_SCREEN_SIZE_X,PROJECTOR_SCREEN_SIZE_Y);
    else
        _projectorScreenVideo.draw(PROJECTOR_SCREEN_POS_X,0,PROJECTOR_SCREEN_SIZE_X,PROJECTOR_SCREEN_SIZE_Y);

}

void SceneMetropolis::setGreenScreenVals(int r,int g, int b)
{
    
}

bool SceneMetropolis::isFinished()
{
    
    if(_projectorScreenVideo.getPosition()>0.99f)
        return true;
    else
        return false;
    //return !_projectorScreenVideo.isPlaying();
}


void SceneMetropolis::closeAssets()
{
    
    _projectorScreenVideo.close();
    _ringsVideo.close();
    
    
}