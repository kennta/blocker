#ifndef _SCENE_TITLE_H_
#define _SCENE_TITLE_H_

#include "SceneBase.h"

class SceneTitle : public SceneBase
{
public:
    SceneTitle();
    virtual ~SceneTitle();
    virtual bool onInit();
    virtual void onRelease();
    virtual void onTick();
    virtual void onDraw(Graphics& g);

private:
    int _blinkCount;
};

#endif // _SCENE_TITLE_H_
