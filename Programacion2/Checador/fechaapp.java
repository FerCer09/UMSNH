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
 * @author a1416339f
 */
public class fechaapp {
    public static void main(String[] args) throws FileNotFoundException, IOException {
        String archivo= "/home/fernando/fecha.txt";
        String cadena;
        FileReader f = new  FileReader(archivo);
        BufferedReader b = new BufferedReader(f);
        while ((cadena = b.readLine())!= null) {
            
            String cad []= cadena.split("-"); //divide una cadena por el "-", split desmenusa una cadena
            
            /*
            char anio[]= new char[4];
            cadena.getChars(0, 4, anio, 0); // es indice +1 = 4 por 2018
             
            char mes[]= new char[2];
            cadena.getChars(5, 7, mes, 0); 
             
            char dia[]= new char[2];
            cadena.getChars(8, 10, dia, 0); 
            */
            //System.out.println(dia);
           // System.out.println(Integer.parseInt(cad[0]));
           Fecha f1 = new Fecha(Integer.parseInt(cad[2]),Integer.parseInt(cad[1]), Integer.parseInt(cad[0]));
            System.out.println(f1.getAño()+"-"+f1.getMes()+"-"+f1.getDia());
        }
        
    
    }
}
