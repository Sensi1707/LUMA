#include "ImageViewer.h"

#include <QWheelEvent>
#include <QScrollBar>
#include <QPropertyAnimation>
#include <QFrame>

// Konstruktor: Wird aufgerufen, wenn ein neues ImageViewer-Objekt erstellt wird.

ImageViewer::ImageViewer(QWidget* parent)
// Initialisierungsliste: Ruft den Konstruktor der Basisklasse QGraphicsView auf.
// 'parent' wird weitergegeben, um das Widget in die Qt-Objekthierarchie einzubinden.
	: QGraphicsView(parent)
{
	// Erstellt ein neues QGraphicsScene-Objekt auf dem Heap.
	// 'this' wird als Parent übergeben, damit Qt die Speicherverwaltung der Szene übernimmt.
	m_scene = new QGraphicsScene(this);

	// Weist dem ImageViewer (dem 'Betrachter') die gerade erstellte Szene zu.
	// Ab jetzt weiß der View, welchen Inhalt er darstellen soll.
	setScene(m_scene);

    viewport()->setContentsMargins(0, 0, 0, 0);
}

// Destruktor: Wird aufgerufen, wenn das ImageViewer-Objekt zerstört wird.
ImageViewer::~ImageViewer()
{

}

void ImageViewer::setImage(const QImage& image)
{
	m_scene->clear();
	QPixmap pixmap = QPixmap::fromImage(image);

    resetTransform();  // Alte Skalierung zurücksetzen

	float scaleX = static_cast<float>(width()) / pixmap.width();
	float scaleY = static_cast<float>(height()) / pixmap.height();
	
    float scaleFactor = std::min(scaleX, scaleY); // kleinster wert, damit nicht gestretcht & immer gleiches Seitenverhältnis

    scale(scaleFactor, scaleFactor);

	m_scene->addPixmap(pixmap);
}

void ImageViewer::smoothScroll(QScrollBar* scrollBar, int delta)
{
    QPropertyAnimation* anim = new QPropertyAnimation(scrollBar, "value");
    anim->setDuration(150); // Dauer anpassen
    anim->setStartValue(scrollBar->value());
    anim->setEndValue(scrollBar->value() + delta);
    anim->setEasingCurve(QEasingCurve::OutQuad);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void ImageViewer::wheelEvent(QWheelEvent* event)
{
    // 1. Fall: STRG gedrückt -> Horizontal scrollen
    if (event->modifiers() & Qt::ControlModifier) {
		if (event->angleDelta().y() > 0) { // nach oben scrollen
			horizontalScrollBar()->setValue(horizontalScrollBar()->value() - 20); // 20 Pixel nach links scrollen
        }
		else { // nach unten scrollen
			horizontalScrollBar()->setValue(horizontalScrollBar()->value() + 20); // 20 Pixel nach rechts scrollen
        }
    }

    // 2. Fall: SHIFT gedrückt -> Vertikal scrollen
    else if (event->modifiers() & Qt::ShiftModifier) {
		if (event->angleDelta().y() > 0) { // nach oben scrollen
			verticalScrollBar()->setValue(verticalScrollBar()->value() - 20); // 20 Pixel nach oben scrollen
        }
		else { // nach unten scrollen
			verticalScrollBar()->setValue(verticalScrollBar()->value() + 20); // 20 Pixel nach unten scrollen
        }
    }
    
    // 3. Fall: Keine Taste -> Zoomen
    else {
		qreal currentScale = transform().m11(); // Aktuelle Skalierung abrufen
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse); // Wichtig für intuitives Zoomen

        if (event->angleDelta().y() > 0) { // Hineinzoomen
            if (currentScale < 100.0) { // Obergrenze prüfen
                scale(1.2, 1.2);
            }
        }
        else { // Herauszoomen
            if (currentScale > 0.1) { // Untergrenze prüfen
                scale(1.0 / 1.2, 1.0 / 1.2);
            }
        }
    }

    event->accept(); // Event als verarbeitet markieren
}
