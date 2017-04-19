//
//  ofxFboPreview.cpp
//  ArbutusLite
//
//  Created by Daniel Almeida on 08/04/17.
//
//

#include "ofxFboPreview.hpp"
#include "ofMain.h"


ofxFboPreview::ofxFboPreview()
{
    fbo = NULL;
}


ofxFboPreview::~ofxFboPreview()
{
}


void
ofxFboPreview::generateDraw()
{
    bg.clear();
    bg.setFillColor(thisBackgroundColor);
    bg.rectangle(b);
    
    
}

bool
ofxFboPreview::mouseMoved(ofMouseEventArgs & args)
{
}


bool
ofxFboPreview::mousePressed(ofMouseEventArgs & args)
{
}


bool
ofxFboPreview::mouseDragged(ofMouseEventArgs & args)
{
}



bool
ofxFboPreview::mouseReleased(ofMouseEventArgs & args)
{
}


/*
bool
ofxFboPreview::mouseScrolled(ofMouseEventArgs & args)
{
}
 */

ofAbstractParameter &
ofxFboPreview::getParameter() {
    return value;
}

void
ofxFboPreview::render(){
    bg.draw();
    fg.draw();
    
    ofColor c = ofGetStyle().color;
    ofBlendMode blendMode = ofGetStyle().blendingMode;
    if(blendMode!=OF_BLENDMODE_ALPHA){
        ofEnableAlphaBlending();
    }
    ofSetColor(thisTextColor);
    
    if  (fbo != NULL && fbo->isAllocated()) {
        fbo->draw(b.x,
                  b.y,
                  b.width,
                  b.height);

    }
    
    
    
   
    
    bindFontTexture();
    textMesh.draw();
    unbindFontTexture();
    
    ofSetColor(c);
    if(blendMode!=OF_BLENDMODE_ALPHA){
        ofEnableBlendMode(blendMode);
    }
}

bool
ofxFboPreview::setValue(float mx, float my, bool bCheck) {
    
}

ofxFboPreview*
ofxFboPreview::setup(
                     ofFbo *_fbo,
                     float width
                     )
{
    fbo = _fbo;
    b.x = 0;
    b.y = 0;
    b.width = width;
    b.height = width * 3.0 / 4.0;
        
    
    return this;
}
