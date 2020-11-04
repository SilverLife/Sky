#pragma once

#include "../../Sky/Shared/Geometry/Point.h"
#include "../../Sky/Shared/Geometry/RectangleSize.h"

namespace SnakeEvent
{
	using PointCoordsType = short;
	using Point = Shared::Geometry::Point<PointCoordsType>;
	using uint = unsigned int;
	using Size = Shared::Geometry::RectangleSize<PointCoordsType>;
}