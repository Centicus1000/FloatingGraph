#ifndef vml_mat4_h
#define vml_mat4_h

#include "basics.h"
#include "vec3.h"
#include "vec4.h"

namespace vml {

/**
 * @brief 4x4 Matrix.
 *
 * Mat4 ist eine Implementierung einer 4x4 Matrix.
 * Die Matrix kann affine Transformationen (Rotation, Verschiebung, Skalierung, ect) im dreidimensionalen Raum beschrieben.
 * Sie eignet sich zum Verwenden mit OpenGL.
 * Intern ist sind die Einträge als eine c-Style array gespeichert.
 * @Todo: matmul, transpose, det
 */
struct mat4
{
    /// Anzahl der Vec4-Vektor pro Matrix, bzw. Anzahl der Reihen oder Spalten
    static const int v_size {  4 };
    /// Anzahl der float-Einträge in der Matrix =  4*4
    static const int f_size { 16 };
    
    /// Interner Datenspeicher der Matrix: c-Style array
    float M[f_size];
    
    // Konstruktoren
    mat4(const vec4&, const vec4&, const vec4&, const vec4&);
    mat4(float);
    mat4();
    
    // Zugang zu Einträgen
    float* data();
    float& operator[] (int i);
    const float& operator[] (int i) const;
    float& at(int, int);
    float at(int, int) const;
    vec4 row(int i) const;
    vec4 col(int i) const;
    
    // Methoden
    void transpose();
    float det();
    
    // printing
    friend std::ostream& operator << (std::ostream& os, const mat4& m);
};

// ----------------------------------------------
// Namespace Methoden

mat4 lookat(const vec3&, const vec3&, const vec3&);
mat4 ortho(float left, float right, float bottom, float top, float nearVal, float farVal);

} /* vml */
#endif /* vml_mat4_h */