<template>
  <div>
    <h1>
      <strong>{{ $t("real_time_data") }}</strong>
    </h1>
    <div v-if="connected">
      <h3>{{ $t("time") }}: {{ time }}</h3>
      <h3>{{ $t("voltage") }}: {{ voltage }}</h3>
      <h3>{{ $t("current") }}: {{ current }}</h3>
      <h3>{{ $t("rpm") }}: {{ rpm }}</h3>
      <h3>{{ $t("distance") }}: {{ distance }}</h3>
      <h3>{{ $t("speed") }}: {{ speed }}</h3>
      <h3>{{ $t("soc") }}: {{ soc }}</h3>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      connected: false, // Propiedad para verificar si el WebSocket está conectado
      time: null,
      voltage: null,
      current: null,
      rpm: null,
      distance: null,
      speed: null,
      soc: null,
      ws: null, // Instancia del WebSocket
    };
  },
  created() {
    this.connectWebSocket();
  },
  methods: {
    connectWebSocket() {
      this.ws = new WebSocket("ws://localhost:8000/ws-status");

      this.ws.onopen = () => {
        console.log("Conexión WebSocket abierta");
        this.connected = true; // Cambia a verdadero cuando se establece la conexión
      };

      this.ws.onmessage = (event) => {
        const parsedData = JSON.parse(event.data);
        console.log("Datos recibidos: ", parsedData);
        this.time = parsedData.Time;
        this.voltage = parsedData.Voltage;
        this.current = parsedData.Current;
        this.rpm = parsedData.RPM;
        this.distance = parsedData.Distance;
        this.speed = parsedData.Velocity;
        this.soc = parsedData.SoC;
      };

      this.ws.onclose = () => {
        console.log("Conexión WebSocket cerrada");
        this.connected = false; // Cambia a falso cuando se pierde la conexión
      };
    },
  },
  beforeUnmount() {
    if (this.ws) {
      this.ws.close(); // Cierra la conexión WebSocket cuando el componente se destruye
    }
  },
};
</script>

<style>
/* Add some basic styling */
</style>
