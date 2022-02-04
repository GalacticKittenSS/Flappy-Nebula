#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <functional>

class WritetoFile {
public:
	WritetoFile(const std::string& file) {
		m_File.open(file.c_str());
	}

	~WritetoFile() {
		m_File.close();
	}

	void WriteHighScore(int score, const std::string& name) {
		m_File << score << " " << name << "\n";
	}

	void Write(const std::string& str) {
		m_File << str;
	}

	void EndLine() {
		m_File << "\n";
	}

	void Close() {
		m_File.close();
	}
private:
	std::ofstream m_File;
};


class ReadfromFile {
public:
	ReadfromFile(const std::string& file) {
		m_File.open(file.c_str());
	}

	~ReadfromFile() {
		m_File.close();
	}

	template <typename function>
	void ReadHighScore(function func) {
		int Score; std::string Name;
		while (m_File >> Score >> std::ws && getline(m_File, Name)) {
			func(Name, Score);
		}
	}

	void Close() {
		m_File.close();
	}
private:
	std::ifstream m_File;
};