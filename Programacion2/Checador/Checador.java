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
public class Checador {

    private int horaChecar;
    private int MinutoChecar;
    private String dia;
    private int num;
    private String[] semana = {"lunes", "martes", "miercoles", "jueves", "viernes", "sabado", "domingo"};
    private Profesor prof;
    private int año;
    private int mes;
    private int dia1;

    Checador(int Unaño, int Unmes,int Undia1,int Undia, int unaHora, int unMinuto, Profesor Unprofesor) {
        año=Unaño;
        mes=Unmes;
        dia1=Undia1;
        horaChecar = unaHora;
        MinutoChecar = unMinuto;
        prof = Unprofesor;
        num = Undia;
        dia = semana[Undia];
    }
    int obtenAño(){
        return año;
    }
    
    int obtenMes(){
        return mes;
    }
    int obtenDianum(){
        return dia1;
    }

    int Obtennum() {
        return num;
    }

    String Obtendia() {
        return dia;
    }

    int ObtenHora() {
        return horaChecar;
    }

    int ObtenMinuto() {
        return MinutoChecar;
    }

    void Comparar(Profesor a) {
        
        //int Undia, int unaHora, int unMinuto, Profesor Unprofesor
        
        // this.num -> Número del día (0:Lunes ...)
        //this.horaChecar
        //this.MinutoChecar
        //this.prof; ó a
        
        String r = "No tienes clases en este momento.";
        String c = "";
        String d = "";
        String l = "No tienes clase en este momento."+
                "\nFecha y hora: "+obtenAño()+"/"+obtenMes()+"/"+obtenDianum()+" "+Obtendia()+" a las "+ObtenHora()+":"+ObtenMinuto();
        
        int nd = 0;
        int hr = 0;
        for (Materia m : a.Getclases()) {
            c = m.ObtenMateria();
            //System.out.println("Clase: " + c);
            
            for (Horario h : m.gethours()) {
                d = h.obtendia();
                nd = h.obtennum();
                hr = h.obtenhorario();
                
                
                if (this.num == nd) {
                   if(horaChecar+1 == (hr)){
                 if(MinutoChecar >= 45 ){
                    horaChecar = horaChecar+1;
                    l="LLegaste Temprano,Tienes clase a la Siguiente hora de "+c+
                    "\nFecha y hora: " +obtenAño()+"/"+obtenMes()+"/"+obtenDianum()+" "+Obtendia()+" a las "+ObtenHora()+":"+ObtenMinuto();
                    
                }
                } else
               if(horaChecar == (hr)){
                 if(MinutoChecar <= 15 ){
                    hr = hr;
                    l="Tienes clase hoy a esta hora de " +c+
                    "\nFecha y hora: " +obtenAño()+"/"+obtenMes()+"/"+obtenDianum()+" "+Obtendia()+" a las "+ObtenHora()+":"+ObtenMinuto();
                }else{
                     l="LLegaste tarde, Tienes clase hoy a esta hora de "+c
                    +"\nFecha y hora: "+obtenAño()+"/"+obtenMes()+"/"+obtenDianum()+" "+Obtendia()+" a las "+ObtenHora()+":"+ObtenMinuto();
                     
                 }
                }
                   
                  //  r="Tienes clase hoy a esta hora de "+c;
                }
            }            
            //System.out.println(d+" ("+nd+")"+" a las " + hr);
            
            
        }
        
        System.out.println(l);
        

      
    }

}
