#pragma once

#include <Windows.h>
#include <thread>

class MouseInterpolates
{
public:
	MouseInterpolates() = default;
	~MouseInterpolates() = default;

	void StartouseInterpolate(int value, POINT& start, POINT& control, POINT& end, double& time);
static POINT BezierInterpolate(const POINT& start, const POINT& control, const POINT& end, const double t);

protected:

private:
};
