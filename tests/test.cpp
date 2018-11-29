#include "../include/kimiko/command.h"

using namespace kimiko;
using namespace lambdacommon::lstring::stream;

int main()
{
	Command<CLISender &> cmd{{"kimiko_test:test1"}};
	cmd.set_executor(
			[](const CommandContext<CLISender &> &_context, const Command<CLISender &> &cmd, const std::string &label,
			   const std::vector<std::string> &args)
			{
				if (!args.empty())
					return KIMIKO_COMMANDRESULT_USAGE_ERROR;
				// Recast to proper context.
				const auto &context = (const CLICommandContext &) _context;
				context << lambdacommon::terminal::LIGHT_GREEN << "Hello world (Executed with the command " + cmd.get_name() + ")\n" << lambdacommon::terminal::RESET;
				return KIMIKO_COMMANDRESULT_SUCCESS;
			});
	auto result = cmd.execute(CLICommandContext(), "test1", {}).to_string();
	std::cout << "Result of execution is: " << result << std::endl;
	return EXIT_SUCCESS;
}