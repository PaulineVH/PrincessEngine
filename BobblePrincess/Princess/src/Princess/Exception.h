//2DAE07 - Vanden Heede, Pauline - 2019/2020
#pragma once
#include <exception>
#include <string>

/*
	Inspiration: Programming 2 course : week 7 handson theory class
*/

namespace Princess
{
	class Exception : public std::exception
	{
	public:
		//------ Public Functions ------
		//---- Constructor ----
		Exception(const std::string& message);
		//---- Functionality ----
		virtual const char* what() const override;

	private:
		//------ Data Members ------
		std::string m_Message;
	};
}
