ld28-runner
====================

This is my [Ludum Dare 28](http://www.ludumdare.com/compo/ludum-dare-28/) prototype.

Goals
----------
My main goal for this project was to make a fair amount of progress towards a working game. In the
past, I would get stuck in 'planning' mode, and never really make any progress. With that in mind, I
chose to ignore deep planning and try to get to a playable state as fast as possible. To help with
this, I decided to just use SDL and draw lines and boxes. SDL also helped as it handles window
management and is supported by emscripten.

Another goal I had was to experiment with [emscripten](https://github.com/kripken/emscripten).
Emscripten is an interesting project as it strives to reach native performance in a browser
environment. Check out Epic's Unreal Engine 3 [demo](https://www.youtube.com/watch?v=BV32Cs_CMqo)
[unfortunately it seems like the live is no longer online]. Supporting emscripten wasn't as hard as
I initially thought, the api is relatively simple, and as long as you dont do too much computation
each frame, it performs nicely.


Design
----------
My interpretation of the theme was "You only get one... button".  With this, I build a runner game
\[like [BIT.TRIP RUNNER](http://bittripgame.com/bittrip-runner.html)\] with the idea of overloading
one button to perform multiple actions \[jump, slide, etc\].

However, this concept somewhat breaks down with the following action bindings:

- tap = jump
- hold = slide

From my [fairly simple] experiments, a normal 'tap' [from key down to key up] is roughly
200 ms. Therefore, in order to make sure the player is performing a 'hold', I would need to wait
200+ms to enable that state.

The question comes down to: when do we trigger the jump?

If its on key down, then as the player performs a hold, the character would perform a jump, and
after a small bit of time, fall down to the ground and start sliding.

If its on key up, the player would encounter a small lag, as the actions occurs on release rather
then when the key is pressed down.

Towards the end of the weekend, I decided to remove the slide action for now, and just have jump and
double jump implemented. I believe a game with solid mechanics is more fun to play than one with
wonky controls designed to fit a theme.


Next steps
----------
Here's my next step plans for continuing the project:

- Add Title and Score screens
- Improve the random map algorithm
- Add sprites for the map / characters
- Possibly move slide / hover logic to a second button
