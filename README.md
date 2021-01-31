
# Manual de usuario
**Autor:** *David Camuñas*  

La compilación y ejecución se realiza de forma automática con el uso de la herramienta Makefile.


## Creación de directorios necesarios
Con este comando se crearan el directorio que contiene los ejecutables.  
***$ make dirs***  


## Limpieza de directorios
Este comando se ha utilizado para limpiar los directorios en los que se almacenan los ejecutables (explicada anteriormente su creación).

* *Nota:* Es de muy buena ayuda a la hora de ejecutar la practica en distintos computadores, debido a que como bien es sabido, no se pueden ejecutar un fichero que ha sido compilado en un ordenador, en otro distinto. Esto se debe a que cada ordenador tiene un juego de instrucciones distinto.

***$ make clean***


## Compilación
El proceso de compilación, se puede realizar de varias formas:  
***$ make compile***

* Otra opción es la de crear los directorios requeridos y compilar los programas a la vez, para ello se utilizara:   
    ***$ make all***
    
El formato de compilación utilizado es el siguiente:  
**g++ src/gpg-cracker.cpp -o exec/gpg-cracker -I include/ -pthread -std=c++11** 


## Ejecución
Para la ejecución del programa se puede realizar de varias formas:

***$ exec --len [n] --charset [letters-minus-digits] [name_file_to_descrypt]***
* **exec:** path donde se encuentra el ejecutable (ejemplo: *./exec/gpg-cracker*).
* **--len:** indica la longitud de la clave a probar.
* **--charset:** indica el conjunto de símbolos a probar. Pueden ser:  
    * **letters**: se seleccionará como conjunto de símbolos letras Mayúsculas y minúsculas.  
    Usando **make** (***$ make solution-letters***).

    * **minus:** se seleccionará como conjunto de símbolos unicamente letras minúsculas.  
    Usando **make** (***$ make solution-minus***).

    * **digits:** se seleccionará como conjunto de símbolos unicamente dígitos.  
    Usando **make** (***$ make solution-digits***).
    
* **name_file_to_descrypt:** nombre del fichero a descifrar (path, ejemplo: files/hello.gpg).

***$ exec --charset [name_file_keys] [name_file_to_descrypt]***
* **name_file_keys:** indica el nombre del fichero donde se encuentran las claves a probar (path, ejemplo: files/rockyou.txt).
* **name_file_to_descrypt:** nombre del fichero a descifrar (path, ejemplo: files/hello.gpg).  

Usando **make** (***$ make solution-file***).

***$ exec --len [n] [name_file_to_descrypt]***  
En esta opción, donde no se espécifica el conjunto de símbolos a usar. Probará un conjunto de símbolos alfanumércos.  
Usando **make** (***$ make solution***).


## Información del archivo de prueba (*Hello*)
La contraseña para descifrar el archivo de prueba *hello.gpg* es: **aabc**.  
* Se puede realizar de forma manual introducciendo el comando:  
***$ gpg -d hello.gpg***
* Su cifrado se realizado con la utilización del comando:  
***$ gpg -c hello***
