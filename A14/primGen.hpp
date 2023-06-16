/**
 * Since the cube is centered in the origin and has edge len of 2, each of its vertices will be in
 * a position with all coordinates equal to either +1 or -1.
 * We can also notice that the four vertices composing a cube face have the coordinate indicated by the
 * only norm coord != 0 equal to that coord, and the other two coordinates are all the four possible
 * combinations of +/-1.
 * That's why it's the only required param is the norm of the face.
 */
void createCubeFace(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx, glm::vec3 norm) {
    int fixedIndex;
    float fixedValue;
    for (int i : {0, 1, 2}) {
        if (norm[i] != 0){
            fixedIndex = i;
            fixedValue = norm[i];
        }
    }

    std::vector<int> variableIndices = {0, 1, 2};
    variableIndices.erase(variableIndices.begin() + fixedIndex);

    int firstVIdx = -1;
    for (float i : {1.0f, -1.0f}) {
        for (float j : {1.0f, -1.0f}) {
            glm::vec3 pos = {};
            pos[fixedIndex] = fixedValue;
            pos[variableIndices[0]] = i;
            pos[variableIndices[1]] = j;

            if (firstVIdx == -1) firstVIdx = (int)vDef.size();
            vDef.push_back({pos, norm});
        }
    }

    vIdx.push_back(firstVIdx); vIdx.push_back(firstVIdx + 1); vIdx.push_back(firstVIdx + 2);
    vIdx.push_back(firstVIdx + 1); vIdx.push_back(firstVIdx + 2); vIdx.push_back(firstVIdx + 3);
}

void Assignment14::createCubeMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx) {
	// The primitive built here is a cube centered in the origin, whose edge lenght is 2.
	// Fill array vPos with the positions of the vertices of the mesh

    createCubeFace(vDef, vIdx, {1.0, 0.0, 0.0});
    createCubeFace(vDef, vIdx, {-1.0, 0.0, 0.0});
    createCubeFace(vDef, vIdx, {0.0, 1.0, 0.0});
    createCubeFace(vDef, vIdx, {0.0, -1.0, 0.0});
    createCubeFace(vDef, vIdx, {0.0, 0.0, 1.0});
    createCubeFace(vDef, vIdx, {0.0, 0.0, -1.0});
}

glm::vec3 computeSurface(glm::vec2 coord) {
    // y = sin(x) * cos(z)
    float y = sin(coord.x) * cos(coord.y);
    return {coord.x, y, coord.y};
}

glm::vec3 computeSurfaceNorm(glm::vec3 pos) {
    /* cross product of the partial derivatives of y = sin(x) * cos(z)
        y = sinx * cosz
        pos = [x, sinx * cosz, z]

        ddx = [1, cosx * cosz, 0]
        ddz = [0, -sinx * sinz, 1]

        crossprod = [a2b3 - a3b2 = cosx * cosz, a3b1 - a1b3 = -1, a1b2 - a2b1 = -sinx * sinz]
                  = [cosx * cosz, -1, -sinx * sinz]
     */

    // note: norm must be normalized and is multiplied by -1 to get the other side of the surface norms
    return glm::normalize(glm::vec3(
            -cos(pos.x) * cos(pos.z),
            1.0,
            sin(pos.x) * sin(pos.z)));
}

