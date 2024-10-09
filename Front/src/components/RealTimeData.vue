<template>
  <div>
    <h2>{{ $t("real_time_data") }}</h2>
    <div v-if="connected">
      <p>
        <strong>{{ $t("time") }}:</strong> {{ voltage }}
      </p>
      <p>
        <strong>{{ $t("voltage") }}:</strong> {{ voltage }}
      </p>
      <p>
        <strong>{{ $t("current") }}:</strong> {{ current }}
      </p>
      <p>
        <strong>{{ $t("rpm") }}:</strong> {{ rpm }}
      </p>
      <p>
        <strong>{{ $t("distance") }}:</strong> {{ distance }}
      </p>
      <p>
        <strong>{{ $t("speed") }}:</strong> {{ speed }}
      </p>
      <p>
        <strong>{{ $t("soc") }}:</strong> {{ soc }}
      </p>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      data: null, // Aquí se almacenarán los datos en tiempo real
      ws: null, // Instancia del WebSocket
    };
  },
  created() {
    this.connectWebSocket();
  },
  methods: {
    connectWebSocket() {
      this.ws = new WebSocket("ws://localhost:8000/ws-data");

      this.ws.onopen = () => {
        console.log("Conexión WebSocket abierta");
      };

      this.ws.onmessage = (event) => {
        this.data = JSON.parse(event.data); // Recibe los datos en tiempo real
      };

      this.ws.onclose = () => {
        console.log("Conexión WebSocket cerrada");
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
