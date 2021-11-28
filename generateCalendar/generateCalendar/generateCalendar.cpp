#include "calendar.h"

int main(int argc, char** argv)
{
	if (argc >= 2)
	{
		int year = std::stoi(argv[1]);
		log(year);
		auto calendar = std::make_unique<Calendar>(year);
		calendar->generateCalendarHtml();
	}
	else {
		log("Provide an year as an argument.");
	}
	
	return 0;
}