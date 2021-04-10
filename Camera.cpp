#include "Camera.h"

Camera::Camera(const Vector& position_, const Matrix& attitude_):
			position(position_),
			attitude(attitude_)	{}

void Camera::updateUniforms(Shader& shader) const{

	shader.setUniform("uCameraPosition", position);
	shader.setUniform("uCameraAttitude", attitude);
	shader.setUniform("uCameraDeltax", deltax);
	shader.setUniform("uCameraDeltaz", deltaz);
	shader.setUniform("uCameraNear", near);
	shader.setUniform("uCameraAspectRatio", aspectRatio);

}


