#ifndef RENDERUTIL
#define RENDERUTIL
#include "Enum.h"
#include "DataModelV2/Instance.h"
void renderShape(const Enum::Shape::Value& shape, const Vector3& size, const Color3& ncolor);
void renderSurface(const char face, const Enum::SurfaceType::Value& surface, const Vector3& size, const Enum::Controller::Value& controller, const Color3& color);

void util_renderSquare(Vector3 v1,Vector3 v2,Vector3 v3,Vector3 v4,Vector3 v5,Vector3 v6);

void render_markShadows(Vector4 light);
#endif
