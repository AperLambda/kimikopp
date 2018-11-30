#include "../include/kimiko/manager.h"

using namespace kimiko;
using namespace lambdacommon::lstring::stream;

int main(int argc, char **argv)
{
	CommandManager<CLISender &> manager;
	auto cmd = std::make_shared<Command<CLISender &>>(lambdacommon::ResourceName("kimiko_test:test1"));
	cmd->set_executor(
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
	manager.register_command(cmd);
	auto result = cmd->execute(CLICommandContext(), "test1", {}).to_string();
	std::cout << "Result of execution is: " << result << std::endl;
	return EXIT_SUCCESS;
}