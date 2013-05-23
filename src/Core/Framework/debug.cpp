/*
	This file is part of Warzone 2100.
	Copyright (C) 1999-2004  Eidos Interactive
	Copyright (C) 2005-2011  Warzone 2100 Project

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
/*
 * Debug.c
 *
 * Various debugging output functions.
 *
 */

#include "frame.h"

#include <QtGui/QMessageBox>

#include <string.h>
#include <stdio.h>
#include <time.h>
#include "string_ext.h"
// #include "lib/gamelib/gtime.h"

#include <lib/WzLog/Logger.h>

extern void NotifyUserOfError(char *);		// will throw up a notifier on error

#define MAX_LEN_LOG_LINE 512

char last_called_script_event[MAX_EVENT_NAME_LEN];
UDWORD traceID = -1;

#ifdef DEBUG
bool assertEnabled = true;
#else
bool assertEnabled = false;
#endif

const int LOG_MAIN = WzLog::Logger::instance().addLoggingLevel("main", false);
const int LOG_SOUND = WzLog::Logger::instance().addLoggingLevel("sound", false);
const int LOG_VIDEO = WzLog::Logger::instance().addLoggingLevel("video", false);
const int LOG_WZ = WzLog::Logger::instance().addLoggingLevel("wz", false);
const int LOG_3D = WzLog::Logger::instance().addLoggingLevel("3d", false);
const int LOG_TEXTURE = WzLog::Logger::instance().addLoggingLevel("texture", false);
// const int LOG_NET = WzLog::Logger::instance().addLoggingLevel("net", false);
const int LOG_MEMORY = WzLog::Logger::instance().addLoggingLevel("memory", false);
const int LOG_SCRIPT = WzLog::Logger::instance().addLoggingLevel("script", false);
const int LOG_MOVEMENT = WzLog::Logger::instance().addLoggingLevel("movement", false);
const int LOG_ATTACK = WzLog::Logger::instance().addLoggingLevel("attack", false);
const int LOG_FOG = WzLog::Logger::instance().addLoggingLevel("fog", false);
const int LOG_SENSOR = WzLog::Logger::instance().addLoggingLevel("sensor", false);
const int LOG_GUI = WzLog::Logger::instance().addLoggingLevel("gui", false);
const int LOG_MAP = WzLog::Logger::instance().addLoggingLevel("map", false);
const int LOG_SAVE = WzLog::Logger::instance().addLoggingLevel("save", false);
const int LOG_SYNC = WzLog::Logger::instance().addLoggingLevel("sync", false);
const int LOG_DEATH = WzLog::Logger::instance().addLoggingLevel("death", false);
const int LOG_LIFE = WzLog::Logger::instance().addLoggingLevel("life", false);
const int LOG_GATEWAY = WzLog::Logger::instance().addLoggingLevel("gateway", false);
const int LOG_MSG = WzLog::Logger::instance().addLoggingLevel("msg", false);
const int LOG_TERRAIN = WzLog::Logger::instance().addLoggingLevel("terrain", false);
const int LOG_FEATURE = WzLog::Logger::instance().addLoggingLevel("feature", false);
const int LOG_INPUT = WzLog::Logger::instance().addLoggingLevel("input", false);
const int LOG_CONSOLE = WzLog::Logger::instance().addLoggingLevel("console", false);

// MSVC specific rotuines to set/clear allocation tracking
#if defined(WZ_CC_MSVC) && defined(DEBUG)
void debug_MEMCHKOFF(void)
{
	// Disable allocation tracking
	int flags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	flags &= ~_CRTDBG_ALLOC_MEM_DF;
	_CrtSetDbgFlag(flags);
}
void debug_MEMCHKON(void)
{
	// Enable allocation tracking
	int flags = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
	flags |= _CRTDBG_ALLOC_MEM_DF;
	_CrtSetDbgFlag(flags);
}
void debug_MEMSTATS(void)
{
	_CrtMemState state;
	_CrtMemCheckpoint(&state);
	_CrtMemDumpStatistics(&state);
}
#endif

void debug_init(void)
{
	/*** Initialize the debug subsystem ***/
#if defined(WZ_CC_MSVC) && defined(DEBUG)
	int tmpDbgFlag;
	_CrtSetReportMode( _CRT_WARN, _CRTDBG_MODE_DEBUG ); // Output CRT info to debugger

	tmpDbgFlag = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG ); // Grab current flags
# if defined(DEBUG_MEMORY)
	tmpDbgFlag |= _CRTDBG_CHECK_ALWAYS_DF; // Check every (de)allocation
# endif // DEBUG_MEMORY
	tmpDbgFlag |= _CRTDBG_ALLOC_MEM_DF; // Check allocations
	tmpDbgFlag |= _CRTDBG_LEAK_CHECK_DF; // Check for memleaks
	_CrtSetDbgFlag( tmpDbgFlag );
#endif // WZ_CC_MSVC && DEBUG

#if defined(Q_OS_WIN) && defined(DEBUG_INSANE)
    WzLog::LoggerDestination* debugDestination = new WzLog::LoggerWinDebugDestition();
    WzLog::Logger::instance().addDestination(debugDestination);
#endif // WZ_OS_WIN && DEBUG_INSANE

    WzLog::Logger::instance().setPopupTitleBody("Warzone has detected a problem.",
                                         "A non fatal error has occurred.\n\n%1\n\n");

#if defined(WZ_OS_WIN)
    WzLog::Logger::instance().setFatalTitleBody(
        "Warzone has terminated unexpectedly",
        "%1\n\nPlease check your stderr.txt file in the same directory as the program file for more details. \
        \nDo not forget to upload both the stderr.txt file and the warzone2100.rpt file in your bug reports!");
#elif defined(WZ_OS_MAC)
    WzLog::Logger::instance().setFatalTitleBody(
        "Warzone has terminated unexpectedly",
        "%1\n\nPlease check your logs for more details."
        "\n\nRun Console.app, search for \"wz2100\", and copy that to a file."
        "\n\nIf you are on 10.4 (Tiger) or 10.5 (Leopard) the crash report"
        " is in ~/Library/Logs/CrashReporter."
        " If you are on 10.6 (Snow Leopard), it is in"
        "\n~/Library/Logs/DiagnosticReports."
        "\n\nDo not forget to upload and attach those to a bug report at http://developer.wz2100.net/newticket"
        "\nThanks!");
#else
    WzLog::Logger::instance().setFatalTitleBody(
        "Warzone has terminated unexpectedly",
        "%1\n\nPlease check your logs for more details.");
#endif

#ifdef DEBUG
    WzLog::Logger::instance().setLevelStatus(LOG_WARNING, true);
#endif
}


void debug_exit(void)
{
    // FIXME: add unloading code to the logger.
}

void _realObjTrace(int id, const char *function, const char *str, ...)
{
	char vaBuffer[MAX_LEN_LOG_LINE];
	char outputBuffer[MAX_LEN_LOG_LINE];
	va_list ap;

	va_start(ap, str);
	vssprintf(vaBuffer, str, ap);
	va_end(ap);

	ssprintf(outputBuffer, "[%6d]: [%s] %s", id, function, vaBuffer);
    WzLog::Logger::instance().write(outputBuffer);
}



void debugDisableAssert()
{
	assertEnabled = false;
}
