# Datalogger Secador de alimentos
## Contenido
En este repositorio encontrará:

* Lista de componente
* Esquematicos / Archivos
  * Archivo PCB para fabribar
  * Archivo de para subir al arduino
  * Archivos del modelo 3D de la caja
* Funcionamiento
* Sonidos
* Errores
* repositorio https://github.com/dparrova/Logger-master 

## Listado de componentes
para el desarrollo del Datalogger se usaron los siguiente modulos

* placa de Arduino Nano
* modulo de RTC
* modulo de Micro SD
* modulo DTH11
* modulo de sensor de temeratura MAX667
* micro SD
* conecotr de RJ45
* cable de dato upt RJ45

## Esquematicos / Archivos
Dendro de la carpeta de Archivos se encuentran los esquematicos, modelos de la caja en archivos STL para la impreción en 3D, tambien los archivo Gerber para la impresión de la placa.

## Funcionamiento
El dispositivo cuenta con alimentación proporcinada por cuatro baterias AA. Almacena datos cada minuto de dos temperaturas, una humedad relativa y la fecha y hora de cada dato. Emite sonidos de como idicador de errores o procesos satisfactorios, se neciende y apaga con el interrutor lateral.

### Crear archivo Datos.csv 
Teniendo la memoria dentro del dispositivo, se verifica que exista el archivo Datos.csv, si no existe, lo crea automaticamente y comienza a guardar datos.

### Procedimiento de apagado/encendido
Apague o encienda el dispositivo con el interruptor ubicado en la parte lateral.

### Procedimdiento de toma de datos
Primero coloque las baterias en el porta baterias. 
Coloque tambien la memoria microSD en la ranura. Esta memoria debe tener en su interior un archivo llamado Datos.csv.
Conecte el cable de datos al dispositivo mediante el conector de red.
Encienda el dispositivo con el interruptor ubicado en la parte lateral.
El dispositivo realizara sonidos (ver la sección de *sonidos*)
Los datos se tomaran cada minuto

### Recolección de datos
Con el dispositivo apagado, retire la memoria microSD del dispositivo, use un adaptador microSD/USB para transferir los datos al computador, haga una copia del archivo Datos.csv a su equipo.

Asegurese de no abrir directamente el archivo que se encuentra en memoria desde Excel o cualquier otro programa que modifque el tipo de archivo.

## Sonidos
Se integra un buzzer para tener una ayuda auditiva para identificar acciones
* Un pitido (cada minuto) : indica que el dispositivo almacenó los datos correctamente, este tiene un intervalo de un minuto
* Dos pitidos (repetitivos) : indica que no encuentra la memora microSD conectada o que hay un error.

### Errores comunes
* Reconoce el archivo Datos.csv pero no guarda información
  * Solución: elimine el archivo y vuelvalo a crear.
* Alacena datos pero con el errores en la fecha
  * Solución : configurar el reloj,
  * Remplace la bateria y compile de nuevo el archivo al arduino.
* En cada reinicio del dispositivo se desconfigura la fecha y hora
  * Cambiar la bateria del RTC, esto se hace abriendo la caja y cambiado la bateria redonda.

   
