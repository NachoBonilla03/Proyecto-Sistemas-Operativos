# Sistema de Monitoreo del sistema 

# Estudiantes
* Ignacio Bonilla Rojas
* Marcos Vasquez Díaz 

# Funcionalidades del programa 
* Porcentaje de utilización del CPU 
* Proceso con mayor porcentaje de utilizacion del CPU en los ultimos 5 minutos 
* Porcentaje de memoria virtual de todos los procesos
* Porcentaje de memoria real de todos los procesos
* Porcentaje de memoria virtual de un proceso especifico
* Porcentaje real de memoria de un proceso especifcio
* Porcentaje libre del disco duro 
* Porcenajte utilizado del disco duro

# Manual de uso
Para poder comenzar a utilizar el sistema de monitoreo, ejecute el comando make 
Posterior a esto ejecute el comando ./main con alguna de las siguientes opciones: 

* Monitoreo de CPU
  - Ingrese "./main  -C cpu" para mostrar el porcentaje de utilizacion del CPU.
  - Ingrese "./main -C cpu <PID>" para mostrar el porcentaje de utilizacion de CPU de un determinado  proceso en los proximos 5 mins

* Monitoreo de RAM
  - Ingrese "./main -R -MR" para mostrar el porcentaje de uso de memoria real de todos los procesos en el sistema
  - Ingrese "./main -R -MV" para mostrar el porccentaje de uso de memoria virtual de todos los procesos en el sistema 
  - Ingrese "./main -R -MR <PID>" para mostrar el porcentaje de uso de memoria real de un proceso determinado
  - Ingrese "./main -R -MV <PID>" para mostrar el porcentaje de uso de memoria virtual  de un proceso determinado

* Monitoreo de Disco
  - Ingrese "./main -D -U" para mostrar el porcentaje de disco en uso 
  - Ingrese "./main -D -L" para mostrar el porcentaje de disco disponible 
