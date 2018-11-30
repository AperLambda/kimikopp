/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of kimiko++.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef KIMIKO_CONTEXT_H
#define KIMIKO_CONTEXT_H

#include <lambdacommon/system/terminal.h>
#include <string>

namespace kimiko
{
	/*!
	 * A command context.
	 *
	 * Represents a context within the command is executed.
	 *
	 * @tparam S The typename of the sender.
	 * @version 1.0.0
	 * @since 1.0.0
	 */
	template<class S>
	class CommandContext
	{
	public:
		/*!
		 * Gets the command sender.
		 * @return The command sender.
		 */
		virtual S get_sender() const = 0;

		/*!
		 * Gets the name of the command sender.
		 * @return The command sender's name.
		 */
		virtual std::string get_sender_name() const = 0;

		/*!
		 * Sends a message to the sender.
		 * @param message The message to send.
		 */
		virtual void send_message(const std::string &message) const = 0;

		virtual const CommandContext<S> &operator<<(const std::string &buffer) const
		{
			send_message(buffer);
			return *this;
		}
	};

	/*!
	 * CLISender.
	 *
	 * Represents a command sender in a command line interface.
	 *
	 * @version 1.0.0
	 * @since 1.0.0
	 */
	class CLISender
	{
	private:
		static CLISender singleton;

		CLISender() = default;

	public:
		CLISender(const CLISender &) = delete;

		/*!
		 * Gets the name of the sender.
		 * @return The name of the user.
		 */
		std::string get_name() const;

		/*!
		 * Sends a message to the terminal output stream.
		 * @param message The message to send.
		 */
		void send_message(const std::string &message) const;

		CLISender &operator=(const CLISender &) = delete;

		/*!
		 * Gets the singleton.
		 * @return The singleton.
		 */
		static CLISender &get() noexcept
		{
			return singleton;
		}
	};

	/*!
	 * CLICommandContext
	 *
	 * Represents a command line context within a command is executed.
	 *
	 * @version 1.0.0
	 * @since 1.0.0
	 */
	class CLICommandContext : public CommandContext<CLISender &>
	{
	public:
		CLISender &get_sender() const override
		{
			return CLISender::get();
		}

		std::string get_sender_name() const override
		{
			return get_sender().get_name();
		}

		void send_message(const std::string &message) const override
		{
			get_sender().send_message(message);
		}

		const CLICommandContext &operator<<(const std::string &buffer) const override
		{
			send_message(buffer);
			return *this;
		}

		const CLICommandContext &operator<<(lambdacommon::terminal::TermFormatting formatting) const
		{
			std::cout << formatting;
			return *this;
		}
	};
}

#endif //KIMIKO_CONTEXT_H