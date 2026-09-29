# Left Click Player 2

Bind **Player 2's jump** to a **mouse button** (left by default) in Geometry Dash
two-player mode.

## Why

Vanilla Geometry Dash only lets you bind keyboard keys to Player 2. There is no
way to bind a mouse button to Player 2's jump, which makes two-player mode
awkward if you want to use the mouse for the second player. This mod fixes that.

## How it works

Geode hooks raw mouse input on Windows and dispatches a `MouseInputEvent` for
every mouse button event. This mod listens for the bound mouse button and, while
you are actively playing a **two-player** level, feeds the input into the game
through `GJBaseGameLayer::queueButton(..., isPlayer2 = true)`.

That is the same function the game itself (and the official Custom Keybinds mod)
uses to drive Player 2, so jumping, click counters, effects and replays all
behave normally. Because Geode lets a listener stop the event before it reaches
the game, the mod can also prevent the click from reaching Player 1.

## Settings

* **Enabled** — master switch.
* **Bound button ONLY controls Player 2** — on by default. When enabled, the
  bound button no longer makes Player 1 jump (the button is dedicated to
  Player 2). Turn it off if you want it to make **both** players jump.
* **Bind mouse button** — click this button, then press the mouse button you
  want to use. The choice is saved in the **Mouse button** setting below it
  (0 = Left, 1 = Right, 2 = Middle, 3 = Button 4, 4 = Button 5).
* **Mouse button** — the bound mouse button (you can also set it manually).
* **Keyboard bind (optional)** — an extra key that also controls Player 2.
* **Debug logs** — prints each handled input to the Geode log.

## Notes

* Only active during gameplay in two-player mode. Menus, the editor and paused
  games are untouched.
* Windows only (Geode's raw mouse input handling is what the mod relies on).
