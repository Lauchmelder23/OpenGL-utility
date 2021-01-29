#include "material.hpp"

namespace oglu
{
	void Material::AddProperty(const std::string& name, const std::any& value)
	{
		properties.insert(std::make_pair(name, value));
	}

	void Material::RemoveProperty(const std::string& name)
	{
		properties.erase(name);
	}
}
