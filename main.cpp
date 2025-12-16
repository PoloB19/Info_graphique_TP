#include "viewer.h"
#include "triangle.h"
#include "cylinder.h"
#include "node.h"
#include "shader.h"
#include <string>

#ifndef SHADER_DIR
#error "SHADER_DIR not defined"
#endif

int main()
{
    // create window, add shaders & scene objects, then run rendering loop
    Viewer viewer(800, 800);

    // get shader directory
    std::string shader_dir = SHADER_DIR;

    Shader *color_shader = new Shader(shader_dir + "node.vert", shader_dir + "node.frag");

    //Human
    glm::mat4 human_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -7.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 3.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        
    Node* human = new Node(human_mat);
    
    //Tête 
    
    Shape* tete = new Cylinder(color_shader, 0.2, 0.1, 5000);
    glm::mat4 tete_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -0.3f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Node* tete_node = new Node(tete_matrix);
    tete_node -> add(tete);
    human -> add(tete_node);

    //Torse
    Shape* torse = new Cylinder(color_shader, 0.4, 0.2, 5000);
    glm::mat4 torse_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Node* torse_node = new Node(torse_matrix);
    torse_node -> add(torse);
    human -> add(torse_node);
    
    /* -- Bras droit -- */
    
    //Arrière-bras
    Shape* arriere_bras_droit = new Cylinder(color_shader, 0.15, 0.05, 5000);
    glm::mat4 arriere_bras_droit_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.25f, 0.0f, -0.1f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(-20.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Node* arriere_bras_droit_node = new Node(arriere_bras_droit_matrix);
    arriere_bras_droit_node -> add(arriere_bras_droit);
    human -> add(arriere_bras_droit_node);
    
    
    //Avant-bras
    Shape* avant_bras_droit = new Cylinder(color_shader, 0.2, 0.04, 5000);
    glm::mat4 avant_bras_droit_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.15f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Node* avant_bras_droit_node = new Node(avant_bras_droit_matrix);
    avant_bras_droit_node -> add(avant_bras_droit);
    arriere_bras_droit_node -> add(avant_bras_droit_node);
     
    
    /* -- Bras gauche-- */

    //Arrière-bras
    Shape* arriere_bras_gauche = new Cylinder(color_shader, 0.15, 0.05, 5000);
    glm::mat4 arriere_bras_gauche_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, 0.0f, -0.1f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(-20.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Node* arriere_bras_gauche_node = new Node(arriere_bras_gauche_matrix);
    arriere_bras_gauche_node -> add(arriere_bras_gauche);
    human -> add(arriere_bras_gauche_node);
    
    //Avant-bras
    Shape* avant_bras_gauche = new Cylinder(color_shader, 0.2, 0.04, 5000);
    glm::mat4 avant_bras_gauche_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.15f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Node* avant_bras_gauche_node = new Node(avant_bras_gauche_matrix);
    avant_bras_gauche_node -> add(avant_bras_gauche);
    arriere_bras_gauche_node -> add(avant_bras_gauche_node);
    
    
    /* -- Jambe droite -- */
    
    //Arrière-jambe
    Shape* arriere_jambe_droite = new Cylinder(color_shader, 0.2, 0.07, 5000);
    glm::mat4 arriere_jambe_droite_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.1f, 0.0f, 0.3f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Node* arriere_jambe_droite_node = new Node(arriere_jambe_droite_matrix);
    arriere_jambe_droite_node -> add(arriere_jambe_droite);
    human -> add(arriere_jambe_droite_node);
    
    //Avant-jambe
    Shape* avant_jambe_droite = new Cylinder(color_shader, 0.2, 0.06, 5000);
    glm::mat4 avant_jambe_droite_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.2f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Node* avant_jambe_droite_node = new Node(avant_jambe_droite_matrix);
    avant_jambe_droite_node -> add(avant_jambe_droite);
    arriere_jambe_droite_node -> add(avant_jambe_droite_node);
    
    
    /* -- Jambe gauche -- */
    
    //Arrière-jambe
    Shape* arriere_jambe_gauche = new Cylinder(color_shader, 0.2, 0.07, 5000);
    glm::mat4 arriere_jambe_gauche_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.1f, 0.0f, 0.3f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Node* arriere_jambe_gauche_node = new Node(arriere_jambe_gauche_matrix);
    arriere_jambe_gauche_node -> add(arriere_jambe_gauche);
    human -> add(arriere_jambe_gauche_node);
    
    //Avant-jambe
    Shape* avant_jambe_gauche = new Cylinder(color_shader, 0.2, 0.06, 5000);
    glm::mat4 avant_jambe_gauche_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.2f))
        * glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f))
        * glm::rotate(glm::mat4(1.0f), glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));

    Node* avant_jambe_gauche_node = new Node(avant_jambe_gauche_matrix);
    avant_jambe_gauche_node -> add(avant_jambe_gauche);
    arriere_jambe_gauche_node -> add(avant_jambe_gauche_node);
    
    
    //Affichage
    viewer.scene_root->add(human);

    //Animation
    viewer.animation_loop = [&](float t) {
        
        float speed = 5.0f; // Vitesse de la marche
        float angle = 30.0f; // Amplitude du balancement en degrés

        // Calcul du balancement
        float swing = glm::radians(sin(t * speed) * angle);
        
        // Vitesse de rotation sur lui-même
        float vitesse_rotation = 0.5f;

        // --- ROTATION GLOBALE DE L'HUMAIN ---
        
        //On reconstruit la matrice complète de l'humain à chaque image car c'est + simple
        glm::mat4 global_human_mat = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -7.0f))
             * glm::rotate(glm::mat4(1.0f), t * vitesse_rotation, glm::vec3(0.0f, 1.0f, 0.0f))
             * glm::scale(glm::mat4(1.0f), glm::vec3(3.0f, 3.0f, 3.0f))
             * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

        human->set_matrix(global_human_mat);

        // --- BRAS DROIT ---
        glm::mat4 anim_bras_d = glm::translate(glm::mat4(1.0f), glm::vec3(-0.25f, 0.0f, -0.1f)) 
                              * glm::rotate(glm::mat4(1.0f), glm::radians(-20.0f) + swing, glm::vec3(1.0f, 0.0f, 0.0f));
        arriere_bras_droit_node->set_matrix(anim_bras_d);

        // --- BRAS GAUCHE (opposé au bras droit, on inverse le signe du swing) ---
        glm::mat4 anim_bras_g = glm::translate(glm::mat4(1.0f), glm::vec3(0.25f, 0.0f, -0.1f)) 
                              * glm::rotate(glm::mat4(1.0f), glm::radians(-20.0f) - swing, glm::vec3(1.0f, 0.0f, 0.0f));
        arriere_bras_gauche_node->set_matrix(anim_bras_g);

        // --- JAMBE DROITE (Bouge comme le bras droite donc swing) ---
        glm::mat4 anim_jambe_d = glm::translate(glm::mat4(1.0f), glm::vec3(-0.1f, 0.0f, 0.3f))
                               * glm::rotate(glm::mat4(1.0f), + swing, glm::vec3(1.0f, 0.0f, 0.0f));
        arriere_jambe_droite_node->set_matrix(anim_jambe_d);

        // --- JAMBE GAUCHE (Bouge comme le bras droit donc - swing) ---
        glm::mat4 anim_jambe_g = glm::translate(glm::mat4(1.0f), glm::vec3(0.1f, 0.0f, 0.3f))
                               * glm::rotate(glm::mat4(1.0f), - swing, glm::vec3(1.0f, 0.0f, 0.0f));
        arriere_jambe_gauche_node->set_matrix(anim_jambe_g);
    };

    viewer.run();
}