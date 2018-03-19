#ifndef BALL_H
#define BALL_H

#include "physicsobject.h"

class Ball : public PhysicsObject
{
    public:
        Ball(SceneObject *a, Shader *s, GLuint t = 0, Texture *tex = nullptr);
        ~Ball();

        void physicsUpdate() override;

    private:
};

#endif // BALL_H
