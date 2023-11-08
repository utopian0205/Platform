#include "ribbonmenubar.h"
#include "ui_ribbonmenubar.h"
#include<QMenu>
#include"ribbontabcontent.h"
#include<QVBoxLayout>

RibbonMenuBar::RibbonMenuBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RibbonMenuBar)
{
    ui->setupUi(this);


    QFile file(":/res/qss/QTabWidget.qss");
    if(file.open(QFile::ReadOnly))
    {
        QString qss = QLatin1String(file.readAll());
        file.close();
        setStyleSheet(qss);
    }

    initTitle();
    initTitleBar();
    initMenu();


}

RibbonMenuBar::~RibbonMenuBar()
{
    delete ui;
}
void RibbonMenuBar::initTitle()
{
    ui->title->setText("系统测试平台V1.0");
//    QPalette pal = ui->title->palette();
//    pal.setColor(QPalette::WindowText,QColor(0x3a,0x51,0x6e));
//    ui->title->setPalette(pal);
//    QFont font = ui->title->font();
//    font.setFamily("Times New Roman");
//    font.setPixelSize(30);
//    ui->title->setFont(font);


}

void RibbonMenuBar::initMenu()
{
    // Add tabs to ribbon
    ui->ribbonTabWidget->addTab(QIcon(":/icons/briefcase_1.svg"), "Project");
    ui->ribbonTabWidget->addTab(QIcon(":/icons/monitor_1.svg"), "View");
    ui->ribbonTabWidget->addTab(QIcon(":/icons/engineering_1.svg"), "Tools");
    ui->ribbonTabWidget->addTab(QIcon(":/icons/information_1.svg"), "Help");

    //return;

    // Add 'Open project' button
    QToolButton *openProjectButton = new QToolButton;
    openProjectButton->setText(tr("Open"));
    openProjectButton->setToolTip(tr("Open existing project"));
    openProjectButton->setIcon(QIcon(":/icons/live_folder_2.svg"));
    openProjectButton->setEnabled(true);
    ui->ribbonTabWidget->addButton("Project", "Project", openProjectButton);

    // Add 'New project' button
    QToolButton *newProjectButton = new QToolButton;
    newProjectButton->setText(tr("New"));
    newProjectButton->setToolTip(tr("Create new project"));
    newProjectButton->setIcon(QIcon(":/icons/create_new_2.svg"));
    newProjectButton->setEnabled(true);
    ui->ribbonTabWidget->addButton("Project", "Project", newProjectButton);

    // Add 'Save project' button
    QToolButton *saveProjectButton = new QToolButton;
    saveProjectButton->setText(tr("Save"));
    saveProjectButton->setToolTip(tr("Save project"));
    saveProjectButton->setIcon(QIcon(":/icons/save_2.svg"));
    saveProjectButton->setEnabled(false);
    ui->ribbonTabWidget->addButton("Project", "Project", saveProjectButton);

    // Add 'Open file' button
    QToolButton *openFileButton = new QToolButton(this);
    openFileButton->setText(tr("File"));
    openFileButton->setToolTip(tr("Open file or directory"));
    openFileButton->setIcon(QIcon(":/icons/add_folder_2.svg"));

    // Add dropdown menu to button
    openFileButton->setPopupMode(QToolButton::MenuButtonPopup);
    QMenu *menu = new QMenu("Title");

    menu->addAction(QIcon(":/icons/file_2.svg"), "Recent file 1");
    menu->addAction(QIcon(":/icons/file_2.svg"), "Recent file 2");
    menu->addAction(QIcon(":/icons/file_2.svg"), "Recent file 3");
    openFileButton->setMenu(menu);

    ui->ribbonTabWidget->addButton("Project", "Import", openFileButton);

    // Add 'Open database' button
    QToolButton *openDatabaseButton = new QToolButton;
    openDatabaseButton->setText(tr("Database"));
    openDatabaseButton->setToolTip(tr("Connect to database"));
    openDatabaseButton->setIcon(QIcon(":/icons/add_database_2.svg"));
    ui->ribbonTabWidget->addButton("Project", "Import", openDatabaseButton);


    // Add 'Connect to web service' button
    QToolButton *connectWebserviceButton = new QToolButton;
    connectWebserviceButton->setText(tr("Web service"));
    connectWebserviceButton->setToolTip(tr("Connect to web service"));
    connectWebserviceButton->setIcon(QIcon(":/icons/add_link_2.svg"));
    ui->ribbonTabWidget->addButton("Project", "Import", connectWebserviceButton);

    QToolButton *testButton = new QToolButton;
    testButton->setText(tr("Web service"));
    testButton->setToolTip(tr("Connect to web service"));
    testButton->setIcon(QIcon(":/icons/add_link_2.svg"));
    ui->ribbonTabWidget->addButton("Project", "Twst", testButton);
}

