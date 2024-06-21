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

## Funcionamiento
El dispositivo cuenta con alimentación proporcinada por cuatro baterias AA, almacena datos cada minuto de dos temperaturas, una humedad relativa y la fecha y hora de cada dato. Emite sonidos de como idicador de errores o procesos satisfactorios.

### Crear archivo Datos.csv 
Con el programa Blog de notas y realizar los siguientes pasos:  
* click Archivo
* click Guardar como
* Cambiar la ubicación por la dirección de la memoria microSD
* Cambiar el nombre por *Datos.csv*
* click Guardar

### Configuración de hora
Crear un archivo en la memoria microSD con el nombre fechahora.txt, donde debe colocar el una sola linea la hora deseada respetando el siguiente formato:

Jan 01 2024
01:00:00


El dispositivo, leera la inforamación y configurará el reloj, posteriormente eliminará el archivo. 

### Procedimdiento de toma de datos
Primero coloque las baterias en el porta baterias. 
Coloque tambien la memoria microSD en la ranura. Esta memoria debe tener en su interior un archivo llamado Datos.csv, este archivo se debe crear desde un blog de notas o cualquier generador de texto plano. 
Conecte el cable de datos al dispositivo.
Encienda el dispositivo con el interruptor ubicado en la parte lateral.
El dispositivo realizara sonidos (ver la sección de *sonidos*)

### Procedimiento de apagado
Apague el dispositivo con el interruptor ubicado en la parte lateral.

### Recolección de datos
Con el dispositivo apagado, retire la memoria microSD del dispositivo, use un adaptador microSD/USB para transferir los datos al computador, haga una copia del archivo Datos.csv a su equipo.

Asegurese de no abrir directamente el archivo que se encuentra en memoria desde Excel o cualquier otro programa que modifque el tipo de archivo.

## Sonidos
Se integra un buzzer para tener una ayuda auditiva para identificar acciones
* Un pitido (cada minuto) : indica que el dispositivo almacenó los datos correctamente, este tiene un intervalo de un minuto
* Dos pitidos (ciclicos) : indica que no encuentra la memora microSD conectada o que hay un error.
* Tres pitidos (una sola vez) :  configuración de reloj exitosa.

### Errores
* Reconoce el archivo Datos.csv pero no guarda información
  * Solución: elimine el archivo y vuelvalo a crear (ver sección *Crear archivo Datos.csv*)
* Alacena datos pero con el errores en la fecha
  * Solución : configurar el reloj (ver sección *Configuración de hora*)
* En cada reinicio del dispositivo se desconfigura la fecha y hora
  * Cambiar la bateria del RTC, esto se hace abriendo la caja y cambiado la bateria redonda y despues *Crear archivo Datos.csv*

   
