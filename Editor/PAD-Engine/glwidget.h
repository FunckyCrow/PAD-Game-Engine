#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <PAD Engine/Core/EngineDLL.h>
#include <QOpenGLWidget>
#include <QTimer>
#include <iostream>
#include <fstream>


class GLWidget final : public QOpenGLWidget
{
    Q_OBJECT
public:
    GLWidget() = delete;

    GLWidget(QWidget* _parent = 0, Qt::WindowFlags _f = Qt::WindowFlags()) :
        QOpenGLWidget(_parent, _f)
    {
            QTimer* timer = new QTimer(this);
            connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
            timer->start(0);
            std::ofstream toto("toto.dest");
            toto << "dest";
            toto.close();
    }

    ~GLWidget()
    {
    }
private:
    QTimer* timer;

public:

    inline void Init() {}

public slots:
    inline void Update()
    {
        pad::Simulate();
    }
private:
    inline void paintGL() override
    {
        pad::Simulate();
    }
    inline void resizeGL(int w, int h) override
    {

    }
};

#endif
