#ifndef __SRC_CORE_CONFIG_WZHEADERS_H__
#define __SRC_CORE_CONFIG_WZHEADERS_H__

/**
 * For Config::init() from src/warzoneconfig.h 35:50
 */
enum FMV_MODE
{
	FMV_FULLSCREEN,
	FMV_1X,
	FMV_2X,
	FMV_MAX
};

enum FSAA_LEVEL
{
	FSAA_OFF,
	FSAA_2X,
	FSAA_4X,
	FSAA_8X,
	FSAA_MAX
};

/**
 * For Config::init() from lib/sequence/sequence.h 25:29
 */
typedef enum {
    SCANLINES_OFF,
    SCANLINES_50,
    SCANLINES_BLACK
} SCANLINE_MODE;

/**
 * For Config::init() from src/ai.h 35:37
 */
#define NO_ALLIANCES		0			//alliance possibilities for games.
#define ALLIANCES			1
#define	ALLIANCES_TEAMS		2			//locked teams

/**
 * For Config::init() from src/multiplay.h 108:110
 */
#define CAMP_CLEAN				0			// campaign subtypes
#define CAMP_BASE				1
#define CAMP_WALLS				2

/**
 * For Config::init() from src/multiplay.h 114:116
 */
#define LEV_LOW					400			// how many points to allocate for res levels???
#define LEV_MED					700
#define LEV_HI					1000

/**
 * For Config::init() from src/difficulty.h 24:32
 */
enum DIFFICULTY_LEVEL
{
	DL_EASY,
	DL_NORMAL,
	DL_HARD,
	DL_INSANE,
	DL_TOUGH,
	DL_KILLER
};

#endif // __SRC_CORE_CONFIG_WZHEADERS_H__