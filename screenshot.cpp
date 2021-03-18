#include <QtWidgets>

#include "screenshot.h"
#include "SimpleCppTextFileHandler/file.hpp"

Screenshot::Screenshot()
{
    //setStyleSheet("background:transparent;");
    //setAttribute(Qt::WA_NoSystemBackground, true);
    //setAttribute(Qt::WA_TranslucentBackground, true);
    //setWindowFlags(Qt::FramelessWindowHint);
    
    trayIcon = new QSystemTrayIcon(QIcon(":/Icon.png"), this);

    //connect( trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(on_show_hide(QSystemTrayIcon::ActivationReason)) );

    QAction *quit_action = new QAction( "Exit", trayIcon );
    connect( quit_action, SIGNAL(triggered()), this, SLOT(exit()) );

    QAction *hide_action = new QAction( "Show/Hide Options", trayIcon );
    connect( hide_action, SIGNAL(triggered()), this, SLOT(on_show_hide()) );

    QMenu *tray_icon_menu = new QMenu;
    tray_icon_menu->addAction( hide_action );
    tray_icon_menu->addAction( quit_action );

    trayIcon->setContextMenu( tray_icon_menu );

    trayIcon->show();
    
    this->setMouseTracking(true);

    //QTimer::singleShot(0, this, SLOT(showFullScreen()));
    

    const QRect screenGeometry = screen()->geometry();
    //screenshotLabel->setMinimumSize(screenGeometry.width() / 8, screenGeometry.height() / 8);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    //mainLayout->addLayout(buttonsLayout);

    shootScreen();

    setWindowTitle(tr("Screenshot"));
    resize(300, 200);

    showFullScreen();
    hide();
}



void Screenshot::on_show_hide()
{
	if(options != 0){
		options->on_show_hide();
	}
}

void Screenshot::resizeEvent(QResizeEvent * /* event */)
{
    QSize scaledSize = originalPixmap.size();
    //scaledSize.scale(screenshotLabel->size(), Qt::KeepAspectRatio);
    //if (scaledSize != screenshotLabel->pixmap(Qt::ReturnByValue).size())
    //    updateScreenshotLabel();
}

void Screenshot::saveScreenshot()
{  
    const QString fileName = "__ScreenshotOCRTemp.png";
    QPixmap croppedPixMap = originalPixmap.copy(mousex1, mousey1, mousex2-mousex1, mousey2-mousey1);
    if (!croppedPixMap.save(fileName)) {
        QMessageBox::warning(this, tr("Save Error"), tr("The image could not be saved to \"%1\".")
                             .arg(QDir::toNativeSeparators(fileName)));
    }
}

void deletePreviousScreenshot(){
		if(fileExists("__ScreenshotOCRTemp.png")){
			deleteFile("__ScreenshotOCRTemp.png");
		}
}

std::string Screenshot::OCRImage(){
    //std::string tesseractEnv = std::string(getenv("TESSDATA_PREFIX"));
    const char* lang = options->language->text().toStdString().c_str();
    const char* filename = "__ScreenshotOCRTemp.png";

    tesseract::TessBaseAPI* tess = new tesseract::TessBaseAPI(); // debug stopped here on this line
    tess->Init(NULL, lang, tesseract::OEM_DEFAULT);
    tess->SetPageSegMode(tesseract::PSM_AUTO);
    //tess->SetInputName(filename);
    Pix* pix = pixRead(filename);
    tess->SetImage(pix);
    std::string outText = tess->GetUTF8Text();
    tess->End();
    std::cout<<outText<<std::endl;
    return(outText);
    //FILE* fin = fopen(filename, "rb");
    //if (fin == NULL)
    //{
    //    std::cout << "Cannot open " << filename << std::endl;
    //    return("");
    //}
    //fclose(fin);

    //const char* text;
    //tesseract::TessTextRenderer textRenderer(text);
 
  
    //if (tess.ProcessPages(filename, NULL, 0, &textRenderer))
    //{  
       // std::cout << text.string() << std::endl;
//	   
//	return(text.string());
   // }
    return("");
}

