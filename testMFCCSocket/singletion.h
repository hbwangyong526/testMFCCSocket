#pragma once

template<typename T>
class Singletion
{
	friend T;
private:
	Singletion(){}
	virtual ~Singletion(){}

	static T* pObject;

	//���ô������������ͷŵ���ʵ���ڴ�
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

	//�ṩ��������ĳ�ʼ���ӿ�
	virtual int init()=0;
	virtual int deInit()=0;

public:
	//��ȡ����
	inline static T* getSingleton()
	{
		//����ϵͳ�˳�ʱ�ͷŵ���ʵ�����ڴ�
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
