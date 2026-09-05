#pragma once

#include "point.hpp"

class Listener {
public:
	Point GetMove();
	bool WantsToQuit();
};