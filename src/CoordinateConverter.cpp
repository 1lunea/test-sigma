#include "CoordinateConverter.h"
#include <cmath>

RectangularCoordinate CoordinateConverter::polarToRectangular(const PolarCoordinate& polar) {
    return {
        polar.r * std::cos(polar.theta),
        polar.r * std::sin(polar.theta)
    };
}

PolarCoordinate CoordinateConverter::rectangularToPolar(const RectangularCoordinate& rect) {
    double r = std::sqrt(rect.x * rect.x + rect.y * rect.y);
    double theta = std::atan2(rect.y, rect.x);
    return {r, theta};
}

double CoordinateConverter::degreesToRadians(double degrees) {
    return degrees * M_PI / 180.0;
}

double CoordinateConverter::radiansToDegrees(double radians) {
    return radians * 180.0 / M_PI;
} 