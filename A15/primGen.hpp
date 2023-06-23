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
        auto u = (float) (0.5 + ( (atan2(z, x)) / (2 * M_PI) ));
        auto v = (float) (0.5 + ( (asin(h)) / M_PI ));
        vDef.push_back({pos, norm, {u, v}});
    }
}

void Assignment15::createSphereMesh(std::vector<Vertex> &vDef, std::vector<uint32_t> &vIdx) {
	// The primitive built here is a sphere of radius 1, centered in the origin, on which the Mars texture is applied seamless.
    int nDisc = 6;
    int nHeight = 6;

	vDef.push_back({{0,1,0}, {0,1,0}, {0,1}});	// North Pole
    for (int i = 0; i < nHeight; ++i) {
        // createVertexDisc with nHeight different heights from +1 to -1
    }
    createVertexDisc(vDef, 0.7, nDisc);

    for (int i = 0; i < nDisc - 1; ++i) {
        vIdx.push_back(0); vIdx.push_back(i + 1); vIdx.push_back(i + 2);	// First triangle
    }
    vIdx.push_back(0) ; vIdx.push_back(1); vIdx.push_back(nDisc);
}

