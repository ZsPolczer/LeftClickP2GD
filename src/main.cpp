#include <Geode/Geode.hpp>
#include <Geode/binding/GJBaseGameLayer.hpp>
#include <Geode/binding/PlayLayer.hpp>
#include <Geode/binding/PlayerObject.hpp>
#include <Geode/utils/Keyboard.hpp>

using namespace geode::prelude;

/**
 * Geode already hooks raw mouse input on Windows and dispatches a
 * MouseInputEvent for every mouse button press / release. If a listener
 * returns ListenerResult::Stop for the left button, the loader will *not*
 * forward that click to the game's normal touch handling, which is what
 * normally makes Player 1 jump.
 *
 * So we simply:
 *   1. listen for left mouse button events,
 *   2. feed them into the exact same input path the game uses for Player 2
 *      (GJBaseGameLayer::handleButton with isPlayer1 = false), and
 *   3. optionally swallow the event so Player 1 does not also jump.
 */
$on_mod(Loaded) {
    MouseInputEvent().listen([](MouseInputData& data) -> ListenerResult {
        // We only care about the left mouse button.
        if (data.button != MouseInputData::Button::Left) {
            return ListenerResult::Propagate;
        }

        // Master switch.
        if (!Mod::get()->getSettingValue<bool>("enabled")) {
            return ListenerResult::Propagate;
        }

        // Only act while a level is actively being played (not paused).
        auto playLayer = PlayLayer::get();
        if (!playLayer || playLayer->m_isPaused) {
            return ListenerResult::Propagate;
        }

        // Player 2 only exists in two-player mode.
        if (!playLayer->m_level || !playLayer->m_level->m_twoPlayerMode) {
            return ListenerResult::Propagate;
        }
        if (!playLayer->m_player2) {
            return ListenerResult::Propagate;
        }

        const bool isPress = data.action == MouseInputData::Action::Press;

        // Route the click through the vanilla Player 2 input path so that
        // jumping, click counters, effects and replays all behave normally.
        playLayer->handleButton(isPress, static_cast<int>(PlayerButton::Jump), false);

        // In "exclusive" mode we stop the event so the click is not also
        // forwarded to Player 1. Otherwise let it propagate (both jump).
        if (Mod::get()->getSettingValue<bool>("exclusive")) {
            return ListenerResult::Stop;
        }
        return ListenerResult::Propagate;
    }).leak();

    log::info("Left Click Player 2 loaded");
}