void RibbonMenuBar::initTitleBar()
{
    ui->btnClose->setFixedSize(QSize(BUTTON_WIDTH,BUTTON_HEIGHT));
    ui->btnStyle->setFixedSize(QSize(BUTTON_WIDTH,BUTTON_HEIGHT));
    ui->btnMinSize->setFixedSize(QSize(BUTTON_WIDTH,BUTTON_HEIGHT));
    ui->btnMaxSize->setFixedSize(QSize(BUTTON_WIDTH,BUTTON_HEIGHT));

    ui->btnClose->setIcon(QIcon(":/res/svg/close-button.svg"));
    ui->btnMinSize->setIcon(QIcon(":/res/svg/minimize-button.svg"));
    ui->btnMaxSize->setIcon(QIcon(":/res/svg/maximize-button.svg"));
    ui->btnStyle->setIcon(QIcon(":/res/svg/list-button.svg"));

    QMenu* pMenu = new QMenu();
    QAction* pActStyleBlue = new QAction(QIcon(":/res/svg/style_blue.svg"),tr("蓝色样式"),this);
    QAction* pActStyleAqua = new QAction(QIcon(":/res/svg/style_aqua.svg"),tr("水绿色样式"),this);
    QAction* pActStyleSilver = new QAction(QIcon(":/res/svg/style_silver.svg"),tr("水银色样式"),this);
    QAction* pActStyleBlack = new QAction(QIcon(":/res/svg/style_black.svg"),tr("黑色样式"),this);
    pMenu->addAction(pActStyleBlue);
    pMenu->addAction(pActStyleAqua);
    pMenu->addAction(pActStyleSilver);
    pMenu->addAction(pActStyleBlack);
    ui->btnStyle->setMenu(pMenu);

    connect(pActStyleBlue,&QAction::triggered,this,[=](){
        setBackStyle(STYLE_SHEET_BLUE);
    });
    connect(pActStyleAqua,&QAction::triggered,this,[=](){
        setBackStyle(STYLE_SHEET_AQUA);
    });
    connect(pActStyleSilver,&QAction::triggered,this,[=](){
        setBackStyle(STYLE_SHEET_SILVER);
    });
    connect(pActStyleBlack,&QAction::triggered,this,[=](){
        setBackStyle(STYLE_SHEET_BLACK);
    });


    QObject::connect(ui->btnClose, &QPushButton::clicked, this, [=]() {
        sigBtnCloseClicked();
    });
    QObject::connect(ui->btnMinSize, &QPushButton::clicked, this, [=]() {
        sigBtnMinClicked();
    });
    QObject::connect(ui->btnMaxSize, &QPushButton::clicked, this, [=]() {
        sigBtnMaxClicked();
    });

}

void RibbonMenuBar::mouseDoubleClickEvent(QMouseEvent* event)
{
    QRect rect = ui->title->geometry();
    if(event->button() == Qt::LeftButton && event->y()<rect.height()+10)
    {
        sigBtnMaxClicked();
    }

//    QWidget::mouseDoubleClickEvent(event);
}

void RibbonMenuBar::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && event->y()<ui->title->height()+10 && event->x()<ui->title->width()+10)
    {

        m_bIsPressed = true;
        m_mouseStartPos = event->globalPos();
    }

    QWidget::mousePressEvent(event);
}

