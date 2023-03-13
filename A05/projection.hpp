

glm::mat4 perspectiveVulkan(float radians, float aspect, float zNear, float zFar);

void SetupProjectionMatrices(Assignment05 *A, float Ar) {
/**************
 Method Matrix(int N, glm::mat4 M) of object A,
 receives in N the number of the matrix that needs to be set, and the matrix in M
***************/

	glm::mat4 S;

    float n = 0.1f; // near-plane
    float f = 50.0f; // far-plane
    float a = Ar; // aspect-ratio
	
	// Fov-y = 60 deg
    float fovy = glm::radians(60.0f);
	S = perspectiveVulkan(fovy, a, n, f);
    S[1][1] *= -1;
	A->Matrix(1, S); // sets the matrix corresponding to piece 1

	// Fov-y = 105 deg
    fovy = glm::radians(105.0f);
	S = perspectiveVulkan(fovy, a, n, f);
	A->Matrix(2, S); // sets the matrix corresponding to piece 2

	// Fov-y = 25 deg
    fovy = glm::radians(25.0f);
	S = perspectiveVulkan(fovy, a, n, f);
	A->Matrix(3, S); // sets the matrix corresponding to piece 3

	// Right View, Fov-x = 45 deg
    // TODO: fix geometry and make right view
    float fovx = glm::radians(45.0f);
    float w = 2 * n * tan(fovx);
    float h = w / a;
    //std::cout << "aspect ratio a: " << a;
    fovy = atan(h/n);
	S = perspectiveVulkan(fovy, a, n, f);
	A->Matrix(4, S); // sets the matrix corresponding to piece 4

}

glm::mat4 perspectiveVulkan(float fovyRadians, float aspect, float zNear, float zFar) {
    glm::mat4 perspective = glm::perspective(fovyRadians, aspect, zNear, zFar);
    perspective[1][1] *= -1;
    return perspective;
}
