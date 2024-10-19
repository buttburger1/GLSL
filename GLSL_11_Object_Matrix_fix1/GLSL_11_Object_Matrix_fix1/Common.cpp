#include "Common.h"

//ARCBALL
glm::mat4 LookAt(const glm::vec3& Eye, const glm::vec3& Center, const glm::vec3& Up)
{
	glm::mat4 Matrix;
	glm::vec3 X, Y, Z;
	Z = Eye - Center;
	glm::normalize(Z);//Z.glm::Normalize();
	Y = Up;

	X = glm::cross(Y, Z);//X = Y.Cross( Z );
	Y = glm::cross(Z, X);//Y = Z.Cross( X );

	glm::normalize(X);//X.Normalize();
	glm::normalize(Y);//Y.Normalize();
	Matrix[0][0] = X.x;
	Matrix[1][0] = X.y;
	Matrix[2][0] = X.z;

	Matrix[3][0] = glm::dot(-X, Eye);//Matrix[3][0] = -X.Dot(Eye);

	Matrix[0][1] = Y.x;
	Matrix[1][1] = Y.y;
	Matrix[2][1] = Y.z;

	Matrix[3][1] = glm::dot(-Y, Eye);//Matrix[3][1] = -Y.Dot(Eye);

	Matrix[0][2] = Z.x;
	Matrix[1][2] = Z.y;
	Matrix[2][2] = Z.z;
	Matrix[3][2] = glm::dot(-Z, Eye);//Matrix[3][2] = -Z.Dot(Eye);
	Matrix[0][3] = 0;
	Matrix[1][3] = 0;
	Matrix[2][3] = 0;
	Matrix[3][3] = 1.0f;
	return Matrix;
}

//Returns a quaternion such that q*start = dest
quat RotationBetweenVectors(vec3 start, vec3 dest)
{
	start = normalize(start);
	dest = normalize(dest);

	float cosTheta = dot(start, dest);
	vec3 rotationAxis;

	if(cosTheta < -1 + 0.001f)
	{
		//special case when vectors in opposite directions :
		//there is no "ideal" rotation axis
		//So guess one; any will do as long as it's perpendicular to start
		//This implementation favors a rotation around the Up axis,
		//since it's often what you want to do.
		rotationAxis = cross(vec3(0.0f, 0.0f, 1.0f), start);
		if(length2(rotationAxis) < 0.01 )//bad luck, they were parallel, try again!
			rotationAxis = cross(vec3(1.0f, 0.0f, 0.0f), start);

		rotationAxis = normalize(rotationAxis);
		return angleAxis(glm::radians(180.0f), rotationAxis);
	}

	//Implementation from Stan Melax's Game Programming Gems 1 article
	rotationAxis = cross(start, dest);

	float s = sqrt((1+cosTheta)*2);
	float invs = 1 / s;

	return quat(
		s * 0.5f,
		rotationAxis.x * invs,
		rotationAxis.y * invs,
		rotationAxis.z * invs
		);
}

//Returns a quaternion that will make your object looking towards 'direction'.
//Similar to RotationBetweenVectors, but also controls the vertical orientation.
//This assumes that at rest, the object faces +Z.
//Beware, the first parameter is a direction, not the target point!
quat qLookAt(vec3 direction, vec3 desiredUp)
{
	if(length2(direction) < 0.0001f)return quat();

	//Recompute desiredUp so that it's perpendicular to the direction
	//You can skip that part if you really want to force desiredUp

	vec3 right = cross(direction, desiredUp);
	desiredUp = cross(right, direction);

	//Find the rotation between the front of the object (that we assume towards +Z,
	//but this depends on your model) and the desired direction

	quat rot1 = RotationBetweenVectors(vec3(0.0f, 0.0f, 1.0f), direction);

	//Because of the 1rst rotation, the up is probably completely screwed up. 
	//Find the rotation between the "up" of the rotated object, and the desired up

	vec3 newUp = rot1 * vec3(0.0f, 1.0f, 0.0f);
	quat rot2 = RotationBetweenVectors(newUp, desiredUp);
	return rot2 * rot1; //Apply them in reverse order.
}

