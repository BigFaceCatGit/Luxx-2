#include "stdafx.h"
#include "webFunctions.h"
#include "WinHttpClient.h"
#include "sha256.h"
#include <tchar.h>
#include "boost\lexical_cast.hpp"

namespace auth {
	Ini Auth("auth");
	network server(L"https://luxx.menu/auth/");
	std::string rndShit[]{
		"WbdYpWaY8GFGtCLyJ",
		"EtjZbTz5yde6RxHFu",
		"rs7SfNKDQjHcfHRD5",
		"FU5R2Tds88a39SHdf",
		"mtguYQe5kVthPuu3e",
		"ZnxmjmBAAxwwHe6eT",
		"w3DVqKhfg2UXJP6kJ",
		"fBs5bjUuP34tmRKEA",
		"fYzJB235nQvLPN7nh",
		"muzn4ZJhYpyGbQBMp",
		"qDfZsaBTpgNffEdxD",
		"4kgRhXeN3uReKZ2ww",
		"JesBFthkY8azt37sz",
		"MJrWrDJhNTukGaFAp",
		"L2dXUB3y9hYpHkuUj",
		"Y7PPbnveTvVau7NB3",
		"wCDyCfa5HwzW6zv3m",
		"R7J2FBt75j2WS8c5v",
		"K7UxBfT62XfH2SEWf"
	};
	std::vector<std::wstring> responses;
	std::string getHWID() {
		char hwid[4096];

		// total physical memory
		MEMORYSTATUSEX statex;
		statex.dwLength = sizeof(statex);
		GlobalMemoryStatusEx(&statex);
		sprintf_s(hwid, "%I64i", statex.ullTotalPhys / 1024);

		// volume information
		TCHAR volume_name[MAX_PATH + 1] = { 0 };
		TCHAR filesystem_name[MAX_PATH + 1] = { 0 };
		DWORD serial_number = 0, maxcomponentlen = 0, filesystemflags = 0;
		GetVolumeInformation(_T("C:\\"), volume_name, ARRAYSIZE(volume_name), &serial_number, &maxcomponentlen, &filesystemflags, filesystem_name, ARRAYSIZE(filesystem_name));
		sprintf_s(hwid, "%s%li%ws%li", hwid, serial_number, filesystem_name, maxcomponentlen);

		// computer name
		TCHAR computer_name[MAX_COMPUTERNAME_LENGTH + 1];
		DWORD size = sizeof(computer_name) / sizeof(computer_name[0]);
		GetComputerName(computer_name, &size);
		sprintf_s(hwid, "%s%ws", hwid, computer_name);

		// hash the hwid we made
		std::string hHwid = sha256(boost::lexical_cast<std::string>(hwid));
		std::string lM = hwid + (std::string)" hashed to " + hHwid;
		CLog::Message(&lM[0u]);
		return hHwid;
	}
	void readFile(std::string *discord, std::string *token, std::string *scid) {
		std::string ldiscord = Auth.read("Auth", "reference");//
		std::string ltoken = Auth.read("Auth", "token");//auth_file.readLine(2);
		std::string lscid = static_cast<std::string>(SOCIALCLUB::_SC_GET_NICKNAME());
		*(std::string*)discord = ldiscord;
		*(std::string*)token = ltoken;
		*(std::string*)scid = lscid;
		CLog::Message("User= %s Discord= %s", ldiscord, ltoken);
	}
	bool signIn(bool notify = false) {

		std::string discord, token, scid, hashed_hwid_string = getHWID();
		// get their discord, token and construct the post message
		readFile(&discord, &token, &scid);
		std::string message = "scid=" + scid + "&hwid=" + hashed_hwid_string + "&reference=" + discord + "&token=" + token + "&version=" + NativeMenu::CMenu::mVer;
		//std::string message = "scid=" + scid + "&hwid=" + hashed_hwid_string + "&username=" + file::ReadIniKey("auth", "Test", "username") + "&password=" + file::ReadIniKey("auth", "Test", "username") + "&version=" + versionNo;
		// make the post request
		std::wstring response = server.post(message);

		// check if the response has been made before, we only allow 2 same responses
		static int repeat_count = 0;
		for (auto &check : responses) {
			if (check == response) {
				repeat_count += 1;
				if (repeat_count == 2) {
					Features::CUtil::notifyError("Dulplicate Response Received, Forcing Exit");
					return false;
					//exit(0);
				}
			}
		}
		// add this response into the response vector
		responses.push_back(response);

		// cast to string
		std::string str_response; str_response.assign(response.begin(), response.end());
		//Log::Msg(const_cast<char*>(str_response.c_str()));

		//tsOut(str_response);

		if (str_response.find(hashed_hwid_string) == std::string::npos) {
			Features::CUtil::notifyError(str_response); //when using with luxx, change this to game::notifyError(str_response); and remove error from the start of the response.
			return false;
		}

		// split the response into a vector
		std::size_t position = 0; std::string split_token; std::vector<std::string> contents;
		while ((position = str_response.find("q")) != std::string::npos) {
			split_token = str_response.substr(0, position);
			contents.push_back(split_token);
			str_response.erase(0, position + 1);
		}

		contents.push_back(str_response);
		CLog::Message("Split into the vector");

		std::string token1 = rndShit[atoi(contents[1].c_str())],
			token2 = rndShit[atoi(contents[4].c_str())],
			token3 = rndShit[atoi(contents[2].c_str())],
			token4 = rndShit[atoi(contents[5].c_str())],
			combined_unhashed_token = token1 + token2 + token3 + token4,
			hashed_token = sha256(combined_unhashed_token);

		if (hashed_token == contents[3]) {
			//version = "premium";	//Standard Luxx Premium
			Features::CUtil::notifyMap("~g~Premium Version", 1);
			return true;
		}

		token1 = rndShit[atoi(contents[4].c_str())];
		token2 = rndShit[atoi(contents[1].c_str())];
		token3 = rndShit[atoi(contents[5].c_str())];
		token4 = rndShit[atoi(contents[2].c_str())];
		combined_unhashed_token = token1 + token2 + token3 + token4;
		hashed_token = sha256(combined_unhashed_token);

		if (hashed_token == contents[3]) {
			//version = "legacy";	//Legacy Only
			Features::CUtil::notifyMap("~y~Legacy Version", 1);
			return true;
		}

		token1 = rndShit[atoi(contents[5].c_str())];
		token2 = rndShit[atoi(contents[4].c_str())];
		token3 = rndShit[atoi(contents[2].c_str())];
		token4 = rndShit[atoi(contents[1].c_str())];
		combined_unhashed_token = token1 + token2 + token3 + token4;
		hashed_token = sha256(combined_unhashed_token);

		if (hashed_token == contents[3]) {
			//version = "elite";	//LUXX Elite (STAFF) + Recovery (include this in recovery version)
			Features::CUtil::notifyMap("~q~Elite Version", 1);
			return true;
		}
		
		CLog::Error(&str_response[0u]);
		Features::CUtil::notifyError(str_response);
		return false;
	}
}
namespace remote {
	//Set access to my remote functions server
	network remoteServer(L"http://luxx.menu/remote/remote.php");

