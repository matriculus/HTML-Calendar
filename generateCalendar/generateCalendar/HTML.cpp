#include "HTML.h"

HTML::HTML(const String fname)
{
	log("HTML file created.");
	fileName = fname;
	htmlFile.open(fileName);
	writeToHtml(String("<!DOCTYPE html>"));
}

HTML::~HTML()
{
	htmlFile << "</html";
	htmlFile.close();
	log("HTML file closed.");
}

void HTML::title(const String title)
{
	std::unique_ptr<Tag> tag = std::make_unique<Tag>("title");
	writeToHtml(tag->open());
	writeToHtml(tag->write(title));
	writeToHtml(tag->close());
}


void HTML::writeToHtml(const String data)
{
	htmlFile << data;
	htmlFile << "\n";
}

////////////////////////////////////////////////////////////////////////

Tag::Tag(const String tag)
{
	tagname = tag;
	tagWithOptions = "<" + tagname + ">";
}

Tag::Tag(const String tag, const String options)
{
	tagname = tag;
	tagWithOptions = "<" + tagname + " " + options + ">";
}

Tag::~Tag(){}

String Tag::write(const String data)
{
	return data;
}

String Tag::open()
{
	return tagWithOptions;
}

String Tag::close()
{
	return "</" + tagname + ">";
}

String Tag::inlineOpen(const String options)
{
	return "<" + tagname + " " + options + "/>";
}

String Tag::writeInline(const String data)
{
	String text = "";
	text += open();
	text += data;
	text += close();
	return text;
}

////////////////////////////////////////////////////////////////////////
