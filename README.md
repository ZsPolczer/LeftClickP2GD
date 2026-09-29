# Left Click Player 2

Bind Player 2's jump to the left mouse button (or any other mouse button / key)
in Geometry Dash two-player mode.

## Features

* A configurable mouse button triggers Player 2's jump in two-player mode
  (left mouse by default).
* "Press to bind" button in the mod settings — click it, then press the mouse
  button you want.
* Optional "exclusive" mode that stops the button from also triggering Player 1.
* Optional keyboard bind.
* Uses Geometry Dash's own input queue, so click counters, effects and replay
  recording behave as expected.

## Building

Requires the [Geode SDK](https://github.com/geode-sdk/geode) and the
[Geode CLI](https://github.com/geode-sdk/cli).

```sh
geode build
```

The compiled `.geode` file is placed in the `build/` directory. The build also
installs it into your Geometry Dash `geode/mods` folder automatically when a
profile is configured.

## Usage

1. Enable the mod (on by default).
2. Open the mod's settings and press **Bind mouse button**, then press the mouse
   button you want to use for Player 2.
3. Start a level with **two-player mode** enabled.
4. The bound mouse button now controls Player 2's jump.

If you want the bound button to control both players, disable
**"Bound button ONLY controls Player 2"**.
