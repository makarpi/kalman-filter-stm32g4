/*
 * matrix.c
 *
 *  Created on: 7 paŸ 2014
 *      Author: Gandalf
 */

#include "matrix.h"

void matrix_2x2_mul_2x1(float * in1, float * in2, float * out)
{
   out[0] = in1[0] * in2[0] + in1[1] * in2[1];
   out[1] = in1[2] * in2[0] + in1[3] * in2[1];
}

void matrix_2x1_mul_1x1(float * in1, float * in2, float * out)
{
   out[0] = in1[0] * in2[0];
   out[1] = in1[1] * in2[0];
}

void matrix_2x1_add_2x1(float * in1, float * in2, float * out)
{
   out[0] = in1[0] + in2[0];
   out[1] = in1[1] + in2[1];
}

void matrix_2x2_mul_2x2(float * in1, float * in2, float * out)
{
   out[0] = in1[0] * in2[0] + in1[1] * in2[2];
   out[1] = in1[0] * in2[1] + in1[1] * in2[3];
   out[2] = in1[2] * in2[0] + in1[3] * in2[2];
   out[3] = in1[2] * in2[1] + in1[3] * in2[3];
}

void matrix_2x2_add_2x2(float * in1, float * in2, float * out)
{
   out[0] = in1[0] + in2[0];
   out[1] = in1[1] + in2[1];
   out[2] = in1[2] + in2[2];
   out[3] = in1[3] + in2[3];
}

void matrix_1x2_mul_2x1(float * in1, float * in2, float * out)
{
   out[0] = in1[0] * in2[0] + in1[1] * in2[1];
}

void matrix_1x2_mul_2x2(float * in1, float * in2, float * out)
{
   out[0] = in1[0] * in2[0] + in1[1] * in2[2];
   out[1] = in1[0] * in2[1] + in1[1] * in2[3];
}

void matrix_2x1_mul_1x2(float * in1, float * in2, float * out)
{
   out[0] = in1[0] * in2[0];
   out[1] = in1[0] * in2[1];
   out[2] = in1[1] * in2[0];
   out[3] = in1[1] * in2[1];
}

void matrix_2x2_sub_2x2(float * in1, float * in2, float * out)
{
   out[0] = in1[0] - in2[0];
   out[1] = in1[1] - in2[1];
   out[2] = in1[2] - in2[2];
   out[3] = in1[3] - in2[3];
}

void matrix_2x2_trans(float * in, float * out)
{
   out[0] = in[0];
   out[1] = in[2];
   out[2] = in[1];
   out[3] = in[3];
}
