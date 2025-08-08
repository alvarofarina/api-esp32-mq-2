package com.alvaro.apiesp32.Servicios;

import com.alvaro.apiesp32.Entidades.Dato;

import java.util.List;
import java.util.Optional;

public interface DatoService {
    Dato save(Dato dato);
    List<Dato> findAll();
    Dato findByValor(Float valor);
    Optional<Dato> findById(Integer idDato);
    void deleteById(Integer idDato);
}
