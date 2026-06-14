
#include "DW_IO.h"
#include <fstream>

std::string Load_Text_File_As_String(const std::string& file_path)
{
	std::ifstream file(file_path);

	if (!file)
	{
		return "";
	}

	return std::string(
		std::istreambuf_iterator<char>(file),
		std::istreambuf_iterator<char>()
	);
}