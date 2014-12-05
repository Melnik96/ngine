#ifndef __MATRIX_H__
#define __MATRIX_H__

typedef union mat3 {
  float m[3][3];
  float _m[9];
} mat3;

typedef union mat4 {
  float m[4][4];
  float _m[16];
} mat4;

void mat4_identity(mat4* pMat);

void mat4_mul(mat4* _f, mat4* _s);
void mat4_mul_of(mat4* _mat, mat4* _f, mat4* _s);

void mat_perspective(float fov, float aspect, float near, float far, float* mret);
// void mat4_rot(mat4* m, float x, float y, float z);

// primt matrix
//     int row, columns;
//     for (int row=0; row<4; row++) {
//       for(int columns=0; columns<4; columns++)
//         printf("%f     ", _sc_node->matrix.m[row][columns]);
//       
//       printf("\n");
//     }

#endif
