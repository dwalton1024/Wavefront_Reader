#include "DW_String.h"

std::vector<std::string> Parse_Lines(const std::string& text)
{
	std::vector<std::string> lines;

	std::size_t start = 0;

	for (std::size_t i = 0; i < text.size(); ++i)
	{
		if (text[i] == '\n')
		{
			std::size_t end = i;

			if (end > start && text[end - 1] == '\r')
			{
				--end;
			}

			lines.emplace_back(text.substr(start, end - start));
			start = i + 1;
		}
	}

	if (start < text.size())
	{
		std::size_t end = text.size();

		if (end > start && text[end - 1] == '\r')
		{
			--end;
		}

		lines.emplace_back(text.substr(start, end - start));
	}

	return lines;
}

std::vector<float> To_Floats(const std::vector<std::string>& strings)
{
	std::vector<float> result;
	result.reserve(strings.size());

	for (const std::string& s : strings)
	{
		try
		{
			size_t pos = 0;
			float value = std::stof(s, &pos);

			if (pos == s.size())
				result.push_back(value);
		}
		catch (...)
		{
			// Ignore junk tokens.
		}
	}

	return result;
}

bool Try_Parse_Float(const std::string& s, float& out)
{
	try
	{
		out = std::stof(s);
		return true;
	}
	catch (...)
	{
		return false;
	}
}

bool Try_Parse_Int(const std::string& s, int& out)
{
	try
	{
		out = std::stoi(s);
		return true;
	}
	catch (...)
	{
		return false;
	}
}

std::string Parse_First_Word(const std::string& line) {

	std::string delimiter = " ";

	std::string word;
	std::size_t found = line.find_first_of(delimiter);
	word = line.substr(0, found);

	return word;
}

std::vector<std::string> Parse_By(const std::string& input, const std::string& delimiter) {

	std::vector<std::string> result;

	size_t start = 0;
	size_t end = 0;

	while ((end = input.find(delimiter, start)) != std::string::npos)
	{
		result.push_back(input.substr(start, end - start));
		start = end + delimiter.length();
	}

	result.push_back(input.substr(start));

	return result;

}

bool Parse_Bool(const std::string& attrib)
{

	if (attrib == "0" || attrib == "off" || attrib == "OFF" || attrib == "false" || attrib == "FALSE")
		return false;

	return true;

}

std::vector<std::string> Parse_Words(const std::string& line)
{
	std::vector<std::string> words;
	std::string word;

	for (char c : line)
	{
		if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
		{
			if (!word.empty())
			{
				words.push_back(word);
				word.clear();
			}
		}
		else
		{
			word.push_back(c);
		}
	}

	if (!word.empty())
		words.push_back(word);

	return words;
}
