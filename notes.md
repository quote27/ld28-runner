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


organization
====================
as much as i'd like to use opengl, use sdl's blit feature to do 2d drawing
but handle transformations and such in code
use box2d library to do collisions and movement - box2d seems a bit bigger than initially expected, so will just write something simple 
sdlinput to handle input - use 'z' as action key for now
  add ability to customize button

file / class structure idea
----------
- main.cpp: initialization and starts program
x - renderer.h: abstraction for renderer - 2d program so pass window & draw coordinates [game needs to translate from world to screen]
x   - sdlrenderer.{cpp,h}: implementation of above
- resource.h: abstraction for resource loader - loads files and holds references to data in memory
  - sdlresource.{cpp,h}: implementation of above
- game.{cpp,h}: game logic - main loop [update and all]
- obj: abstraction for game object - has x/y info and resource id
  - map/tile: map contains world map for runner, tile contains floor and ceiling information
  - player: the character that's moving [initially a box]
- vec.{cpp,h}: 2d vector library
