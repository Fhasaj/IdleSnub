#include"../headers/UserInterface.h"

UserInterface::UserInterface() {
	UserInterface::DrawUI();
}
//int UserInterface::DrawUI() {
//
//	//auto screen = ftxui::ScreenInteractive::TerminalOutput();
//
//	//std::string button_label = "Start";	// Button label
//
//	//// Function to be toggled
//	//auto toggle_action = [&] {
//	//	is_running = !is_running;
//	//	if (is_running) {
//	//		button_label = "Stop";
//	//		UserInterface::StartMovingMouse();
//	//	}
//	//	else {
//	//		button_label = "Start";
//	//		is_running = false;
//	//	}
//	//	screen.PostEvent(ftxui::Event::Custom); // Force UI update
//	//	};
//
//	//// Button component
//	//auto button = ftxui::Button(&button_label, toggle_action, ftxui::ButtonOption::Animated(ftxui::Color::Blend(ftxui::Color::Aquamarine1, ftxui::Color::Aquamarine3)));
//
//
//	//Tabs
//	//auto tabs = ftxui::Tab(&_tabSelected, _tabNames, ftxui::TabOption::Animated());
//
//
//
//	// Layout components vertically
//	//auto container = ftxui::Container::Vertical({
//	//	button
//	//	});
//
//	//// Custom rendering of the UI
//	//auto renderer = ftxui::Renderer(container, [&] {
//	//	return ftxui::vbox({
//	//		ftxui::text("Mouse Mover") | ftxui::bold,
//	//		ftxui::paragraph("A simple program that randomly moves the mouse cursor to a new position on the screen every second.\nClick on the start button to begin"),
//	//		button->Render(),
//	//		})		
//	//		| ftxui::border | ftxui::flex;
//	//	});
//
//	//screen.Loop(renderer);
//
//
//
//
//	//TESTING
//
//	using namespace ftxui;
//
//	auto tab_toggle = Toggle(
//		&_tabNames,		// The acttual tab values Names
//		&_tabSelected	// referance to the tab that is selected
//	);
//
//	// The is the values of each tab
//	auto tab_container = Container::Tab(
//		{
//			Radiobox(&_tab1Values, &_tabSelteced1),
//			Renderer([] {
//				return vbox({
//					text("About Mouse Mover") | bold,
//					paragraph("A simple program that randomly moves the mouse cursor to a new position on the screen every second.\nClick on the start button to begin")
//						| color(Color::White)
//				}),
//			Renderer([] {
//				return vbox({
//					text("About Mouse Mover") | bold,
//					paragraph("A simple program that randomly moves the mouse cursor to a new position on the screen every second.\nClick on the start button to begin")
//						| color(Color::White)
//				});
//			})
//		},
//		&_tabSelected);
//
//	// Layout components vertically
//	auto container = Container::Vertical({
//		tab_toggle,
//		tab_container,
//		});
//
//	//
//	auto renderer = Renderer(container, [&] {
//		return vbox({
//				   tab_toggle->Render(),
//				   separator(),
//				   tab_container->Render(),
//			}) |
//			border;
//		});
//
//	auto screen = ScreenInteractive::TerminalOutput();
//	screen.Loop(renderer);
//
//	return EXIT_SUCCESS;
//}


//Might need to move this to another file not sure if it makes sense here
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


int UserInterface::DrawUI() {
    using namespace ftxui;

    // Tab 1: Text and Button
     std::string button_label = "Start";	// Button label
    // Function to be toggled
    auto toggle_action = [&] {
    	is_running = !is_running;
    	if (is_running) {
    		button_label = "Stop";
            ftxui::ButtonOption::Animated(ftxui::Color::Blend(ftxui::Color::Red3, ftxui::Color::Red3Bis));

    		UserInterface::StartMovingMouse();
    	}
    	else {
    	button_label = "Start";
        ftxui::ButtonOption::Animated(ftxui::Color::Blend(ftxui::Color::Aquamarine1, ftxui::Color::Aquamarine3));
    	is_running = false;
    }
   // screen.PostEvent(ftxui::Event::Custom); // Force UI update
    	};
    
    // Button component
    auto button = ftxui::Button(&button_label, toggle_action);


    auto tab1_renderer = Renderer([&] {
        return vbox({
            text("Welcome to Mouse Mover!") | bold,
            button->Render()
        });
    });

    // Tab 2: Radio buttons, checkboxes, and textbox
    std::vector<std::string> radio_options = { "Option 1", "Option 2", "Option 3" };
    int radio_selected = 0;
    auto radio = Radiobox(&radio_options, &radio_selected);

    std::vector<std::string> checkbox_labels = { "Enable feature A", "Enable feature B" };
    std::vector<bool> checkbox_states(checkbox_labels.size(), false);
    std::vector<Component> checkboxes;
//    for (size_t i = 0; i < checkbox_labels.size(); ++i) {
//        checkboxes.push_back(Checkbox(&checkbox_labels[i], &checkbox_states[i]));
//    }
    auto checkbox_container = Container::Vertical(checkboxes);

    std::string textbox_content;
    auto textbox = Input(&textbox_content, "Enter text...");

    auto tab2_container = Container::Vertical({
        radio,
        checkbox_container,
        textbox
    });
    auto tab2_renderer = Renderer(tab2_container, [&] {
        Elements elements = {
            text("Settings") | bold,
            separator(),
            text("Choose an option:"),
            radio->Render(),
            separator(),
            text("Features:"),
            checkbox_container->Render(),
            separator(),
            text("Input:"),
            textbox->Render()
        };
        return vbox(std::move(elements));
    });

    // Tab 3: About paragraph
    auto tab3_renderer = Renderer([] {
        return vbox({
            text("About Mouse Mover") | bold,
            paragraph("A simple program that randomly moves the mouse cursor to a new position on the screen every second.\nClick on the start button to begin")
                | color(Color::White)
        });
    });

    // Tab toggle and tab container
    auto tab_toggle = Toggle(&_tabNames, &_tabSelected);
    auto tab_container = Container::Tab({
        tab1_renderer,
        tab2_renderer,
        tab3_renderer
    }, &_tabSelected);

    auto container = Container::Vertical({
        tab_toggle,
        tab_container
    });

    auto renderer = Renderer(container, [&] {
        return vbox({
            tab_toggle->Render(),
            separator(),
            tab_container->Render()
        }) | border;
    });

    auto screen = ScreenInteractive::TerminalOutput();
    screen.Loop(renderer);

    return EXIT_SUCCESS;
}
