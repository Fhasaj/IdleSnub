#pragma once
/**
* @name: MouseController.h 
* @description: holds all the function and variables for the MouseController. The point of the MouseController is to allow for the mouse to be moved with humman
* like to a part of a screen randomly. 
* @class: MouseController
* @created: 29/07/2025 - 07:50
* @moddified: 29/07/2025 - 
*/


#include <Windows.h>
#include <stdio.h>
#include <random>
#include <cmath>    
#include <cstdlib>  
#include <algorithm> 
#include <corecrt_math_defines.h>
#include "MouseInterpolates.h"

class MouseController
{
public:
	MouseController();
	~MouseController() = default;

	//EntryPoint
	void MoveMouse(int& scrennWidth, int& screenHight); 

private:

	struct RandomPoint
	{
		int x;
		int y;
	};

	RandomPoint GetRandomMousePosition();
	static void MouseMove(const int& targetX, const int& targetY);




	int _randomScreenWidth, _randomScreenHight; 
	int scrennWidth; 
	int screenHight;

};
