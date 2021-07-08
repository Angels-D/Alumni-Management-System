#pragma once
#include<string>//值类型（使用字符串类节省空间，方便操作）
#include<map>//储存单位信息
//基本框架
namespace Data//数据类型
{
	const int maxLong = 20;
	//基本类型
	template<typename T>
	class Basic
	{
	private:
		T Data;//储存值
	public:
		virtual bool Value()const { return true; }//判断合法
		Basic(const T& a = NULL) :Data(a) {}
		void set(const T& a) { Data = a; }//设置值
		operator T()const { return Data; }//显示值
	};
	//编码（序号、学校代码）
	template<typename T>
	class Id :public Basic<T> {
	public:
		virtual bool Value()const;
		Id(const T& a = NULL) :Basic<T>(a) {}
	};
	//名字（校友姓名）
	template<typename T>
	class Name :public Basic<T> {
	public:
		virtual bool Value()const;
		Name(const T& a = NULL) :Basic<T>(a) {}
	};
	//电话（电话）
	template<typename T>
	class Phone :public Basic<T> {
	public:
		virtual bool Value()const;
		Phone(const T& a = NULL) :Basic<T>(a) {}
	};
	//专业（专业）
	template<typename T>
	class Major :public Basic<T> {
	public:
		virtual bool Value()const;
		Major(const T& a = NULL) :Basic<T>(a) {}
	};
	//职业（现从事的专业）
	template<typename T>
	class Job :public Basic<T> {
	public:
		virtual bool Value()const;
		Job(const T& a = NULL) :Basic<T>(a) {}
	};
	//职务（职务）
	template<typename T>
	class Work :public Basic<T> {
	public:
		virtual bool Value()const;
		Work(const T& a = NULL) :Basic<T>(a) {}
	};
	//年限（工作年限）
	template<typename T>
	class Time :public Basic<T> {
	public:
		virtual bool Value()const;
		Time(const T& a = NULL) :Basic<T>(a) {}
	};
	//地址（所在城市、地址、办公地点）
	template<typename T>
	class Address :public Basic<T> {
	public:
		virtual bool Value()const;
		Address(const T& a = NULL) :Basic<T>(a) {}
	};
	//行业（所属行业）
	template<typename T>
	class Trade :public Basic<T> {
	public:
		virtual bool Value()const;
		Trade(const T& a = NULL) :Basic<T>(a) {}
	};
	//公司性质（单位性质）
	template<typename T>
	class companyProperties :public Basic<T> {
	public:
		virtual bool Value()const;
		companyProperties(const T& a = NULL) :Basic<T>(a) {}
	};
	//公司规模（单位规模）
	template<typename T>
	class Scale :public Basic<T> {
	public:
		virtual bool Value()const;
		Scale(const T& a = NULL) :Basic<T>(a) {}
	};
	//学校性质（性质）
	template<typename T>
	class schoolProperties :public Basic<T> {
	public:
		virtual bool Value()const;
		schoolProperties(const T& a = NULL) :Basic<T>(a) {}
	};
	//单位
	template<typename BASIC, typename ADDRESS>
	class Unit {
	public:
		Basic<BASIC> basic;
		Address<ADDRESS> address;
		Unit(const BASIC& a = NULL, const ADDRESS& b = NULL) :basic(a), address(b) {}
		virtual ~Unit() = 0;
	};
	//公司（工作单位）
	template<typename BASIC, typename ADDRESS, typename TRADE, typename PROPERTIES, typename SCALE>
	class Company :public Unit<BASIC, ADDRESS> {
	public:
		Trade<TRADE> trade;
		companyProperties<PROPERTIES> properties;
		Scale<SCALE> scale;
		static std::map<int, Company*> List;//记录
		Company(
			const BASIC& b = NULL, const ADDRESS& a = NULL, const TRADE& t = NULL,
			const PROPERTIES& p = NULL, const SCALE& s = NULL
		) :Unit<BASIC, ADDRESS>(b, a), trade(t), properties(p), scale(s) {
			List[List.size()] = this;
		}
	};
	//学校（毕业学校）
	template<typename BASIC, typename ADDRESS, typename ID, typename PROPERTIES>
	class School :public Unit<BASIC, ADDRESS> {
	public:
		Id<ID> id;
		schoolProperties<PROPERTIES> properties;
		static std::map<ID, School*> List;//记录
		School(
			const BASIC& b = NULL, const ADDRESS& a = NULL,
			const ID& i = NULL, const PROPERTIES& p = NULL
		) :Unit<BASIC, ADDRESS>(b, a), id(i), properties(p) {
			List[id] = this;
		}
	};
	//人（校友）
	template<
		typename ID, typename NAME, typename PHONE, typename MAJOR, typename JOB, typename WORK, typename TIME,
		typename LIVE, typename _COMPANY, typename _SCHOOL>
		class People {
		private:
			_COMPANY* company;
			_SCHOOL* school;
			std::map<ID, bool> list;//联系人列表
		public:
			Id<ID> id; Name<NAME> name; Phone<PHONE> phone; Major<MAJOR>major;
			Job<JOB> job; Work<WORK> work; Time<TIME> time; Address<LIVE> address;
			static std::map<ID, People*> List;//记录
			People(
				const ID& i = NULL, const NAME& n = NULL, const PHONE& p = NULL, const MAJOR& m = NULL,
				const JOB& j = NULL, const WORK& w = NULL, const TIME& t = NULL, const LIVE& l = NULL,
				_COMPANY* c = NULL, _SCHOOL* s = NULL
			) :id(i), name(n), phone(p), major(m), job(j),
				work(w), time(t), address(l), company(c), school(s) {
				List[id] = this;
			}
	};
}
