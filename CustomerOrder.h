

#ifndef SDDS_CUSTOMER_ORDER_H
#define SDDS_CUSTOMER_ORDER_H
#include <iostream>
#include <string>
#include "Station.h"
namespace sdds
{
	struct Item
	{
		std::string m_itemName;
		size_t m_serialNumber{ 0 };
		bool m_isFilled{ false };

		Item(const std::string& src) : m_itemName(src) {};
	};

	class CustomerOrder
	{
		std::string m_name{};
		std::string m_product{};
		size_t m_cntItem{};
		Item** m_lstItem{};
		static size_t m_widthField;

	public:
		CustomerOrder();
		CustomerOrder(const std::string &str);
		CustomerOrder(const CustomerOrder& customerOrder);
		CustomerOrder& operator=(const CustomerOrder& customerOrder) = delete;
		CustomerOrder(CustomerOrder&& customerOrder) noexcept;
		CustomerOrder& operator=(CustomerOrder&& customerOrder) noexcept;
		~CustomerOrder();
		bool isOrderFilled() const;
		bool isItemFilled(const std::string& itemName) const;
		void fillItem(Station& station, std::ostream& os);
		void display(std::ostream& os) const;
	};
}
#endif 