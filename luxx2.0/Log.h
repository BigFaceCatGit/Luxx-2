#ifndef ALPHA_LOG_H
#define ALPHA_LOG_H

/*
Credits to Sub1to for his Log init. Only thing I want to change about this is the output shite.
Make it delete everything once the game gets restarted. Right now, it's just plowing logs into a
single file without clearing anything.

Also change the location of the log. It's in appdata right now.
Preferably where the DLL gets injected or into GTAV main directory.
*/

typedef std::vector<std::string> vec_str;

class CLog
{
public:
	static vec_str		m_msg;
	static vec_str		m_error;
	static vec_str		m_fatal;

	static bool	Init(std::string szDir);
	static void Message(char* msg, ...);
	static void Error(char* error, ...);
	static void	Fatal(char* erro, ...);

protected:
	static std::string	m_szFile;
	static std::string	log(char*, char*, va_list vars);
};

#endif
