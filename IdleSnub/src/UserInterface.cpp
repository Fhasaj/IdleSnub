#include"../headers/UserInterface.h"

/**
 *
 */
UserInterface::UserInterface() {UserInterface::DrawUI();}

/**
 *
 * @return
 */
int UserInterface::DrawUI() {

	auto screen = ftxui::ScreenInteractive::TerminalOutput();

    // Function to be toggled
    auto toggle_action = [&] {
        is_running = !is_running;
        if (is_running) {
            button_label = "Stop";
            UserInterface::StartMovingMouse();
            _mouseStarted = true;

            if (!_timer_thread.joinable()) {
                _timer_thread = std::thread([&]() {
                    while (_mouseStarted) {
                        if (_startTimer > 0) {
                            std::this_thread::sleep_for(std::chrono::seconds(1));
                            _startTimer--;
                            screen.PostEvent(ftxui::Event::Custom);
                        }else {
                            // UserInterface::StartMovingMouse();
                            _startTimer = 30;
                            screen.PostEvent(ftxui::Event::Custom);
                        }
                    }
                });
            }
        }
        else {
            button_label = "Start";
            is_running = false;
            _mouseStarted = false;
            if (_timer_thread.joinable()) _timer_thread.join();
            _startTimer = 30;
        }

        // Force the UI to reload
        // _timer_thread.detach(); //TODO: check if I need to detach to release memory
        screen.PostEvent(ftxui::Event::Custom);
    };

    // UI components
    auto button    = ftxui::Button(&button_label, toggle_action);
    auto container = ftxui::Container::Vertical({ button });

    // Renderer (build a vector of Elements; don't call Add() on an Element)
    auto renderer = ftxui::Renderer(container, [&] {
      std::vector<ftxui::Element> lines;

      lines.push_back(ftxui::paragraphAlignCenter("Mouse Mover") | ftxui::bold);
      lines.push_back(ftxui::paragraphAlignCenter(
          "A simple program that randomly moves the mouse cursor to a new position on the screen every second."));
      lines.push_back(ftxui::separator());
      lines.push_back(ftxui::paragraphAlignCenter("Click the Start button to begin."));
      lines.push_back(ftxui::separator());

      if (_mouseStarted) {
        lines.push_back(ftxui::text("Running") | ftxui::bold);
        lines.push_back(ftxui::separator());
        lines.push_back(ftxui::text("Count down till mouse moves: " +
                                    std::to_string(_startTimer)) |
                        ftxui::bold);
      } else {
        lines.push_back(ftxui::text("Stopped") | ftxui::bold);
        lines.push_back(ftxui::separator());
      }

      lines.push_back(button->Render());

      return ftxui::vbox(std::move(lines)) | ftxui::border | ftxui::flex;
    });

    screen.Loop(renderer);

    // Ensure the timer thread is not left running if the UI exits while active.
    _mouseStarted = false;
    if (_timer_thread.joinable())
        _timer_thread.join();

    return EXIT_SUCCESS;
}


//Might need to move this to another file not sure if it makes sense here
void UserInterface::StartMovingMouse() {

	_screenWidth = GetSystemMetrics(SM_CXSCREEN);
	_screenHeight = GetSystemMetrics(SM_CYSCREEN);

	std::thread([this] {
		while (is_running ) {
			MouseController _mouseController; // Getting a reference to the class here
			_mouseController.MoveMouse(_screenWidth, _screenHeight);
			 Sleep(_startTimer * 1000); // Sleep for the start time in milliseconds
	    }
	}).detach();
}
