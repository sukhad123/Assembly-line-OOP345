

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <iomanip>
#include "Utilities.h"
#include "Station.h"
#include "CustomerOrder.h"
using namespace std;
namespace sdds
{
	size_t CustomerOrder::m_widthField{};

	CustomerOrder::CustomerOrder() {}

	CustomerOrder::CustomerOrder(const string &str)
	{
		Utilities ut;
		bool more{true};
		size_t pos{};

		m_name = ut.extractToken(str, pos, more);
		m_product = ut.extractToken(str, pos, more);
		m_cntItem = 1; 
		for (auto i = pos; i < str.size(); i++)
			if (str[i] == ut.getDelimiter())
				m_cntItem++; 

		m_lstItem = new Item *[m_cntItem];
		for (auto i = 0ul; i < m_cntItem; i++)
			m_lstItem[i] = new Item(ut.extractToken(str, pos, more));

		if (m_widthField < ut.getFieldWidth()) 
			m_widthField = ut.getFieldWidth();
	}

	CustomerOrder::CustomerOrder(const CustomerOrder &customerOrder) { throw "----> ERROR: Cannot make copies."; }

	CustomerOrder::CustomerOrder(CustomerOrder &&customerOrder) noexcept { *this = std::move(customerOrder); }

	CustomerOrder &CustomerOrder::operator=(CustomerOrder &&customerOrder) noexcept
	{
		if (this != &customerOrder)
		{
			for (auto i = 0ul; i < m_cntItem; i++) 
				delete m_lstItem[i];
			delete[] m_lstItem;
			m_lstItem = customerOrder.m_lstItem; 
			customerOrder.m_lstItem = nullptr;	 
			m_name = customerOrder.m_name;		
			m_product = customerOrder.m_product;
			m_cntItem = customerOrder.m_cntItem;
			customerOrder.m_cntItem = 0;
		}
		return *this;
	}

	CustomerOrder::~CustomerOrder()
	{
		for (auto i = 0ul; i < m_cntItem; i++)
			delete m_lstItem[i];
		delete[] m_lstItem;
	}

	bool CustomerOrder::isOrderFilled() const
	{
		bool result{true};
		for (auto i = 0ul; i < m_cntItem; i++)
			if (!m_lstItem[i]->m_isFilled)
				result = false;
		return result;
	}

	bool CustomerOrder::isItemFilled(const string &itemName) const
	{
		bool result{true}; 
		for (auto i = 0ul; i < m_cntItem; i++)
			if (m_lstItem[i]->m_itemName == itemName && !m_lstItem[i]->m_isFilled)
				result = false;
		return result;
	}

	void CustomerOrder::fillItem(Station &station, ostream &os)
	{
		for (auto i = 0ul; i < m_cntItem; i++)
			if (m_lstItem[i]->m_isFilled == false && m_lstItem[i]->m_itemName == station.getItemName())
			{
				if (station.getQuantity() > 0)
				{
					station.updateQuantity();									  
					m_lstItem[i]->m_serialNumber = station.getNextSerialNumber(); 
					m_lstItem[i]->m_isFilled = true;							  
					os << "    Filled " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
					break;
				}
				else
					os << "    Unable to fill " << m_name << ", " << m_product << " [" << m_lstItem[i]->m_itemName << "]" << endl;
			}
	}

	void CustomerOrder::display(ostream &os) const
	{
		os << m_name << " - " << m_product << endl;
		for (auto i = 0ul; i < m_cntItem; i++)
			os << right << "[" << setw(6) << setfill('0') << m_lstItem[i]->m_serialNumber << "] "
			   << setw(m_widthField) << setfill(' ') << left << m_lstItem[i]->m_itemName << " - "
			   << (m_lstItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED")
			   << endl;
	}
}
