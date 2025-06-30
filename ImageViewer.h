#pragma once

#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QImage>
#include <QPixmap>

class ImageViewer : public QGraphicsView
{
	Q_OBJECT;

public:
	ImageViewer(QWidget* parent = nullptr); // Konstruktor
	~ImageViewer(); // Dekonstruktor

	void setImage(const QImage& image);


private:
	QGraphicsScene* m_scene;

	void smoothScroll(QScrollBar* scrollBar, int delta);
protected:
	void wheelEvent(QWheelEvent* event) override; // 'override' ist guter Stil

};