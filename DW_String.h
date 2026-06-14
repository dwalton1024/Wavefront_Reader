#pragma once

#ifndef DW_STRING_H_INCLUDED
#define DW_STRING_H_INCLUDED

#include <string>
#include <vector>

std::vector<std::string> Parse_Lines(const std::string& text);

//Takes a vector<string> and converts it to vector<float>
std::vector<float> To_Floats(const std::vector<std::string>& strings);

bool Try_Parse_Float(const std::string& s, float& out);

bool Try_Parse_Int(const std::string& s, int& out);

//Parses only first word, if needed, to save computation time
std::string Parse_First_Word(const std::string& line);

//Parses a sentence string, by a specified delimiter
//Changes 'word1*word2*word3' into 'word1', 'word2', and 'word3' if delimiter is '*'
std::vector<std::string> Parse_By(const std::string& input, const std::string& delimiter);

// "0" "off" "OFF" "false" "FALSE" all mean FALSE
// Any value not explicitly false is treated as TRUE.
bool Parse_Bool(const std::string& attrib);

//Extracts words, also collapses all whitespace
std::vector<std::string> Parse_Words(const std::string& line);

#endif