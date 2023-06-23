/**
 * Adapted from the sol of the previous assignment.
 * Because the box is centered in the origin, we know that the coordinate of each point will either be
 * + or - a value (eg horizontal = 1.16 -> all points either have z = +1.16 or z = -1.16)
 */
void createRectangleFace(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx, glm::vec3 norm,
                         glm::vec3 boxDimensions, glm::vec2 lowUV, glm::vec2 pixels, float scale) {

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

            //uv coords of the lowest corner of the rectangle are passed, others are deducted from the dimensions of the box
            float u = (i > 0) ? lowUV.x + boxDimensions[variableIndices[0]] * scale : lowUV.x;
            u = u / pixels.x;
            float v = (j > 0) ? lowUV.y + boxDimensions[variableIndices[1]] * scale : lowUV.y;
            v = v / pixels.y;
            vDef.push_back({pos, norm, {u, v}});
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
    float scale = 300.0;
    glm::vec3 boxDim = {95.0 / scale, 324.0 / scale, 349.0 / scale};

    createRectangleFace(vDef, vIdx, {1.0, 0.0, 0.0}, boxDim, {95.0, 95.0}, {1024.0, 512.0}, scale);
    // createRectangleFace(vDef, vIdx, {-1.0, 0.0, 0.0}, boxDim, {541.0, 95.0}, {1024.0, 512.0}, scale);
    //createRectangleFace(vDef, vIdx, {0.0, 1.0, 0.0}, boxDim, {0, 0, 0});
    //createRectangleFace(vDef, vIdx, {0.0, -1.0, 0.0}, boxDim, {0, 0, 0});
    //createRectangleFace(vDef, vIdx, {0.0, 0.0, 1.0}, boxDim, {0, 0, 0});
    //createRectangleFace(vDef, vIdx, {0.0, 0.0, -1.0}, boxDim, {0, 0, 0});

}

#define M_PI 3.141595f
/**
 * creates a disc of the unitary-radius sphere of n vertices at the specified height for which the radius is computed based on the height
 * @param vDef vertices vector
 * @param h height
 * @param n number of points in the disc
 */
void createVertexDisc(std::vector<Vertex> &vDef, float h, int n) {
    float r = sqrt(1.0 - pow(h, 2.0)); // compute the radius of the disc using Pythagoras' theorem

    for (int i = 0; i < n; ++i) {
        auto x = (float) r * cos(2 * M_PI * ((float)i) / n);
        auto z = (float) r * sin(2 * M_PI * ((float)i) / n);
        glm::vec3 pos = {x, h, z};
        glm::vec3 norm = glm::normalize(pos); // the norm is the same as the pos for an origin-centered sphere!
        auto u = (float) 1.0f - (0.5 + ( (atan2(z, x)) / (2 * M_PI) ));
        auto v = (float) 1.0f - (0.5 + ( (asin(h)) / M_PI ));
        vDef.push_back({pos, norm, {u, v}});
    }
}

void Assignment15::createSphereMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx) {
	// The primitive built here is a sphere of radius 1, centered in the origin, on which the Mars texture is applied seamless.
    int nDisc = 100;
    int nHeight = 50;

	vDef.push_back({{0,1,0}, {0,1,0}, {0,0}});	// North Pole in y = +1

    for (int i = 1; i < nHeight - 1; ++i) { // for each complete horizontal slice (excluding North and South Pole)
        // createVertexDisc with nHeight different heights from +1 to -1: 1 - (2i)/nH
        createVertexDisc(vDef, 1.0f - (2.0f * (float) i)/((float) nHeight), nDisc);
    }

    vDef.push_back({{0,-1,0}, {0,-1,0}, {0,1}});	// South Pole in y = -1

    // connect North Pole to first disc
    for (int i = 0; i < nDisc - 1; ++i) {
        vIdx.push_back(0); vIdx.push_back(i + 1); vIdx.push_back(i + 2);
    }
    vIdx.push_back(0) ; vIdx.push_back(1); vIdx.push_back(nDisc);

    //connect intermediate discs
    for (int i = 0; i < nHeight - 3; ++i) {
        int upperLeft = i * nDisc + 1;
        int lowerLeft = (i + 1) * nDisc + 1;
        for (int j = 0; j < nDisc - 1; ++j) {
            vIdx.push_back(upperLeft + j); vIdx.push_back(upperLeft + j + 1); vIdx.push_back(lowerLeft + j);
            vIdx.push_back(upperLeft + j + 1); vIdx.push_back(lowerLeft + j); vIdx.push_back(lowerLeft + j + 1);
        }
        vIdx.push_back(upperLeft); vIdx.push_back(upperLeft + nDisc - 1); vIdx.push_back(lowerLeft + nDisc - 1);
        vIdx.push_back(upperLeft); vIdx.push_back(lowerLeft); vIdx.push_back(lowerLeft + nDisc - 1);
    }

    // connect South Pole to last disc
    int startingIndex = nDisc * (nHeight - 3) + 1;
    int southPoleIndex = nDisc * (nHeight - 2) + 1;
    for (int i = startingIndex; i < startingIndex + 6; ++i) {
        vIdx.push_back(i); vIdx.push_back(i + 1); vIdx.push_back(southPoleIndex);
    }
    vIdx.push_back(startingIndex) ; vIdx.push_back(startingIndex + nDisc - 1); vIdx.push_back(southPoleIndex);
}

