/*****************************************************************//**
 * @file   material.hpp
 * @brief  Anything related to materials
 * 
 * @author Lauchmelder
 * @date   January 2021
 *********************************************************************/
#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <map>
#include <any>
#include <iostream>
#include <core.hpp>

namespace oglu
{
	/**
	 * @brief A structure representing an object's material.
	 * 
	 * This object is dynamic and can contain any data that you want
	 */
	class OGLU_API Material
	{
	public:
		/**
		 * @brief Adds a new material property.
		 * 
		 * @param name The name of the property
		 * @param value The value of the property
		 */
		void AddProperty(const std::string& name, const std::any& value);

		/**
		 * @brief Remove the given property from the material.
		 */
		void RemoveProperty(const std::string& name);

		/**
		 * @brief Get a property from the material.
		 * 
		 * Should the material property not be present in the material this function
		 * will attempt to add it, using the default constructor of the supplied class.
		 * You should not rely on this failsafe working properly all the time.
		 * 
		 * @tparam T The type of the stores property
		 * @param name The name of the property
		 * @returns A pointer to the stored property
		 */
		template<typename T> T* GetProperty(const std::string& name, std::ostream& errorStream = OGLU_ERROR_STREAM)
		{
			std::map<std::string, std::any>::iterator it = properties.find(name);
			if (it == properties.end())
			{
				errorStream << "Failed to locate material property \"" << name << "\" in " << static_cast<const void*>(this) << ". Trying to construct default property of type \"" << typeid(T).name() << "\" and add it to the material.\n";

				it = properties.insert(std::make_pair(name, T())).first;
			}

			return std::any_cast<T>(&(it->second));
		}

		/**
		 * @brief Get a property from the material.
		 *
		 * Should the material property not be present in the material this function
		 * will attempt to add it, using the default constructor of the supplied class.
		 * You should not rely on this failsafe working properly all the time.
		 * 
		 * @tparam T The type of the stores property
		 * @param name The name of the property
		 * @returns The value of the stored property
		 */
		template<typename T> inline T GetPropertyValue(const std::string& name, std::ostream& errorStream = OGLU_ERROR_STREAM)
		{
			return *(GetProperty<T>(name, errorStream));
		}

	private:
		std::map<std::string, std::any> properties;
	};

	typedef std::shared_ptr<Material> SharedMaterial;	///< A material that can safely be shared between objects
}

#endif