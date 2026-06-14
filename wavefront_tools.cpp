#include "DW_IO.h"
#include "DW_String.h"

#include "wavefront_tools.h"


//Grabs text file at 'file_path', and returns it as a vector<string> of the individual lines.
std::vector<std::string> Get_Lines(const std::string& file_path)
{
	return Parse_Lines(Load_Text_File_As_String(file_path));
}

bool Extract_Smooth(const std::string& s_line) {
	return Parse_Bool(Extract_Attrib(s_line));
}

bool Check_Type(const std::string& line, const std::string& type) {
	std::string buff = Parse_First_Word(line);
	if (buff == type) {
		return 1;
	}
	else {
		return 0;
	}
}

std::vector<std::string> Extract_Face_Words(const std::string& f_line) {
	return Parse_Words(Extract_Attrib(f_line));
}

std::vector<float> Extract_Float_Vector(const std::string& line) {

	std::vector<float> result;

	std::string attrib = Extract_Attrib(line);

	std::vector<std::string> words = Parse_Words(attrib);

	for (const std::string& word : words)
	{
		float value;

		if (Try_Parse_Float(word, value))
		{
			result.push_back(value);
		}
	}

	return result;
}

float Extract_Float(const std::string& line) {

	std::string attrib = Extract_Attrib(line);

		float value = -9999.999;

		Try_Parse_Float(attrib, value);

	return  value;
}

int Extract_Int(const std::string& line) {

	std::string attrib = Extract_Attrib(line);

	int value = -999999;

	Try_Parse_Int(attrib, value);

	return  value;
}

bool Decode_Face_Vertex(const std::string& slash_word, int& v, int& vt, int& vn)
{

	v = -1;
	vt = -1;
	vn = -1;

	std::string number;
	int slot = 0;

	for (size_t i = 0; i <= slash_word.size(); ++i)
	{
		const bool end = (i == slash_word.size());
		const char c = end ? '/' : slash_word[i];

		if (c == '/')
		{
			if (slot > 2)
				return false;

			if (!number.empty())
			{
				int value = -1;

				if (!Try_Parse_Int(number, value))
					return false;

				if (slot == 0)
					v = value;
				else if (slot == 1)
					vt = value;
				else if (slot == 2)
					vn = value;
			}

			number.clear();
			slot++;
		}
		else
		{
			number.push_back(c);
		}
	}

	return v != -1;
}

//Takes a line of floats, parses them, converts them, and packs them into a vector<float>
std::vector<float> Extract_Floats(const std::string& line) {

	std::vector<float> out = To_Floats(Parse_Words(line));
	return out;

}

std::string Extract_Attrib(const std::string& line) {

	std::string head;

	for (unsigned i = 0; i < (unsigned)line.length(); i++) {
		if (line.at(i) == ' ') {
			i++;
			for (unsigned j = i; j < (unsigned)line.length(); j++) {
				head += line.at(j);
			}
			return head;
		}
	}

	return head;

}
