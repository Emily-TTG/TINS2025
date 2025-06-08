## TINS 2025
### 'Stuffed to the Brimstone'

### Build & Run

The game is built on top of [sPDNgin](https://github.com/Emily-TTG/sPDNgin)
which the build expects to be present at `vendor/sPDNgin`. This is a
hodge-podge of basic initialization code and a runtime loop made ahead of the
jam. It also provides some build infrastructure for dependencies used by the
project (see [final notes](#final-notes) for full 1st-order dependency list).

On Windows LuaJIT can be a bit finicky depending on toolchain - so you may
want to pre-build it in-tree at `vendor/sPDNgin/vendor/luajit`. Visual C
toolsets probably won't work without at least `clang-cl` - Windows was tested
with MinGW.

After that it's a normal cmake build process:
```
cmake -Bbuild -DCMAKE_BUILD_TYPE=Release [whatever else your heart desires...]
cmake --build build [-jN if you want it to go faster]
```

The executable can be run either from the build dir or relative to the top of
the source tree. It should be output to `build/game[.exe]`
(or `build/Release/game[.exe]` if using a multiconfig generator).

### Game

#### Flavour

*You've just finished a lovely meal at the best restaurant the town has to
offer: 'The Chips of Tartarus'. Unfortunately; on your way out you've stumbled
into the Kitchen where the cooks wont take no for an answer. No matter what
they offer - you're already **Stuffed to the Brim-stone***.

#### How to Play

Your health is your ammo! As you get hit by enemy projectiles, your "fullness"
bar will fill up - the only way to empty it is to fire back. Find the keys to
your escape around the unholy kitchen, picking up new weapons to help you along
the way.

At the end of the game - `./results.html` will contain your gameplay results -
best score gets a free (virtual) egg.

#### Controls

`W A S D`: Movement

`Q E`: Cycle weapons

`F`: Pick up item

`Cursor`: Aim

`Mouse 1`: Fire

### Rule Employment

#### Genre - Food & Nutrition

Gameplay is centred on the player's nutrition.
All weapons and projectiles are food or food-related.
All the names are food puns.
The narrative of the game is centred around food and fullness

I have tried to manifest this as a tight coupling of the fundamental gameplay
to the player's nutrition whilst also making it the hinge point of the
aesthetic and narrative flow of the game.

#### Art - Cute & Adorable

Give as much stuff as possible a face - especially giving enemies silly faces.
Make cute sound effects for damage where possible.
Give story a lighthearted angle.

I overall tried to instill a cutesy "vibe" into the game without necessarily
incorporating such into the core of the gameplay.

#### Technical - Layers

The level design is composed of effectively two "layers" where the inner guides
the player out relatively linearly to the outer with a softer introduction to
combat before emerging into the outer layer with more gameplay diversity.
Additionally, the progress to the final area has multiple layered rooms of
increasing difficulty to try to elevate and prepare the player for the final
boss.

The main music is composed as a series of parallel tracks which dip in and
out to provide a layered soundscape without becoming too uniform. The FLStudio
project file at `res/snd/src/KitchenFloor.flp` contains the source with track
information intact if people with an FLStudio licence want to examine this more
closely.

The rendering of the game is designed around layered ECS
"[systems](https://www.flecs.dev/flecs/md_docs_2Systems.html)" on a dependent
ordering from the tilemap, to the entities, to projectiles, to overlays and
then to filters. Because component render is coupled with gameplay ticks, the
purely behavioural "systems" are nonetheless incorporated into the layer stack
in order to maintain same-frame update consistency. This is structured
(messily) in `src/update.c:pdn_update()` with the "systems" themselves
declared in update-order in `src/local.c:pdn_local_start()`.

Finally - the workflow of incorporating static triggers and behaviours into the
game is centred around creating Tiled layers whose contents are checked against
in the code to act as positional triggers both for typical collision and
gameplay events. In a more "traditional" ECS-based scene these behaviours would
nominally be entities, however checking collisions against the tilemap means
hardcoding limited behaviours could be prototyped faster and avoids the need
for bespoke trigger entities whose behaviour would need to be encoded within
the map data and then expanded into structured data during load. Tile layers
`2`, `4`, `5` and `6` in the Tiled project are the behavioural layers in this
context.

#### Bonus - Double or Nothing

Omitting Golden Ratio in favour of doubling down on layers.

### Final Notes

Created with the following tools:
- CLion
- FLStudio
- Tiled
- GIMP
- Audacity
- [JSFXR](https://sfxr.me)

And the following 1st-order dependencies:
- [Allegro](https://liballeg.org/)
- [LuaJIT](https://luajit.org/)
- [Nuklear](https://github.com/Immediate-Mode-UI/Nuklear)
- [Flecs](https://www.flecs.dev/flecs/)
- [STB](https://github.com/nothings/stb/)

A couple of "wish I could have"s from the time constraint:

- The last minute Windows portability checks had some very strange
breakages I was not up to fixing before the deadline so there's a few
dirty `#ifdef _WIN32` fixes. Given the chance I'd probably put more
focus into parity - possibly having my laptop loaded up on the side
or have a build server pre-setup to do hands-off pseudo-CI.
- Bespoke music tracks for the miniboss and boss
- Multiple/longer music tracks for the main area
- A main menu and in-engine results screen
- Multiple-source lighting and particle effects
- More melee weapons and making melee weapons effective against the boss
- Saving/loading or at least graceful reloading instead of hard failing
