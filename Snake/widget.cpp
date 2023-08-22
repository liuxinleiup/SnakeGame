#include "widget.h"
#include "ui_widget.h"
#include <qmediaplayer.h>

//画家
#include <QPainter>
//文字
#include <QRandomGenerator>
//背景音乐
#include <QtMultimedia/QtMultimedia>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QApplication>
#include <QMediaPlayer>
#include <QUrl>
#include <QFileDialog>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //定义窗口大小
        //resize(800,600);
        this->setFixedSize(800,600);

    QMediaPlayer *player = new QMediaPlayer;
    player->setSource(QUrl::fromLocalFile("F:/QT/Snake/images/mu.mp3"));
    player->play();

    //实现定时器 可以让蛇动起来
        //创建定时器
        timer = new QTimer();
        //信号槽   timeout超时
        connect(timer,SIGNAL(timeout()),this,SLOT(timeout()));

    //初始化蛇身
        QRectF rect(400,300,nodeWidth,nodeHeight);
        //小方块加到蛇身上去
        snake.append(rect);
        //再加两端
        addTop();
        addTop();

    //初始化奖品
        addNewReword();


    //背景音乐
//        //创建一个显示视频的控件
//                QVideoWidget* videowin = new QVideoWidget(this);
//                videowin->resize(400,300);
//                //添加一个播放器
//                QMediaPlayer *player = new QMediaPlayer(this);
//                player->setVideoOutput(videowin);
//                //音乐
//                player->setMedia(QMediaContent(QUrl::fromLocalFile("F:/QT/Snake/images/game.mp3")));
//                //player->setVolume(50);//音量
//                //开始播放
//                player->play();






}

Widget::~Widget()
{
    delete ui;
}

//实现按键函数    控制方向
void Widget::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Up:
        if(moveFlag != DIR_DOWN){moveFlag = DIR_UP;}
        break;
    case Qt::Key_Down:
        if(moveFlag != DIR_UP){moveFlag = DIR_DOWN;}
        break;
    case Qt::Key_Right:
        if(moveFlag != DIR_LEFT){moveFlag = DIR_RIGHT;}
        break;
    case Qt::Key_Left:
        if(moveFlag != DIR_RIGHT){moveFlag = DIR_LEFT;}
        break;
    case Qt::Key_Space:
        if(gameStart == false){
            gameStart = true;
            //启动定时器
            timer->start(time);
        }
        else{
            gameStart = false;
            //停止定时器
            timer->stop();
        }
        break;
    default:
        break;
    }
}


//实现超时函数
void Widget::timeout(){//实现逻辑要么都上移，要么底部加一个，顶部取消一个
    //判断有没有重合
    int count = 1;
    if(snake[0].intersects(rewardNode)){
        //相交就吃掉奖品
        count++;
        //吃掉添加新的奖品
        addNewReword();
    }

    while (count--) {
        //蛇的移动
        switch (moveFlag) {
        case DIR_UP:
            addTop();
            break;
        case DIR_DOWN:
            addDown();
            break;
        case DIR_LEFT:
            addLeft();
            break;
        case DIR_RIGHT:
            addRight();
            break;
        default:
            break;
        }
    }

    //删除一个
    deleteLast();
    //刷新一下
    update();

}

//实现上面加一个函数
void Widget::addTop(){
    QPointF leftTop;
    QPointF rightBotom;

    //超出边界（顶端） 加到最下面
    if(snake[0].y()-nodeHeight < 0){
        //this->height窗口
        leftTop = QPoint(snake[0].x(),this->height()-nodeHeight);
        rightBotom = QPointF(snake[0].x()+nodeWidth,this->height());
    }else{
    //没有超出的情况
        //在蛇的上面(蛇和矩形)
        //左上角坐标     nodeHeight小方块矩形
        leftTop = QPointF(snake[0].x(),snake[0].y()-nodeHeight);
        //右下角坐标
        rightBotom = snake[0].topRight();
    }

    //加一个小方块
    snake.insert(0,QRectF(leftTop,rightBotom));
}


