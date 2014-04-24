/*
 * This file is part of youbot_arm_controller
 *
 * Copyright (c)2014 by Robotics Lab 
 * in the Computer Science Department of the 
 * University of Applied Science Gelsenkirchen
 * 
 * Author: Stefan Wilkes <stefan.wilkes@studmail.w-hs.de>
 *  
 * The package is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * 
 * This package is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef KINEMATICSSOLVER_H
#define KINEMATICSSOLVER_H

#include <eigen3/Eigen/Dense>
#include <vector>

using namespace std;
using namespace Eigen;

/**
 * An object of this class implements the kinematics solver
 * for the youBot manipulator.
 *
 * @author Stefan Wilkes
 */
class KinematicsSolver
{
public:

    /**
     * Constructor:
     * Creates a new kinematics solver.
     */
    KinematicsSolver();

    /**
     * Calculates the TCP Matrix for a given robot state.
     * Forward kinematics.
     *
     * @param angles The actual axis values of the robot in radian.
     * @param tcp Vector which gives information about the posititon and
     *            orientation of the TCP (X, Y, Z, Roll, Pitch, Yaw)
     * @return true if the tcp state estimated successfully
     */
    bool forwardTransformation(VectorXd &angles, VectorXd &tcp);

    /**
     * Calculates the robot state for a given TCP
     * using the inverse tranformation.
     *
     * @param tcp The TCP Vector for the desired world position
     *            (X, Y, Z, Roll, Pitch, Yaw)
     * @param angles A vector for storing the calculated angles
     * @return true if a possible state was calculated
     */
    bool inverseTransformation(VectorXd &tcp, VectorXd &angles);

private:

    /**
     * Implementation of the DH Transformation.
     *
     * @param theta Theta to next frame
     * @param d D to next frame
     * @param alpha Alpha to next frame
     * @param r R to next frame
     * @return Matrix with position and orientation for the next frame
     */
    Matrix4f dhTransformation(float theta, float d, float alpha, float r);

    /**
     * Calculates the robot state for a given TCP
     * using the geometric inverse tranformation.
     *
     * @param tcp The TCP vector for the desired position and orientation.
     * @param angles A vector for storing the calculated angles
     * @return true if a possible state was calculated
     */
    bool inverseTransformationNumeric(VectorXd &tcp, VectorXd &angles);

    /**
     * Calculates the distance between two given TCP vectors.
     *
     * @param tcp1 The first TCP vector
     * @param tcp2 The second TCP vector
     * @return The distance between given TCPs
     */
    double calculateDistanceBetweenTCPS(VectorXd &tcp1, VectorXd &tcp2);

    /**
     * Calculates the angle error between two given TCP vectors.
     *
     * @param tcp1 The first TCP vector
     * @param tcp2 The second TCP vector
     * @return Sum of absolute errors in RPY<
     */
    double calculateAngleErrorBetweenTCPS(VectorXd &tcp1, VectorXd &tcp2);

    /**
     * Converts the given TCP vector to the corresponding TCP matrix
     *
     * @param tcpVector Vector representation of the TCP
     * @param tcpRotation Matrix represantation of the orientation of the TCP
     * @todo Check if the function is really needed
     */
    void convertTCPVectorToRotationMatrix(VectorXd &tcpVector, Matrix3f &tcpRotation);
};

#endif // KINEMATICSSOLVER_H
