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
            unsigned int    Create_entity(void)
            {
                entity_mask.push_back(Component::NONE);
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
            
            void    Add_Component(unsigned int entity, Component mask, void *data)
            {
                if (entity >= entity_mask.size())
                    return ;
                entity_mask[entity] |= mask;
                switch (mask)
                {
                    case    Component::DISPLACEMENT:
                        displacement_data
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
    auto entity = E.Create_entity();
    std::cout<<"Done"<<std::endl<<"Adding displacement component"<<std::endl;
    
    std::cout<<"Done"<<std::endl<<"Removing element"<<std::endl;
    return 0;
    E.Destroy_entity(entity);
    std::cout<<"Done"<<std::endl;
    return 0;
}
