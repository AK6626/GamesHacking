Tetris - New Randomizer  v2025-1-18

how to use:
patch the ips file to the rom.

rom version:
Tetris (World) (Rev 1)

back ground:
It was intended that the randomizer reduces the chances of getting one and the same piece shape 3 times in a row. However, the randomizer works differently in practice. Pieces are numerated from 0 to 6, repectively from 000 to 110 in binary notation. The code uses a bitwise OR operation. This is an operation that takes 2 binary numbers to compute a new binary number. The result has a 1 at a certain digit if at least one of the 2 arguments has a 1 at the same digit.
As a result, piece shapes containing many zeros appear less frequent. The relative frequencies should be as follows:
    L: 10.7 %
    J, I, Z: 13.7 %
    O, S, T: 16.1 %


This hack provides 3 kinds of new randomizer. 2H3R is recommended.

1. 0H1R
Do not care about any history. Just random a piece and use it.
This randomizer just like the logic which the Tetris (Electronika 60) use.

2. 1H2R
Random once. If it is different form the one before it, use it. Or random again and use the result whatever it is.
This randomizer make the chance to choose a piece just like before from 1/7 to 1/49. 
This one is a little like the randomizer of NES Tetris (USA). (Because of the invalid value, the probability of being continuously identical decreases from 1 in 7 to 1 in 28 instead of 1 in 49)

3. 2H3R
Random once. if it is different form the current or the preview piece, use it. Or random again and do the same jugement. Or random the third time and use the result whatever it is.
This randomizer may be the closest to the original design intent, while keeping the frequencies of all different 7 piece shapes same.

more: (no need for gamer, just for developer)
The source code is provided in the folder 'src'.
All changes can be found in the area from '.only1player:' to the head of '.hDone:'

special thanks:
vinheim3		https://github.com/vinheim3/tetris-gb-disasm
RGBDS		https://rgbds.gbdev.io/
Deep Toaster	https://clrhome.org/table/
灰机wiki		https://tetris.huijiwiki.com/wiki/%E4%BB%BB%E5%A4%A9%E5%A0%82%E9%9A%8F%E6%9C%BA%E5%99%A8
strategywiki	https://strategywiki.org/w/index.php/Tetris_(Game_Boy)
