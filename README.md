![Windows](https://github.com/Husenap/dubu-input/workflows/Windows/badge.svg)
![Ubuntu](https://github.com/Husenap/dubu-input/workflows/Ubuntu/badge.svg)

```
   _     _           _             _   
 _| |_ _| |_ _ _ ___|_|___ ___ _ _| |_ 
| . | | | . | | |___| |   | . | | |  _|
|___|___|___|___|   |_|_|_|  _|___|_|  
                          |_|          
```

C++ input library depending on [dubu-window](https://github.com/Husenap/dubu-window).

# Features

* Map an arbitrary amount of keys/buttons to user actions
* Register a listener to user action events

# Examples

##### **`Simple input mapping`**
```cpp
#include <iostream>

#include <dubu_input/dubu_input.h>

using namespace dubu::input;

enum Actions {
    Jump1,
};

int main() {
    auto  window = dubu::window::GLFWWindow(400, 400, "dubu-input");
    Input input(window);

    // You can map action keys separately
    input.MapAction(Actions::Jump1, Key::KeySpace);
    input.MapAction(Actions::Jump1, GamepadInput{0, GamepadButton::GamepadButtonA});

    // Or you can map an arbitrary amount of keys in the same `MapAction(...)` function call
    input.MapAction(Actions::Jump1,
                    Key::KeySpace,
                    GamepadInput{0, GamepadButton::GamepadButtonA});

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
```