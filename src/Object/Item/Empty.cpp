#include "Object/Item/Empty.h"

void Empty::Serialize(std::string& content) const
{
	SerializeChildren(content);
}
