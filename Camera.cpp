/*
	GPU accelerated rigid body simulation with OpenGL and OpenCL.
	Created by: Sándor Balázs - it.sandor.balazs@gmail.com
	AX400
	---
	Own camera implementation with sphere coordniates.
*/

#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera(void) : cameraPosition(0.0f), lookedPoint(0.0f), upwardDirection(0.0f, 10.0f, 0.0f), cameraSpherePosition(0.0f) {
	setView(glm::vec3(45,45,45), glm::vec3(0.0f));
	setProjection(45.0f, 640/480.0f, 0.001f, 1000.0f);
}

Camera::~Camera(void) {}

void Camera::setView(glm::vec3 camPos, glm::vec3 lookPoint) {
	cameraPosition = camPos;
	lookedPoint = lookPoint;
	sphereCoordinateUpdate();
	cameraCoordinateUpdate();
}

void Camera::setProjection(float angle, float aspect, float zNear, float zFar) {
	projectionMatrix = glm::perspective(angle, aspect, zNear, zFar);
}

//sphere to descartes
void Camera::cameraCoordinateUpdate() {
	cameraPosition.x = (cameraSpherePosition.x * sinf(cameraSpherePosition.y) * cosf(cameraSpherePosition.z)) + lookedPoint.x;
	cameraPosition.z = (cameraSpherePosition.x * sinf(cameraSpherePosition.y) * sinf(cameraSpherePosition.z)) + lookedPoint.z;
	cameraPosition.y = (cameraSpherePosition.x * cosf(cameraSpherePosition.y)) + lookedPoint.y;
	update();
}

//descartes to sphere
void Camera::sphereCoordinateUpdate() {
	glm::vec3 origoCameraPosition = cameraPosition - lookedPoint;
	cameraSpherePosition.x = sqrt(origoCameraPosition.x* origoCameraPosition.x+ origoCameraPosition.y* origoCameraPosition.y+ origoCameraPosition.z* origoCameraPosition.z);
	cameraSpherePosition.y = acosf(origoCameraPosition.y/cameraSpherePosition.x);
	cameraSpherePosition.z = atanf(origoCameraPosition.z/ origoCameraPosition.x);
}

void Camera::update() {
	viewMatrix = glm::lookAt(cameraPosition, lookedPoint, upwardDirection);
}

void Camera::sphereCoordinateShift(float r, float a, float b) {
	//sphereCoordinateUpdate();
	cameraSpherePosition.x += r;
	cameraSpherePosition.y += b*-1.0f;
	cameraSpherePosition.z += a;
	cameraCoordinateUpdate();
}

void Camera::resize(int width, int height) {
	projectionMatrix = glm::perspective(45.0f, ((float)width)/((float)height), 0.01f, 1000.0f);
	update();
}

void Camera::keyboardDown(SDL_KeyboardEvent& key){
	//previousLookedPoint = lookedPoint;
	//sphereCoordinateUpdate();
	//cameraCoordinateUpdate();
	float s = 0.5f;
	if (key.keysym.sym == SDLK_w) {
		lookedPoint.x += s;
		cameraPosition.x += s;
	}
	if (key.keysym.sym == SDLK_s) {
		lookedPoint.x -= s;
		cameraPosition.x -=s;
	}
	if (key.keysym.sym == SDLK_a) {
		lookedPoint.z += s;
		cameraPosition.z += s;
	}
	if (key.keysym.sym == SDLK_d) {
		lookedPoint.z -= s;
		cameraPosition.z -= s;
	}
	sphereCoordinateUpdate();
	cameraCoordinateUpdate();
	if (key.keysym.sym == SDLK_SPACE) {
		std::cout << "C: " << cameraPosition.x << "," << cameraPosition.y << "," << cameraPosition.z << std::endl;
		std::cout << "S: " << cameraSpherePosition.x << "," << cameraSpherePosition.y << "," << cameraSpherePosition.z << std::endl;
	}
}

void Camera::keyboardUp(SDL_KeyboardEvent& key){
}

void Camera::mouseMove(SDL_MouseMotionEvent& mouse) {
	if ( mouse.state & SDL_BUTTON_LMASK ) {
		sphereCoordinateShift(0, mouse.xrel/100.0f, mouse.yrel/100.0f);
	}
}

void Camera::mouseWheel(SDL_MouseWheelEvent& wheel) {
	if (wheel.y > 0) {
		sphereCoordinateShift(wheel.y*2.0f, 0, 0);
	}
	else if (wheel.y < 0) {
		sphereCoordinateShift(wheel.y*2.0f, 0, 0);
	}
}

void Camera::setLookedPoint(glm::vec3 lookPoint) {
	setView(cameraPosition, lookPoint);
}

