#pragma once

#include "ofMain.h"
#include "Engine.h"
#include "Interface.hpp"
#include "ofxTCPServer.h"
#include "DataHandler.h"

class ofApp : public ofBaseApp {
    Engine engine;
    Interface interface;
    ofFpsCounter fpsCounter;
    ofxTCPServer server;
    DataHandler dataHandler;
    
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    static ofApp* instance();
    static void handleGUIAction(const void * sender, float & value);
    
    void handleAction(string parameter, float newValue);
    
    void startServer(unsigned int port);
    
    
    
private:

    /*!
     */
    void
    changeLayer(unsigned int layer);
};
