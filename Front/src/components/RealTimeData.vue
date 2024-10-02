<template>
  <div>
    <h2>{{ $t('real_time_data') }}</h2>
    <div v-if="connected">
      <p>{{ $t('voltage') }}: {{ data.voltage }}</p>
      <p>{{ $t('current') }}: {{ data.current }}</p>
      <p>{{ $t('temperature') }}: {{ data.temperature }}</p>
      <p>{{ $t('rpm') }}: {{ data.rpm }}</p>
      <p>{{ $t('speed') }}: {{ data.speed }}</p>
      <p>{{ $t('soc') }}: {{ data.soc }}</p>
    </div>
    <div v-else>
      <p>{{ $t('connecting') }}</p>
    </div>
    <button @click="disconnect">{{ $t('disconnect') }}</button>
  </div>
</template>

<script>
export default {
  data() {
    return {
      socket: null,
      data: {
        voltage: 0,
        current: 0,
        temperature: 0,
        rpm: 0,
        speed: 0,
        soc: 0
      },
      connected: false
    }
  },
  mounted() {
    this.connectWebSocket()
  },
  methods: {
    connectWebSocket() {
      this.socket = new WebSocket('wss://www.vehiculoelectricosiima.com/ws')
      this.socket.onopen = () => {
        this.connected = true
      }
      this.socket.onmessage = (event) => {
        this.data = JSON.parse(event.data)
      }
      this.socket.onclose = () => {
        this.connected = false
      }
    },
    disconnect() {
      if (this.socket) {
        this.socket.close()
      }
    }
  },
  beforeUnmount() {
    this.disconnect()
  }
}
</script>

<style>
/* Add some basic styling */
</style>

