#include"Data_S.h"
//重写判断合法
namespace Data {
	template<> bool Id<std::string>::Value()const {
		return true;
	}
	template<> bool Name<std::string>::Value()const {
		return true;
	}
	template<> bool Phone<std::string>::Value()const {
		return true;
	}
	template<> bool Major<std::string>::Value()const {
		return true;
	}
	template<> bool Job<std::string>::Value()const {
		return true;
	}
	template<> bool Work<std::string>::Value()const {
		return true;
	}
	template<> bool Time<std::string>::Value()const {
		return true;
	}
	template<> bool Address<std::string>::Value()const {
		return true;
	}
	template<> bool Trade<std::string>::Value()const {
		return true;
	}
	template<> bool companyProperties<std::string>::Value()const {
		return true;
	}
	template<> bool Scale<std::string>::Value()const {
		return true;
	}
	template<> bool schoolProperties<std::string>::Value()const {
		return true;
	}
}
