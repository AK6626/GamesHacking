Release Notes
==================

ABOUT

"Tetris - Rosy Retrospection" aims to combine the joyful nostalgia of playing
classic GameBoy Tetris with the established comfort of modern gameplay
mechanics.

INSTRUCTIONS

This hack is published as patches in BDF and UPS format for the original game.
You don't need to apply both, just choose the format that's more convenient
for you to use.
MD5 of the unpatched file: 982ed5d2b12a0377eb14bcdc4123744e

For UPS, there is a great browser app at https://www.romhacking.net/patch/.

FEATURES

This hack consists of the following additions and improvements:

- Implement Super Rotation System
  Test multiple locations for collisions when rotating a piece.

- Shadow piece
  A shadow piece indicates where the current piece would touch the bottom.

- Three previews
  Two more preview pieces got squeezed next to the original one.

- Use SELECT to hold
  You can stash one piece for later use using SELECT. This HOLD piece is drawn
  in shadow-style so it doesn't distract from the preview.

- 7-Bag with new pseudo-random number generator
  The original pseudo-random number generator was fully replaced. The new one
  offers better randomness with a more even distribution and entropy that's
  sourced from user input during gameplay.
  This generator is used to draw the next piece from a "bag" containing each
  of the seven pieces once.

- "Hard drop" and saving from my previous hack
  Pressing UP drops the piece in an instant. And you get to keep your
  highscore.

- Redesigned screen layout
  An extensive redesign of the layout for Mode A, B and 2Player was necessary
  to accommodate all new features.

- New demos
  All these changes got the original demos out of sync, so I had to record new
  ones.

- Award spin clears
  If a locked piece clears one or more lines without being free to move up,
  left or down, it's honored as a spin clear.
  Spin clears earn four times as much points in Mode A and count twice the
  number of lines for Mode B. In multiplayer, they always send four lines of
  garbage to the opponent.

- Faster "delayed auto shift"
  Gets you faster to the edges of the field when holding LEFT or RIGHT.

- Lock delay
  A piece locks after 30 frames without movement. Moving it resets the delay,
  but only up to 15 times. Pressing DOWN cancels the delay and locks
  immediately.

- Faster line clear
  Keeps up the pace by clearing lines more quickly

- Extend the field by four invisible lines
  Now there are four more off-screen lines extending the usual 18 lines on
  screen.

- New game over condition
  If the piece locks without being visible at all, it's game over.

- Adjust difficulty
  Level 20 becomes more of a kill-screen as it is known from the NES version.

- Higher start location
  A new piece spawns above the field and not at the top-most line.

- Fix two bugs in the original game
  Pressing START right before finishing a Mode B game could lock up the game.
  The second bug would repeated the first line after a clear.
  Both issues are gone now.

In addition to hard drop, it includes all the other features of my previous
"Classic Harddrop" hack:

- Hard drop
- No more waiting for rockets and disclaimers (START to skip)
- Scores are saved to SRAM
- Independent Highscores for 'Heart Levels' <3
- Character input recalls the last name entered
- Pressing B at name input deletes the current character

Please contact Ospin on romhacking.net if you notice any issues.

Enjoy


FAQ

"Why not release it as IPS/BPS?"
I'm a bit paranoid about releasing copyrighted material. IPS etc. are fine if
you only do in-place changes or insertions. But as soon as you relocate
existing code or data, it will end up in the patch file. But this hack
relocates a lot of stuff in order to fit everything.
BDF is able to identify those relocations, so the patch will only include
meta-data to move the data and patch differences, but not the data itself.
Unfortunately, there aren't many implementations of BDF around and I got many
complaints about usability.
After looking more closely at other patch formats, I identified UPS as a
viable alternative. It's as naive as IPS and thus easily implemented. But it
only stores the difference of a given byte. The original intend is
reversibility, but it also has the advantage that the information stored in
the patch is useless without the original data.

"Tetris DX please?!"
Sorry, not enough nostalgia for that one.


Changelog
==================
v1.2
- Do not increase soft-drop bonus during lock delay
- Corrected SRS table
v1.1
- Fix HOLD for L-blocks
- Reset DAS delay at spawn, even if L/R is pressed already
- Fix a shadow update optimization and improve speed
- Prevent HOLD during line clear
- Avoid possible hang with PAUSE vs line clear
- Disable hard drop for 10 frames after spawn
- Offer a UPS patch
v1.0
- first release

Known Bugs
==================
- Drop bonus may not update the counter immediately
