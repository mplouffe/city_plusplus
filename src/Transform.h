#include "Component.h"

#include <vector>

class Transform : public Component
{
    public:
        ComponentType getComponentType();
        const std::tuple<int, int> getPosition();
        void movePosition(std::tuple<int, int> aNewPosition);
    private:
        int mX;
        int mY;
};