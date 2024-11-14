#ifndef COORDINATE_CONVERTER_H
#define COORDINATE_CONVERTER_H

struct PolarCoordinate {
    double r;
    double theta; // in radians
};

struct RectangularCoordinate {
    double x;
    double y;
};

class CoordinateConverter {
public:
    RectangularCoordinate polarToRectangular(const PolarCoordinate& polar);
    PolarCoordinate rectangularToPolar(const RectangularCoordinate& rect);
    
    // Angle conversion
    double degreesToRadians(double degrees);
    double radiansToDegrees(double radians);
};

#endif 