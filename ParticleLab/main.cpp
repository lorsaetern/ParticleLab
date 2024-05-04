#include "Engine.h"

int main()
{
	srand(time(0));
	// Declare an instance of Engine
	Engine engine;
	// Start the engine
	engine.run();
	// Quit in the usual way when the engine is stopped
	return 0;
}
//Exception thrown at 0x00007FF9D914D009 (ntdll.dll) in ParticleLab.exe: 0xC00000FD : Stack overflow(parameters : 0x0000000000000001, 0x0000007AF2473FF8).
