# TSSOO - taller 2

Felipe Guillermo Castro Aguilar - <felipe.castroa@alumnos.uv.cl>

>`Universidad de Valparaíso`

## Introducción

El presente documento esta sujeto y basado en el informe técnico presentado en este repositorio. 
Una vez analizado el proceso de diseño presentado en el informe mencionado, se trabajó a través del lenguaje de programación c++, con el cual manejaremos threads para cumplir con el objetivo del taller.

Como objetivo del taller se solicitó implementar un programa el cual llene un arreglo de números enteros y luego los sume. Estas tareas se deben realizar en forma paralela, implementadas con threads POSIX.

Es destacable mencionar que este documento es una extensión del reporte técnico presentado en este repositorio el cual muestra las directrices del problema, junto con el problema y su descripción, el diseño de solución y resultados.

Es importante mencionar que para la ejecución del código se debe ejecutar con los parámetros necesarios para su correcta implementación. La manera de ejecutar el código es la siguiente:

> ./ sumArray -N **_nro_** -t  **_nro_** 0-l  **_nro_** -L  **_nro_** [-h]
>
>Los parámetros son los siguientes:
>
>-N : tamaño del arreglo.
>
>-t : número de threads.
>
>-l : limite inferior rango aleatorio.
>
>-L : límite superior rango aleatorio.
>
>[-h] : muestra la ayuda de uso y termina. 
>
>Junto con lo anterior se agrego un parámetro no obligatorio al final de la forma de uso mostrada. El parámetro **-v** muestra información adicional la cual valida la suma y la captura de los datos entregados por parámetros.
## Diseño de la solución

Antes de dar inicio con el desarrollo del código generado, debemos entender que el diseño se desprende del informe técnico dentro del repositorio.
El diseño de la solución se separó en dos grandes módulos los cuales fueron trabajados de manera simultanea a lo largo del desarrollo. Ya que lo solicitado fue la creación de "n" hilos dependiendo de los parámetros de entrada, se creo un ciclo el cual creaba los hilos y otro encargado de inicializarlo. Este proceso se realizo para cada módulo.
A continuación se explicará de modo resumen como se implementaron los módulos.

### Módulo uno.

Para este primer módulo se creo un arreglo el cual almacena los datos aleatorios creados mediante una función. Este arreglo será la base para llenar cada uno de los arreglos de manera paralela, con threads, o de manera secuencial. Luego en la etapa paralela se crearon tantos threads como los solicitados por parámetros y estos llenan un arreglo base **Array**, a través de una función **Llenado**, dividiéndole y almacenando los datos desde el arreglo de datos aleatorios.
Una vez llenado el arreglo base de manera paralela se continuo con la siguiente etapa, el llenado secuencial el cual solo se necesitó un _ciclo for_ para este.

### Módulo dos.

En este segundo módulo se trabajo con el arreglo base mencionado y para el caso paralelo se creo una nueva función la cual es la encargada de sumar las posiciones que le corresponden a cada thread creado. La suma parcial de cada thread es almacenada en un arreglo de tamaño fijo para luego sumar posición por posición y dar como resultado la suma esperada. Explicado de mejor manera, en el arreglo final se suman las sumas obtenidas por cada thread y esto genera la suma esperada.
Para el apartado del secuencial este fue sumando posición por posición del arreglo correspondiente al secuencial y de esta manera obtener la suma total. 
Es importante recalcar que en un inicio el tiempo de suma de la etapa paralela es mayor a la de secuencial pero esto se explica, ya que conlleva más trabajo la creación de threads y el procesamiento de los datos. Este ejemplo aplica cuando se compara el tiempo entre un solo hilo _vs_ el metodo secuencial.

## Conclusiones.
En cuanto lo abordado anteriormente, es destacable que el uso de hilos en la programación es, en su mayoría, eficiente en temas de rendimiento. En el código presentado se ve reflejado los tiempos de ejecución y procesamiento de hilos _vs_ método secuencial lo cual refleja lo anteriormente escrito.

El diseño aplicado al desarrollo del código fue de gran utilidad, ya que marco un buen inicio para generar dicho código y tener una buena base simplica la en términos de tiempo a la hora de la siguiente iteración. 

De manera de comentario, es claro que el código puede presentar mejoras claras al ocupar una forma distinta de consolidación de los datos a la hora de trabajar con hilos y un buen manejo de vectores como de arreglos. 