	//store last string to stop duplicates in game
	std::string lastNotice = "";
	std::string verify = "verify=" + static_cast<std::string>("ddbde340b6cd8fed42a482dd9811a9aaf82c73c7e4cb47de53bb41fedad98c34");

	std::string serverCall(std::string request) {

		//build post message using request data
		std::string requestType = "request=" + request;
		std::string postMsg = requestType + "&" + verify;

		//recieve info matching notice
		std::wstring response = remoteServer.post(postMsg);

		//cast wstring response to string
		std::string str_response; str_response.assign(response.begin(), response.end());

		return str_response;
	}
	std::string serverCall(std::string request, std::string token) {

		//build post message using request data
		std::string userToken = "token=" + token; //to be replaced with token grab function
		std::string postMsg = request + "&" + userToken;

		//call standard function
		std::string response = serverCall(postMsg);//; str_response.assign(response.begin(), response.end());

		return response;
	}
	int ticks;
	void pingServer() {

		Features::CUtil::notifyMap("Pinging Server. . .", 0);
		ticks = GetTickCount();
		if (serverCall("ping") == "Pong.") {
			Features::CUtil::notifyMap("Pong.", 0);
			ostringstream st;
			st << GetTickCount() - ticks;
			Features::CUtil::notifyMap("Server Round Trip took " + st.str() + " ticks.", 0);
		}
		else
			Features::CUtil::notifyMap("Server Unavailable", 0);
	}
	bool checkNotices(std::string *notice) {

		//NOTE: There is a very large limit on the max length that I can receive. However I will limit the display length before anything else.

		//get response from server
		std::string response = serverCall("notice");

		if (response != "Blank") {
			*(std::string*)notice = response;
			if (!(response == lastNotice)) {
				lastNotice = response;
				return true;
			}
			else
				Features::CUtil::notifyMap("No new Server Messages", 0);
		}
		else {
			*(std::string*)notice = "";
			Features::CUtil::notifyMap(response, 0);
		}
		return false;
	}
	void versionCheck() {
		std::string response = serverCall("version");

		if (response.find("version") == std::string::npos) {
			Features::CUtil::notifyMap(response, 0); //when using with luxx, change this to game::notifyError(str_response); and remove error from the start of the response.
			return;
		}

		if (response.find("1.5") == std::string::npos)
			Features::CUtil::notifyMap("~g~Update Available: ~w~"s + response + " download from now!"s, 1); //when using with luxx, change this to game::notifyError(str_response); and remove error from the start of the response.
		else
			Features::CUtil::notifyMap("egg" + " is the most recent version"s, 0);
	}
	void checkNotices() {

		//create notice for future use
		std::string notice;

		if (checkNotices(&notice)) {
			Features::CUtil::notifyMap(notice, 0); //when using with luxx, change this to game::notifyError(str_response); and remove error from the start of the response.
		}
	}
}