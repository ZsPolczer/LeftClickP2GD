#include <Geode/Geode.hpp>
#include <Geode/binding/GJBaseGameLayer.hpp>
#include <Geode/binding/PlayLayer.hpp>
#include <Geode/loader/SettingV3.hpp>
#include <Geode/ui/Notification.hpp>
#include <Geode/utils/Keyboard.hpp>

using namespace geode::prelude;

// Set while the mod is waiting for the user to press a mouse button to bind.
static bool s_capturing = false;

static char const* mouseButtonName(MouseInputData::Button button) {
    switch (button) {
        case MouseInputData::Button::Left:    return "left";
        case MouseInputData::Button::Right:   return "right";
        case MouseInputData::Button::Middle:  return "middle";
        case MouseInputData::Button::Button4: return "button 4";
        case MouseInputData::Button::Button5: return "button 5";
        default: return "unknown";
    }
}

static bool inTwoPlayerRun() {
    auto pl = PlayLayer::get();
    return pl && !pl->m_isPaused
        && pl->m_level && pl->m_level->m_twoPlayerMode
        && pl->m_player2;
}

// Feed the input into the game's own queue. This is exactly how the game
// (and the official Custom Keybinds mod) drives Player 2, so jumping,
// click counters, effects and replays all behave normally.
static void pressPlayer2(bool down, double timestamp) {
    if (!inTwoPlayerRun()) {
        return;
    }
    if (auto layer = GJBaseGameLayer::get()) {
        layer->queueButton(static_cast<int>(PlayerButton::Jump), down, true, timestamp);
        if (Mod::get()->getSettingValue<bool>("debug-logs")) {
            log::info("LC-P2 {} (player 2)", down ? "press" : "release");
        }
    }
}

$on_mod(Loaded) {
    // Optional user-bindable keyboard key.
    geode::listenForKeybindSettingPresses(
        "keyboard-bind",
        [](Keybind const&, bool down, bool repeat, double timestamp) -> ListenerResult {
            if (repeat || !Mod::get()->getSettingValue<bool>("enabled")) {
                return ListenerResult::Propagate;
            }
            pressPlayer2(down, timestamp);
            return ListenerResult::Stop;
        }
    );

    // Mouse buttons.
    MouseInputEvent().listen([](MouseInputData& data) -> ListenerResult {
        // Binding: take the next mouse button that is pressed.
        if (s_capturing) {
            if (data.action != MouseInputData::Action::Press) {
                return ListenerResult::Stop;
            }
            s_capturing = false;
            Mod::get()->setSettingValue<int64_t>(
                "mouse-button", static_cast<int64_t>(data.button)
            );
            Notification::create(
                std::string("Player 2 bound to the ") + mouseButtonName(data.button) + " mouse button",
                NotificationIcon::Success
            )->show();
            return ListenerResult::Stop;
        }

        if (!Mod::get()->getSettingValue<bool>("enabled")) {
            return ListenerResult::Propagate;
        }
        if (static_cast<int64_t>(data.button) != Mod::get()->getSettingValue<int64_t>("mouse-button")) {
            return ListenerResult::Propagate;
        }
        if (!inTwoPlayerRun()) {
            return ListenerResult::Propagate;
        }

        pressPlayer2(data.action == MouseInputData::Action::Press, data.timestamp);

        // In "exclusive" mode we stop the event so it is not also forwarded
        // to Player 1. Otherwise let it propagate (both jump).
        if (Mod::get()->getSettingValue<bool>("exclusive")) {
            return ListenerResult::Stop;
        }
        return ListenerResult::Propagate;
    }).leak();

    // The "Bind mouse button" button shown in the mod's settings.
    ButtonSettingPressedEventV3(Mod::get(), "bind-mouse").listen([](std::string_view) -> ListenerResult {
        Loader::get()->queueInMainThread([] {
            s_capturing = true;
            Notification::create(
                "Press the mouse button you want to bind for Player 2...",
                NotificationIcon::Info
            )->show();
        });
        return ListenerResult::Propagate;
    }).leak();

    log::info("Left Click Player 2 loaded");
}
