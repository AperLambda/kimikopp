/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of kimiko++.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef KIMIKO_MANAGER_H
#define KIMIKO_MANAGER_H

#include "command.h"
#include <optional>

namespace kimiko
{
	/*!
	 * CommandManager.
	 *
	 * Manages command registration and detection.
	 * @tparam S The typename of the sender.
	 * @version 1.0.0
	 * @since 1.0.0
	 */
	template<class S>
	class CommandManager
	{
	protected:
		std::vector<std::shared_ptr<Command<S>>> commands;

	public:
		/*!
		 * Registers the specified command.
		 * @param command The command to register.
		 */
		virtual void register_command(std::shared_ptr<Command<S>> command)
		{
			if (has_command(command->get_identifier()))
				return;
			commands.push_back(command);
		}

		/*!
		 * Checks whether the command is registered or not.
		 * @param identifier The identifier of the command.
		 * @return True if the command is registered, else false.
		 */
		virtual bool has_command(const lambdacommon::ResourceName &identifier) const
		{
			for (const std::shared_ptr<Command<S>> &cmd : commands)
				if (cmd->get_identifier() == identifier)
					return true;
			return false;
		}

		virtual std::optional<std::shared_ptr<Command<S>>>
		get_command(const lambdacommon::ResourceName &identifier) const
		{
			for (const std::shared_ptr<Command<S>> &cmd : commands)
				if (cmd->get_identifier() == identifier)
					return {cmd};
			return std::nullopt;
		}

		/*!
		 * Gets all of the registered commands.
		 * @return The registered commands.
		 */
		const std::vector<std::shared_ptr<Command<S>>> &get_commands() const
		{
			return commands;
		}

		/*!
		 * Removes all of the register commands.
		 */
		virtual void clear()
		{
			commands.clear();
		}
	};
}

#endif //KIMIKO_MANAGER_H