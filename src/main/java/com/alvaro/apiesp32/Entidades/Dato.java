package com.alvaro.apiesp32.Entidades;

import jakarta.persistence.*;

import java.time.LocalDateTime;
@Entity
public class Dato {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    Integer idDato;
    String nombre;
    Float valor;
    LocalDateTime tiempo;
    @PrePersist
    public void prePersist() {
        this.tiempo = LocalDateTime.now();
    }

    public Dato() {}
    public Dato(Integer idDato, String nombre, Float valor, LocalDateTime tiempo) {
        this.nombre = nombre;
        this.valor = valor;
        this.tiempo = tiempo;
    }

    public Integer getIdDato() {
        return idDato;
    }

    public void setIdDato(Integer idDato) {
        this.idDato = idDato;
    }

    public String getNombre() {
        return nombre;
    }

    public Float getValor() {
        return valor;
    }

    public LocalDateTime getTiempo() {
        return tiempo;
    }

    public void setNombre(String nombre) {
        this.nombre = nombre;
    }

    public void setValor(Float valor) {
        this.valor = valor;
    }

    public void setTiempo(LocalDateTime tiempo) {
        this.tiempo = tiempo;
    }
}
