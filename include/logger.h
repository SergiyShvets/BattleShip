#ifndef _LOGFILE_
#define _LOGFILE_

#include <fstream>

enum LOG_LEVELS {
	ERR, WARN, INFO, DBG
};

class Logger {
private:
	static LOG_LEVELS m_logLevel;
	static std::ofstream m_logStream;
	static long m_maxFileSize;
	static std::string m_fileName;

public:
	static bool Open(const char * fname, LOG_LEVELS logLevel, long maxFileSize);
	static void Close();

	static std::ostream & Begin(LOG_LEVELS level);
	static std::ostream & End(std::ostream & os);
	static bool CanTrace(LOG_LEVELS level) {
		return m_logStream.is_open() && level <= m_logLevel;
	}
};

#define LOG( level, args )	\
		if(!Logger::CanTrace( level ));else \
		Logger::Begin( level ) << args << Logger::End

#endif
