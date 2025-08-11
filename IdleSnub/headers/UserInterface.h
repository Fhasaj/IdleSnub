#pragma once

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <iostream>

#include"MouseController.h"

class UserInterface
{
public:
	UserInterface();
	~UserInterface() = default;

	//void UiInit();

private:

	int DrawUI();
	void StartMovingMouse();
	//void Settings();


	
	int _screenWidth{ 0 };		//Screen Width
	int _screenHieght{ 0 };		//Screen Hight
	bool is_running{ true };	// Toggle state
};



