#include <lazysoft/serial.hpp>

int main(int argc,char** argv){

	Serial terminal("stdio",B0);

	terminal.write("Hellow World\n\r");

	return 0;
}
