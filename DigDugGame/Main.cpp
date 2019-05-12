#include "pch.h"
#include "SDL.h"
#include "DigDug.h"
#include <vld.h>

int main(int argc, char *args[]){
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(args);

	{
		DigDug game;
		game.Run();
	}

    return 0;
}
