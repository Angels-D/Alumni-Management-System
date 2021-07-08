#pragma once
#include<regex>//正则表达式（判断合法）
#include"Data.h"
//显式化类型
typedef Data::School//学校
<
	std::string, //名字
	std::string, //地址
	std::string, //ID
	std::string  //性质
> SCHOOL;
typedef Data::Company//公司
<
	std::string, //名字
	std::string, //地址
	std::string, //行业
	std::string, //性质
	std::string  //规模
> COMPANY;
typedef Data::People//人
<
	std::string, //ID
	std::string, //名字
	std::string, //电话
	std::string, //专业
	std::string, //职业
	std::string, //职务
	std::string, //年限
	std::string, //地址
	COMPANY,	 //公司
	SCHOOL		 //学校
> PEOPLE;
template<> std::map<int, COMPANY*> COMPANY::List;
template<> std::map<std::string, SCHOOL*> SCHOOL::List;
template<> std::map<std::string, PEOPLE*> PEOPLE::List;
