#include"../headers/MouseInterpolates.h"


/***
*   Helper function to interpolate along a quadratic B�zier curve
*  https://en.wikipedia.org/wiki/B%C3%A9zier_curve
*
**/

void MouseInterpolates::StartouseInterpolate(int value, POINT& start, POINT& control, POINT& end, double& time) {



}

POINT MouseInterpolates::BezierInterpolate (const POINT& start, const POINT& control, const POINT& end, const double t) {
    // Result will store the interpolated point
    POINT result;

    // Calculate common terms for the B�zier formula
    // t is the interpolation parameter that goes from 0 to 1
    // oneMinusT is (1-t), used in the Bezier formula
    const double _oneMinusT = 1.0 - t;
    // oneMinusTSquared is (1-t)^2, the quadratic term for the start point
    const double _oneMinusTSquared = _oneMinusT * _oneMinusT;
    // tSquared is t^2, the quadratic term for the end point
    const double _tSquared = t * t;

    // Calculate x coordinate using quadratic Bezier formula:
    // B(t) = (1-t)^2 * P0 + 2(1-t)t * P1 + t^2 * P2
    // where P0 is start point, P1 is control point, P2 is end point
    result.x = static_cast<LONG>(
        _oneMinusTSquared * start.x +     // First term: weight of start point
        2 * _oneMinusT * t * control.x +   // Second term: weight of control point
        _tSquared * end.x                 // Third term: weight of end point
        );

    // Calculate y coordinate using the same formula
    result.y = static_cast<LONG>(
        _oneMinusTSquared * start.y +     // First term: weight of start point
        2 * _oneMinusT * t * control.y +  // Second term: weight of control point
        _tSquared * end.y                 // Third term: weight of end point
        );

    return result;
}