package com.alvaro.apiesp32.Controladores;

import com.alvaro.apiesp32.Entidades.Dato;
import com.alvaro.apiesp32.Servicios.DatoService;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping("/MQ-2")
public class DatoController {
    private final DatoService datoService;
    public DatoController(DatoService datoService) {
        this.datoService = datoService;
    }
    @PostMapping
    public Dato insertarDato(@RequestBody Dato dato){
        return datoService.save(dato);
    }
    @GetMapping("/valor/{valor}")
    public Dato obtenerDato(@PathVariable Float valor){
        return datoService.findByValor(valor);
    }
}
