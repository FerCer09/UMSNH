/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Checador;

/**
 *
 * @author fernando
 */
public class Horario {
    private int hora;
    private String dia;
    private String []semana = {"lunes","martes","miercoles","jueves","viernes","sabado","domingo"};
    private int num;

    
    public Horario(int unDia,int unaHora){
        dia = semana[unDia];
        hora = unaHora;
        num=unDia;
    }
    
    int obtennum(){
        return num;
    }
    public String obtendia(){
        return dia;
    }
    
    public int obtenhorario(){
    return hora;
// + ":" +minutos +" hasta " + finhora + ":"+ finminutos;
    
    }
   
}