void copyToClipboard(std::string text){
	QClipboard* clipboard = QApplication::clipboard();
	QString qtext = QString::fromStdString(text);
	if(qtext == ""){
		std::cout<<"Failed to make text into a qstring"<<std::endl;
	}
	clipboard->setText(qtext, QClipboard::Clipboard);
	
	if (clipboard->supportsSelection()) {
		clipboard->setText(qtext, QClipboard::Selection);
	}
}

void Screenshot::shootScreen()
{
    //QScreen *screen = QGuiApplication::primaryScreen();
    QScreen* screen = QGuiApplication::screenAt(QCursor::pos());
    //if (const QWindow *window = windowHandle())
    //    screen = window->screen();
    if (!screen)
        return;

    originalPixmap = screen->grabWindow(0);
    //updateScreenshotLabel();

    //newScreenshotButton->setDisabled(false);
    
}

void Screenshot::takeNewScreenshot(){

	shootScreen();
	showFullScreen();
	
}

void Screenshot::paintEvent(QPaintEvent*){
	QPainter painter(this);
	painter.drawPixmap(0,0,originalPixmap);
	
	painter.setCompositionMode(QPainter::RasterOp_SourceXorDestination);
	painter.setPen(QPen(Qt::white, 0));
	

	if(this->mousex1 >= 0 && this->mousey1 >= 0){
		//painter.drawRect(mousex1, mousey1, mousex-mousex1, mousey-mousey1);
		if(this->mousex2 >= 0 && this->mousey2 >= 0){
			//painter.drawRect(mousex1, mousey1, mousex2-mousex1, mousey2-mousey1);
		}else{
			//painter.drawRect(mousex1, mousey1, mousex-mousex1, mousey-mousey1);
			painter.drawLine(mousex1, 0, mousex1, originalPixmap.height());
			painter.drawLine(0, mousey1, originalPixmap.width(), mousey1);
		}
	}
	painter.drawLine(mousex, 0, mousex, originalPixmap.height());
	painter.drawLine(0, mousey, originalPixmap.width(), mousey);
}

void Screenshot::mousePressEvent(QMouseEvent* event){
	this->mousex = event->x();
	this->mousey = event->y();
	this->mousex1 = this->mousex;
	this->mousey1 = this->mousey;
	this->mousex2 = -1;
	this->mousey2 = -1;
	update();	
}

void Screenshot::mouseMoveEvent(QMouseEvent* event){
	this->mousex = event->x();
	this->mousey = event->y();
	update();
}

void Screenshot::quit(){
	//exit(0);
	showNormal();
	hide();
	//QTimer::singleShot(1250, this, SLOT(hide()));
	//showMinimized();
	//this->close();
}

void Screenshot::exit(){
	QApplication::quit();
}

std::string cutLineBreaks(std::string text, bool should, bool checkForHiphens){
	if(should){
		std::string output = "";
		for(int i=0;i<text.length();i++){
			if(text.substr(i, 1) == "\n"){
				if(i>=1 && checkForHiphens){
					if(text.substr(i-1, 1) != "-"){
						output = output + " ";
						i++;
					}
				}else if(i+1<text.length() && checkForHiphens){
					if(text.substr(i+1, 1) != "-"){
						output = output + " ";
						i++;
					}
				}else{
					output = output + " ";
				}
			}else{
				output = output + text.substr(i, 1);
			}
		}
		return(output);
	}
	return(text);
}

void Screenshot::mouseReleaseEvent(QMouseEvent* event){
	this->mousex = event->x();
	this->mousey = event->y();
	this->mousex2 = this->mousex;
	this->mousey2 = this->mousey;
	//update();
	quit();
	saveScreenshot();
	bool removeLB = options->removeLinebreaks->checkState() == Qt::Checked;
	bool removeLBH = options->rLBcheckForHyphens->checkState() == Qt::Checked;
	copyToClipboard(cutLineBreaks(OCRImage(), removeLB, removeLBH));
	deletePreviousScreenshot();
	//QTimer::singleShot(1, this, SLOT(quit()));

}

void Screenshot::keyPressEvent(QKeyEvent* event){
	if(event->key() == Qt::Key_Escape){
		quit();
	}
}

void Screenshot::setOptions(Options* o){
	options = o;
}
