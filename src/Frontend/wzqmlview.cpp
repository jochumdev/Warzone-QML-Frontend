/*
	This file is part of Warzone 2100.
	Copyright (C) 2011  Warzone 2100 Project

	Warzone 2100 is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 2 of the License, or
	(at your option) any later version.

	Warzone 2100 is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with Warzone 2100; if not, write to the Free Software
	Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/
/**
 * @file wzqmlview.h
 *
 * The launchers Declarative View,
 */

// Self
#include "wzqmlview.h"

// framework - logging
#include <src/Core/Framework/frame.h>


// Imagemap
#include <lib/Imagemap/loader.h>

// Image map to qml proxy.
#include "imageprovider.h"

// WzHelper - QML<->C++ Helper, gets registered as WZ
#include "wzhelper.h"

// Configuration
#include <src/Core/confighandler.h>

// Qt Gui for the quit signal.
#include <QGuiApplication>

// Qt Declarative

#include <QQmlEngine>
#include <QQmlContext>

#include <QQuickView>

#ifdef WZ_WS_X11
#   include <QX11Info>
#   include <X11/extensions/Xrandr.h>
#endif

const int LOG_FRONTEND = WzLog::Logger::instance().addLoggingLevel("frontend", false);

namespace Frontend {

class WzQMLViewPrivate
{
public:
    WzQMLViewPrivate() :
        improvider(0) {}

	void init();

    ImagemapProvider* improvider;
	QStringList resolutions;
};


WzQMLView::WzQMLView(QWindow *parent)
    : QQuickView(parent)
{
	d = new WzQMLViewPrivate();
	wzhelper = new WzHelper(this);
	d->init();
}

WzQMLView::~WzQMLView()
{
	delete wzhelper;
	delete d;
}

void WzQMLViewPrivate::init()
{
	wzLog(LOG_FRONTEND) << "Loading the imagemaps.";
	// Add data/frontend/images/imagemap.js to the imagemap loader
    if (!Imagemap::Loader::instance().addImagemap("wz:/frontend/images/imagemap.js"))
	{
		wzLog(LOG_FATAL) << "Failed to load Imagemap: frontend/images/imagemap.js!";
		qFatal("%s", qPrintable(Imagemap::Loader::instance().errorString()));
	}

	qmlRegisterType<WzHelper>("Warzone",1,0,"Wz");

	improvider = new ImagemapProvider();
}

void WzQMLView::run(const QString loadScreen, const QString loadMenu)
{
    setResizeMode(QQuickView::SizeRootObjectToView);

	engine()->addImageProvider("imagemap", d->improvider);
	rootContext()->setContextProperty("wz", wzhelper);
    setSource(QUrl("wz:/frontend/main.qml"));

    QObject::connect(engine(), SIGNAL(quit()), QGuiApplication::instance(), SLOT(quit()));

	if (!loadScreen.isEmpty())
	{
		rootContext()->setContextProperty("gLoadScreen", loadScreen);
	}
	else
	{
		rootContext()->setContextProperty("gLoadScreen", "screens/menuScreen.qml");
	}

	if (!loadMenu.isEmpty())
	{
		rootContext()->setContextProperty("gLoadMenu", loadMenu);
	}
	else
	{
		rootContext()->setContextProperty("gLoadMenu", "menu/main.qml");
	}

	int w, h;
	// Setup Fullscreen/window mode.
	w = config.get("width").toInt();
	h = config.get("height").toInt();

	wzLog(LOG_FRONTEND) << "show, size:" << w << "x" << h;

	if (config.get("fullscreen").toBool())
	{
		resize(w, h);
		showFullScreen();
	}
	else
	{
		show();
        setMinimumHeight(h);
        setMinimumWidth(w);
	}
}

const QStringList& WzQMLView::getAvailableResolutions() const
{
    if (!d->resolutions.isEmpty())
    {
        return d->resolutions;
    }

#ifdef Q_OS_UNIX
    XRRScreenConfiguration *config = XRRGetScreenInfo(QX11Info::display(), RootWindow(QX11Info::display(), QX11Info::appScreen()));
    int sizeCount = 0;
    XRRScreenSize *sizes = XRRSizes(QX11Info::display(), 0, &sizeCount);
    for (int i = 0; i < sizeCount; i++)
    {
        d->resolutions.append(QString("%1 x %2").arg(sizes[i].width).arg(sizes[i].height));
    }
    XRRFreeScreenConfigInfo(config);
#endif
// 
// 	QList<QSize> res(d->viewPort->availableResolutions());
// 
// 	foreach(QSize resSize, res)
// 	{
// 		d->resolutions.append(QString("%1 x %2")
// 							.arg(resSize.width())
// 							.arg(resSize.height()));
// 	}

	return d->resolutions;
}

} // namespace Frontend
