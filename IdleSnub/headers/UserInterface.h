#pragma once

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/component_base.hpp>
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
	int _screenHieght{ 0 };		//Screen Height
	bool is_running{ true };	// Toggle state



	//Vectorfor horizonta Tabs

	std::vector<std::string> _tabNames{"Main", "Setting", "About"};
	std::vector<std::string> _tab1Values{ "Forest", "Water", "I don't know", };



	int _tabSelected	{ 0 }; 
	int _tabSelteced1	{ 0 };
	int _tabSelteced2	{ 0 };
	int _tabSelteced3	{ 0 };
};



