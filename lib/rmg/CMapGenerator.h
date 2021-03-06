
/*
 * CMapGenerator.h, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */

#pragma once

#include "../GameConstants.h"
#include "../CRandomGenerator.h"
#include "CMapGenOptions.h"
#include "CRmgTemplateZone.h"
#include "../int3.h"

class CMap;
class CRmgTemplate;
class CRmgTemplateZone;
class CMapGenOptions;
class CTerrainViewPatternConfig;
class CMapEditManager;
class JsonNode;
class CMapGenerator;
class CTileInfo;

typedef std::vector<JsonNode> JsonVector;

class rmgException : std::exception
{
	std::string msg;
public:
	explicit rmgException(const std::string& _Message) : msg(_Message)
	{
	}

	virtual ~rmgException() throw ()
	{
	};

	const char *what() const throw () override
	{
		return msg.c_str();
	}
};

/// The map generator creates a map randomly.
class DLL_LINKAGE CMapGenerator
{
public:
	explicit CMapGenerator(shared_ptr<CMapGenOptions> mapGenOptions, int randomSeed = std::time(nullptr));
	~CMapGenerator(); // required due to unique_ptr

	std::unique_ptr<CMap> generate();
	
	shared_ptr<CMapGenOptions> mapGenOptions;
	std::unique_ptr<CMap> map;
	CRandomGenerator rand;
	int randomSeed;
	CMapEditManager * editManager;

	std::map<TRmgTemplateZoneId, CRmgTemplateZone*> getZones() const;
	void createConnections();
	void foreach_neighbour(const int3 &pos, std::function<void(int3& pos)> foo);

	bool isBlocked(const int3 &tile) const;
	bool shouldBeBlocked(const int3 &tile) const;
	bool isPossible(const int3 &tile) const;
	bool isFree(const int3 &tile) const;
	void setOccupied(const int3 &tile, ETileType::ETileType state);
	CTileInfo getTile(const int3 & tile) const;

	int getNearestObjectDistance(const int3 &tile) const; 
	void setNearestObjectDistance(int3 &tile, int value);

	int getNextMonlithIndex();

private:
	std::map<TRmgTemplateZoneId, CRmgTemplateZone*> zones;

	CTileInfo*** tiles;

	int monolithIndex;

	/// Generation methods
	std::string getMapDescription() const;
	void addPlayerInfo();
	void addHeaderInfo();
	void initTiles();
	void genZones();
	void fillZones();

};
