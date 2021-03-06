/**
 * @file
 *
 * @brief
 *
 * @copyright BSD License (see LICENSE.md or https://www.libelektra.org)
 */

keyNew ("system/elektra/modules/" ELEKTRA_PLUGIN_NAME, KEY_VALUE, "crypto plugin waits for your orders", KEY_END),
	keyNew ("system/elektra/modules/" ELEKTRA_PLUGIN_NAME "/exports", KEY_END),
	keyNew ("system/elektra/modules/" ELEKTRA_PLUGIN_NAME "/exports/open", KEY_FUNC, CRYPTO_PLUGIN_FUNCTION (open), KEY_END),
	keyNew ("system/elektra/modules/" ELEKTRA_PLUGIN_NAME "/exports/close", KEY_FUNC, CRYPTO_PLUGIN_FUNCTION (close), KEY_END),
	keyNew ("system/elektra/modules/" ELEKTRA_PLUGIN_NAME "/exports/get", KEY_FUNC, CRYPTO_PLUGIN_FUNCTION (get), KEY_END),
	keyNew ("system/elektra/modules/" ELEKTRA_PLUGIN_NAME "/exports/set", KEY_FUNC, CRYPTO_PLUGIN_FUNCTION (set), KEY_END),
	keyNew ("system/elektra/modules/" ELEKTRA_PLUGIN_NAME "/exports/error", KEY_FUNC, CRYPTO_PLUGIN_FUNCTION (error), KEY_END),
	keyNew ("system/elektra/modules/" ELEKTRA_PLUGIN_NAME "/exports/checkconf", KEY_FUNC, CRYPTO_PLUGIN_FUNCTION (checkconf), KEY_END),
#include ELEKTRA_README (crypto)
	keyNew ("system/elektra/modules/" ELEKTRA_PLUGIN_NAME "/infos/version", KEY_VALUE, PLUGINVERSION, KEY_END),
