////////////////////////////////////////////////////////////////////////////////
// Filename: Modelo.vs
////////////////////////////////////////////////////////////////////////////////
#version 400


/////////////////////
// INPUT VARIABLES //
/////////////////////
in vec3 inputPosition;
in vec3 inputNormal;
in vec2 inputTexCoord;
in vec3 inputTangent;
in vec3 inputBinormal;

//////////////////////
// OUTPUT VARIABLES //
//////////////////////
out vec2 texCoord;
out vec3 normal;
out vec3 tangente;
out vec3 binormal;
out vec3 posicion;
out vec3 lightPosition;
out vec3 NormLightDirection;
out vec4 clipSpace;

///////////////////////
// UNIFORM VARIABLES //
///////////////////////
uniform mat4 worldMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 ligthPoint;
uniform vec3 ligthDirection;

void main(void)
{
	NormLightDirection = normalize(ligthDirection - posicion);
	NormLightDirection = -NormLightDirection;
	
	// Calculate the position of the vertex against the world, view, and projection matrices.
	gl_Position = worldMatrix * vec4(inputPosition, 1.0f);

	posicion = vec3(gl_Position);
	gl_Position = viewMatrix * gl_Position;
	gl_Position = projectionMatrix * gl_Position;
	clipSpace = gl_Position;

	texCoord = vec2(inputTexCoord.x/2.0 + 0.5, inputTexCoord.y/2.0 + 0.5) * 5.6;
	//texCoord = inputTexCoord;
	
	normal = vec3(worldMatrix * vec4(inputNormal,0));
	tangente = vec3(worldMatrix * vec4(inputTangent,0));
	binormal = cross(tangente, normal);

	// Normalize the normal vector.
	normal = normalize(normal);
	tangente = normalize(tangente);
	binormal = normalize(binormal);	
	
}