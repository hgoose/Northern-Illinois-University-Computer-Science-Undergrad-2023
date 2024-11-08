#include "vector3.h"

vector3::vector3(double  x, double y, double z ) {
    this->x = x;
    this->y = y;
    this->z = z;
}


vector3 vector3::operator+(const vector3& other) const {
    return vector3(this->x + other.x, this->y + other.y, this->z + other.z);
}
vector3 vector3::operator-(const vector3& other) const {
    return vector3(this->x - other.x, this->y - other.y, this->z - other.z);
}
double vector3::operator*(const vector3& other) const {
    return this->x * other.x + this->y * other.y + this->z * other.z;
}
vector3 vector3::operator*(double scalar) const {
    return vector3(this->x*scalar, this->y*scalar, this->z*scalar);
}

double vector3::operator[](size_t n) const {

    switch (n) {
        case 0:
            return this->x;
            break;
        case 1:
            return this->y;
            break;
        case 2:
            return this->z;
            break;
        default:
            return 0.0f;
    }
}

double& vector3::operator[](size_t n) {
    switch (n) {
        case 0:
            return this->x;
            break;
        case 1:
            return this->y;
            break;
        case 2:
            return this->z;
            break;
        default:
            return this->x;
    }
}

bool vector3::operator==(const vector3& other) const {
    return this->x == other.x && this->y == other.y && this->z == other.z;
}

std::ostream& operator<<(std::ostream& os, const vector3& obj) {

    os << "("  << obj.x << ", "  << obj.y << ", " << obj.z << ")";
    return os;

}

vector3 operator*(double s, const vector3& obj) {
    return vector3(obj.x * s, obj.y * s, obj.z * s);
}



