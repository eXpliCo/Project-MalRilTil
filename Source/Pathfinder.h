#ifndef __PATHFINDER_H__
#define __PATHFINDER_H__

#include "BaseAgent.h"
#include "PathObj.h"
#include "cthread.h"

using namespace BWAPI;
using namespace BWTA;
using namespace std;

/** This class is used to find a path betweed two tiles in the game world. Currently it uses the 
 * A-star implementation in BWTA, but it can easily be changed to another algorithm if needed.
 *
 * The pathfinder is threaded, so agents have to request a path that is put in a queue. Agents have to
 * check the isReady() method to find out when the path finding is finished.
 *
 * Author: Johan Hagelback (johan.hagelback@gmail.com)
 */
class Pathfinder : public CThread {

private:
	Pathfinder();
	static Pathfinder* instance;
	static bool instanceFlag;
	bool running;
	bool lock;
	bool end;

	vector<PathObj*> pathObj;

	PathObj* getPathObj(TilePosition start, TilePosition end);

	bool isRunning();

public:
	/** Destructor */
	~Pathfinder();

	/** Returns the instance of the class. */
	static Pathfinder* getInstance();

	/** Returns the ground distance between two positions. */
	int getDistance(TilePosition start, TilePosition end);

	void requestPath(TilePosition start, TilePosition end);

	bool isReady(TilePosition start, TilePosition end);

	/** Returns the path between two positions. */
	vector<TilePosition> getPath(TilePosition start, TilePosition end);

	/** Stops the pathfinder thread. */
	void stop();

	/** Thread update method. */
	unsigned long Process (void* parameter);
};

#endif
