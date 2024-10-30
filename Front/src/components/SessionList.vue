<template>
  <div>
    <h2>{{ $t("sessions_registered") }}</h2>
  </div>
  <div class="historial">
    <ul v-if="sessions.length">
      <li v-for="(session, index) in sessions" :key="index">
        <a :href="`/api/download/${session}`" download>{{ session }}</a>
      </li>
    </ul>
  </div>
</template>

<script>
import { ref, onMounted } from "vue";
import axios from "axios";

export default {
  name: "SessionList",
  setup() {
    const sessions = ref([]);

    onMounted(async () => {
      try {
        // Solicitud GET para obtener la lista de archivos CSV
        const response = await axios.get("/sessions");
        // Accede al array en la clave `files` de la respuesta
        sessions.value = response.data.files;
      } catch (error) {
        console.error("Error al obtener las sesiones:", error);
      }
    });

    return { sessions };
  },
};
</script>

<style>
.historial {
  background-color: rgba(5, 13, 27, 0.836);
  width: 70%;
  height: auto;
  margin-top: 20px;
  margin-left: 5%;
  padding: 20px;
  border-radius: 10px;
  align-items: center;
}
.historial ul {
  height: 450px;
  width: auto;
  overflow-y: auto;
}

.historial ul li {
  list-style: none;
  text-decoration: none;
}
</style>
