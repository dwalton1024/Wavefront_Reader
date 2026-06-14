#include "wavefront_tools.h"
#include "wavefront_OBJ.h"

F::F(const std::string& f_line)
{
	std::vector<std::string> indx = Extract_Face_Words(f_line);

	for (size_t i = 0; i < indx.size(); ++i)
	{
		F_Vert fv;

		if (!Decode_Face_Vertex(indx[i], fv.v, fv.vt, fv.vn))
		{
			f_verts_.clear();
			return;
		}

		f_verts_.push_back(fv);
	}

	if (f_verts_.size() < 3)
		f_verts_.clear();
}

V::V(const std::string& line) {

	std::vector<float> f = Extract_Float_Vector(line);

	if (f.size() < 3)
		return;

	x = f[0];
	y = f[1];
	z = f[2];

	valid = true;

}

const float& V::operator[](int i) const
{
	static const float blank = 0.0f;

	switch (i)
	{
	case 0: return x;
	case 1: return y;
	case 2: return z;
	default: return blank;
	}
}

VT::VT(const std::string& line) {

	std::vector<float> f = Extract_Float_Vector(line);

	if (f.size() < 2)
		return;

	x = f[0];
	y = f[1];

	valid = true;

}

const float& VT::operator[](int i) const
{
	static const float blank = 0.0f;

	switch (i)
	{
	case 0: return x;
	case 1: return y;
	default: return blank;
	}
}

VN::VN(const std::string& line) {

	std::vector<float> f = Extract_Float_Vector(line);

	if (f.size() < 3)
		return;

	x = f[0];
	y = f[1];
	z = f[2];

	valid = true;

}

const float& VN::operator[](int i) const
{
	static const float blank = 0.0f;

	switch (i)
	{
	case 0: return x;
	case 1: return y;
	case 2: return z;
	default: return blank;
	}
}

G::G(const std::string& line) {
	name = Extract_Attrib(line);
}

O::O(const std::string& line){
	name = Extract_Attrib(line);
}


//Wavefront_OBJ_File Implementation:

//private:

void Wavefront_OBJ_File::Init() {

	mtllib_.clear();
	filename_.clear();
	loaded_ = false;

	o_.clear();
	g_.clear();
	v_.clear();
	vt_.clear();
	vn_.clear();
	f_.clear();
	comment_.clear();
	usemtl_.clear();
	smooth_ = false;

}

void Wavefront_OBJ_File::Parse_Lines(const std::vector<std::string>& lines) {

	int current_o = -1;
	int current_g = -1;

	for (const std::string& line : lines) {
		
		if (line.empty()) {
			continue;
		}

		if (Check_Type(line, "#")) {

			comment_.push_back(line);

		}
		else if (Check_Type(line, "mtllib")) {

			mtllib_ = Extract_Attrib(line);

		}
		else if (Check_Type(line, "o")) {

			current_o++;
			current_g = -1;
			o_.emplace_back(line);

		}
		else if (Check_Type(line, "g")) {
			current_g++;
			if (current_o < 0) {
				g_.emplace_back(line);
			}
			else {
				o_[current_o].g.emplace_back(line);
			}

		}
		else if (Check_Type(line, "usemtl")) {
			if (current_o < 0) {
				if (current_g < 0) {
					usemtl_ = Extract_Attrib(line);
				}
				else {
					g_[current_g].usemtl = Extract_Attrib(line);
				}
			}
			else {
				if (current_g < 0) {
					o_[current_o].usemtl = Extract_Attrib(line);
				}
				else {
					o_[current_o].g[current_g].usemtl = Extract_Attrib(line);
				}
			}
		}
		else if (Check_Type(line, "s") || Check_Type(line, "smooth")) {

			bool s = Extract_Smooth(line);

			if (current_o < 0) {
				if (current_g < 0) {
					smooth_ = s;
				}
				else {
					g_[current_g].smooth = s;
				}
			}
			else {
				if (current_g < 0) {
					o_[current_o].smooth = s;
				}
				else {
					o_[current_o].g[current_g].smooth = s;
				}
			}
		}
		else if (Check_Type(line, "f")) {
			
			if (current_o < 0) {
				if (current_g < 0) {
					f_.emplace_back(line);
				}
				else {
					g_[current_g].f.emplace_back(line);
				}
			}
			else {
				if (current_g < 0) {
					o_[current_o].f.emplace_back(line);
				}
				else {
					o_[current_o].g[current_g].f.emplace_back(line);
				}
			}

		}
		else if (Check_Type(line, "v")) {

			v_.emplace_back(line);

		}
		else if (Check_Type(line, "vt")) {

			vt_.emplace_back(line);

		}
		else if (Check_Type(line, "vn")) {

			vn_.emplace_back(line);

		}

	}

}

bool Wavefront_OBJ_File::Load_File(const std::string& file_name) {
	
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

	//if (!Parse_Lines(lines)) {
	//	return false;
	//}

	loaded_ = true;

	return true;

}



//Public:

//Constructors
Wavefront_OBJ_File::Wavefront_OBJ_File() {
	Init();
}

Wavefront_OBJ_File::Wavefront_OBJ_File(const std::string& file_name) {

	Init();
	Load_File(file_name);

}

//Getters
const O& Wavefront_OBJ_File::Get_O(const int index) const
{
	static O blank;

	if (index < 0 || index >= (int)o_.size())
		return blank;

	return o_[index];

}

const G& Wavefront_OBJ_File::Get_G(const int index) const
{
	static G blank;

	if (index < 0 || index >= (int)g_.size())
		return blank;

	return g_[index];
}

const V& Wavefront_OBJ_File::Get_V(const int index) const
{

	static V blank;

	if (index < 0 || index >= (int)v_.size())
		return blank;

	return v_[index];
}

const VT& Wavefront_OBJ_File::Get_VT(const int index) const
{

	static VT blank;

	if (index < 0 || index >= (int)vt_.size())
		return blank;

	return vt_[index];
}

const VN& Wavefront_OBJ_File::Get_VN(const int index) const
{

	static VN blank;

	if (index < 0 || index >= (int)vn_.size())
		return blank;

	return vn_[index];
}

const std::string& Wavefront_OBJ_File::Get_Filename() const {
	return filename_;
}
