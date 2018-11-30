#include <utility>

/*
 * Copyright © 2018 AperLambda <aperlambda@gmail.com>
 *
 * This file is part of kimiko++.
 *
 * Licensed under the MIT license. For more information,
 * see the LICENSE file.
 */

#ifndef KIMIKO_ARGUMENTS_H
#define KIMIKO_ARGUMENTS_H

#include <lambdacommon/lstring.h>
#include <functional>

namespace kimiko
{
	template<typename A>
	class ArgumentType
	{
	private:
		std::function<A(const std::string &)> mapper;

	public:
		ArgumentType(std::function<A(const std::string &)> mapper) : mapper(std::move(mapper))
		{}

		virtual A parse(const std::string &string) const
		{
			return mapper(string);
		}
	};

	static const ArgumentType<std::string> TYPE_STRING{[](const std::string &string) { return string; }};
	static const ArgumentType<int> TYPE_INT{[](const std::string &string) { return lambdacommon::lstring::parse_int(string, 10); }};
	static const ArgumentType<long> TYPE_LONG{[](const std::string &string) { return lambdacommon::lstring::parse_long(string, 10); }};

	template<typename A>
	class Argument
	{
	private:
		std::string _name;
		bool optional;
		ArgumentType<A> _type;

	public:
		/*!
		 * Gets the name of the argument.
		 * @return The argument's name.
		 */
		const std::string &get_name() const
		{
			return _name;
		}

		virtual A parse(const std::string &string) const
		{
			return _type.parse(string);
		}
	};
}

#endif //KIMIKO_ARGUMENTS_H