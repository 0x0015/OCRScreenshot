

 #ifndef SCREENSHOT_H
 #define SCREENSHOT_H

 #include <QPixmap>
 #include <QWidget>
 #include <QPainter>
 #include <QKeyEvent>
 #include <QSystemTrayIcon>
 #include <QHotkey>
 #include <tesseract/baseapi.h>
 #include <tesseract/strngs.h>
 #include <leptonica/allheaders.h>
 #include <iostream>
 #include "options.h"
 
 class QCheckBox;
 class QGridLayout;
 class QGroupBox;
 class QHBoxLayout;
 class QLabel;
 class QPushButton;
 class QSpinBox;
 class QVBoxLayout;

 class Screenshot : public QWidget
 {
     Q_OBJECT

 public:
     Screenshot();
     int mousex = -1;
     int mousey = -1;
     int mousex1 = -1;
     int mousey1 = -1;
     int mousex2 = -1;
     int mousey2 = -1;
     bool mousepressed;
     void takeNewScreenshot();
     void setOptions(Options* o);
 protected:
     void resizeEvent(QResizeEvent *event);

 private slots:
     //void newScreenshot();
     void saveScreenshot();
     void shootScreen();
     void quit();
     void exit();
     void on_show_hide();
     //void on_show_hide(QSystemTrayIcon::ActivationReason reason);
 private:
     void createButtonsLayout();
     QPushButton *createButton(const QString &text, QWidget *receiver,
                               const char *member);
     std::string OCRImage();

     void paintEvent(QPaintEvent*);

     QPixmap originalPixmap;

     //QLabel *screenshotLabel;
     //QPushButton *newScreenshotButton;
     //QPushButton *saveScreenshotButton;
     //QPushButton *quitScreenshotButton;
     QPainter* SelectionScreen;

     QSystemTrayIcon* trayIcon;

     Options* options = 0;

     void mousePressEvent(QMouseEvent* event);
     void mouseMoveEvent(QMouseEvent* event);
     void mouseReleaseEvent(QMouseEvent* event);
     void keyPressEvent(QKeyEvent* event);
     QVBoxLayout *mainLayout;
     //QHBoxLayout *buttonsLayout;
 };

 #endif
