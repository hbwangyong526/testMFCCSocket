#pragma once
class CTask
{
public:
	CTask(void);
	virtual ~CTask();

public:
	virtual void Run()=0;
};

