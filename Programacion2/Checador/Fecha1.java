/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package Checador;

import java.time.ZoneId;
import java.util.Calendar;
import static java.util.Calendar.DATE;
import static java.util.Calendar.MONTH;
import static java.util.Calendar.YEAR;
import java.util.Locale;
import java.util.TimeZone;

/**
 *
 * @author fernando
 */
public class Fecha1 {

    private int dia;
    private int mes;
    private int año;
    private int dianum;
    private String[] semana = {"lunes", "martes", "miercoles", "jueves", "viernes", "sabado", "domingo"};
    private String dialet;
    

    public Fecha1(int d, int m, int a) {
        dia = d;
        mes = m;
        año = a;
        dianum=0;
      /*dianum = nd;
        dialet = semana[nd];
         public final void set(int year, int month, int date)
    {
        set(YEAR, year);
        set(MONTH, month);
        set(DATE, date);
    }*/
         Calendar fecha = Calendar.getInstance();
                 
        fecha.set(año, mes, dia);
        
        setDianum(fecha.get(Calendar.DAY_OF_WEEK_IN_MONTH));
        //System.out.println(dianum); 
        dialet = semana[dianum];
        //System.out.println(dialet);
        if (!fechaCorrecta()) {
    Calendar fechaSistema = Calendar.getInstance();
    setDianum(fechaSistema.get(Calendar.DAY_OF_WEEK_IN_MONTH));
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
        boolean diaCorrecto, mesCorrecto, anyoCorrecto,dianumCorrecto;
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

        /**
         * @param dialet the dialet to set
         */
        public void setDialet(String dialet) {
            this.dialet = dialet;
        }

        /**
         * @return the dianum
         */
        public int getDianum() {
            return dianum;
        }

        /**
         * @param dianum the dianum to set
         */
        public void setDianum(int dianum) {
            this.dianum = dianum;
        }

    /**
     * @return the dialet
     */
    public String getDialet() {
        return dialet;
    }
    
}
