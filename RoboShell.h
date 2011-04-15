#ifndef ROBOSHELL_H
#define ROBOSHELL_H

#include <QMainWindow>
#include <QStateMachine>

class FaceTracker;

namespace Ui {
    class RoboShell;
}

class videoInput;

class RoboShell : public QMainWindow
{
    Q_OBJECT

public:
    enum {
        CAMERA,
        ARM,
        BODY,
        WHEELS
    };

    explicit RoboShell(QWidget *parent = 0);
    ~RoboShell();

    void buildStateMachine();

signals:
    void boardOpened();
    void boardClosing();
    void boardClosed();

public slots:
    void close();
    void open(int id = 0);
    void toggleOpen(bool on);

    void poll();

    void stopAllAxes();
    void log(QtMsgType type, const char * message);

private:
    Ui::RoboShell *ui;
    int m_boardId;
    QTimer * m_pollTimer;

    QStateMachine * m_automaton;

    videoInput * m_videoInput;
    QImage m_frame;

    FaceTracker * m_faceTracker;

    static void msgHandler(QtMsgType type, const char * message);
    static RoboShell * s_shell;
    static QtMsgHandler s_oldMsgHandler;
};

#endif // ROBOSHELL_H
