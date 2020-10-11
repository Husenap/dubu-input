#include <iostream>

#include <dubu_input/dubu_input.h>

using namespace dubu::input;

enum Actions {
	Jump1,
	Shoot1,
	Jump2,
	Shoot2,
};

int main() {
	auto window =
	    std::make_unique<dubu::window::GLFWWindow>(400, 400, "dubu-input");
	Input input(*window);

	input.MapAction(
	    Actions::Jump1,
	    Key::KeySpace,
	    GamepadInput{.index = 0, .button = GamepadButton::GamepadButtonA});
	input.MapAction(
	    Actions::Shoot1,
	    Key::KeyEnter,
	    GamepadInput{.index  = 0,
	                 .button = GamepadButton::GamepadButtonRightBumper},
	    MouseButton::MouseButtonLeft);

	input.MapAction(
	    Actions::Jump2,
	    GamepadInput{.index = 1, .button = GamepadButton::GamepadButtonA});
	input.MapAction(
	    Actions::Shoot2,
	    GamepadInput{.index  = 1,
	                 .button = GamepadButton::GamepadButtonRightBumper});

	auto actionToken =
	    input.RegisterListener<UserAction>([&](const auto& action) {
		    switch (action) {
		    case Actions::Jump1:
			    std::cout << "Player 1: Jumping..." << std::endl;
			    break;
		    case Actions::Shoot1:
			    std::cout << "Player 1: Shooting..." << std::endl;
			    break;
		    case Actions::Jump2:
			    std::cout << "Player 2: Jumping..." << std::endl;
			    break;
		    case Actions::Shoot2:
			    std::cout << "Player 2: Shooting..." << std::endl;
			    break;
		    default:
			    break;
		    }
	    });

	while (!window->ShouldClose()) {
		window->PollEvents();

		input.Update(*window);
	}
}

