Tetris - New Randomizer  v2025-1-18

1. How to use:
Patch the ips file on the rom.
The rom should be 'Tetris (World) (Rev 1)'.

2. Background:
It was intended that the randomizer reduces the chances of getting one and the same piece shape 3 times in a row. However, the randomizer works differently in practice. Pieces are numerated from 0 to 6, repectively from 000 to 110 in binary notation. The code uses a bitwise OR operation. This is an operation that takes 2 binary numbers to compute a new binary number. The result has a 1 at a certain digit if at least one of the 2 arguments has a 1 at the same digit.
As a result, piece shapes containing many zeros appear less frequent. The relative frequencies should be as follows:
    L: 10.7 %
    J, I, Z: 13.7 %
    O, S, T: 16.1 %

3. What this patch dose:
This hack provides 4 new randomizer patches. Chose one you like to use.
In a Tetris GB game there are three kinds of pieces. The CURRENT which is under using. The PREVIEW which is shown in the little window. The NEXT which will be given by the randomizer.
Here We difine 3 concepts to simply show what the patch do.

SP (same probability). The probability that the randomizer give a piece just same as the one before.
EP (expected probability). The probability that the randomizer give a piece you just want and this piece should not be same as the one before.
NEITTP (no expected in ten turns probability). The probability that you can't get what you want in successive ten turns.

1) 0H1R
Ignore history, just use the NEXT the randomizer given.
This logic is just like what the Tetris (Electronika 60) use.
SP--14.29%    EP--14.29%    NEITTP--21.41%

2) 1H2R
Random once and check if the NEXT is same as PREVIEW. If it's false then use the NEXT, or random again and use the new NEXT.
SP--2.04%    EP--16.33%    NEITTP--16.82%

3) 2H2R
Random once, then check if the NEXT is same as PREVIEW or CURRENT. If it's false then use the NEXT, or random again and use the new NEXT.
SP--2.04%    EP--16.33%    NEITTP--13.14%

4) 2H3R
Random once, then check if the NEXT is same as PREVIEW or CURRENT. If it's false then use the NEXT, or Random again.
Check if the NEXT is same as PREVIEW or CURRENT. If it's false then use the NEXT, or Random thirdly and use the new NEXT.
SP--0.58%    EP--19.53%    NEITTP--10.20%

Tetris NES ? :
SP--3.57%    EP--16.07%    NEITTP--17.34%

Tetris GB:
SP--8.86%    EP--15.19%    NEITTP--19.25%

4. Special thanks:
vinheim3		https://github.com/vinheim3/tetris-gb-disasm
RGBDS		    https://rgbds.gbdev.io/
Deep Toaster	https://clrhome.org/table/
灰机wiki		https://tetris.huijiwiki.com/wiki/%E4%BB%BB%E5%A4%A9%E5%A0%82%E9%9A%8F%E6%9C%BA%E5%99%A8
strategywiki    https://strategywiki.org/w/index.php/Tetris_(Game_Boy)
