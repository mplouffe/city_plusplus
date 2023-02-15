#include "Transform.h"

Transform::Transform()
{
    mX = 0;
    mY = 0;
}

ComponentType Transform::getComponentType()
{
    return ComponentType::TRANSFORM;
}

const std::tuple<int, int> Transform::getPosition()
{
    return {mX, mY};
}

void Transform::movePosition(std::tuple<int, int> aNewPosition)
{
    std::tie(mX, mY) = aNewPosition;
}