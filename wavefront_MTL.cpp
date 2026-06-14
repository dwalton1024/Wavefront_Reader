#include "wavefront_tools.h"
#include "wavefront_MTL.h"

bool RGB::Parse_RGB(const std::string& RGB_Line) {
	std::vector<float> f = Extract_Float_Vector(RGB_Line);

	if (f.size() < 3)
		return 0;

	r = f[0];
	g = f[1];
	b = f[2];

	valid = true;

	return 1;
}

NEWMTL::NEWMTL(const std::string& Newmtl_Line) {
	name_ = Extract_Attrib(Newmtl_Line);
	valid = true;
}

void Wavefront_MTL_File::Init() {

	material_count_ = 0;
	loaded_ = false;

}

void Wavefront_MTL_File::Parse_Lines(const std::vector<std::string>& lines) {

	int current_newmtl = -1;

	for (const std::string& line : lines) {

		if (line.empty()) {
			continue;
		}

		if (Check_Type(line, "#")) {

			if (current_newmtl > -1) {
				newmtl_[current_newmtl].comments_.push_back(line);
			}
			else {
				comments_.push_back(line);
			}

		}
		else if (Check_Type(line, "newmtl")) {

			current_newmtl++;
			newmtl_.emplace_back(line);

		}
		else if (Check_Type(line, "Ka")) {

			if (current_newmtl > -1) {
				newmtl_[current_newmtl].Ka_.Parse_RGB(line);
			}

		}
		else if (Check_Type(line, "Kd")) {

			if (current_newmtl > -1) {
				newmtl_[current_newmtl].Kd_.Parse_RGB(line);
			}

		}
		else if (Check_Type(line, "Ks")) {

			if (current_newmtl > -1) {
				newmtl_[current_newmtl].Ks_.Parse_RGB(line);
			}

		}
		else if (Check_Type(line, "Ke")) {

			if (current_newmtl > -1) {
				newmtl_[current_newmtl].Ke_.Parse_RGB(line);
			}

		}
		else if (Check_Type(line, "Ns")) {

			if (current_newmtl > -1) {
				newmtl_[current_newmtl].Ns = Extract_Float(line);
			}

		}
		else if (Check_Type(line, "Ni")) {

			if (current_newmtl > -1) {
				newmtl_[current_newmtl].Ni = Extract_Float(line);
			}

		}
		else if (Check_Type(line, "d")) {

			if (current_newmtl > -1) {
				newmtl_[current_newmtl].d = Extract_Float(line);
			}

		}
		else if (Check_Type(line, "Tr")) {

			if (current_newmtl > -1) {
				newmtl_[current_newmtl].Tr = Extract_Float(line);
			}

		}
		else if (Check_Type(line, "illum")) {

			if (current_newmtl > -1) {
				newmtl_[current_newmtl].illum = Extract_Int(line);
			}

		}
		else if (Check_Type(line, "map_Ka")) {

			if (current_newmtl > -1) {
				newmtl_[current_newmtl].map_Ka = Extract_Attrib(line);
			}

		}
		else if (Check_Type(line, "map_Kd")) {

			if (current_newmtl > -1) {
				newmtl_[current_newmtl].map_Kd = Extract_Attrib(line);
			}

		}
		else if (Check_Type(line, "map_Ks")) {

			if (current_newmtl > -1) {
				newmtl_[current_newmtl].map_Ks = Extract_Attrib(line);
			}

		}
		else if (Check_Type(line, "map_Ns")) {

			if (current_newmtl > -1) {
				newmtl_[current_newmtl].map_Ns = Extract_Attrib(line);
			}

		}
		else if (Check_Type(line, "map_d")) {

			if (current_newmtl > -1) {
				newmtl_[current_newmtl].map_d = Extract_Attrib(line);
			}

		}
		else if (Check_Type(line, "bump")) {

			if (current_newmtl > -1) {
				newmtl_[current_newmtl].bump = Extract_Attrib(line);
			}

		}
		else if (Check_Type(line, "map_Bump")) {

			if (current_newmtl > -1) {
				newmtl_[current_newmtl].map_Bump = Extract_Attrib(line);
			}

		}
		else
		{

			if (current_newmtl > -1) {
				newmtl_[current_newmtl].unknown_lines_.push_back(line);
			}
			else {
				unknown_lines_.push_back(line);
			}

		}

	}

}

bool Wavefront_MTL_File::Load_File(const std::string& file_name) {

	//Check if something has already been loaded.
	if (loaded_) {
		return false;
	}

	filename_ = file_name;

	std::vector<std::string> lines = Get_Lines(file_name);

	//Check if Get_Lines() failed to return anything
	if (lines.empty()) {
		return false;
	}

	Parse_Lines(lines);

	loaded_ = true;

	return true;
}

Wavefront_MTL_File::Wavefront_MTL_File(const std::string& file_name) {
	Init();
	Load_File(file_name);

}

Wavefront_MTL_File::Wavefront_MTL_File() {
	Init();
}
