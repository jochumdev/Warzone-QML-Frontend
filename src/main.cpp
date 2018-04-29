// See QString docs for them.
#define QT_USE_FAST_CONCATENATION
#define QT_USE_FAST_OPERATOR_PLUS

#include <src/Core/Framework/frame.h>

#include <QtWidgets/QApplication>

#include <QtCore/QTextCodec>
#include <QtCore/QStringList>

// Logging
#include <lib/WzLog/Logger.h>

#include <Core/Map/map.h>
#include <Core/Filesystem/filesystem.h>

#include <Frontend/wzhelper.h>
#include <Frontend/wzqmlview.h>
#include <Frontend/config.h>
#include <physfs.h>

/* Always use fallbacks on Windows */
#if defined(WZ_OS_WIN)
#  undef WZ_DATADIR
#endif

#if !defined(WZ_DATADIR)
#  define WZ_DATADIR "data"
#endif

#if defined(WZ_OS_WIN)
# define WZ_WRITEDIR "Warzone 2100 master"
#elif defined(WZ_OS_MAC)
# define WZ_WRITEDIR "Warzone 2100 master"
#else
# define WZ_WRITEDIR ".warzone2100-master"
#endif

int main(int argc, char *argv[])
{
    // make Qt treat all C strings in QMLFrontend as UTF-8
    // QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	
    QApplication app(argc, argv);
	
	// Sets a basic debugger up.
	debug_init();

	// Initializes default values for the configuration.
	config_init();

    // Create the logger instance and get a reference to it.
    WzLog::Logger& logger = WzLog::Logger::instance();
    logger.setLevelStatus(LOG_TRACE);

    // Add a console output destination to the logger.
    WzLog::LoggerDestination* debugDestination = new WzLog::LoggerDebugOutputDestination();
    logger.addDestination(debugDestination);    

    // Enable/Disable log components.
    WzLog::Logger::instance().setLevelStatus("fs", true);
    WzLog::Logger::instance().setLevelStatus("fs", true);
    WzLog::Logger::instance().setLevelStatus("imagemap", false);
    WzLog::Logger::instance().setLevelStatus("frontend", true);
    WzLog::Logger::instance().setLevelStatus("map", true);
	WzLog::Logger::instance().setLevelStatus("config", true);

    if (!FileSystem::init(argv[0], WZ_WRITEDIR, config.get("configDir").toString())) {
		return EXIT_FAILURE;
	}
	
	if (!FileSystem::scanDataDirs(config.get("dataDir").toString(), WZ_DATADIR))
	{
		return EXIT_FAILURE;
	}

    // Its important this line is before ParseCommandLine as the user
	// can override values by the cmd.
    config.loadConfig(PHYSFS_getWriteDir() + QString("config"));

	FileSystem::printSearchPath();

	/*** Initialize translations ***/
	initI18n();
	wzLog(LOG_MAIN) << QString("Using language: %1").arg(getLanguage());
	
	// Now run the frontend
	Frontend::WzQMLView view;
	view.run();
	
    app.exec();
	
    config.storeConfig(PHYSFS_getWriteDir() + QString("config"));

	FileSystem::exit();
	debug_exit();

	return EXIT_SUCCESS;
}
