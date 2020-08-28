#include "application.h"

int main()
{
	Application application;

	if (application.initialize()) {
		application.run();
		return 0;
	}

	return -1;
}