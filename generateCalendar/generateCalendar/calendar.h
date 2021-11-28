#pragma once
#include "HTML.h"

#define ToString(x) std::to_string(x)

static const char* dayNames[7] = {
	"Mon",
	"Tue",
	"Wed",
	"Thu",
	"Fri",
	"Sat",
	"Sun"
};

static const char* monthNames[12] = {
	"January",
	"February",
	"March",
	"April",
	"May",
	"June",
	"July",
	"August",
	"September",
	"October",
	"November",
	"December"
};

static const int noDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

class Column
{
public:
	Column() :name{ "" }, span{ 1 }, backgroundColour{ "" } {};
	Column(const String colname, const int span, const String background);
	~Column();
	String getClass();
	String getStyle();

private:
	String name;
	int span;
	String backgroundColour;
};

class Calendar
{
	// Member functions
public:
	Calendar(const int& year);
	~Calendar();
	int getDayOfWeek(const int& date, const int& month, const int& year);
	bool isLeapYear(const int& year);
	void generateCalendarHtml();

private:
	void header();
	void weekTheme();
	bool weekFill(int& weeknum, int& startday, int& startdate, const int & lastdate);
	void monthFill(int& weeknum, const int & monthNum);

	// Member parameters
private:
	int yearRequested;
	int startDay;
	bool leapYear;
	static const int days = sizeof(dayNames)/sizeof(dayNames[0]);
	static const int months = sizeof(monthNames) / sizeof(monthNames[0]);

	String fontFamily;
	String fontSize;
	Column weeks;
	Column weekDays;
	Column saturdays;
	Column sundays;

	std::unique_ptr<HTML> calendarFile;
};

