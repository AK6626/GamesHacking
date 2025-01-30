Hack Game: Tetris (World) (Rev 1)
Hack Name: Improvement v1.0
Hack File Formant: ips file (You can apply this on your rom file with tool like Lunar IPS or Online Patcher (https://www.romhacking.net/patch/))

Content:
Things in "Tetris - Classic Harddrop v1.0" are included.
Faster “delayed auto shift”. First move delay has been changed from $17 to $0f. The held move delay has been changed from $09 to $02.
A new 2H2R randomizer.

About 2H2R randomizer:

In a Tetris GB game there are three kinds of pieces. The CURRENT which is under using. The PREVIEW which is shown in the little window. The NEXT which will be given by the randomizer.

Here We difine 3 concepts to simply show what the patch do.
SP (same probability). The probability that the randomizer give a piece just same as the one before.
EP (expected probability). The probability that the randomizer give a piece you just want and this piece should not be same as the one before.
NEITTP (no expected in ten turns probability). The probability that you can't get what you want in successive ten turns.

2H2R
Random once, then check if the NEXT is same as PREVIEW or CURRENT. If it's false then use the NEXT, or random again and use the new NEXT.
SP--4.08%    EP--18.37%    NEITTP--13.14%
