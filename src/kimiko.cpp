/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of kimiko++.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#include "../include/kimiko/kimiko.h"

namespace kimiko
{
	std::string get_version()
	{
		return std::to_string(KIMIKO_VERSION_MAJOR) + '.' + std::to_string(KIMIKO_VERSION_MINOR) + '.' +
			   std::to_string(KIMIKO_VERSION_PATCH);
	}
}