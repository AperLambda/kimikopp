/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of kimiko++.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef KIMIKO_COMMAND_H
#define KIMIKO_COMMAND_H

#include "context.h"
#include <lambdacommon/resources.h>
#include <functional>
#include <memory>

#define KIMIKO_COMMANDRESULT_SUCCESS lambdacommon::ResourceName("kimiko", "results/success")
#define KIMIKO_COMMANDRESULT_RUNTIME_ERROR lambdacommon::ResourceName("kimiko", "results/errors/runtime")
#define KIMIKO_COMMANDRESULT_USAGE_ERROR lambdacommon::ResourceName("kimiko", "results/errors/usage")
#define KIMIKO_COMMANDRESULT_NOTFOUND_ERROR lambdacommon::ResourceName("kimiko", "results/errors/not_found")

namespace kimiko
{
	/*!
	 * Represents a command.
	 *
	 * @tparam S The typename of the sender.
	 * @version 1.0.0
	 * @since 1.0.0
	 */
	template<class S>
	class Command
	{
	public:
		typedef std::function<lambdacommon::ResourceName(const CommandContext<S> &, const Command &,
														 const std::string &,
														 const std::vector<std::string> &)> executor_t;

	private:
		lambdacommon::ResourceName _name;
		std::shared_ptr<Command<S>> _parent = nullptr;
		std::string _description;
		executor_t _executor = [](const CommandContext<S> &context, const Command &cmd, const std::string &label,
								  const std::vector<std::string> &args) { return KIMIKO_COMMANDRESULT_SUCCESS; };

	public:
		explicit Command(lambdacommon::ResourceName name) : _name(std::move(name))
		{}

		Command(const std::shared_ptr<Command<S>> &parent, lambdacommon::ResourceName name) : _parent(parent),
																								_name(std::move(name))
		{}

		/*!
		 * Gets the identifier of the command.
		 * @return The command's identifier
		 */
		const lambdacommon::ResourceName &get_identifier() const
		{
			return _name;
		}

		/*!
		 * Gets the name of the command.
		 * @return The command's name.
		 */
		inline const std::string &get_name() const
		{
			return get_identifier().get_name();
		}

		/*!
		 * Gets the parent command of the command.
		 * @return The parent command.
		 */
		const std::shared_ptr<Command<S>> &get_parent() const
		{
			return _parent;
		}

		/*!
		 * Checks whether the command has a parent command or not.
		 * @return True if the command has a parent command, else false.
		 */
		bool has_parent() const
		{
			return _parent;
		}

		/*!
		 * Gets the description of the command.
		 * @return The description.
		 */
		const std::string &get_description() const
		{
			return _description;
		}

		/*!
		 * Sets the description of the command.
		 * @param description The command's description.
		 */
		void set_description(const std::string &description)
		{
			_description = description;
		}

		/*!
		 * Gets the executor of the command.
		 * @return The command's executor.
		 */
		const executor_t &get_executor() const
		{
			return _executor;
		}

		/*!
		 * Sets the executor of the command.
		 * @param executor The command's executor.
		 */
		void set_executor(const executor_t &executor)
		{
			_executor = executor;
		}

		/*!
		 * Executes the command within a context.
		 * @param context The execution context.
		 * @param label The label used to identify the command.
		 * @param args The arguments passed to the command.
		 * @return The result of the execution.
		 */
		lambdacommon::ResourceName
		execute(const CommandContext<S> &context, const std::string &label, const std::vector<std::string> &args)
		{
			return _executor(context, *this, label, args);
		}

	private:
		lambdacommon::ResourceName handleLocalExecution(const CommandContext<S> &context, const std::string &label, const std::vector<std::string> &args)
		{
			// Todo: Permission management.
			return execute(context, label, args);
		}
	};
}

#endif //KIMIKO_COMMAND_H