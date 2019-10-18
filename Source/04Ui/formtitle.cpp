// 01frame includes
#include "formtitle.h"
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
    this->setProperty("canMove", 1);
    this->setSizeGripEnabled(true);
    this->setMinimumSize(1200, 900);
    ui->widgetTitle->installEventFilter(this);
    this->my_menu_ = new myMenu(this, this);
    ui->layout_titlemenu->addWidget(my_menu_);
    ui->layout_titlemenu->addWidget(my_menu_->toolbar_);
    connect(this, SIGNAL(SigalOpenFileOut()),
            ui->main_widget, SLOT(SlotOpenFileIn()));
    IconHelper::Instance()->setIcon(ui->btnMenu_Min, QChar(0xf068));
    IconHelper::Instance()->setIcon(ui->btnMenu_Max, QChar(0xf2d0));
    IconHelper::Instance()->setIcon(ui->btnMenu_Close, QChar(0xf00d));
}


void FormTitle::on_btnMenu_Min_clicked() {
    showMinimized();
}

void FormTitle::on_btnMenu_Max_clicked() {
    static bool max = false;
    static QRect location = this->geometry();
    if (max) {
        this->setGeometry(location);
        IconHelper::Instance()->setIcon(ui->btnMenu_Max, QChar(0xf2d0));
    } else {
        location = this->geometry();
        this->setGeometry(qApp->desktop()->availableGeometry());
        IconHelper::Instance()->setIcon(ui->btnMenu_Max, QChar(0xf2d2));
    }
    this->setProperty("canMove", max);
    max = !max;
}

void FormTitle::on_btnMenu_Close_clicked() {
    close();
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
        static QPoint mousePoint;
        static bool mousePressed = false;
        QMouseEvent *event = static_cast<QMouseEvent *>(evt);
        if (event->type() == QEvent::MouseButtonPress) {
            if (event->button() == Qt::LeftButton) {
                mousePressed = true;
                mousePoint = event->globalPos() - this->pos();
            }
        } else if (event->type() == QEvent::MouseButtonRelease) {
            mousePressed = false;
        } else if (event->type() == QEvent::MouseMove) {
            if (mousePressed && (event->buttons() && Qt::LeftButton)) {
                if (this->property("canMove").toBool()) {
                    this->move(event->globalPos() - mousePoint);
                }
            }
        } else if (event->type() == QEvent::MouseButtonDblClick) {
            on_btnMenu_Max_clicked();
        }
    }
    return QWidget::eventFilter(obj, evt);
}


