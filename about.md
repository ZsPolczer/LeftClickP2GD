# Left Click Player 2

Bind **Player 2's jump** to the **left mouse button** in Geometry Dash
two-player mode.

## Why

Vanilla Geometry Dash only lets you bind keyboard keys to Player 2. There is no
way to bind a mouse button to Player 2's jump, which makes two-player mode
awkward if you want to use the mouse for the second player. This mod fixes that.

## How it works

Geode hooks raw mouse input on Windows and dispatches a `MouseInputEvent` for
every mouse button event. This mod listens for **left mouse button** events and,
while you are actively playing a **two-player** level, feeds them into the exact
same input path the game uses for Player 2
(`GJBaseGameLayer::handleButton(..., isPlayer1 = false)`).

Because Geode lets a listener stop the event before it reaches the game, the mod
can also prevent the click from reaching Player 1.

## Settings

* **Enabled** — master switch.
* **Left click ONLY controls Player 2** — on by default. When enabled, left
  click no longer makes Player 1 jump (the mouse is dedicated to Player 2).
  Turn it off if you want left click to make **both** players jump.

## Notes

* Only active during gameplay in two-player mode. Menus, the editor and paused
  games are untouched.
* Windows only (Geode's raw mouse input handling is what the mod relies on).
