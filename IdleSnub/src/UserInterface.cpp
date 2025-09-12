#include"../headers/UserInterface.h"

UserInterface::UserInterface() {UserInterface::DrawUI();}

int UserInterface::DrawUI() {

	auto screen = ftxui::ScreenInteractive::TerminalOutput();

	std::string button_label = "Start";	// Button label

	// Function to be toggled
	auto toggle_action = [&] {
		is_running = !is_running;
		if (is_running) {
			button_label = "Stop";
			UserInterface::StartMovingMouse();
		}
		else {
			button_label = "Start";
			is_running = false;
		}
		screen.PostEvent(ftxui::Event::Custom); // Force UI update
		};

	// Button component
	auto button = ftxui::Button(&button_label, toggle_action);

	// Layout components vertically
	auto container = ftxui::Container::Vertical({button});

	// Custom rendering of the UI
	auto renderer = ftxui::Renderer(container, [&] {
		return ftxui::vbox({
			ftxui::paragraphAlignCenter("Mouse Mover") | ftxui::bold,
			ftxui::paragraphAlignCenter("A simple program that randomly moves the mouse cursor to a new position on the screen every second."),
			ftxui::separator(),
			ftxui::paragraphAlignCenter("Click on the start button to begin. This will then start "),
			ftxui::separator(),
			button->Render(),
			})| ftxui::border | ftxui::flex;
	});

	screen.Loop(renderer);
	return EXIT_SUCCESS;
}


//Might need to move this to another file not sure if it make sense here
void UserInterface::StartMovingMouse() {

	_screenWidth = GetSystemMetrics(SM_CXSCREEN);
	_screenHieght = GetSystemMetrics(SM_CYSCREEN);

	std::thread([this] {
		while (is_running) {
			MouseController _mouseController; // Getting a reference to the class here
			_mouseController.MoveMouse(_screenWidth, _screenHieght);
			Sleep(18000); // Sleep for 30 second before moving the mouse again
	}
	}).detach();
}
