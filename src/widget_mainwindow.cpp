#include "ui_mainwindow.h"
#include "cs_model.h"
#include "cs_design.h"
#include "cs_networker.h"
#include "cs_command.h"
#include "widget_menu.h"
#include "widget_page.h"
#include "dialog_signature.h"
#include "dialog_alarm.h"
#include "dialog_inspector_borrow.h"
#include "dialog_inspector_return.h"
#include "widget_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    d = Design::instance();
    this->setMinimumSize(d->MIM_WINDOW_WIDTH, d->MIM_WINDOW_HEIGHT);
    this->setGeometry(QRect(100, 100, d->widthWindow(), d->heightWindow()));
    ui->setupUi(this);
    frameMenu = ui->widget_menu;
    framePage = ui->widget_list;


    m = Model::instance();
    ui->centralWidget->setStyleSheet("background-color:" + d->c().grary01);

    m_alarm = new DialogAlarm("알림", m->notificator()->message(), 300, 100);
    connect(m, SIGNAL(alarmedChanged()), this, SLOT(updatePage()));

    m_inspectorBorrow = new DialogInspectorBorrow("장비 선택", 500, 200, this);
    m_inspectorReturn = new DialogInspectorReturn("장비 선택", 500, 200, this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::resizeEvent(QResizeEvent *e)
{

    if (!initedUI) {
        initializeUI();
        return;
    }

    QSize newSize = e->size();
    QSize oldSize = e->oldSize();
    d->setWidthWindow(newSize.width());
    d->setHeightWindow(newSize.height());

    resize();

}
void MainWindow::initializeUI()
{
    int x = 0; int y = 0; int w = 0; int h = 0;
    w = d->widthMenu(); h = d->heightMenu();
    setWidget(frameMenu, QRect(x, y, w, h), d->c().grary01);
    widgetMenu = new WidgetMenu(frameMenu);
    QVBoxLayout* vBoxMenubar = new QVBoxLayout(frameMenu);
    vBoxMenubar->setMargin(0);
    vBoxMenubar->addWidget(widgetMenu);

    x += d->widthMenu(); w = d->widthPage(); h = d->heightPage();
    setWidget(framePage, QRect(x, y, w, h), d->c().testColor02);
    widgetPage = new WidgetPage(framePage);
    QVBoxLayout* vBoxList = new QVBoxLayout(framePage);
    vBoxList->setMargin(0);
    vBoxList->addWidget(widgetPage);

    resize();
    connections();
    initedUI = true;
}
void MainWindow::resize()
{
    int x = 0; int y = 0; int w = 0; int h = 0;
    QRect geo;

    geo = frameMenu->geometry();
    x = 0;
    y = 0;
    w = geo.width(); // d->widthWindow(); d->setWidthMenu(w);
    h = d->heightWindow(); d->setHeightMenu(h);//geo.height();
    frameMenu->setGeometry(x, y, w, h);
    widgetMenu->setGeometry(0, 0, w, h);

    geo = framePage->geometry();
    x = d->widthMenu();
    y = 0;
    w = d->widthWindow() - d->widthMenu(); d->setWidthPage(w);
    h = d->heightWindow(); d->setHeightPage(h);
    framePage->setGeometry(x, y, w, h);
    widgetPage->setGeometry(0, 0, w, h);
}

void MainWindow::setWidget(QWidget* w, QRect geometry, QString color)
{
    w->setGeometry(geometry);
    w->setStyleSheet("background-color:" + color);
}

void MainWindow::connections()
{
    connect(widgetMenu->commandProvider()->command(DEVICE_LIST), SIGNAL(clicked()), this, SLOT(listDVIcesWithPageInit()));
    connect(widgetMenu->commandProvider()->command(DEVICE_MANAGE_LIST), SIGNAL(clicked()), this, SLOT(listMNGementsWithPageInit()));
    connect(widgetMenu->commandProvider()->command(EMPLOYEE_MANAGE_LIST), SIGNAL(clicked()), this, SLOT(listEMPloyeesWithPageInit()));
    connect(widgetMenu->btnBorrow(), SIGNAL(clicked()), this, SLOT(doBorrow()));
    connect(widgetMenu->btnReturn(), SIGNAL(clicked()), this, SLOT(doReturn()));
}
void MainWindow::listDVIcesWithPageInit()
{
    m->setPageNumber(1);
    listDVIces();
}
void MainWindow::listMNGementsWithPageInit()
{
    m->setPageNumber(1);
    listMNGements();
}
void MainWindow::listEMPloyeesWithPageInit()
{
    m->setPageNumber(1);
    listEMPloyees();
}
void MainWindow::listDVIces()
{
    widgetMenu->commandProvider()->select(DEVICE_LIST);
    widgetPage->change(DEVICE_LIST);
}
void MainWindow::listMNGements()
{
    widgetMenu->commandProvider()->select(DEVICE_MANAGE_LIST);
    widgetPage->change(DEVICE_MANAGE_LIST);
}
void MainWindow::listEMPloyees()
{
    widgetMenu->commandProvider()->select(EMPLOYEE_MANAGE_LIST);
    widgetPage->change(EMPLOYEE_MANAGE_LIST);
}
void MainWindow::doBorrow()
{
    //m_inspectorBorrow->init();
    //m_inspectorBorrow->show();
    QString fileName = QDir::currentPath() + "/tmp.jpg";
    /*QPixmap pixMap = QPixmap::grabWidget(this);
    if (pixMap.save(fileName))
    {*/
    NetWorker::instance()->uploadFile(fileName)->requestFile();
    //}
}
void MainWindow::doReturn()
{
    m_inspectorReturn->init();
    m_inspectorReturn->show();
}
void MainWindow::updatePage()
{
    if (m->alarmed())
    {
        if (m->notificator()->type() == Notificator::DVIBorrowedSearch) return;
        if (m->notificator()->type() == Notificator::DVIReturnedSearch) return;
        bool result = m->notificator()->result();
        if (m->notificator()->dialog()) {
            m_alarm->setMessage(result ?
                "성공적으로 반영되었습니다." : m->notificator()->message());
            m_alarm->show();
        }

        if (result)
        {
            if (m->notificator()->type() == Notificator::DVIList) listDVIces();
            else if (m->notificator()->type() == Notificator::MNGList) listMNGements();
            else if (m->notificator()->type() == Notificator::DVIModified) QTimer::singleShot(500, this, SLOT(listDVIces()));
            else if (m->notificator()->type() == Notificator::MNGModified) QTimer::singleShot(500, this, SLOT(listMNGements()));
            else if (m->notificator()->type() == Notificator::EMPList) listEMPloyees();
        }
        else
        {
            m_alarm->setMessage(m->notificator()->message());
            m_alarm->show();
        }
        m->alarm(false);
    }
}
