#pragma once
#include "tool.h"
#include "ToolEnum.h"

class HopperTool :
	public Tool
{
public:
	HopperTool(Enum::Hopper::Value _toolType); //OnSelect?
	~HopperTool(void); //OnDeselect?
	void onButton1MouseDown(Mouse);
	void onButton1MouseUp(Mouse);
	void onMouseMoved(Mouse mouse);
	void onSelect(Mouse mouse); 
	void onKeyDown(int key);
	void onKeyUp(int key);
private:
	bool lctrlDown;
	bool rctrlDown;
	int mouseDownStartx;
	int mouseDownStarty;
	bool dragging;
	bool mouseDown;

	Enum::Hopper::Value toolType;

	Vector3 draggingPartOffset;
};
