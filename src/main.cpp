#include <iostream>

#include "Application.h"

using namespace std;

int main(int argc, char** argv)
{
	Application app;
	app.Initialize();

	app.Update();

	app.Destroy();

    return 0;
}
