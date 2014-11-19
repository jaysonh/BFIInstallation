//
//  SceneFlashGordon.cpp
//  opencvExample
//
//  Created by jayson on 9/10/14.
//
//

#include "SceneAliens.h"

 SceneAliens::SceneAliens()
{
    sitDownOff = ofPoint(0,0);
    
    _needsTracking=true;
    _lastBounds.x=0;
    _lastBounds.y=0;
    _lastBounds.width=0;
    _lastBounds.height=0;
    
	

    
    
    _helmetOverlayImg.loadImage(HELMET_OVELRAY_IMAGE);
    
    ofQTKitDecodeMode decodeMode = OF_QTKIT_DECODE_TEXTURE_ONLY;
	
    _alienHeadVid.setPixelFormat(OF_PIXELS_RGBA);
    _alienHeadVid.loadMovie(ALIEN_HEAD_OVERLAY_VIDEO_PATH, decodeMode);

    
    
    _mainVideo.loadMovie(MAIN_VIDEO_PATH);
    _mainVideo.setLoopState(OF_LOOP_NONE);
    
    
    _mainVideo.play();
    
    _currentPlayScene=0;
        
    
    _cutSceneTimesList.push_back(new CutSceneTime(2.07, 6.01, 50.01));
    _cutSceneTimesList.push_back(new CutSceneTime(10.21, 17.08, 50.01));
    _cutSceneTimesList.push_back(new CutSceneTime(30.06, 38.17, 50.01));
    _cutSceneTimesList.push_back(new CutSceneTime(45.14, 50.01, 50.01 ));
    
    _emotionGuideList.push_back(new CutSceneTime(0.0, 6.01, 50.01));
    _emotionGuideList.push_back(new CutSceneTime(6.01, 17.08, 50.01));
    _emotionGuideList.push_back(new CutSceneTime(17.08, 38.17, 50.01));
    _emotionGuideList.push_back(new CutSceneTime(38.17, 50.01, 50.01 ));
    
    fboBuffer.allocate(BOOTH_SCREEN_SIZE_X,BOOTH_SCREEN_SIZE_Y);
    
    
    _alienHeadVid.play();
}

void SceneAliens::closeAssets()
{
    printf("closing alien videos\n");
    _mainVideo.close();
    _alienHeadVid.close();
}

SceneAliens::~SceneAliens()
{
    
}

void SceneAliens::draw(ofxCvColorImage webCamImg, ofRectangle faceBoundingBox)
{
    _mainVideo.update();
    _alienHeadVid.update();
    
    
    if(!_mainVideo.isPlaying() && _mainVideo.isLoaded())
       {
           printf("starting main video\n");
           _mainVideo.play();
       }
    
   // if(!_alienHeadVid.isPlaying() && _alienHeadVid.isLoaded())
   // {
   //     _alienHeadVid.play();
   // }
   
    drawBooth(webCamImg,faceBoundingBox);
    drawProjector();
    
}

float SceneAliens::getVideoPosition()
{
    return _mainVideo.getPosition();
}


