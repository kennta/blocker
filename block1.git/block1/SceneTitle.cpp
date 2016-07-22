#include "GameDefine.h"
#include "SceneTitle.h"

#include <windows.h>

#include "GameMain.h"
#include "TaskManager.h"
#include "SceneGame.h"

SceneTitle::SceneTitle()
{
}

SceneTitle::~SceneTitle()
{
}

bool SceneTitle::onInit()
{
    _blinkCount = 0;

    TaskManager::getInstance().addDrawTask(this, TASK_PRIORITY_SCENE);

    return true;
}

void SceneTitle::onRelease()
{
    GameMain::getInstance().changeScene(new SceneGame());
}

void SceneTitle::onTick()
{
    Input& in = GameMain::getInstance().getInput();
    if (in.isDown(Input::KEY_LEFT)
     || in.isDown(Input::KEY_RIGHT)
     || in.isDown(Input::KEY_UP)
     || in.isDown(Input::KEY_DOWN)
     )
    {
        kill();
    }

    _blinkCount = (_blinkCount + 1) % FPS;
}

void SceneTitle::onDraw(Graphics& g)
{
    if (_blinkCount < FPS / 2)
    {
        HFONT font = CreateFont(40, 0, 0, 0, FW_BLACK, FALSE, FALSE, FALSE,
                SHIFTJIS_CHARSET, OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH | FF_SWISS, NULL);
        g.setFont(font);

        g.setTextColor(128, 128, 255);
        g.setTextAlign(TA_BASELINE | TA_CENTER | TA_NOUPDATECP);

        g.drawString(DWIDTH / 2, DHEIGHT / 2, "Push cursor key");

        g.setFont(NULL);
        DeleteObject(font);
    }
}
