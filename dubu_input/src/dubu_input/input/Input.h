#pragma once

namespace dubu::input {

using Key           = dubu::window::Key;
using MouseButton   = dubu::window::MouseButton;
using GamepadButton = dubu::window::GamepadButton;

struct GamepadInput {
	uint8_t       index;
	GamepadButton button;

	bool operator<(const GamepadInput& rhs) const {
		if (index == rhs.index) {
			return button < rhs.button;
		}
		return index < rhs.index;
	}
};

using UserAction = uint32_t;
using InputType  = std::variant<Key, MouseButton, GamepadInput>;

class Input : public dubu::event::EventSubscriber,
              public dubu::event::EventEmitter {
public:
	Input(dubu::window::IWindow& window);

	template <typename... InputMapping>
	void MapAction(UserAction action, InputMapping&&... inputMappings) {
		((mInputActions[inputMappings] = action), ...);
	}

	void Update(dubu::window::IWindow& window);

private:
	void UpdateGamepadStates(dubu::window::IWindow& window);

	std::vector<dubu::window::Key> mKeysPressed;

	std::vector<InputType>          mInputPressed;
	std::map<InputType, UserAction> mInputActions;

	std::array<dubu::window::GamepadState, 16> mPreviousGamepadState;
};

}  // namespace dubu::input