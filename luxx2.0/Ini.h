#ifndef ALPHA_INI_H
#define ALPHA_INI_H
#include "menuBase.h"

struct rgba {
	int r;
	int g;
	int b;
	int a;
};

class Ini {

protected:
	std::string filename;
	std::string filepath;
	std::string fullpath;

public:
	/* When Declaring leave the default folder blank to avoid overloads (std::string folder = "") */
	Ini(std::string name, std::string folder = "LUXX\\");

	~Ini();

	/* Returns the Filepath */
	std::string path();

	/* Returns the FileName */
	std::string name();

	/* fopen test to check if file exists */
	bool exists();

	/* Write Value to Section, Identified by Key inside the INI obj */
	bool write(std::string section, std::string key, std::string value);

	/* Writes the Default File Values, Called on file creation/if file is not found, Defaults will be stored as objects and called dependent on file type */
	bool write_d();

	/* Write Int Values */
	bool write_i(int integer, std::string section, std::string key);

	/* Write Float Values */
	bool write_f(float flt, std::string section, std::string key);

	/* Write Bool Values in Plaintext for ease of editing */
	bool write_b(bool b00l, std::string section, std::string key);

	/* Better way of saving RGBA Values */
	bool write_rgba(NativeMenu::RGBA &rgba, std::string key, std::string value);

	/* Better Vector Saving */
	bool write_v3(Vector3 vector, std::string key, std::string value);

	/* Write the contents of a vector to file*/
	bool write_v(std::vector<std::string> vector, std::string section, std::string key = "");

	/* Returns Value gathered through Section and Key of File Object*/
	std::string read(std::string section, std::string key);

	/* Return int Value */
	int read_i(std::string section, std::string key);

	/* Return float Value */
	float read_f(std::string section, std::string key);

	/* Return b00l Value from plaintext */
	bool read_b(std::string section, std::string key);

	/* Return RGBA Value */
	NativeMenu::RGBA read_rgba(std::string section, std::string key);

	/* Return Vector3 Value */
	Vector3 read_v3(std::string section, std::string key);

	/* Simple Bool return to check if Data Exists*/
	bool keyExist(std::string key, std::string value);
	int numObjects(std::string section, std::string key = "");
	std::vector<std::string> returnList(std::string section, std::string key = "");
};

#endif