void SceneAliens::drawBooth(ofxCvColorImage webCamImg, ofRectangle faceBoundingBox)
{
    fboBuffer.begin();
   // ofEnableAlphaBlending();
    ofClear(0,0,0);
    
    
    unsigned char *pixs = webCamImg.getPixels();
    
    
    
    ofxCvGrayscaleImage bwImg;
    bwImg= webCamImg;
    int newW = webCamImg.getWidth();
    int newH = webCamImg.getHeight();
    
    webCamImg.setFromPixels(pixs,newW,newH);
    
    float sceneCentreX = CLOSE_UP_FACE_POS_X;
    float sceneCentreY = CLOSE_UP_FACE_POS_Y;
    float sceneCentreW = CLOSE_UP_FACE_SIZE_X;
    float sceneCentreH = CLOSE_UP_FACE_SIZE_Y;
    
    if(_currentPlayScene==2)
    {
        
        sceneCentreX = ALIEN_CLOSE_FACE_POS_X;
        sceneCentreY = ALIEN_CLOSE_FACE_POS_Y;
        sceneCentreW = ALIEN_CLOSE_FACE_SIZE_X;
        sceneCentreH = ALIEN_CLOSE_FACE_SIZE_Y;
    }
    
    
    ofPoint faceCentre = faceBoundingBox.getCenter();
    
    
   
    
    float faceCentreDiffY = sceneCentreY-25.0f-faceCentre.y;
    float faceCentreDiffX = sceneCentreX-faceCentre.x;
    
    ofRectangle faceBounds;
    if(_needsTracking && faceBoundingBox.width>0)
    {
        ofPoint faceCentre = faceBoundingBox.getCenter();
        
        float faceCentreDiffY = sceneCentreY-faceCentre.y;
        float faceCentreDiffX = sceneCentreX-faceCentre.x;
        
        float faceSizeDiff = sceneCentreW / faceBoundingBox.width;
        
        float w = faceSizeDiff * (float)sceneCentreW;
        float h = faceSizeDiff * (float)sceneCentreH;
        
        float xPos = (BOOTH_SCREEN_SIZE_X/2) - w/2 + faceCentreDiffX;
        float yPos = (BOOTH_SCREEN_SIZE_Y/2) - h/2 + faceCentreDiffY;
        
        ofRectangle faceBounds;
        
        float currentMult = 0.15f;
        float prevMult = 1.0f - currentMult;
        
        if(_lastBounds.x != 0 && _lastBounds.y!=0)
        {
            faceBounds = ofRectangle(xPos* currentMult + _lastBounds.x*prevMult,yPos * currentMult + _lastBounds.y * prevMult,w * currentMult + _lastBounds.width * prevMult,h * currentMult + _lastBounds.height*prevMult );
            
        }else
        {
            faceBounds = ofRectangle(xPos,yPos,w,h);
        }
        
        //webCamImg += 50.0f;
        webCamImg.draw(faceBounds.x,faceBounds.y,faceBounds.width,faceBounds.height);
        
        _lastBounds.x = faceBounds.x;
        _lastBounds.y = faceBounds.y;
        _lastBounds.width=faceBounds.width;
        _lastBounds.height=faceBounds.height;
    }
    int lastPlayScene = _currentPlayScene;
    
    _currentPlayScene=isShowBoothOnProjector();
    if(_currentPlayScene != lastPlayScene)
    {
        
        _lastBounds.x=0;
        _lastBounds.y=0;
        _lastBounds.width=0;
        _lastBounds.height=0;
    }
    printf("current Play scene: %i\n",_currentPlayScene);
    switch(_currentPlayScene)
    {
        case 2:
            ofSetColor(0,255,0);
            ofRect(0,0,1000,800);
            ofSetColor(255,255,255);
             _alienHeadVid.draw(BOOTH_SCREEN_POS_X,0,BOOTH_SCREEN_SIZE_X,BOOTH_SCREEN_SIZE_Y);
            break;
        default:
            
            _helmetOverlayImg.draw(BOOTH_SCREEN_POS_X,0,BOOTH_SCREEN_SIZE_X,BOOTH_SCREEN_SIZE_Y);
        
             
           
            break;
            
    }
    
   
    
    fboBuffer.end();
    
    
    ofSetColor(255,255,255);
    fboBuffer.draw(BOOTH_SCREEN_POS_X,0,BOOTH_SCREEN_SIZE_X,BOOTH_SCREEN_SIZE_Y);
    
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
        _mainVideo.draw(BOOTH_PREVIEW_WINDOW_POS_X,BOOTH_PREVIEW_WINDOW_POS_Y,BOOTH_PREVIEW_WINDOW_SIZE_X,BOOTH_PREVIEW_WINDOW_SIZE_Y);
    }
    
    drawEmotionGuideLineText();
    
}

void SceneAliens::drawEmotionGuideLineText()
{
    int indx=0;
    
    for(int i = 0; i < _emotionGuideList.size() ;i++)
    {
        CutSceneTime * cutSceneTime = _emotionGuideList[i];
        
        if(cutSceneTime->isWithIn(_mainVideo.getPosition()))
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
        case 3:
            _font.drawString(TEXT4,EMOTION_GUIDELINES_TEXT4_POS_X,EMOTION_GUIDELINES_TEXT4_POS_Y);
            break;
    }
}
void SceneAliens::drawProjector()
{
    if(isShowBoothOnProjector() >=0)
        fboBuffer.draw(PROJECTOR_SCREEN_POS_X,0,PROJECTOR_SCREEN_SIZE_X,PROJECTOR_SCREEN_SIZE_Y);
    else
        _mainVideo.draw(PROJECTOR_SCREEN_POS_X,0,PROJECTOR_SCREEN_SIZE_X,PROJECTOR_SCREEN_SIZE_Y);
    
}

int SceneAliens::isShowBoothOnProjector()
{
    int indx=-1;
    for(int i = 0; i < _cutSceneTimesList.size();i++)
    {
        CutSceneTime * cutSceneTime = _cutSceneTimesList[i];
        
        if(cutSceneTime->isWithIn(_mainVideo.getPosition() ))
            indx=i;
    }
    return indx;
}



void SceneAliens::setGreenScreenVals(int r,int g, int b)
{
    
}
bool SceneAliens::isFinished()
{
    if(_mainVideo.getPosition()>0.99f)
        return true;
    else
        return false;
        
  //  return !_mainVideo.isPlaying();
}
