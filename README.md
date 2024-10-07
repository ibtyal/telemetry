# ¡Bienvenidos al proyecto de telemetría SIIMA!
Nuestro objetivo es construir un tablero que sirva como recptor y emisor de telemetría en tiempo real de un vehíclo eléctrico prototipo. Aquí encontrarás la documentación técnica sobre el software y hardware utilizados, se estará actualizando la información a medida que se agreguen nuevas funcionalidades ejem, telemetría de varios vehículos al mismo tiempo, se actualice código para hacer la API más robusta o que algún componente se cambie.
## Sobre el proyecto
Este proyecto consiste en caracterizar el desempeño de un vehículo eléctrico prototipo en función de su uso para velocidad o autonomía. Para lo cual se precisa un infraestructura que agrupe arquitectura de software y hardware con el fin de obtener de manera remota datos e información relevante que permita parametrizar las condiciones óptimas de funcionamiento y proponer modificaciones y mejoras en pro de la optimización.

Para la implementación de este proyecto se han seleccionado como varialbes operacionales críticas:
- Estado de carga [%] (SOC).
- Velocidad.
- Aceleración.
- Consumo en batería.
  - Corrient.e
  - Voltaje.

Además, para comparar el rendimiento es necesario conocer:
- RPM del motor.
- Distanciarecorrida.
- tiempo transcurrido.

**Para dar desarrollo al proyecto se precisa de:**
-  [Página web](siima.tech) para mostrar datos en tiempo real.
    - El frontend se ha realizado en [Vue 3](https://vuejs.org/) un framework para [Javascript](https://www.javascript.com/about) por fácil implementación.
      -  Visualización de datos en tiempo real.
      -  Descarga de sesiones.
    - El bancked con [FastAPI](https://fastapi.tiangolo.com/), escrito en [Python](https://www.python.org/about/)
      - Generación y almacenamiento de archivos CSV de cada sesión.
      - Comunicar mediante [Websockets](https://developer.mozilla.org/en-US/docs/Web/API/WebSockets_API) el vehículo y la página web.
      - Cálculo de SoC, mediante librería python especializada
  - Tablero
      - Tarjeta [LilyGo T-Display S3](https://github.com/Xinyuan-LilyGO/T-Display-S3), basada en ESP32 para recibir, procesar, mostrar y enviar la información mediante web.
      - Sensores:
         - [JSY-MK-229](https://www.jsypowermeter.com/jsy-mk-229-single-channel-ac-dc-electric-energy-metering-module-product/#:~:text=Accurate%20measurement%20of%20voltage,), encargado de leer el consumo electrico.
         - Sensor de efecto Hall [KY003](https://infodatasheet.com/ky-003-hall-magnetic-sensor-datasheet.html#:~:text=The%20KY%20003%20Hall%20Magnetic%20Sensor), encargado de calcular las RPM.

## Sobre SIIMA
El Semillero de Investigación en Ingeniería y Mecánica Automotriz (SIIMA), es un grupo interdisciplinario del Programa de Ingeniería Electromecánica adscrito a la Facultad de Ciencias Naturales e Ingenierías de las Unidades Tecnológicas de Santander, que fomentan los espacios académicos extracurricular, el quehacer académico en torno al fortalecimiento del proceso de formación profesional, la cultura en la investigación formativa de los estudiantes, desde una perspectiva de género, teniendo como punto de partida el desarrollo de proyectos de investigación contextualizados con las necesidades del sector automotriz y la academia.

[Instagram](https://www.instagram.com/semillerosiima/?igshid=YmMyMTA2M2Y%3D)
[Facebook](https://www.facebook.com/semilleroSIIMA2019)
[Página web](https://semillerosiima.netlify.app/)
[Spotify](https://open.spotify.com/show/2c8s01dKuKy0oXlhpxSevk?si=5b4215cfc4364aaf)

# Welcome to SIIMA telemetry project!

## English
Go to Spanish 
