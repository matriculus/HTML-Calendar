#include "calendar.h"

Column::Column(const String colname, const int colspan, const String background)
{
	name = colname;
	span = colspan;
	backgroundColour = background;
}

Column::~Column(){}

String Column::getClass()
{
	return "class=\"" + name + "\" span=\"" + ToString(span) + "\"";
}

String Column::getStyle()
{
	/* ".week{ background-color: grey; }" */
	return "." + name + " { background-color: " + backgroundColour + "; }";
}

///////////////////////////////////////////////////////////////

Calendar::Calendar(const int& year)
{
	log("Calendar object created.");
	yearRequested = year;
	calendarFile = std::make_unique<HTML>("index_" + ToString(yearRequested) + ".html");

	startDay = getDayOfWeek(01, 01, yearRequested-1);

	weeks = Column("week", 1, "grey");
	weekDays = Column("weekdays", 5, "lightgrey");
	saturdays = Column("saturdays", 1, "yellow");
	sundays = Column("sundays", 1, "orange");

	fontFamily = "Arial, Helvetica, sans-serif";
	fontSize = "small";
}

Calendar::~Calendar()
{
	log("Calendar object deleted.");
}

int Calendar::getDayOfWeek(const int & date, const int & month, const int & year)
{
	int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
	int y = year;
	y -= month < 3;
	return (((y + int(y / 4) - int(y / 100) + int(y / 400) + t[month - 1] + date) % days) + (days-1)) % days;
}

bool Calendar::isLeapYear(const int &year)
{
	if (year % 4 == 0) {
		if (year % 100 == 0){
			if (year % 400 == 0)
				return true;
			else
				return false;
		} else {
			return true;
		}
	} else {
		return false;
	}
}

void Calendar::header()
{
	Tag head = Tag("head");
	calendarFile->writeToHtml(head.open());
	Tag style = Tag("style");
	calendarFile->writeToHtml(style.open());
	calendarFile->writeToHtml(style.write("div { margin: 0 auto; }"));
	calendarFile->writeToHtml(style.write("table { table-layout: fixed; width: 480px; }"));
	calendarFile->writeToHtml(style.write(".calendar {display: flex; font-family: " + fontFamily + "; font-size: " + fontSize + ";}"));
	calendarFile->writeToHtml(style.write(".year{ text-align: center; float: left; }"));
	calendarFile->writeToHtml(style.write(".month{ background-color: lightgreen; }"));
	calendarFile->writeToHtml(style.write(weeks.getStyle()));
	calendarFile->writeToHtml(style.write(weekDays.getStyle()));
	calendarFile->writeToHtml(style.write(saturdays.getStyle()));
	calendarFile->writeToHtml(style.write(sundays.getStyle()));
	calendarFile->writeToHtml(style.close());
	calendarFile->writeToHtml(head.close());
}

void Calendar::generateCalendarHtml()
{
	calendarFile->title(String("Calendar " + ToString(yearRequested)));
	header();
	
	Tag body = Tag("body");
	Tag cover = Tag("div", "class=\"calendar\"");
	Tag year = Tag("div", "class=\"year\"");
	Tag month = Tag("table", "align =\"center\", width=\"50\"");
	Tag h1 = Tag("h1");

	calendarFile->writeToHtml(body.open());
	calendarFile->writeToHtml(cover.open());
	for (int i = -1; i < 2; ++i) {
		leapYear = isLeapYear(yearRequested + i);
		calendarFile->writeToHtml(year.open());
		calendarFile->writeToHtml(h1.writeInline("Year: " + ToString(yearRequested + i)));
		int weekNum = 1;
		for (int monthNum = 0; monthNum < months; ++monthNum) {
			calendarFile->writeToHtml(month.open());
			monthFill(weekNum, monthNum);
			calendarFile->writeToHtml(month.close());
		}
		calendarFile->writeToHtml(year.close());
	}
	calendarFile->writeToHtml(cover.close());
	calendarFile->writeToHtml(body.close());
}

void Calendar::weekTheme()
{
	Tag colgroup = Tag("colgroup");
	calendarFile->writeToHtml(colgroup.open());
	Tag col = Tag("col");
	calendarFile->writeToHtml(col.inlineOpen(weeks.getClass()));
	calendarFile->writeToHtml(col.inlineOpen(weekDays.getClass()));
	calendarFile->writeToHtml(col.inlineOpen(saturdays.getClass()));
	calendarFile->writeToHtml(col.inlineOpen(sundays.getClass()));
	calendarFile->writeToHtml(colgroup.close());

	Tag tr = Tag("tr");
	calendarFile->writeToHtml(tr.open());
	Tag th = Tag("th");
	calendarFile->writeToHtml(th.writeInline("We #" ));
	for (int i=0; i<days; ++i)
		calendarFile->writeToHtml(th.writeInline(dayNames[i]));
	calendarFile->writeToHtml(tr.close());
}

bool Calendar::weekFill(int & weeknum, int & startday, int& startdate, const int & lastdate)
{
	bool flag = false;
	Tag td = Tag("td");
	calendarFile->writeToHtml(td.writeInline(ToString(weeknum) ));
	for (int i = 0; i < startday; ++i) {
		calendarFile->writeToHtml(td.writeInline(""));
	}
	int temp = startday;
	for (int i = 0; i < (days - temp); ++i) {
		calendarFile->writeToHtml(td.writeInline(ToString(startdate)));
		startday++;
		if (startdate == lastdate) {
			flag = true;
			break;
		}
		startdate++;
	}
	startday = startday % days;
	if (!flag) {
		weeknum++;
	}
	else {
		if (startday == 0)
			weeknum++;
	}
	return flag;
}


void Calendar::monthFill(int & weeknum, const int & monthNum)
{
	Tag tr = Tag("tr");
	calendarFile->writeToHtml(tr.open());
	Tag th = Tag("th", "colspan=\"8\" class=\"month\"");
	calendarFile->writeToHtml(th.writeInline(monthNames[monthNum]));
	calendarFile->writeToHtml(tr.close());
		
	weekTheme();

	int startdate = 1;
	bool cond;
	int lastdate = noDays[monthNum];
	if (leapYear && monthNum == 1)
		lastdate++;
		
	do {
		calendarFile->writeToHtml(tr.open());
		cond = weekFill(weeknum, startDay, startdate, lastdate);
		calendarFile->writeToHtml(tr.close());
	} while (!cond);
}