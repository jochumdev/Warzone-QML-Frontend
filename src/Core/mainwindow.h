#ifndef CORE_MAINWINDOW_H
#define CORE_MAINWINDOW_H

#include <lib/qtgame/qtgame.h>

// class MainWindow : public QtGameWidget
// {
//     Q_OBJECT
//
// private:
//     void loadCursor(CURSOR cursor, int x, int y, QImageReader &buffer);
//     void mouseMoveEvent(QMouseEvent *event);
//     void mousePressEvent(QMouseEvent *event);
//     void mouseReleaseEvent(QMouseEvent *event);
//     void wheelEvent(QWheelEvent *event);
//     void keyPressEvent(QKeyEvent *event);
//     void keyReleaseEvent(QKeyEvent *event);
//     void inputMethodEvent(QInputMethodEvent *event);
//     void realHandleKeyEvent(QKeyEvent *event, bool pressed);
//     void focusOutEvent(QFocusEvent *event);
//     MOUSE_KEY_CODE buttonToIdx(Qt::MouseButton button);
//
//     QCursor *cursors[CURSOR_MAX];
//     QTimer *timer;
//     QTime tickCount;
//     QFont regularFont, boldFont, smallFont, scaledFont;
//     bool notReadyToPaint;  ///< HACK Don't draw during initial show(), since some global variables apparently aren't set up.
//     static MainWindow *myself;
//
// public:
//     MainWindow(QSize resolution, const QGLFormat &format, QWidget *parent = 0);
//     ~MainWindow();
//     void initializeGL();
//     void resizeGL(int w, int h);
//     void paintGL();
//     static MainWindow *instance();
//     void setCursor(CURSOR index);
//     void setCursor(QCursor cursor);
//     void setFontType(enum iV_fonts FontID);
//     void setFontSize(float size);
//     int ticks() { return tickCount.elapsed(); }
//     void setReadyToPaint() { notReadyToPaint = false; }
//     void drawPixmap(int XPos, int YPos, QPixmap *pix);
//
// public slots:
//     void tick();
//     void close();
// };

#endif // #ifndef CORE_MAINWINDOW_H