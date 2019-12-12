#include <string>
#include <iostream>
#include <lazysoft/storm32_command.hpp>

int main(int argc,char** argv){

	Serial terminal("stdio",B0);
	Serial storm32(argv[1], B9600);

	float f0 = std::stof(argv[2]);
	float f1 = std::stof(argv[3]);
	float f2 = std::stof(argv[4]);

	Storm32_command command(argv[1], B9600);

 	//command.getVersion();
 	command.setAngle(f0, f1, f2);
//        terminal.write(std::hex);
 	//command.getDataFields("IMU1ANGLES");
	command.getAngles();
/*
	unsigned char console_command = 'D';
	unsigned char lectura;
	int size = 0;
	while(console_command!='q'){
		if(storm32.read(&lectura) > 0){
			if(lectura == 251) size = 0;
			size++;
//			terminal.write(&lectura);
			std::cout << lectura << "\t";
//			terminal.write(" ");
			std::cout << std::dec << (int)lectura << "\t";
			std::cout << std::hex << (int)lectura << "\t";
			std::cout << std::dec << size << "\t";
//			if(lectura == 251) terminal.write(" -> Inicio");
			if(lectura == 251) std::cout << "-> Inicio";
//			terminal.write("\n\r");
			std::cout << "\n\r";
		}
		if(terminal.read(&console_command) > 0) terminal.write(&console_command);
		terminal.read(&console_command);

	}
//	terminal.write("\n\r");
//	std::cout << "\n\r";
	*/
	return 0;
}