void Assignment14::createFunctionMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx) {
	// The procedure fills array vPos with the positions of the vertices and of the normal vectors of the mesh
	// The procedures also fill the array vIdx with the indices of the vertices of the triangles
	// The primitive built here is the surface y = sin(x) * cos(z) with -3 <= x <= 3 and -3 <= z <= 3.
	
	// Fill array vPos with the positions of the vertices of the mesh

    // range parameters
    float start = -3.0; // included in range
    float end = 3.0; // excluded from range
    float pace = 0.1; // creates 6.0/0.1 = 60 values -> 60x60 square
    int edgeSize = (int) ((end - start) / pace); // 60

    // create the xz range of values
    std::vector<float> range;
    int count = 0; // makes sure range has size 60 avoiding float approx issues
    for (float i = start; i < end; i+= pace) {
        range.push_back(i);

        if (count < edgeSize - 1) count++;
        else break;
    }

    for (float x : range) {
        for (float z : range) {
            glm::vec3 pos = computeSurface({x, z});
            glm::vec3 norm = computeSurfaceNorm(pos);
            vDef.push_back({pos, norm});
        }
    }

    for (int x = 0; x < edgeSize - 1; ++x) {
        for (int z = 0; z < edgeSize - 1; ++z) {
            int upperLeft = edgeSize * x + z; // index of upper left corner of triangle
            int upperRight = upperLeft + 1;
            int lowerLeft = edgeSize * (x + 1) + z; // index of lower left corner of triangle
            int lowerRight = lowerLeft + 1;
            /*
            std::cout << std::setprecision(2) << std::fixed
            << "(" << std::setw(4) << upperLeft << ")"
            << std::setw(6) << vDef[upperLeft].pos.x
            << std::setw(6) << vDef[upperLeft].pos.y
            << std::setw(6) << vDef[upperLeft].pos.z << " |"; */
            vIdx.push_back(upperLeft); vIdx.push_back(upperRight); vIdx.push_back(lowerLeft);
            vIdx.push_back(upperRight); vIdx.push_back(lowerLeft); vIdx.push_back(lowerRight);
        }
        // std::cout << "\n";
    }

    /*
    int conta = 1;
    for (int i : vIdx) {
        std::cout << i << " ";
        if (conta % 3 == 0) std::cout << "|";
        if (conta % 60 == 0) std::cout << "\n";
        conta++;
    }
    */
}

/**
 * creates a disc centered on and normal to the y-axis
 * @param y height coordinate at which to create the disc (norm direction of points is determined by y's sign)
 * @param r radius of the disc
 * @param sides sides of the figure approximating a circle
 */
void createDisc(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx, float y, float r, int sides, bool normOut = false) {
    int startIndex = (int) vDef.size();
    glm::vec3 norm = {0, abs(y) / y, 0}; // norm is the same for all points of the disc if !normOut

    vDef.push_back({{0.0f, y, 0.0f}, norm}); // vDef[0] is the origin of the disc


    for (int i = 0; i < sides; ++i) {
        auto x = (float) r * cos(2 * M_PI * ((float)i) / sides);
        auto z = (float) r * sin(2 * M_PI * ((float)i) / sides);
        if (normOut) norm = glm::normalize(glm::vec3(x, 0.0, z));
        vDef.push_back({{x, y, z}, norm});
    }

    if (normOut) return;
    for (int i = 1; i < sides; ++i) {
        vIdx.push_back(startIndex); vIdx.push_back(startIndex + i); vIdx.push_back(startIndex + i + 1);
    }
    vIdx.push_back(startIndex); vIdx.push_back(startIndex + 1); vIdx.push_back(startIndex + sides);

}

/**
 * creates a tube centered on and normal to the y-axis
 * @param y1 height coordinate at which the tube starts
 * @param y2 height coordinate at which th tube ends
 * @param r radius of the tube
 * @param sides sides of the figure approximating a circle
 */
void createTube(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx, float y1, float y2, float r, int sides) {
    for (int i = 1; i < sides; ++i) { // 1 to 19
        vIdx.push_back(i); vIdx.push_back(i + 1); vIdx.push_back(i + sides + 1);
        vIdx.push_back(i + sides + 2); vIdx.push_back(i + 1); vIdx.push_back(i + sides + 1);
    }
    // last 2
    vIdx.push_back(sides); vIdx.push_back(1); vIdx.push_back(2 * sides + 1);
    vIdx.push_back(1); vIdx.push_back(sides + 2); vIdx.push_back(2 * sides + 1);
}

void Assignment14::createCylinderMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx) {
	// The procedure fills array vPos with the positions of the vertices and of the normal vectors of the mesh
	// The procedures also fill the array vIdx with the indices of the vertices of the triangles
	// The primitive built here is a cylinder, with radius 1, and height 2, centered in the origin.

    int sides = 60;
    // the discs are created twice to have different norms for the faces vs the sides
    createDisc(vDef, vIdx, 1.0, 1.0, sides, true);
    createDisc(vDef, vIdx, -1.0, 1.0, sides, true);
    createTube(vDef, vIdx, 1.0, -1.0, 1.0, sides);
    createDisc(vDef, vIdx, 1.0, 1.0, sides);
    createDisc(vDef, vIdx, -1.0, 1.0, sides);

}
