#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//按键
#include <QKeyEvent>
//定时器
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE



//定义方向
enum Dirct{DIR_LEFT,DIR_RIGHT,DIR_DOWN,DIR_UP};


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    //声明渲染绘图
    void paintEvent(QPaintEvent *event);

    //声明按键处理
    void keyPressEvent(QKeyEvent *event);

    //声明上面加一个函数
    void addTop();
    //声明下面加一个函数
    void addDown();
    //声明左面加一个函数
    void addLeft();
    //声明右面加一个函数
    void addRight();

    //声明减去一个模块
    void deleteLast();

    //声明添加奖品函数
    void addNewReword();

    //声明判断蛇头蛇身
    bool checkContact();

private:
    Ui::Widget *ui;
    //初始化定义方向
    int moveFlag = DIR_UP;
    //定义启动的开始
    bool gameStart = false;

    //定义定时器
    QTimer *timer;
    int time = 100;//超时事件间隔(毫秒)

    //蛇的表示  矩形两点确定(容器)
    QList <QRectF> snake;

    //小方块表示
    int nodeWidth = 20;
    int nodeHeight = 20;

    //奖品的表示
    QRectF rewardNode;

protected slots:
    //定义超时函数
    void timeout();
};


#endif // WIDGET_H
