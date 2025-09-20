#pragma once

#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_options.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/component/event.hpp>  // for Event
#include <iostream>
#include <memory>                  // for allocator, shared_ptr
#include <string>                  // for operator+, to_string
#include <thread>                  // for sleep_for
#include <chrono>                     // for milliseconds


#include"MouseController.h"

class UserInterface
{
public:
	UserInterface();
	~UserInterface() = default;
private:

	int DrawUI();
	void StartMovingMouse();
	//void Settings();


	
	int _screenWidth{ 0 };		            //Screen Width
	int _screenHeight{ 0 };		            //Screen Height
    int _startTimer{ 30 };                  //Used to sleep the program

	bool is_running{ true };	            // Toggle state of buton
    bool _mouseStarted {false};             // Toggle when the program is started


    std::string button_label = "Start";	    // Button label
    std::thread _timer_thread;              //

};



