/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Checador;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

/**
 *
 * @author fernando
 */
public class ChecadorApp {
    public static void main(String[] args) throws FileNotFoundException, IOException {
        Materia A = new Materia("Matematicas", 123);
        Materia B = new Materia("Calculo", 123);
        
        Horario a = new Horario(3, 14);
        Horario b = new Horario(1, 17);
       
        
        A.Agregar_Horario(a);
        B.Agregar_Horario(b);
       
        Profesor a1= new Profesor("Fernando", 123);
        //Profesor a2= new Profesor("Alejandro",234);
        
       a1.agregar_materia(B);
       a1.agregar_materia(A);
        
        
        //System.out.println(a1.obtenLista_Materias());
        
        
             /*                   //(año,me,d1,d,h,m,profe)
        Checador l = new Checador(2018,2,3,3,1,45, a1);
        l.Comparar(a1);
        */
        
        
        String archivo= "/home/usuarios/a1416339f/Escritorio/fecha.txt";
        String cadena;
        
         FileReader f = new  FileReader(archivo);
        BufferedReader s = new BufferedReader(f);
        while ((cadena = s.readLine())!= null) {
            
            String cad []= cadena.split("-");
           Fecha1 f1 = new Fecha1(Integer.parseInt(cad[2]),Integer.parseInt(cad[1]), Integer.parseInt(cad[0]));
          //  System.out.println(f1.getAño()+"-"+f1.getMes()+"-"+f1.getDia());
          
                                   //(año,me,d1numerodelmes,dporsemana,h,m,profe)
        Checador m = new Checador(f1.getAño(),f1.getMes(),f1.getDia(),f1.getDianum(),Integer.parseInt(cad[3]),Integer.parseInt(cad[4]), a1);
        m.Comparar(a1);
            System.out.println("");
        }
       

        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
      
        
    }
}