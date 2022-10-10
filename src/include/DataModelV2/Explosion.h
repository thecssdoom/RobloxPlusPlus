#pragma once
#include "Instance.h"
#include "PartInstance.h"
#include "enum.h"
#include <ode/ode.h>

class Explosion :
	public Instance
{
public:
	Explosion(void);
	~Explosion(void);
	Explosion(const Explosion &oinst);

	virtual void postRender(RenderDevice* rd);
	virtual void render(RenderDevice*);

	void setParent(Instance* parent);

	void setBlastRadius(float _blastRadius);
	void setBlastPressure(float _blastPressure);

	float getBlastRadius();
	float getBlastPressure();

	Color3 color;

	Vector3 position;

	bool isVisible();
	void setVisible(bool Visible);

	void doBlast(const std::vector<PartInstance *> parts);

	virtual void simulate(float sdt);

	virtual std::vector<PROPGRIDITEM> getProperties();
	virtual void PropUpdate(LPPROPGRIDITEM &pItem);
protected:

	float blastRadius;
	float blastPressure;

	float blastTimer;

	bool hasExploded;

	bool visible;
	GLuint glList;
};
