#include "pyramid.h"

#include <iostream>
#include <cstddef>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

struct Vertex {
    glm::vec3 position;
    glm::vec3 color;
};

Pyramid::Pyramid(Shader *shader_program) : shader_program_(shader_program->get_id()) {

    std::vector<Vertex> vertices = {
        // 0: Sommet (Haut) -> ROUGE VIF
    { { 0.0f,  0.5f,  0.0f},   {1.0f, 0.0f, 0.0f} }, 

    // 1: Base Avant Gauche -> VERT
    { {-0.5f, -0.5f,  0.5f},   {0.0f, 1.0f, 0.0f} },

    // 2: Base Avant Droite -> BLEU
    { { 0.5f, -0.5f,  0.5f},   {0.0f, 0.0f, 1.0f} },

    // 3: Base Arrière Droite -> JAUNE (Mix Rouge+Vert)
    { { 0.5f, -0.5f, -0.5f},   {1.0f, 1.0f, 0.0f} },

    // 4: Base Arrière Gauche -> CYAN (Mix Vert+Bleu)
    { {-0.5f, -0.5f, -0.5f},   {0.0f, 1.0f, 1.0f} }
        
    };
    
    GLint indices[] = {
        // Faces latérales (4 triangles)
        0, 1, 2, // Avant
        0, 2, 3, // Droite
        0, 3, 4, // Arrière
        0, 4, 1, // Gauche
        
        // Base (2 triangles formant le carré)
        1, 4, 3, // Base T1
        1, 3, 2  // Base T2 
    };
    
    //Initialisation du VAO, création des Buffers (VBO et IBO, que l'on appelera buffer)
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(2, &buffer[0]);

    // Lie (VBO) au point GL_ARRAY_BUFFER et y copie les données de position/couleur des sommets.
    glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    //Pour la position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),(void*)offsetof(Vertex, position));             

    //Pour la couleur
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    // Lie (IBO) au point GL_ELEMENT_ARRAY_BUFFER et y copie les indices de dessin.
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer[1]); // Utiliser buffer[1] pour l'IBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
}

Pyramid::~Pyramid() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(2, &buffer[0]);
}

void Pyramid::draw() {
    glUseProgram( this->shader_program_ );
    glBindVertexArray( VAO );

    //Translation, définit une matrice de déplacement pour éloigner l'objet sur l'axe Z.
    glm::vec3 pos = glm::vec3(0.0f, 0.0f, -3.0f);
    glm::mat4 translation = glm::translate(glm::mat4(1.0f), pos);

    //Rotation, définit une matrice de rotation autour de l'axe Y, utilisant le temps pour une rotation continue.
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f),
                                    (float) glm::radians(glfwGetTime() * 50.0f),
                                    glm::vec3(0, 1, 0));

    //Scale, définit une matrice de mise à l'échelle (ici, mise à l'échelle neutre car 1.0f).
    glm::mat4 scale = glm::scale(glm::mat4(1.0f),
                             glm::vec3(1.0f, 1.0f, 1.0f));

    //Calcule la matrice 'view' de transformation en combinant translation, rotation et scale
    glm::mat4 view = translation * rotation * scale;
    
    //Calcule la matrice de projection qui définit l'effet de perspective (champ de vision 45°, ratio 800/600).
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    //Récupère l'emplacement de la variable 'view' dans le shader et envoie les données de la matrice 'view'.
    GLint viewloc = glGetUniformLocation(this->shader_program_, "view");
    glUniformMatrix4fv(viewloc, 1, GL_FALSE, glm::value_ptr(view));

    //Récupère l'emplacement de la variable 'projection' dans le shader et envoie les données de la matrice 'projection'.
    GLint viewproj = glGetUniformLocation(this->shader_program_, "projection");
    glUniformMatrix4fv(viewproj, 1, GL_FALSE, glm::value_ptr(projection));
    
    //Dessine la pyramide en utilisant les 18 indices stockés dans l'IBO (chaque groupe de 3 indices forme un triangle).
    glDrawElements( GL_TRIANGLES, 18, GL_UNSIGNED_INT, 0);
}

void Pyramid::key_handler(int key) {
    return;
}
