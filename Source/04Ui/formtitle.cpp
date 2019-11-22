// 01frame includes
#include "formtitle.h"
#include "quiiconhelper.h"
#include "ui_formtitle.h"


FormTitle::FormTitle(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormTitle) {
    ui->setupUi(this);
    this->Initial();
}

FormTitle::~FormTitle() {
    delete ui;
}


void FormTitle::Initial() {
    full_screen_ = false;
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setProperty("can_move", 1);
    this->setSizeGripEnabled(true);
    this->setMinimumSize(1200, 900);
    ui->widgetTitle->installEventFilter(this);
    this->my_menu_ = new QUIMenu(this, this);
    ui->layout_titlemenu->addWidget(my_menu_);
    ui->layout_titlemenu->addWidget(my_menu_->toolbar_);
    connect(this, SIGNAL(SignalOpenFileOut()),
            ui->main_widget, SLOT(SlotOpenFileIn()));
    QUIIconHelper::Instance()->setIcon(ui->btnMenu_Min, QChar(0xf068));
    QUIIconHelper::Instance()->setIcon(ui->btnMenu_Max, QChar(0xf2d0));
    QUIIconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xf00d));
}


void FormTitle::on_btnMenu_Min_clicked() {
    showMinimized();
}

void FormTitle::on_btnMenu_Max_clicked() {
    static bool max = false;
    static QRect location = this->geometry();
    if (max) {
        this->setGeometry(location);
        QUIIconHelper::Instance()->setIcon(ui->btnMenu_Max, QChar(0xf2d0));
    } else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
        QUIIconHelper::Instance()->setIcon(ui->btnMenu_Max, QChar(0xf2d2));
    }
    this->setProperty("can_move", max);
    max = !max;
}

void FormTitle::on_btnMenu_Close_clicked() {
    this->close();
}

void FormTitle::SlotFullScreen() {
    ui->widget_titlebtn->hide();
    full_screen_ = true;
    this->showFullScreen();
}

void FormTitle::SlotNormalScreen() {
    ui->widget_titlebtn->show();
    full_screen_ = false;
    this->showNormal();
}

bool FormTitle::eventFilter(QObject *obj, QEvent *evt) {
    if (false == full_screen_) {
        QMouseEvent *event = static_cast<QMouseEvent *>(evt);
        if (event->type() == QEvent::MouseButtonDblClick) {
            on_btnMenu_Max_clicked();
        }
    }
    return QWidget::eventFilter(obj, evt);
}


