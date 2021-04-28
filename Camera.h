/*
	GPU accelerated rigid body simulation with OpenGL and OpenCL.
	Created by: Sándor Balázs - it.sandor.balazs@gmail.com
	AX400
	---
	Own camera implementation with sphere coordniates.
*/

#pragma once

#include <SDL.h>
#include <glm/glm.hpp>

class Camera {
public:
	Camera(void);
	~Camera(void);

	void setView(glm::vec3 cameraPosition, glm::vec3 _at);

	void setLookedPoint(glm::vec3 _at);

	glm::vec3 getCameraPosition() {
		return cameraPosition;
	}

	glm::vec3 getLookedPoint() {
		return lookedPoint;
	}

	glm::vec3 getUpwardVector() {
		return upwardDirection;
	}

	glm::mat4 getProjectionMatrix() {
		return projectionMatrix;
	}

	//The product of the view and the projection matrix
	glm::mat4 gerViewProjectionMatrix() {
		return projectionMatrix * viewMatrix;
	}

	void resize(int _w, int _h);
	void keyboardDown(SDL_KeyboardEvent& key);
	void keyboardUp(SDL_KeyboardEvent& key);
	void mouseMove(SDL_MouseMotionEvent& mouse);
	void mouseWheel(SDL_MouseWheelEvent& wheel);
	glm::mat4 getViewMatrix() {
		return viewMatrix;
	}
	void update();

	glm::vec3 previousLookedPoint = glm::vec3(0.0f);
private:
	void cameraCoordinateUpdate();
	void sphereCoordinateUpdate();

	void setProjection(float angle, float aspect, float zNear, float zFar);
	void sphereCoordinateShift(float r, float a, float b);

	//The view matrix of the camera
	glm::mat4	viewMatrix;

	//The camera position.
	glm::vec3	cameraPosition;

	//The camera position in the sphere.
	glm::vec3	cameraSpherePosition;

	//The vector pointing upwards
	glm::vec3	upwardDirection;

	//The camera look at point.
	glm::vec3	lookedPoint;

	//The projection matrix
	glm::mat4	projectionMatrix;

};

