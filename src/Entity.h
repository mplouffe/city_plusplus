#include "Component.h"
#include <map>

class Entity
{
    public:
        Component* getComponentByType(ComponentType a_componentType);
        bool addComponent(Component* a_newComponent);
    private:
        std::map<ComponentType, Component*> m_components;
};