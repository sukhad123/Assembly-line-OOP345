

#ifndef SDDS_STATION_H
#define SDDS_STATION_H
#include <iostream>
#include <iomanip>
#include <string>

namespace sdds {
    typedef std::string string;
    class Station {
        size_t s_id{};
        string s_name{};
        string s_description{};
        size_t s_nextSerialNo{ 0 };
        size_t s_numInStock{ 0 };
        static size_t m_widthField;
        static size_t id_generator;
    public:
        Station(const string& str);
        const string& getItemName() const;
        size_t getNextSerialNumber();
        size_t getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
        static void setWidthField(size_t width);
        static size_t getWidthField();
    };
}
#endif
