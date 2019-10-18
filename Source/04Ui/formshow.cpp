// 01 frame
#include "formshow.h"
#include "ui_formshow.h"

//---------------------界面初始化---------------------//
FormShow::FormShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormShow) {
    ui->setupUi(this);
    this->Initial();
}
FormShow::~FormShow() {
    delete ui;
}
bool FormShow::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::MouseButtonDblClick) {
        QLabel *widget = static_cast<QLabel *>(watched);
        if (!videoMax) {
            videoMax = true;
            hide_video_all();
            ui->formshow_gridLayout->addWidget(widget, 0, 0);
            widget->setVisible(true);
        } else {
            videoMax = false;
            show_video_all();
        }
    } else if (event->type() == QEvent::MouseButtonPress) {
        if (qApp->mouseButtons() == Qt::RightButton) {
            videoMenu->exec(QCursor::pos());
        }
    }
    return QWidget::eventFilter(watched, event);
}
void FormShow::Initial() {
    videoMax = false;
    videoCount = 16;
    videoType = "1_16";
    for (int i = 0; i < videoCount; i++) {
        QLabel *lab = new QLabel;
        lab->setProperty("formshow", "lab");
        lab->setObjectName(QString("video%1").arg(i + 1));
        lab->installEventFilter(this);
        lab->setFocusPolicy(Qt::StrongFocus);
        lab->setAlignment(Qt::AlignCenter);
        lab->setText(QString("通道 %1").arg(i + 1));
        lab->setScaledContents(true);
        widgets.append(lab);
    }
    videoMenu = new QMenu(this);
    QMenu *menu4 = videoMenu->addMenu("切换到4画面");
    menu4->addAction("通道1-通道4", this, SLOT(show_video_4()));
    menu4->addAction("通道5-通道8", this, SLOT(show_video_4()));
    menu4->addAction("通道9-通道12", this, SLOT(show_video_4()));
    menu4->addAction("通道13-通道16", this, SLOT(show_video_4()));
    QMenu *menu6 = videoMenu->addMenu("切换到6画面");
    menu6->addAction("通道1-通道6", this, SLOT(show_video_6()));
    menu6->addAction("通道6-通道11", this, SLOT(show_video_6()));
    menu6->addAction("通道11-通道16", this, SLOT(show_video_6()));
    QMenu *menu8 = videoMenu->addMenu("切换到8画面");
    menu8->addAction("通道1-通道8", this, SLOT(show_video_8()));
    menu8->addAction("通道9-通道16", this, SLOT(show_video_8()));
    QMenu *menu9 = videoMenu->addMenu("切换到9画面");
    menu9->addAction("通道1-通道9", this, SLOT(show_video_9()));
    menu9->addAction("通道8-通道16", this, SLOT(show_video_9()));
    videoMenu->addAction("切换到16画面", this, SLOT(show_video_16()));
    this->show_video_all();
}


