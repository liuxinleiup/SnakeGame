# 基于C++的QT实现贪吃蛇小游戏  

 通过按键控制蛇的移动，每吃一个商品蛇身就会加长，如果蛇身头尾相碰就结束游戏  

        声明渲染绘图：画笔画刷进行相关的渲染背景蛇和奖品	

        按键处理机制：方便后面的键盘操作
	          定时器：到时就会触发
	          按下空格：代表开始
	          上下左右键控制蛇的移动方向：DIR_DOWN DIR_UP DIR_LEFT DIR_RIGHT
        
        蛇：
	          蛇的表示：矩形的两点确定小方块，3个小方块为初始蛇身
	          判断蛇身蛇头：如果蛇头蛇尾接触就结束游戏
	          蛇身变动：相交就吃掉奖品，吃一个加一个小方块

        奖品
	          奖品的表示：小红点
	          奖品的添加：蛇吃完一个奖品就马上随机添加一个奖品

        蛇吃奖品：
	          吃一个奖品会加一个方块：上面、下面、左面、右面
