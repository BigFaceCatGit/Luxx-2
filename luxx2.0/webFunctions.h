#pragma once

#ifndef WEB_FUNCTIONS_H
#define WEB_FUNCTIONS_H

namespace auth {

	extern std::string rndShit[];
	extern std::vector<std::wstring> responses;
	std::string getHWID();
	void readFile(std::string * discord, std::string * token, std::string * scid);
	bool signIn(bool notify);
}

namespace remote {
	std::string serverCall(std::string request);
	std::string serverCall(std::string request, std::string token);
	void pingServer();
	bool checkNotices(std::string * notice);
	void versionCheck();
	void checkNotices();
}
#endif // !WEB_FUNCTIONS_H
