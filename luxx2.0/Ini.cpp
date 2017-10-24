#include "stdafx.h"
#include "boost\lexical_cast.hpp"

/* Returns the Documents Path (Credz to Force, not the nicest function but it works) */
std::string DocumentsPath(bool trailing = 1) {
	wchar_t Folder[1024];
	HRESULT hr = SHGetFolderPathW(0, CSIDL_MYDOCUMENTS, 0, 0, Folder);
	if (SUCCEEDED(hr))
	{
		char str[1024];
		wcstombs(str, Folder, 1023);
		if (trailing)
			return str + (std::string)"\\";
		else return str;
	}
	else return "";
}

Ini::Ini(std::string name, std::string folder) {

	this->filename = name;
	this->filepath = DocumentsPath() + folder;
	this->fullpath = this->filepath + name + ".ini";

	if (!CreateDirectoryA(filepath.c_str(), NULL)) {
		if (this->exists()) {
			this->write_d();
		}
	}
}

Ini::~Ini() { }

std::string Ini::path() {
	return this->fullpath;
}

std::string Ini::name() {
	return this->filename;
}

inline bool Ini::exists() {
	if (FILE *file = fopen(&this->fullpath[0u], "r")) {
		fclose(file);
		return true;
	}
	else {
		std::ofstream Nfile(this->fullpath);
		Nfile.close();
		return false;
	}
}

bool Ini::write(std::string section, std::string key, std::string value) {
	/* Checks if the file exists */
	if (!std::ifstream(this->fullpath)) {
		std::ofstream file(this->fullpath);
		this->write_d();

	}
	/* Write Values to file*/
	WritePrivateProfileStringA(section.c_str(), key.c_str(), value.c_str(), this->fullpath.c_str());

	return this->keyExist(section, key);
}

bool Ini::write_d() {
	return true;
}

bool Ini::write_i(int integer, std::string section, std::string key) {
	return this->write(section, key, boost::lexical_cast<std::string>(integer));
}

bool Ini::write_f(float flt, std::string section, std::string key) {
	return this->write(section, key, boost::lexical_cast<std::string>(flt));
}

bool Ini::write_b(bool b00l, std::string section, std::string key) {
	std::string bStr;
	b00l ? bStr = "true" : bStr = "false";
	return this->write(section, key, bStr);
}

bool Ini::write_rgba(NativeMenu::RGBA &rgba, std::string section, std::string key) {
	this->write_i(rgba.r, section, key + "R");
	this->write_i(rgba.g, section, key + "G");
	this->write_i(rgba.b, section, key + "B");
	return this->write_i(rgba.a, section, key + "A");
}

bool Ini::write_v3(Vector3 vector, std::string section, std::string key) {
	this->write_f(vector.x, section, key + "X");
	this->write_f(vector.y, section, key + "Y");
	return this->write_f(vector.z, section, key + "Z");
}

bool Ini::write_v(std::vector<std::string> vector, std::string section, std::string key) {
	for (int i = 0; i < vector.size(); i++) {
		this->write(section, key + boost::lexical_cast<std::string>(i), vector[i]);
	}
	return this->read(section, key + "0") == vector[0];
}

bool Ini::write_h(Hash hash, std::string section, std::string key) {
	return this->write(section, key, boost::lexical_cast<std::string>(hash));
}

bool Ini::write_fav(fVehicle vehicle, int section) {

	std::string sec = boost::lexical_cast<std::string>(section);

	this->write_h(vehicle.hash, sec, "model");
	this->write(sec, "name", vehicle.name);
	return this->write(sec, "uName", vehicle.uName);
}

std::string Ini::read(std::string section, std::string key) {

	/* Checks if the file exists */
	if (!std::ifstream(this->fullpath)) {
		std::ofstream file(this->fullpath);
		this->write_d();
	}

	char retVal[255];
	GetPrivateProfileStringA(section.c_str(), key.c_str(), "", retVal, 255, this->fullpath.c_str());
	return retVal;
}

int Ini::read_i(std::string section, std::string key) {
	return stoi(this->read(section, key));
}

float Ini::read_f(std::string section, std::string key) {
	return std::stof(this->read(section, key));
}

bool Ini::read_b(std::string section, std::string key) {
	if (this->read(section, key) == "true")
		return true;
	else if (this->read(section, key) == "false")
		return false;
}

NativeMenu::RGBA Ini::read_rgba(std::string section, std::string key) {

	if (!this->keyExist(section, key + "R")) { Features::CUtil::notifyError("Theme failed to load. Are you sure it exists?"); return { 0,0,0,0 }; }

	//cout << this->read(section, key + "R"s) << std::endl;
	return {
		this->read_i(section, key + "R"),
		this->read_i(section, key + "G"),
		this->read_i(section, key + "B"),
		this->read_i(section, key + "A")
	};
}

Vector3 Ini::read_v3(std::string section, std::string key) {
	return {
		this->read_f(section, key + "X"), 0,
		this->read_f(section, key + "Y"), 0,
		this->read_f(section, key + "Z"), 0
	};
}

Hash Ini::read_h(std::string section, std::string key) {
	return std::stoul(this->read(section, key));
}

fVehicle Ini::read_fav(int section) {

	std::string sec = boost::lexical_cast<std::string>(section);

	Hash hash = this->read_h(sec, "model");
	std::string name = this->read(sec, "name");
	std::string uName = this->read(sec, "uName");

	return { hash, name, uName };
}

bool Ini::keyExist(std::string section, std::string key) {
	return this->read(section, key).length() > 0;
}

int Ini::numKeys(std::string section, std::string key) {
	int no = 0;
	for (int i = 0; i < 150; i++) {
		std::stringstream ss;
		ss << i;
		if (this->keyExist(section, key + ss.str()))
			no++;
		else return no;
	}
	return no;
}

int Ini::numSections(std::string key) {
	int no = 0;
	for (int i = 0; i < 150; i++) {
		if (this->keyExist(boost::lexical_cast<std::string>(i), key))
			no++;
		else return no;
	}
	return no;
}

std::vector<std::string> Ini::returnList(std::string section, std::string key) {
	std::vector<std::string> returnV;
	for (int i = 0; i <= numKeys(section, key); i++){
		std::stringstream ss;
		ss << i;
		returnV.push_back(this->read(section, key + ss.str()));
	}
	return returnV;
}
