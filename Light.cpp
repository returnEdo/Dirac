#include "Light.h"

Light::Light(const Vector& position_):
		position(position_)	{}


void Light::updateUniforms(Shader& shader) const{

	shader.setUniform("uLightPosition", position);
}
