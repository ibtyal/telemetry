<template>
  <div>
    <h2>{{ $t('real_time_data') }}</h2>
    <div v-if="connected">
      <p><strong>{{ $t('voltage') }}:</strong> {{ voltage }}</p>
      <p><strong>{{ $t('current') }}:</strong> {{ current }}</p>
      <p><strong>{{ $t('temperature') }}:</strong> {{ temperature }}</p>
      <p><strong>{{ $t('rpm') }}:</strong> {{ rpm }}</p>
      <p><strong>{{ $t('speed') }}:</strong> {{ speed }}</p>
      <p><strong>{{ $t('soc') }}:</strong> {{ soc }}</p>
    </div>
  </div>
</template>

<script>
export default {
  data() {
    return {
      socket: null,
      voltage: null,
      current: null,
      temperature: null,
      rpm: null,
      speed: null,
      soc: null
    };
  },
  methods: {
    connectWebSocket() {
      // Conectar al WebSocket de FastAPI
      this.socket = new WebSocket("ws://localhost:8000/ws-csv");

      // Manejar los mensajes que lleguen desde el servidor
      this.socket.onmessage = (event) => {
        const data = JSON.parse(event.data);
        this.voltage = data.voltage;
        this.current = data.current;
        this.temperature = data.temperature;
        this.rpm = data.rpm;
        this.speed = data.speed;
        this.soc = data.soc;
      };

      this.socket.onclose = () => {
        console.log("WebSocket cerrado, reconectando...");
        setTimeout(this.connectWebSocket, 1000);  // Reconectar después de 1 segundo
      };
    }
  },
  mounted() {
    this.connectWebSocket();  // Conectar al WebSocket al montar el componente
  },
  beforeUnmount() {
    if (this.socket) {
      this.socket.close();  // Cerrar el WebSocket cuando el componente se desmonte
    }
  }
};
</script>

<style>
/* Add some basic styling */
</style>