void FormShow::show_video_all() {
    if (videoType == "1_4") {
        change_video_4(0);
    } else if (videoType == "5_8") {
        change_video_4(4);
    } else if (videoType == "9_12") {
        change_video_4(8);
    } else if (videoType == "13_16") {
        change_video_4(12);
    } else if (videoType == "1_6") {
        change_video_6(0);
    } else if (videoType == "6_11") {
        change_video_6(5);
    } else if (videoType == "11_16") {
        change_video_6(10);
    } else if (videoType == "1_8") {
        change_video_8(0);
    } else if (videoType == "9_16") {
        change_video_8(8);
    } else if (videoType == "1_9") {
        change_video_9(0);
    } else if (videoType == "8_16") {
        change_video_9(7);
    } else if (videoType == "1_16") {
        change_video_16(0);
    }
}
void FormShow::show_video_4() {
    videoMax = false;
    QString videoType;
    int index = 0;
    QAction *action = static_cast<QAction *>(sender());
    QString name = action->text();
    if (name == "通道1-通道4") {
        index = 0;
        videoType = "1_4";
    } else if (name == "通道5-通道8") {
        index = 4;
        videoType = "5_8";
    } else if (name == "通道9-通道12") {
        index = 8;
        videoType = "9_12";
    } else if (name == "通道13-通道16") {
        index = 12;
        videoType = "13_16";
    }
    if (this->videoType != videoType) {
        this->videoType = videoType;
        change_video_4(index);
    }
}
void FormShow::show_video_6() {
    videoMax = false;
    QString videoType;
    int index = 0;
    QAction *action = static_cast<QAction *>(sender());
    QString name = action->text();
    if (name == "通道1-通道6") {
        index = 0;
        videoType = "1_6";
    } else if (name == "通道6-通道11") {
        index = 5;
        videoType = "6_11";
    } else if (name == "通道11-通道16") {
        index = 10;
        videoType = "11_16";
    }
    if (this->videoType != videoType) {
        this->videoType = videoType;
        change_video_6(index);
    }
}
void FormShow::show_video_8() {
    videoMax = false;
    QString videoType;
    int index = 0;
    QAction *action = static_cast<QAction *>(sender());
    QString name = action->text();
    if (name == "通道1-通道8") {
        index = 0;
        videoType = "1_8";
    } else if (name == "通道9-通道16") {
        index = 8;
        videoType = "9_16";
    }
    if (this->videoType != videoType) {
        this->videoType = videoType;
        change_video_8(index);
    }
}
void FormShow::show_video_9() {
    videoMax = false;
    QString videoType;
    int index = 0;
    QAction *action = static_cast<QAction *>(sender());
    QString name = action->text();
    if (name == "通道1-通道9") {
        index = 0;
        videoType = "1_9";
    } else if (name == "通道8-通道16") {
        index = 7;
        videoType = "8_16";
    }
    if (this->videoType != videoType) {
        this->videoType = videoType;
        change_video_9(index);
    }
}
void FormShow::show_video_16() {
    videoMax = false;
    QString videoType;
    int index = 0;
    videoType = "1_16";
    if (this->videoType != videoType) {
        this->videoType = videoType;
        change_video_16(index);
    }
}

//---------------------界面清空---------------------//
void FormShow::hide_video_all() {
    for (int i = 0; i < videoCount; i++) {
        ui->formshow_gridLayout->removeWidget(widgets.at(i));
        widgets.at(i)->setVisible(false);
    }
}

//---------------------界面选择---------------------//
void FormShow::change_video(int index, int flag) {
    int count = 0;
    int row = 0;
    int column = 0;
    for (int i = 0; i < videoCount; i++) {
        if (i >= index) {
            ui->formshow_gridLayout->addWidget(widgets.at(i), row, column);
            widgets.at(i)->setVisible(true);
            count++;
            column++;
            if (column == flag) {
                row++;
                column = 0;
            }
        }
        if (count == (flag * flag)) {
            break;
        }
    }
}
void FormShow::change_video_4(int index) {
    hide_video_all();
    change_video(index, 2);
}
void FormShow::change_video_6(int index) {
    hide_video_all();
    if (index == 0) {
        ui->formshow_gridLayout->addWidget(widgets.at(0), 0, 0, 2, 2);
        ui->formshow_gridLayout->addWidget(widgets.at(1), 0, 2, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(2), 1, 2, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(3), 2, 2, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(4), 2, 1, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(5), 2, 0, 1, 1);
        for (int i = 0; i < 6; i++) {
            widgets.at(i)->setVisible(true);
        }
    } else if (index == 5) {
        ui->formshow_gridLayout->addWidget(widgets.at(5), 0, 0, 2, 2);
        ui->formshow_gridLayout->addWidget(widgets.at(6), 0, 2, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(7), 1, 2, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(8), 2, 2, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(9), 2, 1, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(10), 2, 0, 1, 1);
        for (int i = 5; i < 11; i++) {
            widgets.at(i)->setVisible(true);
        }
    } else if (index == 10) {
        ui->formshow_gridLayout->addWidget(widgets.at(10), 0, 0, 2, 2);
        ui->formshow_gridLayout->addWidget(widgets.at(11), 0, 2, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(12), 1, 2, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(13), 2, 2, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(14), 2, 1, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(15), 2, 0, 1, 1);
        for (int i = 10; i < 16; i++) {
            widgets.at(i)->setVisible(true);
        }
    }
}
void FormShow::change_video_8(int index) {
    hide_video_all();
    if (index == 0) {
        ui->formshow_gridLayout->addWidget(widgets.at(0), 0, 0, 3, 3);
        ui->formshow_gridLayout->addWidget(widgets.at(1), 0, 3, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(2), 1, 3, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(3), 2, 3, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(4), 3, 3, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(5), 3, 2, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(6), 3, 1, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(7), 3, 0, 1, 1);
        for (int i = 0; i < 8; i++) {
            widgets.at(i)->setVisible(true);
        }
    } else if (index == 8) {
        ui->formshow_gridLayout->addWidget(widgets.at(8), 0, 0, 3, 3);
        ui->formshow_gridLayout->addWidget(widgets.at(9), 0, 3, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(10), 1, 3, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(11), 2, 3, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(12), 3, 3, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(13), 3, 2, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(14), 3, 1, 1, 1);
        ui->formshow_gridLayout->addWidget(widgets.at(15), 3, 0, 1, 1);
        for (int i = 8; i < 16; i++) {
            widgets.at(i)->setVisible(true);
        }
    }
}
void FormShow::change_video_9(int index) {
    hide_video_all();
    change_video(index, 3);
}
void FormShow::change_video_16(int index) {
    hide_video_all();
    change_video(index, 4);
}


