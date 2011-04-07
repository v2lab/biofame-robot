#include "RoboShell.h"
#include "ui_RoboShell.h"

#include <QtCore>

extern "C" {
#include <Ads1240.h>
}

RoboShell::RoboShell(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RoboShell)
    , m_boardId(-1)
{
    ui->setupUi(this);

    // now connect the signals
    connect(ui->openControllerButton, SIGNAL(toggled(bool)),SLOT(toggleOpen(bool)));

    // now autoconnect...
    ui->openControllerButton->setChecked(true);
}

RoboShell::~RoboShell()
{
    delete ui;
    if (m_boardId >= 0)
        close();
}

void RoboShell::close()
{
    if (m_boardId < 0)
        return;

    if (P1240MotDevClose(m_boardId) == ERROR_SUCCESS) {
        qDebug() << "Successfully closed board";
    }
    m_boardId = -1;
}

void RoboShell::open(int id)
{
    Q_ASSERT( id >= 0 && id <= 15 );
    close();
    if (P1240MotDevOpen(id) != ERROR_SUCCESS) {
        qWarning() << "Motor controller wasn't open";
        return;
    }
    m_boardId = id;
}

void RoboShell::toggleOpen(bool on)
{
    if (on)
        open();
    else
        close();

    ui->openControllerButton->setChecked( m_boardId >= 0 );
}
