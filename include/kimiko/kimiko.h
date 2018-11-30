/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of kimiko++.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */


#ifndef KIMIKO_LIBRARY_H
#define KIMIKO_LIBRARY_H

#include "arguments.h"
#include "manager.h"

#define KIMIKO_VERSION_MAJOR 0
#define KIMIKO_VERSION_MINOR 0
#define KIMIKO_VERSION_PATCH 0

namespace kimiko
{
	/*!
	 * Gets the runtime version of kimiko.
	 * @return The runtime version of kimiko.
	 */
	extern std::string get_version();
}

#endif // KIMIKO_LIBRARY_H