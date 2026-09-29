# Left Click Player 2

Bind Player 2's jump to the left mouse button in Geometry Dash two-player mode.

## Features

* Left mouse button triggers Player 2's jump in two-player mode.
* Optional "exclusive" mode that stops the click from also triggering Player 1.
* Works through Geometry Dash's normal input path, so click counters, effects
  and replay recording behave as expected.

## Building

Requires the [Geode SDK](https://github.com/geode-sdk/geode) and the
[Geode CLI](https://github.com/geode-sdk/cli).

```sh
geode build
```

The compiled `.geode` file is placed in the `build/` directory. Copy it into
your Geometry Dash `geode/mods` folder, or run `geode package install` to have
the CLI do it for you.

## Usage

1. Enable the mod (it is on by default).
2. Start a level that has **two-player mode** enabled.
3. Left mouse click now controls Player 2's jump.

If you want left click to control both players, disable the
**"Left click ONLY controls Player 2"** setting.
