#pragma once

using namespace std; 

class CLog: public Singletion<CLog>
{
SINGLETON_INIT(CLog)

public:
	void trace(TCHAR*);
	void info(TCHAR*);
	void warn(TCHAR*);
	void error(TCHAR*);
	void fatal(TCHAR*);
	void debug(TCHAR*);
	void setLogMode(bool console, wstring& filename = wstring());
private:
	int init() override;
	int deInit() override;
public:
	Logger _logger;
};
