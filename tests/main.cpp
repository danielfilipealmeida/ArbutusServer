//
//  main.cpp
//  catch
//
//  Created by Daniel Almeida on 10/03/17.
//
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "json.hpp"
#include "interface.hpp"


using json = nlohmann::json;



TEST_CASE("String is prepend to keys of simple json"," [prependStringToKeys]") {
    json inputData = {
        {"key1", "value"},
        {"key2", 1}
    };
    
    json result = Interface::prependStringToKeys(inputData, "lorem");
    
    unsigned int count = 0;
    for (
         json::iterator it = result.begin();
         it != result.end();
         it++
         )
    {
        json::iterator it2 = inputData.begin();

        // move if needed
        for (int f=0;f<count;f++) { it2++;}

        REQUIRE(it.key().compare("lorem" + it2.key()) == 0);
        count ++;
    }
}
