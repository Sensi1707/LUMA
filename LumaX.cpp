#include "LumaX.h"
#include "ImageViewer.h"
#include <QFileDialog>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QLayout>

// Konstruktor
LumaX::LumaX(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    mdiArea = new QMdiArea;
    setCentralWidget(mdiArea);

    connect(ui.actionOpen, &QAction::triggered, this, &LumaX::onFileOpen); // connected Menü und funktion onFileOpen

    setWindowTitle("LumaX - Development "); // Setzt den Fenstertitel   

    this->setWindowState(Qt::WindowMaximized); //Maximizes the window

}

// Destruktor
LumaX::~LumaX()
{

}

// Funktion zum Öffnen einer Datei
void LumaX::onFileOpen()
{
    QString filename = QFileDialog::getOpenFileName(
        this, // parent
        "Open Image", // title
        QDir::homePath(), // directory
		"Images(*.png *.jpg *.jpeg);;All Files (*)" // filetype filter
    );

    if (filename.isEmpty())
    {
        qDebug() << "no file selected";
		qWarning() << "No file selected. Please select a file.";
        return;
    }
    
    QImage image(filename); // Bild laden

    if (image.isNull())
    {
        qDebug() << "Failed to load image: " << filename;
        qWarning() << "Failed to load image: " << filename;
        return;
    }

    ImageViewer* viewer = new ImageViewer;

	viewer->setImage(image); // Bild im Viewer setzen
	
    QMdiSubWindow* subWindow = mdiArea->addSubWindow(viewer);
    
    subWindow->setWindowTitle(QFileInfo(filename).fileName()); // Setzt den Fenstertitel des Viewers
    subWindow->setStyleSheet(R"(
    QScrollBar:vertical {
        width: 8px;
        margin: 0px 0px 0px 0px;
    }
    QScrollBar::handle:vertical {
        background: gray;
        min-height: 20px;
        border-radius: 4px;
    }
    QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
        height: 0px;
    }
    QScrollBar:horizontal {
        height: 8px;
        margin: 0px 0px 0px 0px;
    }
    QScrollBar::handle:horizontal {
        background: gray;
        min-width: 20px;
        border-radius: 4px;
    }
    QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
        width: 0px;
    }
)");
    subWindow->show(); // Viewer anzeigen
}