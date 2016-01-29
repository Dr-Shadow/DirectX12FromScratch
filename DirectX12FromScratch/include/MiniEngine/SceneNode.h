#pragma once

# include <list>
# include "MiniEngine/Geometry.h"
# include "MiniEngine/MovableObject.h"
# include "MiniEngine/Camera.h"
# include "MiniEngine/CommandList.h"
# include "MiniEngine/RenderableObject.h"

namespace MiniEngine
{
    class SceneManager;

    class SceneNode
    {
    public:
        SceneNode(SceneManager &manager);
        ~SceneNode();

        virtual SceneNode       *createChild();
        virtual SceneNode       *addChild(SceneNode *node);
        virtual void            attachObject(MovableObject *obj);

        virtual SceneNode       *getParent();

        virtual bool            render(Camera &camera, CommandList &commandList);

        virtual Matrix4f const &getTransformationMatrix() const;
        virtual Matrix4f const &getWorldTransformationMatrix() const;

        virtual void            updateMatrix();

    protected:
        virtual void            setParent(SceneNode *node);

    protected:
        SceneManager            &_manager;

        SceneNode               *_parent;
        std::list<SceneNode*>   _childs;
        MovableObject           *_obj;

        Vector3f                _position;
        Quatf                   _rotation;
        Vector3f                _scaling;

        Matrix4f                _localMatrix;
        Matrix4f                _worldMatrix;
    };
}