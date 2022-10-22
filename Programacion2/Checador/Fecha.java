/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Checador;

import java.util.Calendar;

/**
 *
 * @author a1416339f
 */
public class Fecha {

    private int dia;
    private int mes;
    private int año;

    Fecha() {

    }

    public Fecha(int d, int m, int a) {
        dia = d;
        mes = m;
        año = a;
        if (!fechaCorrecta()) {
    Calendar fechaSistema = Calendar.getInstance();
    setDia(fechaSistema.get(Calendar.DAY_OF_MONTH));
    setMes(fechaSistema.get(Calendar.MONTH));
    setAño(fechaSistema.get(Calendar.YEAR));
    }
    }

    /**
     * @return the dia
     */
    public int getDia() {
        return dia;
    }

    /**
     * @param dia the dia to set
     */
    public void setDia(int dia) {
        this.dia = dia;
    }

    /**
     * @return the mes
     */
    public int getMes() {
        return mes;
    }

    /**
     * @param mes the mes to set
     */
    public void setMes(int mes) {
        this.mes = mes;
    }

    /**
     * @return the año
     */
    public int getAño() {
        return año;
    }

    /**
     * @param año the año to set
     */
    public void setAño(int año) {
        this.año = año;
    }

    public boolean fechaCorrecta() {
        boolean diaCorrecto, mesCorrecto, anyoCorrecto;
        anyoCorrecto = (año > 0
        );
        mesCorrecto = (mes >= 1) && (mes <= 12);
        switch (mes) {
            case 2:
                if (esBisiesto()) {
                    diaCorrecto = (dia >= 1 && dia <= 29);
                } else {
                    diaCorrecto = (dia >= 1 && dia <= 28);
                }
                break;
            case 4:
            case 6:
            case 9:
            case 11:
                diaCorrecto = (dia >= 1 && dia <= 30);
                break;
            default:
                diaCorrecto = (dia >= 1 && dia <= 31);
        }
        return diaCorrecto && mesCorrecto && anyoCorrecto;
    }
    private boolean esBisiesto() {
return ((año % 4 == 0) && (año % 100 != 0) || (año % 400 == 0));
}
    
}
