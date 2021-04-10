#include "Camera.h"

#include <cmath>

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


void Camera::lookAt(const Vector& x){
	
	Vector direction = position - x;

	float thetay = atan2(direction.x, direction.z);
	float thetax = atan2(direction.y, sqrt(direction.x * direction.x + direction.z * direction.z));

	Matrix Ry(Vector(.0f, 1.0f, .0f), thetay);
	Vector kx = Ry * Vector(1.0f, .0f, .0f);
	Matrix Rx(Vector(1.0f, .0f, .0f), -thetax);

	attitude = Ry * Rx;
}
