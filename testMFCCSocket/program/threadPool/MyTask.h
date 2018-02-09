#pragma once

#include "Task.h"
#include <typeinfo>
class ParamTem
{
protected:
	ParamTem(){};
};


template <class ReturnType,class P0=ParamTem,class P1=ParamTem,
class P2=ParamTem,class P3=ParamTem, class P4=ParamTem,
class P5=ParamTem,class P6=ParamTem, class P7=ParamTem>
class CMyTask: public CTask,public ParamTem
{
private:
	typedef ReturnType (*FuncTem)();
	typedef ReturnType (*FuncTem0)(P0 p0);
	typedef ReturnType (*FuncTem1)(P0 p0, P1 p1);
	typedef ReturnType (*FuncTem2)(P0 p0, P1 p1, P2 p2);
	typedef ReturnType (*FuncTem3)(P0 p0, P1 p1, P2 p2,P3 p3);
	typedef ReturnType (*FuncTem4)(P0 p0, P1 p1, P2 p2, P3 p3,P4 p4);
	typedef ReturnType (*FuncTem5)(P0 p0, P1 p1, P2 p2, P3 p3,P4 p4, P5 p5);
	typedef ReturnType (*FuncTem6)(P0 p0, P1 p1, P2 p2, P3 p3,P4 p4, P5 p5, P6 p6);
	typedef ReturnType (*FuncTem7)(P0 p0, P1 p1, P2 p2, P3 p3,P4 p4, P5 p5, P6 p6, P7 p7);
	FuncTem ft;
	FuncTem0 ft0;
	FuncTem1 ft1;
	FuncTem2 ft2;
	FuncTem3 ft3;
	FuncTem4 ft4;
	FuncTem5 ft5;
	FuncTem6 ft6;
	FuncTem7 ft7;
	P0 p0;
	P1 p1;
	P2 p2;
	P3 p3;
	P4 p4;
	P5 p5;
	P6 p6;
	P7 p7;
public:
	CMyTask(FuncTem ft)
	{
		this->ft = ft;
	}
	CMyTask(FuncTem0 ft,P0 p0)
	{
		this->ft0 = ft;
		this->p0 = p0;
	}
	CMyTask(FuncTem1 ft,P0 p0, P1 p1)
	{
		this->ft1 = ft;
		this->p0 = p0;
		this->p1 = p1;
	}
	CMyTask(FuncTem2 ft,P0 p0, P1 p1, P2 p2)
	{
		this->ft2 = ft;
		this->p0 = p0;
		this->p1 = p1;
		this->p2 = p2;
	}
	CMyTask(FuncTem3 ft,P0 p0, P1 p1, P2 p2, P3 p3)
	{
		this->ft3 = ft;
		this->p0 = p0;
		this->p1 = p1;
		this->p2 = p2;
		this->p3 = p3;
	}
	CMyTask(FuncTem4 ft,P0 p0, P1 p1, P2 p2, P3 p3,P4 p4)
	{
		this->ft4 = ft;
		this->p0 = p0;
		this->p1 = p1;
		this->p2 = p2;
		this->p3 = p3;
		this->p4 = p4;
	}
	CMyTask(FuncTem5 ft,P0 p0, P1 p1, P2 p2, P3 p3,P4 p4, P5 p5)
	{
		this->ft5 = ft;
		this->p0 = p0;
		this->p1 = p1;
		this->p2 = p2;
		this->p3 = p3;
		this->p4 = p4;
		this->p5 = p5;
	}
	CMyTask(FuncTem6 ft,P0 p0, P1 p1, P2 p2, P3 p3,P4 p4, P5 p5, P6 p6)
	{
		this->ft6 = ft;
		this->p0 = p0;
		this->p1 = p1;
		this->p2 = p2;
		this->p3 = p3;
		this->p4 = p4;
		this->p5 = p5;
		this->p6 = p6;
	}
	CMyTask(FuncTem7 ft,P0 p0, P1 p1, P2 p2, P3 p3,P4 p4, P5 p5, P6 p6, P7 p7)
	{
		this->ft7 = ft;
		this->p0 = p0;
		this->p1 = p1;
		this->p2 = p2;
		this->p3 = p3;
		this->p4 = p4;
		this->p5 = p5;
		this->p6 = p6;
		this->p7 = p7;
	}
	virtual void Run()
	{
		if(!strcmp(typeid(P0).name(),"class ParamTem"))
		{
			this->ft();
		}
		else if(!strcmp(typeid(P1).name(),"class ParamTem"))
		{
			this->ft0(this->p0);
		}
		else if(!strcmp(typeid(P2).name(),"class ParamTem"))
		{
			this->ft1(this->p0,this->p1);
		}
		else if(!strcmp(typeid(P3).name(),"class ParamTem"))
		{
			this->ft2(this->p0,this->p1,this->p2);
		}
		else if(!strcmp(typeid(P4).name(),"class ParamTem"))
		{
			this->ft3(this->p0,this->p1,this->p2,this->p3);
		}
		else if(!strcmp(typeid(P5).name(),"class ParamTem"))
		{
			this->ft4(this->p0,this->p1,this->p2,this->p3,this->p4);
		}
		else if(!strcmp(typeid(P6).name(),"class ParamTem"))
		{
			this->ft5(this->p0,this->p1,this->p2,this->p3,this->p4,this->p5);
		}
		else if(!strcmp(typeid(P7).name(),"class ParamTem"))
		{
			this->ft6(this->p0,this->p1,this->p2,this->p3,this->p4,this->p5\
				,this->p6);
		}
		else if(strcmp(typeid(P7).name(),"class ParamTem"))
		{
			this->ft7(this->p0,this->p1,this->p2,this->p3,this->p4,this->p5\
				,this->p6,this->p7);
		}
	}
};