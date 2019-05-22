#pragma once
class User
{
private:
	char username[20];
public:
	User(const char* name="No name");
	const char* getName() const {
		return username;
	}

	bool operator==(const User& eqUser);
	bool operator!=(const User& eqUser);
};

