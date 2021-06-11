#include "Input.h"

namespace dubu::input {

Input::Input(dubu::window::IWindow& window) {
	Subscribe<dubu::window::EventKeyPress>(
	    [&](const auto& e) { mInputPressed.push_back(e.key); }, window);
	Subscribe<dubu::window::EventMouseButtonPress>(
	    [&](const auto& e) { mInputPressed.push_back(e.button); }, window);
}

void Input::Update(dubu::window::IWindow& window) {
	UpdateGamepadStates(window);

	for (auto& key : mInputPressed) {
		if (auto it = mInputActions.find(key); it != mInputActions.end()) {
			Emit(it->second);
		}
	}
	mInputPressed.clear();
}

void Input::UpdateGamepadStates(dubu::window::IWindow& window) {
	for (uint8_t gamepadIndex = 0; gamepadIndex < mPreviousGamepadState.size();
	     ++gamepadIndex) {
		if (auto gps = window.GetGamepadState(gamepadIndex); gps) {
			const auto& pgps = mPreviousGamepadState[gamepadIndex];

			for (uint8_t buttonIndex = 0;
			     buttonIndex <= dubu::window::GamepadButtonLast;
			     ++buttonIndex) {
				if (pgps.buttons[buttonIndex] ==
				        dubu::window::Action::Release &&
				    gps->buttons[buttonIndex] == dubu::window::Action::Press) {
					mInputPressed.push_back(GamepadInput{
					    .index  = gamepadIndex,
					    .button = static_cast<GamepadButton>(buttonIndex)});
				}
			}

			mPreviousGamepadState[gamepadIndex] = *gps;
		}
	}
}

}  // namespace dubu::input