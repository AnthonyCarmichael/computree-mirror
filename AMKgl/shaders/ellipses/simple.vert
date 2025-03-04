
///// VERTEX //////

// vertex
attribute vec3 vertex;

///// COLOR //////

// color
attribute vec4 color;

///// MATRIX /////

// matrix
attribute mat3 params;

void main()
{
    if(prepareToComputeVertex(color, true)) {

        mat4 newMatrix = mat4(1.0);

        newMatrix[0] = vec4(params[0], 0);
        newMatrix[1] = vec4(cross(params[0], params[1]), 0);
        newMatrix[2] = vec4(params[1], 0);
        newMatrix[3] = vec4(params[2], 1);

        gl_Position = gl_ModelViewProjectionMatrix * newMatrix * vec4(vertex, 1);
    }
}
