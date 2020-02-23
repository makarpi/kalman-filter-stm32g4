/*
 * matrix.h
 *
 *  Created on: 7 paü 2014
 *      Author: Gandalf
 */


#ifndef LIB_DSP_MATRIX_H_
#define LIB_DSP_MATRIX_H_


void matrix_2x2_mul_2x1(float * in1, float * in2, float * out);
void matrix_2x1_mul_1x1(float * in1, float * in2, float * out);
void matrix_2x1_add_2x1(float * in1, float * in2, float * out);
void matrix_2x2_mul_2x2(float * in1, float * in2, float * out);
void matrix_2x2_add_2x2(float * in1, float * in2, float * out);
void matrix_1x2_mul_2x1(float * in1, float * in2, float * out);
void matrix_1x2_mul_2x2(float * in1, float * in2, float * out);
void matrix_2x1_mul_1x2(float * in1, float * in2, float * out);
void matrix_2x2_sub_2x2(float * in1, float * in2, float * out);
void matrix_2x2_trans(float * in, float * out);



#endif /* LIB_DSP_MATRIX_H_ */
