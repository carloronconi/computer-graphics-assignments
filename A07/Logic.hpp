

void GameLogic(Assignment07 *A, float Ar, glm::mat4 &ViewPrj, glm::mat4 &World) {
	// The procedure must implement the game logic  to move the character in third person.
	// Input:
	// <Assignment07 *A> Pointer to the current assignment code. Required to read the input from the user
	// <float Ar> Aspect ratio of the current window (for the Projection Matrix)
	// Output:
	// <glm::mat4 &ViewPrj> the view-projection matrix of the camera
	// <glm::mat4 &World> the world matrix of the object
	// Parameters
	// Camera FOV-y, Near Plane and Far Plane
	const float FOVy = glm::radians(45.0f);
	const float nearPlane = 0.1f;
	const float farPlane = 100.f;
	
	// Player starting point
	const glm::vec3 StartingPosition = glm::vec3(-41.50, 0.0, -19.5);
	
	// Camera target height and distance
	const float camHeight = 0.25;
	const float camDist = 1.5;
	// Camera Pitch limits
	const float minPitch = glm::radians(-8.75f);
	const float maxPitch = glm::radians(60.0f);
	// Rotation and motion speed
	const float ROT_SPEED = glm::radians(120.0f);
	const float MOVE_SPEED = 2.0f;

	// Integration with the timers and the controllers
	// returns:
	// <float deltaT> the time passed since the last frame
	// <glm::vec3 m> the state of the motion axes of the controllers (-1 <= m.x, m.y, m.z <= 1)
	// <glm::vec3 r> the state of the rotation axes of the controllers (-1 <= r.x, r.y, r.z <= 1)
	// <bool fire> if the user has pressed a fire button (not required in this assginment)
	float deltaT;
	glm::vec3 m = glm::vec3(0.0f), r = glm::vec3(0.0f);
	bool fire = false;
	A->getSixAxis(deltaT, m, r, fire);

	// Game Logic implementation
	// Current Player Position - static variables make sure that their value remain unchanged in subsequent calls to the procedure
	static glm::vec3 Pos = StartingPosition;


	// To be done in the assignment

    static auto Rot = glm::vec3(0, 0, 0);

    Pos.x += MOVE_SPEED * m.x * deltaT;
    Pos.y += MOVE_SPEED * m.y * deltaT;
    Pos.z += -MOVE_SPEED * m.z * deltaT;

    Rot.x += ROT_SPEED * r.x * deltaT;
    Rot.y += ROT_SPEED * r.y * deltaT;
    Rot.z += ROT_SPEED * r.z * deltaT;

    World = glm::translate(glm::mat4(1),glm::vec3(Pos.x, Pos.y, Pos.z)) *
            glm::rotate(glm::mat4(1), Rot.x,glm::vec3(1, 0, 0)) *
            glm::rotate(glm::mat4(1), Rot.y, glm::vec3(0, 1, 0)) *
            glm::rotate(glm::mat4(1), Rot.z, glm::vec3(0, 0, 1));

    float pitch = glm::radians(15.0f);
    auto cameraPosition = glm::vec3(0.0f);
    auto cameraPositionHomogeneous = glm::vec4(0.0f);
    cameraPositionHomogeneous = World *
            glm::vec4(0.0f, camHeight + camDist * std::sin(pitch), camDist * std::cos(pitch), 1);

    cameraPosition.x = cameraPositionHomogeneous.x;
    cameraPosition.y = cameraPositionHomogeneous.y;
    cameraPosition.z = cameraPositionHomogeneous.z;

    auto characterPosition = glm::vec3(0.0f);
    /*auto characterPositionHomogeneous = glm::vec4(0.0f);
    characterPositionHomogeneous = World * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

    characterPosition.x = characterPositionHomogeneous.x;
    characterPosition.y = characterPositionHomogeneous.y;
    characterPosition.z = characterPositionHomogeneous.z + camHeight;*/

    glm::mat4 Mv = glm::lookAt(cameraPosition, Pos, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Mprj = glm::perspective(FOVy, Ar, nearPlane, farPlane);
    Mprj[1][1] *= -1;
    ViewPrj = Mprj * Mv;
}