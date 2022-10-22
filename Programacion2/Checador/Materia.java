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
public class Materia {
    private String materia;
    private int clave;
    private ArrayList <Horario> horarios;
    
   
    
    public Materia(String unNombre, int unaClave){
        horarios = new ArrayList <Horario>();
        materia = unNombre;
        clave = unaClave;
    }
    
    public void Agregar_Horario(Horario unHorario){
    horarios.add(unHorario);
    }
    public int ObtenClave(){
    return clave;
    }
    public String ObtenMateria(){
    return materia;
    }
    
    public String ObtenHorarios(){
         String r="";
        for (Horario m : horarios) {
            r = r + m.obtenhorario()+" Los dias "+ m.obtendia()+"\n";
        }
        return r;
     }
    
    public ArrayList <Horario> gethours(){
      
        return horarios;
        }
    }
    
   

