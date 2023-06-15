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

void Assignment14::createFunctionMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx) {
	// The procedure fills array vPos with the positions of the vertices and of the normal vectors of the mesh
	// The procedures also fill the array vIdx with the indices of the vertices of the triangles
	// The primitive built here is the surface y = sin(x) * cos(z) with -3 <= x <= 3 and -3 <= z <= 3.
	
	// Fill array vPos with the positions of the vertices of the mesh
	vDef.push_back({{0.0f, 0.0f, 0.1f}, {0.5f, 0.0f, 0.866f}});	// vertex 0 - Position and Normal
	vDef.push_back({{1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}});	// vertex 1 - Position and Normal
	vDef.push_back({{0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}});	// vertex 2 - Position and Normal

	// Fill the array vIdx with the indices of the vertices of the triangles
	vIdx.push_back(0); vIdx.push_back(1); vIdx.push_back(2);	// First triangle
}

void Assignment14::createCylinderMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx) {
	// The procedure fills array vPos with the positions of the vertices and of the normal vectors of the mesh
	// The procedures also fill the array vIdx with the indices of the vertices of the triangles
	// The primitive built here is a cylinder, with radius 1, and height 2, centered in the origin.
	
	// Fill array vPos with the positions of the vertices of the mesh
	vDef.push_back({{1.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 1.0f}});	// vertex 0 - Position and Normal
	vDef.push_back({{0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 1.0f}});	// vertex 1 - Position and Normal
	vDef.push_back({{1.0f, 1.0f, 0.1f}, {-0.5f, 0.0f, 0.866f}});// vertex 2 - Position and Normal

	// Fill the array vIdx with the indices of the vertices of the triangles
	vIdx.push_back(0); vIdx.push_back(1); vIdx.push_back(2);	// First triangle
}
