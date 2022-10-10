#include "Tool/HopperTool.h"
#include "DataModelV2/Explosion.h"
#include "Application.h"
HopperTool::HopperTool(Enum::Hopper::Value _toolType)
{
	toolType = _toolType;
}

HopperTool::~HopperTool(void)
{
}

void HopperTool::onButton1MouseDown(Mouse mouse)
{
	PartInstance * target = mouse.getTarget();
	if(target != NULL)
	{
		AudioPlayer::playSound(GetFileInPath("/content/sounds/snap.wav"));

		std::vector<Instance*> instances;
		Vector3 pos = mouse.getPosition(instances);
		
		Explosion* explode = new Explosion();

		explode->position = pos;
		explode->setParent(g_dataModel->getWorkspace());
		explode->setBlastRadius(12.0F);
#ifdef _DEBUG
		explode->setBlastRadius(100.0F);
#endif
		explode->setBlastPressure(500000.0F);
	}
}
void HopperTool::onButton1MouseUp(Mouse mouse)
{
	
}

void HopperTool::onMouseMoved(Mouse mouse)
{
}
void HopperTool::onSelect(Mouse mouse)
{
	AudioPlayer::playSound(dingSound);
}

void HopperTool::onKeyDown(int key)
{
	
}

void HopperTool::onKeyUp(int key)
{
	
}