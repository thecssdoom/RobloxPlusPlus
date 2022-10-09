#include "DataModelV2/LightingInstance.h"
#include "Globals.h"
#include "Renderer.h"
#include <sstream>
#include <iomanip>
#include "Faces.h"

LightingInstance::LightingInstance(void)
{
	Instance::Instance();
	name = "Lighting";
	className = "Lighting";

	canDelete = false;

	listicon = 10;
}

LightingInstance::LightingInstance(const LightingInstance &oinst)
{
	PVInstance::PVInstance();
	name = "Unnamed PVItem";
	className = "Lighting";
}

LightingInstance::~LightingInstance(void)
{

}

std::vector<PROPGRIDITEM> LightingInstance::getProperties()
{
	std::vector<PROPGRIDITEM> properties = Instance::getProperties();
	return properties;
}


