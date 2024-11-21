#!/usr/bin/env python
import svgwrite
from math import *
import random

def rotation(point, angle):
    x, y = point
    out = (x*cos(angle)+y*(-sin(angle)), x*sin(angle)+y*cos(angle))
    return out 

def translater(input, vectTrans):
    x,y=input
    tx,ty=vectTrans
    return ((x+tx,y+ty))

def prodMatVect(Mat,Vect):
    x,y=Vect
    ((a11,a12),(a21,a22))=Mat
    x2=a11*x+a12*y
    y2=a21*x+a22*y
    return (x2,y2)

def Matrotation(angle):
    return ((cos(angle), -sin(angle)),(sin(angle), cos(angle)))

def MatDilatation(k):
    return ((k,0),(0,k))

def prodMatMat(MatA,MatB):
    ((a11,a12),(a21,a22))=MatA
    ((B11,B12),(B21,B22))=MatB
    return ((a11*B11+a12*B21,a11*B12+a12*B22),(a21*B11+a22*B21,a21*B12+a22*B22))

def compose(points,triangles):
  colors=("blue","red","green","purple","yellow","white","coral","darkblue")
  for i in range(0,len(triangles)//3):
      dessin.add(dessin.polygon((points[triangles[3*i]],points[triangles[3*i+1]],points[triangles[3*i+2]]), fill=colors[(i%(len(colors)*2))//2],  opacity=0.5,stroke='black'))

def projection(point3d):
    return(point3d[0],point3d[1])

def translation(point, direction):
    x, y, z = point
    dx, dy, dz = direction
    return (x + dx, y + dy, z + dz)

def prodMatVect3D(Mat,Vect):
    x,y,z=Vect
    ((a11,a12,a13),(a21,a22,a23),(a31,a32,a33))=Mat
    x2=a11*x+a12*y+a13*z
    y2=a21*x+a22*y+a23*z
    z2=a31*x+a32*y+a33*z
    return (x2,y2,z2)

def prodMatMat3D(MatA,MatB):
    ((a11,a12,a13),
    (a21,a22,a23),
    (a31,a32,a33))=MatA
    ((b11,b12,b13),
    (b21,b22,b23),
    (b31,b32,b33))=MatB
    return ((a11*b11+a12*b21+a13*b31,a11*b12+a12*b22+a13*b32,a11*b13+a12*b23+a13*b33),
            (a21*b11+a22*b21+a23*b31,a21*b12+a22*b22+a23*b32,a21*b13+a22*b23+a23*b33),
            (a31*b11+a32*b21+a33*b31,a31*b12+a32*b22+a33*b32,a31*b13+a32*b23+a33*b33))

def Matdilatation3D(coefDilatation):
    return ((coefDilatation,0,0),(0,coefDilatation,0),(0,0,coefDilatation))

def Matrotation3DY(angle):
    return (
        (cos(angle), 0,sin(angle)),
        (0,1,0,),
        (-sin(angle),0, cos(angle)))

def Matrotation3DX(angle):
    return (
        (1,0,0),
        (0,cos(angle),-sin(angle)),
        (0,sin(angle),cos(angle)))

def Matrotation3DZ(angle):
    return (
        (cos(angle),-sin(angle),0),
        (sin(angle),cos(angle),0),
        (0,0,1))

def Matrotation3D(angle1,angle2,angle3):
    return prodMatMat3D(Matrotation3DY(angle1),prodMatMat3D(Matrotation3DX(angle2),Matrotation3DZ(angle3)))

def Matrotation3DUnique(angle):
    return Matrotation3D(angle,angle,angle)

dessin  = svgwrite.Drawing('exercice_1.svg', size=(800,600))

# carré
# carre=[(0,0),(0,200),(200,200),(200,0)]
# dessin.add(dessin.polygon(carre, fill='#00FFFF', stroke="#000000", opacity=0.7 ))

# carré déplacé
# carre_trans=[translater(sommet,(200,200)) for sommet in carre]
# dessin.add(dessin.polygon(carre_trans, fill='#FF0000',stroke="#000000", opacity=0.7))

# carré tourné
# carre_rota=[rotation(sommet,pi/4) for sommet in carre]
# dessin.add(dessin.polygon(carre_rota, fill='#00FF00',stroke="#000000", opacity=0.7))

# carrés les uns dans les autres
# for i in range(100):
#     color = "#"+''.join([random.choice('0123456789ABCDEF') for j in range(6)])
#     carre= [prodMatVect(MatDilatation(0.9),sommet) for sommet in carre]
#     carre= [translater(sommet, (10,10)) for sommet in carre]
#     dessin.add(dessin.polygon(carre, fill=color,stroke="#000000", opacity=0.7))

# carrés de plus en plus petits les uns à côté des autres
# forme = [(0,0),(0,200),(200,200),(200,0)]
# for i in range(4):
#     forme = [prodMatVect(MatDilatation(0.5**i),sommet) for sommet in carre]
#     forme = [translater(sommet, (200 + 200*(1-1/2**(i-1)),0)) for sommet in forme]
#     dessin.add(dessin.polygon(forme, fill="#"+''.join([random.choice('0123456789ABCDEF') for j in range(6)]), stroke="#000000", opacity=0.7))

# carrés les uns dans les autres
# forme = [(0,0),(0,200),(200,200),(200,0)]
# for i in range(4):
#     forme_n = [prodMatVect(MatDilatation(0.5**i),sommet) for sommet in forme]
#     forme_n = [translater(sommet, (300 + 50*(1-1/2**(i-1)),300 + 50*(1-1/2**(i-1)))) for sommet in forme_n]
#     dessin.add(dessin.polygon(forme_n, fill="#"+''.join([random.choice('0123456789ABCDEF') for j in range(6)]), stroke="#000000", opacity=0.7))

# carrés qui se décalent en tournant
# forme = [(-50,-50),(-50,50),(50,50),(50,-50)]
# for i in range(50):
#     forme_n = [prodMatVect(Matrotation((pi*i)/12),sommet) for sommet in forme]
#     forme_n = [translater(sommet, (25*i + 50, 100)) for sommet in forme_n]
#     dessin.add(dessin.polygon(forme_n, fill="#"+''.join([random.choice('0123456789ABCDEF') for j in range(6)]), stroke="#000000", opacity=0.7))

# carrés qui se décalent en tournant et se rétrécissent
# forme = [(-50,-50),(-50,50),(50,50),(50,-50)]
# for i in range(50):
#     forme_n = [prodMatVect(Matrotation((pi*i)/12),sommet) for sommet in forme]
#     forme_n = [prodMatVect(MatDilatation(0.9**i),sommet) for sommet in forme_n]
#     forme_n = [translater(sommet, (50*i + 50, 100)) for sommet in forme_n]
#     dessin.add(dessin.polygon(forme_n, fill="#"+''.join([random.choice('0123456789ABCDEF') for j in range(6)]), stroke="#000000", opacity=0.7))

# dessiner un carré à partir de triangles
# aux=100
# points=[(aux, aux),(-aux, aux),(-aux, -aux),(aux, -aux)]
# triangles=[0,1,2,0,2,3]

# i=0
# dessin.add(dessin.polygon((points[triangles[3*i]],points[triangles[3*i+1]],points[triangles[3*i+2]]), fill='blue',  opacity=0.5,stroke='black'))
# i=1
# dessin.add(dessin.polygon((points[triangles[3*i]],points[triangles[3*i+1]],points[triangles[3*i+2]]), fill='blue',  opacity=0.5,stroke='black'))

# # faire tourner, grandir et translater les points
# points_fin=[rotation(point,pi/4) for point in points]
# points_fin=[prodMatVect(MatDilatation(1.5),point) for point in points_fin]
# points_fin=[translater(point,(300,300)) for point in points_fin]
# i=0
# dessin.add(dessin.polygon((points_fin[triangles[3*i]],points_fin[triangles[3*i+1]],points_fin[triangles[3*i+2]]), fill='red',  opacity=0.5,stroke='black'))
# i=1
# dessin.add(dessin.polygon((points_fin[triangles[3*i]],points_fin[triangles[3*i+1]],points_fin[triangles[3*i+2]]), fill='red',  opacity=0.5,stroke='black'))

# carré
# compose([(100,100),(-100,100),(-100,-100),(100,-100)],[0,1,2,0,2,3])

# chat
# points_chat = [(-100,0),(100,0),(0,50),(-100,-70),(-50,0),(0,-30),(50,0),(100,-70)]
# triangles_chat = [0,1,2,0,3,4,4,5,6,6,7,1]

# compose(points_chat,triangles_chat)

# faire tourner, grandir et translater les points
# points_chat_fin=[rotation(point,pi/4) for point in points_chat]
# points_chat_fin=[prodMatVect(MatDilatation(1.5),point) for point in points_chat_fin]
# points_chat_fin=[translater(point,(300,300)) for point in points_chat_fin]
# compose(points_chat_fin,triangles_chat)

# faire tourner, grandir et translater plusieurs fois les points
# for i in range(5):
#     points_chat_n=[rotation(point,(pi*i)/4) for point in points_chat]
#     points_chat_n=[prodMatVect(MatDilatation(0.9**i),point) for point in points_chat_n]
#     points_chat_n=[translater(point,(150*i+100,100)) for point in points_chat_n]
#     compose(points_chat_n,triangles_chat)

# cube à 6 faces
aux=100
points=[[-aux, -aux, aux], #point 0 (face devant)
        [-aux, aux, aux],#point 1   (face devant)
        [aux, aux, aux],#point 2    (face devant)
        [aux, -aux, aux],#point 3   (face devant)
        [-aux, -aux, -aux],#point 4 (face arrière)
        [-aux, aux, -aux],#point 5   (face arrière)
        [aux, aux, -aux],#point 6    (face arrière)
        [aux, -aux, -aux]]#point 7   (face arrière)

cube=[0,1,2,   #triangle 1 face 1 (devant)
    0,2,3,     #triangle 2 face 1
    4,5,6,     #triangle 1 face 2 (arriere)
    4,6,7,     #triangle 2 face 2
    0,1,5,     #triangle 1 face 3 (gauche)
    0,5,4,     #triangle 2 face 3
    3,2,6,     #triangle 1 face 4 (droite)
    3,6,7,     #triangle 2 face 4
    0,3,7,     #triangle 1 face 5 (dessus)
    0,7,4,     #triangle 2 face 5
    1,2,6,     #triangle 1 face 6 (dessous)
    1,6,5]     #triangle 2 face 6

triangles=[0,1,2,0,2,3]

# points_proj = [ projection(sommet) for sommet in points ]
# compose(points_proj,triangles)

# translater le cube
# points_trans = [ translation(sommet, (200,200,0)) for sommet in points ]
# points_proj = [ projection(sommet) for sommet in points_trans ]
# compose(points_proj,triangles)

# faire grandir et translater les points en 3D
# points_dil = [prodMatVect3D(Matdilatation3D(2),sommet) for sommet in points]
# points_dil = [translation(sommet, (200,200,0)) for sommet in points_dil]
# points_proj = [ projection(sommet) for sommet in points_dil ]
# compose(points_proj,cube)

# faire tourner, grandir et translater les points en 3D
# points_rot = [prodMatVect3D(Matrotation3DY(pi/4),sommet) for sommet in points]
# points_rot = [prodMatVect3D(Matrotation3DX(pi/4),sommet) for sommet in points_rot]
# points_rot = [prodMatVect3D(Matrotation3DZ(pi/4),sommet) for sommet in points_rot]
# points_rot = [prodMatVect3D(Matdilatation3D(1.5),sommet) for sommet in points_rot]
# points_rot = [translation(sommet, (300,300,0)) for sommet in points_rot]
# points_proj = [ projection(sommet) for sommet in points_rot ]
# compose(points_proj,cube)

# faire tourner, grandir et translater plusieurs fois les points en 3D
points = [prodMatVect3D(Matrotation3D(pi/24,pi/24,0),sommet) for sommet in points]
for i in range(10):
    points_rot = [prodMatVect3D(Matrotation3DUnique((pi*i)/12),sommet) for sommet in points]
    points_rot = [prodMatVect3D(Matdilatation3D(0.8**i),sommet) for sommet in points_rot]
    points_rot = [translation(sommet, (75*i+100,200,0)) for sommet in points_rot]
    points_proj = [ projection(sommet) for sommet in points_rot ]
    compose(points_proj,cube)

dessin.save()
