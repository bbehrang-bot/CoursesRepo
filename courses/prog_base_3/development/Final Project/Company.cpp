#include "stdafx.h"
#include "Company.h"
Company::Company(std::string cName, std::string cTelephone, std::string cAbout, std::string cAddress)
{
	name = cName;
	telephone = cTelephone;
	about = cAbout;
	address = cAddress;
}

std::string Company::Company_getName()
{
	return name;
}

std::string Company::Company_getTelephone()
{
	return telephone;
}

std::string Company::Company_getAbout()
{
	return about;
}

std::string Company::Company_getAddress()
{
	return address;
}