//实现下面加一个函数
void Widget::addDown(){
    QPointF leftTop;
    QPointF rightBotom;

    //超出边界（顶端） 加到最下面
    if(snake[0].y()+nodeHeight*2 > this->height()){
        leftTop = QPointF(snake[0].x(),0);
        rightBotom = QPointF(snake[0].x()+nodeWidth,nodeHeight);
    }else{
        //没有超出的情况
        //在蛇的上面(蛇和矩形)
        //左上角坐标     nodeHeight小方块矩形
        leftTop = snake[0].bottomLeft();
        //右下角坐标
        rightBotom = snake[0].bottomRight()+QPointF(0,nodeHeight);
    }

    //加一个小方块
    snake.insert(0,QRectF(leftTop,rightBotom));
}


//实现左面加一个函数
void Widget::addLeft(){
    QPointF leftTop;
    QPointF rightBotom;

    //超出边界（顶端） 加到最下面
    if(snake[0].x()-nodeWidth < 0){
        leftTop = QPointF(this->width()-nodeWidth,snake[0].y());
    }else{
        //没有超出的情况
        //在蛇的上面(蛇和矩形)
        //左上角坐标     nodeHeight小方块矩形
        leftTop = snake[0].topLeft()-QPointF(nodeWidth,0);
    }

    rightBotom = leftTop+QPointF(nodeWidth,nodeHeight);
    //右下角坐标
    //加一个小方块
    snake.insert(0,QRectF(leftTop,rightBotom));
}


//实现右面加一个函数
void Widget::addRight(){
    QPointF leftTop;
    QPointF rightBotom;

    //超出边界（顶端） 加到最下面
    if(snake[0].x()-nodeWidth*2 > this->width()){
        leftTop = QPointF(0,snake[0].y());
    }else{
        //没有超出的情况
        //在蛇的上面(蛇和矩形)
        //左上角坐标     nodeHeight小方块矩形
        leftTop = snake[0].topRight();
    }

    rightBotom = leftTop+QPointF(nodeWidth,nodeHeight);
    //右下角坐标
    //加一个小方块
    snake.insert(0,QRectF(leftTop,rightBotom));
}





//实现绘图
void Widget::paintEvent(QPaintEvent *event){
    //画家
    QPainter painter(this);
    //画笔
    QPen pen;
    //画刷
    QBrush brush;

    //背景图片
    QPixmap pix;
    pix.load("F:/QT/Snake/images/bk.png");
    //    QPixmap pixmap(":/images/bk.png");
    painter.drawPixmap(0,0,800,600,pix);

    //画蛇
        //画笔
        pen.setColor(Qt::black);
        //画刷
        brush.setColor(Qt::darkMagenta);
        brush.setStyle(Qt::SolidPattern);

        //画家使用画笔和画刷
        painter.setPen(pen);
        painter.setBrush(brush);

        //画蛇的头尾
        for(int i=0;i<snake.length();i++){
            painter.drawRect(snake[i]);
        }

    //画奖品
        //画笔
        pen.setColor(Qt::red);
        //画刷
        brush.setColor(Qt::red);
        brush.setStyle(Qt::SolidPattern);

        //画家使用画笔和画刷
        painter.setPen(pen);
        painter.setBrush(brush);
        //painter.drawRect(rewardNode);//奖品
        painter.drawEllipse(rewardNode);

    //判断蛇头是否碰到蛇身
        if(checkContact()){
            QFont font("方块输出",30,QFont::ExtraLight,false);
            painter.setFont(font);
            painter.drawText(
                    (this->width()-300)/2,
                    (this->height()-30)/2,
                    QString("完成")
                );
            timer->stop();
        }

    //调用一下父类
    QWidget::paintEvent(event);
}


//实现减去一个方块
void Widget::deleteLast(){
    snake.removeLast();
}


//实现添加奖品函数
void Widget::addNewReword(){
    //奖品
    int width = this->width();
    int a = QRandomGenerator::global()->bounded(width/20*20);
    int height = this->height();
    int b = QRandomGenerator::global()->bounded(height/20*20);
    rewardNode = QRectF(
            //qrand()%(this->width()/20)*20,
            //qrand()%(this->height()/20)*20,
            //QT6用上面方法会报错：'qrand' was not declared in this scope; did you mean 'srand'?
            a,
            b,
            nodeWidth,
            nodeHeight
        );
}


//实现判断蛇头是否碰到蛇身函数
bool Widget::checkContact(){
    for(int i = 1; i < snake.length(); i++)
        for (int j = i+1; j < snake.length(); j++) {
                if(snake[i] == snake[j]){
                    return true;
                }
        }
    return false;
}






