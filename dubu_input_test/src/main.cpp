#include <iostream>

#include <dubu_input/dubu_input.h>

using namespace dubu::input;

enum Actions {
	Jump1,
};

int main() {
	auto  window = dubu::window::GLFWWindow(400, 400, "dubu-input");
	Input input(window);

	input.MapAction(Actions::Jump1,
	                Key::KeySpace,
	                GamepadInput{0, GamepadButton::GamepadButtonCross});

	auto actionToken =
	    input.RegisterListener<UserAction>([&](const auto& action) {
		    switch (action) {
		    case Actions::Jump1:
			    std::cout << "Player 1: Jumping..." << std::endl;
			    break;
		    }
	    });

	while (!window.ShouldClose()) {
		window.PollEvents();

		input.Update(window);
	}
}
