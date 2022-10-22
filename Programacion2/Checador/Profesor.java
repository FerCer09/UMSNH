/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Checador;


import java.util.ArrayList;

/**
 *
 * @author a1416339f
 */
public class Profesor {
    private String nombre;
    private int matricula;
    private ArrayList <Materia>Lista_Materias;
    
    public Profesor(String unNombre,int unaMatricula){
        nombre = unNombre;
        matricula = unaMatricula; 
        Lista_Materias = new ArrayList <Materia>();
    }
    
    public String Obtennomprofe(){
        return nombre;
    }
    
    public int Obtenmatriculaprofe(){
    return matricula;
}
     public void agregar_materia(Materia unaMateria) {
        Lista_Materias.add(unaMateria);
    }
     
     public String obtenLista_Materias(){
         String r="";
        for (Materia m : Lista_Materias) {
            r = r + m.ObtenMateria()+" Horario: "+ m.ObtenHorarios()+ "\n";
        } 
        return r;
     }
    
    public ArrayList <Materia> Getclases(){
        return Lista_Materias;
        } 
     
     
}
