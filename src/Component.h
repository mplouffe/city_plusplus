
enum ComponentType
{
    TRANSFORM,
	BOX_COLLIDER,
    PHYSICBODY,
    SPRITE,
};

class Component
{
    public:
        virtual ComponentType getComponentType() = 0;
    private:
        ComponentType m_componentType; 
};