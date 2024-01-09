

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include "Station.h"
#include "Utilities.h"
using namespace std;

namespace sdds
{
    size_t Station::m_widthField{};
    size_t Station::id_generator{};

    Station::Station(const std::string& str)
    {
        Utilities ut;
        bool more{ true };
        size_t pos{};

        s_id = ++id_generator;
        s_name = ut.extractToken(str, pos, more);
        s_nextSerialNo = stoi(ut.extractToken(str, pos, more));
        s_numInStock = stoi(ut.extractToken(str, pos, more));

        if (m_widthField < ut.getFieldWidth()) 
            m_widthField = ut.getFieldWidth();

        s_description = ut.extractToken(str, pos, more);
    }

    const string& Station::getItemName() const { return s_name; }

    size_t Station::getNextSerialNumber() { return s_nextSerialNo++; }

    size_t Station::getQuantity() const { return s_numInStock; }

    void Station::updateQuantity()
    {
        if (s_numInStock > 0)
            s_numInStock--;
    }

    void Station::display(ostream& os, bool full) const
    {
        os << right << setw(3) << setfill('0') << s_id << " | "
            << left << setw(m_widthField) << setfill(' ') << s_name << " | "
            << right << setw(6) << setfill('0') << s_nextSerialNo << " | ";

        if (full)
            os << right << setw(4) << setfill(' ') << s_numInStock << " | "
            << s_description;

        os << endl;
    }
}
