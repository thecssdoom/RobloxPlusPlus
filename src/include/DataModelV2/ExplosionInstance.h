#pragma once
#include "instance.h"
#include "enum.h"
#include <ode/ode.h>

class ExplosionInstance :
	public Instance
{
public:
	ExplosionInstance(void);
	~ExplosionInstance(void);
	ExplosionInstance(const ExplosionInstance &oinst);

	virtual void postRender(RenderDevice* rd);
	virtual void render(RenderDevice*);

	void setParent(Instance* parent);

	Color3 color;
	int blastRadius;
	int blastPressure;

	Vector3 position;

	bool isVisible();
	void setVisible(bool Visible);

	virtual std::vector<PROPGRIDITEM> getProperties();
	virtual void PropUpdate(LPPROPGRIDITEM &pItem);
protected:
	void blastOff();

	bool visible;
	GLuint glList;
};
