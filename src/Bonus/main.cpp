#include "../../include/Bot.hpp"
#include <stdlib.h>

int main(int argc, char **argv) {
	if (argc < 4)
	{
		std::cout << "Error, bad arguments: ./bot <ip> <port> <password>" << std::endl;
		return (1);
	}

	try
	{
		int port = static_cast<int>(strtod(argv[1], NULL));
		Bot bot(argv[1], port, argv[2]);
		//bot.connect();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << std::endl;
		return (1);
	}

	return (0);
}