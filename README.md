# TSSOO - taller 2

Felipe Guillermo Castro Aguilar - <felipe.castroa@alumnos.uv.cl>

>`Universidad de Valparaíso`

## Introducción

El presente documento esta sujeto y basado en el informe técnico presentado en este repositorio. 
Una vez analizado el proceso de diseño presentado en el informe mencionado, se trabajó a través del lenguaje de programación c++, con el cual manejaremos threads para cumplir con el objetivo del taller.

Como objetivo del taller se solicitó implementar un programa el cual llenerá un arreglo de números enteros y luego los sume. Estas tareas se deben realizar en forma paralela, implementadas con threads POSIX.

Es destacable mencionar que este documento es una extensión del reporte técnico presentado en este repositorio el cual muestra las directrices del problema, junto con el problema y su descripción, el diseño de solución y resultados.

## Diseño de la solución

Antes de dar inicio con el desarrollo del código generado, debemos entender que el diseño se desprende del informe técnico dentro del repositorio.
El diseño de la solución se separó en dos grandes módulos los cuales fueron trabajados de manera simultanea a lo largo del desarrollo. Ya que lo solicitado fue la creación de "n" hilos dependiendo de los parametros de entraada se creo un ciclo el creaba los hilos y otro encargado de inicializarlo. Este proceso se realizo para cada módulo.
A continuación se explicará de modo resumen como se implenmentaron los modulos.

### Módulo uno.

Para este primer módulo se creo un arreglo el cual almacena los datos randomicos creados. Este arreglo será la base para llenar cada uno de los arreglos de manera paralela, con threads, o de manera secuencial.
 