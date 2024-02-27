#include "shapes.h"

bool is_inside(const point& p, const rectangle& r) {

    if ( ((p.x < r.origin.x) || (p.x > (r.origin.x + r.width))) || ( (p.y < r.origin.y) || (p.y > (r.origin.y + r.height))) ) {
        return false;
    }
    return true;

}
