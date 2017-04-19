//
//  ofxFboPreview.hpp
//  ArbutusLite
//
//  Created by Daniel Almeida on 08/04/17.
//
//

#ifndef ofxFboPreview_hpp
#define ofxFboPreview_hpp

#include <stdio.h>
#include "ofParameter.h"
#include "ofxBaseGui.h"


class ofxFboPreview : public ofxBaseGui{
public:
    ofxFboPreview();
    ~ofxFboPreview();
    
    virtual bool mouseMoved(ofMouseEventArgs & args);
    virtual bool mousePressed(ofMouseEventArgs & args);
    virtual bool mouseDragged(ofMouseEventArgs & args);
    virtual bool mouseReleased(ofMouseEventArgs & args);
    virtual bool mouseScrolled(ofMouseEventArgs & args){return false;}

    template<class ListenerClass, typename ListenerMethod>
    void addListener(ListenerClass * listener, ListenerMethod method){
        value.addListener(listener,method);
    }
    
    template<class ListenerClass, typename ListenerMethod>
    void removeListener(ListenerClass * listener, ListenerMethod method){
        value.removeListener(listener,method);
    }
    
    
    
    bool operator=(bool v);
    operator const bool & ();
    
    ofAbstractParameter & getParameter();
    
    ofxFboPreview*
    setup(
          ofFbo *_fbo,
          float width = defaultWidth
          );
    
    
protected:
    std::string caption;
    ofFbo *fbo;
    
    
    void render();
    ofRectangle checkboxRect;
    ofParameter<bool> value;
    
    void generateDraw();

    ofPath bg,fg,cross;
    ofVboMesh textMesh;
    bool setValue(float mx, float my, bool bCheck);
    
};

#endif /* ofxFboPreview_hpp */