//Like SLERP, but forbids rotation greater than maxAngle (in radians)
//In conjunction to LookAt, can make your characters
quat RotateTowards(quat q1, quat q2, float maxAngle)
{
	if(maxAngle < 0.001f)
	{
		//No rotation allowed. Prevent dividing by 0 later.
		return q1;
	}
	float cosTheta = dot(q1, q2);
	//q1 and q2 are already equal.
	//Force q2 just to be sure
	if(cosTheta > 0.9999f)
	{
		return q2;
	}
	//Avoid taking the long path around the sphere
	if(cosTheta < 0)
	{
		q1 = q1*-1.0f;
		cosTheta *= -1.0f;
	}
	float angle = acos(cosTheta);
	//If there is only a 2° difference, and we are allowed 5°, then we arrived.
	if(angle < maxAngle)
	{
		return q2;
	}
	//This is just like slerp(), but with a custom t
	float t = maxAngle / angle;
	angle = maxAngle;

	quat res = (sin((1.0f - t) * angle) * q1 + sin(t * angle) * q2) / sin(angle);
	res = normalize(res);
	return res;
}

void tests()
{
	glm::vec3 Xpos(+1.0f,  0.0f,  0.0f);
	glm::vec3 Ypos( 0.0f, +1.0f,  0.0f);
	glm::vec3 Zpos( 0.0f,  0.0f, +1.0f);
	glm::vec3 Xneg(-1.0f,  0.0f,  0.0f);
	glm::vec3 Yneg( 0.0f, -1.0f,  0.0f);
	glm::vec3 Zneg( 0.0f,  0.0f, -1.0f);

	//Testing standard, easy case
	//Must be 90° rotation on X : 0.7 0 0 0.7
	quat X90rot = RotationBetweenVectors(Ypos, Zpos);
	//Testing with v1 = v2
	//Must be identity : 0 0 0 1
	quat id = RotationBetweenVectors(Xpos, Xpos);
	//Testing with v1 = -v2
	//Must be 180° on +/-Y axis : 0 +/-1 0 0
	quat Y180rot = RotationBetweenVectors(Xpos, Xneg);
	//Testing with v1 = -v2, but with a "bad first guess"
	//Must be 180° on +/-Y axis : 0 +/-1 0 0
	quat X180rot = RotationBetweenVectors(Zpos, Zneg);
}

/*
void hermiteCurve(int steps, float p1, float p2)
{
	for(int t = 0; t < steps; t += 1)
	{
		//float s = (float)t / (float)steps;    // scale s to go from 0 to 1
		//float s = (float)t / (float)1.0f;    // scale s to go from 0 to 1
		float s = t / 1;    // scale s to go from 0 to 1
		//float h1 =  2s^3 - 3s^2 + 1;          // calculate basis function 1
		float h1 = 2* pow(s, 3) - 3* pow(s, 2) + 1;          // calculate basis function 1
		//float h2 = -2s^3 + 3s^2;              // calculate basis function 2
		float h2 = -2* pow(s, 3) + 3* pow(s, 2);              // calculate basis function 2
		//float h3 =   s^3 - 2*s^2 + s;         // calculate basis function 3
		float h3 = pow(s,3) - 2* pow(s, 2) + s;         // calculate basis function 3
		//float h4 =   s^3 -  s^2;              // calculate basis function 4
		float h4 = pow(s,3) - pow(s,2);              // calculate basis function 4

		//X POINTS
		//vec2 p1(0.0f,0.0f);
		//p1 = myXOutput[0][0];
		//vec2 p2(8.0f,0.0f);
		//p2 = myXOutput[0][1];

		//TEST X TANGENT 1
		vec2 tangentOut1(myXOutTangent[0][0], 0.0f);
		vec2 tangentIn1(myXInTangent[0][0], 0.0f);
		//TEST X TANGENT 2
		vec2 tangentOut2(myXOutTangent[0][1], 0.0f);
		vec2 tangentIn2(myXInTangent[0][1], 0.0f);

		vec2 p;
		if(t == 0)
		{
			p = vec2(h1*p1) +                    // multiply and sum all funtions
				vec2(h2*p2) +                    // together to build the interpolated
				vec2(h3*tangentOut1) +                    // point along the curve.
				vec2(h4*tangentIn1);
			p1 = p.x;
		}
		if(t == 1)
		{
			p = vec2(h1*p1) +                    // multiply and sum all funtions
				vec2(h2*p2) +                    // together to build the interpolated
				vec2(h3*tangentOut2) +                    // point along the curve.
				vec2(h4*tangentIn2);
			p2 = p.x;
		}
		//lineto (p)                            // draw to calculated point on the curve
		//printf("t: %f X: %f Y: %f\n", t, p.x, p.y);
		//printf("t: %d X: %f Y: %f\n", t, p.x, p.y);
	}
}
*/