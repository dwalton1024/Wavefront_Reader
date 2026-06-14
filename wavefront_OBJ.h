// Copyright (c) 2026 Dan Walton
// Licensed under the MIT License.

#pragma once
#ifndef WAVEFRONT_OBJ_H_INCLUDED
#define WAVEFRONT_OBJ_H_INCLUDED

#include <vector>
#include <string>

struct F_Vert
{

	int v = -1;
	int vt = -1;
	int vn = -1;

	F_Vert() = default;

};

struct F
{

	std::vector<F_Vert> f_verts_;

	F() = default;

	F(const std::string& f_line);

};

struct V
{
	float x = -999999.0f;
	float y = -999999.0f;
	float z = -999999.0f;

	bool valid = false;

	V() = default;

	V(const std::string& line);

	const float& operator[](int i) const;

};

struct VT
{
	float x = -999999.0f;
	float y = -999999.0f;

	bool valid = false;

	VT() = default;

	VT(const std::string& line);

	const float& operator[](int i) const;

};

struct VN
{
	float x = -999999.0f;
	float y = -999999.0f;
	float z = -999999.0f;

	bool valid = false;

	VN() = default;

	VN(const std::string& line);

	const float& operator[](int i) const;

};

struct G
{
	std::string name;

	std::string usemtl;

	bool smooth = 0;

	std::vector<F> f;

	G() = default;

	G(const std::string& line);

};

struct O
{
	std::string name;
	
	std::string usemtl;
	
	bool smooth = 0;

	std::vector<G> g;

	std::vector<F> f;

	O() = default;

	O(const std::string& line);

};

class Wavefront_OBJ_File {
private:

	std::vector<O> o_;
	std::vector<G> g_;

	std::vector<V> v_;
	std::vector<VT> vt_;
	std::vector<VN> vn_;

	std::vector<F> f_;

	std::string filename_;

	std::string mtllib_;

	std::string usemtl_;

	bool smooth_ = false;

	std::vector<std::string> comment_;

	bool loaded_ = false;

	//Will parse a default vert for bad vert data, because we don't want to invalidate face indices.
	void Parse_Lines(const std::vector<std::string>& lines);

	bool Load_File(const std::string& file_name);

	void Init();

protected:

public:

	Wavefront_OBJ_File& operator= (const Wavefront_OBJ_File& param) = default;

	Wavefront_OBJ_File();

	Wavefront_OBJ_File(const std::string& file_name);

	const std::string& Get_Filename() const;

	// Returns a static blank object if index is out of range.
	const O& Get_O(const int index) const;

	const G& Get_G(const int index) const;

	const V& Get_V(const int index) const;

	const VT& Get_VT(const int index) const;

	const VN& Get_VN(const int index) const;

};

#endif