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

	static void read_vertex(mesh &m, std::istream &is)
	{
		m.vertices.push_back(mesh::vertex());
		auto &v = m.vertices.back();
		is >> v.x >> v.y >> v.z;
	}

	static void read_texcoord(mesh &m, std::istream &is)
	{
		m.texcoords.push_back(mesh::texcoord());
		auto &vt = m.texcoords.back();
		is >> vt.s >> vt.t;
	}

	static void read_normal(mesh &m, std::istream &is)
	{
		m.normals.push_back(mesh::normal());
		auto &vn = m.normals.back();
		is >> vn.x >> vn.y >> vn.z;
	}

	static int read_index(std::istream &is)
	{
		std::string token;
		std::getline(is, token, '/');
		int index = 0;
		std::istringstream(token) >> index;
		return index - 1;
	}

	static void read_face_vertex(mesh &m, std::istream &is)
	{
		auto &f = m.faces.back();
		f.vertices.push_back(mesh::face::vertex());
		auto &fv = f.vertices.back();
		fv.v = read_index(is);
		fv.vt = read_index(is);
		fv.vn = read_index(is);
	}

	static void read_face(mesh &m, std::istream &is)
	{
		m.faces.push_back(mesh::face());
		std::string token;
		while (is >> token)
		{
			auto token_stream = std::istringstream(token);
			read_face_vertex(m, token_stream);
		}
	}

	static void read_line(mesh &m, std::istream &is)
	{
		std::string type;
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

	static void read_lines(mesh &m, std::istream &is)
	{
		std::string line;
		while (getline(is, line))
		{
			auto line_stream = std::istringstream(line);
			read_line(m, line_stream);
		}
	}

	void read(mesh &m, const char *filename)
	{
		auto filename_stream = std::ifstream(filename);
		read_lines(m, filename_stream);
	}
}