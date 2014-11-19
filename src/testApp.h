#pragma once

#define OF_VIDEO_PLAYER_QUICKTIME
#include "ofMain.h"
#include "ofxGui.h"

#include "ofxOpenCv.h"
#include "SceneMetropolis.h"
#include "ForbiddenPlanet.h"
#include "FilmScene.h"
#include "SceneFlashGordon.h"
#include "SceneAliens.h"
#include "TitleScreens.h"
#include "ofxGui.h"
#include "ofxSyphon.h"

//#define _USE_LIVE_VIDEO		// uncomment this to use a live camera
								// otherwise, we'll use a movie file

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		
        void displayFPSCounter();
    
    void selectScene(int sceneNum);
    
		  ofVideoGrabber 		vidGrabber;

        ofxCvColorImage			colorImg;

        ofxCvGrayscaleImage 	grayImage;

        ofxCvContourFinder 	contourFinder;

		int 				threshold;
		bool				bLearnBakground;
    bool _showWebcamImg;
    FilmScene * _scene;
    bool displayTitle;
    ofRectangle faceBoundingBox;
    ofxCvHaarFinder faceFinder;
    bool drawnOnce;
    bool _fullscreen;
    bool _showFPS;
    int _currentScene;
    TitleScreens titleScreens;
    bool _showUI;
	ofxPanel _gui;
	ofxFloatSlider _redThreshSlider;
	ofxFloatSlider _greenThreshSlider;
	ofxFloatSlider _blueThreshSlider;
	ofxSyphonServer mainOutputSyphonServer;
};

