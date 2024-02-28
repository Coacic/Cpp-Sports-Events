#include "Athlete.h"

Athlete::Athlete(int _id, std::string _age, std::string _weight, std::string _height, std::string _name, std::string _gender)
{
	id = _id;
	age = _age;
	weight = _weight;
	height = _height;
	name = _name;
	gender = *_gender.c_str();
}

Athlete::Athlete()
{
	id = NULL;
	age = nullptr;
	weight = nullptr;
	height = nullptr;
	name = nullptr;
	gender = 0;
}

Athlete::~Athlete()
{
}

const int Athlete::getId() const
{
	return id;
}

const std::string& Athlete::getName() const
{
	return name;
}

const char& Athlete::getGender() const
{
	return gender;
}

void Athlete::parseCompetitor()
{
}

bool Athlete::operator<(const Athlete& ath) const
{
		return ath.getAge() < getAge();
}

bool Athlete::operator==(const Athlete& ath) const
{
	if (id == ath.getId())
		return true;
	return false;
}

const std::string& Athlete::getAge() const
{
	return age;
}

const std::string& Athlete::getWeight() const
{
	return weight;
}

const std::string& Athlete::getHeight() const
{
	return height;
}

std::ostream& operator<<(std::ostream& os, const Athlete& a)
{
	os << a.getId() << " " << a.getName() << " " << a.getGender() << " "
		<< a.getAge() << " " << a.getHeight() << " " << a.getWeight();
	return os;
}
