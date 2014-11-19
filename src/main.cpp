#include "ofMain.h"
#include "testApp.h"
#include "global.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){

	//ofSetupOpenGL(SCREEN_WIDTH,SCREEN_HEIGHT, OF_WINDOW);			// <-------- setup the GL context
    //ofRunApp( new testApp());

    ofAppGLFWWindow win;
	//win.setNumSamples(8);
	win.setMultiDisplayFullscreen(true); //this makes the fullscreen window span across all your monitors
    
	ofSetupOpenGL(&win, SCREEN_WIDTH,SCREEN_HEIGHT, OF_FULLSCREEN);
	ofRunApp(new testApp());
}
