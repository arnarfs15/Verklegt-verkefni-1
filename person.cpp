#include "person.h"

//========CONSTRUCTORS==========
Person::Person()
{
    name = "";
    gender = "";
    date_of_birth = "";
    date_of_death = "";
}
//========PRIVATE FUNCTIONS==========
bool Person::checkDateFormat(string date)
{
    if(date.size() != 10)
    {
        return false;
    }

    for(unsigned int i=0; i<date.size(); i++)
    {
        if(i == 2 || i == 5)
        {
            if(date[i] != '/')
            {
                return false;
            }
        }
        else
        {
            if(!isdigit(date[i]))
            {
                return false;
            }
        }
    }

    return true;

}

QDate Person::strToQDate(string date)
{
    int day = stoi(date.substr(0,2));
    int month = stoi(date.substr(3,2));
    int year = stoi(date.substr(6,4));

    QDate date_check(year, month, day);

    return date_check;
}

//========PUBLIC FUNCTIONS==========
QString Person::getName()
{
    return QString::fromStdString(name);
}

QString Person::getGender()
{
    return QString::fromStdString(gender);
}

QString Person::getDoB()
{
    return QString::fromStdString(date_of_birth);
}

QString Person::getDoD()
{
    return QString::fromStdString(date_of_death);
}

void Person::setName(string _name)
{
    name = _name;
}

void Person::setGender(string _gender)
{
    gender = _gender;
}

void Person::setDoB(string dob)
{
    date_of_birth = dob;
}

void Person::setDoD(string dod)
{
    date_of_death = dod;
}

bool Person::lessThanName(Person &lhs, Person &rhs)
{
    return lhs.getName() < rhs.getName();
}

//========FRIEND FUNCTIONS==========
istream& operator >>(istream& ins, Person& person1)
{
    char temp;  //temporary variable to enter a character for the persons gender
    string tempGender;  //makes the interface easier to read

    QDate bdate, ddate; //for checking valid dates

    cout << "Enter the name of a computer scientist: ";
    cin.ignore(1000, '\n'); //this might be needed because cin leaves stuff in the buffer
    getline(ins, person1.name);

    while(1) //input checker
    {
        cout << "Enter that scientists gender (m for male, f for female): ";
        cin >> temp;
        if(temp == 'm')
        {
            person1.gender = "Male";
            tempGender = "his ";
            break;
        }
        else if(temp == 'f')
        {
            person1.gender = "Female";
            tempGender = "her ";
            break;
        }
    }

    while(1) //input checker
    {
        cout << "Enter " << tempGender << "date of birth (DD/MM/YYYY): ";
        ins >> person1.date_of_birth;

        if(person1.checkDateFormat(person1.date_of_birth))
        {
            bdate = person1.strToQDate(person1.date_of_birth);
            if(bdate.isValid() && bdate < QDate::currentDate())
            {
                break;
            }
        }
    }

    while(1) //input checker
    {
        cout << "Enter " << tempGender << "date of death (DD/MM/YYYY - enter 0 for still alive): ";
        ins >> person1.date_of_death;
        if(person1.date_of_death == "0")
        {
            person1.date_of_death = "alive";
            break;
        }


        if(person1.checkDateFormat(person1.date_of_death))
        {
            ddate = person1.strToQDate(person1.date_of_death);
            if(ddate.isValid() && bdate < ddate && ddate <= QDate::currentDate())
            {
                break;
            }
        }
    }
    return ins;
}

ostream& operator <<(ostream& os, Person person1)
{
    os << "Name: " <<  person1.name << ", ";
    os << "Gender: " << person1.gender << ", ";
    os << "Born: " << person1.date_of_birth << ", ";
    if(person1.date_of_death != "alive")
    {
        os << " Died: " << person1.date_of_death << endl;
    }
    else
    {
        os << endl;
    }

    return os;
}