//---------------------按钮功能---------------------//
void FormShow::on_frmshowpushButton_8_clicked() {
    videoMax = false;
    QString videoType;
    int index = 0;
    index = 0;
    videoType = "1_4";
    if (this->videoType != videoType) {
        this->videoType = videoType;
        change_video_4(index);
    }
}
void FormShow::on_frmshowpushButton_9_clicked() {
    videoMax = false;
    QString videoType;
    int index = 0;
    index = 0;
    videoType = "1_6";
    if (this->videoType != videoType) {
        this->videoType = videoType;
        change_video_6(index);
    }
}
void FormShow::on_frmshowpushButton_10_clicked() {
    videoMax = false;
    QString videoType;
    int index = 0;
    index = 0;
    videoType = "1_8";
    if (this->videoType != videoType) {
        this->videoType = videoType;
        change_video_8(index);
    }
}
void FormShow::on_frmshowpushButton_11_clicked() {
    videoMax = false;
    QString videoType;
    int index = 0;
    index = 0;
    videoType = "1_9";
    if (this->videoType != videoType) {
        this->videoType = videoType;
        change_video_9(index);
    }
}
void FormShow::on_frmshowpushButton_12_clicked() {
    videoMax = false;
    QString videoType;
    int index = 0;
    index = 0;
    videoType = "1_16";
    if (this->videoType != videoType) {
        this->videoType = videoType;
        change_video_16(index);
    }
}
void FormShow::on_frmshowpushButton_clicked() {
    QStringList filenames = QFileDialog::getOpenFileNames(
                                this, tr("open image file"),
                                "./", tr("Image files(*.bmp *.jpg *.pbm "
                                         "*.pgm *.png *.ppm *.xbm *.xpm);;"
                                         "All files (*.*)"));
    for (int i = 0; (i < filenames.size()) && (i < 16); ++i) {
        QString path = filenames.at(i);
        if (!path.isEmpty()) {
            QImage *img = new QImage(path);
            if ((img->isNull())) {
                QUIHelper::showMessageBoxError("打开图片错误！");
                delete img;
                return;
            }
            QLabel *lab = widgets.at(i);
            QSize laSize = lab->size();
            QImage img1 = img->scaled(laSize - QSize(5, 5), Qt::IgnoreAspectRatio);
            lab->setPixmap(QPixmap::fromImage(img1));
        }
    }
}
