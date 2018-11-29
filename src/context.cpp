/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of kimiko++.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#include "../include/kimiko/context.h"
#include <lambdacommon/system/system.h>

namespace kimiko
{
	CLISender CLISender::singleton{};

	std::string CLISender::get_name() const
	{
		return lambdacommon::system::get_user_name();
	}

	void CLISender::send_message(const std::string &message) const
	{
		std::cout << message;
	}
}