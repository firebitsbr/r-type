//
// Created by Quentin Liardeaux on 11/7/19.
//

#ifndef R_TYPE_SERVER_AABBCOLLISIONDETECTION_HPP
#define R_TYPE_SERVER_AABBCOLLISIONDETECTION_HPP

#include "CollisionDetection.hpp"

struct Frame {
    double x;
    double y;
    double width;
    double height;
};

class AABBCollisionDetection: public CollisionDetection {
public:
    AABBCollisionDetection(const Frame &frameRect);
    ~AABBCollisionDetection() final = default;

    [[nodiscard]] bool isCollidingWith(shared_ptr<CollisionDetection> object) const final;

    Frame m_frameRect;
private:
    bool isInside(double value, double min, double max) const;
};

#endif //R_TYPE_SERVER_AABBCOLLISIONDETECTION_HPP
