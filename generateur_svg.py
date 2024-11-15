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
    return (((cos(angle), -sin(angle)),(sin(angle), cos(angle))))

def MatDilatation(k):
    return ((k,0),(0,k))

def prodMatMat(MatA,MatB):
    ((a11,a12),(a21,a22))=MatA
    ((B11,B12),(B21,B22))=MatB
    return ((a11*B11+a12*B21,a11*B12+a12*B22),(a21*B11+a22*B21,a21*B12+a22*B22))

dessin  = svgwrite.Drawing('exercice_1.svg', size=(800,600))

carre=[(0,0),(0,200),(200,200),(200,0)]

# dessin.add(dessin.polygon(carre, fill='#00FFFF', stroke="#000000", opacity=0.7 ))

# carre_trans=[translater(sommet,(200,200)) for sommet in carre]

# dessin.add(dessin.polygon(carre_trans, fill='#FF0000',stroke="#000000", opacity=0.7))

carre_rota=[rotation(sommet,pi/4) for sommet in carre]

# dessin.add(dessin.polygon(carre_rota, fill='#00FF00',stroke="#000000", opacity=0.7))

for i in range(100):
    color = "#"+''.join([random.choice('0123456789ABCDEF') for j in range(6)])
    carre= [prodMatVect(MatDilatation(0.9),sommet) for sommet in carre]
    carre= [translater(sommet, (10,10)) for sommet in carre]
    dessin.add(dessin.polygon(carre, fill=color,stroke="#000000", opacity=0.7))

# for i in range(4):
#     forme = [prodMatVect(MatDilatation(0.5**i),sommet) for sommet in carre]
#     forme = [translater(sommet, (200 + 200*(1-1/2**(i-1)),0)) for sommet in forme]
#     dessin.add(dessin.polygon(forme, fill="#"+''.join([random.choice('0123456789ABCDEF') for j in range(6)]), stroke="#000000", opacity=0.7))

forme = [(0,0),(0,200),(200,200),(200,0)]
for i in range(4):
    forme_n = [prodMatVect(MatDilatation(0.5**i),sommet) for sommet in forme]
    forme_n = [translater(sommet, (300 + 50*(1-1/2**(i-1)),300 + 50*(1-1/2**(i-1)))) for sommet in forme_n]
    dessin.add(dessin.polygon(forme_n, fill="#"+''.join([random.choice('0123456789ABCDEF') for j in range(6)]), stroke="#000000", opacity=0.7))

dessin.save()
