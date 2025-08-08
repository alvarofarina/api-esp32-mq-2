package com.alvaro.apiesp32.Servicios;

import com.alvaro.apiesp32.Entidades.Dato;
import com.alvaro.apiesp32.Repositorios.DatoRepository;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Optional;

@Service
public class DatoServiceImp implements DatoService {

    private final DatoRepository datoRepository;

    public DatoServiceImp(DatoRepository datoRepository) {
        this.datoRepository = datoRepository;
    }

    @Override
    public Dato save(Dato dato) {
        return datoRepository.save(dato);
    }

    @Override
    public List<Dato> findAll() {
        return datoRepository.findAll();
    }

    @Override
    public Dato findByValor(Float valor) {
        return findByValor(valor);
    }

    @Override
    public Optional<Dato> findById(Integer idDato) {
        return datoRepository.findById(idDato);
    }

    @Override
    public void deleteById(Integer idDato) {
        datoRepository.deleteById(idDato);
    }
}
