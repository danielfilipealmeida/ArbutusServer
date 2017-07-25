//
//  DataHandler.hpp
//  ArbutusServer
//
//  Created by Daniel Almeida on 22/07/17.
//
//

#ifndef DataHandler_hpp
#define DataHandler_hpp

#include <stdio.h>
#include "Engine.h"
#include "json.hpp"
using json = nlohmann::json;

/**!
 @abstract Implements the handling of the requests to the server
 */
class DataHandler {
public:
    DataHandler();
    ~DataHandler();
    
    /**!
     @abstract process the json sent on a request to the server
     */
    json handleRequest(json requestJson);
    
    
    /**!
     @abstract process a `getState` request
     */
    json getStateResponse();
    
};


#endif /* DataHandler_hpp */
