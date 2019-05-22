#include "stdafx.h"
#include "User.h"
#include <cstring>


User::User(const char* name)
{
			strcpy_s(username, strlen(name) + 1, name);
		

}

bool User::operator==(const User & eqUser)
{
	if (strcmp((this->getName()), eqUser.getName()) == 0) {
		return true;
	}
	return false;
}

bool User::operator!=(const User & eqUser)
{
	return !(operator==(eqUser));
}

