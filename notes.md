ludum dare 48

theme: "you only have one"

idea
====================
"you only have one... button"

kinda like the 'press space to continue' game
you can do different timings of button presses to do different actions

take a runner game, possibilities:
- taphold = slide
- tap = jump
  - +tap = double jump
  - +taphold = hover

things needed
====================
input
- manage different timings of presses
- figure out best way to differentiate between tap and taphold

graphics
- pretty simple, start off with box for character and lines for world
- add pixel art later
- add animations [can do without pixel art too]

levels
- build in some
- add procedural generation

framework
- kinda want to use glfw as its new, but emscripten doesnt support it yet
- use sdl to handle events

audio
- use sdl audio too
- maybe bit trip runner themed?




