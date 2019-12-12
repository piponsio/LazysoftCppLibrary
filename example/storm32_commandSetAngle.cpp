#include <string>
#include <lazysoft/storm32_command.hpp>

int main(int argc,char** argv){

	Serial terminal("stdio",B0);

	float f0 = std::stof(argv[2]);
	float f1 = std::stof(argv[3]);
	float f2 = std::stof(argv[4]);

	Storm32_command command(argv[1], B9600);

	command.setAngle(f0, f1, f2);
	terminal.write("Mensaje enviado\n\r");

	return 0;
}
