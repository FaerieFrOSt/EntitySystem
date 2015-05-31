#include <vector>
#include <iostream>
#include <string>
#include <functional>
#include <algorithm>
#include <deque>

class   Data_base
{};

class   Pos: public Data_base
{
	public:
	Pos(int x, int y) : x(x), y(y) {}

	int x, y;
};

class   Print: public Data_base
{
	public:
	Print(std::string s) : str(s) {}

	std::string str;
};

namespace ES
{
	typedef enum
	{
		NONE = 0,
		DISPLACEMENT = 0x1,
		PRINT = 0x1 << 1,
		First = DISPLACEMENT,
		Last = PRINT,
	}Component;

	template <typename T>
	class   Enum
	{
		public:
			class   Iterator
			{
				public:
					Iterator(int value) : m_value(value) {}

					T   operator*(void) const { return (T)m_value; }

					void    operator++(void) { m_value = m_value << 1; }

					bool    operator!=(Iterator &rhs) { return m_value != rhs.m_value; }

				private:
					int m_value;
			};
	};

	template<typename T>
	typename Enum<T>::Iterator  begin(Enum<T>)
	{
		return typename Enum<T>::Iterator((int)T::First);
	}

	template<typename T>
	typename Enum<T>::Iterator  end(Enum<T>)
	{
		return typename Enum<T>::Iterator((int)T::Last << 1);
	}

	class   EntityManager
	{
		public:
			EntityManager()
			{
				data.push_back(std::vector<Data_base*>());
				data.push_back(std::vector<Data_base*>());
				systems.push_back([] (Data_base *i) { (void)i; });
				systems.push_back([] (Data_base *i) { Print *j = static_cast<Print *>(i); std::cout<<"function called "<<j->str<<std::endl; });
			}

			unsigned int    Create_entity(void)
			{
				for (auto it = entity_mask.begin(); it != entity_mask.end(); ++it)
					if (*it == Component::NONE)
						return it - entity_mask.begin();
				entity_mask.push_back(Component::NONE);
				for (auto &i : data)
					i.push_back(0);
				return entity_mask.size() - 1;
			}
            
			void    Destroy_entity(unsigned int entity)
			{
				unsigned int    k = 0;
				for (auto i : Enum<Component>())
				{
					if (entity_mask[entity] & i == i)
						delete data[k][entity];
					++k;
				}
				entity_mask[entity] = Component::NONE;
			}

			void    Add_Component(unsigned int entity, Component mask, Data_base *d)
			{
				if (entity >= entity_mask.size())
					return ;
				entity_mask[entity] |= mask;
				unsigned int    i = 0;
				while (1 << i++ < mask);
				data[i - 1][entity] = d;
			}

			void    run(void)
			{
				for_each(entity_mask.begin(), entity_mask.end(), [this] (unsigned int i) {
					unsigned int    k = 0;
					for (auto j : Enum<Component>())
					{
						if (i & j)
							systems[k](data[k][i]);
						++k;
					}
				});
			}

		protected:
			std::vector<unsigned int>   entity_mask;
			std::deque<std::vector<Data_base*>>  data;
			std::vector<std::function<void(Data_base*)>>  systems;
	};
}

int main()
{
	std::cout<<"Adding entity"<<std::endl;
	ES::EntityManager E;
	std::cout<<"Created manager"<<std::endl;
	auto entity = E.Create_entity();
	std::cout<<"Done"<<std::endl<<"Adding print component"<<std::endl;
	E.Add_Component(entity, ES::Component::PRINT, new Print("hello world"));
	std::cout<<"Done"<<std::endl<<"Running"<<std::endl;
	E.run();
	std::cout<<"Done"<<std::endl<<"Removing element"<<std::endl;
	E.Destroy_entity(entity);
	std::cout<<"Done"<<std::endl;
	return 0;
}
