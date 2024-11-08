#include "shapes.h"

bool overlap(const rectangle& r1, const rectangle& r2) {

    if ( ((r2.origin.x >= r1.origin.x ) && (r2.origin.x <= (r1.origin.x + r1.width))) && ( (r2.origin.y >= r1.origin.y) && (r2.origin.y <= (r1.origin.y + r1.height)))) {
        return true;
    } else if ( ((r2.origin.x >= r1.origin.x ) && (r2.origin.x <= (r1.origin.x + r1.width))) && ( (((r2.origin.y -r2.height) < r1.origin.y) && ((r2.origin.y -r2.height) > (r1.origin.y - r1.height))) )) {
        return true;
    } else if (  ( ((r2.origin.x + r2.width) >= r1.origin.x ) && ((r2.origin.x + r2.width) <= (r1.origin.x + r1.width))) && ( (r2.origin.y >= r1.origin.y) && (r2.origin.y <= (r1.origin.y + r1.height))) ) {
        return true;
    } else if ( (((r2.origin.x +r2.width) >= r1.origin.x ) && ( (r2.origin.x  + r2.width) <= (r1.origin.x + r1.width))) && ( (((r2.origin.y -r2.height) < r1.origin.y) && ((r2.origin.y -r2.height) > (r1.origin.y - r1.height))) )) {
    }

    

    return false;

}

