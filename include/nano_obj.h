/*
	Copyright 2015 Sebastian Viklund
	Licenced under the zlib licence
*/

#pragma once

/*
	Copyright 2015 Sebastian Viklund
	Licenced under the zlib licence
*/

#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

namespace obj
{

	struct mesh
	{
		struct vertex
		{
			float x = 0.0f, y = 0.0f, z = 0.0f;
		};
		struct texcoord
		{
			float s = 0.0f, t = 0.0f;
		};
		struct normal
		{
			float x = 0.0f, y = 0.0f, z = 0.0f;
		};

		struct face
		{
			struct vertex
			{
				int v = -1, vt = -1, vn = -1;
			};
			std::vector<vertex> vertices;
		};

		std::vector<vertex> vertices;
		std::vector<texcoord> texcoords;
		std::vector<normal> normals;
		std::vector<face> faces;
	};

	static void read_vertex(mesh &m, istream &is)
	{
		m.vertices.push_back(mesh::vertex());
		auto &v = m.vertices.back();
		is >> v.x >> v.y >> v.z;
	}

	static void read_texcoord(mesh &m, istream &is)
	{
		m.texcoords.push_back(mesh::texcoord());
		auto &vt = m.texcoords.back();
		is >> vt.s >> vt.t;
	}

	static void read_normal(mesh &m, istream &is)
	{
		m.normals.push_back(mesh::normal());
		auto &vn = m.normals.back();
		is >> vn.x >> vn.y >> vn.z;
	}

	static int read_index(istream &is)
	{
		string token;
		getline(is, token, '/');
		int index = 0;
		istringstream(token) >> index;
		return index - 1;
	}

	static void read_face_vertex(mesh &m, istream &is)
	{
		auto &f = m.faces.back();
		f.vertices.push_back(mesh::face::vertex());
		auto &fv = f.vertices.back();
		fv.v = read_index(is);
		fv.vt = read_index(is);
		fv.vn = read_index(is);
	}

	static void read_face(mesh &m, istream &is)
	{
		m.faces.push_back(mesh::face());
		string token;
		while (is >> token)
			read_face_vertex(m, istringstream(token));
	}

	static void read_line(mesh &m, istream &is)
	{
		string type;
		is >> type;
		if (type == "v")
			read_vertex(m, is);
		else if (type == "vt")
			read_texcoord(m, is);
		else if (type == "vn")
			read_normal(m, is);
		else if (type == "f")
			read_face(m, is);
	}

	static void read_lines(mesh &m, istream &is)
	{
		string line;
		while (getline(is, line))
			read_line(m, istringstream(line));
	}

	void read(mesh &m, const char *filename)
	{
		read_lines(m, ifstream(filename));
	}
}