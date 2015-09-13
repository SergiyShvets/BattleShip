#include "logger.h"
#include <ctime>

using namespace std;

LOG_LEVELS Logger::m_logLevel = ERR;
ofstream Logger::m_logStream;
long Logger::m_maxFileSize = -1;
string Logger::m_fileName;

const char * const LOG_LEVEL[] = { "ERROR", "WARNING", "INFO", "DEBUG", };

bool Logger::Open(const char *fname, LOG_LEVELS logLevel, long maxFileSize) {

	if (m_logStream.is_open()) {
		m_logStream.flush();
		m_logStream.close();
	}

	m_logLevel = logLevel;
	m_maxFileSize = maxFileSize;
	m_logStream.open(fname);

	bool retval = m_logStream.is_open();
	if (retval) {
		m_fileName = fname;

		char timebuff[26];
		tm newtime;
		time_t alloc;
		time(&alloc);
#ifdef _WIN32
		localtime(&alloc);
		asctime(&newtime);
#else
		localtime_r( &alloc, &newtime );
		asctime_r(&newtime, timebuff );
#endif
		asctime(&newtime);
		m_logStream << "Log started at " << timebuff << endl;
	}

	return retval;
}

void Logger::Close() {
	if (m_logStream.is_open()) {
		char timebuff[26];
		tm newtime;
		time_t alloc;
		time(&alloc);
#ifdef _WIN32
		localtime(&alloc);
		asctime(&newtime);
#else
		localtime_r( &alloc, &newtime );
		asctime_r(&newtime, timebuff );
#endif
		m_logStream << endl << "Log finished at " << timebuff << endl;
	}

}
ostream & Logger::Begin(LOG_LEVELS level) {
	time_t rawtime;
	::time(&rawtime);

	tm *timeinfo = ::localtime(&rawtime);
	char szTime[30];
	snprintf(szTime, 30, "%.2d:%.2d:%.2d", timeinfo->tm_hour, timeinfo->tm_min,
			timeinfo->tm_sec);

	m_logStream << szTime << "\t";

	if (level > DBG)
		m_logStream << "DEBUG" << "\t";
	else
		m_logStream << LOG_LEVEL[level] << "\t";

	return m_logStream;
}

ostream & Logger::End(std::ostream &os) {
	os << endl;
	ios::pos_type endPos = m_logStream.tellp();
	if (m_maxFileSize > 0 && endPos > m_maxFileSize) {
		if (m_logStream.is_open()) {
			m_logStream.flush();
			m_logStream.close();
			(void) remove(m_fileName.c_str());

			m_logStream.open(m_fileName.c_str());
		}
	}

	return m_logStream;
}
