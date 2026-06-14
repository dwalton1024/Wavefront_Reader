/*
This header contains library classes and functions to facilitate the
object-oriented use of wavefront .mtl files that accompany the .obj files.
Comes in handy when exporting 3D models.
Copyright Dan Walton 2023
*/

#pragma once
#ifndef WAVEFRONT_MTL_H_INCLUDED
#define WAVEFRONT_MTL_H_INCLUDED

#include <vector>
#include <string>

struct RGB
{

    float r = -99999.999f;
    float g = -99999.999f;
    float b = -99999.999f;

    bool valid = false;

    RGB() = default;

    bool Parse_RGB(const std::string& RGB_Line);

};

struct NEWMTL
{

    std::string name_;

    RGB Ka_;     // ambient
    RGB Kd_;     // diffuse
    RGB Ks_;     // specular
    RGB Ke_;     // emissive, common extension


    float Ns  = -99999.999;    // shininess/spec exponent
    float Ni  = -99999.999;    // optical density / IOR
    float d   = -99999.999;    // dissolve / opacity
    float Tr  = -99999.999;    // inverse-ish transparency, legacy annoyance
    int illum = -99999;        // illumination model

    std::string map_Ka;
    std::string map_Kd;
    std::string map_Ks;
    std::string map_Ns;
    std::string map_d;
    std::string bump;
    std::string map_Bump;

    std::vector<std::string> comments_;
    std::vector<std::string> unknown_lines_;

    bool valid = false;

    NEWMTL(const std::string& Newmtl_Line);

};

class Wavefront_MTL_File {
private:

	std::string filename_;

	int material_count_;

	std::vector<std::string> comments_;

	std::vector<NEWMTL> newmtl_;

    std::vector<std::string> unknown_lines_;

	bool loaded_;

	void Init();

	bool Load_File(const std::string& file_name);

	//Will parse a default vert for bad vert data, because we don't want to invalidate face indices.
	void Parse_Lines(const std::vector<std::string>& lines);

protected:

public:

	Wavefront_MTL_File& operator= (const Wavefront_MTL_File& param) = default;

	Wavefront_MTL_File();

	Wavefront_MTL_File(const std::string& file_name);

    //Gotta make getters

};

#endif