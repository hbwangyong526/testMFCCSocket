#pragma once

template<typename T>
class Singletion
{
	friend T;
private:
	Singletion(){}
	virtual ~Singletion(){}

	static T* pObject;

	//利用此类析构函数释放单例实例内存
	class CCarbageCollector
	{
	public:
		~CCarbageCollector()
		{
			if(Singletion<T>::pObject != NULL)
			{
				delete Singletion<T>::pObject;
			}
		}
	};

protected:

	//提供给单例类的初始化接口
	virtual int init()=0;
	virtual int deInit()=0;

public:
	//获取单例
	inline static T* getSingleton()
	{
		//用于系统退出时释放单例实例的内存
		static Singletion<T>::CCarbageCollector CarCo;

		pObject==NULL && (pObject=new T);
		return pObject;
	}

};

template<typename T>
T* Singletion<T>::pObject = NULL;

#define SINGLETON_INIT(ClassType)\
	friend ClassType* Singletion<ClassType>::getSingleton();\
	friend Singletion<ClassType>::CCarbageCollector;\
	public:\
	ClassType(){init();}\
	virtual ~ClassType(){deInit();}
