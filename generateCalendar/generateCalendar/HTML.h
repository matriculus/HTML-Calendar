#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<memory>


#define OutputFile std::ofstream
#define log(x) std::cout << x << std::endl
#define String std::string

class Tag
{
public:
	Tag(const String tag, const String options);
	Tag(const String tag);
	~Tag();
	String write(const String data);
	String open();
	String close();
	String inlineOpen(const String options);
	String writeInline(const String data);

protected:
	String tagname;
	String tagWithOptions;
};

class HTML
{
public:
	HTML(const String fname);
	~HTML();
	void title(const String title);
	void writeToHtml(const String data);

private:
	String fileName;
	OutputFile htmlFile;
};

