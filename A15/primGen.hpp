/**
 * Adapted from the sol of the previous assignment.
 * Because the box is centered in the origin, we know that the coordinate of each point will either be
 * + or - a value (eg horizontal = 1.16 -> all points either have z = +1.16 or z = -1.16)
 */
void createRectangleFace(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx, glm::vec3 norm, glm::vec3 boxDimensions, glm::vec3 uv) {

    int fixedIndex;
    float fixedValue;
    for (int i : {0, 1, 2}) {
        if (norm[i] != 0){
            fixedIndex = i;
            fixedValue = norm[i] * boxDimensions[i];
        }
    }

    std::vector<int> variableIndices = {0, 1, 2};
    variableIndices.erase(variableIndices.begin() + fixedIndex);

    int firstVIdx = -1;
    for (float i : {1.0f, -1.0f}) {
        for (float j : {1.0f, -1.0f}) {
            glm::vec3 pos = {};
            pos[fixedIndex] = fixedValue;
            pos[variableIndices[0]] = i * boxDimensions[variableIndices[0]];
            pos[variableIndices[1]] = j * boxDimensions[variableIndices[1]];

            if (firstVIdx == -1) firstVIdx = (int)vDef.size();
            vDef.push_back({pos, norm, uv});
        }
    }

    vIdx.push_back(firstVIdx); vIdx.push_back(firstVIdx + 1); vIdx.push_back(firstVIdx + 2);
    vIdx.push_back(firstVIdx + 1); vIdx.push_back(firstVIdx + 2); vIdx.push_back(firstVIdx + 3);
}

void Assignment15::createBoxMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx) {
	// The primitive built here is a box centered in the origin, with proportions respecting the texture.

	// The procedure fills array vPos with the positions of the vertices and of the normal vectors of the mesh
	//vDef.push_back({{0,0,0}, {0,0,1}, {95.0 / 1024.0, 95.0 / 512.0}});	// vertex 0 - Position, Normal and uv

    /* calculations for box coordinates and uv (computed from the box texture pixels measurements):
     * horizontal = 349 -> 349/300 = 1.16 (z)
     * vertical = 324 -> 324/300 = 1.08 (y)
     * short = 95 -> 95/300 = 0.32 (x)
     *
     * other coordinates written onn the image TBs_20140623_1_02-annotated.png
     */
    glm::vec3 boxDim = {0.32, 1.08, 1.16};

    createRectangleFace(vDef, vIdx, {1.0, 0.0, 0.0}, boxDim, {0, 0, 0});
    createRectangleFace(vDef, vIdx, {-1.0, 0.0, 0.0}, boxDim, {0, 0, 0});
    createRectangleFace(vDef, vIdx, {0.0, 1.0, 0.0}, boxDim, {0, 0, 0});
    createRectangleFace(vDef, vIdx, {0.0, -1.0, 0.0}, boxDim, {0, 0, 0});
    createRectangleFace(vDef, vIdx, {0.0, 0.0, 1.0}, boxDim, {0, 0, 0});
    createRectangleFace(vDef, vIdx, {0.0, 0.0, -1.0}, boxDim, {0, 0, 0});

}

#define M_PI 3.141595f
void Assignment15::createSphereMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx) {
	// The primitive built here is a sphere of radius 1, centered in the origin, on which the Mars texture is applied seamless.
	
	// The procedure fills array vPos with the positions of the vertices and of the normal vectors of the mesh
	vDef.push_back({{0,0,0}, {0,0,1}, {0,0}});	// vertex 0 - Position, Normal and uv
	vDef.push_back({{1,0,0}, {0,0,1}, {1,0}});	// vertex 1 - Position and Normal
	vDef.push_back({{0,1,0}, {0,0,1}, {0,1}});	// vertex 2 - Position and Normal
	vDef.push_back({{1,1,0}, {0,0,1}, {1,1}});// vertex 3 - Position and Normal

	// The procedures also fill the array vIdx with the indices of the vertices of the triangles
	vIdx.push_back(0); vIdx.push_back(1); vIdx.push_back(2);	// First triangle
	vIdx.push_back(1); vIdx.push_back(2); vIdx.push_back(3);	// Second triangle
}

