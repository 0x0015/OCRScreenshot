

 #ifndef OPTIONS_H
 #define OPTIONS_H

 #include <QPixmap>
 #include <QWidget>
 #include <QPainter>
 #include <QKeyEvent>
 #include <QLineEdit>
 
 class QCheckBox;
 class QGridLayout;
 class QGroupBox;
 class QHBoxLayout;
 class QLabel;
 class QPushButton;
 class QSpinBox;
 class QVBoxLayout;

 class Options : public QWidget
 {
     Q_OBJECT

 public:
	Options();
	void on_show_hide();
     QLineEdit* language;
     QLineEdit* tempFilename;
     QCheckBox* removeLinebreaks;
     QCheckBox* rLBcheckForHyphens;
 protected:
	
 private slots:
     //void on_show_hide(QSystemTrayIcon::ActivationReason reason);
 private:
     void createButtonsLayout();

     //QLabel *screenshotLabel;
     //QPushButton *newScreenshotButton;
     //QPushButton *saveScreenshotButton;
     //QPushButton *quitScreenshotButton;
     //QPainter* SelectionScreen;


     QVBoxLayout *mainLayout;
     //QHBoxLayout *buttonsLayout;
 };

 #endif
