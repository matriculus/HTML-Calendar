# Calendar Generator

Calendar Generator program is written in C++ in Windows platform (Visual Studio 2019). The Visual Studio solution can be found in `generateCalendar\generateCalendar.sln`. The executable is in `generateCalendar\Release\generateCalendar.exe`. The html file is created in the same location as the executable with the name `index_<year>.html`.

The program generates calendars for the requested year as well as its previous and next years. Each year is stacked in column.

## Usage
---
`> generateCalendar <year>` or `> .\generateCalendar.exe <year>`

Example:

`> generateCalendar 1800` generates `index_1800.html` in the same location as the executable.
