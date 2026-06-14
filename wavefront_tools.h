/*
This header contains some useful functions when parsing text files.
Copyright Dan Walton 2023
*/

#pragma once
#ifndef WAVEFRONT_TOOLS_H_INCLUDED
#define WAVEFRONT_TOOLS_H_INCLUDED

#include <vector>
#include <string>

std::vector<std::string> Get_Lines(const std::string& file_path);

bool Extract_Smooth(const std::string& s_line);

bool Decode_Face_Vertex(const std::string& slash_word, int& v, int& vt, int& vn);

std::vector<float> Extract_Float_Vector(const std::string& line);

float Extract_Float(const std::string& line);

int Extract_Int(const std::string& line);

std::vector<std::string> Extract_Face_Words(const std::string& f_line);

//Checks to see what type a line is:
//If line is 'v 0.0000 0.0000 0.0000', and we pass 'v' to 'type', returns TRUE.
bool Check_Type(const std::string& line, const std::string& type);

std::vector<float> Extract_Floats(const std::string& line);

//Grabs everything after the first 'word' in the sentence
//E.g. everything *after* the 'f', 'o', 'v', etc.
std::string Extract_Attrib(const std::string& line);

#endif