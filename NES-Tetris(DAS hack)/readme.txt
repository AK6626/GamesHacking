Sorry for some content is Chinese only.

Game Version: Tetris (USA).nes
Hack Description:
1) Shorten the display time of the copyright display page.
2) Change the hex value of the rom to reduce DAS and ARR.
Tetris (USA) (h, A540).ips: 
DAS hex value is changed from $10 to $0A.
ARR hex value is changed from $0A to $05.
$05 make the move left or right speed higher while not too high.
Tetris (USA) (h, A840).ips: 
DAS hex value is changed from $10 to $0A.
ARR hex value is changed from $0A to $08.
These make the move left or right speed more like SRS does.

NES游戏：Tetris (USA)
1、关于DAS、ARR的修改涉及2个位置的数据共3个。
偏移9D8:
C910XXXXA90A
偏移A15:
A910

根据参考1可知
DAS_DELAY := $0A
DAS_RESET := $10
测试发现$10值减小后可减小DAS
而$0A、$10差值减小会减小ARR

如果按照参考2的说法，改为SRS系统的相应时间，两处偏移的2个10应改为0A，1个0A应该为08（保持差值为2）。
初步测试手感很像。

本次修改暂定改为：
C90AXXXXA905
A90A
主要考虑ARR值改为5可保留部分横向移动追求准确的手感。

2、关于版权声明的显示时间
偏移246和24B:
A9FF
FF为显示时间

本次修改暂定改为：40

参考：
1、NES Tetris USA 反汇编：https://github.com/CelestialAmber/TetrisNESDisasm
2、GBC Tetris DX 反汇编：https://github.com/CreepercraftYT/tetris-gb-disasm-dx
