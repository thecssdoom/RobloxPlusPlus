#include "DataModelV2/Explosion.h"
#include "Globals.h"
#include "Renderer.h"
#include <sstream>
#include <iomanip>
#include "Faces.h"

Explosion::Explosion(void)
{
    glList = glGenLists(1);
	name = "Explosion";
	className = "Explosion";
	
	blastPressure	= 500000.0F;
	blastRadius		= 4;

	blastTimer = 0.25F;
	hasExploded = false;

	listicon = 17;

	visible = true;

	color = Color3(1,0,0);

	position = Vector3(0,0,0);
}


void Explosion::setBlastRadius(float _blastRadius)
{ blastRadius = _blastRadius; }

void Explosion::setBlastPressure(float _blastPressure)
{ blastPressure = _blastPressure; }

float Explosion::getBlastRadius()
{ return blastRadius; }

float Explosion::getBlastPressure()
{ return blastPressure; }



void Explosion::postRender(RenderDevice *rd) { }

void Explosion::doBlast(const std::vector<PartInstance *> parts) { 
	if (blastPressure > 0.0f) {
		for (size_t i = 0; i < parts.size(); ++i) {
			if (parts[i] != NULL) {
				Vector3 delta = (parts[i]->getCFrame().translation - position);
				Vector3 normal = (delta == Vector3::zero()) ? Vector3::unitY() : delta.direction();

				if (delta.magnitude() <= (blastRadius+(parts[i]->getPartPrimitive()->getRadius()/2))/2.0f) {
					float radius = parts[i]->getPartPrimitive()->getRadius();
					float dt = 0.12f;

					Vector3 impulse = (normal * blastPressure) * (1.0f / 4560.0f) * dt;
					Vector3 angle = (impulse * 0.5 * radius) * dt;

					if(parts[i]->physBody) {
						dBodyEnable(parts[i]->physBody);

						dBodySetLinearVel(parts[i]->physBody,impulse.x,impulse.y,impulse.z);
						dBodySetAngularVel(parts[i]->physBody,angle.x,angle.y,angle.z);
					}

					printf("part got hit");
				}
			}
		}
	}

	hasExploded = true;
}

void Explosion::simulate(float sdt) { 
	blastTimer -= sdt;

	//printf("aa");

	if (blastTimer <= 0) {
		if (!hasExploded) {
			doBlast(g_dataModel->getWorkspace()->partObjects);
		}
		blastTimer = 0;
	}
}

void Explosion::setParent(Instance* prnt) 
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

Explosion::Explosion(const Explosion &oinst)
{
	glList = glGenLists(1);
	name = "Explosion";
	className = "Explosion";
	
	blastPressure	= oinst.blastPressure;
	blastRadius		= oinst.blastRadius;

	color = oinst.color;

	position = oinst.position;
}

void Explosion::render(RenderDevice* rd) {
	if (!visible || hasExploded)
		return;

	rd->disableLighting();

	Vector3 renderSize = Vector3(blastRadius/2.0f,blastRadius/2.0f,blastRadius/2.0f);
	//glScalef(0.5f,0.5f,0.5f);
	rd->setObjectToWorldMatrix(CoordinateFrame(position));

	renderShape(Enum::Shape::Ball, renderSize, color);

	postRender(rd);

	rd->enableLighting();
}

Explosion::~Explosion(void)
{

}

char blastRadiusText[256];
char blastPressureText[256];
char blastTimerText[256];
char eto[512];

std::vector<PROPGRIDITEM> Explosion::getProperties()
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

	sprintf_s(blastRadiusText, "%f", blastRadius);
	sprintf_s(blastPressureText, "%f", blastPressure);
	sprintf_s(blastTimerText, "%f", blastTimer*2);
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
	properties.push_back(createPGI("Data",
		"BlastTimer",
		"How much time until the explosion occurs.",
		(LPARAM)blastTimerText,
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

void Explosion::PropUpdate(LPPROPGRIDITEM &item)
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
		setBlastRadius(atoi((LPSTR)item->lpCurValue));
	}
	else if(strcmp(item->lpszPropName, "BlastPressure") == 0)
	{
		setBlastPressure(atoi((LPSTR)item->lpCurValue));
	}
	else if(strcmp(item->lpszPropName, "BlastTimer") == 0)
	{
		blastTimer = (atof((LPSTR)item->lpCurValue))/2.0f;
	}
	else if(strcmp(item->lpszPropName, "Visible") == 0)
	{
		visible = item->lpCurValue == TRUE;
	}
	else Instance::PropUpdate(item);
}

bool Explosion::isVisible()
{
	return visible;
}

void Explosion::setVisible(bool Visible)
{
	visible = Visible;
}