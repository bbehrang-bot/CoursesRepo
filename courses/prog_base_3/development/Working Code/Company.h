#pragma once
#include "stdafx.h"
#include <string>
#include <iostream>
class Company
{
private:
	std::string name;
	std::string telephone;
	std::string about;
	std::string address;
public:
	Company();
	Company(std::string gcName, std::string cTelephone, std::string cAbout, std::string cAddress);
	std::string Company_getName();
	std::string Company_getTelephone();
	std::string Company_getAbout();
	std::string Company_getAddress();
};

