#include "stdafx.h"
#include "globalRes.h"
#include "InitPara.h"


int CLog::init()
{
	log4cplus::initialize();
	return 0;
}

int CLog::deInit()
{
	log4cplus::threadCleanup();
	return 0;
}

void CLog::trace( TCHAR* str)
{
	LOG4CPLUS_TRACE(_logger, str);
}

void CLog::info( TCHAR* str)
{
	LOG4CPLUS_INFO(_logger, str);
}

void CLog::warn( TCHAR* str)
{
	LOG4CPLUS_WARN(_logger, str);
}

void CLog::error( TCHAR* str)
{
	LOG4CPLUS_ERROR(_logger, str);
}

void CLog::fatal( TCHAR* str)
{
	LOG4CPLUS_FATAL(_logger, str);
}

void CLog::debug( TCHAR* str)
{
	LOG4CPLUS_DEBUG(_logger, str);
}

void CLog::setLogMode( bool console, wstring& filename )
{
	_logger = Logger::getInstance(LOG4CPLUS_TEXT("test")); 
	Appender* app2 = nullptr;
	if (filename.empty() == false)
	{
		string filePath = CInitPara::getSingleton()->getPara()->rootPath;
		filePath += "/log/";
		if (0 != _access_s(filePath.c_str(), 0)){
			_mkdir(filePath.c_str());
		}
		std::wstring wstr(filePath.length(),L' ');
		std::copy(filePath.begin(), filePath.end(), wstr.begin());
		wstr += filename;
		app2 = new RollingFileAppender( wstr, 1024*1024*200, 50 );

		/* step 1: Instantiate an appender object */  
		SharedObjectPtr<Appender> _append (app2);    
		_append->setName(LOG4CPLUS_TEXT("append for test"));   
		/* step 2: Instantiate a layout object */    
		//std::string pattern = ;   
		//std::auto_ptr<Layout> _layout(new PatternLayout(LOG4CPLUS_TEXT("%D{%m/%d/%y %H:%M:%S}  - %m [%l]%n")));  
		std::auto_ptr<Layout> _layout(new PatternLayout(LOG4CPLUS_TEXT("%D{%m/%d/%y %H:%M:%S:%q}--%m--%t%n")));   
		/* step 3: Attach the layout object to the appender */   
		_append->setLayout( _layout );   
		/* step 4: Instantiate a logger object */   
		//	_logger = Logger::getInstance(LOG4CPLUS_TEXT("test"));  
		/* step 5: Attach the appender object to the logger  */  
		_logger.addAppender(_append);   
	}
	//加入打印文件
	if (console)
	{
		/* step 1: Instantiate an appender object */  
		SharedObjectPtr<Appender> _append (new ConsoleAppender());    
		_append->setName(LOG4CPLUS_TEXT("append for test"));   
		/* step 2: Instantiate a layout object */    
		//std::string pattern = ;   
		//std::auto_ptr<Layout> _layout(new PatternLayout(LOG4CPLUS_TEXT("%D{%m/%d/%y %H:%M:%S}  - %m [%l]%n")));  
		std::auto_ptr<Layout> _layout(new PatternLayout(LOG4CPLUS_TEXT("%D{%m/%d/%y %H:%M:%S:%q}--%m--%t%n")));   
		/* step 3: Attach the layout object to the appender */   
		_append->setLayout( _layout );   
		_logger.addAppender(_append);
	}
	/* step 6: Set a priority for the logger  */   
	_logger.setLogLevel(ALL_LOG_LEVEL);   
}

