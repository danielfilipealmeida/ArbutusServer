//
//  Interface.hpp
//  ArbutusLite
//
//  Created by Daniel Almeida on 13/03/17.
//
//

#ifndef Interface_hpp
#define Interface_hpp

#include <stdio.h>
#include "ofxGui.h"
#include "InterfaceBlock.hpp"
#include "Engine.h"
#include "ofxFboPreview.hpp"

typedef enum {
    UI_WIDGET_BUTTON = 1,
    UI_WIDGET_SLIDER
} UI_WIDGET;



/*!
 @abstract Handles the Graphic interface
 */
class Interface {
    //ofxPanel gui, gui2;
    
    //ofxButton newButton, newButton2;
    InterfaceBlock *menu, *layer1, *layer2;
    InterfaceBlock *layerPreviews;
    InterfaceBlock *visual;
    json menuData, layersData, visualInterfaceData;
    
public:
    /*!
     */
    Interface();
    
    
    /*!
     */
    ~Interface();
    
    
    json
    loadFromFile(string file);
    
    
    /*!
     @abstract traverse a simple json and append string to the keys
     */
    static json
    prependStringToKeys(
                       json input,
                       string appendString
                       );
    
    void
    setup();
    
    void
    reload();


    /*!
     */
    void
    draw();
    
    
private:
    
    /*!
     */
    void
    updateInterfaceBlockDataWithState(
                                      json & interfaceBlockData,
                                      json state
                                      );
};

#endif /* Interface_hpp */
