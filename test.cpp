#include <vector>
#include <iostream>

namespace ES
{
    class Entity
    {
        public:
            Entity(unsigned int id):id(id) {}
            Entity(Entity &copy)
            {
                id = copy.id;
            }
            ~Entity(void) {}
            
            
            unsigned int id;
    };
    
    typedef struct
    {
        float   x;
        float   y;
    }Displacement;
    
    typedef enum
    {
        NONE = 0,
        DISPLACEMENT = 0x1,
    }Component;
    
    class   EntityManager
    {
        public:
            unsigned int    Create_entity(unsigned int mask)
            {
                entity_mask.push_back(mask);
                return entity_mask.size() - 1;
            }
            
            void    Destroy_entity(unsigned int entity)
            {
                static int  deleted = 0;
                
                entity_mask[entity] = Component::NONE;
                ++deleted;
                if (deleted >= 1)
                {
                    for (auto it = entity_mask.begin(); it != entity_mask.end(); ++it)
                        if (*it == Component::NONE)
                            entity_mask.erase(it);
                    deleted = 0;
                }
            }
            
        protected:
            std::vector<unsigned int>   entity_mask;
            std::vector<Displacement>   displacement_data;
    };
}

int main()
{
    std::cout<<"Adding entity"<<std::endl;
    ES::EntityManager E;
    std::cout<<"Created manager"<<std::endl;
    return 0;
    auto entity = E.Create_entity(ES::Component::DISPLACEMENT);
    std::cout<<"Done"<<std::endl<<"Removing element"<<std::endl;
    return 0;
    E.Destroy_entity(entity);
    std::cout<<"Done"<<std::endl;
    return 0;
}
