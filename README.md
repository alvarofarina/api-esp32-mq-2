Este proyecto es una solución rústica a la problemática de registrar y guardar mediciones de un sensor a una base de datos SQL (en este caso, una base de datos de pruebas H2)
Es un Web Service programado en Java con el Framework Springboot (usa MAVEN), con un patrón de diseño MVC, similar a un CRUD, pero solo con los métodos POST y GET, más adelante le agrego el DELETE si es que pinta
El funcionamiento del proyecto es que se consuma el endpoint en cualquier dispositivo programable, puede ser un PIC (muy poco práctico por la capacidad del microcontrolador), un Arduino, ESP32, etc.

PARA SETEAR EL PROYECTO Y QUE FUNCIONE HAY QUE SEGUIR ESTOS PASOS
1. Descargar el archivo .zip del repositorio, y descomprimirlo
2. En tu IDE de confianza (yo uso IntelliJ IDEA, puede ser VSCODE o lo que se pinte), agregar la carpeta a tu workspace
3. Buildeas el proyecto y te va a tirar unos warnings que no afectan al funcionamiento del proyecto (hasta ahora)
4. Y ahi el Web Service ya estará corriendo de forma local en tu PC en el puerto 8080
5. Para acceder a la base de datos H2, tenes que ingresar en tu navegador a localhost:8080/h2-console
6. Si no te anda, posiblemente tenes que agregar el URL de la DB, la URL podes encontrarlo en el archivo "application.properties", ese lo vas a ver en la carpeta que agregaste a tu IDE, y en donde dice "spring.datasource.url", copias todo lo que esta despues del "=" y lo pegas en donde te pide URL en la consola del H2 (la que ingresaste en tu navegador)
7. el usuario del H2 es "us" y la contraseña es "password", te dice tambien en el application.properties
8. una vez que accediste a la consola, creas la estructura de datos SQL, abajo te dejo un copypaste para ingresar y correrlo en la consola de H2
9.   CREATE TABLE Datos (idDato INT PRIMARY KEY,nombre VARCHAR(255),valor FLOAT, fechaHora TIMESTAMP);
10. Y listo, ya podes empezar a consumir la API   
11. El ENDPOINT a consumir desde tu microcontrolador es "<IP>:8080/MQ-2", y la estructura del JSON es {"\"nombre\":\"Sensor1\","\"valor\": <tu variable medida>}
12. En el archivo de extensión ".ino" está un programa para ESP32 para un sensor de gas MQ-2, de igual manera se puede usar cualquier otro tipo de sensor mientras la variable sea del TIPO FLOAT
13. sal a gusto y a disfrutar

