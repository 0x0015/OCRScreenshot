#include <QtWidgets>

#include "options.h"
//#include "SimpleCppTextFileHandler/file.hpp"

Options::Options()
{
    language = new QLineEdit("eng");
    QLabel* languageLabel = new QLabel("OCR language:");
    tempFilename = new QLineEdit("__ScreenshotOCRTemp.png");
    QLabel* tempFilenameLabel = new QLabel("Temporary Filename:");

    mainLayout = new QVBoxLayout(this);

   
    mainLayout->addWidget(languageLabel);
    mainLayout->addWidget(language);
     mainLayout->addWidget(tempFilenameLabel);
    mainLayout->addWidget(tempFilename);
   

    setWindowTitle(tr("Screenshot"));
    resize(300, 200);

    show();
    hide();
}


void Options::on_show_hide(){
	if(isVisible()){
		hide();
	}else{
		show();
	}
}
