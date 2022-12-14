#include "raylib.h"
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include "constantes.h"


#define M_PI 3.14159265358979323846

typedef struct Fleche
{                // Structure Fleche
    int etat;    // visible (1) ou non (0)
    int cible;   // cible pas touchée (0), cible touchée (1), a atteint les bords (2)
    float dir_x; // sa direction vers sa cible, en x
    float dir_y; // sa sirection vers sa cible, en y
    Vector2 position;
    Vector2 size;
    Color color;
} Fleche;

Fleche creer_fleche(Vector2 position, Ballon B)
{
    Fleche F;
    F.etat = 1;
    F.cible = 0;
    F.dir_x = B.position.x - position.x;
    F.dir_y = B.position.y - position.y;
    F.position = position;
    F.size = {60, 15};
    F.color = PINK;
    return F;
}

void dessiner_fleche(Fleche &F)
{ // Pour dessiner un ballon, en fonction position rayon et couleur
    if (F.etat == 1)
    {
        Vector2 F_center = {((F.size.x) / 2), ((F.size.y) / 2)};
        Rectangle Rect_F;
        Rect_F.x = F.position.x;
        Rect_F.y = F.position.y;
        Rect_F.height = F.size.y;
        Rect_F.width = F.size.x;
        double angle = atan((F.dir_y) / (F.dir_x));
        double pi = M_PI;
        angle = (angle * 180.) / pi;

        // if (F.dir_x<0 && F.dir_y<0){
        //     angle=angle;
        // }
        // if (F.dir_x > 0 && F.dir_y < 0)
        // {
        //     angle=angle;
        // }
        if (F.dir_x > 0 && F.dir_y > 0)
        {
            angle += 180.;
        }
        if (F.dir_x < 0 && F.dir_y > 0)
        {
            angle += 180.;
        }

        DrawRectanglePro(Rect_F, F_center, angle, F.color);
    }
}

void mouv_fleche(Fleche &F){
    double distance = sqrt(pow(F.dir_x,2) + pow(F.dir_y,2));
    F.position.x += (F.dir_x/distance)*20;
    F.position.y += (F.dir_y/distance)*20;
}

bool check_coll_s_b(Singe S, Ballon B){
    Vector2 S_center = {(S.position.x+(S.taille.x/ 2)), (S.position.y+(S.taille.y/ 2))};

    if (CheckCollisionCircles(S_center, S.range, B.position, B.radius))
    {
        Vector2 S_center = {S.position.x + ((S.taille.x) / 2), S.position.y + ((S.taille.y) / 2)};
        return true;
    }
    return false;
}

Fleche check_coll_b_f(Fleche F, Ballon B){
    Rectangle Rect_F;
    Rect_F.x = F.position.x;
    Rect_F.y = F.position.y;
    Rect_F.height = F.size.y;
    Rect_F.width = F.size.x;

    if (CheckCollisionCircleRec(B.position, B.radius, Rect_F))
    {
        F.etat = 0;
        F.cible = 1;
    }
    if ((F.position.x <= 0) || (F.position.y <= 0) || (F.position.x >= GetScreenWidth()) || (F.position.y >= GetScreenHeight()))
    {
        F.etat = 0;
        F.cible = 2;
    }
    return F;
}
