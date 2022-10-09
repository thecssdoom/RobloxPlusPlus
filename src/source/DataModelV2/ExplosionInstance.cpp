#include "DataModelV2/ExplosionInstance.h"
#include "Globals.h"
#include "Renderer.h"
#include <sstream>
#include <iomanip>
#include "Faces.h"

ExplosionInstance::ExplosionInstance(void)
{
    glList = glGenLists(1);
	name = "Explosion";
	className = "Explosion";
	
	blastPressure	= 50000;
	blastRadius		= 20;

	listicon = 17;

	color = Color3(1,0,0);

	position = Vector3(0,0,0);
}

void ExplosionInstance::postRender(RenderDevice *rd) { }
void ExplosionInstance::blastOff() { }

void ExplosionInstance::setParent(Instance* prnt) 
{ 
	Instance * cparent = getParent();
	while(cparent != NULL)
	{
		if(WorkspaceInstance* workspace = dynamic_cast<WorkspaceInstance*>(cparent))
		{
			break;
		}
		cparent = cparent->getParent();
	}
	Instance::setParent(prnt);
	while(parent != NULL)
	{
		if(WorkspaceInstance* workspace = dynamic_cast<WorkspaceInstance*>(parent))
		{
			break;
		}
		parent = parent->getParent();
	}
}

ExplosionInstance::ExplosionInstance(const ExplosionInstance &oinst)
{
	glList = glGenLists(1);
	name = "Explosion";
	className = "Explosion";
	
	blastPressure	= oinst.blastPressure;
	blastRadius		= oinst.blastRadius;

	color = oinst.color;

	position = oinst.position;
}

void ExplosionInstance::render(RenderDevice* rd) {
	if (!visible)
		return;

	rd->disableLighting();

	Vector3 renderSize = Vector3(blastRadius/2,blastRadius/2,blastRadius/2);
	//glScalef(0.5f,0.5f,0.5f);
	rd->setObjectToWorldMatrix(CoordinateFrame(position));

	renderShape(Enum::Shape::Ball, renderSize, color);

	postRender(rd);

	rd->enableLighting();
}

ExplosionInstance::~ExplosionInstance(void)
{

}

char blastRadiusText[32];
char blastPressureText[32];
char eto[512];

std::vector<PROPGRIDITEM> ExplosionInstance::getProperties()
{
	std::vector<PROPGRIDITEM> properties = Instance::getProperties();
    

	sprintf_s(eto, "%g, %g, %g", position.x, position.y, position.z);
	properties.push_back(createPGI(
		"Data",
		"Position",
		"The position of the explosion",
		(LPARAM)eto,
		PIT_EDIT
		));

	sprintf_s(blastRadiusText, "%i", blastRadius);
	sprintf_s(blastPressureText, "%i", blastPressure);
	properties.push_back(createPGI("Data",
		"BlastRadius",
		"How big the Explosion is. This is a circle start from the center of the Explosion's Position, the larger this property the larger distance it will go.",
		(LPARAM)blastRadiusText,
		PIT_EDIT));
	properties.push_back(createPGI("Data",
		"BlastPressure",
		"How much force this Explosion exerts on objects within it's BlastRadius. Setting this to 0 causes a purely graphical explosions, while higher values will cause Parts to fly away at high speeds.",
		(LPARAM)blastPressureText,
		PIT_EDIT));

	properties.push_back(createPGI(
		"Appearance",
		"Visible",
		"Visible",
		(LPARAM)visible,
		PIT_CHECK
		));

	properties.push_back(createPGI(
		"Appearance",
		"Color3",
		"The color of the explosion.",
		RGB((color.r*255),(color.g*255),(color.b*255)),
		PIT_COLOR
		));

	return properties;
}

void ExplosionInstance::PropUpdate(LPPROPGRIDITEM &item)
{
	if(strcmp(item->lpszPropName, "Color3") == 0)
	{
		color = Color3(GetRValue(item->lpCurValue)/255.0F,GetGValue(item->lpCurValue)/255.0F,GetBValue(item->lpCurValue)/255.0F);
	}
	else if(strcmp(item->lpszPropName, "Position") == 0)
	{
		std::string str = (LPTSTR)item->lpCurValue;
		std::vector<float> vect;
		std::stringstream ss(str);
		float i;

		while (ss >> i)
		{
			vect.push_back(i);

			if (ss.peek() == ',')
				ss.ignore();
		}

		//if(vect.size() != 3)
		//{
			//sprintf(pto, "%g, %g, %g", cFrame.translation.x, cFrame.translation.y, cFrame.translation.z, "what");
			//LPCSTR str = LPCSTR(pto);
			//item->lpCurValue = (LPARAM)str;
		//}
		//else
		if(vect.size() == 3)
		{
			Vector3 pos(vect.at(0),vect.at(1),vect.at(2));
			position = pos;
		}
	}

	else if(strcmp(item->lpszPropName, "BlastRadius") == 0)
	{
		blastRadius = atoi((LPSTR)item->lpCurValue);
	}
	else if(strcmp(item->lpszPropName, "BlastPressure") == 0)
	{
		blastPressure = atoi((LPSTR)item->lpCurValue);
	}
	else if(strcmp(item->lpszPropName, "Visible") == 0)
	{
		visible = item->lpCurValue == TRUE;
	}
	else Instance::PropUpdate(item);
}

bool ExplosionInstance::isVisible()
{
	return visible;
}

void ExplosionInstance::setVisible(bool Visible)
{
	visible = Visible;
}