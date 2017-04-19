//
//  InterfaceBlock.hpp
//  ArbutusLite
//
//  Created by Daniel Almeida on 13/03/17.
//
//

#ifndef InterfaceBlock_hpp
#define InterfaceBlock_hpp

#include <stdio.h>
#include "json.hpp"
#include "ofxGui.h"

using json = nlohmann::json;

class InterfaceBlock {
    json _data;
    ofxPanel panel;
    
public:

    
    /*!
     */
    InterfaceBlock(
                   json data,
                   unsigned int x = 0,
                   unsigned int y = 0
                   );

    
    /*!
     */
    ~InterfaceBlock();
  
    
    /*!
     */
    void draw();
    
    
private:
    /*!
     */
    void setup(
               json         data,
               ofxGuiGroup   *parent = NULL
    );
    
    
    /*!
     */
    void
    addLabel(
             std::string caption,
             ofxGuiGroup *parent
    );

    /*!
     */
    void
    addButton(
                   std::string caption,
                   ofxGuiGroup    *parent = NULL
                   );

    
    
    /*!
     */
    void addSlider(
                   std::string caption,
                   float minVal,
                   float maxVal,
                   float val,
                   ofxGuiGroup    *parent = NULL
                   );

    
    /*!
     */
    void addRGB(
                   std::string caption,
                   ofxGuiGroup    *parent = NULL
                   );

    
    /*!
     */
    void addGroup(
                  json children,
                  string      label = "",
                  ofxGuiGroup    *parent = NULL
    );
    
    /*!
     */
    void
    addPreview(
             ofFbo *_fbo,
             ofxGuiGroup *parent
               );

   // void setup(json data);
    
    void
    handleAction(
                 const void * sender,
                 float & value
                 );
    
    
    string
    getSenderPath(const void * sender);

};

#endif /* InterfaceBlock_hpp */