void RibbonMenuBar::mouseMoveEvent(QMouseEvent* event)
{
    if(m_bIsPressed)
    {

        bool maxOrFull = this->parentWidget()->windowState() & (Qt::WindowFullScreen | Qt::WindowMaximized);

        if (maxOrFull)
        {
            auto w = this->parentWidget();
            auto geom = this->parentWidget()->normalGeometry();
            w->mapFromGlobal(event->globalPos());
            auto localX = geom.width() * (event->globalX() * 1.0 / w->width());
            geom.moveTopLeft(QPoint(event->x() - localX, 0));
            sigBtnMaxClicked();
            w->setGeometry(geom);
            m_mouseStartPos = event->globalPos();
        }
        else
        {
            //获得鼠标移动的距离
            QPoint offset = event->globalPos() - m_mouseStartPos;
            //主窗口的位置
            QPoint mainPos = this->parentWidget()->frameGeometry().topLeft();
            this->parentWidget()->move(mainPos.x()+offset.x(),mainPos.y()+offset.y());
            m_mouseStartPos = event->globalPos();
        }


    }
    QWidget::mouseMoveEvent(event);
}

void RibbonMenuBar::mouseReleaseEvent(QMouseEvent* event)
{

    if(event->button() == Qt::LeftButton)
    {
        m_bIsPressed = false;

    }
    QWidget::mouseReleaseEvent(event);
}

void RibbonMenuBar::setBackStyle(int style)
{
    sigPaletteChange(style);
    QString filepath;
    switch (style) {
    case STYLE_SHEET_BLUE:
        filepath = ":/res/qss/QTabWidget.qss";
        break;
    case STYLE_SHEET_AQUA:
        filepath = ":/res/qss/QTabWidget_aqua.qss";
        break;
    case STYLE_SHEET_SILVER:
        filepath = ":/res/qss/QTabWidget_silver.qss";
        break;
    case STYLE_SHEET_BLACK:
        filepath = ":/res/qss/QTabWidget_black.qss";
        break;
    default:
        filepath = ":/res/qss/QTabWidget.qss";
        break;
    }

    QFile file(filepath);
    if(file.open(QFile::ReadOnly))
    {
        QString qss = QLatin1String(file.readAll());
        file.close();
        setStyleSheet(qss);
    }

//    setStyleSheet(styleSheet);
}

void RibbonMenuBar::setTitleState(Qt::WindowStates state)
{
    if(state == Qt::WindowMaximized)
        ui->btnMaxSize->setIcon(QIcon(":/res/svg/maximize-button.svg"));
    else if(state == Qt::WindowNoState)
        ui->btnMaxSize->setIcon(QIcon(":/res/svg/restore-button.svg"));

}

void RibbonMenuBar::on_ribbonTabWidget_tabBarDoubleClicked(int )
{
    //ui->ribbonTabWidget->hide();
    //ui->ribbonTabWidget->setTabBarAutoHide(true);
    //ui->ribbonTabWidget->tabBar()->hide();
    //ui->ribbonTabWidget->hide();

    int cnt =  ui->ribbonTabWidget->count();
    if(cnt<=0) return;
    QWidget *tab = ui->ribbonTabWidget->widget(0);
    RibbonTabContent *ribbonTabContent = static_cast<RibbonTabContent*>(tab);
    bool bExtand = ribbonTabContent->isVisible();
    if(bExtand)
    {

        for (int i=0;i<cnt;++i) {
            QWidget *tab = ui->ribbonTabWidget->widget(i);
            RibbonTabContent *ribbonTabContent = static_cast<RibbonTabContent*>(tab);
            ribbonTabContent->hideTab();
        }
    }
    else
    {

        for (int i=0;i<cnt;++i) {
            QWidget *tab = ui->ribbonTabWidget->widget(i);
            RibbonTabContent *ribbonTabContent = static_cast<RibbonTabContent*>(tab);
            ribbonTabContent->extandTab();
        }
    }
}
