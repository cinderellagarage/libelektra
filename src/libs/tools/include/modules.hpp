/**
 * @file
 *
 * @brief Allows one to load plugins
 *
 * @copyright BSD License (see doc/COPYING or http://www.libelektra.org)
 *
 */


#ifndef TOOLS_MODULES_HPP
#define TOOLS_MODULES_HPP

#include <plugin.hpp>
#include <keyset.hpp>
#include <toolexcept.hpp>
#include <pluginspec.hpp>

namespace kdb
{

namespace tools
{

/**
 * @brief Allows one to load plugins
 */
class Modules
{
public:
	Modules();
	~Modules();

	/**
	 * @deprecated do not use
	 */
	PluginPtr load (std::string const& pluginName);
	/**
	 * @deprecated do not use
	 */
	PluginPtr load (std::string const& pluginName, kdb::KeySet const& config);
	/**
	 * @return a newly created plugin
	 */
	PluginPtr load (PluginSpec const & spec);

private:
	KeySet modules;
};

}

}

#endif
