#include <QtWidgets>

#include "options.h"
//#include "SimpleCppTextFileHandler/file.hpp"

Options::Options()
{
    language = new QLineEdit("eng");
    QLabel* languageLabel = new QLabel("OCR language:");
    tempFilename = new QLineEdit("__ScreenshotOCRTemp.png");
    QLabel* tempFilenameLabel = new QLabel("Temporary Filename:");
    removeLinebreaks = new QCheckBox("Remove linebreaks");
    rLBcheckForHyphens = new QCheckBox("When removing linebreaks, check for hyphens?");

    mainLayout = new QVBoxLayout(this);

   
    mainLayout->addWidget(languageLabel);
    mainLayout->addWidget(language);
    mainLayout->addWidget(tempFilenameLabel);
    mainLayout->addWidget(tempFilename);
    mainLayout->addWidget(removeLinebreaks);
    mainLayout->addWidget(rLBcheckForHyphens);
   

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
