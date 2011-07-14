#include <QtGui/QApplication>

// WZ
#include <QtCore/QTextCodec>

// WZ OpenGL
#include <QtOpenGL/QGLWidget>

// Logging
#include <lib/WzLog/Log.h>

// QML Viewer
#include <lib/Imagemap/loader.h>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeContext>

#include <Core/Filesystem/filesystem.h>

#include <Frontend/wzhelper.h>
#include <Frontend/qmlimagemapprovider.h>

#include <Core/Map/map.h>

// See QString docs for them.
#define QT_USE_FAST_CONCATENATION
#define QT_USE_FAST_OPERATOR_PLUS

// Test translations
// #include <locale.h>
// #include <libintl.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    WzLog::init();
    WzLog::Logger::instance().setLevelStatus("fs", true);
    WzLog::Logger::instance().setLevelStatus("imagemap", true);
    WzLog::Logger::instance().setLevelStatus("frontend", true);
    WzLog::Logger::instance().setLevelStatus("map", true);

    FileSystem::init(argv[0], ".warzone2100-master");
    FileSystem::scanDataDirs();

    // make Qt treat all C strings in Warzone as UTF-8
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    // From wz: setup opengl
    QGL::setPreferredPaintEngine(QPaintEngine::OpenGL);
    QGLFormat format;
    format.setDoubleBuffer(true);
    format.setAlpha(true);
    format.setSampleBuffers(true);
    format.setSamples(8);
    QGLWidget *glWidget = new QGLWidget(format);
    if (!glWidget->isValid())
    {
        qFatal("Cannot create a GL Context!");
    }

    // Add data/frontend/images/imagemap.js to the imagemap loader
    if (!Imagemap::Loader::instance().addImagemap("wz::frontend/images/imagemap.js"))
    {
        // abort() on errors.
        qFatal("%s", qPrintable(Imagemap::Loader::instance().errorString()));
    }

    // Test translations
//     setlocale(LC_MESSAGES, "fr");
//     const char* dir = bindtextdomain("warzone2100", "/usr/local/share/locale");
//     if (!dir)
//     {
//         qFatal("Binding gettext failed.");
//     }
//
//     bind_textdomain_codeset("warzone2100", "UTF-8");
//     textdomain("warzone2100");

    // Now setup the QML viewer
    QDeclarativeView *view = new QDeclarativeView;
    view->setViewport(glWidget);
    view->setResizeMode(QDeclarativeView::SizeRootObjectToView);

    Frontend::QMLImagemapProvider* improvider = new Frontend::QMLImagemapProvider();
    view->engine()->addImageProvider("imagemap", improvider);

    Frontend::WzHelper wzHelper("wz::config");
    view->rootContext()->setContextProperty("wz", &wzHelper);

    view->setSource(QUrl("wz::frontend/main.qml"));
    view->show();

    return app.exec();
}
