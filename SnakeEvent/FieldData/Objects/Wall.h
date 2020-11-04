// ☕ Привет
#pragma once

#include "../FieldObject.h"

namespace SnakeEvent
{
	namespace FieldData
	{
		class Wall : public FieldObject
		{
		public:
			Wall()
				: FieldObject(219)
			{}

			virtual int OnActiveIntersect(FieldObject* intersected_object)
			{
				throw std::logic_error("Walls cannot move");
			}

			virtual int OnPassiveIntersect(FieldObject* intersected_object)
			{
				// Кто бы не пытался наступить на стену, сделать он это не сможет, и выживет
				return 0;
			}

			void OnRemove() override
			{
				throw "Cannot remove wall";
			}
		};
	}
}