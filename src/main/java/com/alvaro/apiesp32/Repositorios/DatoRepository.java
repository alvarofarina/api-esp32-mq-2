package com.alvaro.apiesp32.Repositorios;

import com.alvaro.apiesp32.Entidades.Dato;
import org.springframework.data.jpa.repository.JpaRepository;

public interface DatoRepository extends JpaRepository<Dato, Integer> {
}
