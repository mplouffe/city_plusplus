#include "Entity.h"

Component* Entity::getComponentByType(ComponentType a_componentType)
{
    return m_components[a_componentType];
}

bool Entity::addComponent(Component* a_newComponent)
{
    ComponentType newComponentType = a_newComponent->getComponentType();
    bool add = m_components[newComponentType] == NULL;
    if (add)
    {
        m_components[newComponentType] = a_newComponent;
    }
    return add;
}